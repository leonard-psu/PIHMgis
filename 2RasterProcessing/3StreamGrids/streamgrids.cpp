#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>

#include "streamgrids.h"
#include "ui_streamgrids.h"

#include "0LibsIO/IOProjectFile.h"
#include "0LibsRaster/stream_definition.h"
#include "globals.h"

StreamGrids::StreamGrids(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StreamGrids)
{

    if(print_debug_messages)
        qDebug() << "INFO: Start StreamGrids";

    try {
        ui->setupUi(this);

        QObject::connect(ui->lineEditThreshold,SIGNAL(textChanged(QString)),this,SLOT(on_lineEditThreshold_textChanged()));


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

        ModuleStringList = ReadModuleLine(ProjectFileName,tr("FlowGrids"));
        if ( ModuleStringList.length() > 0  )
        {
            ui->lineEditFlowAccGrids->setText(ModuleStringList.at(3));
            ui->lineEditStreamGrids->setText(ProjectFolder+"/1RasterProcessing/Stream"+ui->lineEditThreshold->text()+".asc");
            ui->lineEditThreshold->setText("");
        }

        ModuleStringList = ReadModuleLine(ProjectFileName,tr("StreamGrids"));

        if ( ModuleStringList.length() > 0 )
        {
            ui->lineEditFlowAccGrids->setStyleSheet("color: rgb(0, 180, 0);");
            ui->lineEditStreamGrids->setStyleSheet("color: rgb(0, 180, 0);");
            ui->lineEditThreshold->setStyleSheet("color: rgb(0, 180, 0);");

            ui->lineEditFlowAccGrids->setText(ModuleStringList.at(1));
            ui->lineEditStreamGrids->setText(ModuleStringList.at(2));
            ui->lineEditThreshold->setText(ModuleStringList.at(3));
        }
        // ** End: Fill Form If Module Has Been Run Previously

        pushButtonSetFocus();

    } catch (...) {
        qDebug() << "Error: StreamGrids is returning w/o checking";
    }
}

StreamGrids::~StreamGrids()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ~StreamGrids";

    try {
        delete ui;
    } catch (...) {
        qDebug() << "Error: ~StreamGrids is returning w/o checking";
    }
}

void StreamGrids::pushButtonSetFocus()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start pushButtonSetFocus";

    try {
        ui->pushButtonFlowAccGrids->setDefault(false);
        ui->pushButtonStreamGrids->setDefault(false);
        ui->pushButtonSuggestMe->setDefault(false);
        ui->pushButtonRun->setDefault(false);

        if (ui->lineEditFlowAccGrids->text() == nullptr)
        {
            ui->pushButtonFlowAccGrids->setDefault(true);
            ui->pushButtonFlowAccGrids->setFocus();
            return;
        }
        if (ui->lineEditStreamGrids->text() == nullptr)
        {
            ui->pushButtonStreamGrids->setDefault(true);
            ui->pushButtonStreamGrids->setFocus();
            return;
        }
        if (ui->lineEditThreshold->text() == nullptr)
        {
            ui->pushButtonSuggestMe->setDefault(true);
            ui->pushButtonSuggestMe->setFocus();
            return;
        }
        ui->pushButtonRun->setDefault(true);
        ui->pushButtonRun->setFocus();

    } catch (...) {
        qDebug() << "Error: pushButtonSetFocus is returning w/o checking";
    }
}

void StreamGrids::on_lineEditThreshold_textChanged()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start on_lineEditThreshold_textChanged";

    try {

        QFile ProjectFile(user_pihmgis_root_folder+user_pihmgis_project_folder + "/OpenProject.txt");
        if ( ! ProjectFile.open(QIODevice::ReadOnly | QIODevice::Text) )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Open File: </span>")+user_pihmgis_root_folder+user_pihmgis_project_folder + "/OpenProject.txt"+tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
        }
        QTextStream ProjectFileTextStream(&ProjectFile);
        QString ProjectFolder   = ProjectFileTextStream.readLine();

        ui->lineEditStreamGrids->setText(ProjectFolder+"/1RasterProcessing/Stream"+ui->lineEditThreshold->text()+".asc");

    } catch (...) {
        qDebug() << "Error: on_lineEditThreshold_textChanged is returning w/o checking";
    }
}

