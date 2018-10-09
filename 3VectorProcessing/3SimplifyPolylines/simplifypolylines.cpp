#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>

#include "simplifypolylines.h"
#include "ui_simplifypolylines.h"

#include "0LibsIO/IOProjectFile.h"
#include "0LibsVector/simplify_shape.h"
#include "globals.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SimplifyPolylines Constructor
// Parent is Main Window, filename is the open project text file used to store project details
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SimplifyPolylines::SimplifyPolylines(QWidget *parent, QString filename) :
    QDialog(parent),
    ui(new Ui::SimplifyPolylines)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start SimplifyPolylines";

    try {

        ui->setupUi(this);

        filename_open_project = filename;
        bool found_file = false;

        QFile ProjectFile(filename_open_project);
        if ( ! ProjectFile.open(QIODevice::ReadOnly | QIODevice::Text) )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Open File: </span>") + filename_open_project + tr("<br>"));
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
        qDebug() << "Error: SimplifyPolylines is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SimplifyPolylines Deconstructor
// Todo: Check for memory leaks
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SimplifyPolylines::~SimplifyPolylines()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ~SimplifyPolylines";

    try {
        delete ui;
    } catch (...) {
        qDebug() << "Error: ~SimplifyPolylines is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Load_Project_Settings
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SimplifyPolylines::Load_Project_Settings()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start SimplifyPolylines::Load_Project_Settings";

    try {
        ui->tableWidget->blockSignals(true);

        QString InpPolygonFileName, OutPolylineFileName;
        QTableWidgetItem *NewTableItem;

        QStringList ModuleStringList = ReadModuleLine(filename_open_project,tr("FlowGrids"));
        if ( ModuleStringList.length() > 0  )
        {
            DEMResolution = ModuleStringList.at(4).toInt();
            qDebug() << "DEM Resolution = " << DEMResolution;
        }

        ModuleStringList = ReadModuleLine(filename_open_project,tr("StreamRasterVector"));
        if ( ModuleStringList.length() > 0  )
        {
            ui->tableWidget->insertRow(ui->tableWidget->rowCount());

            int rowlen = ui->tableWidget->rowCount()-1;
            if(rowlen >= 0)
            {
                QString file1 = ModuleStringList.at(2);
                OutPolylineFileName = file1;
                OutPolylineFileName.replace(QString(".shp"), QString("_sln") + QString::number(DEMResolution) + QString(".shp"));

                bool file1_check = Check_File_Valid(file1);
                bool file2_check = Check_File_Valid(OutPolylineFileName);

                qDebug() << file1 << " " << file1_check;
                qDebug() << OutPolylineFileName << " " << file2_check;


                NewTableItem = new QTableWidgetItem(file1);
                ui->tableWidget->setItem(rowlen,0,NewTableItem);
                if(file1_check)
                {
                    ui->tableWidget->item(rowlen,0)->setTextColor(Qt::black);
                }
                else
                {
                    LogsString.append(tr("<span style=\"color:#FF0000\">Error: ") + file1 + tr(" input does not exist. </span>") +tr("<br>"));
                    ui->tableWidget->item(rowlen,0)->setTextColor(Qt::red);
                }

                NewTableItem = new QTableWidgetItem(QString::number(DEMResolution));
                ui->tableWidget->setItem(rowlen,1,NewTableItem);

                NewTableItem = new QTableWidgetItem(OutPolylineFileName);
                ui->tableWidget->setItem(rowlen,2,NewTableItem);
                if(!file2_check)
                {
                    ui->tableWidget->item(rowlen,2)->setTextColor(Qt::black);
                }
                else
                {
                    LogsString.append(tr("<span style=\"color:#FF0000\">Warning: ") + OutPolylineFileName + tr(" output already exists. </span>") +tr("<br>"));
                    ui->tableWidget->item(rowlen,2)->setTextColor(Qt::red);
                }
            }

            OutPolylineFileName = "";
        }

        ModuleStringList = ReadModuleLine(filename_open_project,tr("PolygonToPolylines"));
        if ( ModuleStringList.length() > 0  )
        {
            for (int i=1; i+1<ModuleStringList.length(); i=i+2)
            {
                ui->tableWidget->insertRow(ui->tableWidget->rowCount());

                QString file1 = ModuleStringList.at(i);
                OutPolylineFileName = ModuleStringList.at(i+1);
                OutPolylineFileName.replace(QString(".shp"),QString("_sln")+QString::number(2*DEMResolution)+QString(".shp"));

                bool file1_check = Check_File_Valid(file1);
                bool file2_check = Check_File_Valid(OutPolylineFileName);

                int rowlen = ui->tableWidget->rowCount()-1;
                if(rowlen >= 0)
                {
                    NewTableItem = new QTableWidgetItem(file1);
                    ui->tableWidget->setItem(rowlen,0,NewTableItem);
                    if(file1_check)
                    {
                        ui->tableWidget->item(rowlen,0)->setTextColor(Qt::black);
                    }
                    else
                    {
                        LogsString.append(tr("<span style=\"color:#FF0000\">Error: ") + file1 + tr(" input does not exist. </span>") +tr("<br>"));
                        ui->tableWidget->item(rowlen,0)->setTextColor(Qt::red);
                    }

                    NewTableItem = new QTableWidgetItem(QString::number(2*DEMResolution));
                    ui->tableWidget->setItem(rowlen,1,NewTableItem);

                    NewTableItem = new QTableWidgetItem(OutPolylineFileName);
                    ui->tableWidget->setItem(rowlen,2,NewTableItem);

                    if(!file2_check)
                    {
                        ui->tableWidget->item(rowlen,2)->setTextColor(Qt::black);
                    }
                    else
                    {
                        LogsString.append(tr("<span style=\"color:#FF0000\">Warning: ") + OutPolylineFileName + tr(" output already exists. </span>") +tr("<br>"));
                        ui->tableWidget->item(rowlen,2)->setTextColor(Qt::red);
                    }

                    OutPolylineFileName = "";
                }
            }
        }


        ModuleStringList = ReadModuleLine(filename_open_project,tr("SimplifyPolylines"));
        if ( ModuleStringList.length() > 0 )
        {
            while( ui->tableWidget->rowCount() )
                ui->tableWidget->removeRow( ui->tableWidget->rowCount()-1 );

            ui->tableWidget->setRowCount(0);
            qDebug() << "Length = " << ModuleStringList.length();

            for (int i=1; i+1<ModuleStringList.length(); i=i+3)
            {
                ui->tableWidget->insertRow(ui->tableWidget->rowCount());

                int rowlen = ui->tableWidget->rowCount()-1;
                if(rowlen >= 0)
                {
                    QString file1 = ModuleStringList.at(i);
                    QString file2 = ModuleStringList.at(i+1);
                    qDebug() << "file1 = " << file1;
                    qDebug() << "file2 = " << file2;

                    bool file1_check = Check_File_Valid(file1);
                    bool file2_check = Check_File_Valid(file2);

                    qDebug() << file1 << " " << file1_check;
                    qDebug() << OutPolylineFileName << " " << file2_check;

                    NewTableItem = new QTableWidgetItem(file1);
                    ui->tableWidget->setItem(rowlen,0,NewTableItem);
                    if(file1_check)
                    {
                        ui->tableWidget->item(rowlen,0)->setTextColor(Qt::black);
                    }
                    else
                    {
                        LogsString.append(tr("<span style=\"color:#FF0000\">Error: ") + file2 + tr(" input does not exist. </span>") +tr("<br>"));
                        ui->tableWidget->item(rowlen,0)->setTextColor(Qt::red);
                    }
                    ui->tableWidget->item(rowlen,0)->setTextAlignment(Qt::AlignRight);
                    ui->tableWidget->item(rowlen,0)->setTextAlignment(Qt::AlignVCenter);

                    NewTableItem = new QTableWidgetItem(file2);
                    ui->tableWidget->setItem(rowlen,2,NewTableItem);
                    if(file2_check)
                    {
                        LogsString.append(tr("<span style=\"color:#FF0000\">Warning: ") + file2 + tr(" output already exists. </span>") +tr("<br>"));
                        ui->tableWidget->item(rowlen,2)->setTextColor(Qt::red);
                    }
                    else
                    {
                        LogsString.append(tr("<span style=\"color:#FF0000\">INFO: ") + file2 + tr(" does not exist. </span>") +tr("<br>"));
                        ui->tableWidget->item(rowlen,2)->setTextColor(Qt::black);
                    }
                    ui->tableWidget->item(rowlen,2)->setTextAlignment(Qt::AlignRight);
                    ui->tableWidget->item(rowlen,2)->setTextAlignment(Qt::AlignVCenter);

                    NewTableItem = new QTableWidgetItem(ModuleStringList.at(i+2));
                    ui->tableWidget->setItem(rowlen,1,NewTableItem);
                    ui->tableWidget->item(rowlen,1)->setTextColor(QColor(0, 180, 0));
                    ui->tableWidget->item(rowlen,1)->setTextAlignment(Qt::AlignRight);
                    ui->tableWidget->item(rowlen,1)->setTextAlignment(Qt::AlignVCenter);
                }
                //qDebug() << i << " " << InpPolygonFileName << " <> " << OutPolygonFileName << "\n";
            }

        }

        ui->tableWidget->resizeColumnsToContents();
        ui->tableWidget->blockSignals(false);
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

        pushButtonSetFocus();
    } catch (...) {
        qDebug() << "Error: SimplifyPolylines::Load_Project_Settings is returning w/o checking";
        return false;
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to focus button selection (needed for users w/o mouse)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SimplifyPolylines::pushButtonSetFocus()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start SimplifyPolylines::pushButtonSetFocus()";

    try {
        ui->pushButtonAdd->setDefault(false);
        ui->pushButtonRun->setDefault(false);

        if ( ui->tableWidget->rowCount() == 0 )
        {
            ui->pushButtonAdd->setDefault(true);
            ui->pushButtonAdd->setFocus();
            return;
        }

        ui->pushButtonRun->setDefault(true);
        ui->pushButtonRun->setFocus();

    } catch (...) {
        qDebug() << "Error: SimplifyPolylines::pushButtonSetFocus() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to assist if input file exists (returns true) or does not (returns false)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SimplifyPolylines::Check_File_Valid(QString file)
{
    if(print_debug_messages)
        qDebug() << "INFO: Check_File_Valid()";

    bool result = false;

    try {

        if( fileExists(file) )
        {
            result = true;

            qint64 size = file_Size(file);
            qDebug() << "size " << size;

            if( size < 1)
            {
                LogsString.append(tr("<span style=\"color:#FF0000\">Error: Check_File_Valid failed, file : </span>") + file +tr("<br>"));
                LogsString.append(tr("<span style=\"color:#FF0000\">Error: Check_File_Valid failed, invalid file size: </span>") + size +tr("<br>"));
                ui->textBrowserLogs->setHtml(LogsString);
                ui->textBrowserLogs->repaint();
                result = false;
            }

        }

    } catch (...) {
        qDebug() << "Error: Check_File_Valid is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to clear message log
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SimplifyPolylines::Clear_Log()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start SimplifyPolylines::Clear_Log()";

    try {

        LogsString = tr("");
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

    } catch (...) {
        qDebug() << "Error: SimplifyPolylines::Clear_Log() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Add Button Clicked Event  (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SimplifyPolylines::on_pushButtonAdd_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start SimplifyPolylines::on_pushButtonAdd_clicked()";

    try {

        Clear_Log();

        QTableWidgetItem *NewTableItem;
        QStringList InputPolygonsFileNames = QFileDialog::getOpenFileNames(this, "Choose Shape Files", user_pihmgis_root_folder + tr("/.."), "Shape File(*.shp *.SHP)");

        if ( InputPolygonsFileNames.length() > 0)
        {
            for (int i=0; i<InputPolygonsFileNames.length(); i++)
            {
                ui->tableWidget->insertRow(ui->tableWidget->rowCount());

                QString file1 = InputPolygonsFileNames.at(i);
                QString file2 = file1.replace(QString(".shp"),QString("_sln")+QString::number(2*DEMResolution)+QString(".shp"));
                bool file1_check = Check_File_Valid(file1);
                bool file2_check = Check_File_Valid(file2);

                int rowlen = ui->tableWidget->rowCount()-1;
                if(file1.length() > 0 )
                {
                    NewTableItem = new QTableWidgetItem(file1);
                    ui->tableWidget->setItem(rowlen,0,NewTableItem);
                    if(file1_check)
                    {
                        ui->tableWidget->item(rowlen,0)->setTextColor(Qt::black);
                    }
                    else
                    {
                        LogsString.append(tr("<span style=\"color:#FF0000\">Error: ") + file1 + tr(" input does not exist. </span>") +tr("<br>"));
                        ui->tableWidget->item(rowlen,0)->setTextColor(Qt::red);
                    }

                    ui->tableWidget->item(rowlen,0)->setTextAlignment(Qt::AlignRight);
                    ui->tableWidget->item(rowlen,0)->setTextAlignment(Qt::AlignVCenter);
                }

                if(file2.length() > 0 )
                {
                    NewTableItem = new QTableWidgetItem(file2);
                    ui->tableWidget->setItem(rowlen,2,NewTableItem);
                    if(file2_check)
                    {
                        LogsString.append(tr("<span style=\"color:#FF0000\">Warning: ") + file2 + tr(" output already exists. </span>") +tr("<br>"));
                        ui->tableWidget->item(rowlen,2)->setTextColor(Qt::red);
                    }
                    else
                    {
                        LogsString.append(tr("<span style=\"color:#FF0000\">INFO: ") + file2 + tr(" does not exist. </span>") +tr("<br>"));
                        ui->tableWidget->item(rowlen,2)->setTextColor(Qt::black);
                    }
                    ui->tableWidget->item(rowlen,2)->setTextAlignment(Qt::AlignRight);
                    ui->tableWidget->item(rowlen,2)->setTextAlignment(Qt::AlignVCenter);
                }

                NewTableItem = new QTableWidgetItem(QString::number(2*DEMResolution));
                ui->tableWidget->setItem(rowlen,1,NewTableItem);
                ui->tableWidget->item(rowlen,1)->setTextColor(QColor(0,0,0));
                ui->tableWidget->item(rowlen,1)->setTextAlignment(Qt::AlignRight);
                ui->tableWidget->item(rowlen,1)->setTextAlignment(Qt::AlignVCenter);
            }

            pushButtonSetFocus();
        }

        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

    } catch (...) {
        qDebug() << "Error: SimplifyPolylines::on_pushButtonAdd_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Remove Button Clicked Event  (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SimplifyPolylines::on_pushButtonRemove_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start SimplifyPolylines::on_pushButtonRemove_clicked()";

    try {

        ui->tableWidget->removeRow(ui->tableWidget->currentRow());
        qDebug() << "Row Count = " << ui->tableWidget->rowCount();

        pushButtonSetFocus();

    } catch (...) {
        qDebug() << "Error: SimplifyPolylines::on_pushButtonRemove_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Clear Button Clicked Event  (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SimplifyPolylines::on_pushButtonClear_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start SimplifyPolylines::on_pushButtonClear_clicked()";

    try {
        while( ui->tableWidget->rowCount() )
            ui->tableWidget->removeRow( ui->tableWidget->rowCount()-1 );

        qDebug() << "Row Count = " << ui->tableWidget->rowCount();

        pushButtonSetFocus();
    } catch (...) {
        qDebug() << "Error: SimplifyPolylines::on_pushButtonClear_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Run Button Clicked Event  (OUTPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SimplifyPolylines::on_pushButtonRun_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start SimplifyPolylines::on_pushButtonRun_clicked()";

    try {

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Clear Log
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Clear_Log();

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check inputs
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if( ui->tableWidget->rowCount() == 0 )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Polyline Input File(s) Missing </span>")+tr("<br>"));
            return;
        }

        bool failure_found = false;

        for (int i=0; i<ui->tableWidget->rowCount(); i++)
        {
            QString file1 = ui->tableWidget->item(i,0)->text();
            QString file2 = ui->tableWidget->item(i,2)->text(); //Note 2 index not 1

            bool file1_check = Check_File_Valid(file1);
            bool file2_check = Check_File_Valid(file2);

            if(file1_check)
            {
                if ( ! CheckFileAccess(file1, "ReadOnly") )
                {
                    LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Read Access ... </span>") + file1 +tr("<br>"));
                    failure_found = true;
                }
            }
            else
            {
                failure_found = true;
            }

            if(file2_check)
            {
                LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Polyline Output File already exists </span>")+ file2 + tr("<br>"));
                ui->textBrowserLogs->setHtml(LogsString);
                ui->textBrowserLogs->repaint();
                failure_found = true;
            }
            else
            {
                if ( ! CheckFolderAccessFromFilePath(file2, "WriteOnly") )
                {
                    LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Write Access ... </span>") + file2 +tr("<br>"));
                    ui->textBrowserLogs->setHtml(LogsString);
                    ui->textBrowserLogs->repaint();
                    failure_found = true;
                }
            }
        }

        if(failure_found)
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Polyline Input and Output File issues </span>")+ tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Run SimplifyPolylines
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        LogsString.append("Running Simplify Polylines ... <br>");
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

        QStringList ProjectIOStringList;
        ProjectIOStringList << "SimplifyPolylines";

        for (int i=0; i<ui->tableWidget->rowCount(); i++)
        {
            QString InpShpFileName, InpDbfFileName;
            QString OutShpFileName, OutDbfFileName;
            int Tolerance;

            QString InputPolylinesFileName;
            QStringList InputPolylinesFileNameList;

            InpShpFileName = ui->tableWidget->item(i,0)->text();
            InpDbfFileName = InpShpFileName;
            InpDbfFileName.replace(QString(".shp"), QString(".dbf"));

            Tolerance = ui->tableWidget->item(i,1)->text().toInt();

            OutShpFileName = ui->tableWidget->item(i,2)->text();
            OutDbfFileName = OutShpFileName;
            OutDbfFileName.replace(QString(".shp"), QString(".dbf"));

            qDebug() << InpShpFileName << " # " << InpDbfFileName;
            qDebug() << Tolerance;
            qDebug() << OutShpFileName << " # " << OutDbfFileName;

            int ErrorSln = simplify_shape((char *)qPrintable(InpShpFileName), (char *)qPrintable(InpDbfFileName), (char *)qPrintable(OutShpFileName), (char *)qPrintable(OutDbfFileName), Tolerance);
            if ( ErrorSln == 1 || ErrorSln == 5 || ErrorSln == 8 )
            {
                LogsString.append(tr("<span style=\"color:#FF0000\">Warning: Skipping Non-Polyline Layer ... </span>")+InpShpFileName+tr("<br>"));
                ui->textBrowserLogs->setHtml(LogsString);
                ui->textBrowserLogs->repaint();
            }
            else if ( ErrorSln != 0 )
            {
                LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Simplify Polyline Processing Failed ... </span>")+tr("<br>"));
                LogsString.append(tr("<span style=\"color:#FF0000\">RETURN CODE: ... </span>")+QString::number(ErrorSln)+tr("<br>"));
                ui->textBrowserLogs->setHtml(LogsString);
                ui->textBrowserLogs->repaint();
                return;
            }
            else
            {
                LogsString.append(tr("<span><b>Processing ... </span>")+InpShpFileName+tr("<br>"));
                ui->textBrowserLogs->setHtml(LogsString);
                ui->textBrowserLogs->repaint();

                ProjectIOStringList << InpShpFileName << OutShpFileName << QString::number(Tolerance);
            }
        }


        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update Project file
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if ( ProjectIOStringList.length() > 2)
            WriteModuleLine(filename_open_project, ProjectIOStringList);

        ProjectIOStringList.clear();

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update Message box
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Clear_Log();

        LogsString.append(tr("<br><b>Simplify Polylines Processing Completed.</b>")+tr("<br>"));
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

        ui->pushButtonRun->setDefault(false);
        ui->pushButtonClose->setDefault(true);
        ui->pushButtonClose->setFocus();


    } catch (...) {
        qDebug() << "Error: SimplifyPolylines::on_pushButtonRun_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TableWidget cellChange Event
// NOTE: In Load project settings, block signals are disabled before and restored.
// TODO: This code has not been tested.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SimplifyPolylines::on_tableWidget_cellChanged(int row, int column)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start SimplifyPolylines::on_tableWidget_cellChanged()";

    try {

        if ( column == 1 )
        {
            qDebug() << QString::number(row) << " " << QString::number(column);

            ui->tableWidget->item(row,column  )->setTextColor(QColor(0,0,0));
            ui->tableWidget->item(row,column-1)->setTextColor(QColor(0,0,0));
            ui->tableWidget->item(row,column+1)->setTextColor(QColor(0,0,0));

            QString PolylineFileName = ui->tableWidget->item(row, column-1)->text();
            QString Tolerance        = ui->tableWidget->item(row, column)->text();

            PolylineFileName.replace(".shp",QString("_sln")+Tolerance+QString(".shp"));

            QTableWidgetItem *NewTableItem = new QTableWidgetItem(PolylineFileName);
            ui->tableWidget->setItem(row,2,NewTableItem);
        }

    } catch (...) {
        qDebug() << "Error: SimplifyPolylines::on_tableWidget_cellChanged() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Close button event
// TODO, Decide on keeping button next highlights or not
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SimplifyPolylines::on_pushButtonClose_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start SimplifyPolylines::on_pushButtonClose_clicked()";

    try {
        //QStringList default_params; default_params << "WORKFLOW3" << "POLYLINE";
        //QMetaObject::invokeMethod(parent(),"set_defaults",Q_ARG(QStringList,default_params));
        close();
    } catch (...) {
        qDebug() << "Error: SimplifyPolylines::on_pushButtonClose_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Help button event
// TODO, Need cataract server back online
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SimplifyPolylines::on_pushButtonHelp_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start SimplifyPolylines::on_pushButtonHelp_clicked()";

    try {
        //        LogsString = tr("");
        //        if ( ! QDesktopServices::openUrl(QUrl("http://cataract.cee.psu.edu/PIHM/index.php/PIHMgis_3.0#Simplify_Polylines")) )
        //            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Load HTTP Link ... </span>")+tr("<br>"));
        //        ui->textBrowserLogs->setHtml(LogsString);
        //        ui->textBrowserLogs->repaint();
    } catch (...) {
        qDebug() << "Error: SimplifyPolylines::on_pushButtonHelp_clicked() is returning w/o checking";
    }
}
