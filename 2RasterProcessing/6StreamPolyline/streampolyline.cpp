#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>

#include "streampolyline.h"
#include "ui_streampolyline.h"

#include "0LibsIO/IOProjectFile.h"
#include "0LibsRaster/stream_shape.h"
#include "globals.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// StreamPolyline Constructor
// Parent is Main Window, filename is the open project text file used to store project details
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
StreamPolyline::StreamPolyline(QWidget *parent, QString filename) :
    QDialog(parent),
    ui(new Ui::StreamPolyline)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start StreamPolyline";

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
        qDebug() << "Error: StreamPolyline is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// StreamPolyline Deconstructor
// Todo: Check for memory leaks
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
StreamPolyline::~StreamPolyline()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ~StreamPolyline";

    try {
        delete ui;
    } catch (...) {
        qDebug() << "Error: ~StreamPolyline is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Load_Project_Settings
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool StreamPolyline::Load_Project_Settings()
{
    if (print_debug_messages)
        qDebug() << "INFO: StreamPolyline::Load_Project_Settings()";

    try {

        QString StreamGrids_filename;
        QString FlowDirGrids_filename;
        QString StreamPolyline_filename;

        QStringList ModuleStringList = ReadModuleLine(filename_open_project,tr("StreamGrids"));

        if ( ModuleStringList.length() > 0  )
        {
            StreamGrids_filename = ModuleStringList.at(2);
            //Suggest name
            StreamPolyline_filename = filename_open_project+"/1RasterProcessing/Stream"+ModuleStringList.at(3)+".shp";
        }

        ModuleStringList = ReadModuleLine(filename_open_project,tr("FlowGrids"));

        if ( ModuleStringList.length() > 0  )
        {
            FlowDirGrids_filename = ModuleStringList.at(2);
        }

        ModuleStringList = ReadModuleLine(filename_open_project,tr("StreamPolyline"));

        if ( ModuleStringList.length() > 0  )
        {
            StreamGrids_filename = ModuleStringList.at(1);
            FlowDirGrids_filename = ModuleStringList.at(2);
            StreamPolyline_filename = ModuleStringList.at(3);
        }

        bool StreamGrids_check = Check_StreamGrids_Input(StreamGrids_filename);
        if(!StreamGrids_check)
        {
            Log_Error_Message(tr("<span style=\"color:#FF0000\">ERROR: StreamGrids input does not exist. </span>") +tr("<br>"));
        }

        bool FlowDirGrids_check = Check_FlowDirGrids_Input(FlowDirGrids_filename);
        if(!FlowDirGrids_check)
        {
            Log_Error_Message(tr("<span style=\"color:#FF0000\">ERROR: FlowDirGrid input does not exist. </span>") +tr("<br>"));
        }

        bool StreamPolyline_check = Check_StreamPolyline_Output(StreamPolyline_filename, true);

    } catch (...) {
        qDebug() << "Error: StreamPolyline::Load_Project_Settings is returning w/o checking";
        return false;
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to focus button selection (needed for users w/o mouse)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StreamPolyline::pushButtonSetFocus()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start StreamPolyline::pushButtonSetFocus()";

    try {
        ui->pushButtonStreamGrids->setDefault(false);
        ui->pushButtonFlowDirGrids->setDefault(false);
        ui->pushButtonStreamPolyline->setDefault(false);
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

        if (ui->lineEditStreamPolyline->text() == nullptr)
        {
            ui->pushButtonStreamPolyline->setDefault(true);
            ui->pushButtonStreamPolyline->setFocus();
            return;
        }

        ui->pushButtonRun->setDefault(true);
        ui->pushButtonRun->setFocus();

    } catch (...) {
        qDebug() << "Error: StreamPolyline::pushButtonSetFocus() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to clear message log
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StreamPolyline::Clear_Log()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start StreamPolyline::Clear_Log()";

    try {

        LogsString = tr("");
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

    } catch (...) {
        qDebug() << "Error: StreamPolyline::Clear_Log() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check Log_Error_Message
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StreamPolyline::Log_Error_Message(QString message)
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
void StreamPolyline::Log_Message(QString message)
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
// Helper Function to assist if input file exists (returns true) or does not (returns false)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool StreamPolyline::Check_StreamGrids_Input(QString file)
{
    if(print_debug_messages)
        qDebug() << "INFO: Check_StreamGrids_Input()";

    bool result = false;

    try {

        if(  fileExists(file) )
        {
            ui->lineEditStreamGrids->setStyleSheet("color: black;");
            ui->lineEditStreamGrids->setText(file);
            result = true;
        }
        else
        {
            ui->lineEditStreamGrids->setStyleSheet("color: red;");
            ui->lineEditStreamGrids->setText(file);

            Log_Error_Message(tr("<span style=\"color:#FF0000\">ERROR: StreamGrids input does not exist: </span>") + file +tr("<br>"));
            result = false;
        }

    } catch (...) {
        qDebug() << "Error: Check_StreamGrids_Input is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to assist if input file exists (returns true) or does not (returns false)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool StreamPolyline::Check_FlowDirGrids_Input(QString file)
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

            Log_Error_Message(tr("<span style=\"color:#FF0000\">ERROR: FlowDirGrids input does not exist: </span>") + file +tr("<br>"));
            result = false;
        }


    } catch (...) {
        qDebug() << "Error: Check_FlowDirGrids_Input is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to assist if StreamPolyline OUTPUT file exists (returns true) or does not (returns false)
// Will color red and warning if exists with color_and_message_if_exists=true
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool StreamPolyline::Check_StreamPolyline_Output(QString file, bool color_and_message_if_exists)
{
    if(print_debug_messages)
        qDebug() << "INFO: Check_StreamPolyline_Output()";

    bool result = false;

    try {

        if(  fileExists(file) )
        {
            if(color_and_message_if_exists)
            {
                Log_Message(tr("<span style=\"color:#FF0000\">Warning: StreamPolyline output already exists: </span>") + file +tr(" You may need to delete these files.<br>"));
            }

            ui->lineEditStreamPolyline->setStyleSheet("color: red;");
            ui->lineEditStreamPolyline->setText(file);
            result = true;
        }
        else
        {
            ui->lineEditStreamPolyline->setStyleSheet("color: black;");
            ui->lineEditStreamPolyline->setText(file);

            result = false;
        }


    } catch (...) {
        qDebug() << "Error: Check_StreamPolyline_Output is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button Clicked Event for StreamGrids (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StreamPolyline::on_pushButtonStreamGrids_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start StreamPolyline::on_pushButtonStreamGrids_clicked()";

    try {

        Clear_Log();

        QString StreamGridFileName = QFileDialog::getOpenFileName(this, "Choose Stream Grid File", user_pihmgis_root_folder +tr("/1RasterProcessing"), "Stream Grid File(*.asc *.ASC)");
        if ( StreamGridFileName != nullptr)
        {
            bool StreamGrids_check = Check_StreamGrids_Input(StreamGridFileName);
            if(!StreamGrids_check)
            {
                Log_Error_Message(tr("<span style=\"color:#FF0000\">ERROR: StreamGrids input does not exist. </span>") +tr("<br>"));
            }

            pushButtonSetFocus();
        }


    } catch (...) {
        qDebug() << "Error: StreamPolyline::on_pushButtonStreamGrids_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button Clicked Event for FlowDirGrids (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StreamPolyline::on_pushButtonFlowDirGrids_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start StreamPolyline::on_pushButtonFlowDirGrids_clicked()";

    try {
        Clear_Log();

        QString FlowDirGridFileName = QFileDialog::getOpenFileName(this, "Choose Flow Dir Grid File", user_pihmgis_root_folder+tr("/1RasterProcessing"), "Flow Dir Grid File(*.asc *.ASC)");
        if ( FlowDirGridFileName != nullptr)
        {
            bool FlowDirGrids_check = Check_FlowDirGrids_Input(FlowDirGridFileName);
            if(!FlowDirGrids_check)
            {
                Log_Error_Message(tr("<span style=\"color:#FF0000\">ERROR: FlowDirGrids input does not exist. </span>") +tr("<br>"));
            }

            pushButtonSetFocus();
        }

    } catch (...) {
        qDebug() << "Error: StreamPolyline::on_pushButtonFlowDirGrids_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button Clicked Event for StreamPolyline (OUTPUT) file
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StreamPolyline::on_pushButtonStreamPolyline_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start StreamPolyline::on_pushButtonStreamPolyline_clicked()";

    try {

        Clear_Log();

        QString StreamPolylineFileName = QFileDialog::getSaveFileName(this, "Choose Stream Polyline", user_pihmgis_root_folder +"/1RasterProcessing","Stream Polyline File(*.shp)");

        if ( StreamPolylineFileName != nullptr)
        {
            QString tempString = StreamPolylineFileName;
            if( ! (tempString.toLower()).endsWith(".shp") )
            {
                tempString.append(".shp");
                StreamPolylineFileName = tempString;
            }

            Check_StreamPolyline_Output(StreamPolylineFileName, true);

            pushButtonSetFocus();

        }

    } catch (...) {
        qDebug() << "Error: StreamPolyline::on_pushButtonStreamPolyline_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Run Button Clicked Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StreamPolyline::on_pushButtonRun_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start StreamPolyline::on_pushButtonRun_clicked()";

    try {

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Clear Log
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Clear_Log();

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check inputs
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QString StreamGrids_filename = ui->lineEditStreamGrids->text();
        QString FlowDirGrids_filename = ui->lineEditFlowDirGrids->text();
        QString StreamPolyline_filename =  ui->lineEditStreamPolyline->text();

        bool StreamGridsCheck = Check_StreamGrids_Input(StreamGrids_filename);
        if(!StreamGridsCheck)
        {
            Log_Error_Message(tr("<span style=\"color:#FF0000\">ERROR: StreamGrids Input File Missing </span>")+tr("<br>"));
            return;
        }

        bool FlowDirGridsCheck = Check_FlowDirGrids_Input(FlowDirGrids_filename);
        if(!FlowDirGridsCheck)
        {
            Log_Error_Message(tr("<span style=\"color:#FF0000\">ERROR: FlowDirGrids Input File Missing </span>")+tr("<br>"));
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Does output already exist?
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool StreamPolylineCheck = Check_StreamPolyline_Output(StreamPolyline_filename, true);
        if(StreamPolylineCheck)
        {
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check file access
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if ( ! CheckFileAccess(StreamGrids_filename, "ReadOnly") )
        {
            Log_Error_Message(tr("<span style=\"color:#FF0000\">Error: No Read Access to ... </span>") + StreamGrids_filename + tr("<br>"));
            return;
        }
        if ( ! CheckFileAccess(FlowDirGrids_filename, "ReadOnly") )
        {
            Log_Error_Message(tr("<span style=\"color:#FF0000\">Error: No Read Access to ... </span>") + FlowDirGrids_filename + tr("<br>"));
            return;
        }

        if ( ! CheckFileAccess(StreamPolyline_filename, "WriteOnly") )
        {
            Log_Error_Message(tr("<span style=\"color:#FF0000\">Error: No Write Access to ... </span>") + StreamPolyline_filename + tr("<br>"));
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Run Stream Polyline
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Log_Message("Running Stream Polyline ... <br>");

        QString ShpFileName, DbfFileName;
        ShpFileName = StreamPolyline_filename;
        DbfFileName = ShpFileName;
        DbfFileName.replace(QString(".shp"), QString(".dbf"));
        int ErrorStr = stream_shape(StreamGrids_filename,
                                    FlowDirGrids_filename,
                                    ShpFileName,
                                    DbfFileName);
        if( ErrorStr != 0 )
        {
            Log_Error_Message(tr("<span style=\"color:#FF0000\">ERROR: Stream Polyline Processing Failed ... </span>")+tr("<br>"));
            Log_Error_Message(tr("<span style=\"color:#FF0000\">RETURN CODE: ... </span>")+QString::number(ErrorStr)+tr("<br>"));
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check output filenames
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        StreamPolylineCheck = Check_StreamPolyline_Output(StreamPolyline_filename, true);
        if(!StreamPolylineCheck)
        {
            return;
        }

        qint64 size = file_Size(StreamPolyline_filename);
        if( size < 1)
        {
            Log_Error_Message(tr("<span style=\"color:#FF0000\">Error: StreamPolyline failed, invalid file size: </span>") + size +tr("<br>"));
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update Project file
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QStringList ProjectIOStringList;
        ProjectIOStringList << "StreamPolyline" << StreamGrids_filename << FlowDirGrids_filename << StreamPolyline_filename;
        WriteModuleLine(filename_open_project, ProjectIOStringList);
        ProjectIOStringList.clear();

        Clear_Log();

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update Project file
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        QString StreamFileNameInRaster = StreamPolyline_filename;
        QString StreamFileNameInVector = StreamFileNameInRaster;
        StreamFileNameInVector.replace("1RasterProcessing","2VectorProcessing");  //TODO

        ProjectIOStringList << "StreamRasterVector" << StreamFileNameInRaster << StreamFileNameInVector;
        WriteModuleLine(filename_open_project, ProjectIOStringList);
        ProjectIOStringList.clear();

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Shapefile renaming
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QFile::remove(StreamFileNameInVector);
        QFile::copy(StreamFileNameInRaster,StreamFileNameInVector);

        StreamFileNameInRaster.replace(".shp",".shx");
        StreamFileNameInVector.replace(".shp",".shx");
        QFile::remove(StreamFileNameInVector);
        QFile::copy(StreamFileNameInRaster,StreamFileNameInVector);

        StreamFileNameInRaster.replace(".shx",".dbf");
        StreamFileNameInVector.replace(".shx",".dbf");
        QFile::remove(StreamFileNameInVector);
        QFile::copy(StreamFileNameInRaster,StreamFileNameInVector);

        StreamFileNameInVector.replace(".dbf",".shp");

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update Message box
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Clear_Log();

        Log_Message(tr("<br><b>Stream Polyline Processing Completed.</b>")+tr("<br>"));
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

        ui->pushButtonRun->setDefault(false);
        ui->pushButtonClose->setDefault(true);
        ui->pushButtonClose->setFocus();


    } catch (...) {
        qDebug() << "Error: StreamPolyline::on_pushButtonRun_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Close button event
// TODO, Decide on keeping button next highlights or not
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StreamPolyline::on_pushButtonClose_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start StreamPolyline::on_pushButtonClose_clicked()";

    try {
        //QStringList default_params; default_params << "WORKFLOW2" << "CATPOLY";
        //QMetaObject::invokeMethod(parent(),"set_defaults",Q_ARG(QStringList,default_params));
        close();
    } catch (...) {
        qDebug() << "Error: StreamPolyline::on_pushButtonClose_clicked() is returning w/o checking";
    }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Help button event
// TODO, Need cataract server back online
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StreamPolyline::on_pushButtonHelp_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start StreamPolyline::on_pushButtonHelp_clicked()";

    try {
        //        LogsString = tr("");
        //        if ( ! QDesktopServices::openUrl(QUrl("http://cataract.cee.psu.edu/PIHM/index.php/PIHMgis_3.0#Stream_Polyline")) )
        //            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Load HTTP Link ... </span>")+tr("<br>"));
        //        ui->textBrowserLogs->setHtml(LogsString);
        //        ui->textBrowserLogs->repaint();
    } catch (...) {
        qDebug() << "Error: StreamPolyline::on_pushButtonHelp_clicked() is returning w/o checking";
    }
}