void StreamGrids::on_pushButtonFlowAccGrids_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start on_pushButtonFlowAccGrids_clicked";

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

        QString FlowAccFileName = QFileDialog::getOpenFileName(this, "Choose Flow Acc File", ProjectFolder+tr("/1RasterProcessing"), "DEM Grid File(*.asc *.ASC)");
        if ( FlowAccFileName != nullptr)
        {
            ui->lineEditFlowAccGrids->setStyleSheet("color: black;");

            ui->lineEditFlowAccGrids->setText(FlowAccFileName);

            if( ui->lineEditStreamGrids->text() == nullptr )
            {
                ui->lineEditStreamGrids->setStyleSheet("color: black;");
                ui->lineEditStreamGrids->setText(ProjectFolder+"/1RasterProcessing/Stream"+ui->lineEditThreshold->text()+".asc");
            }

            pushButtonSetFocus();
        }

        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();


    } catch (...) {
        qDebug() << "Error: on_pushButtonFlowAccGrids_clicked is returning w/o checking";
    }

}

void StreamGrids::on_pushButtonStreamGrids_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start on_pushButtonStreamGrids_clicked";

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

        QString StreamGridsFileName = QFileDialog::getSaveFileName(this, "Choose Stream Grid", ProjectFolder+"/1RasterProcessing","Stream Grid File(*.asc)");
        QString tempString = StreamGridsFileName;
        if ( StreamGridsFileName != nullptr)
        {
            ui->lineEditStreamGrids->setStyleSheet("color: black;");

            if( ! (tempString.toLower()).endsWith(".asc") )
            {
                tempString.append(".asc");
                StreamGridsFileName = tempString;
            }
            ui->lineEditStreamGrids->setText(StreamGridsFileName);

            pushButtonSetFocus();
        }

        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();


    } catch (...) {
        qDebug() << "Error: on_pushButtonStreamGrids_clicked is returning w/o checking";
    }
}

void StreamGrids::on_pushButtonSuggestMe_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start on_pushButtonSuggestMe_clicked";

    try {

        LogsString = tr("");
        LogsString.append(tr("Processing ... <br>"));
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();
        LogsString = tr("");

        QString FlowAccFileName = ui->lineEditFlowAccGrids->text();
        QFile FlowAccFile(FlowAccFileName);

        if ( FlowAccFileName == nullptr )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Missing Flow Acc Input File ... </span>")+tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
            return;
        }
        if ( ! FlowAccFile.open(QIODevice::ReadOnly | QIODevice::Text) )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Open File: </span>")+user_pihmgis_root_folder+user_pihmgis_project_folder + "/OpenProject.txt"+tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
            return;
        }

        QTextStream FlowAccFileTextStream(&FlowAccFile);

        QString TempString;
        int tempInt, NumRows, NumColumns, NoData = 0;
        double tempDouble = 0;
        QList<int> FlowAccData;
        int count=0;
        //int flag = 1;

        FlowAccFileTextStream >> TempString; FlowAccFileTextStream >> NumColumns;
        FlowAccFileTextStream >> TempString; FlowAccFileTextStream >> NumRows;
        FlowAccFileTextStream >> TempString; FlowAccFileTextStream >> tempDouble;
        FlowAccFileTextStream >> TempString; FlowAccFileTextStream >> tempDouble;
        //??FlowAccFileTextStream >> tempDouble; FlowAccFileTextStream >> NoData;
        FlowAccFileTextStream >> TempString; FlowAccFileTextStream >> tempDouble;
        FlowAccFileTextStream >> TempString; FlowAccFileTextStream >> NoData;

        qDebug() <<"NumRows = " <<NumRows<<" NumColumns = "<<NumColumns<<" NoData = "<<NoData<<"\n";

        //FlowAccData = (int *)malloc(NumRows*NumColumns* sizeof(int));
        for(int i=0; i<NumRows*NumColumns; i++)
        {
            FlowAccFileTextStream >> tempInt;
            if(tempInt >= 0)
            {
                //FlowAccData[i] = tempInt;
                FlowAccData << tempInt;
                count++;
            }
        }

        qSort(FlowAccData.begin(), FlowAccData.end());

        //qDebug() << FlowAccData;

        qDebug() << "FlowAccData Length = " << FlowAccData.length();
        qDebug() << "Num Threshold Grids = " << FlowAccData.length() - ( (int) (FlowAccData.length() * 0.9937) + 1 );
        qDebug() << "Threshold Acc Value = " << FlowAccData.at( (int) (FlowAccData.length() * 0.9937) + 1);

        ui->lineEditThreshold->setText(QString::number(FlowAccData.at( (int) (FlowAccData.length() * 0.9937) + 1)));

        ui->lineEditThreshold->setStyleSheet("color: black;");

        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

        pushButtonSetFocus();


    } catch (...) {
        qDebug() << "Error: on_pushButtonSuggestMe_clicked is returning w/o checking";
    }
}

