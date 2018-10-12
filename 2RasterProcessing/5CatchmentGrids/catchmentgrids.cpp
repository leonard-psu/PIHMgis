#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>

#include "catchmentgrids.h"
#include "ui_catchmentgrids.h"

#include "0LibsIO/IOProjectFile.h"
#include "0LibsRaster/catchment.h"
#include "globals.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CatchmentGrids Constructor
// Parent is Main Window, filename is the open project text file used to store project details
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CatchmentGrids::CatchmentGrids(QWidget *parent, QString filename) :
    QDialog(parent),
    ui(new Ui::CatchmentGrids)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start CatchmentGrids";

    try {

        ui->setupUi(this);

        filename_open_project = filename;
        bool found_file = false;

        // ** Start: Fill Form If Module Has Been Run Previously
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
        qDebug() << "Error: CatchmentGrids is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CatchmentGrids Deconstructor
// Todo: Check for memory leaks
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CatchmentGrids::~CatchmentGrids()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ~CatchmentGrids";

    try {
        delete ui;
    } catch (...) {
        qDebug() << "Error: ~CatchmentGrids is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Load_Project_Settings
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CatchmentGrids::Load_Project_Settings()
{
    if (print_debug_messages)
        qDebug() << "INFO: CatchmentGrids::Load_Project_Settings()";

    try {

        QString LinkGrids_filename;
        QString FlowDirGrids_filename;
        QString CatchmentGrids_filename;

        QStringList ModuleStringList = ReadModuleLine(filename_open_project,tr("LinkGrids"));

        if ( ModuleStringList.length() > 0  )
        {
            LinkGrids_filename = ModuleStringList.at(3);
        }

        ModuleStringList = ReadModuleLine(filename_open_project,tr("StreamGrids"));
        if ( ModuleStringList.length() > 0  )
        {
            CatchmentGrids_filename = filename_open_project +"/1RasterProcessing/Catchment"+ModuleStringList.at(3)+".asc";
        }

        ModuleStringList = ReadModuleLine(filename_open_project,tr("FlowGrids"));
        if ( ModuleStringList.length() > 0  )
        {
            FlowDirGrids_filename = ModuleStringList.at(2);
        }

        ModuleStringList = ReadModuleLine(filename_open_project,tr("CatchmentGrids"));

        if ( ModuleStringList.length() > 0 )
        {
            LinkGrids_filename = ModuleStringList.at(1);
            FlowDirGrids_filename = ModuleStringList.at(2);
            CatchmentGrids_filename = ModuleStringList.at(3);
        }

        bool LinkGrids_check = Check_LinkGrids_Input(LinkGrids_filename);
        if(!LinkGrids_check)
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: LinkGrids input does not exist. </span>") +tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
        }

        bool FlowDirGrids_check = Check_FlowDirGrids_Input(FlowDirGrids_filename);
        if(!FlowDirGrids_check)
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: FlowDirGrid input does not exist. </span>") +tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
        }

        bool CatchmentGrids_check = Check_CatchmentGrids_Output(CatchmentGrids_filename, true);


    } catch (...) {
        qDebug() << "Error: CatchmentGrids::Load_Project_Settings is returning w/o checking";
        return false;
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to assist if input file exists (returns true) or does not (returns false)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CatchmentGrids::Check_LinkGrids_Input(QString file)
{
    if(print_debug_messages)
        qDebug() << "INFO: Check_LinkGrids_Input()";

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
            ui->lineEditLinkGrids->setStyleSheet("color: red;");
            ui->lineEditLinkGrids->setText(file);

            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: LinkGrids input does not exist: </span>") + file +tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
            result = false;
        }


    } catch (...) {
        qDebug() << "Error: Check_LinkGrids_Input is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to assist if input file exists (returns true) or does not (returns false)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CatchmentGrids::Check_FlowDirGrids_Input(QString file)
{
    if(print_debug_messages)
        qDebug() << "INFO: Check_FlowDirGrids_Input()";

    bool result = false;

    try {

        if(  fileExists(file) )
        {
            ui->lineEditFlowDirGrids->setStyleSheet("color: black;");
            ui->lineEditFlowDirGrids->setText(file);
            result = true;
        }
        else
        {
            ui->lineEditFlowDirGrids->setStyleSheet("color: red;");
            ui->lineEditFlowDirGrids->setText(file);

            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: FlowDirGrids input does not exist: </span>") + file +tr("<br>"));
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
// Helper Function to assist if CatchmentGrids OUTPUT file exists (returns true) or does not (returns false)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CatchmentGrids::Check_CatchmentGrids_Output(QString file, bool color_and_message_if_exists)
{
    if(print_debug_messages)
        qDebug() << "INFO: Check_CatchmentGrids_Output()";

    bool result = false;

    try {

        if(  fileExists(file) )
        {
            if(color_and_message_if_exists)
            {
                LogsString.append(tr("<span style=\"color:#FF0000\">Warning: CatchmentGrids output already exists: </span>") + file +tr(" You may need to delete these files.<br>"));
                ui->textBrowserLogs->setHtml(LogsString);
                ui->textBrowserLogs->repaint();
            }

            ui->lineEditCatchmentGrids->setStyleSheet("color: red;");
            ui->lineEditCatchmentGrids->setText(file);
            result = true;
        }
        else
        {

            ui->lineEditCatchmentGrids->setStyleSheet("color: black;");
            ui->lineEditCatchmentGrids->setText(file);


            result = false;
        }


    } catch (...) {
        qDebug() << "Error: Check_CatchmentGrids_Output is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to focus button selection (needed for users w/o mouse)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CatchmentGrids::pushButtonSetFocus()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start pushButtonSetFocus()";

    try {

        ui->pushButtonLinkGrids->setDefault(false);
        ui->pushButtonFlowDirGrids->setDefault(false);
        ui->pushButtonCatchmentGrids->setDefault(false);
        ui->pushButtonRun->setDefault(false);

        if (ui->lineEditLinkGrids->text() == nullptr)
        {
            ui->pushButtonLinkGrids->setDefault(true);
            ui->pushButtonLinkGrids->setFocus();
            return;
        }

        if (ui->lineEditFlowDirGrids->text() == nullptr)
        {
            ui->pushButtonFlowDirGrids->setDefault(true);
            ui->pushButtonFlowDirGrids->setFocus();
            return;
        }

        if (ui->lineEditCatchmentGrids->text() == nullptr)
        {
            ui->pushButtonCatchmentGrids->setDefault(true);
            ui->pushButtonCatchmentGrids->setFocus();
            return;
        }

        ui->pushButtonRun->setDefault(true);
        ui->pushButtonRun->setFocus();

    } catch (...) {
        qDebug() << "Error:CatchmentGrids::pushButtonSetFocus() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to clear message log
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CatchmentGrids::Clear_Log()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start CatchmentGrids::Clear_Log()";

    try {

        LogsString = tr("");
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

    } catch (...) {
        qDebug() << "Error: CatchmentGrids::Clear_Log() is returning w/o checking";
    }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button Clicked Event for LinkGrids (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CatchmentGrids::on_pushButtonLinkGrids_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start on_pushButtonLinkGrids_clicked()";

    try {

        Clear_Log();

        QString LinkGridFileName = QFileDialog::getOpenFileName(this, "Choose Link Grid File", user_pihmgis_root_folder+tr("/1RasterProcessing"), "Link Grid File(*.asc *.ASC)");
        if ( LinkGridFileName != nullptr)
        {
            bool LinkGrids_check = Check_LinkGrids_Input(LinkGridFileName);
            if(!LinkGrids_check)
            {
                LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: LinkGrids input does not exist. </span>") +tr("<br>"));
                ui->textBrowserLogs->setHtml(LogsString);
                ui->textBrowserLogs->repaint();
            }

            pushButtonSetFocus();
        }

    } catch (...) {
        qDebug() << "Error:CatchmentGrids::on_pushButtonLinkGrids_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button Clicked Event for FlowDirGrids (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CatchmentGrids::on_pushButtonFlowDirGrids_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start on_pushButtonFlowDirGrids_clicked()";

    try {

        Clear_Log();

        QString FlowDirGridFileName = QFileDialog::getOpenFileName(this, "Choose Flow Dir Grid File", user_pihmgis_root_folder+tr("/1RasterProcessing"), "Flow Dir Grid File(*.asc *.ASC)");
        if ( FlowDirGridFileName != nullptr)
        {
            bool FlowDirGrids_check = Check_FlowDirGrids_Input(FlowDirGridFileName);
            if(!FlowDirGrids_check)
            {
                LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: FlowDirGrids input does not exist. </span>") +tr("<br>"));
                ui->textBrowserLogs->setHtml(LogsString);
                ui->textBrowserLogs->repaint();
            }

            pushButtonSetFocus();
        }

    } catch (...) {
        qDebug() << "Error:CatchmentGrids::on_pushButtonFlowDirGrids_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button Clicked Event for CatchmentGrids (OUTPUT) file
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CatchmentGrids::on_pushButtonCatchmentGrids_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start on_pushButtonCatchmentGrids_clicked()";

    try {

        Clear_Log();

        QString CatchmentGridsFileName = QFileDialog::getSaveFileName(this, "Choose Catchment Grid", user_pihmgis_root_folder+"/1RasterProcessing","Catchment Grid File(*.asc)");
        if ( CatchmentGridsFileName != nullptr)
        {
            QString tempString = CatchmentGridsFileName;
            if( ! (tempString.toLower()).endsWith(".asc") )
            {
                tempString.append(".asc");
                CatchmentGridsFileName = tempString;
            }

            Check_CatchmentGrids_Output(CatchmentGridsFileName, true);

            pushButtonSetFocus();

        }

    } catch (...) {
        qDebug() << "Error:CatchmentGrids::on_pushButtonCatchmentGrids_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Run Button Clicked Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CatchmentGrids::on_pushButtonRun_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start on_pushButtonRun_clicked()";

    try {

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Clear Log
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Clear_Log();

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check inputs
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QString LinkGrids_filename = ui->lineEditLinkGrids->text();
        QString FlowDirGrids_filename = ui->lineEditFlowDirGrids->text();
        QString CatchmentGrids_filename =  ui->lineEditCatchmentGrids->text();

        bool LinkGridsCheck = Check_LinkGrids_Input(LinkGrids_filename);
        if(!LinkGridsCheck)
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: LinkGrids Input File Missing </span>")+tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
            return;
        }

        bool FlowDirGridsCheck = Check_FlowDirGrids_Input(FlowDirGrids_filename);
        if(!FlowDirGridsCheck)
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: FlowDirGrids Input File Missing </span>")+tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Does output already exist?
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool CatchmentGridsCheck = Check_CatchmentGrids_Output(CatchmentGrids_filename, true);
        if(CatchmentGridsCheck)
        {
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check file access
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if ( ! CheckFileAccess(LinkGrids_filename, "ReadOnly") )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Read Access ... </span>") + LinkGrids_filename + tr("<br>"));
            return;
        }
        if ( ! CheckFileAccess(FlowDirGrids_filename, "ReadOnly") )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Read Access ... </span>") + FlowDirGrids_filename + tr("<br>"));
            return;
        }

        if ( ! CheckFileAccess(CatchmentGrids_filename, "WriteOnly") )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Write Access ... </span>") + CatchmentGrids_filename + tr("<br>"));
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Run Stream Grids
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        LogsString.append("Running Catchment Grids ... <br>");
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

        int ErrorCat = catchment((char *)qPrintable
                                 (LinkGrids_filename),
                                 (char *)qPrintable(FlowDirGrids_filename),
                                 (char *)qPrintable(CatchmentGrids_filename) );
        qDebug()<<tr("ErrorCat = ") << QString::number(ErrorCat);
        if( ErrorCat != 0 )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Catchment Grid Processing Failed ... </span>")+tr("<br>"));
            LogsString.append(tr("<span style=\"color:#FF0000\">RETURN CODE: ... </span>")+QString::number(ErrorCat)+tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check output filenames
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        CatchmentGridsCheck = Check_CatchmentGrids_Output(CatchmentGrids_filename, true);
        if(!CatchmentGridsCheck)
        {
            return;
        }

        qint64 size = file_Size(CatchmentGrids_filename);
        if( size < 1)
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">Error: CatchmentGrids failed, invalid file size: </span>") + size +tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update Project file
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QStringList ProjectIOStringList;
        ProjectIOStringList << "CatchmentGrids" << LinkGrids_filename << FlowDirGrids_filename << CatchmentGrids_filename;
        WriteModuleLine(filename_open_project, ProjectIOStringList);
        ProjectIOStringList.clear();

        Clear_Log();

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update Message box
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Clear_Log();

        LogsString.append(tr("<br><b>Catchment Grids Processing Completed.</b>")+tr("<br>"));
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

        ui->pushButtonRun->setDefault(false);
        ui->pushButtonClose->setDefault(true);
        ui->pushButtonClose->setFocus();


    } catch (...) {
        qDebug() << "Error:CatchmentGrids::on_pushButtonRun_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Close button event
// TODO, Decide on keeping button next highlights or not
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CatchmentGrids::on_pushButtonClose_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start on_pushButtonClose_clicked()";

    try {
        // QStringList default_params; default_params << "WORKFLOW2" << "STRPOLY";
        //QMetaObject::invokeMethod(parent(),"set_defaults",Q_ARG(QStringList,default_params));
        close();
    } catch (...) {
        qDebug() << "Error:CatchmentGrids::on_pushButtonClose_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Help button event
// TODO, Need cataract server back online
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CatchmentGrids::on_pushButtonHelp_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start on_pushButtonHelp_clicked()";

    try {
        //        LogsString = tr("");
        //        if ( ! QDesktopServices::openUrl(QUrl("http://cataract.cee.psu.edu/PIHM/index.php/PIHMgis_3.0#Catchment_Grids")) )
        //            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Load HTTP Link ... </span>")+tr("<br>"));
        //        ui->textBrowserLogs->setHtml(LogsString);
        //        ui->textBrowserLogs->repaint();
    } catch (...) {
        qDebug() << "Error:CatchmentGrids::on_pushButtonHelp_clicked() is returning w/o checking";
    }
}
