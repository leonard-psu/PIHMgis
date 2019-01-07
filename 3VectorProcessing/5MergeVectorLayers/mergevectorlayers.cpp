#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>

#include <stdio.h>

#include "mergevectorlayers.h"
#include "ui_mergevectorlayers.h"

#include "0LibsIO/IOProjectFile.h"
#include "0LibsVector/merge_lines.h"
#include "globals.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MergeVectorLayers Constructor
// Parent is Main Window, filename is the open project text file used to store project details
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MergeVectorLayers::MergeVectorLayers(QWidget *parent, QString filename) :
    QDialog(parent),
    ui(new Ui::MergeVectorLayers)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MergeVectorLayers";

    try {
        ui->setupUi(this);


        filename_open_project = filename;
        bool found_file = false;

        QFile ProjectFile(filename_open_project);
        if ( ProjectFile.open(QIODevice::ReadOnly | QIODevice::Text) == false)
        {
            Log_Error_Message("Unable to Open File: " + filename_open_project);
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
        qDebug() << "Error: MergeVectorLayers is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Load_Project_Settings
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool MergeVectorLayers::Load_Project_Settings()
{
    try {

        QStringList ModuleStringList = ReadModuleLine(filename_open_project,tr("PolylineToLines"));

        if ( ModuleStringList.length() > 0  )
        {
            for (int i=1; i+1 < ModuleStringList.length(); i=i+2)
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
                            Log_Error_Message(file1 + " input does not exist. ");
                        }
                    }
                }
            }
        }

        ModuleStringList = ReadModuleLine(filename_open_project,tr("MergeVectorLayers"));

        QString outputfile = "";

        if ( ModuleStringList.length() > 0 )
        {
            while( ui->tableWidget->rowCount() )
            {
                ui->tableWidget->removeRow( ui->tableWidget->rowCount()-1 );
            }

            ui->tableWidget->setRowCount(0);

            for (int i=1; i < ModuleStringList.length()-2; i++)
            {
                ui->tableWidget->insertRow(ui->tableWidget->rowCount());

                int rowlen = ui->tableWidget->rowCount()-1;
                if(rowlen >= 0)
                {
                    QString file1 = ModuleStringList.at(i);
                    bool file1_check = Check_File_Valid(file1);

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
            }

            int id = ModuleStringList.length()-2;
            outputfile = ModuleStringList.at(id);
        }

        /* //TODO make this user option. Disabled for now, so users don't get confused with auto name changing
        int ID = 0;
        QString ID_String = QString("%1").arg(QString::number(ID),3,'0');
        while ( QFile::exists(user_pihmgis_root_folder+"/2VectorProcessing/MergeVectorLayer"+ID_String+".shp") )
        {
            ID ++;
            ID_String = QString("%1").arg(QString::number(ID),3,'0');
        }

        QString outputfile = user_pihmgis_root_folder+"/2VectorProcessing/MergeVectorLayer" + ID_String + ".shp";
*/

        bool outputfile_check = Check_File_Valid(outputfile);
        Check_MergeLayer_Output(outputfile, true);

        ui->tableWidget->resizeColumnsToContents();

        pushButtonSetFocus();

    } catch (...) {
        qDebug() << "Error: MergeVectorLayers::Load_Project_Settings is returning w/o checking";
        return false;
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MergeVectorLayers Deconstructor
// Todo: Check for memory leaks
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MergeVectorLayers::~MergeVectorLayers()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ~MergeVectorLayers";

    try {
        delete ui;
    } catch (...) {
        qDebug() << "Error: ~MergeVectorLayers is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to clear message log
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MergeVectorLayers::Clear_Log()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MergeVectorLayers::Clear_Log()";

    try {

        LogsString = tr("");
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

    } catch (...) {
        qDebug() << "Error: MergeVectorLayers::Clear_Log() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check Log_Error_Message
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MergeVectorLayers::Log_Error_Message(QString message)
{
    try {
        LogsString.append(tr("<span style=\"color:#FF0000\">Error: ") + message + " </span>" +tr("<br>"));
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

        if(redirect_debug_messages_to_log)
        {
            ((PIHMgisDialog*)this->parent())->Log_Message( message );
        }

    } catch (...) {
        qDebug() << "Error: Log_Error_Message is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check Log_Error_Message
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MergeVectorLayers::Log_Message(QString message)
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
bool MergeVectorLayers::Check_File_Valid(QString file)
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
                Log_Error_Message("Check_File_Valid failed, invalid file size: " + size );
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
// Helper Function to focus button selection (needed for users w/o mouse)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MergeVectorLayers::pushButtonSetFocus()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MergeVectorLayers::pushButtonSetFocus()";

    try {
        ui->pushButtonAdd->setDefault(false);
        ui->pushButtonMergeLayer->setDefault(false);
        ui->pushButtonRun->setDefault(false);

        if ( ui->tableWidget->rowCount() == 0 )
        {
            ui->pushButtonAdd->setDefault(true);
            ui->pushButtonAdd->setFocus();
            return;
        }

        if ( ui->lineEditMergeLayer->text() == "" )
        {
            ui->pushButtonMergeLayer->setDefault(true);
            ui->pushButtonMergeLayer->setFocus();
            return;
        }

        ui->pushButtonRun->setDefault(true);
        ui->pushButtonRun->setFocus();
    } catch (...) {
        qDebug() << "Error: MergeVectorLayers::pushButtonSetFocus() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Add Button Clicked Event (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MergeVectorLayers::on_pushButtonAdd_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MergeVectorLayers::on_pushButtonAdd_clicked()";

    try {

        Clear_Log();

        QStringList InputLinesFileNames = QFileDialog::getOpenFileNames(this, "Choose Shape Files", user_pihmgis_root_folder+tr("/2VectorProcessing"), "Shape File(*.shp *.SHP)");
        if ( InputLinesFileNames.length() > 0)
        {
            for (int i=0; i<InputLinesFileNames.length(); i++)
            {
                ui->tableWidget->insertRow(ui->tableWidget->rowCount());

                QString file1 = InputLinesFileNames.at(i);
                bool file1_check = Check_File_Valid(file1);
                int rowlen = ui->tableWidget->rowCount()-1;

                if(file1.length() > 0 )
                {
                    QTableWidgetItem *NewTableItem = new QTableWidgetItem(file1);
                    ui->tableWidget->setItem(rowlen,0,NewTableItem);
                    ui->tableWidget->item(rowlen,0)->setTextColor(QColor(0,0,0));

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
            }

            pushButtonSetFocus();
        }

    } catch (...) {
        qDebug() << "Error: MergeVectorLayers::on_pushButtonAdd_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Remove Button Clicked Event (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MergeVectorLayers::on_pushButtonRemove_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MergeVectorLayers::on_pushButtonRemove_clicked()";

    try {

        ui->tableWidget->removeRow(ui->tableWidget->currentRow());

        //qDebug() << "Row Count = " << ui->tableWidget->rowCount();

        pushButtonSetFocus();
    } catch (...) {
        qDebug() << "Error: MergeVectorLayers::on_pushButtonRemove_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Clear Button Clicked Event  (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MergeVectorLayers::on_pushButtonClear_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MergeVectorLayers::on_pushButtonClear_clicked()";

    try {
        while( ui->tableWidget->rowCount() )
        {
            ui->tableWidget->removeRow( ui->tableWidget->rowCount()-1 );
        }

        pushButtonSetFocus();
    } catch (...) {
        qDebug() << "Error: MergeVectorLayers::on_pushButtonClear_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Merge (Save) Button Clicked Event  (OUTPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MergeVectorLayers::on_pushButtonMergeLayer_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MergeVectorLayers::on_pushButtonMergeLayer_clicked()";

    try {

        Clear_Log();

        QString MergeVectorFileName = QFileDialog::getSaveFileName(this, "Choose Merge Layer", user_pihmgis_root_folder + "/2VectorProcessing","Merge Vector File(*.shp)");
        QString tempString = MergeVectorFileName;
        if ( MergeVectorFileName != nullptr)
        {
            ui->lineEditMergeLayer->setStyleSheet("color: black;");

            if( (tempString.toLower()).endsWith(".shp") == false)
            {
                tempString.append(".shp");
                MergeVectorFileName = tempString;
            }

            bool file1_check = Check_File_Valid(MergeVectorFileName);

            Check_MergeLayer_Output(MergeVectorFileName, true);

            pushButtonSetFocus();
        }

    } catch (...) {
        qDebug() << "Error: MergeVectorLayers::on_pushButtonMergeLayer_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Run Button Clicked Event  (OUTPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MergeVectorLayers::on_pushButtonRun_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MergeVectorLayers::on_pushButtonRun_clicked()";

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
            Log_Error_Message("Split-Line Input File(s) Missing ");
            return;
        }

        bool failure_found = false;

        for (int i=0; i < ui->tableWidget->rowCount(); i++)
        {
            QString file1 = ui->tableWidget->item(i,0)->text();

            bool file1_check = Check_File_Valid(file1);

            if(file1_check)
            {
                if ( ! CheckFileAccess(file1, "ReadOnly") )
                {
                    Log_Error_Message("No Read Access to ... " + file1 );
                    failure_found = true;
                }
            }
            else
            {
                failure_found = true;
            }
        }

        QString file2 = ui->lineEditMergeLayer->text();
        if ( CheckFileAccess(file2, "WriteOnly") == false)
        {
            Log_Error_Message("No Write Access to ... " + file2);
            failure_found = true;
        }

        if(failure_found)
        {
            Log_Error_Message("Input and Output File issues ");
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Run MergeVectorLayers
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Log_Message("Running Merge Vector Split Lines ... ");

        QStringList ProjectIOStringList;
        ProjectIOStringList << "MergeVectorLayers";

        QString OutShpFileName, OutDbfFileName;

        OutShpFileName = ui->lineEditMergeLayer->text();
        OutDbfFileName = OutShpFileName;
        OutDbfFileName.replace(QString(".shp"), QString(".dbf"));

        int row_count = ui->tableWidget->rowCount();

        QStringList shpFileNames;
        QStringList dbfFileNames;

        for (int i=0; i < row_count; i++)
        {
            QString InpShpFileName = ui->tableWidget->item(i,0)->text();
            QString InpDbfFileName = InpShpFileName;

            InpDbfFileName.replace(QString(".shp"), QString(".dbf"));

            shpFileNames.append(InpShpFileName);
            dbfFileNames.append(InpDbfFileName);

            ProjectIOStringList << InpShpFileName;
        }

        ProjectIOStringList << OutShpFileName;

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Run merge_lines
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        int ErrorMrg = merge_lines( shpFileNames, dbfFileNames, OutShpFileName, OutDbfFileName );
        if ( ErrorMrg == 1 || ErrorMrg == 5 || ErrorMrg == 8 )
        {
            Log_Error_Message("Non-Arc Layer specified... ");
            return;
        }
        else if ( ErrorMrg != 0 )
        {
            Log_Error_Message("Merge Vector Split Lines Processing Failed ... ");
            Log_Error_Message("RETURN CODE: ... " + QString::number(ErrorMrg) );
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update Project file
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        if ( ProjectIOStringList.length() > 2)
        {
            WriteModuleLine(filename_open_project, ProjectIOStringList);
        }

        ProjectIOStringList.clear();

        QString MergeFileNameInVector = ui->lineEditMergeLayer->text();
        QString MergeFileNameInDomainDecomposition = MergeFileNameInVector;
        MergeFileNameInDomainDecomposition.replace("2VectorProcessing","3DomainDecomposition");

        ProjectIOStringList << "MergeVectorDomainDecomposition" << MergeFileNameInVector << MergeFileNameInDomainDecomposition;
        WriteModuleLine(filename_open_project, ProjectIOStringList);
        ProjectIOStringList.clear();

        bool removed = QFile::remove(MergeFileNameInDomainDecomposition);
        if(removed == false)
        {
            Log_Error_Message("Failed to remove file " + MergeFileNameInDomainDecomposition);
            return;
        }
        bool copied = QFile::copy(MergeFileNameInVector,MergeFileNameInDomainDecomposition);
        if(copied == false)
        {
            Log_Error_Message("Failed to copy file " + MergeFileNameInDomainDecomposition);
            return;
        }

        MergeFileNameInVector.replace(".shp",".shx");
        MergeFileNameInDomainDecomposition.replace(".shp",".shx");

        removed = QFile::remove(MergeFileNameInDomainDecomposition);
        if(removed == false)
        {
            Log_Error_Message("Failed to remove file " + MergeFileNameInDomainDecomposition);
            return;
        }
        copied = QFile::copy(MergeFileNameInVector,MergeFileNameInDomainDecomposition);
        if(copied == false)
        {
            Log_Error_Message("Failed to copy file " + MergeFileNameInDomainDecomposition);
            return;
        }

        MergeFileNameInVector.replace(".shx",".dbf");
        MergeFileNameInDomainDecomposition.replace(".shx",".dbf");

        removed = QFile::remove(MergeFileNameInDomainDecomposition);
        if(removed == false)
        {
            Log_Error_Message("Failed to remove file " + MergeFileNameInDomainDecomposition);
            return;
        }
        copied = QFile::copy(MergeFileNameInVector,MergeFileNameInDomainDecomposition);
        if(copied == false)
        {
            Log_Error_Message("Failed to copy file " + MergeFileNameInDomainDecomposition);
            return;
        }
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update Message box
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Clear_Log();

        Log_Message("Merge Vector Split Lines Processing Completed.");

        ui->pushButtonRun->setDefault(false);
        ui->pushButtonClose->setDefault(true);
        ui->pushButtonClose->setFocus();

    } catch (...) {
        qDebug() << "Error: MergeVectorLayers::on_pushButtonRun_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Close button event
// TODO, Decide on keeping button next highlights or not
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MergeVectorLayers::on_pushButtonClose_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MergeVectorLayers::on_pushButtonClose_clicked()";

    try {
        //QStringList default_params; default_params << "WORKFLOW4" << "WORKFLOW8";
        //QMetaObject::invokeMethod(parent(),"set_defaults",Q_ARG(QStringList,default_params));
        close();
    } catch (...) {
        qDebug() << "Error: MergeVectorLayers::on_pushButtonClose_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Help button event
// TODO, Need cataract server back online
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MergeVectorLayers::on_pushButtonHelp_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MergeVectorLayers::on_pushButtonHelp_clicked()";

    try {
        //        LogsString = tr("");
        //        if ( ! QDesktopServices::openUrl(QUrl("http://cataract.cee.psu.edu/PIHM/index.php/PIHMgis_3.0#Merge_Vector_Layers")) )
        //            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Load HTTP Link ... </span>")+tr("<br>"));
        //        ui->textBrowserLogs->setHtml(LogsString);
        //        ui->textBrowserLogs->repaint();
    } catch (...) {
        qDebug() << "Error: MergeVectorLayers::on_pushButtonHelp_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to assist if MergeLayer OUTPUT file exists (returns true) or does not (returns false)
// Will color red and warning if exists with color_and_message_if_exists=true
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool MergeVectorLayers::Check_MergeLayer_Output(QString file, bool color_and_message_if_exists){

    if(print_debug_messages)
        qDebug() << "INFO: Check_MergeLayer_Output()";

    bool result = false;

    try {

        if( fileExists(file) )
        {
            if(color_and_message_if_exists)
            {
                Log_Message("Warning: MergeLayer output already exists: " + file + " You may need to delete these files.");
            }

            ui->lineEditMergeLayer->setStyleSheet("color: red;");
            ui->lineEditMergeLayer->setText(file);
            result = true;
        }
        else
        {
            ui->lineEditMergeLayer->setStyleSheet("color: black;");
            ui->lineEditMergeLayer->setText(file);

            result = false;
        }

    } catch (...) {
        qDebug() << "Error: Check_MergeLayer_Output is returning w/o checking";
        result = false;
    }

    return result;
}
