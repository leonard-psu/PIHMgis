#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>

#include "soildatafile.h"
#include "ui_soildatafile.h"

#include "0LibsIO/IOProjectFile.h"
#include "0LibsOther/pedo_transfer_functions.h"
#include "globals.h"


SoilDataFile::SoilDataFile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SoilDataFile)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start SoilDataFile";

    try {
        ui->setupUi(this);

        // ** Start: Set Defaults
        QFile ProjectFile(user_pihmgis_root_folder+"/.PIHMgis/OpenProject.txt");
        if ( ! ProjectFile.open(QIODevice::ReadOnly | QIODevice::Text) )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Open File: </span>")+user_pihmgis_root_folder+"/.PIHMgis/OpenProject.txt"+tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
        }
        QTextStream ProjectFileTextStream(&ProjectFile);
        QString ProjectFolder   = ProjectFileTextStream.readLine();
        QString ProjectFileName = ProjectFileTextStream.readLine();
        ProjectFile.close();

        QStringList ModuleStringList;
        QString TempFileName;

        // ** Data Model OUTPUT File Name
        ModuleStringList = ReadModuleLine(ProjectFileName,tr("TINShapeLayer"));
        if ( ModuleStringList.length() > 0  )
        {
            TempFileName = ModuleStringList.at(3);
            TempFileName = TempFileName.right(TempFileName.length()-TempFileName.lastIndexOf("/")-1);
            TempFileName.replace( QString(".shp"), QString(".soil") );
            ui->lineEditSoilDataFile->setText(ProjectFolder+"/4DataModelLoader/"+TempFileName);
        }

        ModuleStringList = ReadModuleLine(ProjectFileName,tr("MeshDataFile"));
        if ( ModuleStringList.length() > 0  )
        {
            TempFileName = ModuleStringList.at(9);
            ui->lineEditSoilDataFile->setText(ProjectFolder+"/4DataModelLoader/"+TempFileName+".soil");
        }
        // ** End: Set Defaults


        // ** Start: Fill Form If Module Has Been Run Previously

        ModuleStringList = ReadModuleLine(ProjectFileName,tr("SoilDataFile"));

        if ( ModuleStringList.length() > 0 )
        {
            ui->lineEditSoilTextureFile->setStyleSheet("color: rgb(0, 180, 0);");
            ui->lineEditSoilDataFile->setStyleSheet("color: rgb(0, 180, 0);");

            ui->lineEditSoilTextureFile->setText(ModuleStringList.at(1));
            ui->lineEditSoilDataFile->setText(ModuleStringList.at(2));

        }
        // ** End: Fill Form If Module Has Been Run Previously

        pushButtonSetFocus();

    } catch (...) {
        qDebug() << "Error: SoilDataFile is returning w/o checking";
    }

}

SoilDataFile::~SoilDataFile()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ~SoilDataFile";

    try {
        delete ui;
    } catch (...) {
        qDebug() << "Error: ~SoilDataFile is returning w/o checking";
    }
}

void SoilDataFile::pushButtonSetFocus()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start SoilDataFile::pushButtonSetFocus()";

    try {
        ui->pushButtonSoilTextureFile->setDefault(false);
        ui->pushButtonSoilDataFile->setDefault(false);

        if (ui->lineEditSoilTextureFile->text() == nullptr)
        {
            ui->pushButtonSoilTextureFile->setDefault(true);
            ui->pushButtonSoilTextureFile->setFocus();
            return;
        }

        if (ui->lineEditSoilDataFile->text() == nullptr)
        {
            ui->pushButtonSoilDataFile->setDefault(true);
            ui->pushButtonSoilDataFile->setFocus();
            return;
        }

        ui->pushButtonRun->setDefault(true);
        ui->pushButtonRun->setFocus();
    } catch (...) {
        qDebug() << "Error: SoilDataFile::pushButtonSetFocus() is returning w/o checking";
    }
}

void SoilDataFile::on_pushButtonSoilTextureFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start SoilDataFile::on_pushButtonSoilTextureFile_clicked()";

    try {
        LogsString = tr("");
        LogsString.append(tr("Processing ... <br>"));
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();
        LogsString = tr("");

        QString ProjectFolder, ProjectFileName;
        QFile ProjectFile(user_pihmgis_root_folder+"/.PIHMgis/OpenProject.txt");
        if( ! ProjectFile.open(QIODevice::ReadOnly | QIODevice::Text) )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Open File: </span>")+user_pihmgis_root_folder+"/.PIHMgis/OpenProject.txt"+tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
            return;
        }

        QTextStream ProjectFileTextStream(&ProjectFile);
        ProjectFolder   = ProjectFileTextStream.readLine();
        ProjectFileName = ProjectFileTextStream.readLine();
        ProjectFile.close();
        qDebug() << ProjectFolder;

        QString SoilTextureFileName = QFileDialog::getOpenFileName(this, "Soil Texture File Name", ProjectFolder, "Soil Texture File(*.txt *.TXT)");

        if ( SoilTextureFileName != nullptr)
        {
            ui->lineEditSoilTextureFile->setStyleSheet("color: black;");
            ui->lineEditSoilTextureFile->setText(SoilTextureFileName);

            pushButtonSetFocus();
        }

        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();
    } catch (...) {
        qDebug() << "Error: SoilDataFile::on_pushButtonSoilTextureFile_clicked() is returning w/o checking";
    }
}

