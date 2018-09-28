#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>

#include "ibcdatafile.h"
#include "ui_ibcdatafile.h"

#include "0LibsIO/IOProjectFile.h"
#include "globals.h"


IbcDataFile::IbcDataFile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IbcDataFile)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start IbcDataFile";

    try {

        ui->setupUi(this);

        // ** Start: Set Defaults
        QFile ProjectFile(user_pihmgis_root_folder+user_pihmgis_project_folder + "/OpenProject.txt");
        if ( ! ProjectFile.open(QIODevice::ReadOnly | QIODevice::Text) )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Open File: </span>")+user_pihmgis_root_folder+user_pihmgis_project_folder + "/OpenProject.txt"+tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
        }
        QTextStream ProjectFileTextStream(&ProjectFile);
        QString ProjectFolder   = ProjectFileTextStream.readLine();
        QString ProjectFileName = ProjectFileTextStream.readLine();
        ProjectFile.close();

        QStringList ModuleStringList;
        QString TempFileName;

        // ** Data Model INPUT File Name
        ModuleStringList = ReadModuleLine(ProjectFileName,tr("TINShapeLayer"));
        if ( ModuleStringList.length() > 0  )
        {
            TempFileName = ModuleStringList.at(3);
            TempFileName = TempFileName.right(TempFileName.length()-TempFileName.lastIndexOf("/")-1);

            TempFileName.replace( QString(".shp"), QString(".ibc") );
            ui->lineEditIbcDataFile->setText(ProjectFolder+"/4DataModelLoader/"+TempFileName);
        }

        ModuleStringList = ReadModuleLine(ProjectFileName,tr("MeshDataFile"));
        if ( ModuleStringList.length() > 0  )
        {
            TempFileName = ModuleStringList.at(9);
            ui->lineEditIbcDataFile->setText(ProjectFolder+"/4DataModelLoader/"+TempFileName+".ibc");
        }
        // ** End: Set Defaults

        // ** Start: Fill Form If Module Has Been Run Previously

        ModuleStringList = ReadModuleLine(ProjectFileName,tr("IbcDataFile"));

        if ( ModuleStringList.length() > 0 )
        {
            ui->lineEditIbcDataFile->setStyleSheet("color: rgb(0, 180, 0);");

            ui->lineEditIbcDataFile->setText(ModuleStringList.at(1));
        }
        // ** End: Fill Form If Module Has Been Run Previously

        pushButtonSetFocus();

    } catch (...) {
        qDebug() << "Error: IbcDataFile is returning w/o checking";
    }
}

IbcDataFile::~IbcDataFile()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ~IbcDataFile";

    try {
        delete ui;
    } catch (...) {
        qDebug() << "Error: ~IbcDataFile is returning w/o checking";
    }
}

void IbcDataFile::pushButtonSetFocus()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start IbcDataFile::pushButtonSetFocus()";

    try {
        ui->pushButtonIbcDataFile->setDefault(false);

        if (ui->lineEditIbcDataFile->text() == nullptr)
        {
            ui->pushButtonIbcDataFile->setDefault(true);
            ui->pushButtonIbcDataFile->setFocus();
            return;
        }

        ui->pushButtonRun->setDefault(true);
        ui->pushButtonRun->setFocus();

    } catch (...) {
        qDebug() << "Error: IbcDataFile::pushButtonSetFocus() is returning w/o checking";
    }
}

void IbcDataFile::on_pushButtonIbcDataFile_clicked()
{

    if(print_debug_messages)
        qDebug() << "INFO: Start IbcDataFile::on_pushButtonIbcDataFile_clicked()";

    try {
        LogsString = tr("");
        LogsString.append(tr("Processing ... <br>"));
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();
        LogsString = tr("");

        QString ProjectFolder, ProjectFileName;
        QFile ProjectFile(user_pihmgis_root_folder+user_pihmgis_project_folder + "/OpenProject.txt");
        if ( ! ProjectFile.open(QIODevice::ReadOnly | QIODevice::Text) )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Open File: </span>")+user_pihmgis_root_folder+user_pihmgis_project_folder + "/OpenProject.txt"+tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
            return;
        }
        QTextStream ProjectFileTextStream(&ProjectFile);
        ProjectFolder   = ProjectFileTextStream.readLine();
        ProjectFileName = ProjectFileTextStream.readLine();
        ProjectFile.close();
        qDebug() << ProjectFolder;

        QString IbcDataFileName = QFileDialog::getSaveFileName(this, "Choose IBC Data File Name", ProjectFolder+"/4DataModelLoader","IBC Data File(*.ibc)");
        QString tempString = IbcDataFileName;
        if ( IbcDataFileName != nullptr)
        {
            ui->lineEditIbcDataFile->setStyleSheet("color: black;");

            if( ! (tempString.toLower()).endsWith(".ibc") )
            {
                tempString.append(".ibc");
                IbcDataFileName = tempString;
            }
            ui->lineEditIbcDataFile->setText(IbcDataFileName);

            pushButtonSetFocus();
        }

        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

    } catch (...) {
        qDebug() << "Error: IbcDataFile::on_pushButtonIbcDataFile_clicked() is returning w/o checking";
    }
}

