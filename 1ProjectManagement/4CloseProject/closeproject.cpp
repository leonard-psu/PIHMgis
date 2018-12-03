#include <QtGui>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>

#include "closeproject.h"
#include "ui_closeproject.h"
#include "globals.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CloseProject Constructor
// Parent is Main Window, filename is the project base folder
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CloseProject::CloseProject(QWidget *parent, QString filename) : QDialog(parent), ui(new Ui::CloseProject)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start CloseProject";

    try {

        ui->setupUi(this);
        filename_open_project = filename;
        bool found_file = false;
        user_wants_project_closed = false;

        if(print_debug_messages)
            qDebug() << "INFO: filename -> " << filename_open_project;

        QFile ProjectFile(filename_open_project);
        if ( ! ProjectFile.open(QIODevice::ReadOnly | QIODevice::Text) )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">Error: Unable to Open project file: </span>") + filename_open_project);
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

    } catch (...) {
        qDebug() << "Error: CloseProject is returning w/o checking";
    }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CloseProject Deconstructor
// Todo: Check for memory leaks
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CloseProject::~CloseProject()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ~CloseProject";

    try {

        delete ui;

     } catch (...) {
        qDebug() << "Error: ~CloseProject is returning w/o checking";
     }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper function to get if user decided on closing project successfully
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CloseProject::user_closed_project()
{
    return  user_wants_project_closed;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Load_Project_Settings
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CloseProject::Load_Project_Settings()
{
    if(print_debug_messages)
        qDebug() << "INFO: CloseProject::Load_Project_Settings()";

    try {

        ui->textEdit->setText(filename_open_project);
        ui->label_3->setText(filename_open_project);


    } catch (...) {
        qDebug() << "Error: CloseProject::Load_Project_Settings is returning w/o checking";
        return false;
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Close button event
// TODO, Decide on keeping button next highlights or not
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CloseProject::on_pushButtonClose_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start CloseProject::on_pushButtonClose_clicked()";

    try {

        close();

    } catch (...)
    {
        qDebug() << "Error: CloseProject::on_pushButtonClose_clicked()";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to clear message log
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CloseProject::Clear_Log()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start CloseProject::Clear_Log()";

    try {

        LogsString = tr("");
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

    } catch (...) {
        qDebug() << "Error: CloseProject::Clear_Log() is returning w/o checking";
    }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Help button event
// TODO, Need cataract server back online
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CloseProject::on_pushButtonHelp_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start CloseProject::on_pushButtonHelp_clicked()";

    try{

//        LogsString = tr("");
//        if ( ! QDesktopServices::openUrl(QUrl("http://cataract.cee.psu.edu/PIHM/index.php/PIHMgis_3.0#Close_Project")) )
//            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Load HTTP Link ... </span>")+tr("<br>"));
//        ui->textBrowserLogs->setHtml(LogsString);
//        ui->textBrowserLogs->repaint();

    } catch (...) {
        qDebug() << "Error: CloseProject::on_pushButtonHelp_clicked()";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Close Project Button event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CloseProject::on_pushButtonCloseProject_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start CloseProject::on_pushButtonCloseProject_clicked()";

    try {

        Clear_Log();

        user_wants_project_closed = true;

        ui->label_3->setText("");
        ui->textEdit->setText("");

        LogsString.append(tr("<b>Project Closed Successfully.")+tr("<br>"));
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

        ui->pushButtonCloseProject->setDefault(false);
        ui->pushButtonClose->setDefault(true);
        ui->pushButtonClose->setFocus();

    } catch (...) {
        qDebug() << "Error: CloseProject::on_pushButtonCloseProject_clicked()";
    }
}
