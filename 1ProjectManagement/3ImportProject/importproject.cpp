#include <QtGui>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>

#include "importproject.h"
#include "ui_importproject.h"
#include "globals.h"


ImportProject::ImportProject(QWidget *parent)
    : QDialog(parent), ui(new Ui::ImportProject)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ImportProject";

    ui->setupUi(this);

    ui->pushButtonProject->setDefault(true);
    ui->pushButtonProject->setFocus();
}

ImportProject::~ImportProject()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ~ImportProject";

    delete ui;
}

void ImportProject::on_pushButtonProject_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ImportProject::on_pushButtonProject_clicked()";

    try {
        LogsString = tr("");
        LogsString.append(tr("Processing ... <br>"));
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();
        LogsString = tr("");

        QString ProjectFolder, ProjectFileName;
        QFile OpenProjectFile(user_pihmgis_root_folder+"/.PIHMgis/OpenProject.txt");
        if ( ! OpenProjectFile.open(QIODevice::ReadOnly | QIODevice::Text) )
        {
            ProjectFolder = user_pihmgis_root_folder;
        }
        else
        {
            QTextStream OpenProjectFileTextStream(&OpenProjectFile);
            ProjectFolder = OpenProjectFileTextStream.readLine();
            ProjectFileName= OpenProjectFileTextStream.readLine();
            OpenProjectFile.close();
        }

        QString OldProjectFolder, OldProjectFileName;
        QString NewProjectFolder, NewProjectFileName;
        OldProjectFileName = QFileDialog::getOpenFileName(this, "Import Existing Project", ProjectFolder, "PIHMgis Project (*.pihmgis)");

        if (OldProjectFileName != nullptr)
        {
            NewProjectFileName = OldProjectFileName;

            NewProjectFolder   = OldProjectFileName;
            NewProjectFolder.truncate(NewProjectFolder.lastIndexOf("/",-1));

            QFile OldOpenProjectFile(OldProjectFileName);
            OldOpenProjectFile.open(QIODevice::ReadOnly | QIODevice::Text);
            QTextStream OldOpenProjectFileTextStream(&OldOpenProjectFile);
            OldOpenProjectFileTextStream.readLine();
            OldProjectFolder = OldOpenProjectFileTextStream.readLine();
            OldOpenProjectFile.close();

            qDebug()<<"OldProjectFolder   = "<<OldProjectFolder<<"\n";
            qDebug()<<"OldProjectFileName = "<<OldProjectFileName<<"\n";
            qDebug()<<"NewProjectFolder   = "<<NewProjectFolder<<"\n";
            qDebug()<<"NewProjectFileName = "<<NewProjectFileName<<"\n";

            ui->lineEdit->setText(OldProjectFileName);
            ui->lineEditOld->setText(OldProjectFolder);
            ui->lineEditNew->setText(NewProjectFolder);

            ui->pushButtonProject->setDefault(false);
            ui->pushButtonImport->setDefault(true);
            ui->pushButtonImport->setFocus();
        }

        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

    } catch (...) {
        qDebug() << "Error: ImportProject::on_pushButtonProject_clicked()";
    }
}

void ImportProject::on_pushButtonClose_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ImportProject::on_pushButtonClose_clicked()";

    try {
        QStringList default_params; default_params << "WORKFLOW2" << "WORKFLOW8";
        QMetaObject::invokeMethod(parent(),"set_defaults",Q_ARG(QStringList,default_params));
        close();
    } catch (...) {
        qDebug() << "Error: ImportProject::on_pushButtonClose_clicked()";
    }
}

