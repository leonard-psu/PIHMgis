#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>

#include "calibdatafile.h"
#include "ui_calibdatafile.h"

#include "0LibsIO/IOProjectFile.h"
#include "globals.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CalibDataFile Constructor
// Parent is Main Window, filename is the open project text file used to store project details
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CalibDataFile::CalibDataFile(QWidget *parent, QString filename) :
    QDialog(parent),
    ui(new Ui::CalibDataFile)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start CalibDataFile";

    try {
        ui->setupUi(this);

        filename_open_project = filename;
        bool found_file = false;

        QFile ProjectFile(filename_open_project);
        if ( ! ProjectFile.open(QIODevice::ReadOnly | QIODevice::Text) )
        {
            Log_Error_Message("Unable to Open File: " + filename_open_project );
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

        ui->tabWidget->setCurrentIndex( 0 );

        pushButtonSetFocus();
    } catch (...) {
        qDebug() << "Error: CalibDataFile is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CalibDataFile Deconstructor
// Todo: Check for memory leaks
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CalibDataFile::~CalibDataFile()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ~CalibDataFile";

    try {
        delete ui;
    } catch (...) {
        qDebug() << "Error: ~CalibDataFile is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check Log_Error_Message
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CalibDataFile::Log_Warning_Message(QString message)
{
    try {
        LogsString.append(tr("<span style=\"color:#FF0000\">Warning: ") + message + " </span>")+tr("<br>");
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();
    } catch (...) {
        qDebug() << "Error: Log_Warning_Message is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check Log_Error_Message
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CalibDataFile::Log_Error_Message(QString message)
{
    try {
        LogsString.append(tr("<span style=\"color:#FF0000\">Error: ") + message + " </span>" +tr("<br>"));
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();
    } catch (...) {
        qDebug() << "Error: Log_Error_Message is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Load_Project_Settings
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CalibDataFile::Load_Project_Settings()
{
    if (print_debug_messages)
        qDebug() << "INFO: TINShapeLayer::Load_Project_Settings()";

    try {

        QStringList ModuleStringList = ReadModuleLine(filename_open_project,tr("TINShapeLayer"));
        if ( ModuleStringList.length() > 0  )
        {
            QString TempFileName = ModuleStringList.at(3);
            TempFileName = TempFileName.right(TempFileName.length()-TempFileName.lastIndexOf("/")-1);

            TempFileName.replace( QString(".shp"), QString(".calib") );
            ui->lineEditCalibDataFile->setText(user_pihmgis_root_folder+"/4DataModelLoader/"+TempFileName);
        }

        ModuleStringList = ReadModuleLine(filename_open_project,tr("MeshDataFile"));
        if ( ModuleStringList.length() > 0  )
        {
            QString TempFileName = ModuleStringList.at(9);
            ui->lineEditCalibDataFile->setText(user_pihmgis_root_folder+"/4DataModelLoader/"+TempFileName+".calib");
        }

        ModuleStringList = ReadModuleLine(filename_open_project,tr("CalibDataFile"));
        if ( ModuleStringList.length() > 0 )
        {
            QString calib_filename = ModuleStringList.at(1);
            Check_Calib_Output(calib_filename,true);

            ui->doubleSpinBoxS_Alpha->setValue(ModuleStringList.at(2).toDouble());
            ui->doubleSpinBoxS_Beta->setValue(ModuleStringList.at(3).toDouble());
            ui->doubleSpinBoxS_Porosity->setValue(ModuleStringList.at(4).toDouble());
            ui->doubleSpinBoxS_InfilDepth->setValue(ModuleStringList.at(5).toDouble());
            ui->doubleSpinBoxS_KsatV->setValue(ModuleStringList.at(6).toDouble());
            ui->doubleSpinBoxS_MPKsatV->setValue(ModuleStringList.at(7).toDouble());

            ui->doubleSpinBoxG_KsatH->setValue(ModuleStringList.at(8).toDouble());
            ui->doubleSpinBoxG_KsatV->setValue(ModuleStringList.at(9).toDouble());
            ui->doubleSpinBoxG_MPKsatH->setValue(ModuleStringList.at(10).toDouble());
            ui->doubleSpinBoxG_MPDepth->setValue(ModuleStringList.at(11).toDouble());
            ui->doubleSpinBoxG_MPfracV->setValue(ModuleStringList.at(12).toDouble());
            ui->doubleSpinBoxG_MPfracH->setValue(ModuleStringList.at(13).toDouble());

            ui->doubleSpinBoxL_RZDepth->setValue(ModuleStringList.at(14).toDouble());
            ui->doubleSpinBoxL_VegFrac->setValue(ModuleStringList.at(15).toDouble());
            ui->doubleSpinBoxL_Albedo->setValue(ModuleStringList.at(16).toDouble());
            ui->doubleSpinBoxL_Roughness->setValue(ModuleStringList.at(17).toDouble());

            ui->doubleSpinBoxR_Rough->setValue(ModuleStringList.at(18).toDouble());
            ui->doubleSpinBoxR_BedTh->setValue(ModuleStringList.at(19).toDouble());
            ui->doubleSpinBoxR_KsatH->setValue(ModuleStringList.at(20).toDouble());
            ui->doubleSpinBoxR_KsatV->setValue(ModuleStringList.at(21).toDouble());
            ui->doubleSpinBoxR_Depth->setValue(ModuleStringList.at(22).toDouble());
            ui->doubleSpinBoxR_Width->setValue(ModuleStringList.at(23).toDouble());

            ui->doubleSpinBoxF_Precip->setValue(ModuleStringList.at(24).toDouble());
            ui->doubleSpinBoxF_Temp->setValue(ModuleStringList.at(25).toDouble());
            ui->doubleSpinBoxF_ET0->setValue(ModuleStringList.at(26).toDouble());
            ui->doubleSpinBoxF_ET1->setValue(ModuleStringList.at(27).toDouble());
            ui->doubleSpinBoxF_ET2->setValue(ModuleStringList.at(28).toDouble());
            ui->doubleSpinBoxF_ISMax->setValue(ModuleStringList.at(29).toDouble());
            ui->doubleSpinBoxF_ThruFall->setValue(ModuleStringList.at(30).toDouble());
            ui->doubleSpinBoxF_MeltFac->setValue(ModuleStringList.at(31).toDouble());
        }


    } catch (...) {
        qDebug() << "Error: TINShapeLayer::Load_Project_Settings is returning w/o checking";
        return false;
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to clear message log
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CalibDataFile::Clear_Log()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start CalibDataFile::Clear_Log()";

    try {

        LogsString = tr("");
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

    } catch (...) {
        qDebug() << "Error: CalibDataFile::Clear_Log() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to focus button selection (needed for users w/o mouse)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CalibDataFile::pushButtonSetFocus()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start CalibDataFile::pushButtonSetFocus()";

    try {
        ui->pushButtonCalibDataFile->setDefault(false);

        if (ui->lineEditCalibDataFile->text() == nullptr)
        {
            ui->pushButtonCalibDataFile->setDefault(true);
            ui->pushButtonCalibDataFile->setFocus();
            return;
        }

        ui->pushButtonRun->setDefault(true);
        ui->pushButtonRun->setFocus();
    } catch (...) {
        qDebug() << "Error: CalibDataFile::pushButtonSetFocus() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button Clicked Event  (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CalibDataFile::on_pushButtonCalibDataFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start CalibDataFile::on_pushButtonCalibDataFile_clicked()";

    try {

        Clear_Log();

        QString CalibDataFileName = QFileDialog::getSaveFileName(this, "Choose Calib Data File Name", user_pihmgis_root_folder +"/4DataModelLoader","Calib Data File(*.calib)");
        QString tempString = CalibDataFileName;
        if ( CalibDataFileName != nullptr)
        {
            if( ! (tempString.toLower()).endsWith(".calib") )
            {
                tempString.append(".calib");
                CalibDataFileName = tempString;
            }
            Check_Calib_Output(CalibDataFileName,true);
            pushButtonSetFocus();
        }

    } catch (...) {
        qDebug() << "Error: CalibDataFile::on_pushButtonCalibDataFile_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to assist if CALIB OUTPUT file exists (returns true) or does not (returns false)
// Will color red and warning if exists with color_and_message_if_exists=true
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CalibDataFile::Check_Calib_Output(QString file, bool color_and_message_if_exists){

    if(print_debug_messages)
        qDebug() << "INFO: Check_Calib_Output()";

    bool result = false;

    try {

        if(  fileExists(file) )
        {
            if(color_and_message_if_exists)
            {
                Log_Error_Message("Calib output already exists: " + file +tr(" You may need to delete this file."));
            }

            ui->lineEditCalibDataFile->setStyleSheet("color: red;");
            ui->lineEditCalibDataFile->setText(file);
            result = true;
        }
        else
        {
            ui->lineEditCalibDataFile->setStyleSheet("color: black;");
            ui->lineEditCalibDataFile->setText(file);

            result = false;
        }

    } catch (...) {
        qDebug() << "Error: Check_Calib_Output is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Create CALIB file (OUTPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CalibDataFile::calib_data_file(QString filename)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start CalibDataFile::calib_data_file()";

    try {

        QFile CalibFile( filename );
        if ( ! CalibFile.open(QIODevice::WriteOnly | QIODevice::Text) )
            return 129;

        QTextStream CalibFileTextStream(&CalibFile);

        CalibFileTextStream << ui->doubleSpinBoxG_KsatH->text() << "\t";
        CalibFileTextStream << ui->doubleSpinBoxG_KsatV->text() << "\t";
        CalibFileTextStream << ui->doubleSpinBoxS_KsatV->text() << "\t";
        CalibFileTextStream << ui->doubleSpinBoxG_MPKsatH->text() << "\t";
        CalibFileTextStream << ui->doubleSpinBoxS_MPKsatV->text() << "\n";

        CalibFileTextStream << ui->doubleSpinBoxS_InfilDepth->text() << "\t";
        CalibFileTextStream << ui->doubleSpinBoxL_RZDepth->text() << "\t";
        CalibFileTextStream << ui->doubleSpinBoxG_MPDepth->text() << "\n";

        CalibFileTextStream << ui->doubleSpinBoxS_Porosity->text() << "\t";
        CalibFileTextStream << ui->doubleSpinBoxS_Alpha->text() << "\t";
        CalibFileTextStream << ui->doubleSpinBoxS_Beta->text() << "\n";

        CalibFileTextStream << ui->doubleSpinBoxG_MPfracV->text() << "\t";
        CalibFileTextStream << ui->doubleSpinBoxG_MPfracH->text() << "\n";

        CalibFileTextStream << ui->doubleSpinBoxL_VegFrac->text() << "\t";
        CalibFileTextStream << ui->doubleSpinBoxL_Albedo->text() << "\t";
        CalibFileTextStream << ui->doubleSpinBoxL_Roughness->text() << "\n";

        CalibFileTextStream << ui->doubleSpinBoxF_Precip->text() << "\t";
        CalibFileTextStream << ui->doubleSpinBoxF_Temp->text() << "\n";

        CalibFileTextStream << ui->doubleSpinBoxF_ET0->text() << "\t";
        CalibFileTextStream << ui->doubleSpinBoxF_ET1->text() << "\t";
        CalibFileTextStream << ui->doubleSpinBoxF_ET2->text() << "\n";

        CalibFileTextStream << ui->doubleSpinBoxR_Rough->text() << "\t";
        CalibFileTextStream << ui->doubleSpinBoxR_KsatH->text() << "\t";
        CalibFileTextStream << ui->doubleSpinBoxR_KsatV->text() << "\t";
        CalibFileTextStream << ui->doubleSpinBoxR_BedTh->text() << "\n";

        CalibFileTextStream << ui->doubleSpinBoxR_Depth->text() << "\t";
        CalibFileTextStream << ui->doubleSpinBoxR_Width->text() << "\n";

        CalibFileTextStream << ui->doubleSpinBoxF_ISMax->text() << "\t";
        CalibFileTextStream << ui->doubleSpinBoxF_ThruFall->text() << "\t";
        CalibFileTextStream << ui->doubleSpinBoxF_MeltFac->text() << "\n";


        CalibFile.close();

    } catch (...) {
        qDebug() << "Error: CalibDataFile::calib_data_file() is returning w/o checking";
    }

    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Run Button Clicked Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CalibDataFile::on_pushButtonRun_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start CalibDataFile::on_pushButtonRun_clicked()";

    try {

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Clear Log
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Clear_Log();

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Does output already exist?
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QString calib_filename = ui->lineEditCalibDataFile->text();

        bool calibCheck = Check_Calib_Output(calib_filename, true);
        if(calibCheck)
        {
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check file access
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if ( ! CheckFileAccess(calib_filename, "WriteOnly") )
        {
            Log_Error_Message("No Write Access to " + calib_filename );
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Running Catchment Polygon
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        LogsString.append("Running Calib Data File ... <br>");
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

        int ErrorCalib = calib_data_file(calib_filename);

        if( ErrorCalib != 0 )
        {
            Log_Error_Message("Calib Data File Processing Failed "  );
            Log_Error_Message("Calib error code: " + QString::number(ErrorCalib) );
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update Project file
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QStringList ProjectIOStringList;

        ProjectIOStringList << "CalibDataFile" << ui->lineEditCalibDataFile->text();
        ProjectIOStringList << ui->doubleSpinBoxS_Alpha->text();
        ProjectIOStringList << ui->doubleSpinBoxS_Beta->text();
        ProjectIOStringList << ui->doubleSpinBoxS_Porosity->text();
        ProjectIOStringList << ui->doubleSpinBoxS_InfilDepth->text();
        ProjectIOStringList << ui->doubleSpinBoxS_KsatV->text();
        ProjectIOStringList << ui->doubleSpinBoxS_MPKsatV->text();

        ProjectIOStringList << ui->doubleSpinBoxG_KsatH->text();
        ProjectIOStringList << ui->doubleSpinBoxG_KsatV->text();
        ProjectIOStringList << ui->doubleSpinBoxG_MPKsatH->text();
        ProjectIOStringList << ui->doubleSpinBoxG_MPDepth->text();
        ProjectIOStringList << ui->doubleSpinBoxG_MPfracV->text();
        ProjectIOStringList << ui->doubleSpinBoxG_MPfracH->text();

        ProjectIOStringList << ui->doubleSpinBoxL_RZDepth->text();
        ProjectIOStringList << ui->doubleSpinBoxL_VegFrac->text();
        ProjectIOStringList << ui->doubleSpinBoxL_Albedo->text();
        ProjectIOStringList << ui->doubleSpinBoxL_Roughness->text();

        ProjectIOStringList << ui->doubleSpinBoxR_Rough->text();
        ProjectIOStringList << ui->doubleSpinBoxR_BedTh->text();
        ProjectIOStringList << ui->doubleSpinBoxR_KsatH->text();
        ProjectIOStringList << ui->doubleSpinBoxR_KsatV->text();
        ProjectIOStringList << ui->doubleSpinBoxR_Depth->text();
        ProjectIOStringList << ui->doubleSpinBoxR_Width->text();

        ProjectIOStringList << ui->doubleSpinBoxF_Precip->text();
        ProjectIOStringList << ui->doubleSpinBoxF_Temp->text();
        ProjectIOStringList << ui->doubleSpinBoxF_ET0->text();
        ProjectIOStringList << ui->doubleSpinBoxF_ET1->text();
        ProjectIOStringList << ui->doubleSpinBoxF_ET2->text();
        ProjectIOStringList << ui->doubleSpinBoxF_ISMax->text();
        ProjectIOStringList << ui->doubleSpinBoxF_ThruFall->text();
        ProjectIOStringList << ui->doubleSpinBoxF_MeltFac->text();

        WriteModuleLine(filename_open_project, ProjectIOStringList);
        ProjectIOStringList.clear();


        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update Message box
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Clear_Log();

        LogsString.append(tr("<br><b>Calib Data File Processing Complete.</b>")+tr("<br>"));
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

        ui->pushButtonRun->setDefault(false);
        ui->pushButtonClose->setDefault(true);
        ui->pushButtonClose->setFocus();


    } catch (...) {
        qDebug() << "Error: CalibDataFile::on_pushButtonRun_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Close button event
// TODO, Decide on keeping button next highlights or not
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CalibDataFile::on_pushButtonClose_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start CalibDataFile::on_pushButtonClose_clicked()";

    try {
        //QStringList default_params; default_params << "WORKFLOW5" << "FORC";
        //QMetaObject::invokeMethod(parent(),"set_defaults",Q_ARG(QStringList,default_params));
        close();
    } catch (...) {
        qDebug() << "Error: CalibDataFile::on_pushButtonClose_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Help button event
// TODO, Need cataract server back online
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CalibDataFile::on_pushButtonHelp_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start CalibDataFile::on_pushButtonHelp_clicked()";

    try {
        //        LogsString = tr("");
        //        if ( ! QDesktopServices::openUrl(QUrl("http://cataract.cee.psu.edu/PIHM/index.php/PIHMgis_3.0#calib_Data_File")) )
        //            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Load HTTP Link ... </span>")+tr("<br>"));
        //        ui->textBrowserLogs->setHtml(LogsString);
        //        ui->textBrowserLogs->repaint();
    } catch (...) {
        qDebug() << "Error: CalibDataFile::on_pushButtonHelp_clicked() is returning w/o checking";
    }
}
