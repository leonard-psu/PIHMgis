#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>

#include "5DataModelLoader/6LcDataFile/lcdatafile.h"
#include "ui_lcdatafile.h"

#include "0LibsIO/IOProjectFile.h"
#include "0LibsOther/pedo_transfer_functions.h"
#include "globals.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// LcDataFile Constructor
// Parent is Main Window, filename is the open project text file used to store project details
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LcDataFile::LcDataFile(QWidget *parent, QString filename) :
    QDialog(parent),
    ui(new Ui::LcDataFile)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start LcDataFile";

    try {

        ui->setupUi(this);

        filename_open_project = filename;
        bool found_file = false;

        QFile ProjectFile(filename_open_project);
        if ( ! ProjectFile.open(QIODevice::ReadOnly | QIODevice::Text) )
        {
            Log_Error_Message("Unable to Open File: " + filename_open_project + tr("<br>"));
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
        qDebug() << "Error: LcDataFile is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MeshDataFile Deconstructor
// Todo: Check for memory leaks
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LcDataFile::~LcDataFile()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ~LcDataFile";

    try {
        delete ui;
    } catch (...) {
        qDebug() << "Error: ~LcDataFile is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check Log_Error_Message
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LcDataFile::Log_Warning_Message(QString message)
{
    try {
        LogsString.append(tr("<span style=\"color:#FF0000\">Warning: ") + message + " </span>")+tr("<br>");
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();
    } catch (...) {
        qDebug() << "Error: Log_Error_Message is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check Log_Error_Message
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LcDataFile::Log_Error_Message(QString message)
{
    try {
        LogsString.append(tr("<span style=\"color:#FF0000\">Error: ") + message + " </span>")+tr("<br>");
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();
    } catch (...) {
        qDebug() << "Error: Log_Error_Message is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Load_Project_Settings
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool LcDataFile::Load_Project_Settings()
{
    if (print_debug_messages)
        qDebug() << "INFO: LcDataFile::Load_Project_Settings()";

    try {

        //Data Model OUTPUT File Name
        QStringList ModuleStringList = ReadModuleLine(filename_open_project,tr("TINShapeLayer"));
        if ( ModuleStringList.length() > 0  )
        {
            QString TempFileName = ModuleStringList.at(3);
            TempFileName = TempFileName.right(TempFileName.length()-TempFileName.lastIndexOf("/")-1);
            TempFileName.replace( QString(".shp"), QString(".lc") );
            QString fname = user_pihmgis_root_folder+"/4DataModelLoader/"+TempFileName;
            Check_LCData_Output(fname,true);
        }

        ModuleStringList = ReadModuleLine(filename_open_project,tr("MeshDataFile"));
        if ( ModuleStringList.length() > 0  )
        {
            QString TempFileName = ModuleStringList.at(9);
            QString fname = user_pihmgis_root_folder+"/4DataModelLoader/"+TempFileName+".lc";
            Check_LCData_Output(fname,true);
        }
        //End: Set Defaults

        //Start: Fill Form If Module Has Been Run Previously
        ModuleStringList = ReadModuleLine(filename_open_project,tr("LcDataFile"));
        if ( ModuleStringList.length() > 0 )
        {
            Check_LCTexture_Input(ModuleStringList.at(1));
            Check_LCData_Output(ModuleStringList.at(2),true);
        }
        //End: Fill Form If Module Has Been Run Previously

        pushButtonSetFocus();

    } catch (...) {
        qDebug() << "Error: LcDataFile::Load_Project_Settings is returning w/o checking";
        return false;
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to clear message log
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LcDataFile::Clear_Log()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshDataFile::Clear_Log()";

    try {

        LogsString = tr("");
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

    } catch (...) {
        qDebug() << "Error: LcDataFile::Clear_Log() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Check LCTexture File exists (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool LcDataFile::Check_LCTexture_Input(QString file){

    if(print_debug_messages)
        qDebug() << "INFO: Check_LCTexture_Input()";

    bool result = false;

    try {

        if(  fileExists(file) )
        {
            ui->lineEditLcClassFile->setStyleSheet("color: black;");
            ui->lineEditLcClassFile->setText(file);
            result = true;
        }
        else
        {
            ui->lineEditLcClassFile->setStyleSheet("color: red;");
            ui->lineEditLcClassFile->setText(file);

            Log_Error_Message("Missing LCTexture input file: " + file);

            result = false;
        }

    } catch (...) {
        qDebug() << "Error: Check_LCTexture_Input is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to assist if Check_SoilData_Output OUTPUT file exists (returns true) or does not (returns false)
// Will color red and warning if exists with color_and_message_if_exists=true
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool LcDataFile::Check_LCData_Output(QString file, bool color_and_message_if_exists){

    if(print_debug_messages)
        qDebug() << "INFO: Check_LCData_Output()";

    bool result = false;

    try {

        if(  fileExists(file) )
        {
            if(color_and_message_if_exists)
            {
                Log_Error_Message("Warning: MeshData output already exists: " + file +tr(" You may need to delete this file.<br>"));
            }

            ui->lineEditLcDataFile->setStyleSheet("color: red;");
            ui->lineEditLcDataFile->setText(file);
            result = true;
        }
        else
        {
            ui->lineEditLcDataFile->setStyleSheet("color: black;");
            ui->lineEditLcDataFile->setText(file);

            result = false;
        }

    } catch (...) {
        qDebug() << "Error: LcDataFile::Check_LCData_Output is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to focus button selection (needed for users w/o mouse)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LcDataFile::pushButtonSetFocus()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start LcDataFile::pushButtonSetFocus()";

    try {
        ui->pushButtonLcClassFile->setDefault(false);
        ui->pushButtonLcDataFile->setDefault(false);

        if (ui->lineEditLcClassFile->text() == nullptr)
        {
            ui->pushButtonLcClassFile->setDefault(true);
            ui->pushButtonLcClassFile->setFocus();
            return;
        }

        if (ui->lineEditLcDataFile->text() == nullptr)
        {
            ui->pushButtonLcDataFile->setDefault(true);
            ui->pushButtonLcDataFile->setFocus();
            return;
        }

        ui->pushButtonRun->setDefault(true);
        ui->pushButtonRun->setFocus();
    } catch (...) {
        qDebug() << "Error: LcDataFile::pushButtonSetFocus() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button LcClass Clicked Event (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LcDataFile::on_pushButtonLcClassFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start LcDataFile::on_pushButtonLcClassFile_clicked()";

    try {

        Clear_Log();

        QString LcClassFileName = QFileDialog::getOpenFileName(this, "Lc class File Name", user_pihmgis_root_folder, "Lc Class File(*.txt *.TXT)");

        if ( LcClassFileName != nullptr)
        {
            Check_LCTexture_Input(LcClassFileName);
            pushButtonSetFocus();
        }

    } catch (...) {
        qDebug() << "Error: LcDataFile::on_pushButtonLcClassFile_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button LcData Clicked Event (OUTPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LcDataFile::on_pushButtonLcDataFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start LcDataFile::on_pushButtonLcDataFile_clicked()";

    try {

        Clear_Log();

        QString LcDataFileName = QFileDialog::getSaveFileName(this, "Choose Lc Data File Name", user_pihmgis_root_folder+"/4DataModelLoader","Lc Data File(*.lc)");
        QString tempString = LcDataFileName;
        if ( LcDataFileName != nullptr)
        {
            if( ! (tempString.toLower()).endsWith(".lc") )
            {
                tempString.append(".lc");
                LcDataFileName = tempString;
            }
            Check_LCData_Output(LcDataFileName,true);
            pushButtonSetFocus();
        }


    } catch (...) {
        qDebug() << "Error: LcDataFile::on_pushButtonLcDataFile_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Run Button Clicked Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LcDataFile::on_pushButtonRun_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start LcDataFile::on_pushButtonRun_clicked()";

    try {

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Clear Log
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Clear_Log();

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check Input
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QString input_LCTexture_filename = ui->lineEditLcClassFile->text();

        bool checked_LCTexture = Check_LCTexture_Input(input_LCTexture_filename);
        if(!checked_LCTexture)
        {
            Log_Error_Message("LC Texture File (*.txt *.TXT) Input File Missing " + input_LCTexture_filename + tr("<br>"));
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check Output
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QString output_LCData_filename = ui->lineEditLcDataFile->text();

        bool output_check = Check_LCData_Output(output_LCData_filename, true);
        if(output_check)
        {
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check file access
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if ( ! CheckFileAccess(input_LCTexture_filename, "ReadOnly") )
        {
            Log_Error_Message("No Read Access to " + input_LCTexture_filename + tr("<br>"));
            return;
        }

        if ( ! CheckFileAccess(output_LCData_filename, "WriteOnly") )
        {
            Log_Error_Message("No Write Access to " + output_LCData_filename + tr("<br>"));
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Running Mesh Data File
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        LogsString.append("Running Lc Data File ... <br>");
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

        int ErrorLc = Lc_PedoTransferFunction( input_LCTexture_filename, output_LCData_filename );

        if( ErrorLc != 0 )
        {
            Log_Error_Message("LC Data File Processing Failed ... </span>"+tr("<br>"));
            Log_Error_Message("LC error return code: " + QString::number(ErrorLc)+tr("<br>"));
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update Project file
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QStringList ProjectIOStringList;
        ProjectIOStringList << "LcDataFile" << input_LCTexture_filename << input_LCTexture_filename;
        WriteModuleLine(filename_open_project, ProjectIOStringList);
        ProjectIOStringList.clear();

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update Message box
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Clear_Log();

        LogsString.append(tr("<br><b>Lc Data File Processing Complete.</b>")+tr("<br>"));
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

        ui->pushButtonRun->setDefault(false);
        ui->pushButtonClose->setDefault(true);
        ui->pushButtonClose->setFocus();


    } catch (...) {
        qDebug() << "Error: LcDataFile::on_pushButtonRun_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Close button event
// TODO, Decide on keeping button next highlights or not
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LcDataFile::on_pushButtonClose_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start LcDataFile::on_pushButtonClose_clicked()";

    try {
        //QStringList default_params; default_params << "WORKFLOW5" << "INIT";
        //QMetaObject::invokeMethod(parent(),"set_defaults",Q_ARG(QStringList,default_params));
        close();

    } catch (...) {
        qDebug() << "Error: LcDataFile::on_pushButtonClose_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Help button event
// TODO, Need cataract server back online
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LcDataFile::on_pushButtonHelp_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start LcDataFile::on_pushButtonHelp_clicked()";

    try {
        //        LogsString = tr("");
        //        if ( ! QDesktopServices::openUrl(QUrl("http://cataract.cee.psu.edu/PIHM/index.php/PIHMgis_3.0#lc_Data_File")) )
        //            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Load HTTP Link ... </span>")+tr("<br>"));
        //        ui->textBrowserLogs->setHtml(LogsString);
        //        ui->textBrowserLogs->repaint();
    } catch (...) {
        qDebug() << "Error: LcDataFile::on_pushButtonHelp_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// User edited LcClass Event (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LcDataFile::on_lineEditLcClassFile_textEdited(const QString &arg1)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start LcDataFile::on_lineEditLcClassFile_textEdited()";

    try {

        Check_LCTexture_Input(arg1);

    } catch (...) {
        qDebug() << "Error: LcDataFile::on_lineEditLcClassFile_textEdited() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// User edited output Event (OUTPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LcDataFile::on_lineEditLcDataFile_textEdited(const QString &arg1)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start LcDataFile::on_lineEditLcDataFile_textEdited()";

    try {

        Check_LCData_Output(arg1, true);

    } catch (...) {
        qDebug() << "Error: LcDataFile::on_lineEditLcDataFile_textEdited() is returning w/o checking";
    }
}
