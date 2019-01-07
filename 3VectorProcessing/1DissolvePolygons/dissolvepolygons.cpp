#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>

#include "dissolvepolygons.h"
#include "ui_dissolvepolygons.h"

#include "0LibsIO/IOProjectFile.h"
#include "0LibsVector/dissolve.h"
#include "0LibsVector/dissolve_ogr.h"
#include "1ProjectManagement/VariableSettings/variablesettings.h"

#include "globals.h"

static QString dissolve_name = "new_layer";

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DissolvePolygons Constructor
// Parent is Main Window, filename is the open project text file used to store project details
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DissolvePolygons::DissolvePolygons(QWidget *parent, QString filename) :
    QDialog(parent),
    ui(new Ui::DissolvePolygons)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start DissolvePolygons";

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

    } catch (...) {
        qDebug() << "Error: DissolvePolygons is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Load_Project_Settings
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool DissolvePolygons::Load_Project_Settings()
{
    try {

        QString InpPolygonFileName, OutPolygonFileName;

        QStringList ModuleStringList = ReadModuleLine(filename_open_project,tr("CatchmentRasterVector"));
        if ( ModuleStringList.length() > 0  )
        {
            QString file1 = ModuleStringList.at(2);
            if(file1.length() > 0 )
            {
                bool file1_check = Check_File_Valid(file1);

                ui->tableWidget->insertRow(ui->tableWidget->rowCount());

                if(file1_check)
                {
                    QTableWidgetItem *NewTableItem = new QTableWidgetItem(file1);
                    if(NewTableItem != nullptr)
                    {
                        int rowlen = ui->tableWidget->rowCount()-1;
                        if(rowlen >= 0)
                        {
                            ui->tableWidget->setItem(rowlen,0,NewTableItem);
                            ui->tableWidget->item(rowlen,0)->setTextColor(Qt::black);
                        }
                    }
                }
                else
                {
                    QTableWidgetItem *NewTableItem = new QTableWidgetItem(file1);
                    if(NewTableItem != nullptr)
                    {
                        int rowlen = ui->tableWidget->rowCount()-1;
                        if(rowlen >= 0)
                        {
                            ui->tableWidget->setItem(rowlen,0,NewTableItem);
                            ui->tableWidget->item(rowlen,0)->setTextColor(Qt::red);

                            Log_Error_Message(file1 + " input does not exist. ");
                        }
                    }
                }
            }

            OutPolygonFileName = ModuleStringList.at(2);
            if(OutPolygonFileName.length() > 0 )
            {
                OutPolygonFileName.replace(".shp","_dis.shp");
                bool file2_check = Check_File_Valid(OutPolygonFileName);
                if(!file2_check)
                {
                    QTableWidgetItem *NewTableItem = new QTableWidgetItem(OutPolygonFileName);
                    if(NewTableItem != nullptr)
                    {
                        int rowlen = ui->tableWidget->rowCount()-1;
                        if(rowlen >= 0)
                        {
                            ui->tableWidget->setItem(rowlen,1,NewTableItem);
                            ui->tableWidget->item(rowlen,1)->setTextColor(Qt::black);
                        }
                    }
                }
                else
                {
                    Log_Message("Warning: " + OutPolygonFileName + " Output already exist. ");

                    QTableWidgetItem *NewTableItem = new QTableWidgetItem(OutPolygonFileName);
                    if(NewTableItem != nullptr)
                    {
                        int rowlen = ui->tableWidget->rowCount()-1;
                        if(rowlen >= 0)
                        {
                            ui->tableWidget->setItem(rowlen,1,NewTableItem);
                            ui->tableWidget->item(rowlen,1)->setTextColor(Qt::red);
                        }
                    }
                }

            }
            OutPolygonFileName = "";
        }

        Clear_Log();

        ModuleStringList = ReadModuleLine(filename_open_project,tr("DissolvePolygons"));
        if ( ModuleStringList.length() > 0 )
        {
            while( ui->tableWidget->rowCount() )
            {
                ui->tableWidget->removeRow( ui->tableWidget->rowCount()-1 );
            }

            ui->tableWidget->setRowCount(0);

            for (int i=1; i+1<ModuleStringList.length(); i=i+2)
            {
                ui->tableWidget->insertRow(ui->tableWidget->rowCount());

                QString file1 = ModuleStringList.at(i);
                QString file2 = ModuleStringList.at(i+1);

                bool file1_check = Check_File_Valid(file1);
                bool file2_check = Check_File_Valid(file2);

                if(file1.length() > 0 )
                {
                    QTableWidgetItem *NewTableItem = new QTableWidgetItem(file1);
                    if(NewTableItem != nullptr)
                    {
                        int rowlen = ui->tableWidget->rowCount()-1;
                        if(rowlen >= 0)
                        {
                            ui->tableWidget->setItem(rowlen,0,NewTableItem);
                            if(file1_check)
                            {
                                ui->tableWidget->item(rowlen,0)->setTextColor(Qt::black);
                            }
                            else
                            {
                                Log_Error_Message(file2 + " input does not exist. ");
                                ui->tableWidget->item(rowlen,0)->setTextColor(Qt::red);
                            }

                            ui->tableWidget->item(rowlen,0)->setTextAlignment(Qt::AlignRight);
                            ui->tableWidget->item(rowlen,0)->setTextAlignment(Qt::AlignVCenter);
                        }
                    }
                }

                if(file2.length() > 0 )
                {
                    QTableWidgetItem *NewTableItem = new QTableWidgetItem(file2);
                    if(NewTableItem != nullptr)
                    {
                        int rowlen = ui->tableWidget->rowCount()-1;
                        if(rowlen >= 0)
                        {
                            ui->tableWidget->setItem(rowlen,1,NewTableItem);
                            if(file2_check)
                            {
                                Log_Message("Warning: " + file2 + " output already exists. ");
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

                ui->textBrowserLogs->setHtml(LogsString);
                ui->textBrowserLogs->repaint();
            }
        }

        ui->tableWidget->resizeColumnsToContents();

        pushButtonSetFocus();

    } catch (...) {
        qDebug() << "Error: DissolvePolygons::Load_Project_Settings is returning w/o checking";
        return false;
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DissolvePolygons Deconstructor
// Todo: Check for memory leaks
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DissolvePolygons::~DissolvePolygons()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ~DissolvePolygons";

    try {
        delete ui;
    } catch (...) {
        qDebug() << "Error: ~DissolvePolygons is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to focus button selection (needed for users w/o mouse)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DissolvePolygons::pushButtonSetFocus()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start DissolvePolygons::pushButtonSetFocus()";

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
        qDebug() << "Error: DissolvePolygons::pushButtonSetFocus() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to clear message log
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DissolvePolygons::Clear_Log()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start DissolvePolygons::Clear_Log()";

    try {
        LogsString = tr("");
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

    } catch (...) {
        qDebug() << "Error: DissolvePolygons::Clear_Log() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check Log_Error_Message
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DissolvePolygons::Log_Error_Message(QString message)
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
void DissolvePolygons::Log_Message(QString message)
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
bool DissolvePolygons::Check_File_Valid(QString file)
{
    if(print_debug_messages)
        qDebug() << "INFO: Check_File_Valid()";

    bool result = false;

    try {
        //qDebug() << "INFO: Check_File_Valid() " << file;

        bool fileExists = QFileInfo::exists(file) && QFileInfo(file).isFile();
        return fileExists;

        /* DOES NOT WORK WITH SHP
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
*/
    } catch (...) {
        qDebug() << "Error: Check_File_Valid is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Add Button Clicked Event (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DissolvePolygons::on_pushButtonAdd_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start DissolvePolygons::on_pushButtonAdd_clicked()";

    try {

        Clear_Log();

        QTableWidgetItem *NewTableItem;

        QStringList InputPolygonsFileNames = QFileDialog::getOpenFileNames(this, "Choose Shape Files", user_pihmgis_root_folder +tr("/2VectorProcessing"), "Shape File(*.shp *.SHP)");
        if ( InputPolygonsFileNames.length() > 0)
        {
            for (int i=0; i<InputPolygonsFileNames.length(); i++)
            {
                ui->tableWidget->insertRow(ui->tableWidget->rowCount());

                QString file1 = InputPolygonsFileNames.at(i);
                QString file2 = file1.replace(".shp","_dis.shp");

                bool file1_check = Check_File_Valid(file1);
                bool file2_check = Check_File_Valid(file2);

                NewTableItem = new QTableWidgetItem(file1);
                ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,NewTableItem);

                if(file1_check)
                {
                    ui->tableWidget->item(ui->tableWidget->rowCount()-1,0)->setTextColor("color: black;");
                }
                else
                {
                    Log_Error_Message(file2 + " input does not exist. ");
                    ui->tableWidget->item(ui->tableWidget->rowCount()-1,0)->setTextColor(QColor(0, 180, 0));
                }
                ui->tableWidget->item(ui->tableWidget->rowCount()-1,0)->setTextAlignment(Qt::AlignRight);
                ui->tableWidget->item(ui->tableWidget->rowCount()-1,0)->setTextAlignment(Qt::AlignVCenter);

                NewTableItem = new QTableWidgetItem(file2);
                ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,NewTableItem);

                if(file2_check)
                {
                    Log_Message("Warning: " + file2 + " output already exists. ");
                    ui->tableWidget->item(ui->tableWidget->rowCount()-1,1)->setTextColor("color: red;");
                }
                else
                {
                    ui->tableWidget->item(ui->tableWidget->rowCount()-1,1)->setTextColor("color: black;");
                }

                ui->tableWidget->item(ui->tableWidget->rowCount()-1,1)->setTextAlignment(Qt::AlignRight);
                ui->tableWidget->item(ui->tableWidget->rowCount()-1,1)->setTextAlignment(Qt::AlignVCenter);
            }

            pushButtonSetFocus();
        }

        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

    } catch (...) {
        qDebug() << "Error: DissolvePolygons::on_pushButtonAdd_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Remove Button Clicked Event (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DissolvePolygons::on_pushButtonRemove_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start DissolvePolygons::on_pushButtonRemove_clicked()";

    try {
        ui->tableWidget->removeRow(ui->tableWidget->currentRow());

        //qDebug() << "Row Count = " << ui->tableWidget->rowCount();

        pushButtonSetFocus();
    } catch (...) {
        qDebug() << "Error: DissolvePolygons::on_pushButtonRemove_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Clear Button Clicked Event (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DissolvePolygons::on_pushButtonClear_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start DissolvePolygons::on_pushButtonClear_clicked()";

    try {

        while( ui->tableWidget->rowCount() )
        {
            ui->tableWidget->removeRow( ui->tableWidget->rowCount()-1 );
        }
        //ui->tableWidget->setRowCount(0);
        //qDebug() << "Row Count = " << ui->tableWidget->rowCount();

        pushButtonSetFocus();
    } catch (...) {
        qDebug() << "Error: DissolvePolygons::on_pushButtonClear_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Run Button Clicked Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DissolvePolygons::on_pushButtonRun_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start DissolvePolygons::on_pushButtonRun_clicked()";

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
            Log_Error_Message("Polygon Input File(s) Missing ");
            return;
        }

        bool dissolve_method_two = true;
        if( ui->radioButton_dissolve_method1->isChecked())
        {
            dissolve_method_two = false;
        }

        bool failure_found = false;

        for (int i = 0; i < ui->tableWidget->rowCount(); i++)
        {
            QString file1 = ui->tableWidget->item(i,0)->text();
            QString file2 = ui->tableWidget->item(i,1)->text();

            bool file1_check = Check_File_Valid(file1);
            bool file2_check = Check_File_Valid(file2);

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

            if(file2_check)
            {
                Log_Error_Message("Polygon Output File already exists "+ file2);
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
            Log_Error_Message("Polygon Input and Output File issues ");
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Run Dissolve Polygons
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Log_Message("Running Dissolve Polygons ");

        QStringList ProjectIOStringList;
        ProjectIOStringList << "DissolvePolygons";

        for (int i=0; i < ui->tableWidget->rowCount(); i++)
        {
            QString InpShpFileName, InpDbfFileName;
            QString OutShpFileName, OutDbfFileName, OutShxFileName;

            InpShpFileName = ui->tableWidget->item(i,0)->text();
            InpDbfFileName = InpShpFileName;
            InpDbfFileName.replace(QString(".shp"), QString(".dbf"));

            OutShpFileName = ui->tableWidget->item(i,1)->text();
            OutDbfFileName = OutShpFileName;
            OutDbfFileName.replace(QString(".shp"), QString(".dbf"));
            OutShxFileName = OutShpFileName;
            OutShxFileName.replace(QString(".shp"), QString(".shx"));

            //qDebug() << InpShpFileName << " # " << InpDbfFileName;
            //qDebug() << OutShpFileName << " # " << OutDbfFileName;

            if(dissolve_method_two == false)
            {
                // DISSOLVE METHOD 1 : START
                int ErrorDis = dissolve(InpShpFileName, InpDbfFileName, OutShpFileName, OutDbfFileName);
                // DISSOLVE METHOD 1 : FINISH

                if ( ErrorDis != 0 )
                {
                    Log_Error_Message("Dissolve Polygons Processing Failed ... ");
                    Log_Error_Message("RETURN CODE: ... " + QString::number(ErrorDis));
                    return;
                }
                else
                {
                    Log_Message("Dissolving Method 1... " + InpShpFileName);
                    ProjectIOStringList << InpShpFileName << OutShpFileName;
                }
            }
            else
            {
                // DISSOLVE METHOD 2 : START
                int my_argc = 5;
                char **my_argv;
                my_argv = (char ** ) malloc(my_argc*sizeof(char *));
                for ( int j=0; j<my_argc; j++ )
                {
                    my_argv[j] = (char *) malloc(100*sizeof(char));
                }

                sprintf(my_argv[0],"%s",qPrintable("dummy") );
                sprintf(my_argv[1],"%s",qPrintable("-a") );
                sprintf(my_argv[2],"%s",qPrintable("Watershed") );
                sprintf(my_argv[3],"%s",qPrintable(InpShpFileName) );
                sprintf(my_argv[4],"%s",qPrintable(user_pihmgis_root_folder+user_pihmgis_project_folder + "") );

                //qDebug() << "my_argv";
                //qDebug() <<  my_argv[0] << my_argv[1] << my_argv[2] << my_argv[3] << my_argv[4];

                //Not checking removed status as files may not exist
                bool removed = QFile::remove( user_pihmgis_root_folder+user_pihmgis_project_folder + "/" + dissolve_name + ".shp" );
                removed = QFile::remove( user_pihmgis_root_folder+user_pihmgis_project_folder + "/" + dissolve_name + ".shx" );
                removed = QFile::remove( user_pihmgis_root_folder+user_pihmgis_project_folder + "/" + dissolve_name + ".dbf" );

                int ErrorDis = dissolve_ogr(my_argc, my_argv);

                //Not checking removed status as files may not exist
                removed = QFile::remove( OutShpFileName );
                removed = QFile::remove( OutShxFileName );
                removed = QFile::remove( OutDbfFileName );

                bool copied = QFile::copy( user_pihmgis_root_folder+user_pihmgis_project_folder + "/" + dissolve_name + ".shp", OutShpFileName );
                if(copied == false)
                {
                    Log_Error_Message("Failed to copy " + OutShpFileName );
                    return;
                }
                copied = QFile::copy( user_pihmgis_root_folder+user_pihmgis_project_folder + "/" + dissolve_name + ".shx", OutShxFileName );
                if(copied == false)
                {
                    Log_Error_Message("Failed to copy " + OutShxFileName );
                    return;
                }
                copied = QFile::copy( user_pihmgis_root_folder+user_pihmgis_project_folder + "/" + dissolve_name + ".dbf", OutDbfFileName );
                if(copied == false)
                {
                    Log_Error_Message("Failed to copy " + OutDbfFileName );
                    return;
                }

                // DISSOLVE METHOD 2 : FINISH
                if( ErrorDis == 5000)
                {
                    Log_Message("Warning: Potential Feature/Geometry errors were discovered. ... " + InpShpFileName);
                    Log_Message("Warning: It is recommened to check the shapefiles with GIS tools.... ");
                }
                else if ( ErrorDis == 1 || ErrorDis == 3 || ErrorDis == 8 )
                {
                    Log_Message("Warning: Skipping Non-Polygon Layer ... " + InpShpFileName);
                }
                else if ( ErrorDis != 0 )
                {
                    Log_Error_Message("Dissolve Polygons Processing Failed ... ");
                    Log_Error_Message("RETURN CODE: ... " + QString::number(ErrorDis));
                    return;
                }
                else
                {
                    Log_Message("Dissolving Method 2... " + InpShpFileName);

                    ProjectIOStringList << InpShpFileName << OutShpFileName;
                }
            }
        }


        if ( ProjectIOStringList.length() > 2)
            WriteModuleLine(filename_open_project, ProjectIOStringList);

        ProjectIOStringList.clear();

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update Message box
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Clear_Log();

        Log_Message("Dissolve Polygons Processing Completed.");

        ui->pushButtonRun->setDefault(false);
        ui->pushButtonClose->setDefault(true);
        ui->pushButtonClose->setFocus();

    } catch (...) {
        qDebug() << "Error: DissolvePolygons::on_pushButtonClear_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Close button event
// TODO, Decide on keeping button next highlights or not
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DissolvePolygons::on_pushButtonClose_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start DissolvePolygons::on_pushButtonClose_clicked()";

    try {
        //QStringList default_params; default_params << "WORKFLOW3" << "POLYGON";
        //QMetaObject::invokeMethod(parent(),"set_defaults",Q_ARG(QStringList,default_params));
        close();
    } catch (...) {
        qDebug() << "Error: DissolvePolygons::on_pushButtonClose_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Help button event
// TODO, Need cataract server back online
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DissolvePolygons::on_pushButtonHelp_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start DissolvePolygons::on_pushButtonClose_clicked()";

    try {
        //        LogsString = tr("");
        //        if ( ! QDesktopServices::openUrl(QUrl("http://cataract.cee.psu.edu/PIHM/index.php/PIHMgis_3.0#Dissolve_Polygon")) )
        //            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Load HTTP Link ... </span>")+tr("<br>"));
        //        ui->textBrowserLogs->setHtml(LogsString);
        //        ui->textBrowserLogs->repaint();
    } catch (...) {
        qDebug() << "Error: DissolvePolygons::on_pushButtonClose_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Settings button event
// User can change dissolve eplison value
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DissolvePolygons::on_pushButtonSettings_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start DissolvePolygons::on_pushButtonSettings_clicked()";

    try {

        VariableSettings *vs = new VariableSettings(this);
        vs->setModal(true);
        vs->exec();

    } catch (...) {
        qDebug() << "Error: DissolvePolygons::on_pushButtonSettings_clicked() is returning w/o checking";
    }
}
