#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>

#include "ibcdatafile.h"
#include "ui_ibcdatafile.h"

#include "0LibsIO/IOProjectFile.h"
#include "globals.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// IbcDataFile Constructor
// Parent is Main Window, filename is the open project text file used to store project details
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
IbcDataFile::IbcDataFile(QWidget *parent, QString filename) :
    QDialog(parent),
    ui(new Ui::IbcDataFile)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start IbcDataFile";

    try {

        ui->setupUi(this);

        filename_open_project = filename;
        bool found_file = false;

        QFile ProjectFile(filename_open_project);
        if ( ! ProjectFile.open(QIODevice::ReadOnly | QIODevice::Text) )
        {
            Log_Error_Message(tr("<span style=\"color:#FF0000\">ERROR: Unable to Open File: </span>") + filename_open_project + tr("<br>"));
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
        qDebug() << "Error: IbcDataFile is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// IbcDataFile Deconstructor
// Todo: Check for memory leaks
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
IbcDataFile::~IbcDataFile()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ~IbcDataFile";

    try {
        delete ui;
    } catch (...) {
        qDebug() << "Error: ~IbcDataFile is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Load_Project_Settings
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool IbcDataFile::Load_Project_Settings()
{
    if (print_debug_messages)
        qDebug() << "INFO: IbcDataFile::Load_Project_Settings()";

    try {

        // Data Model INPUT File Name
        QStringList ModuleStringList = ReadModuleLine(filename_open_project,tr("TINShapeLayer"));
        if ( ModuleStringList.length() > 0  )
        {
            QString TempFileName = ModuleStringList.at(3);
            TempFileName = TempFileName.right(TempFileName.length()-TempFileName.lastIndexOf("/")-1);
            TempFileName.replace( QString(".shp"), QString(".ibc") );
            Check_IbcData_Output(user_pihmgis_root_folder+"/4DataModelLoader/"+TempFileName, true);
        }

        ModuleStringList = ReadModuleLine(filename_open_project,tr("MeshDataFile"));
        if ( ModuleStringList.length() > 0  )
        {
            QString TempFileName = ModuleStringList.at(9);
            Check_IbcData_Output(user_pihmgis_root_folder+"/4DataModelLoader/"+TempFileName+".ibc", true);
        }
        // End: Set Defaults

        // Start: Fill Form If Module Has Been Run Previously

        ModuleStringList = ReadModuleLine(filename_open_project,tr("IbcDataFile"));
        if ( ModuleStringList.length() > 0 )
        {
            Check_IbcData_Output(ModuleStringList.at(1), true);
        }
        // End: Fill Form If Module Has Been Run Previously

        pushButtonSetFocus();

    } catch (...) {
        qDebug() << "Error: IbcDataFile::Load_Project_Settings is returning w/o checking";
        return false;
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to clear message log
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void IbcDataFile::Clear_Log()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start IbcDataFile::Clear_Log()";

    try {

        LogsString = tr("");
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

    } catch (...) {
        qDebug() << "Error: IbcDataFile::Clear_Log() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to assist if Check_IbcData_Output OUTPUT file exists (returns true) or does not (returns false)
// Will color red and warning if exists with color_and_message_if_exists=true
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool IbcDataFile::Check_IbcData_Output(QString file, bool color_and_message_if_exists){

    if(print_debug_messages)
        qDebug() << "INFO: Check_IbcData_Output()";

    bool result = false;

    try {

        if(  fileExists(file) )
        {
            if(color_and_message_if_exists)
            {
                Log_Error_Message(" IBC output already exists: " + file +tr(" You may need to delete these files.<br>"));
            }

            ui->lineEditIbcDataFile->setStyleSheet("color: red;");
            ui->lineEditIbcDataFile->setText(file);
            result = true;
        }
        else
        {
            ui->lineEditIbcDataFile->setStyleSheet("color: black;");
            ui->lineEditIbcDataFile->setText(file);

            result = false;
        }

    } catch (...) {
        qDebug() << "Error: IbcDataFile::Check_IbcData_Output is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to focus button selection (needed for users w/o mouse)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void IbcDataFile::pushButtonSetFocus()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start IbcDataFile::pushButtonSetFocus()";

    try {
        ui->pushButtonIbcDataFile->setDefault(false);

        if (ui->lineEditIbcDataFile->text() == nullptr)
        {
            ui->pushButtonIbcDataFile->setDefault(true);
            ui->pushButtonIbcDataFile->setFocus();
            return;
        }

        ui->pushButtonRun->setDefault(true);
        ui->pushButtonRun->setFocus();

    } catch (...) {
        qDebug() << "Error: IbcDataFile::pushButtonSetFocus() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button IBC Clicked Event (OUTPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void IbcDataFile::on_pushButtonIbcDataFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start IbcDataFile::on_pushButtonIbcDataFile_clicked()";

    try {

        Clear_Log();

        QString IbcDataFileName = QFileDialog::getSaveFileName(this, "Choose IBC Data File Name", user_pihmgis_root_folder+"/4DataModelLoader","IBC Data File(*.ibc)");
        QString tempString = IbcDataFileName;
        if ( IbcDataFileName != nullptr)
        {
            if( ! (tempString.toLower()).endsWith(".ibc") )
            {
                tempString.append(".ibc");
                IbcDataFileName = tempString;
            }
            Check_IbcData_Output(IbcDataFileName, true);

            pushButtonSetFocus();
        }

    } catch (...) {
        qDebug() << "Error: IbcDataFile::on_pushButtonIbcDataFile_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Create file (Is dummy file) TODO
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int IbcDataFile::ibc_data_file( QString IbcDataFileName )
{
    if(print_debug_messages)
        qDebug() << "INFO: Start IbcDataFile::ibc_data_file()";

    try {
        QFile IbcFile( IbcDataFileName );
        if ( ! IbcFile.open(QIODevice::WriteOnly | QIODevice::Text) )
            return 137;

        QTextStream IbcFileTextStream(&IbcFile);

        IbcFileTextStream << "0\t0\n0";

        IbcFile.close();

    } catch (...) {
        qDebug() << "Error: IbcDataFile::ibc_data_file() is returning w/o checking";
    }

    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Run Button Clicked Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void IbcDataFile::on_pushButtonRun_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start IbcDataFile::on_pushButtonRun_clicked()";

    try {

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Clear Log
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Clear_Log();

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check output and file access
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QString output_filename = ui->lineEditIbcDataFile->text();

        bool output_check = Check_IbcData_Output(output_filename, true);
        if(output_check)
        {
            return;
        }
        if ( ! CheckFileAccess(output_filename, "WriteOnly") )
        {
            Log_Error_Message(tr("<span style=\"color:#FF0000\">Error: No Write Access to ... </span>") + output_filename + tr("<br>"));
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Running Att Data File
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Log_Message("Running IBC Data File ... <br>");

        int ErrorIbc = ibc_data_file( output_filename );

        if( ErrorIbc != 0 )
        {
            Log_Error_Message(tr("<span style=\"color:#FF0000\">ERROR: Ibc Data File Processing Failed ... </span>")+tr("<br>"));
            Log_Error_Message(tr("<span style=\"color:#FF0000\">RETURN CODE IBC: ... </span>")+QString::number(ErrorIbc)+tr("<br>"));
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update Project file
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QStringList ProjectIOStringList;

        ProjectIOStringList << "IbcDataFile" << output_filename;
        WriteModuleLine(filename_open_project, ProjectIOStringList);
        ProjectIOStringList.clear();

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update Message box
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Clear_Log();

        Log_Message(tr("<br><b>Ibc Data File Processing Complete.</b>")+tr("<br>"));

        ui->pushButtonRun->setDefault(false);
        ui->pushButtonClose->setDefault(true);
        ui->pushButtonClose->setFocus();


    } catch (...) {
        qDebug() << "Error: IbcDataFile::on_pushButtonRun_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check Log_Error_Message
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void IbcDataFile::Log_Error_Message(QString message)
{
    try {
        LogsString.append(tr("<span style=\"color:#FF0000\">Error: ") + message + " </span>" +tr("<br>"));
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

        if(redirect_debug_messages_to_log)
        {
            ((PIHMgisDialog*)this->parent())->Log_Message(tr("<span style=\"color:#FF0000\">Error: ") + message + " </span>" + tr("<br>"));
        }

    } catch (...) {
        qDebug() << "Error: Log_Error_Message is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check Log_Error_Message
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void IbcDataFile::Log_Message(QString message)
{
    try {
        LogsString.append(tr("<span style=\"color:#000000\"> ") + message + " </span>" + tr("<br>"));
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

        if(redirect_debug_messages_to_log)
        {
            ((PIHMgisDialog*)this->parent())->Log_Message(tr("<span style=\"color:#000000\"> ") + message + " </span>" + tr("<br>"));
        }

    } catch (...) {
        qDebug() << "Error: Log_Message is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Help button event
// TODO, Need cataract server back online
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void IbcDataFile::on_pushButtonClose_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start IbcDataFile::on_pushButtonClose_clicked()";

    try {
        //QStringList default_params; default_params << "WORKFLOW5" << "PARA";
        //QMetaObject::invokeMethod(parent(),"set_defaults",Q_ARG(QStringList,default_params));
        close();
    } catch (...) {
        qDebug() << "Error: IbcDataFile::on_pushButtonClose_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Help button event
// TODO, Need cataract server back online
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void IbcDataFile::on_pushButtonHelp_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start IbcDataFile::on_pushButtonHelp_clicked()";

    try {
        //        LogsString = tr("");
        //        if ( ! QDesktopServices::openUrl(QUrl("http://cataract.cee.psu.edu/PIHM/index.php/PIHMgis_3.0#ibc_Data_File")) )
        //            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Load HTTP Link ... </span>")+tr("<br>"));
        //        ui->textBrowserLogs->setHtml(LogsString);
        //        ui->textBrowserLogs->repaint();
    } catch (...) {
        qDebug() << "Error: IbcDataFile::on_pushButtonHelp_clicked() is returning w/o checking";
    }
}
