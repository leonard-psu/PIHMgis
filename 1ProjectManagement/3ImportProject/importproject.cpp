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

    try {
        ui->setupUi(this);

        ui->lineEditNew->setText(user_pihmgis_root_folder);

//        string_FillPits = "";
//        string_FlowGrids = "";
//        string_StreamGrids = "";
//        string_LinkGrids = "";
//        string_CatchmentGrids = "";
//        string_StreamPolyline = "";
//        string_StreamRasterVector = "";
//        string_CatchmentPolygon = "";
//        string_CatchmentRasterVector = "";
//        string_DissolvePolygons = "";
//        string_PolygonToPolylines = "";
//        string_SimplifyPolylines = "";
//        string_PolylineToLines = "";
//        string_MergeVectorLayers = "";
//        string_MergeVectorDomainDecomposition = "";
//        string_ReadTopology = "";
//        string_DelaunayTriangulation = "";
//        string_TINShapeLayer = "";


        ui->pushButtonProject->setDefault(true);
        ui->pushButtonProject->setFocus();
    } catch (...) {
        qDebug() << "Error: ImportProject";
    }
}

ImportProject::~ImportProject()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ~ImportProject";
    try {
        delete ui;
    } catch (...) {
        qDebug() << "Error: ~ImportProject";
    }
}

