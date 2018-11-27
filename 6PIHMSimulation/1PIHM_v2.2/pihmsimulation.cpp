#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>
#include <QDir>
#include <QtConcurrentRun>
#include <QFuture>
#include <QFutureWatcher>
#include <QProgressDialog>
#include <qtconcurrentmap.h>

#include "pihmsimulation.h"
#include "ui_pihmsimulation.h"

#include "0LibsIO/IOProjectFile.h"
#include "globals.h"

#include "6PIHMSimulation/PIHMThread/user_def.h"
#include "6PIHMSimulation/PIHMThread/MyThread.h"

Q_DECLARE_METATYPE(std::string)

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PIHMSimulation Constructor
// Parent is Main Window, filename is the open project text file used to store project details
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PIHMSimulation::PIHMSimulation(QWidget *parent, QString filename) :
    QDialog(parent),
    ui(new Ui::PIHMSimulation)
{

    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMSimulation";

    try {

        ui->setupUi(this);
        filename_open_project = filename;
        bool found_file = false;
        pihm_running = false;

        ui->progressBar->setValue(0);

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
        qDebug() << "Error: PIHMSimulation is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PIHMSimulation Deconstructor
// Todo: Check for memory leaks
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PIHMSimulation::~PIHMSimulation()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ~PIHMSimulation";

    try {

        if(mThread)
        {
            mThread->quit();
            mThread->wait();
        }

        delete ui;

    } catch (...) {
        qDebug() << "Error: ~PIHMSimulation is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Load_Project_Settings
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PIHMSimulation::Load_Project_Settings()
{
    if (print_debug_messages)
        qDebug() << "INFO: MeshDataFile::Load_Project_Settings()";

    try {

        Check_InputDataFolder(user_pihmgis_root_folder+"/4DataModelLoader");

        QStringList ModuleStringList = ReadModuleLine(filename_open_project,tr("TINShapeLayer"));
        if ( ModuleStringList.length() > 0  )
        {
            QString TempFileName = ModuleStringList.at(3);
            TempFileName = TempFileName.right(TempFileName.length()-TempFileName.lastIndexOf("/")-1);
            TempFileName.replace( QString(".shp"), QString("") );
            Check_DataKey(TempFileName);
        }

        ModuleStringList = ReadModuleLine(filename_open_project,tr("MeshDataFile"));
        if ( ModuleStringList.length() > 0  )
        {
            QString TempFileName = ModuleStringList.at(9);
            Check_DataKey(TempFileName);
        }

        //Start: Fill Form If Module Has Been Run Previously
        ModuleStringList = ReadModuleLine(filename_open_project,tr("PIHMSimulation"));

        if ( ModuleStringList.length() > 0 )
        {
            Check_InputDataFolder(ModuleStringList.at(1));
            Check_DataKey(ModuleStringList.at(2));
        }

        ui->pushButtonRun->setText("Run");
        pushButtonSetFocus();

    } catch (...) {
        qDebug() << "Error: MeshDataFile::Load_Project_Settings is returning w/o checking";
        return false;
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to clear message log
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMSimulation::Clear_Log()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMSimulation::Clear_Log()";

    try {

        LogsString = tr("");
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

    } catch (...) {
        qDebug() << "Error: PIHMSimulation::Clear_Log() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check Log_Error_Message
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMSimulation::Log_Warning_Message(QString message)
{
    try {
        LogsString.append(tr("<span style=\"color:#FF0000\">Warning: ") + message + " </span>")+tr("<br>");
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();
    } catch (...) {
        qDebug() << "Error: Log_Error_Message is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check Log_Error_Message
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMSimulation::Log_Error_Message(QString message)
{
    try {
        LogsString.append(tr("<span style=\"color:#FF0000\">Error: ") + message + " </span>")+tr("<br>");
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();
    } catch (...) {
        qDebug() << "Error: Log_Error_Message is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Check InputDataFolder File exists (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PIHMSimulation::Check_InputDataFolder(QString folder){

    if(print_debug_messages)
        qDebug() << "INFO: Check_InputDataFolder()";

    bool result = false;

    try {

        QDir check_dir(folder);

        if(  check_dir.exists() )
        {
            ui->lineEditInputDataFolder->setStyleSheet("color: black;");
            ui->lineEditInputDataFolder->setText(folder);
            result = true;
        }
        else
        {
            ui->lineEditInputDataFolder->setStyleSheet("color: red;");
            ui->lineEditInputDataFolder->setText(folder);

            result = false;
        }

    } catch (...) {
        qDebug() << "Error: Check_InputDataFolder is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Check_DataKey Value exists (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PIHMSimulation::Check_DataKey(QString value){

    if(print_debug_messages)
        qDebug() << "INFO: Check_DataKey()";

    bool result = false;

    try {

        if(value.isNull() || value.isEmpty() )
        {
            ui->lineEditDataKey->setStyleSheet("color: red;");
            ui->lineEditDataKey->setText("Missing");
            result = false;
        }
        else if(value == QString("Missing"))
        {
            result = false;
        }
        else
        {
            ui->lineEditDataKey->setText(value);
            result = true;
        }

    } catch (...) {
        qDebug() << "Error: Check_DataKey is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button InputDataFolder Clicked Event (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMSimulation::on_pushButtonInputDataFolder_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMSimulation::on_pushButtonInputDataFolder_clicked()";

    try {

        Clear_Log();

        QString InputDataFolder = QFileDialog::getExistingDirectory(this, "PIHM Input Data Folder", user_pihmgis_root_folder+"/4DataModelLoader", 0);

        if( InputDataFolder != nullptr )
        {
            Check_InputDataFolder(InputDataFolder);
            pushButtonSetFocus();
        }

    } catch (...) {
        qDebug() << "Error: PIHMSimulation::on_pushButtonInputDataFolder_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to focus button selection (needed for users w/o mouse)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMSimulation::pushButtonSetFocus()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMSimulation::pushButtonSetFocus()";

    try {
        ui->pushButtonInputDataFolder->setDefault(false);

        if (ui->lineEditInputDataFolder->text() == nullptr)
        {
            ui->pushButtonInputDataFolder->setDefault(true);
            ui->pushButtonInputDataFolder->setFocus();
            return;
        }

        if (ui->lineEditDataKey->text() == nullptr)
        {
            ui->lineEditDataKey->setFocus();
            return;
        }

        ui->pushButtonRun->setDefault(true);
        ui->pushButtonRun->setFocus();

    } catch (...) {
        qDebug() << "Error: PIHMSimulation::pushButtonSetFocus() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check file contents exist for PIHM project
// Note depenency on using project folder and name. Meaning, users cannot mix and match.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PIHMSimulation::Check_PIHM_Project_Inputs(QString base_folder, QString project_name, bool return_on_error)
{
    if(print_debug_messages)
        qDebug() << "INFO: Check_PIHM_Project_Inputs()";

    bool result = false;

    try {
        if ( this->ModelVersion == "PIHM v2.2")
        {
            if(return_on_error)
            {
                if ( CheckInputFileAccess(base_folder,project_name, tr(".mesh"), true)  != 0 ) return 2201;
                if ( CheckInputFileAccess(base_folder,project_name, tr(".att"), true)   != 0 ) return 2202;
                if ( CheckInputFileAccess(base_folder,project_name, tr(".riv"), true)   != 0 ) return 2203;
                if ( CheckInputFileAccess(base_folder,project_name, tr(".soil"), true)  != 0 ) return 2204;
                if ( CheckInputFileAccess(base_folder,project_name, tr(".geol"), true)  != 0 ) return 2205;
                if ( CheckInputFileAccess(base_folder,project_name, tr(".lc"), true)    != 0 ) return 2206;
                if ( CheckInputFileAccess(base_folder,project_name, tr(".init"), true)  != 0 ) return 2207;
                if ( CheckInputFileAccess(base_folder,project_name, tr(".ibc"), true)   != 0 ) return 2208;
                if ( CheckInputFileAccess(base_folder,project_name, tr(".para"), true)  != 0 ) return 2209;
                if ( CheckInputFileAccess(base_folder,project_name, tr(".calib"), true) != 0 ) return 2210;
                if ( CheckInputFileAccess(base_folder,project_name, tr(".forc"), true)  != 0 ) return 2211;

                result = true;
            }
            else
            {
                bool error_found = false;
                if ( CheckInputFileAccess(base_folder,project_name, tr(".mesh"), true)  != 0 ) error_found = true;
                if ( CheckInputFileAccess(base_folder,project_name, tr(".att"), true)   != 0 ) error_found = true;
                if ( CheckInputFileAccess(base_folder,project_name, tr(".riv"), true)   != 0 ) error_found = true;
                if ( CheckInputFileAccess(base_folder,project_name, tr(".soil"), true)  != 0 ) error_found = true;
                if ( CheckInputFileAccess(base_folder,project_name, tr(".geol"), true)  != 0 ) error_found = true;
                if ( CheckInputFileAccess(base_folder,project_name, tr(".lc"), true)    != 0 ) error_found = true;
                if ( CheckInputFileAccess(base_folder,project_name, tr(".init"), true)  != 0 ) error_found = true;
                if ( CheckInputFileAccess(base_folder,project_name, tr(".ibc"), true)   != 0 ) error_found = true;
                if ( CheckInputFileAccess(base_folder,project_name, tr(".para"), true)  != 0 ) error_found = true;
                if ( CheckInputFileAccess(base_folder,project_name, tr(".calib"), true) != 0 ) error_found = true;
                if ( CheckInputFileAccess(base_folder,project_name, tr(".forc"), true)  != 0 ) error_found = true;

                result = error_found;
            }
        }
        else
        {
            Log_Warning_Message("PIHM Version Not Supported " + tr("<br>"));
            result = false;
        }


    } catch (...) {
        qDebug() << "Error: Check_PIHM_Project_Inputs is returning w/o checking";
        result = false;
    }

    return result;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check file access
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PIHMSimulation::CheckInputFileAccess(QString folder, QString project_name, QString Extension, bool message)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMSimulation::CheckInputFileAccess()";

    try {
        QString FileNamewithExtension = folder + "/" + project_name + Extension;

        if ( ! CheckFileAccess(FileNamewithExtension, "ReadOnly") )
        {
            Log_Error_Message("No Read Access to " + FileNamewithExtension +tr("<br>"));
            return -9;
        }

        if(message)
        {
            LogsString.append(FileNamewithExtension + " ... <br>");
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
        }

    } catch (...) {
        qDebug() << "Error: PIHMSimulation::CheckInputFileAccess() is returning w/o checking";
        return -10;
    }
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Copy PIHM Input file to PIHM output folder
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PIHMSimulation::CopyInputFile( QString output_folder, QString input_folder, QString project_name, QString file_extension, bool delete_existing_output_file )
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMSimulation::CopyInputFile()";

    try {

        QString input_FileName = input_folder + "/" + project_name + file_extension;
        QString output_FileName = output_folder + "/" + project_name + file_extension;

        if( QFile(output_FileName).exists() )
        {
            if(delete_existing_output_file)
            {
                if ( ! QFile::remove(output_FileName) )
                {
                    Log_Error_Message("Unable to remove file " + output_FileName + tr("<br>"));
                    ui->textBrowserLogs->setHtml(LogsString);
                    ui->textBrowserLogs->repaint();
                    return -9;
                }
            }
            else {
                Log_Warning_Message("Not overwriting Input file that already exists in Output folder location. " + output_FileName + tr("<br>"));
                return -10;
            }
        }

        if ( ! QFile::copy(input_FileName, output_FileName) )
        {
            Log_Error_Message("Unable to copy file " + input_FileName + tr("<br>"));
            return -11;
        }

    } catch (...) {
        qDebug() << "Error: PIHMSimulation::CopyInputFile() is returning w/o checking";
        return -12;
    }
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Copy PIHM Input files to PIHM output folder
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PIHMSimulation::CopyInputFiles( QString output_folder, QString input_folder, QString project_name, bool delete_existing_output_file )
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMSimulation::CopyInputFiles()";

    bool result = false;

    try {

        if ( this->ModelVersion == "PIHM v2.2")
        {

            result = true;

            if ( CopyInputFile(output_folder,input_folder, project_name,tr(".mesh"),delete_existing_output_file) != 0 )
            {
                Log_Error_Message("Unable to copy file mesh file<br>");
                result = false;
            }
            if ( CopyInputFile(output_folder,input_folder, project_name,tr(".att"),delete_existing_output_file) != 0 )
            {
                Log_Error_Message("Unable to copy file att file<br>");
                result = false;
            }
            if ( CopyInputFile(output_folder,input_folder, project_name,tr(".riv"),delete_existing_output_file) != 0 )
            {
                Log_Error_Message("Unable to copy file riv file<br>");
                result = false;
            }

            if ( CopyInputFile(output_folder,input_folder, project_name,tr(".soil"),delete_existing_output_file) != 0 )
            {
                Log_Error_Message("Unable to copy file soil file<br>");
                result = false;
            }
            if ( CopyInputFile(output_folder,input_folder, project_name,tr(".geol"),delete_existing_output_file) != 0 )
            {
                Log_Error_Message("Unable to copy file geol file<br>");
                result = false;
            }
            if ( CopyInputFile(output_folder,input_folder, project_name,tr(".lc"),delete_existing_output_file) != 0 )
            {
                Log_Error_Message("Unable to copy file lc file<br>");
                result = false;
            }

            if ( CopyInputFile(output_folder,input_folder, project_name,tr(".init"),delete_existing_output_file) != 0 )
            {
                Log_Error_Message("Unable to copy file init file<br>");
                result = false;
            }

            if ( CopyInputFile(output_folder,input_folder, project_name,tr(".ibc"),delete_existing_output_file) != 0 )
            {
                Log_Error_Message("Unable to copy file ibc file<br>");
                result = false;
            }

            if ( CopyInputFile(output_folder,input_folder, project_name,tr(".para"),delete_existing_output_file) != 0 )
            {
                Log_Error_Message("Unable to copy file para file<br>");
                result = false;
            }

            if ( CopyInputFile(output_folder,input_folder, project_name,tr(".calib"),delete_existing_output_file) != 0 )
            {
                Log_Error_Message("Unable to copy file calib file<br>");
                result = false;
            }

            if ( CopyInputFile(output_folder,input_folder, project_name,tr(".forc"),delete_existing_output_file) != 0 )
            {
                Log_Error_Message("Unable to copy file forc file<br>");
                result = false;
            }

        }
        else
        {
            Log_Error_Message("PIHM Version Not Supported "+tr("<br>"));
            result = false;
        }

    } catch (...) {
        qDebug() << "Error: PIHMSimulation::CopyInputFiles() is returning w/o checking";
        result = false;
    }
    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Run Button Clicked Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMSimulation::on_pushButtonRun_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMSimulation::on_pushButtonRun_clicked()";

    try {

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Clear Log
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Clear_Log();
        ui->progressBar->setValue(0);

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Get Input Values
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QString input_folder  = ui->lineEditInputDataFolder->text();
        QString project_name  = ui->lineEditDataKey->text();
        bool delete_existing_output_file = ui->checkBoxOverWriteFiles->isChecked();

        bool checked_input = Check_InputDataFolder(input_folder);
        if(!checked_input)
        {
            Log_Error_Message("Invalid Project Input Folder or Value Missing" + input_folder );
            return;
        }
        checked_input = Check_DataKey(project_name);
        if(!checked_input)
        {
            Log_Error_Message("Invalid Project Name or Value Missing " + project_name );
            return;
        }

        checked_input = Check_PIHM_Project_Inputs(input_folder, project_name, true);
        if(!checked_input)
        {
            Log_Error_Message("Missing input file(s) for project: " + project_name );
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check Output Location
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QString output_folder = user_pihmgis_root_folder + "/5PIHMSimulation";
        if (!QDir(output_folder).exists() )
        {
            Log_Error_Message("Project output folder is missing: " + output_folder );
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Copy input files to Output Location
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        bool checked_output = CopyInputFiles(output_folder, input_folder, project_name, delete_existing_output_file);
        if(!checked_output)
        {
            Log_Error_Message("Issues with copying input file(s) to output folder: " + output_folder );
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Running Simulation
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        LogsString = tr("");
        LogsString.append(tr("PIHM Simulation Processing ... <br>"));
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update Project file
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QStringList ProjectIOStringList;

        ProjectIOStringList << "PIHMSimulation" << input_folder;
        ProjectIOStringList << project_name;
        ProjectIOStringList << QString::number(false); //TODO Update project expectations sometime later
        ProjectIOStringList << output_folder;
        WriteModuleLine(filename_open_project, ProjectIOStringList);
        ProjectIOStringList.clear();


        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Starting PIHM thread
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        this->setCursor(Qt::WaitCursor);
        ui->pushButton_Stop->setEnabled(true);
        QString input_folder2  = ui->lineEditInputDataFolder->text();
        QString project_name2  = ui->lineEditDataKey->text();
        QString output_folder2 = user_pihmgis_root_folder + "/5PIHMSimulation";

        mThread = new MyThread(this);
        mThread->set_Output_Folder(output_folder2);
        mThread->set_Project_Name(project_name2);

        qRegisterMetaType<std::string>("std::string");
        connect(mThread, SIGNAL(onPIHM_Finished(bool)), this, SLOT(onPIHM_Finished(bool)));
        connect(mThread, SIGNAL(onPIHM_Failed()), this, SLOT(onPIHM_Failed()));
        connect(mThread, SIGNAL(onPIHM_StatusChanged(std::string)), this, SLOT(onPIHM_StatusChanged(std::string)));
        connect(mThread, SIGNAL(valueChanged(int)), this, SLOT(onValueChanged(int)));
        pihm_running = true;
        mThread->start();

        return;

    } catch (...) {
        this->setCursor(Qt::ArrowCursor);
        qDebug() << "Error: PIHMSimulation::on_pushButtonRun_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Close button event
// TODO, Need cataract server back online
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMSimulation::on_pushButtonClose_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMSimulation::on_pushButtonClose_clicked()";

    try {

        if(pihm_running)
        {
            //User can close window regardless if PIHM is running or not

            if(mThread == nullptr)
            {
                close();
            }

            int ret = QMessageBox::warning(this, tr("PIHM is running"),
                                           tr("Closing this window will not stop the PIHM thread.\n"
                                              "You will need to stop the PIHM process yourself. Otherwise stop before closing this window."),
                                           QMessageBox::Close | QMessageBox::Cancel,
                                           QMessageBox::Close);

            switch(ret)
            {
            case QMessageBox::Close:
                close();
                break;
            case QMessageBox::Cancel:
                //Do nothing
                break;
            }

        }
        else
        {
             close();
        }


        if(mThread == nullptr)
        {
            //Assume its safe to close winsow
            //mThread->Stop = true;
            //ui->pushButton_Stop->setEnabled(false);
            close();
        }
        else
        {

            if(mThread->Stop)
            {
                //Assume thread is in process of closing and safe to close window
                close();
            }
            else
            {
                //Not closing thread, user needs to decide on stop
                ui->label_PIHM_Status->setText("Thread still running" );
            }
        }

    } catch (...) {
        qDebug() << "Error: PIHMSimulation::on_pushButtonClose_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Help button event
// TODO, Need cataract server back online
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMSimulation::on_pushButtonHelp_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMSimulation::on_pushButtonHelp_clicked()";

    try {
        //        LogsString = tr("");
        //        if ( ! QDesktopServices::openUrl(QUrl("http://cataract.cee.psu.edu/PIHM/index.php/PIHMgis_3.0#PIHM_Simulation")) )
        //            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Load HTTP Link ... </span>")+tr("<br>"));
        //        ui->textBrowserLogs->setHtml(LogsString);
        //        ui->textBrowserLogs->repaint();

        pushButtonSetFocus();
    } catch (...) {
        qDebug() << "Error: PIHMSimulation::on_pushButtonHelp_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper function to indicate when PIHM finished
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMSimulation::on_progressBar_valueChanged(int value)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMSimulation::on_progressBar_valueChanged()";

    try {
        if ( value == 100 )
            ui->pushButtonRun->setText("Finished");

    } catch (...) {
        qDebug() << "Error: PIHMSimulation::on_progressBar_valueChanged() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper function to update progress bar. Used by threads.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMSimulation::updateProgressBarValue(int value)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMSimulation::updateProgressBarValue()";

    try {
        ui->progressBar->setValue(value);
    } catch (...) {
        qDebug() << "Error: PIHMSimulation::updateProgressBarValue() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper function to update GUI simulation has finished
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMSimulation::PIHMThreadFinished()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMSimulation::PIHMThreadFinished()";

    try {

        this->setCursor(Qt::ArrowCursor);

        LogsString.append(tr("<b>PIHM Simulation Complete.</b>")+tr("<br>"));
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();
        ui->pushButtonRun->setText("Run");

        ui->pushButtonRun->setDefault(false);
        ui->pushButtonClose->setDefault(true);
        ui->pushButtonClose->setFocus();

    } catch (...) {
        qDebug() << "Error: PIHMSimulation::PIHMThreadFinished() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// User has modified InputDataFolder text
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMSimulation::on_lineEditInputDataFolder_textChanged(const QString &arg1)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMSimulation::on_lineEditInputDataFolder_textChanged()";

    try {

        verifyInputOutputFile();

    } catch (...) {
        qDebug() << "Error: PIHMSimulation::on_lineEditInputDataFolder_textChanged() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// User has modified DataKey text
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMSimulation::on_lineEditDataKey_textChanged(const QString &arg1)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMSimulation::on_lineEditDataKey_textChanged()";

    try {

        verifyInputOutputFile();

    } catch (...) {
        qDebug() << "Error: PIHMSimulation::on_lineEditDataKey_textChanged() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper function to check files required for PIHM
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMSimulation::verifyInputOutputFile()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMSimulation::verifyInputOutputFile()";

    try {

        LogsString = tr("");
        if ( ! QDir(ui->lineEditInputDataFolder->text()).exists() )
        {
            Log_Error_Message("Folder Does Not Exist " + ui->lineEditInputDataFolder->text() + tr("<br>"));
        }
        else
        {
            LogsString.append(tr("Output Folder Exists ... ")+ui->lineEditInputDataFolder->text()+tr("<br>"));

        }

        QString FileName;
        FileName = ui->lineEditInputDataFolder->text() + "/" + ui->lineEditDataKey->text();

        QStringList Extensions;
        Extensions << ".mesh";
        Extensions << ".att";
        Extensions << ".riv";
        Extensions << ".soil";
        Extensions << ".geol";
        Extensions << ".lc";
        Extensions << ".init";
        Extensions << ".ibc";
        Extensions << ".para";
        Extensions << ".calib";
        Extensions << ".forc";

        bool missing_files = false;
        for( int i=0; i < Extensions.length(); i++)
        {
            if ( ! QFile(FileName + Extensions.at(i)).exists() )
            {
                Log_Error_Message("Input File Does Not Exist " + FileName + Extensions.at(i) +tr("<br>"));
                missing_files = true;
            }
            else
            {
                LogsString.append(tr("Input File Exists ... ")+ FileName + Extensions.at(i) +tr("<br>"));
            }
        }

        if(!missing_files)
        {
            LogsString.append(tr("All PIHM input files found ") +tr("<br>"));
            ui->pushButtonRun->setEnabled(true);
        }
        else
        {
            ui->pushButtonRun->setEnabled(false);
        }

        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

    } catch (...) {
        qDebug() << "Error: PIHMSimulation::verifyInputOutputFile() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Button Event, user clicked on Check Inputs Button (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMSimulation::on_pushButtonCheckInputs_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMSimulation::on_pushButtonCheckInputs_clicked()";

    try {

        verifyInputOutputFile();
    } catch (...) {
        qDebug() << "Error: PIHMSimulation::on_pushButtonCheckInputs_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Button Event, user clicked on Stop Button (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMSimulation::on_pushButton_Stop_clicked()
{

    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMSimulation::on_pushButton_Stop_clicked()";

    try {

        if(mThread != nullptr)
        {
            mThread->Stop = true;
            ui->pushButton_Stop->setEnabled(false);
        }

    } catch (...) {
        qDebug() << "Error: PIHMSimulation::on_pushButton_Stop_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Value Changed Event received by PIHM Thread
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMSimulation::onValueChanged(int count)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMSimulation::onValueChanged()";

    try {

        ui->progressBar->setValue(count);

    } catch (...) {
        qDebug() << "Error: PIHMSimulation::onValueChanged() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Messages from PIHM Thread
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMSimulation::onPIHM_StatusChanged(std::string value)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMSimulation::onPIHM_StatusChanged()";

    try {

        ui->label_PIHM_Status->setText(value.c_str());

    } catch (...) {
        qDebug() << "Error: PIHMSimulation::onPIHM_StatusChanged() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PIHM model finished
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMSimulation::onPIHM_Finished(bool status)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMSimulation::onPIHM_Finished()";

    try {

        if(status)
        {
            this->setCursor(Qt::ArrowCursor);
            ui->pushButton_Stop->setEnabled(false);
            pihm_running = false;
        }
        else
        {
            this->setCursor(Qt::WaitCursor);
            ui->pushButton_Stop->setEnabled(true);
            pihm_running = true;

        }

    } catch (...) {
        qDebug() << "Error: PIHMSimulation::onPIHM_Finished() is returning w/o checking";
    }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PIHM model failed
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMSimulation::onPIHM_Failed()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMSimulation::onPIHM_Failed()";

    try {

        ui->pushButton_Stop->setEnabled(false);

    } catch (...) {
        qDebug() << "Error: PIHMSimulation::onPIHM_Failed() is returning w/o checking";
    }

}

