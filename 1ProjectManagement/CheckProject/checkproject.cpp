#include "checkproject.h"
#include "ui_checkproject.h"
#include "globals.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CheckProject Constructor
// Parent is Main Window, filename is the project base folder
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CheckProject::CheckProject(QWidget *parent, QString folder) :
    QDialog(parent),
    ui(new Ui::CheckProject)
{
    try {

        user_project_folder = folder;
        ui->setupUi(this);

        ui->lineEditWorkspaceFolder->setText(user_project_folder);

        int found = check_pihmgis_project_exists(user_project_folder);

    } catch (...) {
        qDebug() << "Error: CheckProject is returning w/o checking";
    }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CheckProject Deconstructor
// Todo: Check for memory leaks
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CheckProject::~CheckProject()
{
    try {

        delete ui;

    } catch (...) {
        qDebug() << "Error: CheckProject is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Close button w/o checking
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CheckProject::on_pushButtonClose_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start CheckProject::on_pushButtonClose_clicked()";
    try {

        close();

    } catch (...) {
        qDebug() << "Error: CheckProject::on_pushButtonClose_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Recheck button
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CheckProject::on_pushButtonRecheck_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start CheckProject::on_pushButtonRecheck_clicked()";

    try {

        Clear_Log();
        int found = check_pihmgis_project_exists(user_project_folder);

    } catch (...) {
        qDebug() << "Error: CheckProject::on_pushButtonRecheck_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to clear message log
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CheckProject::Clear_Log()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start CheckProject::Clear_Log()";

    try {

        LogsString = tr("");
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

    } catch (...) {
        qDebug() << "Error: CheckProject::Clear_Log() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check Log_Error_Message
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CheckProject::Log_Error_Message(QString message)
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
// Helper Function to check Log_Error_Message
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CheckProject::Log_Message(QString message)
{
    try {
        LogsString.append(tr("<span style=\"color:#000000\"> ") + message + " </span>")+tr("<br>");
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();
    } catch (...) {
        qDebug() << "Error: Log_Message is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Return value indicates the number of folders (total of 7) required for pihm gis
//Warning not checking if files exist in folder. As users should be able to stop/start project components
//This function should be in sync with main dialog code check logic used to load the dialog
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CheckProject::check_pihmgis_project_exists(QString folder)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start CheckProject::check_pihmgis_project_exists()";

    try {
        int result = 0;
        QString project_folder = folder + user_pihmgis_project_folder;
        QDir dir(project_folder);
        if (!dir.exists())
        {
            result = 0;
            Log_Error_Message("Could not find  :" + project_folder );
            return result; //No point checking any further
        }
        else
        {
            Log_Message("Found : " + project_folder  );
            result++;
        }

        QString gisfolder = folder + "/1RasterProcessing";
        QDir dir1(gisfolder);
        if (dir1.exists())
        {
            Log_Message("Found : " + gisfolder  );
            result++;
        }
        else
        {
            Log_Error_Message("Could not find : " + gisfolder  );
        }

        gisfolder = folder + "/2VectorProcessing";
        QDir dir2(gisfolder);
        if (dir2.exists())
        {
            Log_Message("Found : " + gisfolder  );
            result++;
        }
        else
        {
            Log_Error_Message("Could not find : " + gisfolder  );
        }

        gisfolder = folder + "/3DomainDecomposition";
        QDir dir3(gisfolder);
        if (dir3.exists())
        {
            Log_Message("Found : " + gisfolder  );
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
            Log_Message("Found : " + gisfolder  );
            result++;
        }
        else
        {
            Log_Error_Message("Could not find : " + gisfolder  );
        }

        gisfolder = folder + "/5PIHMSimulation";
        QDir dir5(gisfolder);
        if (dir5.exists())
        {
            Log_Message("Found : " + gisfolder  );
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
            Log_Message("Found : " + gisfolder  );
            result++;
        }
        else
        {
            Log_Error_Message("Could not find : " + gisfolder );
        }

        return result;

    } catch (...) {
        qDebug() << "Error: check_pihmgis_project_exists is returning w/o checking";
    }

    return 0;
}

