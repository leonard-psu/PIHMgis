#include "meshspatial.h"
#include "ui_meshspatial.h"

#include "7VisualAnalytics/QCustomPlot/qcustomplot.h"
#include "7VisualAnalytics/QCustomPlotMainWindow/qcustomplotmainwindow.h"

#include "0LibsIO/IOProjectFile.h"
#include "0LibsShape/shapefil.h"
#include "globals.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MeshSpatial Constructor
// Parent is Main Window, filename is the open project text file used to store project details
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MeshSpatial::MeshSpatial(QWidget *parent, QString filename) :
    QDialog(parent),
    ui(new Ui::MeshSpatial)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshSpatial";

    try {
        ui->setupUi(this);

        filename_open_project = filename;
        bool found_file = false;

        QFile ProjectFile(filename_open_project);
        if ( ! ProjectFile.open(QIODevice::ReadOnly | QIODevice::Text) )
        {
            Log_Error_Message("Unable to Open File: </span>" + filename_open_project  );
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
        qDebug() << "Error: MeshSpatial is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MeshSpatial Deconstructor
// Todo: Check for memory leaks
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MeshSpatial::~MeshSpatial()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ~MeshSpatial";

    try {
        delete ui;
    } catch (...) {
        qDebug() << "Error: ~MeshSpatial is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check Log_Error_Message
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MeshSpatial::Log_Error_Message(QString message)
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
void MeshSpatial::Log_Message(QString message)
{
    try {
        LogsString.append(tr("<span style=\"color:#FF0000\"> ") + message + " </span>")+tr("<br>");
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
// Load_Project_Settings
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool MeshSpatial::Load_Project_Settings()
{
    if (print_debug_messages)
        qDebug() << "INFO: MeshSpatial::Load_Project_Settings()";

    try {

        // Start: Set Defaults
        QStringList ModuleStringList = ReadModuleLine(filename_open_project,tr("PIHMSimulation"));
        if ( ModuleStringList.length() > 0  )
        {
            QString folder_Name = ModuleStringList.at(4);
            Check_OutputFolder_Location(folder_Name);

            QString TempFileName = ModuleStringList.at(2);
            Check_Project_Name_Input(TempFileName);

            QString para_filename = folder_Name + "/" + TempFileName +".para";

            Load_Para_Input(para_filename,-1);

        }

        ModuleStringList = ReadModuleLine(filename_open_project,tr("TINShapeLayer"));
        if ( ModuleStringList.length() > 0 )
        {
            QString TempFileName = ModuleStringList.at(3);
            Check_Mesh_Input(TempFileName);
        }
        // End: Set Defaults

        // Start: Fill Form If Module Has Been Run Previously
        ModuleStringList = ReadModuleLine(filename_open_project,tr("MeshSpatial"));

        if ( ModuleStringList.length() > 0 )
        {
            Check_OutputFolder_Location(ModuleStringList.at(1));
            Check_Project_Name_Input(ModuleStringList.at(2));
            Check_Mesh_Input(ModuleStringList.at(8));
        }
        // End: Fill Form If Module Has Been Run Previously

        verifyInputOutputFile();
        pushButtonSetFocus();

    } catch (...) {
        qDebug() << "Error: MeshSpatial::Load_Project_Settings is returning w/o checking";
        return false;
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to clear message log
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MeshSpatial::Clear_Log()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshSpatial::Clear_Log()";

    try {

        LogsString = tr("");
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

    } catch (...) {
        qDebug() << "Error: MeshSpatial::Clear_Log() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Check OutputFolder File exists (INPUT Location of Model)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool MeshSpatial::Check_OutputFolder_Location(QString folder)
{
    if(print_debug_messages)
        qDebug() << "INFO: Check_OutputFolder_Location()";

    bool result = false;

    try {
        QDir dir(folder);

        if(dir.exists())
        {
            ui->lineEditOutputDataFolder->setText(folder);
            ui->lineEditOutputDataFolder->setStyleSheet("color: black;");
            result = true;
        }
        else
        {
            ui->lineEditOutputDataFolder->setText(folder);
            ui->lineEditOutputDataFolder->setStyleSheet("color: red;");
            result = false;
        }

    } catch (...) {
        qDebug() << "Error: Check_OutputFolder_Location is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Check Project_Name value exists (INPUT Location of Model)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool  MeshSpatial::Check_Project_Name_Input(QString value){

    if(print_debug_messages)
        qDebug() << "INFO: Check_Project_Name_Input()";

    bool result = false;

    try {

        if(value.isNull() || value.isEmpty())
        {
            ui->lineEditDataKey->setStyleSheet("color: red;");
            ui->lineEditDataKey->setText("Missing");
            result = false;
        }
        else if(value == QString("Missing"))
        {
            ui->lineEditDataKey->setStyleSheet("color: red;");
            result = false;
        }
        else
        {
            ui->lineEditDataKey->setStyleSheet("color: black;");
            ui->lineEditDataKey->setText(value);
            result = true; //For now assume validators work
        }

    } catch (...) {
        qDebug() << "Error: Check_Project_Name_Input is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Check Mesh exists (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool MeshSpatial::Check_Mesh_Input(QString file){

    if(print_debug_messages)
        qDebug() << "INFO: Check_Mesh_Input()";

    bool result = false;

    try {

        if(  fileExists(file) )
        {
            ui->lineEditMeshShapeFile->setStyleSheet("color: black;");
            ui->lineEditMeshShapeFile->setText(file);
            result = true;
        }
        else
        {
            ui->lineEditMeshShapeFile->setStyleSheet("color: red;");
            ui->lineEditMeshShapeFile->setText(file);

            result = false;
        }

    } catch (...) {
        qDebug() << "Error: Check_Mesh_Input is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button OutputDataFolder Clicked Event (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MeshSpatial::on_pushButtonOutputDataFolder_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshSpatial::on_pushButtonOutputDataFolder_clicked()";

    try {

        Clear_Log();

        QString OutputDataFolder = QFileDialog::getExistingDirectory(this, "PIHM Input Data Folder", user_pihmgis_root_folder + "/5PIHMSimulation", 0);

        if( OutputDataFolder != nullptr )
        {
            Check_OutputFolder_Location(OutputDataFolder);
            pushButtonSetFocus();
        }

    } catch (...) {
        qDebug() << "Error: MeshSpatial::on_pushButtonOutputDataFolder_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check entered value for OutputDataFolder
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MeshSpatial::on_lineEditOutputDataFolder_textChanged(const QString &arg1)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshSpatial::on_lineEditOutputDataFolder_textChanged()";

    try {
        bool checked = Check_OutputFolder_Location(arg1);
        if(checked)
            verifyInputOutputFile();
    } catch (...) {
        qDebug() << "Error: MeshSpatial::on_lineEditOutputDataFolder_textChanged() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check entered value for Project Name
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MeshSpatial::on_lineEditDataKey_textChanged(const QString &arg1)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshSpatial::on_lineEditDataKey_textChanged()";

    try {
        bool checked = Check_Project_Name_Input(arg1);
        if(checked)
            verifyInputOutputFile();
    } catch (...) {
        qDebug() << "Error: MeshSpatial::on_lineEditDataKey_textChanged() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check entered value for Project Name
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MeshSpatial::on_lineEditMeshShapeFile_textChanged(const QString &arg1)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshSpatial::on_lineEditMeshShapeFile_textChanged()";

    try {
        bool checked = Check_Mesh_Input(arg1);
        if(checked)
            verifyInputOutputFile();

    } catch (...) {
        qDebug() << "Error: MeshSpatial::on_lineEditMeshShapeFile_textChanged() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Plot Variable Index Change Event (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MeshSpatial::on_comboBoxPlotVariable_currentIndexChanged(int index)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshSpatial::on_comboBoxPlotVariable_currentIndexChanged()";

    try {
        verifyInputOutputFile();
    } catch (...) {
        qDebug() << "Error: MeshSpatial::on_comboBoxPlotVariable_currentIndexChanged() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to load para file
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool MeshSpatial::Load_Para_Input(QString para_filename, int index)
{
    if(print_debug_messages)
        qDebug() << "INFO: Load_Para_Input()";

    bool result = false;

    try {

        if ( QFile(para_filename).exists() )
        {
            if(index < 0)
            {
                QFile TempFile(para_filename);
                TempFile.open(QIODevice::ReadOnly | QIODevice::Text);
                QTextStream TempFileTextStream(&TempFile);
                double TempDouble;
                int Start, Stop;
                for (int i=1; i<=45; i++)
                {
                    TempFileTextStream >> TempDouble;
                    //qDebug() << TempDouble << "\t";
                }
                TempFileTextStream >> Start;
                //qDebug() << "Start = " << Start << "\t";
                TempFileTextStream >> Stop;
                //qDebug() << "Stop  = " << Stop  << "\t";
                if ( index == 5 ) { Start = Start / (60*24*365); Stop = Stop / (60*24*365); }
                if ( index == 4 ) { Start = Start / (60*24*30);  Stop = Stop / (60*24*30);  }
                if ( index == 3 ) { Start = Start / (60*24*7);   Stop = Stop / (60*24*7);   }
                if ( index == 2 ) { Start = Start / (60*24*1);   Stop = Stop / (60*24*1);   }
                if ( index == 1 ) { Start = Start / (60*1*1);    Stop = Stop / (60*1*1);    }
                if ( index == 0 ) { Start = Start / (1*1*1);     Stop = Stop / (1*1*1);     }

                ui->spinBoxStartTime->setValue( Start );
                ui->spinBoxStopTime->setValue( Stop );
            }
            else
            {
                QFile TempFile(para_filename);
                TempFile.open(QIODevice::ReadOnly | QIODevice::Text);
                QTextStream TempFileTextStream(&TempFile);
                double TempDouble;
                int Start, Stop;
                for (int i=1; i<=45; i++)
                {
                    TempFileTextStream >> TempDouble;
                    //qDebug() << TempDouble << "\t";
                }
                TempFileTextStream >> Start;
                //qDebug() << "Start = " << Start << "\t";
                TempFileTextStream >> Stop;
                //qDebug() << "Stop  = " << Stop  << "\t";
                if      ( Stop / (60*24*365) >= 1 ) { Start = Start / (60*24*365); Stop = Stop / (60*24*365); ui->comboBoxStartStop->setCurrentIndex(5); }
                else if ( Stop / (60*24*30)  >= 1 ) { Start = Start / (60*24*30);  Stop = Stop / (60*24*30);  ui->comboBoxStartStop->setCurrentIndex(4); }
                else if ( Stop / (60*24*7)   >= 1 ) { Start = Start / (60*24*7);   Stop = Stop / (60*24*7);   ui->comboBoxStartStop->setCurrentIndex(3); }
                else if ( Stop / (60*24*1)   >= 1 ) { Start = Start / (60*24*1);   Stop = Stop / (60*24*1);   ui->comboBoxStartStop->setCurrentIndex(2); }
                else if ( Stop / (60*1*1)    >= 1 ) { Start = Start / (60*1*1);    Stop = Stop / (60*1*1);    ui->comboBoxStartStop->setCurrentIndex(1); }
                else if ( Stop / (1*1*1)     >= 1 ) { Start = Start / (1*1*1);     Stop = Stop / (1*1*1);     ui->comboBoxStartStop->setCurrentIndex(0); }

                ui->spinBoxStartTime->setValue( Start );
                ui->spinBoxStopTime->setValue( Stop );
            }
        }

    } catch (...) {
        qDebug() << "Error: Load_Para_Input is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to validate inputs and outputs
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MeshSpatial::verifyInputOutputFile()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshSpatial::verifyInputOutputFile()";

    try {

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Clear Log
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Clear_Log();

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check Input Values
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QString output_data_folder = ui->lineEditOutputDataFolder->text();
        QString project_name = ui->lineEditDataKey->text();

        bool exists = Check_OutputFolder_Location(output_data_folder);

        if ( !exists)
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Folder Does Not Exist ... </span>") + output_data_folder + tr("<br>"));
        }
        else
        {
            //LogsString.append(tr("Output Folder Exists ... ") + output_data_folder + tr("<br>"));
        }

        QString FileName = output_data_folder + "/" + project_name;
        QString Extension = tr(".para");
        QString para_filename = FileName + Extension;

        if ( ! QFile(para_filename).exists() )
        {
            Log_Error_Message(tr("<span style=\"color:#FF0000\">ERROR: Para File Does Not Exist ... </span>")+ para_filename +tr("<br>"));
        }
        else
        {
            //LogsString.append(tr("Para File Exists ... ")+ para_filename +tr("<br>"));
        }

        QStringList Extensions;
        if (ui->comboBoxPlotVariable->currentIndex() ==  0) Extensions << ".surf.dat";  //surface storage
        if (ui->comboBoxPlotVariable->currentIndex() ==  1) Extensions << ".unsat.dat"; //soil moisture storage
        if (ui->comboBoxPlotVariable->currentIndex() ==  2) Extensions << ".gw.dat";    //groundwater storage
        if (ui->comboBoxPlotVariable->currentIndex() ==  3) Extensions << ".is.dat";    //interception strorage
        if (ui->comboBoxPlotVariable->currentIndex() ==  4) Extensions << ".snow.dat";  //snowpack storage
        if (ui->comboBoxPlotVariable->currentIndex() ==  5) Extensions << ".et0.dat";   //evapotranspiration
        if (ui->comboBoxPlotVariable->currentIndex() ==  5) Extensions << ".et1.dat";   //evapotranspiration
        if (ui->comboBoxPlotVariable->currentIndex() ==  5) Extensions << ".et2.dat";   //evapotranspiration
        if (ui->comboBoxPlotVariable->currentIndex() ==  6) Extensions << ".et0.dat";   //interception loss
        if (ui->comboBoxPlotVariable->currentIndex() ==  7) Extensions << ".et1.dat";   //transpiration
        if (ui->comboBoxPlotVariable->currentIndex() ==  8) Extensions << ".et2.dat";   //evaporation
        if (ui->comboBoxPlotVariable->currentIndex() ==  9) Extensions << ".infil.dat"; //infiltration
        if (ui->comboBoxPlotVariable->currentIndex() == 10) Extensions << ".rech.dat";  //recharge

        for( int i=0; i < Extensions.length(); i++)
        {
            QString tmp_filename = FileName + Extensions.at(i);
            if ( ! QFile(tmp_filename).exists() )
            {
                Log_Error_Message(tr("<span style=\"color:#FF0000\">ERROR: Output File Does Not Exist ... </span>") + tmp_filename +tr("<br>"));
            }
            else
            {
                Log_Message(tr("Output File Exists ... ") + tmp_filename +tr("<br>"));
            }
        }

        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

    } catch (...) {
        qDebug() << "Error: MeshSpatial::verifyInputOutputFile() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to focus button selection (needed for users w/o mouse)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MeshSpatial::pushButtonSetFocus()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshSpatial::pushButtonSetFocus()";

    try {
        ui->pushButtonOutputDataFolder->setDefault(false);

        if (ui->lineEditOutputDataFolder->text() == nullptr)
        {
            ui->pushButtonOutputDataFolder->setDefault(true);
            ui->pushButtonOutputDataFolder->setFocus();
            return;
        }

        if (ui->lineEditDataKey->text() == nullptr)
        {
            ui->lineEditDataKey->setFocus();
            return;
        }

        ui->pushButtonMeshShapeFile->setDefault(false);
        if (ui->lineEditMeshShapeFile->text() == nullptr)
        {
            ui->pushButtonMeshShapeFile->setDefault(true);
            ui->pushButtonMeshShapeFile->setFocus();
            return;
        }

        ui->pushButtonRun->setDefault(true);
        ui->pushButtonRun->setFocus();

    } catch (...) {
        qDebug() << "Error: MeshSpatial::pushButtonSetFocus() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to update Start/Stop times based on para file and selected index
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MeshSpatial::on_comboBoxStartStop_currentIndexChanged(int index)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshSpatial::on_comboBoxStartStop_currentIndexChanged()";

    try {

        Clear_Log();

        QStringList ModuleStringList = ReadModuleLine(filename_open_project,tr("PIHMSimulation"));
        if ( ModuleStringList.length() > 0  )
        {
            QString output_data_folder = ui->lineEditOutputDataFolder->text();
            QString project_name = ui->lineEditDataKey->text();
            QString para_file_name = output_data_folder + "/" + project_name +  tr(".para");
            Load_Para_Input(para_file_name, index);
        }

    } catch (...) {
        qDebug() << "Error: MeshSpatial::on_comboBoxStartStop_currentIndexChanged() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to update Mesh shapefile
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MeshSpatial::on_pushButtonMeshShapeFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshSpatial::on_pushButtonMeshShapeFile_clicked()";

    try {

        Clear_Log();

        QString MeshShapeFile = QFileDialog::getOpenFileName(this, "Mesh Shape File", user_pihmgis_root_folder +"/3DomainDecomposition", "Mesh Shape File(*.shp)");

        if( MeshShapeFile != nullptr )
        {
            Check_Mesh_Input(MeshShapeFile);
            pushButtonSetFocus();
        }

    } catch (...) {
        qDebug() << "Error: MeshSpatial::on_pushButtonMeshShapeFile_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get Number of elements in Mesh file
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MeshSpatial::Get_Element_Count(QString element_filename, bool message)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshSpatial::Get_Element_Count()";

    int element_count = -1;

    try {
        QFile TempFile;
        QTextStream TempFileTextStream;

        TempFile.setFileName(element_filename);
        TempFile.open(QIODevice::ReadOnly | QIODevice::Text);
        TempFileTextStream.setDevice(&TempFile);
        TempFileTextStream >> element_count;
        TempFile.close();

        if(message)
        {
            Log_Message(tr("Number of Elements = ")+QString::number(element_count)+tr("<br>"));
        }

    }
    catch (...)
    {
        element_count = -1;
        qDebug() << "Error: MeshSpatial::Get_Element_Count() is returning w/o checking";

    }

    return element_count;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get Number of River Segments in RIV file
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MeshSpatial::Get_River_Count(QString river_filename, bool message)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshSpatial::Get_River_Count()";

    int river_count = -1;

    try {
        QFile TempFile;
        QTextStream TempFileTextStream;

        TempFile.setFileName(river_filename);
        TempFile.open(QIODevice::ReadOnly | QIODevice::Text);
        TempFileTextStream.setDevice(&TempFile);
        TempFileTextStream >> river_count;
        TempFile.close();

        if(message)
        {
            Log_Message(tr("Number of River Segments = ")+QString::number(river_count)+tr("<br>"));
        }

    }
    catch (...)
    {
        river_count = -1;
        qDebug() << "Error: MeshSpatial::Get_River_Count() is returning w/o checking";

    }

    return river_count;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get time step
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Time_Values MeshSpatial::Get_Time_Steps(QString filename, int num_elements, bool message)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshSpatial::Get_Time_Step()";

    Time_Values result;
    result.time_step1 = -1;
    result.time_step2 = -1;

    try {
        QFile TempFile;
        QTextStream TempFileTextStream;
        int TIMESTEP1, TIMESTEP2;
        double TempDouble;

        TempFile.setFileName(filename);
        TempFile.open(QIODevice::ReadOnly | QIODevice::Text);
        TempFileTextStream.setDevice(&TempFile);

        TempFileTextStream >> TIMESTEP1;

        //if(message) qDebug() << "Time Step1 = " << TIMESTEP1 << "\n";

        for (int i=0; i < num_elements+1; i++)
        {
            TempFileTextStream >> TempDouble;
            //if(message) qDebug() << TempDouble << ", ";
        }
        TempFileTextStream >> TIMESTEP2;
        TempFile.close();

        //if(message) qDebug() << "\nTime Step2 = " << TIMESTEP2 << "\n";

        //time_step = TIMESTEP2 - TIMESTEP1;
        //if(message) qDebug() << "Time Step = " << time_step << "\n";
        result.time_step1 = TIMESTEP1;
        result.time_step2 = TIMESTEP2;

    }
    catch (...)
    {
        result.time_step1 = -1;
        result.time_step2 = -1;
        qDebug() << "Error: MeshSpatial::Get_Time_Step() is returning w/o checking";
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check if shapefile exists (Will handle all files for shapefile)
// If problems found, returns false
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool MeshSpatial::Check_ShapeFile_Output(QString file_name_without_extension, bool delete_files)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshSpatial::Check_ShapeFile_Output()";

    bool result = true;
    try
    {

        if ( QFile(file_name_without_extension + ".shp").exists() )
        {
            if(delete_files)
            {
                if ( ! QFile::remove(file_name_without_extension + ".shp") )
                {
                    Log_Error_Message("Unable to delete file... </span>" + file_name_without_extension + ".shp"  );
                }
                else
                {
                    result = false;
                }
            }
            else
            {
                result = false;
            }
        }


        if ( QFile(file_name_without_extension + ".shx").exists() )
        {
            if(delete_files)
            {
                if ( ! QFile::remove(file_name_without_extension + ".shx") )
                {
                    Log_Error_Message("Unable to delete file... </span>" + file_name_without_extension+".shx"  );
                }
                else
                {
                    result = false;
                }
            }
            else
            {
                result = false;
            }
        }

        if ( QFile(file_name_without_extension + ".dbf").exists() )
        {
            if(delete_files)
            {
                if ( ! QFile::remove(file_name_without_extension + ".dbf") )
                {
                    Log_Error_Message("Unable to delete file... </span>" + file_name_without_extension + ".dbf" );
                }
                else
                {
                    result = false;
                }
            }
            else
            {
                result = false;
            }
        }

    }
    catch (...)
    {
        result = false;
        qDebug() << "Error: MeshSpatial::Check_ShapeFile_Output() is returning w/o checking";
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Run Button Clicked Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MeshSpatial::on_pushButtonRun_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshSpatial::on_pushButtonRun_clicked()";

    try {

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Clear Log
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Clear_Log();

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check Inputs from GUI
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QString project_folder = ui->lineEditOutputDataFolder->text();
        QString project_name = ui->lineEditDataKey->text();
        QString mesh_shape_filename = ui->lineEditMeshShapeFile->text();
        QString output_base_filename = project_folder + "/" + project_name;
        QString river_filename = output_base_filename + ".riv";
        QString mesh_filename = output_base_filename + ".mesh";

        int start_time = ui->spinBoxStartTime->value();
        int stop_time  = ui->spinBoxStopTime->value();
        int num_breaks = ui->spinBoxNumBreaks->value();

        bool checked = Check_OutputFolder_Location(project_folder);
        if(!checked)
        {
            Log_Error_Message("Issue with Input Folder : </span>" + project_folder );
            return;
        }
        checked = Check_Project_Name_Input(project_name);
        if(!checked)
        {
            Log_Error_Message("Issue with Input Folder : </span>" + project_name  );
            return;
        }
        if( stop_time - start_time <= 0 )
        {
            Log_Error_Message("Issue with Start and Stop times : Duration calculated is zero or negative</span>"  );
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check file access
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        QStringList extensions_list;
        int current_index_comboBoxPlotVariable = ui->comboBoxPlotVariable->currentIndex();
        if (current_index_comboBoxPlotVariable ==  0) extensions_list << ".surf.dat";  //surface storage
        if (current_index_comboBoxPlotVariable ==  1) extensions_list << ".unsat.dat"; //soil moisture storage
        if (current_index_comboBoxPlotVariable ==  2) extensions_list << ".gw.dat";    //groundwater storage
        if (current_index_comboBoxPlotVariable ==  3) extensions_list << ".is.dat";    //interception strorage
        if (current_index_comboBoxPlotVariable ==  4) extensions_list << ".snow.dat";  //snowpack storage
        if (current_index_comboBoxPlotVariable ==  5) extensions_list << ".et0.dat";   //evapotranspiration
        if (current_index_comboBoxPlotVariable ==  5) extensions_list << ".et1.dat";   //evapotranspiration
        if (current_index_comboBoxPlotVariable ==  5) extensions_list << ".et2.dat";   //evapotranspiration
        if (current_index_comboBoxPlotVariable ==  6) extensions_list << ".et0.dat";   //interception loss
        if (current_index_comboBoxPlotVariable ==  7) extensions_list << ".et1.dat";   //transpiration
        if (current_index_comboBoxPlotVariable ==  8) extensions_list << ".et2.dat";   //evaporation
        if (current_index_comboBoxPlotVariable ==  9) extensions_list << ".infil.dat"; //infiltration
        if (current_index_comboBoxPlotVariable == 10) extensions_list << ".rech.dat";  //recharge

        if ( ! CheckFileAccess(mesh_filename, "ReadOnly") )
        {
            Log_Error_Message(tr("<span style=\"color:#FF0000\">No Read Access to ... </span>") + mesh_filename  );
            return;
        }
        if ( ! CheckFileAccess(river_filename, "ReadOnly") )
        {
            Log_Error_Message(tr("<span style=\"color:#FF0000\">No Read Access to ... </span>") + river_filename  );
            return;
        }
        if ( ! CheckFileAccess(mesh_shape_filename, "ReadOnly") )
        {
            Log_Error_Message(tr("<span style=\"color:#FF0000\">No Read Access to ... </span>") + mesh_shape_filename );
            return;
        }

        bool error_found = false;
        for (int i=0; i< extensions_list.length(); i++)
        {
            QString tmp_fname = output_base_filename + extensions_list.at(i);
            if ( ! CheckFileAccess(tmp_fname, "ReadOnly") )
            {
                Log_Error_Message(tr("<span style=\"color:#FF0000\">Error: No Read Access to ... </span>") + tmp_fname  );
                error_found = true;
            }
        }
        if(error_found)
        {
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Get Geometry Properties
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        int element_count = Get_Element_Count(mesh_filename,true);
        if(element_count <= 0)
        {
            Log_Error_Message(tr("<span style=\"color:#FF0000\">Problem with mesh geometry file, number of elements </span>") + element_count  );
            return;
        }
        int river_count = Get_River_Count(river_filename,true);
        if(river_count <= 0)
        {
            Log_Error_Message(tr("<span style=\"color:#FF0000\">Problem with riv geometry file, number of river segments </span>") + river_count  );
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Get other inputs (these should be harder to fail as they are GUI based retrieval)
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        QString PlotParameter;
        if (current_index_comboBoxPlotVariable ==  0) PlotParameter = "surf";
        if (current_index_comboBoxPlotVariable ==  1) PlotParameter = "unsat";
        if (current_index_comboBoxPlotVariable ==  2) PlotParameter = "gw";
        if (current_index_comboBoxPlotVariable ==  3) PlotParameter = "is";
        if (current_index_comboBoxPlotVariable ==  4) PlotParameter = "snow";
        if (current_index_comboBoxPlotVariable ==  5) PlotParameter = "etx";
        if (current_index_comboBoxPlotVariable ==  6) PlotParameter = "et0";
        if (current_index_comboBoxPlotVariable ==  7) PlotParameter = "et1";
        if (current_index_comboBoxPlotVariable ==  8) PlotParameter = "et2";
        if (current_index_comboBoxPlotVariable ==  9) PlotParameter = "infil";
        if (current_index_comboBoxPlotVariable == 10) PlotParameter = "rech";

        int timeunitfactor = 1;
        int current_index_comboBoxStartStop = ui->comboBoxStartStop->currentIndex();
        if ( current_index_comboBoxStartStop == 0 ) timeunitfactor = 1;
        if ( current_index_comboBoxStartStop == 1 ) timeunitfactor = 60;
        if ( current_index_comboBoxStartStop == 2 ) timeunitfactor = 60*24;
        if ( current_index_comboBoxStartStop == 3 ) timeunitfactor = 60*24*7;
        if ( current_index_comboBoxStartStop == 4 ) timeunitfactor = 60*24*30;
        if ( current_index_comboBoxStartStop == 5 ) timeunitfactor = 60*24*365;

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check if output exists
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QString output_file_name_without_extension = project_folder + "/6VisualAnalytics/Spatial_"+ PlotParameter;
        bool delete_files = false; //Let user do for now;
        bool check_output = Check_ShapeFile_Output(output_file_name_without_extension,delete_files);
        if( !check_output )
        {
            Log_Error_Message(tr("<span style=\"color:#FF0000\">Problem with Shapefile outputs already existing </span>") + output_file_name_without_extension  );
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Setup time properties
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QString filename_at_zero = output_base_filename + extensions_list.at(0);
        Time_Values time_steps = Get_Time_Steps(filename_at_zero, element_count, true);

        int time_step1 = time_steps.time_step1;
        int time_step2 = time_steps.time_step2;
        int time_step = time_step2 - time_step1;
        if( time_step <=0 )
        {
            Log_Error_Message(tr("<span style=\"color:#FF0000\">Problem with time_step </span>") + QString::number(time_step) );
            return;
        }

        start_time = ui->spinBoxStartTime->value() * timeunitfactor;
        stop_time  = ui->spinBoxStopTime->value()  * timeunitfactor;
        int skip_time_steps = ( start_time + time_step - time_step1 ) / time_step;
        int num_time_steps    = ( stop_time  - start_time ) / time_step;
        int break_steps    = num_time_steps / num_breaks;

        Log_Message("Start Time = " + QString::number( start_time) );
        Log_Message("Stop Time  = " + QString::number(stop_time) );
        Log_Message("Skip Time Steps = " + QString::number(skip_time_steps) );
        Log_Message("Number Time Steps = " + QString::number(num_time_steps) );
        Log_Message("Break Steps = " + QString::number(break_steps) );

        if ( break_steps < 1 )
        {
            Log_Error_Message(tr("<span style=\"color:#FF0000\">:Skip Time Steps = ")+QString::number(skip_time_steps)+tr(" Number time steps = ")+QString::number(num_time_steps)+tr(" Break Steps = ")+QString::number(break_steps)+tr("</span>") );
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Running
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ui->pushButtonRun->setText("Running");

        QVector<QString> Legends(num_breaks);
        QVector<QVector<double>> datax(num_breaks), datay(num_breaks);
        for (int j=0; j < num_breaks; j++)
        {
            datax[j].resize(element_count);
            datay[j].resize(element_count);
        }

        QString TempString;
        if(num_breaks > 1)
            for (int i=0; i < num_breaks; i++)
                Legends[i] = PlotParameter + TempString.sprintf("_%03d",i+1);
        else
            Legends[0] = PlotParameter;

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Read Data
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QFile DataFile;
        QTextStream DataFileTextStream;
        QString DataString;
        QStringList Data;
        for (int i=0; i< extensions_list.length(); i++)
        {
            DataFile.setFileName(output_base_filename + extensions_list.at(i));
            DataFile.open(QIODevice::ReadOnly | QIODevice::Text);
            DataFileTextStream.setDevice(&DataFile);
            int nline  = 1;
            int nbreak = 1;
            while ( nline <= skip_time_steps )
            {
                if( DataFileTextStream.atEnd() )
                {
                    Log_Error_Message("Reached End of File... </span>"+output_base_filename+extensions_list.at(i) );
                    ui->pushButtonRun->setText("Run");
                    return;
                }
                DataString = DataFileTextStream.readLine();
                //qDebug() << "A Line Number = " << nline << "\n";
                nline ++;
            }
            while ( nline <= skip_time_steps+num_time_steps )
            {
                if( DataFileTextStream.atEnd() )
                {
                    Log_Error_Message("Reached End of File... </span>"+output_base_filename+extensions_list.at(i) );
                    ui->pushButtonRun->setText("Run");
                    return;
                }
                DataString = DataFileTextStream.readLine();
                if ( nline > skip_time_steps + nbreak*break_steps )
                    nbreak++;
                //qDebug() << "B Line Number = " << nline << "\n";
                nline++;

                Data = DataString.split(QRegExp("\\s+"),QString::SkipEmptyParts);
                for (int j=0; j<element_count; j++)
                {
                    datax[nbreak-1][j] = Data.at(0).toDouble();
                    datay[nbreak-1][j] = datay[nbreak-1][j] + Data.at(j+1).toDouble()/break_steps;
                    //qDebug() << i << "," << j << "," << nbreak << "," << datax[nbreak-1][j] << "," << datay[nbreak-1][j] << "\n";
                }
            }
            DataFile.close();
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Write Data
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        TempString = mesh_shape_filename;
        TempString.replace(".shp",".shp");
        QFile::copy(TempString, output_file_name_without_extension + ".shp");
        TempString.replace(".shp",".shx");
        QFile::copy(TempString, output_file_name_without_extension + ".shx");

        QString dbfFileName = output_file_name_without_extension + ".dbf";
        DBFHandle DBF;
        DBF = DBFCreate((char *)qPrintable(dbfFileName));
        if ( DBF == nullptr )
        {
            Log_Error_Message("Unable To Open DBF File... </span>"+ dbfFileName  );
            ui->pushButtonRun->setText("Run");
            return;
        }

        int tempInt;
        char fieldName[11];
        QVector<int> fields(num_breaks+1);
        fields[0] = DBFAddField(DBF, "Ele", FTInteger, 9, 0);
        if ( fields[0] == -1 )
        {
            Log_Error_Message("Unable To Add New Attribute Ele To DBF File... </span>" + dbfFileName  );
            ui->pushButtonRun->setText("Run");
            return;
        }
        for (int i=0; i < num_breaks; i++)
        {
            sprintf(fieldName,"%s",qPrintable(Legends[i]));
            //qDebug() << Legends[i] << fieldName;
            fields[i+1] = DBFAddField(DBF, fieldName, FTDouble, 16, 8);
            if ( fields[i+1] == -1 )
            {
                Log_Error_Message("Unable To Add New Attribute To DBF File... </span>" + dbfFileName  );
                ui->pushButtonRun->setText("Run");
                return;
            }
            else
            {
                Log_Message(tr("Added New Attribute #")+QString::number(fields[i+1])+ tr(" ")+Legends[i]+tr(" To DBF File... </span>")+dbfFileName+tr("<br>"));
            }
        }

        for(int j=0; j < element_count; j++)
        {
            tempInt = DBFWriteIntegerAttribute(DBF, j, fields[0], j+1);
            if ( tempInt == 0 )
            {
                Log_Error_Message("Unable To Write Attribute To DBF File... </span>" + dbfFileName  );
                return;
            }
        }

        for (int i=0; i < num_breaks; i++)
        {
            for(int j=0; j < element_count; j++)
            {
                tempInt = DBFWriteDoubleAttribute(DBF, j, fields[i+1], datay[i][j]);
                if ( tempInt == 0 )
                {
                    Log_Error_Message("Unable To Write Attribute To DBF File... </span>" + dbfFileName );
                    return;
                }
            }
        }
        DBFClose(DBF);

        dbfFileName.replace(".dbf",".shp");

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update Project file
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QStringList ProjectIOStringList;

        ProjectIOStringList << "MeshSpatial" << project_folder << project_name;
        ProjectIOStringList << QString::number(current_index_comboBoxPlotVariable);
        ProjectIOStringList << QString::number(start_time) << QString::number(stop_time) << QString::number(current_index_comboBoxStartStop) << QString::number(num_breaks);
        ProjectIOStringList << mesh_shape_filename;
        ProjectIOStringList << dbfFileName;
        WriteModuleLine(filename_open_project, ProjectIOStringList);
        ProjectIOStringList.clear();

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update Message box and Reset buttons
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Clear_Log();

        Log_Message(tr("<br><b>Mesh Spatial Analysis Processing Completed.</b>")+tr("<br>"));

        ui->pushButtonRun->setText("Run");
        ui->pushButtonRun->setDefault(false);
        ui->pushButtonClose->setDefault(true);
        ui->pushButtonClose->setFocus();


    } catch (...) {
        qDebug() << "Error: MeshSpatial::on_pushButtonMeshShapeFile_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Help button event
// TODO, Need cataract server back online
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MeshSpatial::on_pushButtonClose_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshSpatial::on_pushButtonClose_clicked()";

    try {
        close();
    } catch (...) {
        qDebug() << "Error: MeshSpatial::on_pushButtonClose_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Help button event
// TODO, Need cataract server back online
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MeshSpatial::on_pushButtonHelp_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshSpatial::on_pushButtonHelp_clicked()";

    try {
        //        LogsString = tr("");
        //        if ( ! QDesktopServices::openUrl(QUrl("http://cataract.cee.psu.edu/PIHM/index.php/PIHMgis_3.0#Spatial_Analysis:_Mesh_Elements")) )
        //            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Load HTTP Link ... </span>")+tr("<br>"));
        //        ui->textBrowserLogs->setHtml(LogsString);
        //        ui->textBrowserLogs->repaint();
    } catch (...) {
        qDebug() << "Error: MeshSpatial::on_pushButtonHelp_clicked() is returning w/o checking";
    }
}