void SoilDataFile::on_pushButtonSoilDataFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start SoilDataFile::on_pushButtonSoilDataFile_clicked()";

    try {
        LogsString = tr("");
        LogsString.append(tr("Processing ... <br>"));
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();
        LogsString = tr("");

        QString ProjectFolder, ProjectFileName;
        QFile ProjectFile(user_pihmgis_root_folder+"/.PIHMgis/OpenProject.txt");
        if ( ! ProjectFile.open(QIODevice::ReadOnly | QIODevice::Text) )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Open File: </span>")+user_pihmgis_root_folder+"/.PIHMgis/OpenProject.txt"+tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
            return;
        }
        QTextStream ProjectFileTextStream(&ProjectFile);
        ProjectFolder   = ProjectFileTextStream.readLine();
        ProjectFileName = ProjectFileTextStream.readLine();
        ProjectFile.close();
        qDebug() << ProjectFolder;

        QString SoilDataFileName = QFileDialog::getSaveFileName(this, "Choose Soil Data File Name", ProjectFolder+"/4DataModelLoader","Soil Data File(*.soil)");
        QString tempString = SoilDataFileName;
        if ( SoilDataFileName != nullptr)
        {
            ui->lineEditSoilDataFile->setStyleSheet("color: black;");

            if( ! (tempString.toLower()).endsWith(".soil") )
            {
                tempString.append(".soil");
                SoilDataFileName = tempString;
            }
            ui->lineEditSoilDataFile->setText(SoilDataFileName);

            pushButtonSetFocus();
        }

        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();
    } catch (...) {
        qDebug() << "Error: SoilDataFile::on_pushButtonSoilDataFile_clicked() is returning w/o checking";
    }
}

void SoilDataFile::on_pushButtonRun_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start SoilDataFile::on_pushButtonRun_clicked()";

    try {
        LogsString = tr("");
        LogsString.append(tr("Soil Data File Processing Started ... <br>"));
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

        QString ProjectFolder, ProjectFileName;
        QFile ProjectFile(user_pihmgis_root_folder+"/.PIHMgis/OpenProject.txt");
        ProjectFile.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream ProjectFileTextStream(&ProjectFile);
        ProjectFolder   = ProjectFileTextStream.readLine();
        ProjectFileName = ProjectFileTextStream.readLine();
        ProjectFile.close();


        LogsString.append(tr("Verifying Data Files ... <br>"));
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

        int runFlag = 1;

        if( ui->lineEditSoilTextureFile->text() == nullptr )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Soil Texture Input File Missing </span>")+tr("<br>"));
            runFlag = 0;
        }
        else
        {
            if ( ! CheckFileAccess(ui->lineEditSoilTextureFile->text(), "ReadOnly") )
            {
                LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Read Access ... </span>")+ui->lineEditSoilTextureFile->text()+tr("<br>"));
                runFlag = 0;
            }
            LogsString.append(ui->lineEditSoilTextureFile->text() + " ... <br>");
        }
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();


        if( ui->lineEditSoilDataFile->text() == nullptr )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Soil Data Output File Missing </span>")+tr("<br>"));
            runFlag = 0;
        }
        else
        {
            if ( ! CheckFileAccess(ui->lineEditSoilDataFile->text(), "WriteOnly") )
            {
                LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Write Access ... </span>")+ui->lineEditSoilDataFile->text()+tr("<br>"));
                runFlag = 0;
            }
            LogsString.append(ui->lineEditSoilDataFile->text() + " ... <br>");
        }
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();


        if(runFlag == 1)
        {

            LogsString.append("Running Soil Data File ... <br>");
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();

            int ErrorSoil = Soil_PedoTransferFunction( ui->lineEditSoilTextureFile->text(), ui->lineEditSoilDataFile->text() );

            if( ErrorSoil != 0 )
            {
                LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Soil Data File Processing Failed ... </span>")+tr("<br>"));
                LogsString.append(tr("<span style=\"color:#FF0000\">RETURN CODE SOIL: ... </span>")+QString::number(ErrorSoil)+tr("<br>"));
                ui->textBrowserLogs->setHtml(LogsString);
                ui->textBrowserLogs->repaint();
                return;
            }

            ProjectIOStringList << "SoilDataFile" << ui->lineEditSoilTextureFile->text() << ui->lineEditSoilDataFile->text();
            WriteModuleLine(ProjectFileName, ProjectIOStringList);
            ProjectIOStringList.clear();

            LogsString.append(tr("<br><b>Soil Data File Processing Complete.</b>")+tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();

            ui->pushButtonRun->setDefault(false);
            ui->pushButtonClose->setDefault(true);
            ui->pushButtonClose->setFocus();
        }
    } catch (...) {
        qDebug() << "Error: SoilDataFile::on_pushButtonRun_clicked() is returning w/o checking";
    }
}

void SoilDataFile::on_pushButtonClose_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start SoilDataFile::on_pushButtonClose_clicked()";

    try {
        QStringList default_params; default_params << "WORKFLOW5" << "GEOL";
        QMetaObject::invokeMethod(parent(),"set_defaults",Q_ARG(QStringList,default_params));
        close();
    } catch (...) {
        qDebug() << "Error: SoilDataFile::on_pushButtonClose_clicked() is returning w/o checking";
    }
}


void SoilDataFile::on_pushButtonHelp_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start SoilDataFile::on_pushButtonHelp_clicked()";

    try {
//        LogsString = tr("");
//        if ( ! QDesktopServices::openUrl(QUrl("http://cataract.cee.psu.edu/PIHM/index.php/PIHMgis_3.0#soil_Data_File")) )
//            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Load HTTP Link ... </span>")+tr("<br>"));
//        ui->textBrowserLogs->setHtml(LogsString);
//        ui->textBrowserLogs->repaint();
    } catch (...) {
        qDebug() << "Error: SoilDataFile::on_pushButtonHelp_clicked() is returning w/o checking";
    }
}
