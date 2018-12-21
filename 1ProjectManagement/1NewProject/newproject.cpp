#include <QtGui>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>

#include "newproject.h"
#include "ui_newproject.h"
#include "globals.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NewProject Constructor
// Parent is Main Window, filename is the project base folder
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NewProject::NewProject(QWidget *parent, QString workspace_folder, QString project_folder, QString project_name):
    QDialog(parent), ui(new Ui::NewProject)
{
    try {
        if(print_debug_messages)
            qDebug() << "INFO: Start NewProject";

        ui->setupUi(this);
        ui->pushButtonFile->setDefault(true);
        ui->pushButtonFile->setFocus();

        ui->lineEditFile->setText(workspace_folder);
        ui->lineEditFolder->setText(project_folder);
        ui->lineEditFile2->setText(project_name);

        did_user_create_new_project = false;

    } catch (...) {
        qDebug() << "Error: NewProject is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NewProject Deconstructor
// Todo: Check for memory leaks
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NewProject::~NewProject()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ~NewProject";

    try {

        delete ui;

    } catch (...) {
        qDebug() << "Error: ~NewProject is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper function to get user assigned workspace folder
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
QString NewProject::get_Workspace_Folder()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start get_Workspace_Folder";

    try {

        if( ui != nullptr)
        {
            return ui->lineEditFile->text();
        }

    } catch (...) {
        qDebug() << "Error: get_Workspace_Folder is returning w/o checking";
    }

    return "ERROR";
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper function to get user assigned project folder
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
QString NewProject::get_Project_Folder()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start get_Project_Folder";

    try {

        if( ui != nullptr)
        {
            return ui->lineEditFolder->text();
        }

    } catch (...) {
        qDebug() << "Error: get_Project_Folder is returning w/o checking";
    }

    return "ERROR";
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper function to get user assigned project name
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
QString NewProject::get_Project_Name()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start get_Project_Name";

    try {

        if( ui != nullptr)
        {
            return ui->lineEditFile2->text();
        }

    } catch (...) {
        qDebug() << "Error: get_Project_Name is returning w/o checking";
    }

    return "ERROR";
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper function to get if user decided on new project successfully
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool NewProject::get_User_Created_New_Project()
{
    return  did_user_create_new_project;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to clear message log
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void NewProject::Clear_Log()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start NewProject::Clear_Log()";

    try {

        LogsString = tr("");
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

    } catch (...) {
        qDebug() << "Error: NewProject::Clear_Log() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check Log_Error_Message
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void NewProject::Log_Error_Message(QString message)
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
void NewProject::Log_Message(QString message)
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
// Change Workspace Folder Browse Button Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void NewProject::on_pushButtonFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start NewProject on_pushButtonFile_clicked";

    try {

        Clear_Log();

        QString workspace_folder = QFileDialog::getExistingDirectory(this, "Workspace Folder", user_pihmgis_root_folder, 0);

        if(workspace_folder.length() < 1)
            return;

        ui->lineEditFile->setText(workspace_folder);

    } catch (...)
    {
        qDebug() << "Error: NewProject on_pushButtonFile_clicked";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Close Browse Button Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void NewProject::on_pushButtonClose_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start NewProject on_pushButtonClose_clicked";

    try {

        close();

    } catch (...) {
        qDebug() << "Error: NewProject on_pushButtonClose_clicked";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Help Button Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void NewProject::on_pushButtonHelp_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start NewProject on_pushButtonHelp_clicked";

    try {

        //        LogsString = tr("");
        //        if ( ! QDesktopServices::openUrl(QUrl("http://cataract.cee.psu.edu/PIHM/index.php/PIHMgis_3.0#New_Project")) )
        //            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Load HTTP Link ... </span>")+tr("<br>"));
        //        ui->textBrowserLogs->setHtml(LogsString);
        //        ui->textBrowserLogs->repaint();

    } catch (...) {
        qDebug() << "Error: NewProject on_pushButtonHelp_clicked";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Return value indicates the number of folders (total of 7) required for pihm gis
//Warning not checking if files exist in folder. As users should be able to stop/start project components
//This function should be in sync with main dialog code check logic used to load the dialog
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int NewProject::check_pihmgis_project_exists(QString folder, QString project_location)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start NewProject::check_pihmgis_project_exists()";

    try {
        int result = 0;
        QString project_folder = folder + "/" + project_location;
        QDir dir(project_folder);
        if (!dir.exists())
        {
            result = 0;
            Log_Error_Message("Could not find  :" + project_folder);
            return result; //No point checking any further
        }
        else
        {
            Log_Message("Found : " + project_folder);
            result++;
        }

        QString gisfolder = folder + "/1RasterProcessing";
        QDir dir1(gisfolder);
        if (dir1.exists())
        {
            Log_Message("Found : " + gisfolder);
            result++;
        }
        else
        {
            Log_Error_Message("Could not find : " + gisfolder);
        }

        gisfolder = folder + "/2VectorProcessing";
        QDir dir2(gisfolder);
        if (dir2.exists())
        {
            Log_Message("Found : " + gisfolder);
            result++;
        }
        else
        {
            Log_Error_Message("Could not find : " + gisfolder);
        }

        gisfolder = folder + "/3DomainDecomposition";
        QDir dir3(gisfolder);
        if (dir3.exists())
        {
            Log_Message("Found : " + gisfolder);
            result++;
        }
        else
        {
            Log_Error_Message("Could not find : " + gisfolder );
        }

        gisfolder = folder + "/4DataModelLoader";
        QDir dir4(gisfolder);
        if (dir4.exists())
        {
            Log_Message("Found : " + gisfolder);
            result++;
        }
        else
        {
            Log_Error_Message("Could not find : " + gisfolder);
        }

        gisfolder = folder + "/5PIHMSimulation";
        QDir dir5(gisfolder);
        if (dir5.exists())
        {
            Log_Message("Found : " + gisfolder);
            result++;
        }
        else
        {
            Log_Error_Message("Could not find : " + gisfolder );
        }

        gisfolder = folder + "/6VisualAnalytics";
        QDir dir6(gisfolder);
        if (dir6.exists())
        {
            Log_Message("Found : " + gisfolder );
            result++;
        }
        else
        {
            Log_Error_Message("Could not find : " + gisfolder);
        }

        return result;

    } catch (...) {
        qDebug() << "Error: check_pihmgis_project_exists is returning w/o checking";
    }

    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Create PIHMgis Workspace Folders
// This function should be in sync with main dialog code check logic used to load the dialog
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool NewProject::create_default_project_workspace(QString pihmgis_root_folder, QString project_folder)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start NewProject::create_default_project_workspace";

    try
    {
        QString make_folder = pihmgis_root_folder + "/" + project_folder;
        QDir dir(make_folder);

        if (!dir.exists())
        {
            bool created  = dir.mkpath(make_folder);
            if(!created)
            {
                Log_Error_Message("Unable to create folder:  " + make_folder + " .Check your folder permissions and/or disk space.");
                return false;
            }

            Log_Message("Created folder = " + make_folder);
        }
        else
        {
            Log_Error_Message("Folder already exists =  " + make_folder);
        }


        //Need to create default folders for pihmgis
        make_folder = pihmgis_root_folder +  + "/1RasterProcessing";
        QDir dir_1RasterProcessing(make_folder);

        if (!dir_1RasterProcessing.exists()) {
            dir_1RasterProcessing.mkpath(make_folder);
            Log_Message("Creating 1RasterProcessing folder = " + make_folder);
        }
        else
        {
            Log_Error_Message("1RasterProcessing Folder already exists =  " + make_folder);
        }

        make_folder = pihmgis_root_folder + "/2VectorProcessing";
        QDir dir_2VectorProcessing(make_folder);

        if (!dir_2VectorProcessing.exists()) {
            dir_2VectorProcessing.mkpath(make_folder);
            Log_Message("Creating 2VectorProcessing folder = " + make_folder);
        }
        else
        {
            Log_Error_Message("2VectorProcessing Folder already exists =  " + make_folder);
        }


        make_folder = pihmgis_root_folder + "/3DomainDecomposition";
        QDir dir_3DomainDecomposition(make_folder);

        if (!dir_3DomainDecomposition.exists()) {
            dir_3DomainDecomposition.mkpath(make_folder);
            Log_Message("Creating 3DomainDecomposition folder = " + make_folder);
        }
        else
        {
            Log_Error_Message("3DomainDecomposition Folder already exists =  " + make_folder);
        }

        make_folder = pihmgis_root_folder + "/4DataModelLoader";
        QDir dir_4DataModelLoader(make_folder);

        if (!dir_4DataModelLoader.exists()) {
            dir_4DataModelLoader.mkpath(make_folder);
            Log_Message("Creating 4DataModelLoader folder = " + make_folder);
        }
        else
        {
            Log_Error_Message("4DataModelLoader Folder already exists =  " + make_folder);
        }

        make_folder = pihmgis_root_folder + "/5PIHMSimulation";
        QDir dir_5PIHMSimulation(make_folder);

        if (!dir_5PIHMSimulation.exists()) {
            dir_5PIHMSimulation.mkpath(make_folder);
            Log_Message("Creating 5PIHMSimulation folder = " + make_folder);
        }
        else
        {
            Log_Error_Message("5PIHMSimulation Folder already exists =  " + make_folder);
        }

        make_folder = pihmgis_root_folder + "/6VisualAnalytics";
        QDir dir_6VisualAnalytics(make_folder);

        if (!dir_6VisualAnalytics.exists()) {
            dir_6VisualAnalytics.mkpath(make_folder);
            Log_Message("Creating 6VisualAnalytics folder = " + make_folder);
        }
        else
        {
            Log_Error_Message("6VisualAnalytics Folder already exists =  " + make_folder);
        }


        make_folder = pihmgis_root_folder + "/Software";
        QDir dir_Software(make_folder);

        if (!dir_Software.exists()) {
            dir_Software.mkpath(make_folder);
            Log_Message("Creating Software folder = " + make_folder);
        }
        else
        {
            Log_Error_Message("Software Folder already exists =  " + make_folder);
        }

        //If folders already existed, assuming it doesnt matter
        return true;


    } catch (...)
    {
        qDebug() << "Error: NewProject::create_default_project_workspace is returning w/o checking";
        return false;
    }
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Create default PIHMgis project file
// This function should be in sync with main dialog code check logic used to load the dialog
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool NewProject::create_default_PIHMgis_project_file(QString pihmgis_root_folder, QString project_folder, QString name)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start NewProject::create_default_PIHMgis_project_file";

    try
    {

        QString filename = pihmgis_root_folder + "/" + project_folder + "/" + name;
        QFileInfo info(filename);

        QString pName = info.baseName() + ".txt";
        QString newFileName = info.path() +  "/" + pName;
        ui->lineEditFile2->setText(pName);

        QFile file(newFileName);

        if( file.open(QIODevice::WriteOnly | QIODevice::Text) )
        {
            // Date of project folder creation
            // Folder where Project File is Stored
            // Absolute Path of the Project File

            QDateTime ProjectDateTime = ProjectDateTime.currentDateTime();
            QString format = QString("MMMddyyyyhhmm");
            ProjectDateTime = ProjectDateTime.currentDateTime();

            QTextStream textStream(&file);
            textStream << "Created on: " << ProjectDateTime.toString() << "\n";
            textStream << pihmgis_root_folder << "\n";
            textStream << filename  << "\n";

        }
        else
        {
            return false;
        }

        return true;
    }
    catch (...)
    {
        qDebug() << "Error: NewProject::create_default_PIHMgis_project_file is returning w/o checking";
        return false;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Create Button Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void NewProject::on_pushButtonCreate_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start NewProject on_pushButtonCreate_clicked";

    try {

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Clear Log
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Clear_Log();

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check inputs
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        did_user_create_new_project = false;
        QString workspace_folder = ui->lineEditFile->text();
        QString project_folder   = ui->lineEditFolder->text();
        QString project_name     = ui->lineEditFile2->text();

        if(workspace_folder.length() < 1)
        {
            did_user_create_new_project = false;
            Log_Message("Workspace folder empty, create PIHMgis project cancelled.");
            return;
        }

        if(project_folder.length() < 1)
        {
            did_user_create_new_project = false;
            Log_Message("Project folder empty, create PIHMgis project cancelled.");
            return;
        }

        if(project_name.length() < 1)
        {
            did_user_create_new_project = false;
            Log_Message("Project name empty, create PIHMgis project cancelled.");
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Create Folders
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        bool created = create_default_project_workspace(workspace_folder, project_folder);
        if(!created)
        {
            did_user_create_new_project = false;
            Log_Error_Message("Issues creating project folders. Check folder permissions and disk space.");
            return;
        }

        int count = check_pihmgis_project_exists(workspace_folder, project_folder);
        if(count != 7)
        {
            did_user_create_new_project = false;
            Log_Error_Message("Checking project folders found issues. Check folder permissions and disk space.");
            return;
        }

        bool success = create_default_PIHMgis_project_file(workspace_folder, project_folder, project_name);
        if( !success)
        {
            did_user_create_new_project = false;
            Log_Error_Message("Creating PIHMgis project file failed. Check folder permissions and disk space.");
            return;
        }

        did_user_create_new_project = true;

        //Prevent user making new project at same location, they will need to hit close button now
        ui->lineEditFile->setEnabled(false);
        ui->lineEditFolder->setEnabled(false);
        ui->lineEditFile2->setEnabled(false);
        ui->pushButtonFile->setEnabled(false);
        ui->pushButtonCreate->setEnabled(false);

        Clear_Log();
        Log_Message("PIHMgis project ready.");



    } catch (...) {
        did_user_create_new_project = false;
        qDebug() << "Error: NewProject on_pushButtonCreate_clicked";
    }
}
