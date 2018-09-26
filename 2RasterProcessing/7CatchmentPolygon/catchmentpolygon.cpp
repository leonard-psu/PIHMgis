#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>

#include "catchmentpolygon.h"
#include "ui_catchmentpolygon.h"

#include "0LibsIO/IOProjectFile.h"
#include "0LibsRaster/catchment_shape.h"
#include "globals.h"


CatchmentPolygon::CatchmentPolygon(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CatchmentPolygon)
{

    if(print_debug_messages)
        qDebug() << "INFO: Start CatchmentPolygon";

    try {
        ui->setupUi(this);

        // ** Start: Fill Form If Module Has Been Run Previously
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

        ModuleStringList = ReadModuleLine(ProjectFileName,tr("CatchmentGrids"));
        if ( ModuleStringList.length() > 0  )
        {
            ui->lineEditCatchmentGrids->setText(ModuleStringList.at(3));
        }

        ModuleStringList = ReadModuleLine(ProjectFileName,tr("StreamGrids"));
        if ( ModuleStringList.length() > 0  && ui->lineEditCatchmentPolygon->text() == nullptr)
        {
            ui->lineEditCatchmentPolygon->setText(ProjectFolder+"/1RasterProcessing/Catchment"+ModuleStringList.at(3)+".shp");
        }


        ModuleStringList = ReadModuleLine(ProjectFileName,tr("CatchmentPolygon"));

        if ( ModuleStringList.length() > 0 )
        {
            ui->lineEditCatchmentGrids->setStyleSheet("color: rgb(0, 180, 0);");
            ui->lineEditCatchmentPolygon->setStyleSheet("color: rgb(0, 180, 0);");

            ui->lineEditCatchmentGrids->setText(ModuleStringList.at(1));
            ui->lineEditCatchmentPolygon->setText(ModuleStringList.at(2));
        }

        // ** End: Fill Form If Module Has Been Run Previously
        pushButtonSetFocus();

    } catch (...) {
        qDebug() << "Error: CatchmentPolygon is returning w/o checking";
    }
}

CatchmentPolygon::~CatchmentPolygon()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ~CatchmentPolygon";

    try {
        delete ui;
    } catch (...) {
        qDebug() << "Error: ~CatchmentPolygon is returning w/o checking";
    }
}

void CatchmentPolygon::pushButtonSetFocus()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start CatchmentPolygon::pushButtonSetFocus()";

    try {
        ui->pushButtonCatchmentGrids->setDefault(false);
        ui->pushButtonCatchmentPolygon->setDefault(false);
        ui->pushButtonRun->setDefault(false);

        if (ui->lineEditCatchmentGrids->text() == nullptr)
        {
            ui->pushButtonCatchmentGrids->setDefault(true);
            ui->pushButtonCatchmentGrids->setFocus();
            return;
        }
        if (ui->lineEditCatchmentPolygon->text() == nullptr)
        {
            ui->pushButtonCatchmentPolygon->setDefault(true);
            ui->pushButtonCatchmentPolygon->setFocus();
            return;
        }

        ui->pushButtonRun->setDefault(true);
        ui->pushButtonRun->setFocus();

    } catch (...) {
        qDebug() << "Error: CatchmentPolygon::pushButtonSetFocus() is returning w/o checking";
    }
}

void CatchmentPolygon::on_pushButtonCatchmentGrids_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start CatchmentPolygon::on_pushButtonCatchmentGrids_clicked()";

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

        QString CatchmentGridFileName = QFileDialog::getOpenFileName(this, "Choose Catchment Grid File", ProjectFolder+tr("/1RasterProcessing"), "Catchment Grid File(*.asc *.ASC)");
        if ( CatchmentGridFileName != nullptr)
        {
            ui->lineEditCatchmentGrids->setStyleSheet("color: black;");

            ui->lineEditCatchmentGrids->setText(CatchmentGridFileName);

            if( ui->lineEditCatchmentPolygon->text() == nullptr )
            {
                QStringList ModuleStringList = ReadModuleLine(ProjectFileName,tr("StreamGrids"));
                if ( ModuleStringList.length() > 0  )
                {
                    ui->lineEditCatchmentPolygon->setStyleSheet("color: black;");
                    ui->lineEditCatchmentPolygon->setText(ProjectFolder+"/1RasterProcessing/Catchment"+ModuleStringList.at(3)+".shp");
                }
            }
            pushButtonSetFocus();
        }

        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

    } catch (...) {
        qDebug() << "Error: CatchmentPolygon::on_pushButtonCatchmentGrids_clicked() is returning w/o checking";
    }
}

