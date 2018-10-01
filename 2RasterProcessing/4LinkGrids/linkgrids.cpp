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
            QString LinkGrids = "";

            QStringList ModuleStringList = ReadModuleLine(filename_open_project,tr("StreamGrids"));

            if ( ModuleStringList.length() > 0  )
            {
                QString StreamGrids = ModuleStringList.at(2);
                QString temp = ModuleStringList.at(3);
                //Suggested file name
                LinkGrids = user_pihmgis_root_folder + "/1RasterProcessing/Link" + temp + ".asc";

                bool StreamGrids_check = Check_StreamGrids_Input(StreamGrids);
                if(!StreamGrids_check)
                {
                    LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: StreamGrids input does not exist. </span>") +tr("<br>"));
                    ui->textBrowserLogs->setHtml(LogsString);
                    ui->textBrowserLogs->repaint();
                }


            }

            ModuleStringList = ReadModuleLine(filename_open_project,tr("FlowGrids"));
            if ( ModuleStringList.length() > 0  )
            {
                QString FlowDirGrids = ModuleStringList.at(2);

                bool FlowDir_check = Check_FlowDirGrids_Input(FlowDirGrids);
                if(!FlowDir_check)
                {
                    LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: FlowDir input does not exist. </span>") +tr("<br>"));
                    ui->textBrowserLogs->setHtml(LogsString);
                    ui->textBrowserLogs->repaint();
                }
            }

            ModuleStringList = ReadModuleLine(filename_open_project,tr("LinkGrids"));
            if ( ModuleStringList.length() > 0  )
            {
                QString StreamGrids = ModuleStringList.at(1);
                QString FlowDirGrids = ModuleStringList.at(2);
                LinkGrids = ModuleStringList.at(3);

                bool StreamGrids_check = Check_StreamGrids_Input(StreamGrids);
                if(!StreamGrids_check)
                {
                    LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: StreamGrids input does not exist. </span>") +tr("<br>"));
                    ui->textBrowserLogs->setHtml(LogsString);
                    ui->textBrowserLogs->repaint();
                }

                bool FlowDir_check = Check_FlowDirGrids_Input(FlowDirGrids);
                if(!FlowDir_check)
                {
                    LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: FlowDir input does not exist. </span>") +tr("<br>"));
                    ui->textBrowserLogs->setHtml(LogsString);
                    ui->textBrowserLogs->repaint();
                }

            }

            bool LinkGrids_check = Check_LinkGrids_Output(LinkGrids,false);
            if(LinkGrids_check)
            {
                LogsString.append(tr("<span style=\"color:#FF0000\">Warning: LinkGrids output already exists. </span>") +tr("<br>"));
                ui->textBrowserLogs->setHtml(LogsString);
                ui->textBrowserLogs->repaint();
            }

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
            ui->lineEditStreamGrids->setStyleSheet("color: rgb(180, 0, 0);");
            ui->lineEditStreamGrids->setText(file);

            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: StreamGrids input does not exist: </span>") + file +tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
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
            ui->lineEditFlowDirGrids->setStyleSheet("color: rgb(180, 0, 0);");
            ui->lineEditFlowDirGrids->setText(file);

            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: FlowDir Grids input does not exist: </span>") + file +tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
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
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool LinkGrids::Check_LinkGrids_Output(QString file, bool message)
{
    if(print_debug_messages)
        qDebug() << "INFO: Check_LinkGrids_Output()";

    bool result = false;

    try {

        if(  fileExists(file) )
        {
            ui->lineEditLinkGrids->setStyleSheet("color: black;");
            ui->lineEditLinkGrids->setText(file);
            result = true;
        }
        else
        {
            ui->lineEditLinkGrids->setStyleSheet("color: rgb(180, 0, 0);");
            ui->lineEditLinkGrids->setText(file);

            if(message)
            {
                LogsString.append(tr("<span style=\"color:#FF0000\">Warning: LinkGrids output does not exist: </span>") + file +tr(" You will need to redo this step.<br>"));
                ui->textBrowserLogs->setHtml(LogsString);
                ui->textBrowserLogs->repaint();
            }
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
        if ( StreamGridFileName != nullptr)
        {
            bool StreamGrids_check = Check_StreamGrids_Input(StreamGridFileName);

            pushButtonSetFocus();
        }
        else
        {
            qDebug() << "on_pushButtonStreamGrids_clicked: Invalid FlowAccFileName";
        }

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
        if ( FlowDirGridFileName != nullptr)
        {
            bool check = Check_FlowDirGrids_Input(FlowDirGridFileName);

            pushButtonSetFocus();
        }
        else
        {
            qDebug() << "on_pushButtonFlowDirGrids_clicked: Invalid FlowAccFileName";
        }

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
        if ( LinkGridsFileName != nullptr)
        {
            QString tempString = LinkGridsFileName;
            if( ! (tempString.toLower()).endsWith(".asc") )
            {
                tempString.append(".asc");
                LinkGridsFileName = tempString;
            }

            bool LinkGrids_check = Check_LinkGrids_Output(LinkGridsFileName,true);

            pushButtonSetFocus();
        }

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
        if(!StreamGrids_check)
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: StreamGrids Input File Missing </span>")+tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
            return;
        }

        bool FlowDirGrids_check = Check_FlowDirGrids_Input(FlowDirGridsFileName);
        if(!FlowDirGrids_check)
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: FlowDirGrids Input File Missing </span>")+tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Does output already exist?
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool LinkGrids_check = Check_LinkGrids_Output(LinkGridsFileName,false);
        if(LinkGrids_check)
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: LinkGrids Output already exists </span>")+tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check file access
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if ( ! CheckFileAccess(StreamGridsFileName, "ReadOnly") )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Read Access ... </span>") + StreamGridsFileName + tr("<br>"));
            return;
        }

        if ( ! CheckFileAccess(FlowDirGridsFileName, "ReadOnly") )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Read Access ... </span>") + FlowDirGridsFileName + tr("<br>"));
            return;
        }

        if ( ! CheckFileAccess(LinkGridsFileName, "WriteOnly") )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Write Access ... </span>") + LinkGridsFileName + tr("<br>"));
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Run Link Grids
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        LogsString.append("Running Link Grids ... <br>");
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

        int ErrorLnk = stream_links((char *)qPrintable(
                                        StreamGridsFileName),
                                    (char *)qPrintable(FlowDirGridsFileName),
                                    (char *)qPrintable(LinkGridsFileName),
                                    (char *)qPrintable(user_pihmgis_root_folder + "/1RasterProcessing/link_nodes.dat") );
        if( ErrorLnk != 0 )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Link Grid Processing Failed ... </span>")+tr("<br>"));
            LogsString.append(tr("<span style=\"color:#FF0000\">RETURN CODE: ... </span>")+QString::number(ErrorLnk)+tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
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
        // Check output filenames
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        LinkGrids_check = Check_LinkGrids_Output(LinkGridsFileName,true);
        if(!LinkGrids_check)
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">Error: LinkGrids failed, file does not exist: </span>") + LinkGridsFileName +tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
            return;
        }

        qint64 size = file_Size(LinkGridsFileName);
        if( size < 1)
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">Error: StreamGrids failed, invalid file size: </span>") + size +tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update Message box
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Clear_Log();
        LogsString.append(tr("<br><b>Link Grids Processing Completed.</b>")+tr("<br>"));
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

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
