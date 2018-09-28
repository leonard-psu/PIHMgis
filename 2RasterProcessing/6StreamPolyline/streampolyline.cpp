#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>

#include "streampolyline.h"
#include "ui_streampolyline.h"

#include "0LibsIO/IOProjectFile.h"
#include "0LibsRaster/stream_shape.h"
#include "globals.h"

StreamPolyline::StreamPolyline(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StreamPolyline)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start StreamPolyline";

    try {
        ui->setupUi(this);

        // ** Start: Fill Form If Module Has Been Run Previously
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

        ModuleStringList = ReadModuleLine(ProjectFileName,tr("StreamGrids"));
        if ( ModuleStringList.length() > 0  )
        {
            ui->lineEditStreamGrids->setText(ModuleStringList.at(2));
            ui->lineEditStreamPolyline->setText(ProjectFolder+"/1RasterProcessing/Stream"+ModuleStringList.at(3)+".shp");
        }

        ModuleStringList = ReadModuleLine(ProjectFileName,tr("FlowGrids"));
        if ( ModuleStringList.length() > 0  )
        {
            ui->lineEditFlowDirGrids->setText(ModuleStringList.at(2));
        }

        ModuleStringList = ReadModuleLine(ProjectFileName,tr("StreamPolyline"));

        if ( ModuleStringList.length() > 0 )
        {
            ui->lineEditStreamGrids->setStyleSheet("color: rgb(0, 180, 0);");
            ui->lineEditFlowDirGrids->setStyleSheet("color: rgb(0, 180, 0);");
            ui->lineEditStreamPolyline->setStyleSheet("color: rgb(0, 180, 0);");

            ui->lineEditStreamGrids->setText(ModuleStringList.at(1));
            ui->lineEditFlowDirGrids->setText(ModuleStringList.at(2));
            ui->lineEditStreamPolyline->setText(ModuleStringList.at(3));

        }
        // ** End: Fill Form If Module Has Been Run Previously
        pushButtonSetFocus();

    } catch (...) {
        qDebug() << "Error: StreamPolyline is returning w/o checking";
    }
}

StreamPolyline::~StreamPolyline()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ~StreamPolyline";

    try {
        delete ui;
    } catch (...) {
        qDebug() << "Error: ~StreamPolyline is returning w/o checking";
    }
}

void StreamPolyline::pushButtonSetFocus()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start StreamPolyline::pushButtonSetFocus()";

    try {
        ui->pushButtonStreamGrids->setDefault(false);
        ui->pushButtonFlowDirGrids->setDefault(false);
        ui->pushButtonStreamPolyline->setDefault(false);
        ui->pushButtonRun->setDefault(false);

        if (ui->lineEditStreamGrids->text() == nullptr)
        {
            ui->pushButtonStreamGrids->setDefault(true);
            ui->pushButtonStreamGrids->setFocus();
            return;
        }

        if (ui->lineEditFlowDirGrids->text() == nullptr)
        {
            ui->pushButtonFlowDirGrids->setDefault(true);
            ui->pushButtonFlowDirGrids->setFocus();
            return;
        }

        if (ui->lineEditStreamPolyline->text() == nullptr)
        {
            ui->pushButtonStreamPolyline->setDefault(true);
            ui->pushButtonStreamPolyline->setFocus();
            return;
        }

        ui->pushButtonRun->setDefault(true);
        ui->pushButtonRun->setFocus();

    } catch (...) {
        qDebug() << "Error: StreamPolyline::pushButtonSetFocus() is returning w/o checking";
    }
}

void StreamPolyline::on_pushButtonStreamGrids_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start StreamPolyline::on_pushButtonStreamGrids_clicked()";

    try {

        LogsString = tr("");
        LogsString.append(tr("Processing ... <br>"));
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();
        LogsString = tr("");

        QString ProjectFolder, ProjectFileName;
        QFile ProjectFile(user_pihmgis_root_folder+user_pihmgis_project_folder + "/OpenProject.txt");
        if( ! ProjectFile.open(QIODevice::ReadOnly | QIODevice::Text) )
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

        QString StreamGridFileName = QFileDialog::getOpenFileName(this, "Choose Stream Grid File", ProjectFolder+tr("/1RasterProcessing"), "Stream Grid File(*.asc *.ASC)");
        if ( StreamGridFileName != nullptr)
        {
            ui->lineEditStreamGrids->setStyleSheet("color: black;");

            ui->lineEditStreamGrids->setText(StreamGridFileName);

            if( ui->lineEditStreamPolyline->text() == nullptr )
            {
                QStringList ModuleStringList = ReadModuleLine(ProjectFileName,tr("StreamGrids"));
                if ( ModuleStringList.length() > 0  )
                {
                    ui->lineEditStreamPolyline->setStyleSheet("color: black;");
                    ui->lineEditStreamPolyline->setText(ProjectFolder+"/1RasterProcessing/Stream"+ModuleStringList.at(3)+".shp");
                }
            }
            pushButtonSetFocus();
        }

        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

    } catch (...) {
        qDebug() << "Error: StreamPolyline::on_pushButtonStreamGrids_clicked() is returning w/o checking";
    }
}

