#include <QtGui>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>

#include "closeproject.h"
#include "ui_closeproject.h"
#include "globals.h"



CloseProject::CloseProject(QWidget *parent)
    : QDialog(parent), ui(new Ui::CloseProject)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start CloseProject";

    try {
        ui->setupUi(this);

        QString ProjectFolder, ProjectFileName;
        QFile OpenProjectFile(user_pihmgis_root_folder +user_pihmgis_project_folder + "/OpenProject.txt");
        OpenProjectFile.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream OpenProjectFileTextStream(&OpenProjectFile);
        ProjectFolder  = OpenProjectFileTextStream.readLine();
        ProjectFileName = OpenProjectFileTextStream.readLine();
        OpenProjectFile.close();

        ui->textEdit->setText(ProjectFileName);
        ProjectFileName=ProjectFileName.mid(1 + ProjectFileName.lastIndexOf("/", -1));
        qDebug() << qPrintable(ProjectFileName) <<"\n";
        ui->label_3->setText(ProjectFileName);

        if(ProjectFileName == nullptr)
        {
            ui->pushButtonClose->setDefault(true);
            ui->pushButtonClose->setFocus();
        }
        else
        {
            ui->pushButtonOpen->setDefault(true);
            ui->pushButtonOpen->setFocus();
        }
    } catch (...) {
        qDebug() << "Error: CloseProject is returning w/o checking";
    }

}

CloseProject::~CloseProject()
{    if(print_debug_messages)
        qDebug() << "INFO: Start ~CloseProject";

    delete ui;
}

void CloseProject::on_pushButtonClose_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start CloseProject::on_pushButtonClose_clicked()";
    try {

//        QStringList default_params; default_params << "WORKFLOW2"; // << "WORKFLOW8";
        QStringList default_params; default_params << "WORKFLOW1";
        QMetaObject::invokeMethod(parent(),"set_defaults",Q_ARG(QStringList,default_params));
        close();

    } catch (...) {
        qDebug() << "Error: CloseProject::on_pushButtonClose_clicked()";
    }
}

void CloseProject::on_pushButtonOpen_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start CloseProject::on_pushButtonOpen_clicked()";

    try {

        LogsString = tr("");
        bool success;
        QString ProjectFolder, ProjectFileName;
        QFile OpenProjectFile(user_pihmgis_root_folder +user_pihmgis_project_folder + "/OpenProject.txt");
        OpenProjectFile.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream OpenProjectFileTextStream(&OpenProjectFile);
        ProjectFolder  = OpenProjectFileTextStream.readLine();
        ProjectFileName = OpenProjectFileTextStream.readLine();
        OpenProjectFile.close();

        success = QFile::remove(user_pihmgis_root_folder+user_pihmgis_project_folder + "/OpenProject.txt");

        qDebug() << "Delete File: " << user_pihmgis_root_folder + user_pihmgis_project_folder + "/OpenProject.txt";
        if (success == false)
        {
            qDebug() << "ERROR: Unable to Delete Project File!";
            //QMessageBox::critical(this,tr("Close Project"),tr("Error: Unable to Delete Project File"),QMessageBox::Ok);
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Close Project: </span>")+tr("<br>"));
            LogsString.append(tr("Need Write Access to File: ")+user_pihmgis_root_folder+user_pihmgis_project_folder + "/OpenProject.txt");
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
            return;
        }

        ui->label_3->setText("...");
        ui->textEdit->setText("...");

        //QMessageBox::information(this,tr("Close Project"),tr("Project Closed Successfully"),QMessageBox::Ok);
        LogsString.append(tr("<b>Project Closed Successfully.")+tr("<br>"));
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

        ui->pushButtonOpen->setDefault(false);
        ui->pushButtonClose->setDefault(true);
        ui->pushButtonClose->setFocus();

    } catch (...) {
        qDebug() << "Error: CloseProject::on_pushButtonOpen_clicked()";
    }
}

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
