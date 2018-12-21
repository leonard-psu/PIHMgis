#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>

#include "soildatafile.h"
#include "ui_soildatafile.h"

#include "0LibsIO/IOProjectFile.h"
#include "0LibsOther/pedo_transfer_functions.h"
#include "globals.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SoilDataFile Constructor
// Parent is Main Window, filename is the open project text file used to store project details
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SoilDataFile::SoilDataFile(QWidget *parent, QString filename) :
    QDialog(parent),
    ui(new Ui::SoilDataFile)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start SoilDataFile";

    try {

        ui->setupUi(this);

        filename_open_project = filename;
        bool found_file = false;

        QFile ProjectFile(filename_open_project);
        if ( ! ProjectFile.open(QIODevice::ReadOnly | QIODevice::Text) )
        {
            Log_Error_Message("Unable to Open File: " + filename_open_project  );
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
        qDebug() << "Error: SoilDataFile is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SoilDataFile Deconstructor
// Todo: Check for memory leaks
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SoilDataFile::~SoilDataFile()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ~SoilDataFile";

    try {
        delete ui;
    } catch (...) {
        qDebug() << "Error: ~SoilDataFile is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check Log_Error_Message
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoilDataFile::Log_Warning_Message(QString message)
{
    try {
        LogsString.append(tr("<span style=\"color:#FF0000\">Warning: ") + message + " </span>")+tr("<br>");
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
void SoilDataFile::Log_Error_Message(QString message)
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
void SoilDataFile::Log_Message(QString message)
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
// Load_Project_Settings
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SoilDataFile::Load_Project_Settings()
{
    if (print_debug_messages)
        qDebug() << "INFO: MeshDataFile::Load_Project_Settings()";

    try {

        //Data Model OUTPUT File Name
        QStringList ModuleStringList = ReadModuleLine(filename_open_project,tr("TINShapeLayer"));
        if ( ModuleStringList.length() > 0  )
        {
            QString TempFileName = ModuleStringList.at(3);
            TempFileName = TempFileName.right(TempFileName.length()-TempFileName.lastIndexOf("/")-1);
            TempFileName.replace( QString(".shp"), QString(".soil") );
            Check_SoilData_Output(user_pihmgis_root_folder+"/4DataModelLoader/"+TempFileName, true);
        }

        ModuleStringList = ReadModuleLine(filename_open_project,tr("MeshDataFile"));
        if ( ModuleStringList.length() > 0  )
        {
            QString TempFileName = ModuleStringList.at(9);
            Check_SoilData_Output(user_pihmgis_root_folder+"/4DataModelLoader/"+TempFileName+".soil", true);
        }
        //End: Set Defaults

        //Start: Fill Form If Module Has Been Run Previously
        ModuleStringList = ReadModuleLine(filename_open_project,tr("SoilDataFile"));

        if ( ModuleStringList.length() > 0 )
        {
            Check_SoilTexture_Input(ModuleStringList.at(1));
            Check_SoilData_Output(ModuleStringList.at(2), true);
        }
        //End: Fill Form If Module Has Been Run Previously

        pushButtonSetFocus();

    } catch (...) {
        qDebug() << "Error: MeshDataFile::Load_Project_Settings is returning w/o checking";
        return false;
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to clear message log
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoilDataFile::Clear_Log()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start SoilDataFile::Clear_Log()";

    try {

        LogsString = tr("");
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

    } catch (...) {
        qDebug() << "Error: SoilDataFile::Clear_Log() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Check SoilTexture File exists (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SoilDataFile::Check_SoilTexture_Input(QString file){

    if(print_debug_messages)
        qDebug() << "INFO: Check_SoilTexture_Input()";

    bool result = false;

    try {

        if(  fileExists(file) )
        {
            ui->lineEditSoilTextureFile->setStyleSheet("color: black;");
            ui->lineEditSoilTextureFile->setText(file);
            result = true;
        }
        else
        {
            ui->lineEditSoilTextureFile->setStyleSheet("color: red;");
            ui->lineEditSoilTextureFile->setText(file);

            Log_Error_Message("Missing soil input file: " + file);
            result = false;
        }

    } catch (...) {
        qDebug() << "Error: Check_SoilTexture_Input is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to assist if Check_SoilData_Output OUTPUT file exists (returns true) or does not (returns false)
// Will color red and warning if exists with color_and_message_if_exists=true
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SoilDataFile::Check_SoilData_Output(QString file, bool color_and_message_if_exists){

    if(print_debug_messages)
        qDebug() << "INFO: Check_MeshData_Output()";

    bool result = false;

    try {

        if(  fileExists(file) )
        {
            if(color_and_message_if_exists)
            {
                Log_Warning_Message("Soil output already exists: " + file + " You may need to delete this file.");
            }

            ui->lineEditSoilDataFile->setStyleSheet("color: red;");
            ui->lineEditSoilDataFile->setText(file);
            result = true;
        }
        else
        {
            ui->lineEditSoilDataFile->setStyleSheet("color: black;");
            ui->lineEditSoilDataFile->setText(file);

            result = false;
        }

    } catch (...) {
        qDebug() << "Error: SoilDataFile::Check_MeshData_Output is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to focus button selection (needed for users w/o mouse)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoilDataFile::pushButtonSetFocus()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start SoilDataFile::pushButtonSetFocus()";

    try {
        ui->pushButtonSoilTextureFile->setDefault(false);
        ui->pushButtonSoilDataFile->setDefault(false);

        if (ui->lineEditSoilTextureFile->text() == nullptr)
        {
            ui->pushButtonSoilTextureFile->setDefault(true);
            ui->pushButtonSoilTextureFile->setFocus();
            return;
        }

        if (ui->lineEditSoilDataFile->text() == nullptr)
        {
            ui->pushButtonSoilDataFile->setDefault(true);
            ui->pushButtonSoilDataFile->setFocus();
            return;
        }

        ui->pushButtonRun->setDefault(true);
        ui->pushButtonRun->setFocus();
    } catch (...) {
        qDebug() << "Error: SoilDataFile::pushButtonSetFocus() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button SoilTexture Clicked Event (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoilDataFile::on_pushButtonSoilTextureFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start SoilDataFile::on_pushButtonSoilTextureFile_clicked()";

    try {

        Clear_Log();

        QString SoilTextureFileName = QFileDialog::getOpenFileName(this, "Soil Texture File Name", user_pihmgis_root_folder, "Soil Texture File(*.txt *.TXT)");

        if ( SoilTextureFileName != nullptr)
        {
            Check_SoilTexture_Input(SoilTextureFileName);
            pushButtonSetFocus();
        }
    } catch (...) {
        qDebug() << "Error: SoilDataFile::on_pushButtonSoilTextureFile_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button SoilData Clicked Event (OUTPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoilDataFile::on_pushButtonSoilDataFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start SoilDataFile::on_pushButtonSoilDataFile_clicked()";

    try {

        Clear_Log();

        QString SoilDataFileName = QFileDialog::getSaveFileName(this, "Choose Soil Data File Name", user_pihmgis_root_folder+"/4DataModelLoader","Soil Data File(*.soil)");
        QString tempString = SoilDataFileName;
        if ( SoilDataFileName != nullptr)
        {
            if( ! (tempString.toLower()).endsWith(".soil") )
            {
                tempString.append(".soil");
                SoilDataFileName = tempString;
            }
            Check_SoilData_Output(SoilDataFileName, true);
            pushButtonSetFocus();
        }

    } catch (...) {
        qDebug() << "Error: SoilDataFile::on_pushButtonSoilDataFile_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Run Button Clicked Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoilDataFile::on_pushButtonRun_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start SoilDataFile::on_pushButtonRun_clicked()";

    try {

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Clear Log
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Clear_Log();

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check Input
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QString input_SoilTexture_filename = ui->lineEditSoilTextureFile->text();

        bool checked_SoilTexture = Check_SoilTexture_Input(input_SoilTexture_filename);
        if(!checked_SoilTexture)
        {
            Log_Error_Message("Soil Texture File (*.txt *.TXT) Input File Missing " + input_SoilTexture_filename );
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check Output
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QString output_SoilData_filename = ui->lineEditSoilDataFile->text();

        bool output_check = Check_SoilData_Output(output_SoilData_filename, true);
        if(output_check)
        {
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check file access
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if ( ! CheckFileAccess(input_SoilTexture_filename, "ReadOnly") )
        {
            Log_Error_Message("No Read Access to " + input_SoilTexture_filename  );
            return;
        }

        if ( ! CheckFileAccess(output_SoilData_filename, "WriteOnly") )
        {
            Log_Error_Message("No Write Access to " + output_SoilData_filename  );
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Running Mesh Data File
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Log_Message("Running Soil Data File ... ");

        int ErrorSoil = Soil_PedoTransferFunction( input_SoilTexture_filename, output_SoilData_filename );

        if( ErrorSoil != 0 )
        {
            Log_Error_Message("Soil Data File Processing Failed " );
            Log_Error_Message("Soil Error Return code: " + QString::number(ErrorSoil) );
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update Project file
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QStringList ProjectIOStringList;
        ProjectIOStringList << "SoilDataFile" << input_SoilTexture_filename << output_SoilData_filename;
        WriteModuleLine(filename_open_project, ProjectIOStringList);
        ProjectIOStringList.clear();

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update Message box
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Clear_Log();

        Log_Message("Soil Data File Processing Complete.");

        ui->pushButtonRun->setDefault(false);
        ui->pushButtonClose->setDefault(true);
        ui->pushButtonClose->setFocus();

    } catch (...) {
        qDebug() << "Error: SoilDataFile::on_pushButtonRun_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Close button event
// TODO, Decide on keeping button next highlights or not
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoilDataFile::on_pushButtonClose_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start SoilDataFile::on_pushButtonClose_clicked()";

    try {
        //QStringList default_params; default_params << "WORKFLOW5" << "GEOL";
        //QMetaObject::invokeMethod(parent(),"set_defaults",Q_ARG(QStringList,default_params));
        close();
    } catch (...) {
        qDebug() << "Error: SoilDataFile::on_pushButtonClose_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Help button event
// TODO, Need cataract server back online
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoilDataFile::on_pushButtonHelp_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start SoilDataFile::on_pushButtonHelp_clicked()";

    try {
        //        LogsString = tr("");
        //        if ( ! QDesktopServices::openUrl(QUrl("http://cataract.cee.psu.edu/PIHM/index.php/PIHMgis_3.0#soil_Data_File")) )
        //            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Load HTTP Link ... </span>")+tr("<br>"));
        //        ui->textBrowserLogs->setHtml(LogsString);
        //        ui->textBrowserLogs->repaint();
    } catch (...) {
        qDebug() << "Error: SoilDataFile::on_pushButtonHelp_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// User edited SoilTexture Event (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoilDataFile::on_lineEditSoilTextureFile_textEdited(const QString &arg1)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start SoilDataFile::on_lineEditSoilTextureFile_textEdited()";

    try {

        Check_SoilTexture_Input(arg1);

    } catch (...) {
        qDebug() << "Error: SoilDataFile::on_lineEditSoilTextureFile_textEdited() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// User edited output Event (OUTPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoilDataFile::on_lineEditSoilDataFile_textEdited(const QString &arg1)
{

    if(print_debug_messages)
        qDebug() << "INFO: Start SoilDataFile::on_lineEditSoilTextureFile_textEdited()";

    try {

        Check_SoilData_Output(arg1, true);

    } catch (...) {
        qDebug() << "Error: SoilDataFile::on_lineEditSoilTextureFile_textEdited() is returning w/o checking";
    }
}