void StreamPolyline::on_pushButtonFlowDirGrids_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start StreamPolyline::on_pushButtonFlowDirGrids_clicked()";

    try {
        LogsString = tr("");
        LogsString.append(tr("Processing ... <br>"));
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();
        LogsString = tr("");

        QString ProjectFolder, ProjectFileName;
        QFile ProjectFile(user_pihmgis_root_folder+user_pihmgis_project_folder + "/OpenProject.txt");
        if( ! ProjectFile.open(QIODevice::ReadOnly | QIODevice::Text) )
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

        QString FlowDirGridFileName = QFileDialog::getOpenFileName(this, "Choose Flow Dir Grid File", ProjectFolder+tr("/1RasterProcessing"), "Flow Dir Grid File(*.asc *.ASC)");
        if ( FlowDirGridFileName != NULL)
        {
            ui->lineEditFlowDirGrids->setStyleSheet("color: black;");

            ui->lineEditFlowDirGrids->setText(FlowDirGridFileName);

            pushButtonSetFocus();
        }

        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

    } catch (...) {
        qDebug() << "Error: StreamPolyline::on_pushButtonFlowDirGrids_clicked() is returning w/o checking";
    }
}

void StreamPolyline::on_pushButtonStreamPolyline_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start StreamPolyline::on_pushButtonStreamPolyline_clicked()";

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

        QString StreamPolylineFileName = QFileDialog::getSaveFileName(this, "Choose Stream Polyline", ProjectFolder+"/1RasterProcessing","Stream Polyline File(*.shp)");
        QString tempString = StreamPolylineFileName;
        if ( StreamPolylineFileName != nullptr)
        {
            ui->lineEditStreamPolyline->setStyleSheet("color: black;");

            if( ! (tempString.toLower()).endsWith(".shp") )
            {
                tempString.append(".shp");
                StreamPolylineFileName = tempString;
            }
            ui->lineEditStreamPolyline->setText(StreamPolylineFileName);

            pushButtonSetFocus();
        }

        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();
    } catch (...) {
        qDebug() << "Error: StreamPolyline::on_pushButtonStreamPolyline_clicked() is returning w/o checking";
    }
}