//Browse button
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
        QFile OpenProjectFile(user_pihmgis_root_folder+user_pihmgis_project_folder + "/OpenProject.txt");

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

            //NewProjectFolder   = OldProjectFileName;
            //NewProjectFolder.truncate(NewProjectFolder.lastIndexOf("/",-1));
            NewProjectFolder = user_pihmgis_root_folder;

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
        //QStringList default_params; default_params << "WORKFLOW2" << "WORKFLOW8";
        //QMetaObject::invokeMethod(parent(),"set_defaults",Q_ARG(QStringList,default_params));
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

        QString OldProjectFolder = ui->lineEditOld->text();
        QString old_ProjectFileName  = ui->lineEdit->text();

        QString NewProjectFolder = ui->lineEditNew->text();
        QString NewProjectName = ui->new_lineEdit_ProjectFile->text();


        QString make_folder = user_pihmgis_root_folder + user_pihmgis_project_folder;
        QDir dir(make_folder);

        if (!dir.exists()) {
            dir.mkpath(make_folder);
            qDebug() << "Creating folder = " << make_folder;
        }
        else
        {
            qDebug() << "Folder already exists = " << make_folder;
        }

        if(NewProjectName.length() > 0)
        {
            //Do nothing
        }
        else
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Need to specify New Project Name: </span>")+tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
            qDebug() << "Need to specify NewProjectName = " << NewProjectName;
            return;
        }



        if( OldProjectFolder != nullptr && NewProjectFolder != nullptr && old_ProjectFileName != nullptr)
        {
            QFile old_ProjectFile(old_ProjectFileName);
            old_ProjectFile.open(QIODevice::ReadOnly  | QIODevice::Text);

            QTextStream ProjectFileTextStream(&old_ProjectFile);

            QString TempStr;
            QString TempImportFileName = user_pihmgis_root_folder +user_pihmgis_project_folder + "/TempImportFile.txt";
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

            //Need to assign values
            /* while (!ProjectFileTextStream.atEnd())
            {
                QString line = ProjectFileTextStream.readLine();

                bool is_it = line.startsWith("FillPits,");
                if(is_it)
                {
                    string_FillPits = line;
                }
                is_it = line.startsWith("FlowGrids,");
                if(is_it)
                {
                    string_FlowGrids = line;
                }
                is_it = line.startsWith("StreamGrids,");
                if(is_it)
                {
                    string_StreamGrids = line;
                }
                is_it = line.startsWith("LinkGrids,");
                if(is_it)
                {
                    string_LinkGrids = line;
                }
                is_it = line.startsWith("CatchmentGrids,");
                if(is_it)
                {
                    string_CatchmentGrids = line;
                }
                is_it = line.startsWith("StreamPolyline,");
                if(is_it)
                {
                    string_StreamPolyline = line;
                }
                is_it = line.startsWith("StreamRasterVector,");
                if(is_it)
                {
                    string_StreamRasterVector = line;
                }
                is_it = line.startsWith("CatchmentPolygon,");
                if(is_it)
                {
                    string_CatchmentPolygon = line;
                }
                is_it = line.startsWith("CatchmentRasterVector,");
                if(is_it)
                {
                    string_CatchmentRasterVector = line;
                }
                is_it = line.startsWith("DissolvePolygons,");
                if(is_it)
                {
                    string_DissolvePolygons = line;
                }
                is_it = line.startsWith("PolygonToPolylines,");
                if(is_it)
                {
                    string_PolygonToPolylines = line;
                }
                is_it = line.startsWith("SimplifyPolylines,");
                if(is_it)
                {
                    string_SimplifyPolylines = line;
                }
                is_it = line.startsWith("PolylineToLines,");
                if(is_it)
                {
                    string_PolylineToLines = line;
                }
                is_it = line.startsWith("MergeVectorLayers,");
                if(is_it)
                {
                    string_MergeVectorLayers = line;
                }
                is_it = line.startsWith("MergeVectorDomainDecomposition,");
                if(is_it)
                {
                    string_MergeVectorDomainDecomposition = line;
                }
                is_it = line.startsWith("ReadTopology,");
                if(is_it)
                {
                    string_ReadTopology = line;
                }
                is_it = line.startsWith("DelaunayTriangulation,");
                if(is_it)
                {
                    string_DelaunayTriangulation = line;
                }
                is_it = line.startsWith("TINShapeLayer,");
                if(is_it)
                {
                    string_TINShapeLayer = line;
                }

            }
*/

            TempStr = ProjectFileTextStream.readAll();
            qDebug() << "Old Project File: \n"<< qPrintable(TempStr) <<"\n";

            TempStr.replace(OldProjectFolder, NewProjectFolder);
            qDebug() << "New Project File: \n"<< qPrintable(TempStr) <<"\n";
            TempImportFileTextStream<<TempStr;

            //TempStr = "";
            old_ProjectFile.close();
            TempImportFile.close();

            //PLAN TO REMOVE, I DONT WANT TO OVERWRITE OLD FILES
            //            TempImportFile.open(QIODevice::ReadOnly  | QIODevice::Text);
            //            QFile new_OpenProjectFile(new_OpenProjectFileName);
            //            new_OpenProjectFile.open(QIODevice::WriteOnly | QIODevice::Text);
            //            //QTextStream t7(&ProjectFile);
            //            TempStr = TempImportFileTextStream.readAll();
            //            ProjectFileTextStream << TempStr;

            //            qDebug() << "Written To Project File:\n" << TempStr;

            //            TempImportFile.close();
            //            new_OpenProjectFile.close();


            //NewProjectName
            QString output_name = user_pihmgis_root_folder+user_pihmgis_project_folder + "/OpenProject.txt";
            //QString output_name = user_pihmgis_root_folder + "/" + NewProjectName + ".pihmgis";
            QFile OpenProjectFile(output_name);
            qDebug() << "Open Project File: " << output_name;


            if ( ! OpenProjectFile.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                qDebug() << "Error: Unable to Open File!";
                //QMessageBox::critical(this,tr("Import Project"),tr("Error: Unable to Create Project File"),QMessageBox::Ok);
                LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Create Project File: </span>")+ user_pihmgis_root_folder +user_pihmgis_project_folder + "/OpenProject.txt"+tr("<br>"));
                ui->textBrowserLogs->setHtml(LogsString);
                ui->textBrowserLogs->repaint();
                return;
            }

            QTextStream OpenProjectFileTextStream(&OpenProjectFile);

            //MOVE OpenProjectFileTextStream << NewProjectFolder << "\n";
            //MOVE OpenProjectFileTextStream << old_ProjectFileName;
            OpenProjectFileTextStream << TempStr;
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

