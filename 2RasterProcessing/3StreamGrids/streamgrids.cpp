#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>

#include "streamgrids.h"
#include "ui_streamgrids.h"

#include "0LibsIO/IOProjectFile.h"
#include "0LibsRaster/stream_definition.h"
#include "globals.h"



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// StreamGrids Constructor
// Parent is Main Window, filename is the open project text file used to store project details
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
StreamGrids::StreamGrids(QWidget *parent, QString filename) :
    QDialog(parent),
    ui(new Ui::StreamGrids)
{

    if(print_debug_messages)
        qDebug() << "INFO: Start StreamGrids";

    try {
        ui->setupUi(this);

        filename_open_project = filename;
        bool found_file = false;

        QObject::connect(ui->lineEditThreshold,SIGNAL(textChanged(QString)),this,SLOT(on_lineEditThreshold_textChanged()));

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
        qDebug() << "Error: StreamGrids is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// StreamGrids Deconstructor
// Todo: Check for memory leaks
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
StreamGrids::~StreamGrids()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ~StreamGrids";

    try {
        delete ui;
    } catch (...) {
        qDebug() << "Error: ~StreamGrids is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Load_Project_Settings
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool StreamGrids::Load_Project_Settings()
{
    try {

        QStringList ModuleStringList = ReadModuleLine(filename_open_project,tr("FlowGrids"));
        if ( ModuleStringList.length() > 0  )
        {
            QString FlowAccGrids = ModuleStringList.at(3);

            //Suggested file name
            QString threshold = ui->lineEditThreshold->text();
            QString StreamGrids = filename_open_project+"/1RasterProcessing/Stream" + threshold + ".asc";

            bool flowacc_check = Check_FlowAccGrids_Input(FlowAccGrids);
            if(!flowacc_check)
            {
                LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: FlowAcc input does not exist. </span>") +tr("<br>"));
                ui->textBrowserLogs->setHtml(LogsString);
                ui->textBrowserLogs->repaint();
            }

            ui->lineEditStreamGrids->setText(StreamGrids);
            //ui->lineEditThreshold->setText(""); //Why blank it, as threshold is used in name?

            bool streamgrids_check = Check_StreamGrids_Output(StreamGrids, true);

        }

        ModuleStringList = ReadModuleLine(filename_open_project,tr("StreamGrids"));
        if ( ModuleStringList.length() > 0  )
        {
            QString FlowAccGrids = ModuleStringList.at(1);
            QString StreamGrids = ModuleStringList.at(2);
            QString Threshold = ModuleStringList.at(3);

            bool flowacc_check = Check_FlowAccGrids_Input(FlowAccGrids);
            bool threshold_check = Check_Threshold_Input(Threshold);
            bool streamgrids_check = Check_StreamGrids_Output(StreamGrids, true);

        }

    } catch (...) {
        qDebug() << "Error: StreamGrids::Load_Project_Settings is returning w/o checking";
        return false;
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Check threshold value is numeric (returns true) or does not (returns false)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool StreamGrids::Check_Threshold_Input(QString Threshold)
{
    if(print_debug_messages)
        qDebug() << "INFO: Check_Threshold_Input()";

    bool result = false;

    try {
        bool badcharfound = false;
        bool isNumeric = false;
        foreach(const QString &string, Threshold)
        {
            string.toDouble(&isNumeric);
            if(isNumeric == false)
            {
                badcharfound = true;
            }
        }

        if(!badcharfound)
        {
            ui->lineEditThreshold->setText(Threshold);
            result = true;
        }
        else
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Invalid threshold. </span>") +tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
        }

    } catch (...) {
        qDebug() << "Error: Check_Threshold_Input is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to assist if StreamGrids OUTPUT file exists (returns true) or does not (returns false)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool StreamGrids::Check_StreamGrids_Output(QString file, bool color_and_message_if_exists)
{
    if(print_debug_messages)
        qDebug() << "INFO: Check_StreamGrids_Input()";

    bool result = false;

    try {

        if(  fileExists(file) )
        {
            if(color_and_message_if_exists)
            {
                LogsString.append(tr("<span style=\"color:#FF0000\">Warning: StreamGrids output already exists: </span>") + file +tr(" You may need to delete these files.<br>"));
                ui->textBrowserLogs->setHtml(LogsString);
                ui->textBrowserLogs->repaint();
            }

            ui->lineEditStreamGrids->setStyleSheet("color: red;");
            ui->lineEditStreamGrids->setText(file);
            result = true;
        }
        else
        {
            ui->lineEditStreamGrids->setStyleSheet("color: black;");
            ui->lineEditStreamGrids->setText(file);

            result = false;
        }


    } catch (...) {
        qDebug() << "Error: Check_StreamGrids_Input is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to assist if FlowAcc input file exists (returns true) or does not (returns false)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool StreamGrids::Check_FlowAccGrids_Input(QString file )
{
    if(print_debug_messages)
        qDebug() << "INFO: Check_FlowAccGrids_Input()";

    bool result = false;

    try {

        if(  fileExists(file) )
        {
            ui->lineEditFlowAccGrids->setStyleSheet("color: black;");
            ui->lineEditFlowAccGrids->setText(file);
            result = true;
        }
        else
        {
            ui->lineEditFlowAccGrids->setStyleSheet("color: red;");
            ui->lineEditFlowAccGrids->setText(file);

            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: FlowAcc input does not exist: </span>") + file +tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
            result = false;
        }


    } catch (...) {
        qDebug() << "Error: Check_FlowAccGrids_Input is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to focus button selection (needed for users w/o mouse)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StreamGrids::pushButtonSetFocus()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start pushButtonSetFocus";

    try {
        ui->pushButtonFlowAccGrids->setDefault(false);
        ui->pushButtonStreamGrids->setDefault(false);
        ui->pushButtonSuggestMe->setDefault(false);
        ui->pushButtonRun->setDefault(false);

        if (ui->lineEditFlowAccGrids->text() == nullptr)
        {
            ui->pushButtonFlowAccGrids->setDefault(true);
            ui->pushButtonFlowAccGrids->setFocus();
            return;
        }
        if (ui->lineEditStreamGrids->text() == nullptr)
        {
            ui->pushButtonStreamGrids->setDefault(true);
            ui->pushButtonStreamGrids->setFocus();
            return;
        }
        if (ui->lineEditThreshold->text() == nullptr)
        {
            ui->pushButtonSuggestMe->setDefault(true);
            ui->pushButtonSuggestMe->setFocus();
            return;
        }
        ui->pushButtonRun->setDefault(true);
        ui->pushButtonRun->setFocus();

    } catch (...) {
        qDebug() << "Error: pushButtonSetFocus is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to clear message log
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StreamGrids::Clear_Log()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start StreamGrids::Clear_Log()";

    try {

        LogsString = tr("");
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

    } catch (...) {
        qDebug() << "Error: StreamGrids::Clear_Log() is returning w/o checking";
    }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Threshold
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StreamGrids::on_lineEditThreshold_textChanged()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start on_lineEditThreshold_textChanged";

    try {

        Clear_Log();

        QString Threshold = ui->lineEditThreshold->text();
        bool badcharfound = false;
        bool isNumeric = false;
        foreach(const QString &string, Threshold)
        {
            string.toDouble(&isNumeric);
            if(isNumeric == false)
            {
                badcharfound = true;
            }
        }

        if(badcharfound)
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Invalid threshold. </span>") +tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
        }

    } catch (...) {
        qDebug() << "Error: on_lineEditThreshold_textChanged is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button Clicked Event for FlowAccGrids (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StreamGrids::on_pushButtonFlowAccGrids_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start on_pushButtonFlowAccGrids_clicked";

    try {

        Clear_Log();

        QString FlowAccFileName = QFileDialog::getOpenFileName(this, "Choose Flow Acc File", user_pihmgis_root_folder +tr("/1RasterProcessing"), "DEM Grid File(*.asc *.ASC)");
        if ( FlowAccFileName != nullptr)
        {
            Check_FlowAccGrids_Input(FlowAccFileName);

            //Suggested file name
            QString threshold = ui->lineEditThreshold->text();
            QString StreamGrids = filename_open_project+"/1RasterProcessing/Stream" + threshold + ".asc";

            Check_StreamGrids_Output(StreamGrids, true);

            pushButtonSetFocus();
        }
        else
        {
            qDebug() << "on_pushButtonFlowAccGrids_clicked: Invalid FlowAccFileName";
        }

    } catch (...) {
        qDebug() << "Error: on_pushButtonFlowAccGrids_clicked is returning w/o checking";
    }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button Clicked Event for StreamGrids (OUTPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StreamGrids::on_pushButtonStreamGrids_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start on_pushButtonStreamGrids_clicked";

    try {

        Clear_Log();

        QString StreamGridsFileName = QFileDialog::getSaveFileName(this, "Choose Stream Grid", user_pihmgis_root_folder + "/1RasterProcessing","Stream Grid File(*.asc)");
        if ( StreamGridsFileName != nullptr)
        {

            QString FlowAccFileName = ui->lineEditFlowAccGrids->text();
            Check_FlowAccGrids_Input(FlowAccFileName);

            QString tempString = StreamGridsFileName;
            if( ! (tempString.toLower()).endsWith(".asc") )
            {
                tempString.append(".asc");
                StreamGridsFileName = tempString;
            }

            Check_StreamGrids_Output(StreamGridsFileName, true);

            pushButtonSetFocus();
        }
        else
        {
            qDebug() << "on_pushButtonStreamGrids_clicked: Invalid StreamGridsFileName";
        }

    } catch (...) {
        qDebug() << "Error: on_pushButtonStreamGrids_clicked is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SuggestMe Button
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StreamGrids::on_pushButtonSuggestMe_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start on_pushButtonSuggestMe_clicked";

    try {

        Clear_Log();

        QString FlowAccFileName = ui->lineEditFlowAccGrids->text();
        if ( FlowAccFileName == nullptr )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Missing Flow Acc Input File ... </span>")+tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
            return;
        }

        QFile FlowAccFile(FlowAccFileName);
        if ( ! FlowAccFile.open(QIODevice::ReadOnly | QIODevice::Text) )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Open File: </span>") + FlowAccFileName + tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
            return;
        }

        LogsString.append(tr("<span style=\"color:#FF0000\">Started to calculate threshold ... </span>")+tr("<br>"));
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

        QTextStream FlowAccFileTextStream(&FlowAccFile);

        QString TempString;
        int tempInt, NumRows, NumColumns, NoData = 0;
        double tempDouble = 0;
        QList<int> FlowAccData;
        int count=0;
        //int flag = 1;

        FlowAccFileTextStream >> TempString; FlowAccFileTextStream >> NumColumns;
        FlowAccFileTextStream >> TempString; FlowAccFileTextStream >> NumRows;
        FlowAccFileTextStream >> TempString; FlowAccFileTextStream >> tempDouble;
        FlowAccFileTextStream >> TempString; FlowAccFileTextStream >> tempDouble;
        FlowAccFileTextStream >> TempString; FlowAccFileTextStream >> tempDouble;
        FlowAccFileTextStream >> TempString; FlowAccFileTextStream >> NoData;

        qDebug() <<"NumRows = " <<NumRows<<" NumColumns = "<<NumColumns<<" NoData = "<<NoData<<"\n";

        //FlowAccData = (int *)malloc(NumRows*NumColumns* sizeof(int));
        for(int i=0; i<NumRows*NumColumns; i++)
        {
            FlowAccFileTextStream >> tempInt;
            if(tempInt >= 0)
            {
                //FlowAccData[i] = tempInt;
                FlowAccData << tempInt;
                count++;
            }
        }

        qSort(FlowAccData.begin(), FlowAccData.end());
        //qDebug() << FlowAccData;

        qDebug() << "FlowAccData Length = " << FlowAccData.length();
        qDebug() << "Num Threshold Grids = " << FlowAccData.length() - ( (int) (FlowAccData.length() * 0.9937) + 1 );
        qDebug() << "Threshold Acc Value = " << FlowAccData.at( (int) (FlowAccData.length() * 0.9937) + 1);

        ui->lineEditThreshold->setText(QString::number(FlowAccData.at( (int) (FlowAccData.length() * 0.9937) + 1)));
        ui->lineEditThreshold->setStyleSheet("color: black;");

        //Clean up //TODO come back and check if I need to use special pointers
        FlowAccData.clear();
        FlowAccFile.close();

        LogsString.append(tr("<span style=\"color:#FF0000\">Finished calculating threshold ... </span>")+tr("<br>"));
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

    } catch (...) {
        qDebug() << "Error: on_pushButtonSuggestMe_clicked is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Run Button Clicked Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StreamGrids::on_pushButtonRun_clicked()
{

    if(print_debug_messages)
        qDebug() << "INFO: Start on_pushButtonRun_clicked";

    try {

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Clear Log
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Clear_Log();

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check inputs
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QString FlowAccGrids = ui->lineEditFlowAccGrids->text();
        QString StreamGrids = ui->lineEditStreamGrids->text();
        QString Threshold = ui->lineEditThreshold->text();

        bool flowacc_check = Check_FlowAccGrids_Input(FlowAccGrids);
        if(!flowacc_check)
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Flow Acc Grid Input File Missing </span>")+tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
            return;
        }

        bool threshold_check = Check_Threshold_Input(Threshold);
        if(!threshold_check)
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Check Threshold Input (is it a number?) </span>")+tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Does output already exist?
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool streamgrids_check = Check_StreamGrids_Output(StreamGrids, true);
        if(streamgrids_check)
        {
            return;
        }


        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check file access
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if ( ! CheckFileAccess(FlowAccGrids, "ReadOnly") )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Read Access ... </span>") + FlowAccGrids + tr("<br>"));
            return;
        }

        if ( ! CheckFileAccess(StreamGrids, "WriteOnly") )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Write Access ... </span>") + StreamGrids + tr("<br>"));
            return;
        }


        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Run Stream Grids
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        LogsString.append("Running Stream Grids ... <br>");
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

        const char *dummystr = "dummy";
        int ErrorStr = stream_definition((char *)qPrintable(FlowAccGrids), (char *)dummystr, (char *)qPrintable(StreamGrids), 1, Threshold.toInt() );
        if( ErrorStr != 0 )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Stream Grid Processing Failed ... </span>")+tr("<br>"));
            LogsString.append(tr("<span style=\"color:#FF0000\">RETURN CODE: ... </span>")+QString::number(ErrorStr)+tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check output filenames
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        streamgrids_check = Check_StreamGrids_Output(StreamGrids, true);
        if(!streamgrids_check)
        {
            return;
        }

        qint64 size = file_Size(StreamGrids);
        if( size < 1)
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">Error: StreamGrids failed, invalid file size: </span>") + size +tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update Project file
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QStringList ProjectIOStringList;
        ProjectIOStringList << "StreamGrids" << FlowAccGrids << StreamGrids << Threshold;
        WriteModuleLine(filename_open_project, ProjectIOStringList);
        ProjectIOStringList.clear();

        Clear_Log();

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update Message box
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Clear_Log();
        LogsString.append(tr("<br><b>Flow Grids Processing Completed.</b>")+tr("<br>"));
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

        ui->pushButtonRun->setDefault(false);
        ui->pushButtonClose->setDefault(true);
        ui->pushButtonClose->setFocus();

    } catch (...) {
        qDebug() << "Error: on_pushButtonRun_clicked is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Close button event
// TODO, Decide on keeping button next highlights or not
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StreamGrids::on_pushButtonClose_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start on_pushButtonClose_clicked";

    try {
        //QStringList default_params; default_params << "WORKFLOW2" << "LINKGRIDS";
        //QMetaObject::invokeMethod(parent(),"set_defaults",Q_ARG(QStringList,default_params));
        close();
    } catch (...) {
        qDebug() << "Error: on_pushButtonClose_clicked is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Help button event
// TODO, Need cataract server back online
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StreamGrids::on_pushButtonHelp_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start on_pushButtonHelp_clicked";

    try {
        //        LogsString = tr("");
        //        if ( ! QDesktopServices::openUrl(QUrl("http://cataract.cee.psu.edu/PIHM/index.php/PIHMgis_3.0#Stream_Grids")) )
        //            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Load HTTP Link ... </span>")+tr("<br>"));
        //        ui->textBrowserLogs->setHtml(LogsString);
        //        ui->textBrowserLogs->repaint();
    } catch (...) {
        qDebug() << "Error: on_pushButtonHelp_clicked is returning w/o checking";
    }
}
