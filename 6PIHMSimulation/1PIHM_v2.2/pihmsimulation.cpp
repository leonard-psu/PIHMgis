#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>
#include <QDir>

#include "pihmsimulation.h"
#include "ui_pihmsimulation.h"

#include "0LibsIO/IOProjectFile.h"
#include "globals.h"


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
        //this->setWindowTitle(tr(": :   ")+this->ModelVersion+tr("   : :"));

        ui->setupUi(this);
        filename_open_project = filename;
        bool found_file = false;

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
        QStringList ModuleStringList;
        QString TempFileName;

        Check_InputDataFolder(user_pihmgis_root_folder+"/4DataModelLoader");

        ModuleStringList = ReadModuleLine(filename_open_project,tr("TINShapeLayer"));
        if ( ModuleStringList.length() > 0  )
        {
            TempFileName = ModuleStringList.at(3);
            TempFileName = TempFileName.right(TempFileName.length()-TempFileName.lastIndexOf("/")-1);
            TempFileName.replace( QString(".shp"), QString("") );
            Check_DataKey(TempFileName);
        }

        ModuleStringList = ReadModuleLine(filename_open_project,tr("MeshDataFile"));
        if ( ModuleStringList.length() > 0  )
        {
            TempFileName = ModuleStringList.at(9);
            Check_DataKey(TempFileName);
        }

        // ** Start: Fill Form If Module Has Been Run Previously
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

        if(  fileExists(folder) )
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
            LogsString.append(tr("<span style=\"color:#FF0000\">Warning: PIHM Version Not Supported </span>")+tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
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
            LogsString.append(tr("<span style=\"color:#FF0000\">Error: No Read Access to ... </span>")+ FileNamewithExtension +tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
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
                    LogsString.append(tr("<span style=\"color:#FF0000\">Error: Unable to remove file </span>") + output_FileName + tr("<br>"));
                    ui->textBrowserLogs->setHtml(LogsString);
                    ui->textBrowserLogs->repaint();
                    return -9;
                }
            }
            else {
                LogsString.append(tr("<span style=\"color:#FF0000\">Warning: Not overwriting Input file that already exists in Output folder location. </span>") + output_FileName + tr("<br>"));
                ui->textBrowserLogs->setHtml(LogsString);
                ui->textBrowserLogs->repaint();
                return -10;
            }
        }

        if ( ! QFile::copy(input_FileName, output_FileName) )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">Error: Unable to copy file </span>")+input_FileName+tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
            return -11;
        }

    } catch (...) {
        qDebug() << "Error: PIHMSimulation::CopyInputFile() is returning w/o checking";
    }
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Copy PIHM Input files to PIHM output folder
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PIHMSimulation::CopyInputFiles( QString output_folder, QString input_folder, QString project_name, bool delete_existing_output_file, bool return_on_error )
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMSimulation::CopyInputFiles()";

    bool result = false;

    try {

        if ( this->ModelVersion == "PIHM v2.2")
        {
            if(return_on_error)
            {
                if ( CopyInputFile(output_folder,input_folder, project_name,tr(".mesh"),delete_existing_output_file)  != 0 ) return 2301;
                if ( CopyInputFile(output_folder,input_folder, project_name,tr(".att"),delete_existing_output_file)   != 0 ) return 2302;
                if ( CopyInputFile(output_folder,input_folder, project_name,tr(".riv"),delete_existing_output_file)   != 0 ) return 2303;
                if ( CopyInputFile(output_folder,input_folder, project_name,tr(".soil"),delete_existing_output_file)  != 0 ) return 2304;
                if ( CopyInputFile(output_folder,input_folder, project_name,tr(".geol"),delete_existing_output_file)  != 0 ) return 2305;
                if ( CopyInputFile(output_folder,input_folder, project_name,tr(".lc"),delete_existing_output_file)    != 0 ) return 2306;
                if ( CopyInputFile(output_folder,input_folder, project_name,tr(".init"),delete_existing_output_file)  != 0 ) return 2307;
                if ( CopyInputFile(output_folder,input_folder, project_name,tr(".ibc"),delete_existing_output_file)   != 0 ) return 2308;
                if ( CopyInputFile(output_folder,input_folder, project_name,tr(".para"),delete_existing_output_file)  != 0 ) return 2309;
                if ( CopyInputFile(output_folder,input_folder, project_name,tr(".calib"),delete_existing_output_file) != 0 ) return 2310;
                if ( CopyInputFile(output_folder,input_folder, project_name,tr(".forc"),delete_existing_output_file)  != 0 ) return 2311;
            }
            else
            {
                bool error_found = false;
                if ( CopyInputFile(output_folder,input_folder, project_name,tr(".mesh"),delete_existing_output_file)  != 0 ) error_found = true;
                if ( CopyInputFile(output_folder,input_folder, project_name,tr(".att"),delete_existing_output_file)   != 0 ) error_found = true;
                if ( CopyInputFile(output_folder,input_folder, project_name,tr(".riv"),delete_existing_output_file)   != 0 ) error_found = true;
                if ( CopyInputFile(output_folder,input_folder, project_name,tr(".soil"),delete_existing_output_file)  != 0 ) error_found = true;
                if ( CopyInputFile(output_folder,input_folder, project_name,tr(".geol"),delete_existing_output_file)  != 0 ) error_found = true;
                if ( CopyInputFile(output_folder,input_folder, project_name,tr(".lc"),delete_existing_output_file)    != 0 ) error_found = true;
                if ( CopyInputFile(output_folder,input_folder, project_name,tr(".init"),delete_existing_output_file)  != 0 ) error_found = true;
                if ( CopyInputFile(output_folder,input_folder, project_name,tr(".ibc"),delete_existing_output_file)   != 0 ) error_found = true;
                if ( CopyInputFile(output_folder,input_folder, project_name,tr(".para"),delete_existing_output_file)  != 0 ) error_found = true;
                if ( CopyInputFile(output_folder,input_folder, project_name,tr(".calib"),delete_existing_output_file) != 0 ) error_found = true;
                if ( CopyInputFile(output_folder,input_folder, project_name,tr(".forc"),delete_existing_output_file)  != 0 ) error_found = true;
                result = error_found;
            }

        }
        else
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">Error: PIHM Version Not Supported </span>")+tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
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
        bool delete_existing_output_file = false; //TODO GUI
        bool return_on_error = true; //TODO GUI

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

        bool checked_output = CopyInputFiles(output_folder, input_folder, project_name, delete_existing_output_file, return_on_error);
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


        if(ui->pushButtonRun->text() == "Run")
        {
            ui->pushButtonRun->setText("Stop"); //Want user to know to clip to stop existing thread

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
            // Preparing Thread Project file
            //TODO error checking
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            MyPIHMThread = new PIHMThread(this);
            bool error_check = MyPIHMThread->set_Output_Folder(output_folder);
            if(!error_check)
            {
                Log_Error_Message("Problem with output folder: " + output_folder );
                return;
            }
            error_check = MyPIHMThread->set_Project_Name(project_name);
            if(!error_check)
            {
                Log_Error_Message("Problem with Project Name: " + project_name );
                return;
            }
            error_check = MyPIHMThread->set_Model_Version(ModelVersion);
            if(!error_check)
            {
                Log_Error_Message("Problem with Model_Version: " + ModelVersion );
                return;
            }
            error_check = MyPIHMThread->set_Progress_Bar(ui->progressBar);
            if(!error_check)
            {
                Log_Error_Message("Problem with progressBar " );
                return;
            }
            error_check = MyPIHMThread->set_LogFile(LogsString);
            if(!error_check)
            {
                Log_Error_Message("Problem with log string: " + LogsString );
                return;
            }
            error_check = MyPIHMThread->init();
            if(!error_check)
            {
                Log_Error_Message("Problem with setting up thread initization" );
                return;
            }

            LogsString.append(tr("Running PIHM ...")+tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();

            connect(MyPIHMThread,SIGNAL(finished()),this,SLOT(PIHMThreadFinished()));

            this->moveToThread(MyPIHMThread);
            MyPIHMThread->start();


        }
        else
        {
            // TODO: If simulation is running stop it
            ui->pushButtonRun->setText("Stopping...");

            if( MyPIHMThread != nullptr )
            {
                MyPIHMThread->kill();
                //MyPIHMThread->wait();

                //thread->wait();
                //??done(0);
            }

            // TODO Call Stop Thread
            LogsString.append(tr("<span style=\"color:#FF0000\">Simulation has been stopped.</span>")+tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
            ui->progressBar->setValue(0);
            ui->pushButtonRun->setText("Run");

        }

        pushButtonSetFocus();

    } catch (...) {
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

        //        if( MyPIHMThread != nullptr )
        //        {
        //        qDebug() << "MyPIHMThread = " << MyPIHMThread;
        //        }
        //        else
        //        {
        //             qDebug() << "Empty PIHMThread";
        //        }

        //        ui->pushButtonClose->setText("Closing...");
        //        // TODO: If simulation is running -- stop first before closing
        //        if( MyPIHMThread != nullptr )
        //        {
        //            MyPIHMThread->kill();//?? TEST IF THIS IS REQUIRED?
        //            //thread->wait();
        //            //done(0);
        //        }
        //    while () // Wait for thread to close/terminate

        //QStringList default_params; default_params << "WORKFLOW7" << "WORKFLOW8";
        //QMetaObject::invokeMethod(parent(),"set_defaults",Q_ARG(QStringList,default_params));
        close();

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


void PIHMSimulation::updateProgressBarValue(int value)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMSimulation::updateProgressBarValue()";

    try {
        qDebug() << "From SLOT PIHMSimulation::updateProgressBarValue";
        ui->progressBar->setValue(value);
        //QApplication::processEvents();
    } catch (...) {
        qDebug() << "Error: PIHMSimulation::updateProgressBarValue() is returning w/o checking";
    }
}

void PIHMSimulation::PIHMThreadFinished()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMSimulation::PIHMThreadFinished()";

    try {
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

void PIHMSimulation::on_lineEditInputDataFolder_textChanged(const QString &arg1)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMSimulation::on_lineEditInputDataFolder_textChanged()";

    try {
        ui->lineEditInputDataFolder->setStyleSheet("color: rgb(0, 0, 0);");
        verifyInputOutputFile();
    } catch (...) {
        qDebug() << "Error: PIHMSimulation::on_lineEditInputDataFolder_textChanged() is returning w/o checking";
    }
}

void PIHMSimulation::on_lineEditDataKey_textChanged(const QString &arg1)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMSimulation::on_lineEditDataKey_textChanged()";

    try {
        ui->lineEditDataKey->setStyleSheet("color: rgb(0, 0, 0);");
        verifyInputOutputFile();
    } catch (...) {
        qDebug() << "Error: PIHMSimulation::on_lineEditDataKey_textChanged() is returning w/o checking";
    }
}

void PIHMSimulation::verifyInputOutputFile()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMSimulation::verifyInputOutputFile()";

    try {

        LogsString = tr("");
        if ( ! QDir(ui->lineEditInputDataFolder->text()).exists() )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Folder Does Not Exist ... </span>")+ui->lineEditInputDataFolder->text()+tr("<br>"));
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

        for( int i=0; i < Extensions.length(); i++)
        {
            if ( ! QFile(FileName + Extensions.at(i)).exists() )
            {
                LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Input File Does Not Exist ... </span>")+ FileName + Extensions.at(i) +tr("<br>"));
            }
            else
            {
                LogsString.append(tr("Input File Exists ... ")+ FileName + Extensions.at(i) +tr("<br>"));
            }
        }

        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();
        //pushButtonSetFocus();

    } catch (...) {
        qDebug() << "Error: PIHMSimulation::verifyInputOutputFile() is returning w/o checking";
    }
}