void StreamGrids::on_pushButtonRun_clicked()
{

    if(print_debug_messages)
        qDebug() << "INFO: Start on_pushButtonRun_clicked";

    try {

        LogsString = tr("");
        LogsString.append(tr("Stream Grids Processing Started ... <br>"));
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

        if( ui->lineEditFlowAccGrids->text() == nullptr )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Flow Acc Grid Input File Missing </span>")+tr("<br>"));
            runFlag = 0;
        }
        else
        {
            if ( ! CheckFileAccess(ui->lineEditFlowAccGrids->text(), "ReadOnly") )
            {
                LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Read Access ... </span>")+ui->lineEditFlowAccGrids->text()+tr("<br>"));
                runFlag = 0;
            }
            LogsString.append(ui->lineEditFlowAccGrids->text() + " ... <br>");
        }
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

        if( ui->lineEditStreamGrids->text() == nullptr )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Stream Grid Output File Missing </span>")+tr("<br>"));
            runFlag = 0;
        }
        else
        {
            if ( ! CheckFileAccess(ui->lineEditStreamGrids->text(), "WriteOnly") )
            {
                LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Write Access ... </span>")+ui->lineEditStreamGrids->text()+tr("<br>"));
                runFlag = 0;
            }
            LogsString.append(ui->lineEditStreamGrids->text() + " ... <br>");
        }
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

        if( ui->lineEditThreshold->text() == nullptr )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Threshold Input Missing </span>")+tr("<br>"));
            runFlag = 0;
        }
        else
        {
            LogsString.append(tr("Threshold Input") + " ... <br>");
        }
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

        if(runFlag == 1)
        {

            LogsString.append("Running Stream Grids ... <br>");
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();

            const char *dummystr = "dummy";
            //int ErrorStr = stream_definition((char *)qPrintable(ui->lineEditFlowAccGrids->text()), "dummy", (char *)qPrintable(ui->lineEditStreamGrids->text()), 1, ui->lineEditThreshold->text().toInt() );
            int ErrorStr = stream_definition((char *)qPrintable(ui->lineEditFlowAccGrids->text()), (char *)dummystr, (char *)qPrintable(ui->lineEditStreamGrids->text()), 1, ui->lineEditThreshold->text().toInt() );
            if( ErrorStr != 0 )
            {
                LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Stream Grid Processing Failed ... </span>")+tr("<br>"));
                LogsString.append(tr("<span style=\"color:#FF0000\">RETURN CODE: ... </span>")+QString::number(ErrorStr)+tr("<br>"));
                ui->textBrowserLogs->setHtml(LogsString);
                ui->textBrowserLogs->repaint();
                return;
            }


            ProjectIOStringList << "StreamGrids" << ui->lineEditFlowAccGrids->text() << ui->lineEditStreamGrids->text() << ui->lineEditThreshold->text();
            WriteModuleLine(ProjectFileName, ProjectIOStringList);
            ProjectIOStringList.clear();

            if( ui->checkBoxStreamGrids->isChecked() == 1 )
            {
                LogsString.append("Loading Data in GIS ... <br>");
                ui->textBrowserLogs->setHtml(LogsString);
                ui->textBrowserLogs->repaint();
            }

            if(ui->checkBoxStreamGrids->isChecked() == 1)
            {
                if ( ! QDesktopServices::openUrl(QUrl("file://"+ui->lineEditStreamGrids->text())) )
                    LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Load ASC File in GIS ... </span>")+ui->lineEditStreamGrids->text()+tr("<br>"));
            }

            LogsString.append(tr("<br><b>Flow Grids Processing Completed.</b>")+tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();

            ui->pushButtonRun->setDefault(false);
            ui->pushButtonClose->setDefault(true);
            ui->pushButtonClose->setFocus();
        }


    } catch (...) {
        qDebug() << "Error: on_pushButtonRun_clicked is returning w/o checking";
    }
}

void StreamGrids::on_pushButtonClose_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start on_pushButtonClose_clicked";

    try {
        QStringList default_params; default_params << "WORKFLOW2" << "LINKGRIDS";
        QMetaObject::invokeMethod(parent(),"set_defaults",Q_ARG(QStringList,default_params));
        close();
    } catch (...) {
        qDebug() << "Error: on_pushButtonClose_clicked is returning w/o checking";
    }
}

void StreamGrids::on_pushButtonHelp_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start on_pushButtonHelp_clicked";

    try {
//        LogsString = tr("");
//        if ( ! QDesktopServices::openUrl(QUrl("http://cataract.cee.psu.edu/PIHM/index.php/PIHMgis_3.0#Stream_Grids")) )
//            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Load HTTP Link ... </span>")+tr("<br>"));
//        ui->textBrowserLogs->setHtml(LogsString);
//        ui->textBrowserLogs->repaint();
    } catch (...) {
        qDebug() << "Error: on_pushButtonHelp_clicked is returning w/o checking";
    }
}
