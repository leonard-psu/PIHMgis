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
        if ( ! ProjectFile.open(QIODevice::ReadOnly | QIODevice::Text) )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Open File: </span>") + filename_open_project + tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
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
            ui->lineEditMerge->setText(ModuleStringList.at(2));
            QString file1 = ModuleStringList.at(2);
            bool file1_check = Check_File_Valid(file1);
            if(file1_check)
            {
                QString file2 = file1;
                file2.replace(QString(".shp"),QString(".poly"));
                bool file2_check = Check_File_Valid(file2);

                ui->lineEditPSLG->setText(file2);

                if(file2_check)
                {
                    ui->lineEditPSLG->setStyleSheet("Qt::black");
                }
                else
                {
                    LogsString.append(tr("<span style=\"color:#FF0000\">Error: ") + file2 + tr(" input does not exist. </span>") +tr("<br>"));
                    ui->lineEditPSLG->setStyleSheet("Qt::red");
                }
            }
        }

        ModuleStringList = ReadModuleLine(filename_open_project,tr("ReadTopology"));

        if ( ModuleStringList.length() > 0 )
        {
            QString file1 = ModuleStringList.at(1);
            bool file1_check = Check_File_Valid(file1);
            ui->lineEditMerge->setText(file1);
            if(file1_check)
            {
                ui->lineEditMerge->setStyleSheet("Qt::black");
            }
            else
            {
                LogsString.append(tr("<span style=\"color:#FF0000\">Error: ") + file1 + tr(" input does not exist. </span>") +tr("<br>"));
                ui->lineEditMerge->setStyleSheet("Qt::red");
            }

            QString file2 = ModuleStringList.at(2);
            bool file2_check = Check_File_Valid(file2);
            ui->lineEditPSLG->setText(file2);
            if(file2_check)
            {
                ui->lineEditPSLG->setStyleSheet("Qt::black");
            }
            else
            {
                LogsString.append(tr("<span style=\"color:#FF0000\">Error: ") + file2 + tr(" output does not exist. </span>") +tr("<br>"));
                ui->lineEditPSLG->setStyleSheet("Qt::red");
            }
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
            qDebug() << "size " << size;

            if( size < 1)
            {
                LogsString.append(tr("<span style=\"color:#FF0000\">Error: Check_File_Valid failed, file : </span>") + file +tr("<br>"));
                LogsString.append(tr("<span style=\"color:#FF0000\">Error: Check_File_Valid failed, invalid file size: </span>") + size +tr("<br>"));
                ui->textBrowserLogs->setHtml(LogsString);
                ui->textBrowserLogs->repaint();
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

        if(  fileExists(file) )
        {
            ui->lineEditMerge->setStyleSheet("color: black;");
            ui->lineEditMerge->setText(file);
            result = true;
        }
        else
        {
            ui->lineEditMerge->setStyleSheet("color: rgb(180, 0, 0);");
            ui->lineEditMerge->setText(file);

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
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ReadTopology::Check_PSLG_Output(QString file, bool message)
{
    if(print_debug_messages)
        qDebug() << "INFO: Check_PSLG_Output()";

    bool result = false;

    try {

        if(  fileExists(file) )
        {
            ui->lineEditPSLG->setStyleSheet("color: black;");
            ui->lineEditPSLG->setText(file);
            result = true;
        }
        else
        {
            ui->lineEditPSLG->setStyleSheet("color: rgb(180, 0, 0);");
            ui->lineEditPSLG->setText(file);

            if(message)
            {
                LogsString.append(tr("<span style=\"color:#FF0000\">Warning: CatchmentPolygon output does not exist: </span>") + file +tr(" You will need to redo this step.<br>"));
                ui->textBrowserLogs->setHtml(LogsString);
                ui->textBrowserLogs->repaint();
            }
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
        if ( MergeVectorFileName != nullptr)
        {

            Check_MergeVector_Input(MergeVectorFileName);

            QString output = MergeVectorFileName;
            output.replace(QString(".shp"),QString(".poly"));
            Check_PSLG_Output(output,true);

            pushButtonSetFocus();
        }


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
        if ( PSLGFileName != nullptr)
        {

            QString output = PSLGFileName;
            if( ! (output.toLower()).endsWith(".shp") )
            {
                output.append(".shp");
                PSLGFileName = output;
            }
            Check_PSLG_Output(PSLGFileName,true);

            pushButtonSetFocus();
        }

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
        if(!input_filenameCheck)
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: MergeVector Input File Missing </span>")+tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
            return;
        }


        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Does output already exist?
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QString output_filename =  ui->lineEditPSLG->text();
        bool output_filenameCheck = Check_PSLG_Output(output_filename, false);
        if(output_filenameCheck)
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: PSLG Output already exists </span>")+tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check file access
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if ( ! CheckFileAccess(input_filename, "ReadOnly") )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Read Access ... </span>") + input_filename + tr("<br>"));
            return;
        }

        if ( ! CheckFileAccess(output_filename, "WriteOnly") )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Write Access ... </span>") + output_filename +tr("<br>"));
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Running Read Topology
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        LogsString.append("Running Read Topology ... <br>");
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

        int ErrorPSLG = shape_pslg((char *)qPrintable(input_filename), (char *)qPrintable(output_filename), &LogsString);
        if( ErrorPSLG != 0 )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Read Topology Processing Failed ... </span>")+tr("<br>"));
            LogsString.append(tr("<span style=\"color:#FF0000\">RETURN CODE: ... </span>")+QString::number(ErrorPSLG)+tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
            return;
        }


        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check output filenames
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        output_filenameCheck = Check_PSLG_Output(output_filename, false);
        if(!output_filenameCheck)
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">Error: CatchmentPolygon failed, file does not exist: </span>") + output_filename +tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
            return;
        }

        qint64 size = file_Size(output_filename);
        if( size < 1)
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">Error: CatchmentPolygon failed, invalid file size: </span>") + size +tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
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

        LogsString.append(tr("<br><b>Read Topology Processing Completed.</b>")+tr("<br>"));
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

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
