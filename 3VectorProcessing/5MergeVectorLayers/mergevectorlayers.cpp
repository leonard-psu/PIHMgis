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
            }
        }

        ModuleStringList = ReadModuleLine(filename_open_project,tr("MergeVectorLayers"));
        if ( ModuleStringList.length() > 0 )
        {
            while( ui->tableWidget->rowCount() )
                ui->tableWidget->removeRow( ui->tableWidget->rowCount()-1 );
            ui->tableWidget->setRowCount(0);

            for (int i=1; i<ModuleStringList.length()-2; i++)
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
                        LogsString.append(tr("<span style=\"color:#FF0000\">Error: ") + file1 + tr(" input does not exist. </span>") +tr("<br>"));
                        ui->tableWidget->item(rowlen,0)->setTextColor(Qt::red);
                    }
                    ui->tableWidget->item(rowlen,0)->setTextAlignment(Qt::AlignRight);
                    ui->tableWidget->item(rowlen,0)->setTextAlignment(Qt::AlignVCenter);

                    //qDebug() << i << " " << InpPolygonFileName << " <> " << OutPolygonFileName << "\n";

                }
            }
        }


        int ID = 0;
        QString ID_String = QString("%1").arg(QString::number(ID),3,'0');
        while ( QFile::exists(user_pihmgis_root_folder+"/2VectorProcessing/MergeVectorLayer"+ID_String+".shp") )
        {
            ID ++;
            ID_String = QString("%1").arg(QString::number(ID),3,'0');
        }

        QString outputfile = user_pihmgis_root_folder+"/2VectorProcessing/MergeVectorLayer" + ID_String + ".shp";
        bool outputfile_check = Check_File_Valid(outputfile);

        Check_MergeLayer_Output(outputfile, true);

        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();
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
// Add Button Clicked Event  (INPUT)
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
                        LogsString.append(tr("<span style=\"color:#FF0000\">Error: ") + file1 + tr(" input does not exist. </span>") +tr("<br>"));
                        ui->tableWidget->item(rowlen,0)->setTextColor(Qt::red);
                    }

                    ui->tableWidget->item(rowlen,0)->setTextAlignment(Qt::AlignRight);
                    ui->tableWidget->item(rowlen,0)->setTextAlignment(Qt::AlignVCenter);
                }
            }

            pushButtonSetFocus();
        }

        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

    } catch (...) {
        qDebug() << "Error: MergeVectorLayers::on_pushButtonAdd_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Remove Button Clicked Event  (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MergeVectorLayers::on_pushButtonRemove_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MergeVectorLayers::on_pushButtonRemove_clicked()";

    try {
        ui->tableWidget->removeRow(ui->tableWidget->currentRow());

        qDebug() << "Row Count = " << ui->tableWidget->rowCount();

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
            ui->tableWidget->removeRow( ui->tableWidget->rowCount()-1 );

        qDebug() << "Row Count = " << ui->tableWidget->rowCount();

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

            if( ! (tempString.toLower()).endsWith(".shp") )
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
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Split-Line Input File(s) Missing </span>")+tr("<br>"));
            return;
        }

        bool failure_found = false;

        for (int i=0; i<ui->tableWidget->rowCount(); i++)
        {
            QString file1 = ui->tableWidget->item(i,0)->text();

            bool file1_check = Check_File_Valid(file1);

            if(file1_check)
            {
                if ( ! CheckFileAccess(file1, "ReadOnly") )
                {
                    LogsString.append(tr("<span style=\"color:#FF0000\">Error: No Read Access to ... </span>") + file1 +tr("<br>"));
                    failure_found = true;
                }
            }
            else
            {
                failure_found = true;
            }
        }

        QString file2 = ui->lineEditMergeLayer->text();
        if ( ! CheckFileAccess(file2, "WriteOnly") )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">Error: No Write Access to ... </span>") + file2 + tr("<br>"));
            failure_found = true;
        }

        if(failure_found)
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Input and Output File issues </span>")+ tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
            return;
        }


        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Run MergeVectorLayers
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        LogsString.append("Running Merge Vector Split Lines ... <br>");
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

        QStringList ProjectIOStringList;
        ProjectIOStringList << "MergeVectorLayers";


        //QString InpShpFileName, InpDbfFileName;
        QString OutShpFileName, OutDbfFileName;

        OutShpFileName = ui->lineEditMergeLayer->text();
        OutDbfFileName = OutShpFileName;
        OutDbfFileName.replace(QString(".shp"), QString(".dbf"));

        qDebug() << "OutFileName: " << OutShpFileName << " # " << OutDbfFileName;

        int row_count = ui->tableWidget->rowCount();
        const char **shpFileNamesChar = new const char*[row_count];
        const char **dbfFileNamesChar = new const char*[row_count];

        for (int i=0; i < row_count; i++)
        {
            QString InpShpFileName = ui->tableWidget->item(i,0)->text();
            QString InpDbfFileName = InpShpFileName;
            InpDbfFileName.replace(QString(".shp"), QString(".dbf"));

            qDebug() << InpShpFileName << " # " << InpDbfFileName;

            shpFileNamesChar[i] = new char[InpShpFileName.length()+1];
            dbfFileNamesChar[i] = new char[InpDbfFileName.length()+1];

            sprintf( (char *)shpFileNamesChar[i],"%s", qPrintable(InpShpFileName) );
            sprintf( (char *)dbfFileNamesChar[i],"%s", qPrintable(InpDbfFileName) );

            qDebug () << shpFileNamesChar[i];

            ProjectIOStringList << InpShpFileName;
        }

        ProjectIOStringList << OutShpFileName;


        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Run merge_lines
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        int ErrorMrg = merge_lines( shpFileNamesChar, dbfFileNamesChar, ui->tableWidget->rowCount(), (char *)qPrintable(OutShpFileName), (char *)qPrintable(OutDbfFileName) );
        if ( ErrorMrg == 1 || ErrorMrg == 5 || ErrorMrg == 8 )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">Error: Non-Arc Layer specified... </span>")+tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
            return;
        }
        else if ( ErrorMrg != 0 )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Merge Vector Split Lines Processing Failed ... </span>")+tr("<br>"));
            LogsString.append(tr("<span style=\"color:#FF0000\">RETURN CODE: ... </span>")+QString::number(ErrorMrg)+tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update Project file
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        if ( ProjectIOStringList.length() > 2)
            WriteModuleLine(filename_open_project, ProjectIOStringList);
        ProjectIOStringList.clear();

        QString MergeFileNameInVector = ui->lineEditMergeLayer->text();
        QString MergeFileNameInDomainDecomposition = MergeFileNameInVector;
        MergeFileNameInDomainDecomposition.replace("2VectorProcessing","3DomainDecomposition");

        ProjectIOStringList << "MergeVectorDomainDecomposition" << MergeFileNameInVector << MergeFileNameInDomainDecomposition;
        WriteModuleLine(filename_open_project, ProjectIOStringList);
        ProjectIOStringList.clear();


        QFile::remove(MergeFileNameInDomainDecomposition);
        QFile::copy(MergeFileNameInVector,MergeFileNameInDomainDecomposition);

        MergeFileNameInVector.replace(".shp",".shx");
        MergeFileNameInDomainDecomposition.replace(".shp",".shx");
        QFile::remove(MergeFileNameInDomainDecomposition);
        QFile::copy(MergeFileNameInVector,MergeFileNameInDomainDecomposition);

        MergeFileNameInVector.replace(".shx",".dbf");
        MergeFileNameInDomainDecomposition.replace(".shx",".dbf");
        QFile::remove(MergeFileNameInDomainDecomposition);
        QFile::copy(MergeFileNameInVector,MergeFileNameInDomainDecomposition);

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update Message box
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Clear_Log();

        LogsString.append(tr("<br><b>Merge Vector Split Lines Processing Completed.</b>")+tr("<br>"));
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

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

        if(  fileExists(file) )
        {
            if(color_and_message_if_exists)
            {
                LogsString.append(tr("<span style=\"color:#FF0000\">Warning: MergeLayer output already exists: </span>") + file +tr(" You may need to delete these files.<br>"));
                ui->textBrowserLogs->setHtml(LogsString);
                ui->textBrowserLogs->repaint();
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