void CatchmentPolygon::on_pushButtonCatchmentPolygon_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start CatchmentPolygon::on_pushButtonCatchmentPolygon_clicked()";

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

        QString CatchmentPolygonFileName = QFileDialog::getSaveFileName(this, "Choose Catchment Polygon", ProjectFolder+"/1RasterProcessing","Catchment Polygon File(*.shp)");
        QString tempString = CatchmentPolygonFileName;
        if ( CatchmentPolygonFileName != nullptr)
        {
            ui->lineEditCatchmentPolygon->setStyleSheet("color: black;");

            if( ! (tempString.toLower()).endsWith(".shp") )
            {
                tempString.append(".shp");
                CatchmentPolygonFileName = tempString;
            }
            ui->lineEditCatchmentPolygon->setText(CatchmentPolygonFileName);

            pushButtonSetFocus();
        }

        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

    } catch (...) {
        qDebug() << "Error: CatchmentPolygon::on_pushButtonCatchmentPolygon_clicked() is returning w/o checking";
    }
}

void CatchmentPolygon::on_pushButtonRun_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start CatchmentPolygon::on_pushButtonRun_clicked()";

    try {

        LogsString = tr("");
        LogsString.append(tr("Catchment Polygon Processing Started ... <br>"));
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
        QFile IOTestFile;

        if( ui->lineEditCatchmentGrids->text() == nullptr )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Catchment Grid Input File Missing </span>")+tr("<br>"));
            runFlag = 0;
        }
        else
        {
            if ( ! CheckFileAccess(ui->lineEditCatchmentGrids->text(), "ReadOnly") )
            {
                LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Read Access ... </span>")+ui->lineEditCatchmentGrids->text()+tr("<br>"));
                runFlag = 0;
            }
            LogsString.append(ui->lineEditCatchmentGrids->text() + " ... <br>");
        }
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();


        if( ui->lineEditCatchmentPolygon->text() == nullptr )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Catchment Polygon Output File Missing </span>")+tr("<br>"));
            runFlag = 0;
        }
        else
        {
            if ( ! CheckFileAccess(ui->lineEditCatchmentPolygon->text(), "WriteOnly") )
            {
                LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Write Access ... </span>")+ui->lineEditCatchmentPolygon->text()+tr("<br>"));
                runFlag = 0;
            }
            LogsString.append(ui->lineEditCatchmentPolygon->text() + " ... <br>");
        }
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

        if(runFlag == 1)
        {

            LogsString.append("Running Catchment Polygon ... <br>");
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();

            QString ShpFileName, DbfFileName;
            ShpFileName = ui->lineEditCatchmentPolygon->text();
            DbfFileName = ShpFileName;
            DbfFileName.replace(QString(".shp"), QString(".dbf"));
            // int ErrorCat = catchment_shape((char *)qPrintable(ui->lineEditCatchmentGrids->text()), "dummy", (char *)qPrintable(ShpFileName), (char *)qPrintable(DbfFileName));
            const char *dummystr = "dummy";
            int ErrorCat = catchment_shape((char *)qPrintable(ui->lineEditCatchmentGrids->text()),(char *)dummystr, (char *)qPrintable(ShpFileName), (char *)qPrintable(DbfFileName));
            if( ErrorCat != 0 )
            {
                LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Stream Polyline Processing Failed ... </span>")+tr("<br>"));
                LogsString.append(tr("<span style=\"color:#FF0000\">RETURN CODE: ... </span>")+QString::number(ErrorCat)+tr("<br>"));
                ui->textBrowserLogs->setHtml(LogsString);
                ui->textBrowserLogs->repaint();
                return;
            }


            ProjectIOStringList << "CatchmentPolygon" << ui->lineEditCatchmentGrids->text() << ui->lineEditCatchmentPolygon->text();
            WriteModuleLine(ProjectFileName, ProjectIOStringList);
            ProjectIOStringList.clear();

            QString CatchmentFileNameInRaster = ui->lineEditCatchmentPolygon->text();
            QString CatchmentFileNameInVector = CatchmentFileNameInRaster;
            CatchmentFileNameInVector.replace("1RasterProcessing","2VectorProcessing");

            ProjectIOStringList << "CatchmentRasterVector" << CatchmentFileNameInRaster << CatchmentFileNameInVector;
            WriteModuleLine(ProjectFileName, ProjectIOStringList);
            ProjectIOStringList.clear();

            QFile::remove(CatchmentFileNameInVector);
            QFile::copy(CatchmentFileNameInRaster,CatchmentFileNameInVector);

            CatchmentFileNameInRaster.replace(".shp",".shx");
            CatchmentFileNameInVector.replace(".shp",".shx");
            QFile::remove(CatchmentFileNameInVector);
            QFile::copy(CatchmentFileNameInRaster,CatchmentFileNameInVector);

            CatchmentFileNameInRaster.replace(".shx",".dbf");
            CatchmentFileNameInVector.replace(".shx",".dbf");
            QFile::remove(CatchmentFileNameInVector);
            QFile::copy(CatchmentFileNameInRaster,CatchmentFileNameInVector);

            CatchmentFileNameInVector.replace(".dbf",".shp");

            if( ui->checkBoxCatchmentPolygon->isChecked() == 1 )
            {
                LogsString.append("Loading Data in GIS ... <br>");
                ui->textBrowserLogs->setHtml(LogsString);
                ui->textBrowserLogs->repaint();
            }

            if(ui->checkBoxCatchmentPolygon->isChecked() == 1)
            {
                if ( ! QDesktopServices::openUrl(QUrl("file://"+CatchmentFileNameInVector)) )
                    LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Load SHP File in GIS ... </span>")+CatchmentFileNameInVector+tr("<br>"));
            }

            LogsString.append(tr("<br><b>Stream Polyline Processing Completed.</b>")+tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();

            ui->pushButtonRun->setDefault(false);
            ui->pushButtonClose->setDefault(true);
            ui->pushButtonClose->setFocus();
        }

    } catch (...) {
        qDebug() << "Error: CatchmentPolygon::on_pushButtonRun_clicked() is returning w/o checking";
    }
}

void CatchmentPolygon::on_pushButtonClose_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start CatchmentPolygon::on_pushButtonClose_clicked()";

    try {

        QStringList default_params; default_params << "WORKFLOW3" << "WORKFLOW8";
        QMetaObject::invokeMethod(parent(),"set_defaults",Q_ARG(QStringList,default_params));
        close();

    } catch (...) {
        qDebug() << "Error: CatchmentPolygon::on_pushButtonClose_clicked() is returning w/o checking";
    }
}

void CatchmentPolygon::on_pushButtonHelp_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start CatchmentPolygon::on_pushButtonHelp_clicked()";

    try {
//        LogsString = tr("");
//        if ( ! QDesktopServices::openUrl(QUrl("http://cataract.cee.psu.edu/PIHM/index.php/PIHMgis_3.0#Catchment_Polygon")) )
//            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Load HTTP Link ... </span>")+tr("<br>"));
//        ui->textBrowserLogs->setHtml(LogsString);
//        ui->textBrowserLogs->repaint();
    } catch (...) {
        qDebug() << "Error: CatchmentPolygon::on_pushButtonHelp_clicked() is returning w/o checking";
    }
}
