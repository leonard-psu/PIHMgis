#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>

#include "linkgrids.h"
#include "ui_linkgrids.h"

#include "0LibsIO/IOProjectFile.h"
#include "0LibsRaster/stream_links.h"
#include "globals.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// LinkGrids Constructor
// Parent is Main Window, filename is the open project text file used to store project details
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LinkGrids::LinkGrids(QWidget *parent, QString filename) :
    QDialog(parent),
    ui(new Ui::LinkGrids)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start LinkGrids";

    try {

        ui->setupUi(this);

        filename_open_project = filename;
        bool found_file = false;

        QFile ProjectFile(filename_open_project);
        if ( ProjectFile.open(QIODevice::ReadOnly | QIODevice::Text) == false)
        {
            Log_Error_Message("Unable to Open File: " + filename_open_project);
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
        qDebug() << "Error: LinkGrids is returning w/o checking";
    }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// LinkGrids Deconstructor
// Todo: Check for memory leaks
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LinkGrids::~LinkGrids()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start LinkGrids";

    try {
        delete ui;

    } catch (...) {
        qDebug() << "Error: ~LinkGrids is returning w/o checking";

    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Load_Project_Settings
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool LinkGrids::Load_Project_Settings()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start LinkGrids::Load_Project_Settings()";

    try {

        QString LinkGrids = "";

        QStringList ModuleStringList = ReadModuleLine(filename_open_project,tr("StreamGrids"));

        if ( ModuleStringList.length() > 0  )
        {
            QString StreamGrids = ModuleStringList.at(2);
            QString temp = ModuleStringList.at(3);
            //Suggested file name
            LinkGrids = user_pihmgis_root_folder + "/1RasterProcessing/Link" + temp + ".asc";

            bool StreamGrids_check = Check_StreamGrids_Input(StreamGrids);
            if( StreamGrids_check == false)
            {
                Log_Error_Message("StreamGrids input does not exist. ");
            }
        }

        ModuleStringList = ReadModuleLine(filename_open_project,tr("FlowGrids"));
        if ( ModuleStringList.length() > 0  )
        {
            QString FlowDirGrids = ModuleStringList.at(2);

            bool FlowDir_check = Check_FlowDirGrids_Input(FlowDirGrids);
            if( FlowDir_check == false)
            {
                Log_Error_Message("FlowDir input does not exist. ");
            }
        }

        ModuleStringList = ReadModuleLine(filename_open_project,tr("LinkGrids"));
        if ( ModuleStringList.length() > 0  )
        {
            QString StreamGrids = ModuleStringList.at(1);
            QString FlowDirGrids = ModuleStringList.at(2);
            LinkGrids = ModuleStringList.at(3);

            bool StreamGrids_check = Check_StreamGrids_Input(StreamGrids);
            if( StreamGrids_check == false)
            {
                Log_Error_Message("StreamGrids input does not exist.");
            }

            bool FlowDir_check = Check_FlowDirGrids_Input(FlowDirGrids);
            if( FlowDir_check == false)
            {
                Log_Error_Message("FlowDir input does not exist. ");
            }

        }

        bool LinkGrids_check = Check_LinkGrids_Output(LinkGrids,true);


    } catch (...) {
        qDebug() << "Error: LinkGrids::Load_Project_Settings is returning w/o checking";
        return false;
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to clear message log
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LinkGrids::Clear_Log()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start LinkGrids::Clear_Log()";

    try {

        LogsString = tr("");
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

    } catch (...) {
        qDebug() << "Error: LinkGrids::Clear_Log() is returning w/o checking";
    }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check Log_Error_Message
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LinkGrids::Log_Error_Message(QString message)
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
void LinkGrids::Log_Message(QString message)
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
void LinkGrids::pushButtonSetFocus()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start LinkGrids::pushButtonSetFocus()";

    try {
        ui->pushButtonStreamGrids->setDefault(false);
        ui->pushButtonFlowDirGrids->setDefault(false);
        ui->pushButtonLinkGrids->setDefault(false);
        ui->pushButtonRun->setDefault(false);

        if (ui->lineEditStreamGrids->text() == nullptr)
        {
            ui->pushButtonStreamGrids->setDefault(true);
            ui->pushButtonStreamGrids->setFocus();
            return;
        }

        if (ui->lineEditFlowDirGrids->text() == nullptr)
        {
            ui->pushButtonFlowDirGrids->setDefault(true);
            ui->pushButtonFlowDirGrids->setFocus();
            return;
        }

        if (ui->lineEditLinkGrids->text() == nullptr)
        {
            ui->pushButtonLinkGrids->setDefault(true);
            ui->pushButtonLinkGrids->setFocus();
            return;
        }

        ui->pushButtonRun->setDefault(true);
        ui->pushButtonRun->setFocus();

    } catch (...) {
        qDebug() << "Error: LinkGrids::pushButtonSetFocus() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to assist if StreamGrids input file exists (returns true) or does not (returns false)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool LinkGrids::Check_StreamGrids_Input(QString file)
{
    if(print_debug_messages)
        qDebug() << "INFO: Check_StreamGrids_Input()";

    bool result = false;

    try {

        if( fileExists(file) )
        {
            ui->lineEditStreamGrids->setStyleSheet("color: black;");
            ui->lineEditStreamGrids->setText(file);
            result = true;
        }
        else
        {
            ui->lineEditStreamGrids->setStyleSheet("color: red;");
            ui->lineEditStreamGrids->setText(file);

            Log_Error_Message("StreamGrids input does not exist: " + file);
            result = false;
        }

    } catch (...) {
        qDebug() << "Error: Check_StreamGrids_Input is returning w/o checking";
        result = false;
    }
    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to assist if FlowDir input file exists (returns true) or does not (returns false)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool LinkGrids::Check_FlowDirGrids_Input(QString file)
{
    if(print_debug_messages)
        qDebug() << "INFO: Check_FlowDirGrids_Input()";

    bool result = false;

    try {
        if( fileExists(file) )
        {
            ui->lineEditFlowDirGrids->setStyleSheet("color: black;");
            ui->lineEditFlowDirGrids->setText(file);
            result = true;
        }
        else
        {
            ui->lineEditFlowDirGrids->setStyleSheet("color: red;");
            ui->lineEditFlowDirGrids->setText(file);

            Log_Error_Message("FlowDir Grids input does not exist: " + file);
            result = false;
        }

    } catch (...) {
        qDebug() << "Error: Check_FlowDirGrids_Input is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to assist if LinkGrids Output file exists (returns true) or does not (returns false)
// Will color red and warning if exists with color_and_message_if_exists=true
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool LinkGrids::Check_LinkGrids_Output(QString file, bool color_and_message_if_exists)
{
    if(print_debug_messages)
        qDebug() << "INFO: Check_LinkGrids_Output()";

    bool result = false;

    try {

        if(  fileExists(file) )
        {
            if(color_and_message_if_exists)
            {
                Log_Message("Warning: LinkGrids output already exists: " + file + " You may need to delete these files.");
            }

            ui->lineEditLinkGrids->setStyleSheet("color: red;");
            ui->lineEditLinkGrids->setText(file);
            result = true;
        }
        else
        {
            ui->lineEditLinkGrids->setStyleSheet("color: black;");
            ui->lineEditLinkGrids->setText(file);
            result = false;
        }

    } catch (...) {
        qDebug() << "Error: Check_LinkGrids_Output is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button Clicked Event for StreamGrid (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LinkGrids::on_pushButtonStreamGrids_clicked()
{

    if(print_debug_messages)
        qDebug() << "INFO: Start LinkGrids::on_pushButtonStreamGrids_clicked()";

    try {

        Clear_Log();

        QString StreamGridFileName = QFileDialog::getOpenFileName(this, "Choose Stream Grid File", user_pihmgis_root_folder+tr("/1RasterProcessing"), "Stream Grid File(*.asc *.ASC)");
        if ( StreamGridFileName.isNull() == false)
        {
            if( StreamGridFileName.isEmpty() == false)
            {
                bool StreamGrids_check = Check_StreamGrids_Input(StreamGridFileName);

                pushButtonSetFocus();
            }
        }
        //else do nothing

    } catch (...) {
        qDebug() << "Error: LinkGrids::on_pushButtonStreamGrids_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button Clicked Event for FlowDir (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LinkGrids::on_pushButtonFlowDirGrids_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start LinkGrids::on_pushButtonFlowDirGrids_clicked()";

    try {

        Clear_Log();

        QString FlowDirGridFileName = QFileDialog::getOpenFileName(this, "Choose Flow Dir Grid File", user_pihmgis_root_folder+tr("/1RasterProcessing"), "Flow Dir Grid File(*.asc *.ASC)");
        if ( FlowDirGridFileName.isNull() == false)
        {
            if( FlowDirGridFileName.isEmpty() == false)
            {
                bool check = Check_FlowDirGrids_Input(FlowDirGridFileName);
                pushButtonSetFocus();
            }
        }
        //else do nothing

    } catch (...) {
        qDebug() << "Error: LinkGrids::on_pushButtonFlowDirGrids_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button Clicked Event for LinkGrids (OUTPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LinkGrids::on_pushButtonLinkGrids_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start LinkGrids::on_pushButtonLinkGrids_clicked()";

    try {

        Clear_Log();

        QString LinkGridsFileName = QFileDialog::getSaveFileName(this, "Choose Link Grid", user_pihmgis_root_folder + "/1RasterProcessing","Link Grid File(*.asc)");
        if ( LinkGridsFileName.isNull() == false)
        {
            if( LinkGridsFileName.isEmpty() == false)
            {
                QString tempString = LinkGridsFileName;
                if( (tempString.toLower()).endsWith(".asc") == false)
                {
                    tempString.append(".asc");
                    LinkGridsFileName = tempString;
                }

                bool LinkGrids_check = Check_LinkGrids_Output(LinkGridsFileName,true);

                pushButtonSetFocus();
            }
        }
        //else do nothing

    } catch (...) {
        qDebug() << "Error: LinkGrids::on_pushButtonLinkGrids_clicked() is returning w/o checking";
    }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Run Button Clicked Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LinkGrids::on_pushButtonRun_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start LinkGrids::on_pushButtonRun_clicked()";

    try {

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Clear Log
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Clear_Log();

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check inputs
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QString StreamGridsFileName = ui->lineEditStreamGrids->text();
        QString FlowDirGridsFileName = ui->lineEditFlowDirGrids->text();
        QString LinkGridsFileName = ui->lineEditLinkGrids->text();

        bool StreamGrids_check = Check_StreamGrids_Input(StreamGridsFileName);
        if( StreamGrids_check == false)
        {
            Log_Error_Message("StreamGrids Input File Missing ");
            return;
        }

        bool FlowDirGrids_check = Check_FlowDirGrids_Input(FlowDirGridsFileName);
        if( FlowDirGrids_check == false)
        {
            Log_Error_Message("FlowDirGrids Input File Missing ");
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Does output already exist?
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool LinkGrids_check = Check_LinkGrids_Output(LinkGridsFileName,true);
        if(LinkGrids_check)
        {
            Log_Message("LinkGrids Output File already exists ");
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check file access
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if ( CheckFileAccess(StreamGridsFileName, "ReadOnly") == false)
        {
            Log_Error_Message("No Read Access to ... " + StreamGridsFileName );
            return;
        }

        if ( CheckFileAccess(FlowDirGridsFileName, "ReadOnly") == false)
        {
            Log_Error_Message("No Read Access to ... " + FlowDirGridsFileName);
            return;
        }

        if ( CheckFileAccess(LinkGridsFileName, "WriteOnly") == false)
        {
            Log_Error_Message("Unable to Write Access ... " + LinkGridsFileName );
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Run Link Grids
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Log_Message("Running Link Grids ... ");

        int ErrorLnk = stream_links(StreamGridsFileName,
                                    FlowDirGridsFileName,
                                    LinkGridsFileName,
                                    QString(user_pihmgis_root_folder + "/1RasterProcessing/link_nodes.dat") );
        if( ErrorLnk != 0 )
        {
            Log_Error_Message("Link Grid Processing Failed ... ");
            Log_Error_Message("RETURN CODE: ... " + QString::number(ErrorLnk));
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check output filenames
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        LinkGrids_check = Check_LinkGrids_Output(LinkGridsFileName,true);
        if( LinkGrids_check == false)
        {
            return;
        }

        qint64 size = file_Size(LinkGridsFileName);
        if( size < 1)
        {
            Log_Error_Message("StreamGrids failed, invalid file size: " + QString::number(size) );
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update Project file
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QStringList ProjectIOStringList;
        ProjectIOStringList << "LinkGrids" << StreamGridsFileName << FlowDirGridsFileName << LinkGridsFileName;
        WriteModuleLine(filename_open_project, ProjectIOStringList);
        ProjectIOStringList.clear();

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update Message box
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Clear_Log();

        Log_Message("Link Grids Processing Completed.");

        ui->pushButtonRun->setDefault(false);
        ui->pushButtonClose->setDefault(true);
        ui->pushButtonClose->setFocus();

    } catch (...) {
        qDebug() << "Error: LinkGrids::on_pushButtonRun_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Close button event
// TODO, Decide on keeping button next highlights or not
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LinkGrids::on_pushButtonClose_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start LinkGrids::on_pushButtonClose_clicked()";

    try {
        //QStringList default_params; default_params << "WORKFLOW2" << "CATGRIDS";
        //QMetaObject::invokeMethod(parent(),"set_defaults",Q_ARG(QStringList,default_params));
        close();
    } catch (...) {
        qDebug() << "Error: LinkGrids::on_pushButtonClose_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Help button event
// TODO, Need cataract server back online
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LinkGrids::on_pushButtonHelp_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start LinkGrids::on_pushButtonHelp_clicked()";

    try {
        //        LogsString = tr("");
        //        if ( ! QDesktopServices::openUrl(QUrl("http://cataract.cee.psu.edu/PIHM/index.php/PIHMgis_3.0#Link_Grids")) )
        //            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Load HTTP Link ... </span>")+tr("<br>"));
        //        ui->textBrowserLogs->setHtml(LogsString);
        //        ui->textBrowserLogs->repaint();
    } catch (...) {
        qDebug() << "Error: LinkGrids::on_pushButtonHelp_clicked() is returning w/o checking";
    }
}
