#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>

#include "catchmentpolygon.h"
#include "ui_catchmentpolygon.h"

#include "0LibsIO/IOProjectFile.h"
#include "0LibsRaster/catchment_shape.h"
#include "globals.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CatchmentPolygon Constructor
// Parent is Main Window, filename is the open project text file used to store project details
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CatchmentPolygon::CatchmentPolygon(QWidget *parent, QString filename) :
    QDialog(parent),
    ui(new Ui::CatchmentPolygon)
{

    if(print_debug_messages)
        qDebug() << "INFO: Start CatchmentPolygon";

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
        qDebug() << "Error: CatchmentPolygon is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CatchmentPolygon Deconstructor
// Todo: Check for memory leaks
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CatchmentPolygon::~CatchmentPolygon()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ~CatchmentPolygon";

    try {
        delete ui;
    } catch (...) {
        qDebug() << "Error: ~CatchmentPolygon is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Load_Project_Settings
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CatchmentPolygon::Load_Project_Settings()
{
    if (print_debug_messages)
        qDebug() << "INFO: CatchmentPolygon::Load_Project_Settings()";

    try {

        QString CatchmentGrids_filename;
        QString CatchmentPolygon_filename;

        QStringList ModuleStringList = ReadModuleLine(filename_open_project,tr("CatchmentGrids"));

        if ( ModuleStringList.length() > 0  )
        {
            CatchmentGrids_filename = ModuleStringList.at(3);
        }

        ModuleStringList = ReadModuleLine(filename_open_project,tr("StreamGrids"));

        if ( ModuleStringList.length() > 0  && ui->lineEditCatchmentPolygon->text() == nullptr)
        {
            CatchmentPolygon_filename = filename_open_project +"/1RasterProcessing/Catchment"+ModuleStringList.at(3)+".shp";
        }

        ModuleStringList = ReadModuleLine(filename_open_project,tr("CatchmentPolygon"));

        if ( ModuleStringList.length() > 0 )
        {
            CatchmentGrids_filename = ModuleStringList.at(1);
            CatchmentPolygon_filename = ModuleStringList.at(2);
        }

        bool CatchmentGrids_check = Check_CatchmentGrids_Input(CatchmentGrids_filename);
        if(!CatchmentGrids_check)
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: CatchmentGrids input does not exist. </span>") +tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
        }

        bool CatchmentPolygon_check = Check_CatchmentPolygon_Output(CatchmentPolygon_filename, true);

        pushButtonSetFocus();


    } catch (...) {
        qDebug() << "Error: CatchmentPolygon::Load_Project_Settings is returning w/o checking";
        return false;
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to focus button selection (needed for users w/o mouse)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CatchmentPolygon::pushButtonSetFocus()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start CatchmentPolygon::pushButtonSetFocus()";

    try {
        ui->pushButtonCatchmentGrids->setDefault(false);
        ui->pushButtonCatchmentPolygon->setDefault(false);
        ui->pushButtonRun->setDefault(false);

        if (ui->lineEditCatchmentGrids->text() == nullptr)
        {
            ui->pushButtonCatchmentGrids->setDefault(true);
            ui->pushButtonCatchmentGrids->setFocus();
            return;
        }
        if (ui->lineEditCatchmentPolygon->text() == nullptr)
        {
            ui->pushButtonCatchmentPolygon->setDefault(true);
            ui->pushButtonCatchmentPolygon->setFocus();
            return;
        }

        ui->pushButtonRun->setDefault(true);
        ui->pushButtonRun->setFocus();

    } catch (...) {
        qDebug() << "Error: CatchmentPolygon::pushButtonSetFocus() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to clear message log
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CatchmentPolygon::Clear_Log()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start CatchmentPolygon::Clear_Log()";

    try {

        LogsString = tr("");
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

    } catch (...) {
        qDebug() << "Error: CatchmentPolygon::Clear_Log() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button Clicked Event for CatchmentGrids (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CatchmentPolygon::Check_CatchmentGrids_Input(QString file)
{
    if(print_debug_messages)
        qDebug() << "INFO: Check_CatchmentGrids_Input()";

    bool result = false;

    try {

        if(  fileExists(file) )
        {
            ui->lineEditCatchmentGrids->setStyleSheet("color: black;");
            ui->lineEditCatchmentGrids->setText(file);
            result = true;
        }
        else
        {
            ui->lineEditCatchmentGrids->setStyleSheet("color: red;");
            ui->lineEditCatchmentGrids->setText(file);

            result = false;
        }


    } catch (...) {
        qDebug() << "Error: Check_CatchmentGrids_Input is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to assist if CatchmentPolygon OUTPUT file exists (returns true) or does not (returns false)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CatchmentPolygon::Check_CatchmentPolygon_Output(QString file, bool color_and_message_if_exists)
{
    if(print_debug_messages)
        qDebug() << "INFO: Check_CatchmentPolygon_Output()";

    bool result = false;

    try {

        if(  fileExists(file) )
        {
            if(color_and_message_if_exists)
            {
                LogsString.append(tr("<span style=\"color:#FF0000\">Warning: CatchmentPolygon output already exists: </span>") + file +tr(" You may need to delete these files.<br>"));
                ui->textBrowserLogs->setHtml(LogsString);
                ui->textBrowserLogs->repaint();
            }

            ui->lineEditCatchmentPolygon->setStyleSheet("color: red;");
            ui->lineEditCatchmentPolygon->setText(file);
            result = true;
        }
        else
        {
            ui->lineEditCatchmentPolygon->setStyleSheet("color: black;");
            ui->lineEditCatchmentPolygon->setText(file);
            result = false;
        }


    } catch (...) {
        qDebug() << "Error: Check_CatchmentPolygon_Output is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button Clicked Event for CatchmentGrids (INPUT) file
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CatchmentPolygon::on_pushButtonCatchmentGrids_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start CatchmentPolygon::on_pushButtonCatchmentGrids_clicked()";

    try {

        Clear_Log();

        QString CatchmentGridFileName = QFileDialog::getOpenFileName(this, "Choose Catchment Grid File", user_pihmgis_root_folder + tr("/1RasterProcessing"), "Catchment Grid File(*.asc *.ASC)");
        if ( CatchmentGridFileName != nullptr)
        {
            Check_CatchmentGrids_Input(CatchmentGridFileName);

            pushButtonSetFocus();
        }

    } catch (...) {
        qDebug() << "Error: CatchmentPolygon::on_pushButtonCatchmentGrids_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button Clicked Event for CatchmentPolygon (OUTPUT) file
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CatchmentPolygon::on_pushButtonCatchmentPolygon_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start CatchmentPolygon::on_pushButtonCatchmentPolygon_clicked()";

    try {

        Clear_Log();

        QString CatchmentPolygonFileName = QFileDialog::getSaveFileName(this, "Choose Catchment Polygon", user_pihmgis_root_folder+"/1RasterProcessing","Catchment Polygon File(*.shp)");
        if ( CatchmentPolygonFileName != nullptr)
        {
            QString tempString = CatchmentPolygonFileName;
            if( ! (tempString.toLower()).endsWith(".shp") )
            {
                tempString.append(".shp");
                CatchmentPolygonFileName = tempString;
            }

            Check_CatchmentPolygon_Output(CatchmentPolygonFileName, true);

            pushButtonSetFocus();

        }

    } catch (...) {
        qDebug() << "Error: CatchmentPolygon::on_pushButtonCatchmentPolygon_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Run Button Clicked Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CatchmentPolygon::on_pushButtonRun_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start CatchmentPolygon::on_pushButtonRun_clicked()";

    try {
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Clear Log
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Clear_Log();

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check inputs
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QString CatchmentGrids_filename =  ui->lineEditCatchmentGrids->text();
        QString CatchmentPolygon_filename = ui->lineEditCatchmentPolygon->text();


        bool CatchmentGridsCheck = Check_CatchmentGrids_Input(CatchmentGrids_filename);
        if(!CatchmentGridsCheck)
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: CatchmentGrids Input File Missing </span>")+tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Does output already exist?
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool CatchmentPolygonCheck = Check_CatchmentPolygon_Output(CatchmentPolygon_filename, true);
        if(CatchmentPolygonCheck)
        {
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check file access
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if ( ! CheckFileAccess(CatchmentGrids_filename, "ReadOnly") )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Read Access ... </span>") + CatchmentGrids_filename + tr("<br>"));
            return;
        }

        if ( ! CheckFileAccess(CatchmentPolygon_filename, "WriteOnly") )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Write Access ... </span>") + CatchmentPolygon_filename + tr("<br>"));
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Running Catchment Polygon
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        LogsString.append("Running Catchment Polygon ... <br>");
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

        QString ShpFileName, DbfFileName;
        ShpFileName = CatchmentPolygon_filename;
        DbfFileName = ShpFileName;
        DbfFileName.replace(QString(".shp"), QString(".dbf"));
        const char *dummystr = "dummy";
        int ErrorCat = catchment_shape((char *)qPrintable(
                                           CatchmentGrids_filename),
                                       (char *)dummystr,
                                       (char *)qPrintable(ShpFileName),
                                       (char *)qPrintable(DbfFileName));
        if( ErrorCat != 0 )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Stream Polyline Processing Failed ... </span>")+tr("<br>"));
            LogsString.append(tr("<span style=\"color:#FF0000\">RETURN CODE: ... </span>")+QString::number(ErrorCat)+tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check output filenames
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        CatchmentPolygonCheck = Check_CatchmentPolygon_Output(CatchmentPolygon_filename, true);
        if(!CatchmentPolygonCheck)
        {
            return;
        }

        qint64 size = file_Size(CatchmentPolygon_filename);
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
        ProjectIOStringList << "CatchmentPolygon" << CatchmentGrids_filename << CatchmentPolygon_filename;
        WriteModuleLine(filename_open_project, ProjectIOStringList);
        ProjectIOStringList.clear();

        Clear_Log();

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Shapefile renaming
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QString CatchmentFileNameInRaster = CatchmentPolygon_filename;
        QString CatchmentFileNameInVector = CatchmentFileNameInRaster;
        CatchmentFileNameInVector.replace("1RasterProcessing","2VectorProcessing");  //TODO

        ProjectIOStringList << "CatchmentRasterVector" << CatchmentFileNameInRaster << CatchmentFileNameInVector;
        WriteModuleLine(filename_open_project, ProjectIOStringList);
        ProjectIOStringList.clear();

        QFile::remove(CatchmentFileNameInVector);
        QFile::copy(CatchmentFileNameInRaster,CatchmentFileNameInVector);

        CatchmentFileNameInRaster.replace(".shp",".shx");
        CatchmentFileNameInVector.replace(".shp",".shx");
        QFile::remove(CatchmentFileNameInVector);
        QFile::copy(CatchmentFileNameInRaster,CatchmentFileNameInVector);

        CatchmentFileNameInRaster.replace(".shx",".dbf");
        CatchmentFileNameInVector.replace(".shx",".dbf");
        QFile::remove(CatchmentFileNameInVector);
        QFile::copy(CatchmentFileNameInRaster,CatchmentFileNameInVector);

        CatchmentFileNameInVector.replace(".dbf",".shp");  //TODO


        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update Message box
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Clear_Log();

        LogsString.append(tr("<br><b>Catchment Polyline Processing Completed.</b>")+tr("<br>"));
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

        ui->pushButtonRun->setDefault(false);
        ui->pushButtonClose->setDefault(true);
        ui->pushButtonClose->setFocus();

    } catch (...) {
        qDebug() << "Error: CatchmentPolygon::on_pushButtonRun_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Close button event
// TODO, Decide on keeping button next highlights or not
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CatchmentPolygon::on_pushButtonClose_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start CatchmentPolygon::on_pushButtonClose_clicked()";

    try {

        //QStringList default_params; default_params << "WORKFLOW3" << "WORKFLOW8";
        //QMetaObject::invokeMethod(parent(),"set_defaults",Q_ARG(QStringList,default_params));
        close();

    } catch (...) {
        qDebug() << "Error: CatchmentPolygon::on_pushButtonClose_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Help button event
// TODO, Need cataract server back online
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CatchmentPolygon::on_pushButtonHelp_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start CatchmentPolygon::on_pushButtonHelp_clicked()";

    try {
        //        LogsString = tr("");
        //        if ( ! QDesktopServices::openUrl(QUrl("http://cataract.cee.psu.edu/PIHM/index.php/PIHMgis_3.0#Catchment_Polygon")) )
        //            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Load HTTP Link ... </span>")+tr("<br>"));
        //        ui->textBrowserLogs->setHtml(LogsString);
        //        ui->textBrowserLogs->repaint();
    } catch (...) {
        qDebug() << "Error: CatchmentPolygon::on_pushButtonHelp_clicked() is returning w/o checking";
    }
}