void StreamPolyline::on_pushButtonRun_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start StreamPolyline::on_pushButtonRun_clicked()";

    try {
        LogsString = tr("");
        LogsString.append(tr("Stream Polyline Processing Started ... <br>"));
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
        QFile IOTestFile;

        if( ui->lineEditStreamGrids->text() == nullptr )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Stream Grid Input File Missing </span>")+tr("<br>"));
            runFlag = 0;
        }
        else
        {
            if ( ! CheckFileAccess(ui->lineEditStreamGrids->text(), "ReadOnly") )
            {
                LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Read Access ... </span>")+ui->lineEditStreamGrids->text()+tr("<br>"));
                runFlag = 0;
            }
            LogsString.append(ui->lineEditStreamGrids->text() + " ... <br>");
        }
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

        if( ui->lineEditFlowDirGrids->text() == nullptr )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Flow Dir Grid Input File Missing </span>")+tr("<br>"));
            runFlag = 0;
        }
        else
        {
            if ( ! CheckFileAccess(ui->lineEditFlowDirGrids->text(), "ReadOnly") )
            {
                LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Read Access ... </span>")+ui->lineEditFlowDirGrids->text()+tr("<br>"));
                runFlag = 0;
            }
            LogsString.append(ui->lineEditFlowDirGrids->text() + " ... <br>");
        }
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

        if( ui->lineEditStreamPolyline->text() == nullptr )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Stream Polyline Output File Missing </span>")+tr("<br>"));
            runFlag = 0;
        }
        else
        {
            if ( ! CheckFileAccess(ui->lineEditStreamPolyline->text(), "WriteOnly") )
            {
                LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Write Access ... </span>")+ui->lineEditStreamPolyline->text()+tr("<br>"));
                runFlag = 0;
            }
            LogsString.append(ui->lineEditStreamPolyline->text() + " ... <br>");
        }
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

        if(runFlag == 1)
        {

            LogsString.append("Running Stream Polyline ... <br>");
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();

            QString ShpFileName, DbfFileName;
            ShpFileName = ui->lineEditStreamPolyline->text();
            DbfFileName = ShpFileName;
            DbfFileName.replace(QString(".shp"), QString(".dbf"));
            int ErrorStr = stream_shape((char *)qPrintable(ui->lineEditStreamGrids->text()), (char *)qPrintable(ui->lineEditFlowDirGrids->text()), (char *)qPrintable(ShpFileName), (char *)qPrintable(DbfFileName));
            if( ErrorStr != 0 )
            {
                LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Stream Polyline Processing Failed ... </span>")+tr("<br>"));
                LogsString.append(tr("<span style=\"color:#FF0000\">RETURN CODE: ... </span>")+QString::number(ErrorStr)+tr("<br>"));
                ui->textBrowserLogs->setHtml(LogsString);
                ui->textBrowserLogs->repaint();
                return;
            }


            ProjectIOStringList << "StreamPolyline" << ui->lineEditStreamGrids->text() << ui->lineEditFlowDirGrids->text() << ui->lineEditStreamPolyline->text();

            WriteModuleLine(ProjectFileName, ProjectIOStringList);
            ProjectIOStringList.clear();

            QString StreamFileNameInRaster = ui->lineEditStreamPolyline->text();
            QString StreamFileNameInVector = StreamFileNameInRaster;
            StreamFileNameInVector.replace("1RasterProcessing","2VectorProcessing");

            ProjectIOStringList << "StreamRasterVector" << StreamFileNameInRaster << StreamFileNameInVector;
            WriteModuleLine(ProjectFileName, ProjectIOStringList);
            ProjectIOStringList.clear();

            QFile::remove(StreamFileNameInVector);
            QFile::copy(StreamFileNameInRaster,StreamFileNameInVector);

            StreamFileNameInRaster.replace(".shp",".shx");
            StreamFileNameInVector.replace(".shp",".shx");
            QFile::remove(StreamFileNameInVector);
            QFile::copy(StreamFileNameInRaster,StreamFileNameInVector);

            StreamFileNameInRaster.replace(".shx",".dbf");
            StreamFileNameInVector.replace(".shx",".dbf");
            QFile::remove(StreamFileNameInVector);
            QFile::copy(StreamFileNameInRaster,StreamFileNameInVector);

            StreamFileNameInVector.replace(".dbf",".shp");

            if( ui->checkBoxStreamPolyline->isChecked() == 1 )
            {
                LogsString.append("Loading Data in GIS ... <br>");
                ui->textBrowserLogs->setHtml(LogsString);
                ui->textBrowserLogs->repaint();
            }

            if(ui->checkBoxStreamPolyline->isChecked() == 1)
            {
                if ( ! QDesktopServices::openUrl(QUrl("file://"+StreamFileNameInVector)) )
                    LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Load SHP File in GIS ... </span>")+StreamFileNameInVector+tr("<br>"));
            }

            LogsString.append(tr("<br><b>Stream Polyline Processing Completed.</b>")+tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();

            ui->pushButtonRun->setDefault(false);
            ui->pushButtonClose->setDefault(true);
            ui->pushButtonClose->setFocus();
        }

    } catch (...) {
        qDebug() << "Error: StreamPolyline::on_pushButtonRun_clicked() is returning w/o checking";
    }
}

void StreamPolyline::on_pushButtonClose_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start StreamPolyline::on_pushButtonClose_clicked()";

    try {
        QStringList default_params; default_params << "WORKFLOW2" << "CATPOLY";
        QMetaObject::invokeMethod(parent(),"set_defaults",Q_ARG(QStringList,default_params));
        close();
    } catch (...) {
        qDebug() << "Error: StreamPolyline::on_pushButtonClose_clicked() is returning w/o checking";
    }
}


void StreamPolyline::on_pushButtonHelp_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start StreamPolyline::on_pushButtonHelp_clicked()";

    try {
        //        LogsString = tr("");
        //        if ( ! QDesktopServices::openUrl(QUrl("http://cataract.cee.psu.edu/PIHM/index.php/PIHMgis_3.0#Stream_Polyline")) )
        //            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Load HTTP Link ... </span>")+tr("<br>"));
        //        ui->textBrowserLogs->setHtml(LogsString);
        //        ui->textBrowserLogs->repaint();
    } catch (...) {
        qDebug() << "Error: StreamPolyline::on_pushButtonHelp_clicked() is returning w/o checking";
    }
}
