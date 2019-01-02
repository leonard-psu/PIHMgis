#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>

#include "polylinetolines.h"
#include "ui_polylinetolines.h"

#include "0LibsIO/IOProjectFile.h"
#include "0LibsVector/polyline_splitline.h"
#include "globals.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PolylineToLines Constructor
// Parent is Main Window, filename is the open project text file used to store project details
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PolylineToLines::PolylineToLines(QWidget *parent, QString filename) :
    QDialog(parent),
    ui(new Ui::PolylineToLines)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PolylineToLines";

    try {

        ui->setupUi(this);

        filename_open_project = filename;
        bool found_file = false;

        QFile ProjectFile(filename_open_project);
        if ( ! ProjectFile.open(QIODevice::ReadOnly | QIODevice::Text) )
        {
            Log_Error_Message("Unable to Open File: " + filename_open_project );
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

        pushButtonSetFocus();

    } catch (...) {
        qDebug() << "Error: PolylineToLines is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Load_Project_Settings
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PolylineToLines::Load_Project_Settings()
{
    try {

        QTableWidgetItem *NewTableItem;

        QStringList ModuleStringList = ReadModuleLine(filename_open_project,tr("SimplifyPolylines"));
        if ( ModuleStringList.length() > 0  )
        {
            for (int i=1; i+1<ModuleStringList.length(); i=i+3)
            {
                QString InpPolygonFileName, OutPolylineFileName;

                ui->tableWidget->insertRow(ui->tableWidget->rowCount());

                QString file1 = ModuleStringList.at(i+1);
                OutPolylineFileName = file1;
                OutPolylineFileName.replace(".shp","_xln.shp");
                bool file1_check = Check_File_Valid(file1);
                bool file2_check = Check_File_Valid(OutPolylineFileName);

                int rowlen = ui->tableWidget->rowCount()-1;
                if(file1.length() > 0 )
                {
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
                            Log_Error_Message( file1 + " input does not exist. ");
                            ui->tableWidget->item(rowlen,0)->setTextColor(Qt::red);
                        }
                    }
                }

                if(OutPolylineFileName.length() > 0 )
                {
                    if(rowlen >= 0)
                    {
                        NewTableItem = new QTableWidgetItem(OutPolylineFileName);
                        ui->tableWidget->setItem(rowlen,1,NewTableItem);

                        if(file2_check)
                        {
                            Log_Message(OutPolylineFileName + " output already exists.");
                            ui->tableWidget->item(rowlen,1)->setTextColor(Qt::red);
                        }
                        else
                        {
                            //LogsString.append(tr("<span style=\"color:#FF0000\">INFO: ") + OutPolylineFileName + tr(" does not exist. </span>") +tr("<br>"));
                            ui->tableWidget->item(rowlen,1)->setTextColor(Qt::black);
                        }
                    }
                }
            }
        }

        ModuleStringList = ReadModuleLine(filename_open_project,tr("PolylineToLines"));
        if ( ModuleStringList.length() > 0 )
        {
            while( ui->tableWidget->rowCount() )
                ui->tableWidget->removeRow( ui->tableWidget->rowCount()-1 );

            ui->tableWidget->setRowCount(0);

            for (int i=1; i+1<ModuleStringList.length(); i=i+2)
            {
                ui->tableWidget->insertRow(ui->tableWidget->rowCount());

                int rowlen = ui->tableWidget->rowCount()-1;

                QString file1 = ModuleStringList.at(i);
                QString file2 = ModuleStringList.at(i+1);

                bool file1_check = Check_File_Valid(file1);
                bool file2_check = Check_File_Valid(file2);

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
                        Log_Error_Message( file1 + " input does not exist. ");
                        ui->tableWidget->item(rowlen,0)->setTextColor(Qt::red);
                    }
                    ui->tableWidget->item(rowlen,0)->setTextAlignment(Qt::AlignRight);
                    ui->tableWidget->item(rowlen,0)->setTextAlignment(Qt::AlignVCenter);
                }

                if(file2.length() > 0 )
                {
                    NewTableItem = new QTableWidgetItem(file2);
                    ui->tableWidget->setItem(rowlen,1,NewTableItem);
                    if(file2_check)
                    {
                        Log_Message(file2 + " output already exists. ");
                        ui->tableWidget->item(rowlen,1)->setTextColor(Qt::red);
                    }
                    else
                    {
                        //LogsString.append(tr("<span style=\"color:#FF0000\">INFO: ") + file2 + tr(" does not exist. </span>") +tr("<br>"));
                        ui->tableWidget->item(rowlen,1)->setTextColor(Qt::black);
                    }

                    ui->tableWidget->item(rowlen,1)->setTextAlignment(Qt::AlignRight);
                    ui->tableWidget->item(rowlen,1)->setTextAlignment(Qt::AlignVCenter);
                }

            }
        }

        ui->tableWidget->resizeColumnsToContents();

        pushButtonSetFocus();

    } catch (...) {
        qDebug() << "Error: PolylineToLines::Load_Project_Settings is returning w/o checking";
        return false;
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PolylineToLines Deconstructor
// Todo: Check for memory leaks
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PolylineToLines::~PolylineToLines()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ~PolylineToLines";

    try {
        delete ui;
    } catch (...) {
        qDebug() << "Error: ~PolylineToLines is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to focus button selection (needed for users w/o mouse)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PolylineToLines::pushButtonSetFocus()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PolylineToLines::pushButtonSetFocus()";

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
        qDebug() << "Error: PolylineToLines::pushButtonSetFocus()";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to clear message log
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PolylineToLines::Clear_Log()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PolylineToLines::Clear_Log()";

    try {

        LogsString = tr("");
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

    } catch (...) {
        qDebug() << "Error: PolylineToLines::Clear_Log() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check Log_Error_Message
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PolylineToLines::Log_Error_Message(QString message)
{
    try {
        LogsString.append(tr("<span style=\"color:#FF0000\">Error: ") + message + " </span>" +tr("<br>"));
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

        if(redirect_debug_messages_to_log)
        {
            ((PIHMgisDialog*)this->parent())->Log_Message(message);
        }

    } catch (...) {
        qDebug() << "Error: Log_Error_Message is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check Log_Error_Message
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PolylineToLines::Log_Message(QString message)
{
    try {
        LogsString.append(tr("<span style=\"color:#000000\"> ") + message + " </span>" + tr("<br>"));
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

        if(redirect_debug_messages_to_log)
        {
            ((PIHMgisDialog*)this->parent())->Log_Message( message );
        }

    } catch (...) {
        qDebug() << "Error: Log_Message is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to assist if input file exists (returns true) or does not (returns false)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PolylineToLines::Check_File_Valid(QString file)
{
    if(print_debug_messages)
        qDebug() << "INFO: Check_File_Valid()";

    bool result = false;

    try {

        if( fileExists(file) )
        {
            result = true;

            qint64 size = file_Size(file);

            if( size < 1)
            {
                Log_Error_Message("Check_File_Valid failed, file : " + file );
                Log_Error_Message("Check_File_Valid failed, invalid file size: " + size);
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
void PolylineToLines::on_pushButtonAdd_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PolylineToLines::on_pushButtonAdd_clicked()";

    try {

        Clear_Log();

        QStringList InputPolylinesFileNames = QFileDialog::getOpenFileNames(this, "Choose Shape Files", user_pihmgis_root_folder +tr("/2VectorProcessing"), "Shape File(*.shp *.SHP)");
        if ( InputPolylinesFileNames.length() > 0)
        {
            for (int i=0; i<InputPolylinesFileNames.length(); i++)
            {
                ui->tableWidget->insertRow(ui->tableWidget->rowCount());

                QString file1 = InputPolylinesFileNames.at(i);
                QString file2 = file1.replace(".shp","_xln.shp");
                bool file1_check = Check_File_Valid(file1);
                bool file2_check = Check_File_Valid(file2);
                int rowlen = ui->tableWidget->rowCount()-1;

                if(file1.length() > 0 )
                {
                    QTableWidgetItem *NewTableItem = new QTableWidgetItem(file1);
                    ui->tableWidget->setItem(rowlen,0,NewTableItem);
                    if(file1_check)
                    {
                        ui->tableWidget->item(rowlen,0)->setTextColor(Qt::black);
                    }
                    else
                    {
                        Log_Error_Message( file1 + " input does not exist. ");
                        ui->tableWidget->item(rowlen,0)->setTextColor(Qt::red);
                    }
                    ui->tableWidget->item(rowlen,0)->setTextAlignment(Qt::AlignRight);
                    ui->tableWidget->item(rowlen,0)->setTextAlignment(Qt::AlignVCenter);
                }

                if(file2.length() > 0 )
                {
                    QTableWidgetItem *NewTableItem = new QTableWidgetItem(file2);
                    ui->tableWidget->setItem(rowlen,1,NewTableItem);
                    if(file2_check)
                    {
                        Log_Message( file2 + " output already exists. ");
                        ui->tableWidget->item(rowlen,1)->setTextColor(Qt::red);
                    }
                    else
                    {
                        Log_Message("INFO: " + file2 + " does not exist. ");
                        ui->tableWidget->item(rowlen,1)->setTextColor(Qt::black);
                    }

                    ui->tableWidget->item(rowlen,1)->setTextAlignment(Qt::AlignRight);
                    ui->tableWidget->item(rowlen,1)->setTextAlignment(Qt::AlignVCenter);
                }
            }

            pushButtonSetFocus();
        }

        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

    } catch (...) {
        qDebug() << "Error: PolylineToLines::on_pushButtonAdd_clicked()";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Remove Button Clicked Event  (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PolylineToLines::on_pushButtonRemove_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PolylineToLines::on_pushButtonRemove_clicked()";

    try {
        ui->tableWidget->removeRow(ui->tableWidget->currentRow());

        pushButtonSetFocus();
    } catch (...) {
        qDebug() << "Error: PolylineToLines::on_pushButtonRemove_clicked()";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Clear Button Clicked Event  (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PolylineToLines::on_pushButtonClear_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PolylineToLines::on_pushButtonClear_clicked()";

    try {
        while( ui->tableWidget->rowCount() )
            ui->tableWidget->removeRow( ui->tableWidget->rowCount()-1 );

        pushButtonSetFocus();
    } catch (...) {
        qDebug() << "Error: PolylineToLines::on_pushButtonClear_clicked()";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Run Button Clicked Event  (OUTPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PolylineToLines::on_pushButtonRun_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PolylineToLines::on_pushButtonRun_clicked()";

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
            Log_Error_Message("Polyline Input File(s) Missing ");
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
                    Log_Error_Message("No Read Access to ... " + file1);
                    failure_found = true;
                }
            }
            else
            {
                failure_found = true;
            }

            if(file2_check)
            {
                Log_Error_Message("Polyline Output File already exists "+ file2 );
                failure_found = true;
            }
            else
            {
                if ( ! CheckFolderAccessFromFilePath(file2, "WriteOnly") )
                {
                    Log_Error_Message("No Write Access to ... " + file2);
                    failure_found = true;
                }
            }
        }


        if(failure_found)
        {
            Log_Error_Message("Polyline Input and Output File issues ");
            return;
        }


        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Run Polygon to Polylines
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        Log_Message("Running Polyline To Split Lines ... ");

        QStringList ProjectIOStringList;
        ProjectIOStringList << "PolylineToLines";

        for (int i=0; i<ui->tableWidget->rowCount(); i++)
        {
            QString InpShpFileName, InpDbfFileName;
            QString OutShpFileName, OutDbfFileName;

            InpShpFileName = ui->tableWidget->item(i,0)->text();
            InpDbfFileName = InpShpFileName;
            InpDbfFileName.replace(QString(".shp"), QString(".dbf"));

            OutShpFileName = ui->tableWidget->item(i,1)->text();
            OutDbfFileName = OutShpFileName;
            OutDbfFileName.replace(QString(".shp"), QString(".dbf"));

            bool file1_check = Check_File_Valid(InpShpFileName); //Want to exist
            bool file2_check = Check_File_Valid(OutShpFileName); //Dont want to exist
            bool file3_check = Check_File_Valid(InpDbfFileName); //Want to exist
            bool file4_check = Check_File_Valid(OutDbfFileName); //Dont want to exist

            bool valid_check = false;
            if( file1_check && file3_check) //Want to exist
            {
                if( !file2_check && !file4_check) //Dont want to exist
                {
                    valid_check = true;
                }
                else
                {
                    Log_Error_Message("Polyline to lines Output already exist " + OutShpFileName);
                    valid_check = false;
                }
            }
            else
            {
                Log_Error_Message("Polyline to lines Input does not exist " + InpShpFileName);
                valid_check = false;
            }

            if(valid_check)
            {
                int ErrorXln = polyline_splitlines(InpShpFileName, InpDbfFileName, OutShpFileName, OutDbfFileName);

                if ( ErrorXln == 1 || ErrorXln == 5 || ErrorXln == 8 )
                {
                    Log_Message("Warning: Skipping Non-Polyline Layer ... " + InpShpFileName );
                }
                else if ( ErrorXln != 0 )
                {
                    Log_Error_Message("Polyline to Split Lines Processing Failed ... ");
                    Log_Error_Message("RETURN CODE: ... " + QString::number(ErrorXln) );
                    return;
                }
                else
                {
                    Log_Message("Processing ... " + InpShpFileName );

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

        Log_Message("Polyline to Split Lines Processing Completed.");
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

        ui->pushButtonRun->setDefault(false);
        ui->pushButtonClose->setDefault(true);
        ui->pushButtonClose->setFocus();


    } catch (...) {
        qDebug() << "Error: PolylineToLines::on_pushButtonRun_clicked()";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Close button event
// TODO, Decide on keeping button next highlights or not
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PolylineToLines::on_pushButtonClose_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PolylineToLines::on_pushButtonClose_clicked()";

    try {
        //QStringList default_params; default_params << "WORKFLOW3" << "MERGE";
        //QMetaObject::invokeMethod(parent(),"set_defaults",Q_ARG(QStringList,default_params));
        close();
    } catch (...) {
        qDebug() << "Error: PolylineToLines::on_pushButtonClose_clicked()";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Help button event
// TODO, Need cataract server back online
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PolylineToLines::on_pushButtonHelp_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PolylineToLines::on_pushButtonHelp_clicked()";

    try {
        //        LogsString = tr("");
        //        if ( ! QDesktopServices::openUrl(QUrl("http://cataract.cee.psu.edu/PIHM/index.php/PIHMgis_3.0#Polyline_to_Lines")) )
        //            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Load HTTP Link ... </span>")+tr("<br>"));
        //        ui->textBrowserLogs->setHtml(LogsString);
        //        ui->textBrowserLogs->repaint();
    } catch (...) {
        qDebug() << "Error: PolylineToLines::on_pushButtonHelp_clicked()";
    }
}
