#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>

#include "polygontopolylines.h"
#include "ui_polygontopolylines.h"

#include "0LibsIO/IOProjectFile.h"
#include "0LibsVector/polygon_polylines.h"
#include "globals.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PolygonToPolylines Constructor
// Parent is Main Window, filename is the open project text file used to store project details
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PolygonToPolylines::PolygonToPolylines(QWidget *parent, QString filename) :
    QDialog(parent),
    ui(new Ui::PolygonToPolylines)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PolygonToPolylines";

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
        qDebug() << "Error: PolygonToPolylines is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PolygonToPolylines Deconstructor
// Todo: Check for memory leaks
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PolygonToPolylines::~PolygonToPolylines()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ~PolygonToPolylines";

    try {
        delete ui;
    } catch (...) {
        qDebug() << "Error: ~PolygonToPolylines is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Load_Project_Settings
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PolygonToPolylines::Load_Project_Settings()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PolygonToPolylines::Load_Project_Settings";

    try {

        QTableWidgetItem *NewTableItem;
        QStringList ModuleStringList = ReadModuleLine(filename_open_project,tr("DissolvePolygons"));
        if ( ModuleStringList.length() > 0  )
        {
            for (int i=1; i+1<ModuleStringList.length(); i=i+2)
            {
                ui->tableWidget->insertRow(ui->tableWidget->rowCount());

                QString file1 = ModuleStringList.at(i+1);
                if(file1.length() > 0 )
                {
                    bool file1_check = Check_File_Valid(file1);

                    int rowlen = ui->tableWidget->rowCount()-1;
                    if(rowlen >= 0)
                    {
                        if(file1_check)
                        {
                            QTableWidgetItem *NewTableItem = new QTableWidgetItem(file1);
                            ui->tableWidget->setItem(rowlen,0,NewTableItem);
                            ui->tableWidget->item(rowlen,0)->setTextColor(Qt::black);
                        }
                        else
                        {
                            QTableWidgetItem *NewTableItem = new QTableWidgetItem(file1);
                            ui->tableWidget->setItem(rowlen,0,NewTableItem);
                            ui->tableWidget->item(rowlen,0)->setTextColor(Qt::red);
                            LogsString.append(tr("<span style=\"color:#FF0000\">Error: ") + file1 + tr(" input does not exist. </span>") +tr("<br>"));
                        }
                    }
                }


                QString OutPolylineFileName = ModuleStringList.at(i+1);
                if(OutPolylineFileName.length() > 0 )
                {
                    OutPolylineFileName.replace(".shp","_pln.shp");
                    bool file2_check = Check_File_Valid(OutPolylineFileName);

                    int rowlen = ui->tableWidget->rowCount()-1;
                    if(rowlen >= 0)
                    {
                        if(!file2_check)
                        {
                            QTableWidgetItem *NewTableItem = new QTableWidgetItem(OutPolylineFileName);
                            ui->tableWidget->setItem(rowlen,1,NewTableItem);
                            ui->tableWidget->item(rowlen,1)->setTextColor(Qt::black);
                        }
                        else
                        {
                            LogsString.append(tr("<span style=\"color:#FF0000\">Error: ") + OutPolylineFileName + tr(" Output already exist. </span>") +tr("<br>"));
                            QTableWidgetItem *NewTableItem = new QTableWidgetItem(OutPolylineFileName);
                            ui->tableWidget->setItem(rowlen,1,NewTableItem);
                            ui->tableWidget->item(rowlen,1)->setTextColor(Qt::red);
                        }
                    }
                }

                OutPolylineFileName = "";
            }
        }
        else // *** If DISSOLVE POLYGONS step is skipped
        {
            ModuleStringList = ReadModuleLine(filename_open_project,tr("CatchmentRasterVector"));
            if ( ModuleStringList.length() > 0  )
            {
                ui->tableWidget->insertRow(ui->tableWidget->rowCount());

                int rowlen = ui->tableWidget->rowCount()-1;
                if(rowlen >= 0)
                {
                    NewTableItem = new QTableWidgetItem(ModuleStringList.at(2));
                    ui->tableWidget->setItem(rowlen,0,NewTableItem);
                }

                rowlen = ui->tableWidget->rowCount()-1;
                if(rowlen >= 0)
                {
                    QString OutPolylineFileName = ModuleStringList.at(2);
                    OutPolylineFileName.replace(".shp","_pln.shp");

                    NewTableItem = new QTableWidgetItem(OutPolylineFileName);
                    ui->tableWidget->setItem(rowlen,1,NewTableItem);

                    OutPolylineFileName = "";
                }
            }
        }

        Clear_Log();

        ModuleStringList = ReadModuleLine(filename_open_project,tr("PolygonToPolylines"));
        if ( ModuleStringList.length() > 0 )
        {
            while( ui->tableWidget->rowCount() )
                ui->tableWidget->removeRow( ui->tableWidget->rowCount()-1 );
            ui->tableWidget->setRowCount(0);

            qDebug() << "Length = " << ModuleStringList.length();
            for (int i=1; i+1<ModuleStringList.length(); i=i+2)
            {
                ui->tableWidget->insertRow(ui->tableWidget->rowCount());

                QString file1 = ModuleStringList.at(i);
                QString file2 = ModuleStringList.at(i+1);

                bool file1_check = Check_File_Valid(file1);
                bool file2_check = Check_File_Valid(file2);

                if(file1.length() > 0 )
                {
                    int rowlen = ui->tableWidget->rowCount()-1;
                    if(rowlen >= 0)
                    {
                        QTableWidgetItem *NewTableItem = new QTableWidgetItem(file1);
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
                    }
                }

                if(file2.length() > 0 )
                {
                    int rowlen = ui->tableWidget->rowCount()-1;
                    if(rowlen >= 0)
                    {
                        QTableWidgetItem *NewTableItem = new QTableWidgetItem(file2);
                        ui->tableWidget->setItem(rowlen,1,NewTableItem);
                        if(file2_check)
                        {
                            LogsString.append(tr("<span style=\"color:#FF0000\">Warning: ") + file2 + tr(" output already exists. </span>") +tr("<br>"));
                            ui->tableWidget->item(rowlen,1)->setTextColor(Qt::red);
                        }
                        else
                        {
                            LogsString.append(tr("<span style=\"color:#FF0000\">INFO: ") + file2 + tr(" does not exist. </span>") +tr("<br>"));
                            ui->tableWidget->item(rowlen,1)->setTextColor(Qt::black);
                        }

                        ui->tableWidget->item(rowlen,1)->setTextAlignment(Qt::AlignRight);
                        ui->tableWidget->item(rowlen,1)->setTextAlignment(Qt::AlignVCenter);
                    }
                }

                ui->textBrowserLogs->setHtml(LogsString);
                ui->textBrowserLogs->repaint();

            }
        }

        pushButtonSetFocus();
    } catch (...) {
        qDebug() << "Error: PolygonToPolylines::Load_Project_Settings is returning w/o checking";
        return false;
    }

    return true;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to focus button selection (needed for users w/o mouse)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PolygonToPolylines::pushButtonSetFocus()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PolygonToPolylines::pushButtonSetFocus()";

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
        qDebug() << "Error: PolygonToPolylines::pushButtonSetFocus() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to clear message log
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PolygonToPolylines::Clear_Log()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PolygonToPolylines::Clear_Log()";

    try {

        LogsString = tr("");
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

    } catch (...) {
        qDebug() << "Error: PolygonToPolylines::Clear_Log() is returning w/o checking";
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to assist if input file exists (returns true) or does not (returns false)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PolygonToPolylines::Check_File_Valid(QString file)
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
// Add Button Clicked Event  (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PolygonToPolylines::on_pushButtonAdd_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PolygonToPolylines::on_pushButtonAdd_clicked()";

    try {

        Clear_Log();

        QStringList InputPolygonsFileNames = QFileDialog::getOpenFileNames(this, "Choose Shape Files", user_pihmgis_root_folder +tr("/2VectorProcessing"), "Shape File(*.shp *.SHP)");
        if ( InputPolygonsFileNames.length() > 0)
        {
            for (int i=0; i<InputPolygonsFileNames.length(); i++)
            {
                ui->tableWidget->insertRow(ui->tableWidget->rowCount());

                QString file1 = InputPolygonsFileNames.at(i);
                QString file2 = file1.replace(".shp","_pln.shp");
                bool file1_check = Check_File_Valid(file1);
                bool file2_check = Check_File_Valid(file2);

                if(file1.length() > 0 )
                {
                    QTableWidgetItem *NewTableItem = new QTableWidgetItem(file1);
                    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,NewTableItem);
                    if(file1_check)
                    {
                        ui->tableWidget->item(ui->tableWidget->rowCount()-1,0)->setTextColor(Qt::black);
                    }
                    else
                    {
                        LogsString.append(tr("<span style=\"color:#FF0000\">Error: ") + file2 + tr(" input does not exist. </span>") +tr("<br>"));
                        ui->tableWidget->item(ui->tableWidget->rowCount()-1,0)->setTextColor(Qt::red);
                    }
                    ui->tableWidget->item(ui->tableWidget->rowCount()-1,0)->setTextAlignment(Qt::AlignRight);
                    ui->tableWidget->item(ui->tableWidget->rowCount()-1,0)->setTextAlignment(Qt::AlignVCenter);
                }

                if(file2.length() > 0 )
                {
                    QTableWidgetItem *NewTableItem = new QTableWidgetItem(file2);
                    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,NewTableItem);
                    if(file2_check)
                    {
                        LogsString.append(tr("<span style=\"color:#FF0000\">Warning: ") + file2 + tr(" output already exists. </span>") +tr("<br>"));
                        ui->tableWidget->item(ui->tableWidget->rowCount()-1,1)->setTextColor(Qt::red);
                    }
                    else
                    {
                        LogsString.append(tr("<span style=\"color:#FF0000\">INFO: ") + file2 + tr(" does not exist. </span>") +tr("<br>"));
                        ui->tableWidget->item(ui->tableWidget->rowCount()-1,1)->setTextColor(Qt::black);
                    }

                    ui->tableWidget->item(ui->tableWidget->rowCount()-1,1)->setTextAlignment(Qt::AlignRight);
                    ui->tableWidget->item(ui->tableWidget->rowCount()-1,1)->setTextAlignment(Qt::AlignVCenter);
                }

                ui->textBrowserLogs->setHtml(LogsString);
                ui->textBrowserLogs->repaint();

            }

            pushButtonSetFocus();
        }

        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();
    } catch (...) {
        qDebug() << "Error: PolygonToPolylines::on_pushButtonAdd_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Remove Button Clicked Event  (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PolygonToPolylines::on_pushButtonRemove_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PolygonToPolylines::on_pushButtonRemove_clicked()";

    try {

        ui->tableWidget->removeRow(ui->tableWidget->currentRow());

        //qDebug() << "Row Count = " << ui->tableWidget->rowCount();

        pushButtonSetFocus();

    } catch (...) {
        qDebug() << "Error: PolygonToPolylines::on_pushButtonRemove_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Clear Button Clicked Event  (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PolygonToPolylines::on_pushButtonClear_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PolygonToPolylines::on_pushButtonClear_clicked()";

    try {
        while( ui->tableWidget->rowCount() )
            ui->tableWidget->removeRow( ui->tableWidget->rowCount()-1 );
        //ui->tableWidget->setRowCount(0);
        //qDebug() << "Row Count = " << ui->tableWidget->rowCount();

        pushButtonSetFocus();

    } catch (...) {
        qDebug() << "Error: PolygonToPolylines::on_pushButtonClear_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Run Button Clicked Event  (OUTPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PolygonToPolylines::on_pushButtonRun_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PolygonToPolylines::on_pushButtonRun_clicked()";

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
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Polygon Input File(s) Missing </span>")+tr("<br>"));
            return;
        }


        bool failure_found = false;

        for (int i=0; i<ui->tableWidget->rowCount(); i++)
        {
            QString file1 = ui->tableWidget->item(i,0)->text();
            QString file2 = ui->tableWidget->item(i,1)->text();

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
                LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Polygon Output File already exists </span>")+ file2 + tr("<br>"));
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
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Polygon Input and Output File issues </span>")+ tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Run Polygon to Polylines
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        LogsString.append("Running Polygon to Polylines ... <br>");
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

        QStringList ProjectIOStringList;
        ProjectIOStringList << "PolygonToPolylines";

        for (int i=0; i<ui->tableWidget->rowCount(); i++)
        {
            QString InpShpFileName, InpDbfFileName;
            QString OutShpFileName, OutDbfFileName;

            InpShpFileName = ui->tableWidget->item(i,0)->text();
            OutShpFileName = ui->tableWidget->item(i,1)->text();

            InpDbfFileName = InpShpFileName;
            InpDbfFileName.replace(QString(".shp"), QString(".dbf"));

            OutDbfFileName = OutShpFileName;
            OutDbfFileName.replace(QString(".shp"), QString(".dbf"));

            qDebug() << InpShpFileName << " # " << InpDbfFileName;
            qDebug() << OutShpFileName << " # " << OutDbfFileName;

            bool file1_check = Check_File_Valid(InpShpFileName); //Want to exist
            bool file2_check = Check_File_Valid(OutShpFileName); //Dont want to exist
            bool file3_check = Check_File_Valid(InpDbfFileName); //Want to exist
            bool file4_check = Check_File_Valid(OutDbfFileName); //Dont want to exist

            qDebug() << file2_check << " # " << file4_check;

            bool valid_check = false;
            if( file1_check && file3_check) //Want to exist
            {
                if( !file2_check && !file4_check) //Dont want to exist
                {
                    valid_check = true;
                }
                else
                {
                    LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: polygon_polylines Output already exist </span>")+OutShpFileName+tr("<br>"));
                    ui->textBrowserLogs->setHtml(LogsString);
                    ui->textBrowserLogs->repaint();
                    valid_check = false;
                }
            }
            else
            {
                LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: polygon_polylines Input does not exist </span>")+InpShpFileName+tr("<br>"));
                ui->textBrowserLogs->setHtml(LogsString);
                ui->textBrowserLogs->repaint();
                valid_check = false;
            }

            if(valid_check)
            {
                int ErrorPln = polygon_polylines((char *)qPrintable(InpShpFileName), (char *)qPrintable(InpDbfFileName), (char *)qPrintable(OutShpFileName), (char *)qPrintable(OutDbfFileName));
                if ( ErrorPln == 1 || ErrorPln == 3 || ErrorPln == 8 )
                {
                    LogsString.append(tr("<span style=\"color:#FF0000\">Warning: Skipping Non-Polygon Layer ... </span>")+InpShpFileName+tr("<br>"));
                    ui->textBrowserLogs->setHtml(LogsString);
                    ui->textBrowserLogs->repaint();
                }
                else if ( ErrorPln != 0 )
                {
                    LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Polygon to Polyline Processing Failed ... </span>")+tr("<br>"));
                    LogsString.append(tr("<span style=\"color:#FF0000\">RETURN CODE: ... </span>")+QString::number(ErrorPln)+tr("<br>"));
                    ui->textBrowserLogs->setHtml(LogsString);
                    ui->textBrowserLogs->repaint();
                    return;
                }
                else
                {
                    LogsString.append(tr("<span><b>Processing ... </span>")+InpShpFileName+tr("<br>"));
                    ui->textBrowserLogs->setHtml(LogsString);
                    ui->textBrowserLogs->repaint();

                    ProjectIOStringList << InpShpFileName << OutShpFileName;
                }
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

        LogsString.append(tr("<br><b>Polygon to Polylines Processing Completed.</b>")+tr("<br>"));
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

        ui->pushButtonRun->setDefault(false);
        ui->pushButtonClose->setDefault(true);
        ui->pushButtonClose->setFocus();



    } catch (...) {
        qDebug() << "Error: PolygonToPolylines::on_pushButtonRun_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Close button event
// TODO, Decide on keeping button next highlights or not
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PolygonToPolylines::on_pushButtonClose_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PolygonToPolylines::on_pushButtonClose_clicked()";

    try {
        //QStringList default_params; default_params << "WORKFLOW3" << "SIMPLIFY";
        //QMetaObject::invokeMethod(parent(),"set_defaults",Q_ARG(QStringList,default_params));
        close();
    } catch (...) {
        qDebug() << "Error: PolygonToPolylines::on_pushButtonClose_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Help button event
// TODO, Need cataract server back online
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PolygonToPolylines::on_pushButtonHelp_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PolygonToPolylines::on_pushButtonHelp_clicked()";

    try {
        //        LogsString = tr("");
        //        if ( ! QDesktopServices::openUrl(QUrl("http://cataract.cee.psu.edu/PIHM/index.php/PIHMgis_3.0#Polygon_to_Polylines")) )
        //            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Load HTTP Link ... </span>")+tr("<br>"));
        //        ui->textBrowserLogs->setHtml(LogsString);
        //        ui->textBrowserLogs->repaint();
    } catch (...) {
        qDebug() << "Error: PolygonToPolylines::on_pushButtonHelp_clicked() is returning w/o checking";
    }
}
