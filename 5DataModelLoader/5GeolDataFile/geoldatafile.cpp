#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>

#include "geoldatafile.h"
#include "ui_geoldatafile.h"

#include "0LibsIO/IOProjectFile.h"
#include "0LibsOther/pedo_transfer_functions.h"
#include "globals.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GeolDataFile Constructor
// Parent is Main Window, filename is the open project text file used to store project details
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GeolDataFile::GeolDataFile(QWidget *parent, QString filename) :
    QDialog(parent),
    ui(new Ui::GeolDataFile)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start GeolDataFile";

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
        qDebug() << "Error: GeolDataFile is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GeolDataFile Deconstructor
// Todo: Check for memory leaks
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GeolDataFile::~GeolDataFile()
{  
    if(print_debug_messages)
        qDebug() << "INFO: Start ~GeolDataFile";

    try  {
        delete ui;
    } catch (...) {
        qDebug() << "Error: ~GeolDataFile is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check Log_Error_Message
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GeolDataFile::Log_Warning_Message(QString message)
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
void GeolDataFile::Log_Error_Message(QString message)
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
bool GeolDataFile::Load_Project_Settings()
{
    if (print_debug_messages)
        qDebug() << "INFO: GeolDataFile::Load_Project_Settings()";

    try {

        // ** Data Model OUTPUT File Name
        QStringList ModuleStringList = ReadModuleLine(filename_open_project,tr("TINShapeLayer"));
        if ( ModuleStringList.length() > 0  )
        {
            QString TempFileName = ModuleStringList.at(3);
            TempFileName = TempFileName.right(TempFileName.length()-TempFileName.lastIndexOf("/")-1);
            TempFileName.replace( QString(".shp"), QString(".geol") );
            QString output_filename = user_pihmgis_root_folder+"/4DataModelLoader/"+TempFileName;
            Check_GeolData_Output(output_filename, true);
        }

        ModuleStringList = ReadModuleLine(filename_open_project,tr("MeshDataFile"));
        if ( ModuleStringList.length() > 0  )
        {
            QString TempFileName = ModuleStringList.at(9);
            QString output_filename =  user_pihmgis_root_folder+"/4DataModelLoader/"+TempFileName+".geol";
            Check_GeolData_Output(output_filename, true);
        }
        // ** End: Set Defaults


        // ** Start: Fill Form If Module Has Been Run Previously

        ModuleStringList = ReadModuleLine(filename_open_project,tr("GeolDataFile"));
        if ( ModuleStringList.length() > 0 )
        {
            Check_GeolTexture_Input(ModuleStringList.at(1));
            Check_GeolData_Output(ModuleStringList.at(2), true);
        }
        // ** End: Fill Form If Module Has Been Run Previously

        pushButtonSetFocus();

    } catch (...) {
        qDebug() << "Error: GeolDataFile::Load_Project_Settings is returning w/o checking";
        return false;
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to clear message log
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GeolDataFile::Clear_Log()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshDataFile::Clear_Log()";

    try {

        LogsString = tr("");
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

    } catch (...) {
        qDebug() << "Error: GeolDataFile::Clear_Log() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Check SoilTexture File exists (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool GeolDataFile::Check_GeolTexture_Input(QString file){

    if(print_debug_messages)
        qDebug() << "INFO: Check_GeolTexture_Input()";

    bool result = false;

    try {

        if(  fileExists(file) )
        {
            ui->lineEditGeolTextureFile->setStyleSheet("color: black;");
            ui->lineEditGeolTextureFile->setText(file);
            result = true;
        }
        else
        {
            ui->lineEditGeolTextureFile->setStyleSheet("color: red;");
            ui->lineEditGeolTextureFile->setText(file);

            Log_Error_Message("Missing geology input file: " + file);

            result = false;
        }

    } catch (...) {
        qDebug() << "Error: Check_GeolTexture_Input is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to assist if Check_SoilData_Output OUTPUT file exists (returns true) or does not (returns false)
// Will color red and warning if exists with color_and_message_if_exists=true
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool GeolDataFile::Check_GeolData_Output(QString file, bool color_and_message_if_exists){

    if(print_debug_messages)
        qDebug() << "INFO: Check_GeolData_Output()";

    bool result = false;

    try {

        if(  fileExists(file) )
        {
            if(color_and_message_if_exists)
            {
                Log_Warning_Message("Geology output already exists: " + file +tr(" You may need to delete this file.<br>"));
            }

            ui->lineEditGeolDataFile->setStyleSheet("color: red;");
            ui->lineEditGeolDataFile->setText(file);
            result = true;
        }
        else
        {
            ui->lineEditGeolDataFile->setStyleSheet("color: black;");
            ui->lineEditGeolDataFile->setText(file);

            result = false;
        }

    } catch (...) {
        qDebug() << "Error: GeolDataFile::Check_GeolData_Output is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to focus button selection (needed for users w/o mouse)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GeolDataFile::pushButtonSetFocus()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start GeolDataFile::pushButtonSetFocus()";

    try  {
        ui->pushButtonGeolTextureFile->setDefault(false);
        ui->pushButtonGeolDataFile->setDefault(false);

        if (ui->lineEditGeolTextureFile->text() == nullptr)
        {
            ui->pushButtonGeolTextureFile->setDefault(true);
            ui->pushButtonGeolTextureFile->setFocus();
            return;
        }

        if (ui->lineEditGeolDataFile->text() == nullptr)
        {
            ui->pushButtonGeolDataFile->setDefault(true);
            ui->pushButtonGeolDataFile->setFocus();
            return;
        }

        ui->pushButtonRun->setDefault(true);
        ui->pushButtonRun->setFocus();

    } catch (...) {
        qDebug() << "Error: GeolDataFile::pushButtonSetFocus() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button GeolTexture Clicked Event (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GeolDataFile::on_pushButtonGeolTextureFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start GeolDataFile::on_pushButtonGeolTextureFile_clicked()";

    try  {

        Clear_Log();

        QString GeolTextureFileName = QFileDialog::getOpenFileName(this, "Geol Texture File Name", user_pihmgis_root_folder, "Geol Texture File(*.txt *.TXT)");

        if ( GeolTextureFileName != nullptr)
        {
            Check_GeolTexture_Input(GeolTextureFileName);
            pushButtonSetFocus();
        }

    } catch (...) {
        qDebug() << "Error: GeolDataFile::on_pushButtonGeolTextureFile_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button GeolData Clicked Event (OUTPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GeolDataFile::on_pushButtonGeolDataFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start GeolDataFile::on_pushButtonGeolDataFile_clicked()";

    try  {

        Clear_Log();

        QString GeolDataFileName = QFileDialog::getSaveFileName(this, "Choose Geol Data File Name", user_pihmgis_root_folder+"/4DataModelLoader","Geol Data File(*.geol)");
        QString tempString = GeolDataFileName;
        if ( GeolDataFileName != nullptr)
        {
            if( ! (tempString.toLower()).endsWith(".geol") )
            {
                tempString.append(".geol");
                GeolDataFileName = tempString;
            }
            Check_GeolData_Output(GeolDataFileName, true);

            pushButtonSetFocus();
        }


    } catch (...) {
        qDebug() << "Error: GeolDataFile::on_pushButtonGeolDataFile_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Run Button Clicked Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GeolDataFile::on_pushButtonRun_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start GeolDataFile::on_pushButtonRun_clicked()";

    try  {

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Clear Log
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Clear_Log();

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check Input
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QString input_GeolTexture_filename = ui->lineEditGeolTextureFile->text();

        bool checked_GeolTexture = Check_GeolTexture_Input(input_GeolTexture_filename);
        if(!checked_GeolTexture)
        {
            Log_Error_Message("Geol Texture File (*.txt *.TXT) Input File Missing " + input_GeolTexture_filename + tr("<br>"));
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check Output
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QString output_GeolData_filename = ui->lineEditGeolDataFile->text();

        bool output_check = Check_GeolData_Output(output_GeolData_filename, true);
        if(output_check)
        {
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check file access
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if ( ! CheckFileAccess(input_GeolTexture_filename, "ReadOnly") )
        {
            Log_Error_Message("No Read Access to " + input_GeolTexture_filename + tr("<br>"));
            return;
        }

        if ( ! CheckFileAccess(output_GeolData_filename, "WriteOnly") )
        {
            Log_Error_Message("No Write Access to " + output_GeolData_filename + tr("<br>"));
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Running Mesh Data File
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        LogsString.append("Running Geol Data File ... <br>");
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

        int ErrorGeol = Geol_PedoTransferFunction( input_GeolTexture_filename, output_GeolData_filename );

        if( ErrorGeol != 0 )
        {
            Log_Error_Message("Geol Data File Processing Failed "+tr("<br>"));
            Log_Error_Message("Geol error return code: " + QString::number(ErrorGeol)+tr("<br>"));
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update Project file
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QStringList ProjectIOStringList;

        ProjectIOStringList << "GeolDataFile" << input_GeolTexture_filename << output_GeolData_filename;
        WriteModuleLine(filename_open_project, ProjectIOStringList);
        ProjectIOStringList.clear();


        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update Message box
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Clear_Log();

        LogsString.append(tr("<br><b>Geol Data File Processing Complete.</b>")+tr("<br>"));
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

        ui->pushButtonRun->setDefault(false);
        ui->pushButtonClose->setDefault(true);
        ui->pushButtonClose->setFocus();


    } catch (...) {
        qDebug() << "Error: GeolDataFile::on_pushButtonRun_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Close button event
// TODO, Decide on keeping button next highlights or not
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GeolDataFile::on_pushButtonClose_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start GeolDataFile::on_pushButtonClose_clicked()";

    try  {
        //QStringList default_params; default_params << "WORKFLOW5" << "LCXX";
        //QMetaObject::invokeMethod(parent(),"set_defaults",Q_ARG(QStringList,default_params));
        close();
    } catch (...) {
        qDebug() << "Error: GeolDataFile::on_pushButtonClose_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Help button event
// TODO, Need cataract server back online
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GeolDataFile::on_pushButtonHelp_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start GeolDataFile::on_pushButtonHelp_clicked()";

    try  {
        //        LogsString = tr("");
        //        if ( ! QDesktopServices::openUrl(QUrl("http://cataract.cee.psu.edu/PIHM/index.php/PIHMgis_3.0#geol_Data_File")) )
        //            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Load HTTP Link ... </span>")+tr("<br>"));
        //        ui->textBrowserLogs->setHtml(LogsString);
        //        ui->textBrowserLogs->repaint();
    } catch (...) {
        qDebug() << "Error: GeolDataFile::on_pushButtonHelp_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// User edited SoilTexture Event (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GeolDataFile::on_lineEditGeolTextureFile_textEdited(const QString &arg1)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start SoilDataFile::on_lineEditGeolTextureFile_textEdited()";

    try {

        Check_GeolTexture_Input(arg1);

    } catch (...) {
        qDebug() << "Error: SoilDataFile::on_lineEditGeolTextureFile_textEdited() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// User edited output Event (OUTPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GeolDataFile::on_lineEditGeolDataFile_textEdited(const QString &arg1)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start SoilDataFile::on_lineEditGeolDataFile_textEdited()";

    try {

        Check_GeolData_Output(arg1, true);

    } catch (...) {
        qDebug() << "Error: SoilDataFile::on_lineEditGeolDataFile_textEdited() is returning w/o checking";
    }
}




