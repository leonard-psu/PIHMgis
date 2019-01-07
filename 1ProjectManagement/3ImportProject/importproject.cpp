#include <QtGui>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>

#include "importproject.h"
#include "ui_importproject.h"
#include "globals.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ImportProject Constructor
// Parent is Main Window, filename is the open project text file used to store project details
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ImportProject::ImportProject(QWidget *parent)
    : QDialog(parent), ui(new Ui::ImportProject)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ImportProject";

    try {
        ui->setupUi(this);

        //ui->lineEditNew->setText(user_pihmgis_root_folder + user_pihmgis_project_folder); //TODO
        ui->lineEditNew->setText(user_pihmgis_root_folder); //TODO
        //ui->lineEdit_Data_Base_Folder->setText(user_pihmgis_root_folder );

        //TODO
        //filename_open_project = user_pihmgis_root_folder + user_pihmgis_project_folder + "/OpenProject.txt";

        QString name = QDateTime::currentDateTime().date().toString();
        name = name.simplified().remove(' ');
        name = name.append(".pihmgis");
        //Create Default Name
        //ui->new_lineEdit_ProjectFile->setText(filename_open_project); //TODO
        ui->new_lineEdit_ProjectFile->setText(name); //TODO

        ui->pushButtonProject->setDefault(true);
        ui->pushButtonProject->setFocus();

    } catch (...) {
        qDebug() << "Error: ImportProject";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ImportProject Deconstructor
// Todo: Check for memory leaks
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ImportProject::~ImportProject()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ~ImportProject";
    try {
        delete ui;
    } catch (...) {
        qDebug() << "Error: ~ImportProject";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to clear message log
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ImportProject::Clear_Log()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ImportProject::Clear_Log()";

    try {

        LogsString = tr("");
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

    } catch (...) {
        qDebug() << "Error: ImportProject::Clear_Log() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check Log_Error_Message
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ImportProject::Log_Error_Message(QString message)
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
void ImportProject::Log_Message(QString message)
{
    try {
        LogsString.append(tr("<span style=\"color:#000000\"> ") + message + " </span>")+tr("<br>");
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
// Helper Function to get List of Directories
// BEWARE: I've observed develope paths returned when str is not a valid path
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
QStringList ImportProject::Get_Folder_List(const QString& str)
{
    auto path = QDir::cleanPath(str);
    QStringList result(path);
    while((path = QFileInfo(path).path()).length() < result.last().length())
        result << path;
    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get mapped UNIQUE list of directories
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
QMap<QString,QString> ImportProject::Get_Map_Directories(QString input_file_name, QString new_base_folder)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ImportProject::Get_Map_Directories()";

    QMap<QString,QString> result;

    try {

        QFile inputFile(input_file_name);
        if (inputFile.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            int count = 0;
            QTextStream in(&inputFile);
            while (!in.atEnd())
            {
                QString line = in.readLine();

                if(line.startsWith("#") )
                {
                    //Do nothing
                }
                else
                {
                    if( count > 2) //Ignore first 3 lines
                    {
                        QStringList slist = line.split(",");
                        QStringList rebuilt_list;
                        if ( slist.length() > 1)
                        {
                            for(int i = 1; i < slist.count(); i++)
                            {
                                QString str_value = slist[i];

                                if( str_value.contains('/') || str_value.contains('\\'))
                                {
                                    QFileInfo fi(slist[i]);
                                    QString dir = fi.absolutePath();

                                    if(result.contains(dir))
                                    {
                                        //do nothing
                                    }
                                    else
                                    {
                                        if(dir.isEmpty())
                                        {
                                            //Do nothing output_text_stream << line << "\n";
                                        }
                                        else
                                        {
                                            QStringList fslist = Get_Folder_List(dir);
                                            QString value = dir;

                                            QString replace = dir.replace(fslist.at(1), new_base_folder);
                                            QFileInfo fi2(replace);
                                            bool exists = fi2.exists();

                                            if(exists)
                                            {
                                                if(result.contains(replace))
                                                {
                                                    //do nothing
                                                }
                                                else
                                                {
                                                    result.insert(replace,value);
                                                }
                                            }
                                        }
                                    }
                                }

                            } //End for loop

                        } //End of list
                    }
                }

                count++;
            }

            inputFile.close();
        }


    } catch (...) {
        qDebug() << "Error: ImportProject::Get_Map_Directories()";
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to identify unique folders in older project file and FILLS COMBO BBOX
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
QStringList ImportProject::Find_Project_Directories(QString input_file_name, QString new_base_folder)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ImportProject::Find_Project_Directories()";

    QStringList result;

    try {
        //Key->NEW, Value->OLD Directory
        QMap<QString,QString> map_dir = Get_Map_Directories(input_file_name, new_base_folder);

        ui->comboBox_old_project_dirs->clear();
        if(map_dir.count() > 0)
            ui->comboBox_old_project_dirs->addItem("ALL");
        ui->comboBox_old_project_dirs->addItem("NONE");

        for(auto e : map_dir.keys())
        {
            //qDebug() << "Found: " << e << "," << map_dir.value(e) << '\n';
            result.append(e);
            ui->comboBox_old_project_dirs->addItem(map_dir.value(e));
        }

        //Log_Message("Unique directory count: " + QString::number(map_dir.count()) + tr("<br>"));

    } catch (...) {
        qDebug() << "Error: ImportProject::Find_Project_Directories()";

    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to replace Given value from DropDown List of them in older project file
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ImportProject::Find_Replace_Only_Project_Directories(QString input_file_name, QString new_base_folder, QString only_folder, QString output_file_name)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ImportProject::Find_Replace_All_Project_Directories()";

    bool result = false;

    try {

        if(only_folder.length() < 1)
        {
            return false;
        }
        if(QString::compare("ALL", only_folder, Qt::CaseInsensitive) == 0)
        {
            return false;
        }
        if(QString::compare("None", only_folder, Qt::CaseInsensitive) == 0)
        {
            return false;
        }

        //Key->NEW, Value->OLD Directory
        QMap<QString,QString> map_dir = Get_Map_Directories(input_file_name, new_base_folder);

        //qDebug() << only_folder << '\n';
        //qDebug() << map_dir.key(only_folder) << '\n';
        //qDebug() << map_dir.value(only_folder) << '\n';
        QString replace_value;
        QString old_project;
        QString filename_open_project = user_pihmgis_root_folder + user_pihmgis_project_folder + "/OpenProject.txt";
        bool search = ui->checkBox_Search->isChecked();
        QString data_folder = new_base_folder;

        //INEFFICIENT METHOD
        for(auto e : map_dir.keys())
        {
            QString key = e;
            QString value =  map_dir.value(e);
            //qDebug() << "Found: " << e << "," << map_dir.value(e) << '\n';

            if(QString::compare(only_folder, value, Qt::CaseInsensitive) == 0)
            {
                //qDebug() << "Found: " << e << "," << map_dir.value(e) << '\n';
                replace_value = e;
            }
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Replace Directories
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QFile outputFile(output_file_name);

        if (outputFile.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream output_text_stream(&outputFile);
            QFile inputFile(input_file_name);
            if (inputFile.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                int count = 0;
                QTextStream in(&inputFile);
                while (!in.atEnd())
                {
                    QString line = in.readLine();

                    if(count == 0) //Write new create time
                    {
                        QString format = QString("MMMddyyyyhhmm");
                        QDateTime ProjectDateTime = ProjectDateTime.currentDateTime();
                        output_text_stream << "Created on: " << ProjectDateTime.toString() << "\n";
                    }
                    else if (count == 1) //Replace Working directory
                    {
                        old_project = line;
                        output_text_stream << user_pihmgis_root_folder << '\n';
                    }
                    else if (count == 2) //Replace Project File
                    {
                        output_text_stream << filename_open_project << '\n';
                    }
                    else if (line.startsWith("#"))
                    {
                        //Keep original line
                        output_text_stream << line << '\n';
                    }
                    else
                    {
                        if(search)
                        {
                            QString new_line = line;
                            if(line.contains(only_folder))
                            {
                                //new_line = new_line.replace(only_folder, replace_value);
                                QString new_line = line;
                                QStringList line_split = new_line.split(',');
                                QString rebuilt_list;
                                QListIterator<QString> itr (line_split);
                                while (itr.hasNext())
                                {
                                    QString current = itr.next();
                                    if(current.contains('/'))
                                    {
                                        QString search_result = Find_File_In_Base_Folder(current, data_folder);
                                        rebuilt_list.append(search_result + ",");

                                    }
                                    else
                                    {
                                        rebuilt_list.append(current + ",");
                                    }
                                }

                                //Keep original line
                                output_text_stream << "#Import Replaced " << line << '\n';
                                output_text_stream << rebuilt_list << '\n';
                            }
                            else
                            {
                                output_text_stream << line << '\n';
                            }
                        }
                        else
                        {
                            QString new_line = line;

                            if(line.contains(only_folder))
                            {
                                new_line = new_line.replace(only_folder, replace_value);

                                //Keep original line
                                output_text_stream << "#Import Replaced " << line << '\n';
                                output_text_stream << new_line << '\n';
                            }
                            else
                            {
                                output_text_stream << line << '\n';
                            }
                        }
                    }

                    count++;
                }

                inputFile.close();
            }

            outputFile.close();
        }

        result = true;

    } catch (...) {
        qDebug() << "Error: ImportProject::Find_Replace_All_Project_Directories()";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to find files in new data folder location
// Logic Issue, as finds first occurennce. This will be a problem when shapefiles are copied to other folders.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
QString ImportProject::Find_File_In_Base_Folder(QString input_string, QString data_folder)
{
    QString result = "";

    //Slows GUI Response
    //if(print_debug_messages)
    //    qDebug() << "INFO: Start ImportProject::Find_File_In_Base_Folder()";

    try {

        bool found = false;

        QFileInfo finfo(input_string);
        QString ext = "*." + finfo.completeSuffix();
        QString filename(finfo.fileName());
        QDirIterator it(data_folder, QStringList() << ext, QDir::Files, QDirIterator::Subdirectories);

        while (it.hasNext())
        {
            QString it_filename = it.next();
            QFileInfo file_info(it_filename);
            QString found_filename(file_info.fileName());

            if(QString::compare(filename, found_filename, Qt::CaseSensitive) == 0) //Note CaseSensitive
            {
                if(!found)
                {
                    result = it_filename;
                    found = true;
                }
            }
        }

        if(found)
            return result;

    }
    catch (...) {
        qDebug() << "Error: ImportProject::Find_File_In_Base_Folder()";
    }

    //Give up and return original string
    return input_string;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to identify unique folders and replace ALL of them in older project file
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ImportProject::Find_Replace_All_Project_Directories(QString input_file_name, QString new_base_folder, QString output_file_name)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ImportProject::Find_Replace_All_Project_Directories()";

    bool result = false;

    try {

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Step 1, Create Unique List of Directories Suitable for replacing old project file
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //NEW, OLD Directory
        QMap<QString,QString> map_dir = Get_Map_Directories(input_file_name, new_base_folder);

        //Log_Message("Found: " + QString::number(map_dir.count()) + tr("<br>"));

        bool search = ui->checkBox_Search->isChecked();
        QString new_project = user_pihmgis_root_folder;// + user_pihmgis_project_folder;
        QString filename_open_project = user_pihmgis_root_folder + user_pihmgis_project_folder + "/OpenProject.txt";
        QString old_project;
        QString data_folder = new_base_folder;

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Step 2, Replace Directories
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QFile outputFile(output_file_name);
        if (outputFile.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream output_text_stream(&outputFile);
            QFile inputFile(input_file_name);
            if (inputFile.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                int count = 0;
                QTextStream in(&inputFile);
                while (!in.atEnd())
                {
                    QString line = in.readLine();
                    QStringList linelist = line.split(',');
                    QString line_at_0 = linelist.at(0);

                    if(count == 0) //Write new create time
                    {
                        QString format = QString("MMMddyyyyhhmm");
                        QDateTime ProjectDateTime = ProjectDateTime.currentDateTime();
                        output_text_stream << "Created on: " << ProjectDateTime.toString() << "\n";
                    }
                    else if (count == 1) //Replace Working directory
                    {
                        old_project = line;
                        output_text_stream << user_pihmgis_root_folder << '\n';
                    }
                    else if (count == 2) //Replace Project File
                    {
                        output_text_stream << filename_open_project << '\n';
                    }
                    else if (line.startsWith("#"))
                    {
                        //Keep original line
                        output_text_stream << line << '\n';
                    }
                    else
                    {
                        if(search)
                        {
                            QString new_line = line;
                            QStringList line_split = new_line.split(',');
                            QString rebuilt_list;
                            QListIterator<QString> itr (line_split);
                            while (itr.hasNext())
                            {
                                QString current = itr.next();
                                if(current.contains('/'))
                                {
                                    QString search_result = Find_File_In_Base_Folder(current, data_folder);
                                    rebuilt_list.append(search_result + ",");

                                }
                                else
                                {
                                    rebuilt_list.append(current + ",");
                                }
                            }

                            //Keep original line
                            output_text_stream << "#Import Replaced " << line << '\n';
                            output_text_stream << rebuilt_list << '\n';

                        }
                        else
                        {
                            QString new_line = line;
                            new_line = new_line.replace(old_project, new_project);

                            for(auto e : map_dir.keys())
                            {
                                QString key = e;
                                QString value =  map_dir.value(e);
                                //qDebug() << "Found: " << e << "," << map_dir.value(e) << '\n';
                                //Note swapped, as the key is the new value, while value is the original directory
                                new_line = new_line.replace(value, key);
                            }

                            //Keep original line
                            output_text_stream << "#Import Replaced " << line << '\n';
                            output_text_stream << new_line << '\n';
                        }
                    }

                    count++;
                }

                inputFile.close();
            }

            outputFile.close();
        }

        result = true;

    } catch (...) {
        qDebug() << "Error: ImportProject::Find_Replace_All_Project_Directories()";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button Import Existing Project Clicked Event (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ImportProject::on_pushButtonProject_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ImportProject::on_pushButtonProject_clicked()";

    try {

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Clear Log
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Clear_Log();

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Get Existing File name
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QString OldProjectFileName = QFileDialog::getOpenFileName(this, "Import Existing Project", user_pihmgis_root_folder, "PIHMgis Project (*.pihmgis)");

        if (OldProjectFileName != nullptr)
        {
            QString NewProjectFileName = OldProjectFileName;
            //QString NewProjectFolder = user_pihmgis_root_folder + user_pihmgis_project_folder;
            QString NewProjectFolder = user_pihmgis_root_folder;

            QFile OldOpenProjectFile(OldProjectFileName);
            OldOpenProjectFile.open(QIODevice::ReadOnly | QIODevice::Text);
            QTextStream OldOpenProjectFileTextStream(&OldOpenProjectFile);
            OldOpenProjectFileTextStream.readLine();
            QString OldProjectFolder = OldOpenProjectFileTextStream.readLine();
            OldOpenProjectFile.close();

            ui->lineEdit->setText(OldProjectFileName);
            ui->lineEditOld->setText(OldProjectFolder);
            ui->lineEditNew->setText(NewProjectFolder);

            QFileInfo fi(OldProjectFileName);
            ui->lineEdit_Data_Base_Folder->setText( QString( fi.absolutePath()));

            Find_Project_Directories(OldProjectFileName, fi.absolutePath());

            ui->pushButtonProject->setDefault(false);
            ui->pushButtonImport->setDefault(true);
            ui->pushButtonImport->setFocus();
        }

        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

    } catch (...) {
        qDebug() << "Error: ImportProject::on_pushButtonProject_clicked()";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Close Button Clicked Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ImportProject::on_pushButtonClose_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ImportProject::on_pushButtonClose_clicked()";

    try {
        close();
    } catch (...) {
        qDebug() << "Error: ImportProject::on_pushButtonClose_clicked()";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Import Button Clicked Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ImportProject::on_pushButtonImport_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ImportProject::on_pushButtonImport_clicked()";

    try {

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Clear Log
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Clear_Log();

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check Inputs from GUI
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QString OldProjectFolder = ui->lineEditOld->text();
        QString old_ProjectFileName  = ui->lineEdit->text();
        QString NewProjectFolder = ui->lineEditNew->text();
        QString NewProjectName = ui->new_lineEdit_ProjectFile->text();
        QString data_base_folder = ui->lineEdit_Data_Base_Folder->text();
        QString replace_old_folders =  ui->comboBox_old_project_dirs->currentText();

        if(OldProjectFolder.isEmpty())
        {
            Log_Error_Message("No old project folder name specified: </span>" + OldProjectFolder );
            return;
        }
        if(old_ProjectFileName.isEmpty())
        {
            Log_Error_Message("Old project file name not specified </span>" + old_ProjectFileName );
            return;
        }
        if(NewProjectFolder.isEmpty())
        {
            Log_Error_Message("New project folder not specified: </span>" + NewProjectFolder );
            return;
        }
        if(NewProjectName.isEmpty())
        {
            Log_Error_Message("Need to specify New Project Name: </span>" + NewProjectName  );
            return;
        }
        if(data_base_folder.isEmpty())
        {
            Log_Error_Message("Need to specify New Data Folder Location: </span>" + data_base_folder  );
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check Output from GUI
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        QString new_ProjectFileName = user_pihmgis_root_folder + user_pihmgis_project_folder + "/TempImportFile.txt";
        QString new_OpenProject = user_pihmgis_root_folder + user_pihmgis_project_folder + "/OpenProject.txt";
        QString output_name = user_pihmgis_root_folder + "/" + NewProjectName;

        QFileInfo qfi(new_ProjectFileName);
        if(qfi.exists())
        {
            Log_Message("Removing existing project file = " + new_ProjectFileName );
            bool success = QFile::remove(new_ProjectFileName);
            if(success  == false)
            {
                Log_Error_Message("Problems removing file = " + new_ProjectFileName );
                return;
            }
        }

        QFileInfo qfi2(output_name);
        QString given_suffix = qfi2.suffix();

        if( !QString::compare("pihmgis", given_suffix, Qt::CaseInsensitive) == 0)
        {
            output_name = output_name.append(".pihmgis");
        }

        if(qfi2.exists())
        {
            Log_Message("Removing existing project file = " + output_name  );
            bool success = QFile::remove(output_name);
            if(success == false)
            {
                Log_Error_Message("Problems removing file = " + output_name  );
                return;
            }
        }
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check project folder exists, if not create it
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QString make_folder = user_pihmgis_root_folder + user_pihmgis_project_folder;
        QDir dir(make_folder);

        if (!dir.exists())
        {
            dir.mkpath(make_folder);
            //qDebug() << "Creating folder = " << make_folder;
        }
        else
        {
            //qDebug() << "Folder already exists = " << make_folder;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Copy Project File to new location as temp file
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        Log_Message("Opening Existing Project File = " + old_ProjectFileName  );

        bool copied = QFile::copy(old_ProjectFileName, new_ProjectFileName);
        if(copied == false)
        {
            Log_Error_Message("Failed to copy file = " + old_ProjectFileName  );
            return;
        }
        Log_Message("Copying temporary project tile = " + new_ProjectFileName  );

        if(replace_old_folders.length() < 1)
        {
            //do nothing
        }
        if(QString::compare("ALL", replace_old_folders, Qt::CaseInsensitive) == 0)
        {
            Find_Replace_All_Project_Directories(old_ProjectFileName, data_base_folder, new_ProjectFileName);
        }
        else if(QString::compare("None", replace_old_folders, Qt::CaseInsensitive) == 0)
        {
            //do nothing
        }
        else
        {
            QString only_folder = replace_old_folders;
            Find_Replace_Only_Project_Directories(old_ProjectFileName, data_base_folder, only_folder, new_ProjectFileName);

        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Copy Edited Project File to new location
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        QFileInfo qfi3(output_name);
        if(qfi3.exists())
        {
            Log_Message("Removing existing project file = " + output_name  );
            bool success = QFile::remove(output_name);
            if(success == false)
            {
                Log_Error_Message("Problems removing file = " + output_name );
                return;
            }
        }

        Log_Message("Copying edited project file = " + output_name  );
        copied = QFile::copy(new_ProjectFileName, output_name);
        if(copied == false)
        {
            Log_Error_Message("Failed to copy file = " + new_ProjectFileName  );
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Copy open Project File to new location
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        QFileInfo qfi4(new_OpenProject);
        if(qfi4.exists())
        {
            Log_Message("Removing existing open project file = " + new_OpenProject  );
            bool success = QFile::remove(new_OpenProject);
            if(success == false)
            {
                Log_Error_Message("Problems removing file = " + new_OpenProject  );
                return;
            }
        }

        Log_Message("Creating open project file = " + output_name  );
        copied = QFile::copy(new_ProjectFileName, new_OpenProject);
        if(copied == false)
        {
            Log_Error_Message("Failed to copy file = " + new_ProjectFileName  );
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Finished and let user know
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        LogsString.append(tr("<b>Project Imported Successfully.")+tr("<br>"));
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

        ui->pushButtonImport->setDefault(false);
        ui->pushButtonClose->setDefault(true);
        ui->pushButtonClose->setFocus();


    } catch (...) {
        qDebug() << "Error: ImportProject::on_pushButtonImport_clicked()";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Help button event
// TODO, Need cataract server back online
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ImportProject::on_pushButtonHelp_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ImportProject::on_pushButtonHelp_clicked()";

    try {
        //        LogsString = tr("");
        //        if ( ! QDesktopServices::openUrl(QUrl("http://cataract.cee.psu.edu/PIHM/index.php/PIHMgis_3.0#Import_Project")) )
        //            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Load HTTP Link ... </span>")+tr("<br>"));
        //        ui->textBrowserLogs->setHtml(LogsString);
        //        ui->textBrowserLogs->repaint();
    } catch (...) {
        qDebug() << "Error: ImportProject::on_pushButtonImport_clicked()";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button for base folder location (Clicked Event) INPUT
// This is needed to specify where the data is located. Not always the same location as pihmgis file
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ImportProject::on_pushButtonProject_DataFolder_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ImportProject::on_pushButtonProject_DataFolder_clicked()";

    try {

        QString user_folder_location = QFileDialog::getExistingDirectory(this, "Specify Base Folder Location, where your data is", user_pihmgis_root_folder, 0);
        ui->lineEdit_Data_Base_Folder->setText(user_folder_location);

    } catch (...) {
        qDebug() << "Error: ImportProject::on_pushButtonProject_DataFolder_clicked()";
    }
}
