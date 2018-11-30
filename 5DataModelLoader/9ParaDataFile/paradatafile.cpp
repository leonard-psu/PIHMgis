#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>

#include "paradatafile.h"
#include "ui_paradatafile.h"

#include "0LibsIO/IOProjectFile.h"
#include "globals.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ParaDataFile Constructor
// Parent is Main Window, filename is the open project text file used to store project details
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ParaDataFile::ParaDataFile(QWidget *parent, QString filename) :
    QDialog(parent),
    ui(new Ui::ParaDataFile)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ParaDataFile";

    try {

        ui->setupUi(this);

        filename_open_project = filename;
        bool found_file = false;

        QFile ProjectFile(filename_open_project);
        if ( ! ProjectFile.open(QIODevice::ReadOnly | QIODevice::Text) )
        {
            Log_Error_Message("Unable to Open File: </span>" + filename_open_project + tr("<br>"));
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
        qDebug() << "Error: SimplifyPolylines is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ParaDataFile Deconstructor
// Todo: Check for memory leaks
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ParaDataFile::~ParaDataFile()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ~ParaDataFile";

    try {
        delete ui;
    } catch (...) {
        qDebug() << "Error: ~ParaDataFile is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check Log_Error_Message
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ParaDataFile::Log_Error_Message(QString message)
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
bool ParaDataFile::Load_Project_Settings()
{
    if (print_debug_messages)
        qDebug() << "INFO: ParaDataFile::Load_Project_Settings()";

    try {

        //Data Model INPUT File Name
        QStringList ModuleStringList = ReadModuleLine(filename_open_project,tr("TINShapeLayer"));
        if ( ModuleStringList.length() > 0  )
        {
            QString TempFileName = ModuleStringList.at(3);
            TempFileName = TempFileName.right(TempFileName.length()-TempFileName.lastIndexOf("/")-1);

            TempFileName.replace( QString(".shp"), QString(".para") );
            QString output_filename = user_pihmgis_root_folder + "/4DataModelLoader/" + TempFileName;
            Check_Para_Output(output_filename,true);
        }

        ModuleStringList = ReadModuleLine(filename_open_project,tr("MeshDataFile"));
        if ( ModuleStringList.length() > 0  )
        {
            QString TempFileName = ModuleStringList.at(9);
            QString output_filename = user_pihmgis_root_folder + "/4DataModelLoader/" + TempFileName +".para";
            Check_Para_Output(output_filename,true);
        }

        ui->comboBoxStartStop->setCurrentIndex(2);
        ui->comboBoxOutput->setCurrentIndex(2);

        //End: Set Defaults


        //Start: Fill Form If Module Has Been Run Previously

        ModuleStringList = ReadModuleLine(filename_open_project,tr("ParaDataFile"));

        if ( ModuleStringList.length() > 0 )
        {
            Check_Para_Output(ModuleStringList.at(1),true);

            ui->comboBoxSurfaceMode->setCurrentIndex(ModuleStringList.at(2).toInt());
            ui->comboBoxSubsurfaceMode->setCurrentIndex(ModuleStringList.at(3).toInt());
            ui->comboBoxRiverMode->setCurrentIndex(ModuleStringList.at(4).toInt());
            ui->comboBoxInitMode->setCurrentIndex(ModuleStringList.at(5).toInt());
            ui->checkBoxVerboseMode->setChecked(ModuleStringList.at(6).toInt());
            ui->checkBoxDebugMode->setChecked(ModuleStringList.at(7).toInt());

            ui->radioButtonDirectDense->setChecked(ModuleStringList.at(8).toInt());
            ui->radioButtonIterative->setChecked(ModuleStringList.at(9).toInt());
            ui->comboBoxGrahmSchmidt->setCurrentIndex(ModuleStringList.at(10).toInt());
            ui->spinBoxKrylovDimension->setValue(ModuleStringList.at(11).toInt());
            ui->doubleSpinBoxConvergenceThreshold->setValue(ModuleStringList.at(12).toDouble());
            ui->doubleSpinBoxETStep->setValue(ModuleStringList.at(13).toDouble());
            ui->doubleSpinBoxInitialStep->setValue(ModuleStringList.at(14).toDouble());
            ui->doubleSpinBoxMaximumStep->setValue(ModuleStringList.at(15).toDouble());
            ui->doubleSpinBoxRelativeTolerance->setValue(ModuleStringList.at(16).toDouble());
            ui->doubleSpinBoxAbsoluteTolerance->setValue(ModuleStringList.at(17).toDouble());

            ui->spinBoxStartTime->setValue(ModuleStringList.at(18).toInt());
            ui->spinBoxStopTime->setValue(ModuleStringList.at(19).toInt());
            ui->comboBoxStartStop->setCurrentIndex(ModuleStringList.at(20).toInt());
            ui->comboBoxOutput->setCurrentIndex(ModuleStringList.at(21).toInt());

            ui->spinBoxRiver->setValue(ModuleStringList.at(22).toInt());
            ui->spinBoxRiverUpDown->setValue(ModuleStringList.at(23).toInt());
            ui->spinBoxRiverSurfaceLeftRight->setValue(ModuleStringList.at(24).toInt());
            ui->spinBoxRiverBaseLeftRight->setValue(ModuleStringList.at(25).toInt());
            ui->spinBoxRiverbed->setValue(ModuleStringList.at(26).toInt());
            ui->spinBoxRiverbedUpDown->setValue(ModuleStringList.at(27).toInt());
            ui->spinBoxRiverbedLeftRight->setValue(ModuleStringList.at(28).toInt());
            ui->spinBoxRivertoRiverBed->setValue(ModuleStringList.at(29).toInt());
            ui->spinBoxInterception->setValue(ModuleStringList.at(30).toInt());
            ui->spinBoxSnow->setValue(ModuleStringList.at(31).toInt());
            ui->spinBoxSurface->setValue(ModuleStringList.at(32).toInt());
            ui->spinBoxSoilMoisture->setValue(ModuleStringList.at(33).toInt());
            ui->spinBoxGroundwater->setValue(ModuleStringList.at(34).toInt());
            ui->spinBoxInfiltration->setValue(ModuleStringList.at(35).toInt());
            ui->spinBoxRecharge->setValue(ModuleStringList.at(36).toInt());
            ui->spinBoxCanopyEvaporation->setValue(ModuleStringList.at(37).toInt());
            ui->spinBoxTranspiration->setValue(ModuleStringList.at(38).toInt());
            ui->spinBoxGroundEvaporation->setValue(ModuleStringList.at(39).toInt());
        }
        //End: Fill Form If Module Has Been Run Previously


        ui->tabWidget->setCurrentIndex( 2 );

    } catch (...) {
        qDebug() << "Error: ParaDataFile::Load_Project_Settings is returning w/o checking";
        return false;
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to assist if Check_Para_Output OUTPUT file exists (returns true) or does not (returns false)
// Will color red and warning if exists with color_and_message_if_exists=true
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ParaDataFile::Check_Para_Output(QString file, bool color_and_message_if_exists){

    if(print_debug_messages)
        qDebug() << "INFO: Check_Para_Output()";

    bool result = false;

    try {

        if(  fileExists(file) )
        {
            if(color_and_message_if_exists)
            {
                Log_Error_Message(" Para output already exists: " + file +tr(" You may need to delete these files."));
            }

            ui->lineEditParaDataFile->setStyleSheet("color: red;");
            ui->lineEditParaDataFile->setText(file);
            result = true;
        }
        else
        {
            ui->lineEditParaDataFile->setStyleSheet("color: black;");
            ui->lineEditParaDataFile->setText(file);

            result = false;
        }

    } catch (...) {
        qDebug() << "Error: ParaDataFile::Check_Para_Output is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to clear message log
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ParaDataFile::Clear_Log()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ParaDataFile::Clear_Log()";

    try {

        LogsString = tr("");
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

    } catch (...) {
        qDebug() << "Error: ParaDataFile::Clear_Log() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to focus button selection (needed for users w/o mouse)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ParaDataFile::pushButtonSetFocus()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ParaDataFile::pushButtonSetFocus()";

    try {
        ui->pushButtonParaDataFile->setDefault(false);

        if (ui->lineEditParaDataFile->text() == nullptr)
        {
            ui->pushButtonParaDataFile->setDefault(true);
            ui->pushButtonParaDataFile->setFocus();
            return;
        }

        ui->pushButtonRun->setDefault(true);
        ui->pushButtonRun->setFocus();

    } catch (...) {
        qDebug() << "Error:ParaDataFile::pushButtonSetFocus()e is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button TINShapeLayer Clicked Event (OUTPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ParaDataFile::on_pushButtonParaDataFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ParaDataFile::on_pushButtonParaDataFile_clicked()";

    try {

        Clear_Log();

        QString ParaDataFileName = QFileDialog::getSaveFileName(this, "Choose Para Data File Name", user_pihmgis_root_folder+"/4DataModelLoader","Para Data File(*.para)");
        QString tempString = ParaDataFileName;
        if ( ParaDataFileName != nullptr)
        {
            if( ! (tempString.toLower()).endsWith(".para") )
            {
                tempString.append(".para");
                ParaDataFileName = tempString;
            }
            Check_Para_Output(ParaDataFileName, true);

            pushButtonSetFocus();
        }
    } catch (...) {
        qDebug() << "Error:ParaDataFile::on_pushButtonParaDataFile_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to create Para file
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ParaDataFile::para_data_file(QString filename)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ParaDataFile::para_data_file()";

    try {

        QFile ParaFile( filename);
        if ( ! ParaFile.open(QIODevice::WriteOnly | QIODevice::Text) )
            return 129;
        QTextStream ParaFileTextStream(&ParaFile);

        //Verbose
        if ( ui->checkBoxVerboseMode->isChecked() )
            ParaFileTextStream << "1\t";
        else
            ParaFileTextStream << "0\t";

        //Debug
        if ( ui->checkBoxDebugMode->isChecked() )
            ParaFileTextStream << "1\t";
        else
            ParaFileTextStream << "0\t";

        //Init Mode
        ParaFileTextStream << ui->comboBoxInitMode->currentIndex() + 1 << "\n";

        //Print Variables

        ( ui->spinBoxGroundwater->text().toInt() > 0 )              ? ( ParaFileTextStream << "1\t" ) : ( ParaFileTextStream << "0\t" );
        ( ui->spinBoxSurface->text().toInt() > 0 )                  ? ( ParaFileTextStream << "1\t" ) : ( ParaFileTextStream << "0\t" );
        ( ui->spinBoxSnow->text().toInt() > 0 )                     ? ( ParaFileTextStream << "1\t" ) : ( ParaFileTextStream << "0\t" );
        ( ui->spinBoxRiver->text().toInt() > 0 )                    ? ( ParaFileTextStream << "1\n" ) : ( ParaFileTextStream << "0\n" );

        ( ui->spinBoxRecharge->text().toInt() > 0 )                 ? ( ParaFileTextStream << "1\t" ) : ( ParaFileTextStream << "0\t" );
        ( ui->spinBoxInterception->text().toInt() > 0 )             ? ( ParaFileTextStream << "1\t" ) : ( ParaFileTextStream << "0\t" );
        ( ui->spinBoxSoilMoisture->text().toInt() > 0 )             ? ( ParaFileTextStream << "1\n" ) : ( ParaFileTextStream << "0\n" );

        ( ui->spinBoxCanopyEvaporation->text().toInt() > 0 )        ? ( ParaFileTextStream << "1\t" ) : ( ParaFileTextStream << "0\t" );
        ( ui->spinBoxTranspiration->text().toInt() > 0 )            ? ( ParaFileTextStream << "1\t" ) : ( ParaFileTextStream << "0\t" );
        ( ui->spinBoxGroundEvaporation->text().toInt() > 0 )        ? ( ParaFileTextStream << "1\n" ) : ( ParaFileTextStream << "0\n" );

        ( ui->spinBoxRiverUpDown->text().toInt() > 0 )              ? ( ParaFileTextStream << "1\t" ) : ( ParaFileTextStream << "0\t" );
        ( ui->spinBoxRiverUpDown->text().toInt() > 0 )              ? ( ParaFileTextStream << "1\t" ) : ( ParaFileTextStream << "0\t" );
        ( ui->spinBoxRiverSurfaceLeftRight->text().toInt() > 0 )    ? ( ParaFileTextStream << "1\t" ) : ( ParaFileTextStream << "0\t" );
        ( ui->spinBoxRiverSurfaceLeftRight->text().toInt() > 0 )    ? ( ParaFileTextStream << "1\t" ) : ( ParaFileTextStream << "0\t" );
        ( ui->spinBoxRiverBaseLeftRight->text().toInt() > 0 )       ? ( ParaFileTextStream << "1\t" ) : ( ParaFileTextStream << "0\t" );
        ( ui->spinBoxRiverBaseLeftRight->text().toInt() > 0 )       ? ( ParaFileTextStream << "1\t" ) : ( ParaFileTextStream << "0\t" );
        ( ui->spinBoxRiverbedLeftRight->text().toInt() > 0 )        ? ( ParaFileTextStream << "1\t" ) : ( ParaFileTextStream << "0\t" );
        ( ui->spinBoxRiverbedLeftRight->text().toInt() > 0 )        ? ( ParaFileTextStream << "1\t" ) : ( ParaFileTextStream << "0\t" );
        ( ui->spinBoxRiverbedUpDown->text().toInt() > 0 )           ? ( ParaFileTextStream << "1\t" ) : ( ParaFileTextStream << "0\t" );
        ( ui->spinBoxRiverbedUpDown->text().toInt() > 0 )           ? ( ParaFileTextStream << "1\t" ) : ( ParaFileTextStream << "0\t" );
        ( ui->spinBoxRivertoRiverBed->text().toInt() > 0 )          ? ( ParaFileTextStream << "1\n" ) : ( ParaFileTextStream << "0\n" );

        //Print Variable Intervals

        int factor = 1, I_temp = 1;
        if ( ui->comboBoxOutput->currentIndex() + 1 == 1 ) factor = 1;
        if ( ui->comboBoxOutput->currentIndex() + 1 == 2 ) factor = 60;
        if ( ui->comboBoxOutput->currentIndex() + 1 == 3 ) factor = 24*60;
        if ( ui->comboBoxOutput->currentIndex() + 1 == 4 ) factor = 24*60*7;
        if ( ui->comboBoxOutput->currentIndex() + 1 == 5 ) factor = 24*60*30;
        if ( ui->comboBoxOutput->currentIndex() + 1 == 6 ) factor = 24*60*365;

        ParaFileTextStream << ui->spinBoxGroundwater->text().toInt() * factor   << "\t";
        ParaFileTextStream << ui->spinBoxSurface->text().toInt() * factor       << "\t";
        ParaFileTextStream << ui->spinBoxSnow->text().toInt() * factor          << "\t";
        ParaFileTextStream << ui->spinBoxRiver->text().toInt() * factor         << "\n";

        ParaFileTextStream << ui->spinBoxRecharge->text().toInt() * factor      << "\t";
        ParaFileTextStream << ui->spinBoxInterception->text().toInt() * factor  << "\t";
        ParaFileTextStream << ui->spinBoxSoilMoisture->text().toInt() * factor  << "\t";
        I_temp = 99999999;
        if ( ui->spinBoxCanopyEvaporation->text().toInt() > 0   && ui->spinBoxCanopyEvaporation->text().toInt() * factor < I_temp ) I_temp = ui->spinBoxCanopyEvaporation->text().toInt() * factor;
        if ( ui->spinBoxTranspiration->text().toInt() > 0       && ui->spinBoxTranspiration->text().toInt() * factor < I_temp )     I_temp = ui->spinBoxTranspiration->text().toInt() * factor;
        if ( ui->spinBoxGroundEvaporation->text().toInt() > 0   && ui->spinBoxGroundEvaporation->text().toInt() * factor < I_temp ) I_temp = ui->spinBoxGroundEvaporation->text().toInt() * factor;
        ParaFileTextStream << I_temp << "\t";
        I_temp = 99999999;
        if ( ui->spinBoxRiverUpDown->text().toInt() > 0   && ui->spinBoxRiverUpDown->text().toInt() * factor < I_temp ) I_temp = ui->spinBoxRiverUpDown->text().toInt() * factor;
        if ( ui->spinBoxRiverSurfaceLeftRight->text().toInt() > 0   && ui->spinBoxRiverSurfaceLeftRight->text().toInt() * factor < I_temp ) I_temp = ui->spinBoxRiverSurfaceLeftRight->text().toInt() * factor;
        if ( ui->spinBoxRiverBaseLeftRight->text().toInt() > 0   && ui->spinBoxRiverBaseLeftRight->text().toInt() * factor < I_temp ) I_temp = ui->spinBoxRiverBaseLeftRight->text().toInt() * factor;
        if ( ui->spinBoxRiverbedLeftRight->text().toInt() > 0   && ui->spinBoxRiverbedLeftRight->text().toInt() * factor < I_temp ) I_temp = ui->spinBoxRiverbedLeftRight->text().toInt() * factor;
        if ( ui->spinBoxRiverbedUpDown->text().toInt() > 0   && ui->spinBoxRiverbedUpDown->text().toInt() * factor < I_temp ) I_temp = ui->spinBoxRiverbedUpDown->text().toInt() * factor;
        if ( ui->spinBoxRivertoRiverBed->text().toInt() > 0   && ui->spinBoxRivertoRiverBed->text().toInt() * factor < I_temp ) I_temp = ui->spinBoxRivertoRiverBed->text().toInt() * factor;
        ParaFileTextStream << I_temp << "\n";

        ParaFileTextStream << ui->comboBoxSurfaceMode->currentIndex() + 1 << "\t";
        ParaFileTextStream << ui->comboBoxSubsurfaceMode->currentIndex() + 1 << "\t";
        ParaFileTextStream << ui->comboBoxRiverMode->currentIndex() + 1 << "\n";

        if ( ui->radioButtonDirectDense->isChecked() )  ParaFileTextStream << "1\t";
        if ( ui->radioButtonIterative->isChecked() )    ParaFileTextStream << "2\t";
        ParaFileTextStream << ui->comboBoxGrahmSchmidt->currentIndex() + 1 << "\t";
        ParaFileTextStream << ui->spinBoxKrylovDimension->text().toInt() << "\t";
        ParaFileTextStream << ui->doubleSpinBoxConvergenceThreshold->text().toDouble() << "\n";

        ParaFileTextStream << ui->doubleSpinBoxAbsoluteTolerance->text().toDouble() << "\t";
        ParaFileTextStream << ui->doubleSpinBoxRelativeTolerance->text().toDouble() << "\t";
        ParaFileTextStream << ui->doubleSpinBoxInitialStep->text().toDouble() << "\t";
        ParaFileTextStream << ui->doubleSpinBoxMaximumStep->text().toDouble() << "\t";
        ParaFileTextStream << ui->doubleSpinBoxETStep->text().toDouble() << "\n";


        if ( ui->comboBoxStartStop->currentIndex() + 1 == 1 ) factor = 1;
        if ( ui->comboBoxStartStop->currentIndex() + 1 == 2 ) factor = 60;
        if ( ui->comboBoxStartStop->currentIndex() + 1 == 3 ) factor = 60*24;
        if ( ui->comboBoxStartStop->currentIndex() + 1 == 4 ) factor = 60*24*7;
        if ( ui->comboBoxStartStop->currentIndex() + 1 == 5 ) factor = 60*24*30;
        if ( ui->comboBoxStartStop->currentIndex() + 1 == 6 ) factor = 60*24*365;

        ParaFileTextStream << ui->spinBoxStartTime->text().toInt() * factor << "\t";
        ParaFileTextStream << ui->spinBoxStopTime->text().toInt() * factor << "\t";
        ParaFileTextStream << "0\n";

        ParaFileTextStream << "1\t";
        ParaFileTextStream << "1\n";

        ParaFile.close();

    } catch (...) {
        qDebug() << "Error:ParaDataFile::para_data_file() is returning w/o checking";
        return 500;
    }

    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Run Button Clicked Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ParaDataFile::on_pushButtonRun_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ParaDataFile::on_pushButtonRun_clicked()";

    try {

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Clear Log
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Clear_Log();

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check Outputs
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QString output_filename = ui->lineEditParaDataFile->text();

        bool output_check = Check_Para_Output(output_filename, true);
        if(output_check)
        {
            return;
        }

        if ( ! CheckFileAccess(output_filename, "WriteOnly") )
        {
            Log_Error_Message(" No Write Access to " + output_filename );
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Running Mesh Data File
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        LogsString.append("Running Para Data File ... <br>");
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

        int ErrorPara = para_data_file(output_filename);

        if( ErrorPara != 0 )
        {
            Log_Error_Message("Para Data File Processing Failed " );
            Log_Error_Message("Para error return code " + QString::number(ErrorPara) );
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update Project file
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QStringList ProjectIOStringList;

        ProjectIOStringList << "ParaDataFile" << ui->lineEditParaDataFile->text();

        ProjectIOStringList << QString::number(ui->comboBoxSurfaceMode->currentIndex());
        ProjectIOStringList << QString::number(ui->comboBoxSubsurfaceMode->currentIndex());
        ProjectIOStringList << QString::number(ui->comboBoxRiverMode->currentIndex());
        ProjectIOStringList << QString::number(ui->comboBoxInitMode->currentIndex());
        ProjectIOStringList << QString::number(ui->checkBoxVerboseMode->isChecked());
        ProjectIOStringList << QString::number(ui->checkBoxDebugMode->isChecked());

        ProjectIOStringList << QString::number(ui->radioButtonDirectDense->isChecked());
        ProjectIOStringList << QString::number(ui->radioButtonIterative->isChecked());
        ProjectIOStringList << QString::number(ui->comboBoxGrahmSchmidt->currentIndex());
        ProjectIOStringList << ui->spinBoxKrylovDimension->text();
        ProjectIOStringList << ui->doubleSpinBoxConvergenceThreshold->text();
        ProjectIOStringList << ui->doubleSpinBoxETStep->text();
        ProjectIOStringList << ui->doubleSpinBoxInitialStep->text();
        ProjectIOStringList << ui->doubleSpinBoxMaximumStep->text();
        ProjectIOStringList << ui->doubleSpinBoxRelativeTolerance->text();
        ProjectIOStringList << ui->doubleSpinBoxAbsoluteTolerance->text();

        ProjectIOStringList << ui->spinBoxStartTime->text();
        ProjectIOStringList << ui->spinBoxStopTime->text();
        ProjectIOStringList << QString::number(ui->comboBoxStartStop->currentIndex());
        ProjectIOStringList << QString::number(ui->comboBoxOutput->currentIndex());
        ProjectIOStringList << ui->spinBoxRiver->text();
        ProjectIOStringList << ui->spinBoxRiverUpDown->text();
        ProjectIOStringList << ui->spinBoxRiverSurfaceLeftRight->text();
        ProjectIOStringList << ui->spinBoxRiverBaseLeftRight->text();
        ProjectIOStringList << ui->spinBoxRiverbed->text();
        ProjectIOStringList << ui->spinBoxRiverbedUpDown->text();
        ProjectIOStringList << ui->spinBoxRiverbedLeftRight->text();
        ProjectIOStringList << ui->spinBoxRivertoRiverBed->text();
        ProjectIOStringList << ui->spinBoxInterception->text();
        ProjectIOStringList << ui->spinBoxSnow->text();
        ProjectIOStringList << ui->spinBoxSurface->text();
        ProjectIOStringList << ui->spinBoxSoilMoisture->text();
        ProjectIOStringList << ui->spinBoxGroundwater->text();
        ProjectIOStringList << ui->spinBoxInfiltration->text();
        ProjectIOStringList << ui->spinBoxRecharge->text();
        ProjectIOStringList << ui->spinBoxCanopyEvaporation->text();
        ProjectIOStringList << ui->spinBoxTranspiration->text();
        ProjectIOStringList << ui->spinBoxGroundEvaporation->text();

        WriteModuleLine(filename_open_project, ProjectIOStringList);
        ProjectIOStringList.clear();

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update Message box
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Clear_Log();

        LogsString.append(tr("<br><b>Para Data File Processing Complete.</b>")+tr("<br>"));
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

        ui->pushButtonRun->setDefault(false);
        ui->pushButtonClose->setDefault(true);
        ui->pushButtonClose->setFocus();


    } catch (...) {
        qDebug() << "Error:ParaDataFile::on_pushButtonRun_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Help button event
// TODO, Need cataract server back online
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ParaDataFile::on_pushButtonClose_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ParaDataFile::on_pushButtonClose_clicked()";

    try {
        //QStringList default_params; default_params << "WORKFLOW5" << "CALI";
        //QMetaObject::invokeMethod(parent(),"set_defaults",Q_ARG(QStringList,default_params));
        close();
    } catch (...) {
        qDebug() << "Error:ParaDataFile::on_pushButtonClose_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Help button event
// TODO, Need cataract server back online
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ParaDataFile::on_pushButtonHelp_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ParaDataFile::on_pushButtonHelp_clicked()";

    try {
        //        LogsString = tr("");
        //        if ( ! QDesktopServices::openUrl(QUrl("http://cataract.cee.psu.edu/PIHM/index.php/PIHMgis_3.0#para_Data_File")) )
        //            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Load HTTP Link ... </span>")+tr("<br>"));
        //        ui->textBrowserLogs->setHtml(LogsString);
        //        ui->textBrowserLogs->repaint();
    } catch (...) {
        qDebug() << "Error:ParaDataFile::on_pushButtonHelp_clicked() is returning w/o checking";
    }
}