int IbcDataFile::ibc_data_file( QString IbcDataFileName )
{
    if(print_debug_messages)
        qDebug() << "INFO: Start IbcDataFile::ibc_data_file()";

    try {
        QFile IbcFile( IbcDataFileName );
        if ( ! IbcFile.open(QIODevice::WriteOnly | QIODevice::Text) )
            return 137;

        QTextStream IbcFileTextStream(&IbcFile);

        IbcFileTextStream << "0\t0\n0";

        IbcFile.close();

    } catch (...) {
        qDebug() << "Error: IbcDataFile::ibc_data_file() is returning w/o checking";
    }

    return 0;
}

void IbcDataFile::on_pushButtonRun_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start IbcDataFile::on_pushButtonRun_clicked()";

    try {
        LogsString = tr("");
        LogsString.append(tr("Ibc Data File Processing Started ... <br>"));
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

        QString ProjectFolder, ProjectFileName;
        QFile ProjectFile(user_pihmgis_root_folder+user_pihmgis_project_folder + "/OpenProject.txt");
        ProjectFile.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream ProjectFileTextStream(&ProjectFile);
        ProjectFolder   = ProjectFileTextStream.readLine();
        ProjectFileName = ProjectFileTextStream.readLine();
        ProjectFile.close();


        LogsString.append(tr("Verifying Data Files ... <br>"));
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

        int runFlag = 1;

        if( ui->lineEditIbcDataFile->text() == nullptr )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Ibc Data Output File Missing </span>")+tr("<br>"));
            runFlag = 0;
        }
        else
        {
            if ( ! CheckFileAccess(ui->lineEditIbcDataFile->text(), "WriteOnly") )
            {
                LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Write Access ... </span>")+ui->lineEditIbcDataFile->text()+tr("<br>"));
                runFlag = 0;
            }
            LogsString.append(ui->lineEditIbcDataFile->text() + " ... <br>");
        }
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();


        if(runFlag == 1)
        {

            LogsString.append("Running Ibc Data File ... <br>");
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();

            int ErrorIbc = ibc_data_file( ui->lineEditIbcDataFile->text() );

            if( ErrorIbc != 0 )
            {
                LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Ibc Data File Processing Failed ... </span>")+tr("<br>"));
                LogsString.append(tr("<span style=\"color:#FF0000\">RETURN CODE IBC: ... </span>")+QString::number(ErrorIbc)+tr("<br>"));
                ui->textBrowserLogs->setHtml(LogsString);
                ui->textBrowserLogs->repaint();
                return;
            }

            ProjectIOStringList << "IbcDataFile" << ui->lineEditIbcDataFile->text();
            WriteModuleLine(ProjectFileName, ProjectIOStringList);
            ProjectIOStringList.clear();

            LogsString.append(tr("<br><b>Ibc Data File Processing Complete.</b>")+tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();

            ui->pushButtonRun->setDefault(false);
            ui->pushButtonClose->setDefault(true);
            ui->pushButtonClose->setFocus();
        }

    } catch (...) {
        qDebug() << "Error: IbcDataFile::on_pushButtonRun_clicked() is returning w/o checking";
    }
}

void IbcDataFile::on_pushButtonClose_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start IbcDataFile::on_pushButtonClose_clicked()";

    try {
        QStringList default_params; default_params << "WORKFLOW5" << "PARA";
        QMetaObject::invokeMethod(parent(),"set_defaults",Q_ARG(QStringList,default_params));
        close();
    } catch (...) {
        qDebug() << "Error: IbcDataFile::on_pushButtonClose_clicked() is returning w/o checking";
    }
}

void IbcDataFile::on_pushButtonHelp_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start IbcDataFile::on_pushButtonHelp_clicked()";

    try {
//        LogsString = tr("");
//        if ( ! QDesktopServices::openUrl(QUrl("http://cataract.cee.psu.edu/PIHM/index.php/PIHMgis_3.0#ibc_Data_File")) )
//            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Load HTTP Link ... </span>")+tr("<br>"));
//        ui->textBrowserLogs->setHtml(LogsString);
//        ui->textBrowserLogs->repaint();
    } catch (...) {
        qDebug() << "Error: IbcDataFile::on_pushButtonHelp_clicked() is returning w/o checking";
    }
}
