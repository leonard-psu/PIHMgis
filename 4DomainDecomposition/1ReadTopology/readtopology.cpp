#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>

#include "readtopology.h"
#include "ui_readtopology.h"

#include "0LibsIO/IOProjectFile.h"
#include "0LibsOther/shape_pslg.h"
#include "globals.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ReadTopology Constructor
// Parent is Main Window, filename is the open project text file used to store project details
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ReadTopology::ReadTopology(QWidget *parent, QString filename) :
    QDialog(parent),
    ui(new Ui::ReadTopology)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ReadTopology";

    try {
        ui->setupUi(this);

        filename_open_project = filename;
        bool found_file = false;

        QFile ProjectFile(filename_open_project);
        if ( ProjectFile.open(QIODevice::ReadOnly | QIODevice::Text) == false)
        {
            Log_Error_Message("Unable to Open File: " + filename_open_project );
        }
        else
        {
            found_file = true;
        }
        ProjectFile.close();

        if(found_file)
        {
            Load_Project_Settings();
        }

        pushButtonSetFocus();

    } catch (...) {
        qDebug() << "Error: ReadTopology is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ReadTopology Deconstructor
// Todo: Check for memory leaks
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ReadTopology::~ReadTopology()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ~ReadTopology()";

    try {
        delete ui;
    } catch (...) {
        qDebug() << "Error: ~ReadTopology() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Load_Project_Settings
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ReadTopology::Load_Project_Settings()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ReadTopology::Load_Project_Settings";

    try {

        QStringList ModuleStringList = ReadModuleLine(filename_open_project,tr("MergeVectorDomainDecomposition"));
        if ( ModuleStringList.length() > 0  )
        {

            QString MergeVectorFileName = ModuleStringList.at(2);
            Check_MergeVector_Input(MergeVectorFileName);

            bool file1_check = Check_File_Valid(MergeVectorFileName);
            if(file1_check)
            {
                QString file2 = MergeVectorFileName;
                file2.replace(QString(".shp"),QString(".poly"));
                bool file2_check = Check_File_Valid(file2);
                Check_PSLG_Output(file2,true);
            }
        }

        ModuleStringList = ReadModuleLine(filename_open_project,tr("ReadTopology"));

        if ( ModuleStringList.length() > 0 )
        {
            QString file1 = ModuleStringList.at(1);
            Check_MergeVector_Input(file1);

            QString file2 = ModuleStringList.at(2);
            bool file2_check = Check_File_Valid(file2);
            ui->lineEditPSLG->setText(file2);
            Check_PSLG_Output(file2, true);
        }

        pushButtonSetFocus();

    } catch (...) {
        qDebug() << "Error: ReadTopology::Load_Project_Settings is returning w/o checking";
        return false;
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to assist if input file exists (returns true) or does not (returns false)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ReadTopology::Check_File_Valid(QString file)
{
    if(print_debug_messages)
        qDebug() << "INFO: Check_File_Valid()";

    bool result = false;

    try {

        if( fileExists(file) )
        {
            result = true;

            qint64 size = file_Size(file);

            if( size < 1)
            {
                Log_Error_Message("Check_File_Valid failed, file : " + file );
                Log_Error_Message("Check_File_Valid failed, invalid file size: " + QString::number(size) );
                result = false;
            }
        }

    } catch (...) {
        qDebug() << "Error: Check_File_Valid is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to clear message log
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ReadTopology::Clear_Log()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ReadTopology::Clear_Log()";

    try {

        LogsString = tr("");
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

    } catch (...) {
        qDebug() << "Error: ReadTopology::Clear_Log() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check Log_Error_Message
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ReadTopology::Log_Error_Message(QString message)
{
    try {
        LogsString.append(tr("<span style=\"color:#FF0000\">Error: ") + message + " </span>" +tr("<br>"));
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

        if(redirect_debug_messages_to_log)
        {
            ((PIHMgisDialog*)this->parent())->Log_Message( message );
        }

    } catch (...) {
        qDebug() << "Error: Log_Error_Message is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check Log_Error_Message
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ReadTopology::Log_Message(QString message)
{
    try {
        LogsString.append(tr("<span style=\"color:#000000\"> ") + message + " </span>" + tr("<br>"));
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

        if(redirect_debug_messages_to_log)
        {
            ((PIHMgisDialog*)this->parent())->Log_Message( message );
        }

    } catch (...) {
        qDebug() << "Error: Log_Message is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to focus button selection (needed for users w/o mouse)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ReadTopology::pushButtonSetFocus()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ReadTopology::pushButtonSetFocus()";

    try {
        ui->pushButtonMerge->setDefault(false);
        ui->pushButtonPSLG->setDefault(false);
        ui->pushButtonRun->setDefault(false);

        if (ui->lineEditMerge->text() == nullptr)
        {
            ui->pushButtonMerge->setDefault(true);
            ui->pushButtonMerge->setFocus();
            return;
        }
        if (ui->lineEditPSLG->text() == nullptr)
        {
            ui->pushButtonPSLG->setDefault(true);
            ui->pushButtonPSLG->setFocus();
            return;
        }

        ui->pushButtonRun->setDefault(true);
        ui->pushButtonRun->setFocus();
    } catch (...) {
        qDebug() << "Error: ReadTopology::pushButtonSetFocus() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button Clicked Event for CatchmentGrids (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ReadTopology::Check_MergeVector_Input(QString file)
{
    if(print_debug_messages)
        qDebug() << "INFO: Check_MergeVector_Input()";

    bool result = false;

    try {

        if( fileExists(file) )
        {
            ui->lineEditMerge->setStyleSheet("color: black;");
            ui->lineEditMerge->setText(file);
            result = true;
        }
        else
        {
            ui->lineEditMerge->setStyleSheet("color: red;");
            ui->lineEditMerge->setText(file);

            Log_Error_Message("MergeVector input does not exist: " + file );
            result = false;
        }
    } catch (...) {
        qDebug() << "Error: Check_MergeVector_Input is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to assist if CatchmentPolygon OUTPUT file exists (returns true) or does not (returns false)
// Will color red and warning if exists with color_and_message_if_exists=true
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ReadTopology::Check_PSLG_Output(QString file, bool color_and_message_if_exists)
{
    if(print_debug_messages)
        qDebug() << "INFO: Check_PSLG_Output()";

    bool result = false;

    try {

        if( fileExists(file) )
        {
            if(color_and_message_if_exists)
            {
                Log_Error_Message("PLSG output already exists: " + file + " You may need to delete these files.");
            }

            ui->lineEditPSLG->setStyleSheet("color: red;");
            ui->lineEditPSLG->setText(file);
            result = true;
        }
        else
        {
            ui->lineEditPSLG->setStyleSheet("color: black;");
            ui->lineEditPSLG->setText(file);

            result = false;
        }

    } catch (...) {
        qDebug() << "Error: Check_PSLG_Output is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button Clicked Event  (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ReadTopology::on_pushButtonMerge_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ReadTopology::on_pushButtonMerge_clicked()";

    try {

        Clear_Log();

        QString MergeVectorFileName = QFileDialog::getOpenFileName(this, "Choose Merge Vector File", user_pihmgis_root_folder+tr("/3DomainDecomposition"), "Vector Shape File(*.shp *.SHP)");
        if ( MergeVectorFileName.isNull() == false)
        {
            if( MergeVectorFileName.isEmpty() == false)
            {
                Check_MergeVector_Input(MergeVectorFileName);

                QString output = MergeVectorFileName;
                output.replace(QString(".shp"),QString(".poly"));
                Check_PSLG_Output(output,true);

                pushButtonSetFocus();
            }
        }
        //else do nothing

    } catch (...) {
        qDebug() << "Error: ReadTopology::on_pushButtonMerge_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button Clicked Event  (OUTPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ReadTopology::on_pushButtonPSLG_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ReadTopology::on_pushButtonPSLG_clicked()";

    try {

        QString PSLGFileName = QFileDialog::getSaveFileName(this, "Choose Planar Straight Line Graph", user_pihmgis_root_folder +"/3DomainDecomposition","PSLG File(*.poly)");
        if ( PSLGFileName.isNull() == false)
        {
            if( PSLGFileName.isEmpty() == false)
            {
                QString output = PSLGFileName;
                if( (output.toLower()).endsWith(".shp") == false )
                {
                    output.append(".shp");
                    PSLGFileName = output;
                }
                Check_PSLG_Output(PSLGFileName, true);

                pushButtonSetFocus();
            }
        }
        //else do nothing

    } catch (...) {
        qDebug() << "Error: ReadTopology::on_pushButtonPSLG_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Run Button Clicked Event  (OUTPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ReadTopology::on_pushButtonRun_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ReadTopology::on_pushButtonRun_clicked()";

    try {

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Clear Log
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Clear_Log();

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check inputs
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QString input_filename =  ui->lineEditMerge->text();

        bool input_filenameCheck = Check_MergeVector_Input(input_filename);
        if(input_filenameCheck == false)
        {
            Log_Error_Message("MergeVector Input File Missing ");
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Does output already exist?
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QString output_filename =  ui->lineEditPSLG->text();
        bool output_filenameCheck = Check_PSLG_Output(output_filename, false);
        if(output_filenameCheck)
        {
            Log_Error_Message("PSLG Output already exists ");
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check file access
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if ( CheckFileAccess(input_filename, "ReadOnly") == false)
        {
            Log_Error_Message("No Read Access to ... " + input_filename);
            return;
        }

        if ( CheckFileAccess(output_filename, "WriteOnly") == false)
        {
            Log_Error_Message("Unable to Write Access ... " + output_filename );
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Running Read Topology
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Log_Message("Running Read Topology ... ");

        // Note using logstring here.
        int ErrorPSLG = shape_pslg(input_filename, output_filename, &LogsString);
        if( ErrorPSLG != 0 )
        {
            Log_Error_Message("Read Topology Processing Failed ... ");
            Log_Error_Message("RETURN CODE: ... " + QString::number(ErrorPSLG) );
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check output filenames
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        output_filenameCheck = Check_PSLG_Output(output_filename, false);
        if(output_filenameCheck == false)
        {
            Log_Error_Message("CatchmentPolygon failed, file does not exist: " + output_filename );
            return;
        }

        qint64 size = file_Size(output_filename);
        if( size < 1)
        {
            Log_Error_Message("CatchmentPolygon failed, invalid file size: " + QString::number(size) );
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update Project file
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QStringList ProjectIOStringList;
        ProjectIOStringList << "ReadTopology" << input_filename << output_filename;
        WriteModuleLine(filename_open_project, ProjectIOStringList);
        ProjectIOStringList.clear();

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update Message box
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Clear_Log();

        Log_Message("Read Topology Processing Completed.");

        ui->pushButtonRun->setDefault(false);
        ui->pushButtonClose->setDefault(true);
        ui->pushButtonClose->setFocus();


    } catch (...) {
        qDebug() << "Error: ReadTopology::on_pushButtonRun_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Close button event
// TODO, Decide on keeping button next highlights or not
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ReadTopology::on_pushButtonClose_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ReadTopology::on_pushButtonClose_clicked()";

    try {
        //QStringList default_params; default_params << "WORKFLOW4" << "TRIANGLE";
        //QMetaObject::invokeMethod(parent(),"set_defaults",Q_ARG(QStringList,default_params));
        close();
    } catch (...) {
        qDebug() << "Error: ReadTopology::on_pushButtonClose_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Help button event
// TODO, Need cataract server back online
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ReadTopology::on_pushButtonHelp_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ReadTopology::on_pushButtonHelp_clicked()";

    try {
        //        LogsString = tr("");
        //        if ( ! QDesktopServices::openUrl(QUrl("http://cataract.cee.psu.edu/PIHM/index.php/PIHMgis_3.0#Read_Topology")) )
        //            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Load HTTP Link ... </span>")+tr("<br>"));
        //        ui->textBrowserLogs->setHtml(LogsString);
        //        ui->textBrowserLogs->repaint();
    } catch (...) {
        qDebug() << "Error: ReadTopology::on_pushButtonHelp_clicked() is returning w/o checking";
    }
}