void ImportProject::on_pushButtonImport_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ImportProject::on_pushButtonImport_clicked()";

    try {
        LogsString = tr("");
        bool success;
        QString OldProjectFolder;  OldProjectFolder = ui->lineEditOld->text();
        QString NewProjectFolder;  NewProjectFolder = ui->lineEditNew->text();
        QString ProjectFileName;   ProjectFileName  = ui->lineEdit->text();

        if( OldProjectFolder != nullptr && NewProjectFolder != nullptr && ProjectFileName != nullptr)
        {
            QFile ProjectFile(ProjectFileName);
            ProjectFile.open(QIODevice::ReadOnly  | QIODevice::Text);
            QTextStream ProjectFileTextStream(&ProjectFile);

            QString TempStr;
            QString TempImportFileName = user_pihmgis_root_folder +"/.PIHMgis/TempImportFile.txt";
            QFile TempImportFile(TempImportFileName);

            qDebug() << "Open Temporary Import File: " << TempImportFileName;
            if ( ! TempImportFile.open(QIODevice::WriteOnly | QIODevice::Text) )
            {
                qDebug() << "ERROR: Unable to Open File!";
                //QMessageBox::critical(this,tr("Import Project"),tr("Error: Unable to Create Temporary Import File"),QMessageBox::Ok);
                LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Open Temporary Import File for Writing: </span>")+TempImportFileName+tr("<br>"));
                ui->textBrowserLogs->setHtml(LogsString);
                ui->textBrowserLogs->repaint();
                return;
            }
            QTextStream TempImportFileTextStream(&TempImportFile);

            TempStr = ProjectFileTextStream.readAll();
            qDebug() << "Old Project File: \n"<< qPrintable(TempStr) <<"\n";

            TempStr.replace(OldProjectFolder, NewProjectFolder);
            qDebug() << "New Project File: \n"<< qPrintable(TempStr) <<"\n";
            TempImportFileTextStream<<TempStr;

            TempStr = "";
            ProjectFile.close();
            TempImportFile.close();

            TempImportFile.open(QIODevice::ReadOnly  | QIODevice::Text);
            //QTextStream TempImportFileTextStream(&TempImportFile);

            ProjectFile.open(QIODevice::WriteOnly | QIODevice::Text);
            //QTextStream t7(&ProjectFile);
            TempStr = TempImportFileTextStream.readAll();
            ProjectFileTextStream << TempStr;

            qDebug() << "Written To Project File:\n" << TempStr;

            TempImportFile.close();
            ProjectFile.close();


            QFile OpenProjectFile(user_pihmgis_root_folder+"/.PIHMgis/OpenProject.txt");
            qDebug() << "Open Project File: " << user_pihmgis_root_folder +"/.PIHMgis/OpenProject.txt";
            if ( ! OpenProjectFile.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                qDebug() << "Error: Unable to Open File!";
                //QMessageBox::critical(this,tr("Import Project"),tr("Error: Unable to Create Project File"),QMessageBox::Ok);
                LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Create Project File: </span>")+ user_pihmgis_root_folder +"/.PIHMgis/OpenProject.txt"+tr("<br>"));
                ui->textBrowserLogs->setHtml(LogsString);
                ui->textBrowserLogs->repaint();
                return;
            }
            QTextStream OpenProjectFileTextStream(&OpenProjectFile);
            OpenProjectFileTextStream << NewProjectFolder << "\n";
            OpenProjectFileTextStream << ProjectFileName;

            OpenProjectFile.close();

            success = QFile::remove(TempImportFileName);
            if (success == false)
            {
                qDebug() << "ERROR: Unable to Delete Temporary Import File!";
                //QMessageBox::critical(this,tr("Import Project"),tr("Error: Unable to Delete Temporary Import File"),QMessageBox::Ok);
                LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Delete Temporary Import File: </span>")+TempImportFileName+tr("<br>"));
                ui->textBrowserLogs->setHtml(LogsString);
                ui->textBrowserLogs->repaint();
                return;
            }

            //QMessageBox::information(this,tr("Import Project"),tr("Project Imported Successfully."),QMessageBox::Ok);
            LogsString.append(tr("<b>Existing Project Imported Successfully.")+tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();

            ui->pushButtonImport->setDefault(false);
            ui->pushButtonClose->setDefault(true);
            ui->pushButtonClose->setFocus();
        }

    } catch (...) {
        qDebug() << "Error: ImportProject::on_pushButtonImport_clicked()";
    }
}

void ImportProject::on_pushButtonHelp_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ImportProject::on_pushButtonHelp_clicked()";

    try {
//        LogsString = tr("");
//        if ( ! QDesktopServices::openUrl(QUrl("http://cataract.cee.psu.edu/PIHM/index.php/PIHMgis_3.0#Import_Project")) )
//            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Load HTTP Link ... </span>")+tr("<br>"));
//        ui->textBrowserLogs->setHtml(LogsString);
//        ui->textBrowserLogs->repaint();
    } catch (...) {
        qDebug() << "Error: ImportProject::on_pushButtonImport_clicked()";
    }

}

