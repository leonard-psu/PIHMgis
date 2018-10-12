#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>

#include "fillpits.h"
#include "ui_fillpits.h"

#include "0LibsIO/IOProjectFile.h"
#include "0LibsRaster/ADFFiletoASCFile.h"
#include "0LibsRaster/flood.h"
#include "globals.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FillPits Constructor
// Parent is Main Window, filename is the open project text file used to store project details
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FillPits::FillPits(QWidget *parent, QString filename) :
    QDialog(parent),
    ui(new Ui::FillPits)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start FillPits";


    try {

        ui->setupUi(this);

        filename_open_project = filename;
        bool found_file = false;

        if(print_debug_messages)
            qDebug() << "INFO: filename -> " << filename_open_project;

        QFile ProjectFile(filename_open_project);
        if ( ! ProjectFile.open(QIODevice::ReadOnly | QIODevice::Text) )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Open project file: </span>") + filename_open_project +tr("<br>"));
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
        qDebug() << "Error: FillPits is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FillPits Deconstructor
// Todo: Check for memory leaks
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FillPits::~FillPits()
{
    if(print_debug_messages)
        qDebug() << "INFO: ~FillPits()";

    try {
        delete ui;
    } catch (...) {
        qDebug() << "Error: ~FillPits is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Load_Project_Settings
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool FillPits::Load_Project_Settings()
{
    if(print_debug_messages)
        qDebug() << "INFO: FillPits::Load_Project_Settings()";

    try {
        QStringList ModuleStringList = ReadModuleLine(filename_open_project, tr("FillPits"));

        if ( ModuleStringList.length() > 0 )
        {
            QString dem = ModuleStringList.at(1);
            QString fillpits = ModuleStringList.at(2);

            bool dem_check = Check_DEM_Input(dem);

            bool fill_check = Check_Fillpit_Output(fillpits, true);

        }

        pushButtonSetFocus();

    } catch (...) {
        qDebug() << "Error: FillPits::Load_Project_Settings is returning w/o checking";
        return false;
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to assist if DEM input file exists (returns true) or does not (returns false)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool FillPits::Check_DEM_Input(QString dem )
{
    if(print_debug_messages)
        qDebug() << "INFO: Check_DEM_Input()";

    bool result = false;

    try {

        if(  fileExists(dem) )
        {
            ui->lineEditDEM->setStyleSheet("color: black;");
            ui->lineEditDEM->setText(dem);
            result = true;
        }
        else
        {
            ui->lineEditDEM->setStyleSheet("color: red;");
            ui->lineEditDEM->setText(dem);

            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: DEM input does not exist: </span>") + dem +tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
            result = false;
        }


    } catch (...) {
        qDebug() << "Error: Check_DEM_Input is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to assist if Pitfilled DEM output file exists (returns true) or does not (returns false)
// Will color red and warning if exists with color_and_message_if_exists=true
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool FillPits::Check_Fillpit_Output(QString fillpits, bool color_and_message_if_exists )
{
    if(print_debug_messages)
        qDebug() << "INFO: Check_Fillpit_Output()";

    bool result = false;

    try {

        if(  fileExists(fillpits) )
        {
            if(color_and_message_if_exists)
            {
                LogsString.append(tr("<span style=\"color:#FF0000\">Warning: fillpits output already exists: </span>") + fillpits +tr(" You may need to delete this file(s).<br>"));
                ui->textBrowserLogs->setHtml(LogsString);
                ui->textBrowserLogs->repaint();
            }

            ui->lineEditFillPits->setStyleSheet("color: red;");
            ui->lineEditFillPits->setText(fillpits);
            result = true;
        }
        else
        {
            ui->lineEditFillPits->setStyleSheet("color: black;");
            ui->lineEditFillPits->setText(fillpits);

            result = false;
        }

    } catch (...) {
        qDebug() << "Error: Check_Fillpit_Output is returning w/o checking";
        result = false;
    }

    return result;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to focus button selection (needed for users w/o mouse)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FillPits::pushButtonSetFocus()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start FillPits::pushButtonSetFocus()";

    try {
        ui->pushButtonDEM->setDefault(false);
        ui->pushButtonFillPits->setDefault(false);
        ui->pushButtonRun->setDefault(false);

        if (ui->lineEditDEM->text() == nullptr)
        {
            ui->pushButtonDEM->setDefault(true);
            ui->pushButtonDEM->setFocus();
            return;
        }

        if (ui->lineEditFillPits->text() == nullptr)
        {
            ui->pushButtonFillPits->setDefault(true);
            ui->pushButtonFillPits->setFocus();
            return;
        }

        ui->pushButtonRun->setDefault(true);
        ui->pushButtonRun->setFocus();

    } catch (...) {
        qDebug() << "Error: FillPits::pushButtonSetFocus() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to clear message log
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FillPits::Clear_Log()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start FillPits::Clear_Log()";

    try {

        LogsString = tr("");
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

    } catch (...) {
        qDebug() << "Error: FillPits::Clear_Log() is returning w/o checking";
    }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button Clicked Event for DEM
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FillPits::on_pushButtonDEM_clicked()
{

    if(print_debug_messages)
        qDebug() << "INFO: Start FillPits::on_pushButtonDEM_clicked()";

    try {

        Clear_Log();

        QString DEMFileName = QFileDialog::getOpenFileName(this, "Choose DEM File", user_pihmgis_root_folder +tr("/.."), "DEM Grid File(*.adf *.asc *.ASC)");

        if ( DEMFileName != nullptr)
        {
            Check_DEM_Input(DEMFileName);
            Check_Fillpit_Output(ui->lineEditFillPits->text(), true);

            pushButtonSetFocus();
        }
        else
        {
            qDebug() << "on_pushButtonDEM_clicked: Invalid DEMFileName";
        }

    } catch (...) {
        qDebug() << "Error: FillPits::on_pushButtonDEM_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button Clicked Event for Fill pits file
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FillPits::on_pushButtonFillPits_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start FillPits::on_pushButtonFillPits_clicked()";

    try {

        Clear_Log();

        QString FillPitFileName = QFileDialog::getSaveFileName(this, "Choose Fill Pit Grid", user_pihmgis_root_folder+"/1RasterProcessing","Fill Pit Grid File(*.asc)");
        if ( FillPitFileName != nullptr)
        {
            Check_DEM_Input(ui->lineEditDEM->text());
            Check_Fillpit_Output(FillPitFileName, true);
            pushButtonSetFocus();
        }
        else
        {
            qDebug() << "on_pushButtonFillPits_clicked: Invalid FillPitFileName";
        }

    } catch (...) {
        qDebug() << "Error: FillPits::on_pushButtonFillPits_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Here the DEM input is filled using flood function
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FillPits::on_pushButtonRun_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start FillPits::on_pushButtonRun_clicked()";

    try {

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Clear Log
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Clear_Log();

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check input
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QString filename_dem = ui->lineEditDEM->text();
        QString filename_fill =  ui->lineEditFillPits->text();

        bool dem_check = Check_DEM_Input(filename_dem);
        if(!dem_check)
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">Error: DEM input does not exist: </span>") + filename_dem +tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Does output already exist?
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool fill_check = Check_Fillpit_Output(filename_fill, true);
        if(fill_check)
        {
            return;
        }

        if ( ! CheckFileAccess(filename_fill, "WriteOnly") )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Write Access ... </span>") + filename_fill + tr("<br>"));
            return;
        }


        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Convert Binary to Ascii
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QString DEMFileName = filename_dem;
        QString ASCFileName = DEMFileName;

        if((DEMFileName.toLower()).endsWith(".adf"))
        {
            ASCFileName.truncate(ASCFileName.length()-3);
            ASCFileName.append("asc");

            LogsString.append("Converting Arc Binary File to ASC File ... <br>");
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
            ADFFiletoASCFile(DEMFileName, ASCFileName);
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Get DEM Resolution needed as well
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        int DEMResolution = 0;
        QFile ASCFile(ASCFileName);
        ASCFile.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream ASCFileTextStream(&ASCFile);

        QString TempString;
        ASCFileTextStream>>TempString;ASCFileTextStream>>TempString;ASCFileTextStream>>TempString;ASCFileTextStream>>TempString;
        ASCFileTextStream>>TempString;ASCFileTextStream>>TempString;ASCFileTextStream>>TempString;ASCFileTextStream>>TempString;
        ASCFileTextStream>>TempString;

        ASCFileTextStream >> DEMResolution;
        qDebug() << "DEM Resolution (Integer) = "<<DEMResolution<<"\n";
        ASCFile.close();

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Run pit fill
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        LogsString.append("Running Fill Pits ... <br>");
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

        const char *dummystr = "dummy";

        int ErrorFill = flood( (char *)qPrintable(ASCFileName), (char *)dummystr, (char *)qPrintable(filename_fill) );
        if( ErrorFill != 0 )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Fill Pits Processing Failed ... </span>")+tr("<br>"));
            LogsString.append(tr("<span style=\"color:#FF0000\">RETURN CODE: ... </span>")+QString::number(ErrorFill)+tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check output file
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        fill_check = Check_Fillpit_Output(filename_fill, true);
        if(!fill_check)
        {
            return;
        }
        qint64 size = file_Size(filename_fill);
        if( size < 1)
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">Error: Fillpit failed, invalid file size: </span>") + size +tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update Project file
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QStringList ProjectIOStringList;
        ProjectIOStringList << "FillPits" << filename_dem << filename_fill << QString::number(DEMResolution);
        WriteModuleLine(filename_open_project, ProjectIOStringList);
        ProjectIOStringList.clear();

        Clear_Log();

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update Message box
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        LogsString.append(tr("<br><b>Fill Pits Processing Completed.</b>")+tr("<br>"));
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

        ui->pushButtonRun->setDefault(false);
        ui->pushButtonClose->setDefault(true);
        ui->pushButtonClose->setFocus();


    } catch (...) {
        qDebug() << "Error: FillPits::on_pushButtonRun_clicked() is returning w/o checking";
    }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Close button event
// TODO, Decide on keeping button next highlights or not
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FillPits::on_pushButtonClose_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start FillPits::on_pushButtonClose_clicked()";

    try {

        //        QStringList default_params; default_params << "WORKFLOW2" << "FLOWGRIDS";
        //        QMetaObject::invokeMethod(parent(),"set_defaults",Q_ARG(QStringList,default_params));
        close();

    } catch (...) {
        qDebug() << "Error: FillPits::on_pushButtonClose_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Help button event
// TODO, Need cataract server back online
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FillPits::on_pushButtonHelp_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start FillPits::on_pushButtonHelp_clicked()";

    try {

        LogsString = tr("");
        //        if ( ! QDesktopServices::openUrl(QUrl("http://cataract.cee.psu.edu/PIHM/index.php/PIHMgis_3.0#Fill_Pits")) )
        //            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Load HTTP Link ... </span>")+tr("<br>"));
        //        ui->textBrowserLogs->setHtml(LogsString);
        //        ui->textBrowserLogs->repaint();

    } catch (...) {
        qDebug() << "Error: FillPits::on_pushButtonHelp_clicked() is returning w/o checking";
    }
}
