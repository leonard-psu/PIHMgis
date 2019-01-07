#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>

#include "flowgrids.h"
#include "ui_flowgrids.h"

#include "0LibsIO/IOProjectFile.h"
#include "0LibsRaster/ADFFiletoASCFile.h"
#include "0LibsRaster/setdir.h"
#include "0LibsRaster/aread8.h"
#include "globals.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FlowGrids Constructor
// Parent is Main Window, filename is the open project text file used to store project details
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FlowGrids::FlowGrids(QWidget *parent, QString filename) :
    QDialog(parent),
    ui(new Ui::FlowGrids)
{

    if(print_debug_messages)
        qDebug() << "INFO: Start FlowGrids";

    try {

        ui->setupUi(this);

        filename_open_project = filename;
        bool found_file = false;

        QFile ProjectFile(filename_open_project);
        if ( ! ProjectFile.open(QIODevice::ReadOnly | QIODevice::Text) )
        {
            Log_Error_Message("Unable to Open project file: " + filename_open_project);
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
        qDebug() << "Error: FlowGrids is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FlowGrids Deconstructor
// Todo: Check for memory leaks
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FlowGrids::~FlowGrids()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ~FlowGrids";

    try {

        delete ui;

    } catch (...) {
        qDebug() << "Error: ~FlowGrids is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Load_Project_Settings
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool FlowGrids::Load_Project_Settings()
{
    if(print_debug_messages)
        qDebug() << "INFO: FlowGrids::Load_Project_Settings()";

    try {

        QStringList ModuleStringList = ReadModuleLine(filename_open_project,tr("FillPits"));

        if ( ModuleStringList.length() > 0  )
        {
            QString fillpits = ModuleStringList.at(2);

            //Suggested file names
            QString flowdir = filename_open_project+"/1RasterProcessing/FlowDir.asc";
            QString flowacc = filename_open_project+"/1RasterProcessing/FlowAcc.asc";

            bool fill_check = Check_Fillpit_Input(fillpits);
            if(!fill_check)
            {
                Log_Error_Message("Fillpit input does not exist. ");
            }

            ui->lineEditFlowDirGrids->setText(flowdir);
            ui->lineEditFlowAccGrids->setText(flowacc);
        }

        //Check if outputs already exist
        ModuleStringList = ReadModuleLine(filename_open_project,tr("FlowGrids"));

        if ( ModuleStringList.length() > 0 )
        {
            QString flowdir = ModuleStringList.at(2);
            QString flowacc = ModuleStringList.at(3);

            bool flow_check = Check_FlowDir_Output(flowdir, true);
            bool acc_check = Check_FlowAcc_Output(flowacc, true);
        }

    } catch (...) {
        qDebug() << "Error: FlowGrids::Load_Project_Settings is returning w/o checking";
        return false;
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to assist if DEM input file exists (returns true) or does not (returns false)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool FlowGrids::Check_Fillpit_Input(QString file )
{
    if(print_debug_messages)
        qDebug() << "INFO: Check_Fillpit_Intput()";

    bool result = false;

    try {

        if(  fileExists(file) )
        {
            ui->lineEditFillPits->setStyleSheet("color: black;");
            ui->lineEditFillPits->setText(file);
            result = true;
        }
        else
        {
            ui->lineEditFillPits->setStyleSheet("color: red;");
            ui->lineEditFillPits->setText(file);

            Log_Error_Message("Fillpit input does not exist: " + file);
            result = false;
        }


    } catch (...) {
        qDebug() << "Error: Check_Fillpit_Intput is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to assist if Flow Direction Grid output file exists (returns true) or does not (returns false)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool FlowGrids::Check_FlowDir_Output(QString file, bool color_and_message_if_exists )
{
    if(print_debug_messages)
        qDebug() << "INFO: Check_FlowDir_Output()";

    bool result = false;

    try {

        if(  fileExists(file) )
        {
            if(color_and_message_if_exists)
            {
                Log_Message("Warning: Flow Direction output already exists: " + file + " You may need to delete this file(s).");
            }

            ui->lineEditFlowDirGrids->setStyleSheet("color: red;");
            ui->lineEditFlowDirGrids->setText(file);

            result = true;
        }
        else
        {
            ui->lineEditFlowDirGrids->setText(file);
            ui->lineEditFlowDirGrids->setStyleSheet("color: black;");

            result = false;
        }

    } catch (...) {
        qDebug() << "Error: Check_FlowDir_Output is returning w/o checking";
        result = false;
    }

    return result;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to assist if Flow Accumulation Grid output file exists (returns true) or does not (returns false)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool FlowGrids::Check_FlowAcc_Output(QString file, bool color_and_message_if_exists )
{
    if(print_debug_messages)
        qDebug() << "INFO: Check_FlowAcc_Output()";

    bool result = false;

    try {

        if(  fileExists(file) )
        {
            if(color_and_message_if_exists)
            {
                Log_Message("Warning: Flow Accumulation already exist: " + file + " You may need to delete this file(s).");
            }

            ui->lineEditFlowAccGrids->setStyleSheet("color: red;");
            ui->lineEditFlowAccGrids->setText(file);
            result = true;
        }
        else
        {
            ui->lineEditFlowAccGrids->setText(file);
            ui->lineEditFlowAccGrids->setStyleSheet("color: black;");

            result = false;
        }

    } catch (...) {
        qDebug() << "Error: Check_FlowAcc_Output is returning w/o checking";
        result = false;
    }

    return result;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to focus button selection (needed for users w/o mouse)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlowGrids::pushButtonSetFocus()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start FlowGrids::pushButtonSetFocus()";

    try {

        ui->pushButtonFillPits->setDefault(false);
        ui->pushButtonsFlowDirGrid->setDefault(false);
        ui->pushButtonFlowAccGrid->setDefault(false);
        ui->pushButtonRun->setDefault(false);

        if (ui->lineEditFillPits->text() == nullptr)
        {
            ui->pushButtonFillPits->setDefault(true);
            ui->pushButtonFillPits->setFocus();
            return;
        }
        if (ui->lineEditFlowDirGrids->text() == nullptr)
        {
            ui->pushButtonsFlowDirGrid->setDefault(true);
            ui->pushButtonsFlowDirGrid->setFocus();
            return;
        }
        if (ui->lineEditFlowAccGrids->text() == nullptr)
        {
            ui->pushButtonFlowAccGrid->setDefault(true);
            ui->pushButtonFlowAccGrid->setFocus();
            return;
        }

        ui->pushButtonRun->setDefault(true);
        ui->pushButtonRun->setFocus();


    } catch (...) {
        qDebug() << "Error: FlowGrids::pushButtonSetFocus is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to clear message log
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlowGrids::Clear_Log()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start FlowGrids::Clear_Log()";

    try {

        LogsString = tr("");
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

    } catch (...) {
        qDebug() << "Error: FlowGrids::Clear_Log() is returning w/o checking";
    }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check Log_Error_Message
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlowGrids::Log_Error_Message(QString message)
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
void FlowGrids::Log_Message(QString message)
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
// Browse Button Clicked Event for Fill pits file
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlowGrids::on_pushButtonFillPits_clicked()
{

    if(print_debug_messages)
        qDebug() << "INFO: Start FlowGrids::on_pushButtonFillPits_clicked()";

    try {

        Clear_Log();

        QString FillPitsFileName = QFileDialog::getOpenFileName(this, "Choose DEM File", user_pihmgis_root_folder + tr("/.."), "DEM Grid File(*.adf *.asc *.ASC)");
        if ( FillPitsFileName != nullptr)
        {
            Check_Fillpit_Input(FillPitsFileName);
            Check_FlowDir_Output(ui->lineEditFlowDirGrids->text(), true);
            Check_FlowAcc_Output(ui->lineEditFlowAccGrids->text(), true);

            pushButtonSetFocus();
        }
        else
        {
           Log_Message("on_pushButtonFillPits_clicked: Invalid DEMFileName");
        }

    } catch (...) {
        qDebug() << "Error: FlowGrids::on_pushButtonFillPits_clicked is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button Clicked Event for FlowDir file
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlowGrids::on_pushButtonsFlowDirGrid_clicked()
{

    if(print_debug_messages)
        qDebug() << "INFO: Start FlowGrids::on_pushButtonsFlowDirGrid_clicked()";

    try {
        Clear_Log();

        QString FlowDirFileName = QFileDialog::getSaveFileName(this, "Choose Flow Dir Grid", user_pihmgis_root_folder + "/1RasterProcessing","Flow Dir Grid File(*.asc)");
        if ( FlowDirFileName != nullptr)
        {
            Check_Fillpit_Input(ui->lineEditFillPits->text());
            Check_FlowDir_Output(FlowDirFileName, true);
            Check_FlowAcc_Output(ui->lineEditFlowAccGrids->text(), true);

            pushButtonSetFocus();
        }

    } catch (...) {
        qDebug() << "Error: FlowGrids::on_pushButtonsFlowDirGrid_clicked is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button Clicked Event for FlowGrids file
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlowGrids::on_pushButtonFlowAccGrid_clicked()
{

    if(print_debug_messages)
        qDebug() << "INFO: Start FlowGrids::on_pushButtonFlowAccGrid_clicked()";

    try {

        Clear_Log();

        QString FlowAccFileName = QFileDialog::getSaveFileName(this, "Choose Flow Acc Grid", user_pihmgis_root_folder + "/1RasterProcessing","Flwo Acc Grid File(*.asc)");
        if ( FlowAccFileName != nullptr)
        {
            Check_Fillpit_Input(ui->lineEditFillPits->text());
            Check_FlowDir_Output(ui->lineEditFlowDirGrids->text(), true);
            Check_FlowAcc_Output(FlowAccFileName, true);

            pushButtonSetFocus();
        }
        else
        {
            Log_Message("on_pushButtonFlowAccGrid_clicked: Invalid FlowAccFileName");
        }

    } catch (...) {
        qDebug() << "Error: FlowGrids::on_pushButtonFlowAccGrid_clicked is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Run Button Clicked Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlowGrids::on_pushButtonRun_clicked()
{

    if(print_debug_messages)
        qDebug() << "INFO: Start FlowGrids::on_pushButtonRun_clicked()";

    try {

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Clear Log
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Clear_Log();

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check input
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QString filename_fill = ui->lineEditFillPits->text();
        QString filename_flow =  ui->lineEditFlowDirGrids->text();
        QString filename_acc =  ui->lineEditFlowAccGrids->text();

        bool fill_check = Check_Fillpit_Input(filename_fill);
        if(!fill_check)
        {
            Log_Error_Message("Fill Pits Input File Missing: " + filename_fill);
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Does output filename_flow already exist?
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool flow_check = Check_FlowDir_Output(filename_flow, true);
        if(flow_check)
        {
            return;
        }

        if ( ! CheckFileAccess(filename_flow, "WriteOnly") )
        {
            Log_Error_Message("No Write Access to " + filename_flow);
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Does output filename_acc already exist?
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool acc_check = Check_FlowAcc_Output(filename_acc, false);
        if(acc_check)
        {
            Log_Error_Message("Fill acc output already exists: " + filename_acc );
            return;
        }

        if ( ! CheckFileAccess(filename_acc, "WriteOnly") )
        {
            Log_Error_Message("No Write Access to ... " + filename_acc);
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Convert Binary to Ascii
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QString FillPitsFileName = filename_fill;
        QString ASCFileName = FillPitsFileName;

        if((FillPitsFileName.toLower()).endsWith(".adf"))
        {
            ASCFileName.truncate(ASCFileName.length()-3);
            ASCFileName.append("asc");

            Log_Message("Converting Arc Binary File to ASC File ... ");

            int check = ADFFiletoASCFile(FillPitsFileName, ASCFileName);
            if(check == 0 ) // no errors
            {
                Log_Message("Success converting Arc binary file");
            }
            else if (check == -9999) //Something else went wrong
            {
                Log_Error_Message("reading Arc binary file. Check Logs.");
                return;
            }
            else if (check == -1000)
            {
                Log_Error_Message("reading Arc binary file. Check Logs.");
                return;
            }
            else if (check == -1001)
            {
                Log_Error_Message("WARNING, Issues found parsing values. Recommend checking with GIS tool.");
                int ret = QMessageBox::warning(this, tr("Issues found converting file"),
                                               tr("Click Ok to continue. Cancel to stop."),
                                               QMessageBox::Ok | QMessageBox::Cancel,
                                               QMessageBox::Ok);

                bool clicked_cancel = true; //Make it default
                switch(ret)
                {
                case QMessageBox::Ok:
                    clicked_cancel = false;
                    break;
                case QMessageBox::Cancel:
                    clicked_cancel = true;
                    break;
                }

                if(clicked_cancel)
                    return;
            }
            else if (check > 0 ) //Positive numbers mean setup problem
            {
                Log_Error_Message("Error reading Arc binary file. Check Logs.");
                return;
            }
            else
            {
                int ret = QMessageBox::warning(this, tr("Issues found converting file"),
                                               tr("Click Ok to continue. Cancel to stop."),
                                               QMessageBox::Ok | QMessageBox::Cancel,
                                               QMessageBox::Ok);

                bool clicked_cancel = true; //Make it default
                switch(ret)
                {
                case QMessageBox::Ok:
                    clicked_cancel = false;
                    break;
                case QMessageBox::Cancel:
                    clicked_cancel = true;
                    break;
                }

                if(clicked_cancel)
                    return;
            }
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Get DEM Resolution needed as well
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        int DEMResolution = 0;
        QFile ASCFile(ASCFileName);
        ASCFile.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream ASCFileTextStream(&ASCFile);

        QString TempString;
        ASCFileTextStream >> TempString; ASCFileTextStream >> TempString; ASCFileTextStream >> TempString; ASCFileTextStream >> TempString;
        ASCFileTextStream >> TempString; ASCFileTextStream >> TempString; ASCFileTextStream >> TempString; ASCFileTextStream >> TempString;
        ASCFileTextStream >> TempString;

        ASCFileTextStream >> DEMResolution;
        Log_Message("DEM Resolution (Integer) = " + QString::number(DEMResolution) );
        ASCFile.close();


        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Run Flow Dir
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Log_Message("Running Flow Acc Grids ... ");

        QString SlopeFileName = filename_flow;
        SlopeFileName.truncate(SlopeFileName.length()-4);
        SlopeFileName.append("Slope.asc");

        int ErrorFDir = setdird8( ASCFileName,filename_flow, SlopeFileName );
        if( ErrorFDir != 0 )
        {
            Log_Error_Message("Flow Direction Processing Failed ... ");
            Log_Error_Message("RETURN CODE: ... " +QString::number(ErrorFDir));

            return;
        }

        Log_Message("Running Flow Acc Grids ... ");

        int ErrorAcc = aread8( filename_flow, filename_acc, 0.0, 0.0, 1 );
        if( ErrorAcc != 0 )
        {
            Log_Error_Message("Flow Accumulation Processing Failed ... ");
            Log_Error_Message("RETURN CODE: ... "+QString::number(ErrorAcc));

            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check output filename_flow
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        fill_check = Check_FlowDir_Output(filename_flow, true);
        if(!fill_check)
        {
            return;
        }
        qint64 size = file_Size(filename_flow);
        if( size < 1)
        {
            Log_Error_Message("Flow Direction failed, invalid file size: " + size);

            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update Project file
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QStringList ProjectIOStringList;
        ProjectIOStringList << "FlowGrids" << filename_fill << filename_flow << filename_acc << QString::number(DEMResolution);
        WriteModuleLine(filename_open_project, ProjectIOStringList);
        ProjectIOStringList.clear();

        Clear_Log();

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check output filename_acc
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        fill_check = Check_FlowAcc_Output(filename_acc, false);
        if(!fill_check)
        {
            Log_Error_Message("Flow Accumulation failed, file does not exist: " + filename_acc);

            return;
        }
        size = file_Size(filename_acc);
        if( size < 1)
        {
            Log_Error_Message("Flow Accumulation failed, invalid file size: " + size);

            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update Message box
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Log_Message("Flow Grids Processing Completed.");
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

        ui->pushButtonRun->setDefault(false);
        ui->pushButtonClose->setDefault(true);
        ui->pushButtonClose->setFocus();

    } catch (...) {
        qDebug() << "Error: FlowGrids::on_pushButtonRun_clicked is returning w/o checking";
    }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Close button event
// TODO, Decide on keeping button next highlights or not
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlowGrids::on_pushButtonClose_clicked()
{

    if(print_debug_messages)
        qDebug() << "INFO: Start FlowGrids::on_pushButtonClose_clicked()";

    try{
        //        QStringList default_params; default_params << "WORKFLOW2" << "STRGRIDS";
        //        QMetaObject::invokeMethod(parent(),"set_defaults",Q_ARG(QStringList,default_params));
        close();

    } catch (...) {
        qDebug() << "Error: FlowGrids::on_pushButtonClose_clicked is returning w/o checking";
    }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Help button event
// TODO, Need cataract server back online
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlowGrids::on_pushButtonHelp_clicked()
{

    if(print_debug_messages)
        qDebug() << "INFO: Start FlowGrids::on_pushButtonHelp_clicked()";

    try{
        //        LogsString = tr("");
        //        if ( ! QDesktopServices::openUrl(QUrl("http://cataract.cee.psu.edu/PIHM/index.php/PIHMgis_3.0#Flow_Grids")) )
        //            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Load HTTP Link ... </span>")+tr("<br>"));
        //        ui->textBrowserLogs->setHtml(LogsString);
        //        ui->textBrowserLogs->repaint();

    } catch (...) {
        qDebug() << "Error: FlowGrids::on_pushButtonHelp_clicked is returning w/o checking";
    }
}
