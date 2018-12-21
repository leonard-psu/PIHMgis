#include <QFileDialog>
#include <QDebug>

#include "riverspatial.h"
#include "ui_riverspatial.h"
#include "0LibsIO/IOProjectFile.h"
#include "0LibsShape/shapefil.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RiverSpatial Constructor
// Parent is Main Window, filename is the open project text file used to store project details
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RiverSpatial::RiverSpatial(QWidget *parent, QString filename) :
    QDialog(parent),
    ui(new Ui::RiverSpatial)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start RiverSpatial";

    try {

        ui->setupUi(this);

        filename_open_project = filename;
        bool found_file = false;

        QFile ProjectFile(filename_open_project);
        if ( ! ProjectFile.open(QIODevice::ReadOnly | QIODevice::Text) )
        {
            Log_Error_Message("Unable to Open File: </span>" + filename_open_project + tr("<br>"));
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
        qDebug() << "Error: RiverSpatial is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RiverSpatial Deconstructor
// Todo: Check for memory leaks
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RiverSpatial::~RiverSpatial()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ~RiverSpatial";

    try {
        delete ui;
    } catch (...) {
        qDebug() << "Error: ~RiverSpatial is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check Log_Error_Message
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RiverSpatial::Log_Error_Message(QString message)
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
void RiverSpatial::Log_Message(QString message)
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
bool RiverSpatial::Load_Project_Settings()
{
    if (print_debug_messages)
        qDebug() << "INFO: RiverSpatial::Load_Project_Settings()";

    try {

        QStringList ModuleStringList = ReadModuleLine(filename_open_project,tr("PIHMSimulation"));
        if ( ModuleStringList.length() > 0  )
        {
            QString folder_Name = ModuleStringList.at(4);
            Check_OutputFolder_Location(folder_Name);

            QString TempFileName = ModuleStringList.at(2);
            Check_Project_Name_Input(TempFileName);

            QString para_filename = folder_Name + "/" + TempFileName +".para";
            Load_Para_Input(para_filename);
        }

        ModuleStringList = ReadModuleLine(filename_open_project,tr("MeshDataFile"));
        if ( ModuleStringList.length() > 0 )
        {
            QString TempFileName = ModuleStringList.at(10);
            Check_RiverShapeFile_Input(TempFileName);
        }

        // Start: Fill Form If Module Has Been Run Previously
        ModuleStringList = ReadModuleLine(filename_open_project,tr("RiverSpatial"));

        if ( ModuleStringList.length() > 0 )
        {
            Check_OutputFolder_Location(ModuleStringList.at(1));
            Check_Project_Name_Input(ModuleStringList.at(2));
            Check_RiverShapeFile_Input(ModuleStringList.at(8));
        }

        verifyInputOutputFile();
        pushButtonSetFocus();

    } catch (...) {
        qDebug() << "Error: RiverSpatial::Load_Project_Settings is returning w/o checking";
        return false;
    }

    return true;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to clear message log
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RiverSpatial::Clear_Log()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start RiverSpatial::Clear_Log()";

    try {

        LogsString = tr("");
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

    } catch (...) {
        qDebug() << "Error: RiverSpatial::Clear_Log() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Check OutputFolder File exists (INPUT Location of Model)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool RiverSpatial::Check_OutputFolder_Location(QString folder)
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
bool RiverSpatial::Check_Project_Name_Input(QString value){

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
// Helper Function to Check ModelSegments (INPUT)
// TODO error checking
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool RiverSpatial::Check_RiverShapeFile_Input(QString value){

    if(print_debug_messages)
        qDebug() << "INFO: Check_RiverShapeFile_Input()";

    bool result = false;

    try {

        if(value.isNull() || value.isEmpty())
        {
            ui->lineEditRiverShapeFile->setStyleSheet("color: red;");
            ui->lineEditRiverShapeFile->setText("Missing");
            result = false;
        }
        else if(value == QString("Missing"))
        {
            ui->lineEditRiverShapeFile->setStyleSheet("color: red;");
            result = false;
        }
        else
        {
            ui->lineEditRiverShapeFile->setStyleSheet("color: black;");
            ui->lineEditRiverShapeFile->setText(value);
            result = true;
        }

    } catch (...) {
        qDebug() << "Error: Check_RiverShapeFile_Input is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to load para file
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool RiverSpatial::Load_Para_Input(QString para_filename)
{
    if(print_debug_messages)
        qDebug() << "INFO: Load_Para_Input()";

    bool result = false;

    try {

        if ( QFile(para_filename).exists() )
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

    } catch (...) {
        qDebug() << "Error: Load_Para_Input is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to fill GUI based on Project Name
// Assuming only para filename and based on structure
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool RiverSpatial::Load_BasedOnProjectName_Input()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start RiverSpatial::Load_BasedOnProjectName_Input()";

    bool result = false;
    try {

        if( ui->lineEditDataKey->text() == nullptr )
        {
            // Data Model INPUT File Name
            QStringList ModuleStringList = ReadModuleLine(filename_open_project,tr("TINShapeLayer"));
            if ( ModuleStringList.length() > 0  )
            {
                QString TempFileName = ModuleStringList.at(3);
                TempFileName = TempFileName.right(TempFileName.length()-TempFileName.lastIndexOf("/")-1);

                TempFileName.replace( QString(".shp"), QString("") );

                QString para_filename = ui->lineEditOutputDataFolder->text() + "/" + TempFileName + ".para";
                bool checked = Check_OutputFolder_Location(para_filename);
                if ( checked )
                {
                    ui->lineEditDataKey->setText(TempFileName);
                }
            }

            ModuleStringList = ReadModuleLine(filename_open_project,tr("MeshDataFile"));
            if ( ModuleStringList.length() > 0  )
            {
                QString TempFileName = ModuleStringList.at(9);
                QString para_filename = ui->lineEditOutputDataFolder->text() + "/" + TempFileName + ".para";
                bool checked = Check_OutputFolder_Location(para_filename);
                if ( checked )
                {
                    ui->lineEditDataKey->setText(TempFileName);
                }
            }

            result = true;
        }

    } catch (...) {
        qDebug() << "Error: RiverSpatial::Load_BasedOnProjectName_Input() is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button OutputDataFolder Clicked Event (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RiverSpatial::on_pushButtonOutputDataFolder_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start RiverSpatial::on_pushButtonOutputDataFolder_clicked()";

    try {

        Clear_Log();

        QString OutputDataFolder = QFileDialog::getExistingDirectory(this, "PIHM Input Data Folder", user_pihmgis_root_folder+"/5PIHMSimulation", 0);

        if( OutputDataFolder != nullptr )
        {
            Check_OutputFolder_Location(OutputDataFolder);
            Load_BasedOnProjectName_Input();
            pushButtonSetFocus();
        }

    } catch (...) {
        qDebug() << "Error: RiverSpatial::on_pushButtonOutputDataFolder_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check entered value for OutputDataFolder
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RiverSpatial::on_lineEditOutputDataFolder_textChanged(const QString &arg1)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start RiverSpatial::on_lineEditOutputDataFolder_textChanged()";

    try {
        bool checked = Check_OutputFolder_Location(arg1);
        if(checked)
            verifyInputOutputFile();
    } catch (...) {
        qDebug() << "Error: RiverSpatial::on_lineEditOutputDataFolder_textChanged() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check entered value for Project Name
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RiverSpatial::on_lineEditDataKey_textChanged(const QString &arg1)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start RiverSpatial::on_lineEditDataKey_textChanged()";

    try {
        bool checked = Check_Project_Name_Input(arg1);
        if(checked)
            verifyInputOutputFile();
    } catch (...) {
        qDebug() << "Error: RiverSpatial::on_lineEditDataKey_textChanged() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check entered value for RiverShapeFile
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RiverSpatial::on_lineEditRiverShapeFile_textChanged(const QString &arg1)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start RiverSpatial::on_lineEditRiverShapeFile_textChanged()";

    try {
        Check_RiverShapeFile_Input(arg1);
    } catch (...) {
        qDebug() << "Error: RiverSpatial::on_lineEditRiverShapeFile_textChanged() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check entered value for PlotVariable
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RiverSpatial::on_comboBoxPlotVariable_currentIndexChanged(int index)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start RiverSpatial::on_comboBoxPlotVariable_currentIndexChanged()";

    try {
        verifyInputOutputFile();
    } catch (...) {
        qDebug() << "Error: RiverSpatial::on_comboBoxPlotVariable_currentIndexChanged() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to validate inputs and outputs
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RiverSpatial::verifyInputOutputFile()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start RiverSpatial::verifyInputOutputFile()";

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
            Log_Error_Message(tr("<span style=\"color:#FF0000\">ERROR: Folder Does Not Exist ... </span>") + output_data_folder + tr("<br>"));
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
        int current_index_comboBoxPlotVariable = ui->comboBoxPlotVariable->currentIndex();

        if (current_index_comboBoxPlotVariable ==  0) Extensions << ".surf.dat";  //surface storage
        if (current_index_comboBoxPlotVariable ==  1) Extensions << ".unsat.dat"; //soil moisture storage
        if (current_index_comboBoxPlotVariable ==  2) Extensions << ".gw.dat";    //groundwater storage
        if (current_index_comboBoxPlotVariable ==  3) Extensions << ".is.dat";    //interception strorage
        if (current_index_comboBoxPlotVariable ==  4) Extensions << ".snow.dat";  //snowpack storage
        if (current_index_comboBoxPlotVariable ==  5) Extensions << ".et0.dat";   //evapotranspiration
        if (current_index_comboBoxPlotVariable ==  5) Extensions << ".et1.dat";   //evapotranspiration
        if (current_index_comboBoxPlotVariable ==  5) Extensions << ".et2.dat";   //evapotranspiration
        if (current_index_comboBoxPlotVariable ==  6) Extensions << ".et0.dat";   //interception loss
        if (current_index_comboBoxPlotVariable ==  7) Extensions << ".et1.dat";   //transpiration
        if (current_index_comboBoxPlotVariable ==  8) Extensions << ".et2.dat";   //evaporation
        if (current_index_comboBoxPlotVariable ==  9) Extensions << ".infil.dat"; //infiltration
        if (current_index_comboBoxPlotVariable == 10) Extensions << ".rech.dat";  //recharge

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

    } catch (...) {
        qDebug() << "Error: RiverSpatial::verifyInputOutputFile() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to focus button selection (needed for users w/o mouse)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RiverSpatial::pushButtonSetFocus()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start RiverSpatial::pushButtonSetFocus()";

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

        ui->pushButtonRiverShapeFile->setDefault(false);
        if (ui->lineEditRiverShapeFile->text() == nullptr)
        {
            ui->pushButtonRiverShapeFile->setDefault(true);
            ui->pushButtonRiverShapeFile->setFocus();
            return;
        }

        ui->pushButtonRun->setDefault(true);
        ui->pushButtonRun->setFocus();
    } catch (...) {
        qDebug() << "Error: RiverSpatial::pushButtonSetFocus() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to update Start/Stop times based on para file and selected index
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RiverSpatial::on_comboBoxStartStop_currentIndexChanged(int index)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start RiverSpatial::on_comboBoxStartStop_currentIndexChanged()";

    try {

        Clear_Log();

        QStringList ModuleStringList = ReadModuleLine(filename_open_project,tr("PIHMSimulation"));
        if ( ModuleStringList.length() > 0  )
        {
            QString para_filename = ui->lineEditOutputDataFolder->text()+"/"+ui->lineEditDataKey->text()+".para";
            Load_Para_Input(para_filename);
        }

    } catch (...) {
        qDebug() << "Error: RiverSpatial::on_comboBoxStartStop_currentIndexChanged() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to update River shapefile
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RiverSpatial::on_pushButtonRiverShapeFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start RiverSpatial::on_pushButtonRiverShapeFile_clicked()";

    try {

        Clear_Log();

        QString RiverShapeFile = QFileDialog::getOpenFileName(this, "River Shape File", user_pihmgis_root_folder + "/2VectorProcessing", "River Shape File(*.shp)");

        if( RiverShapeFile != nullptr )
        {
            Check_RiverShapeFile_Input(RiverShapeFile);
            pushButtonSetFocus();
        }

    } catch (...) {
        qDebug() << "Error: RiverSpatial::on_pushButtonRiverShapeFile_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get Number of elements in Mesh file
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RiverSpatial::Get_Element_Count(QString element_filename, bool message)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start RiverSpatial::Get_Element_Count()";

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
        qDebug() << "Error: RiverSpatial::Get_Element_Count() is returning w/o checking";
    }

    return element_count;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get Number of River Segments in RIV file
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RiverSpatial::Get_River_Count(QString river_filename, bool message)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start RiverSpatial::Get_River_Count()";

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
        qDebug() << "Error: RiverSpatial::Get_River_Count() is returning w/o checking";

    }

    return river_count;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get time step
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Time_Values RiverSpatial::Get_Time_Steps(QString filename, int num_elements, bool message)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start RiverSpatial::Get_Time_Step()";

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
        qDebug() << "Error: RiverSpatial::Get_Time_Step() is returning w/o checking";
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check if shapefile exists (Will handle all files for shapefile)
// If problems found, returns false
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool RiverSpatial::Check_ShapeFile_Output(QString file_name_without_extension, bool delete_files)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start RiverSpatial::Check_ShapeFile_Output()";

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
                    Log_Error_Message("Unable to delete file... </span>" + file_name_without_extension+".shx" );
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
        qDebug() << "Error: RiverSpatial::Check_ShapeFile_Output() is returning w/o checking";
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Run Button Clicked Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RiverSpatial::on_pushButtonRun_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start RiverSpatial::on_pushButtonRun_clicked()";

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
        QString river_shape_filename = ui->lineEditRiverShapeFile->text();
        QString output_base_filename = project_folder + "/" + project_name;
        QString river_filename = output_base_filename + ".riv";
        QString mesh_filename = output_base_filename + ".mesh";

        int start_time = ui->spinBoxStartTime->value();
        int stop_time  = ui->spinBoxStopTime->value();
        int num_breaks = ui->spinBoxNumBreaks->value();

        bool checked = Check_OutputFolder_Location(project_folder);
        if(!checked)
        {
            Log_Error_Message("Issue with Input Folder : </span>" + project_folder  );
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
        if (current_index_comboBoxPlotVariable ==  0) extensions_list << ".rivFlx01.dat"; //outflow
        if (current_index_comboBoxPlotVariable ==  1) extensions_list << ".rivFlx00.dat"; //inflow
        if (current_index_comboBoxPlotVariable ==  2) extensions_list << ".stage.dat";    //storage
        if (current_index_comboBoxPlotVariable ==  3) extensions_list << ".rivFlx02.dat"; //surfaceflow
        if (current_index_comboBoxPlotVariable ==  3) extensions_list << ".rivFlx03.dat"; //surfaceflow
        if (current_index_comboBoxPlotVariable ==  4) extensions_list << ".rivFlx04.dat"; //baseflow
        if (current_index_comboBoxPlotVariable ==  4) extensions_list << ".rivFlx05.dat"; //baseflow
        if (current_index_comboBoxPlotVariable ==  5) extensions_list << ".rivFlx02.dat"; //surfaceflow left
        if (current_index_comboBoxPlotVariable ==  6) extensions_list << ".rivFlx03.dat"; //surfaceflow right
        if (current_index_comboBoxPlotVariable ==  7) extensions_list << ".rivFlx04.dat"; //baseflow left
        if (current_index_comboBoxPlotVariable ==  8) extensions_list << ".rivFlx05.dat"; //baseflow right
        if (current_index_comboBoxPlotVariable ==  9) extensions_list << ".rivFlx06.dat"; //seepage bed
        if (current_index_comboBoxPlotVariable == 10) extensions_list << ".rivFlx09.dat"; //bed outflow
        if (current_index_comboBoxPlotVariable == 11) extensions_list << ".rivFlx10.dat"; //bed inflow
        if (current_index_comboBoxPlotVariable == 12) extensions_list << ".rbed.dat";     //bed storage
        if (current_index_comboBoxPlotVariable == 13) extensions_list << ".rivFlx07.dat"; //bed baseflow
        if (current_index_comboBoxPlotVariable == 13) extensions_list << ".rivFlx08.dat"; //bed baseflow
        if (current_index_comboBoxPlotVariable == 14) extensions_list << ".rivFlx07.dat"; //bed baseflow left
        if (current_index_comboBoxPlotVariable == 15) extensions_list << ".rivFlx08.dat"; //bed baseflow right


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
        if ( ! CheckFileAccess(river_shape_filename, "ReadOnly") )
        {
            Log_Error_Message(tr("<span style=\"color:#FF0000\">No Read Access to ... </span>") + river_shape_filename  );
            return;
        }

        bool error_found = false;
        for (int i=0; i< extensions_list.length(); i++)
        {
            QString tmp_fname = output_base_filename + extensions_list.at(i);
            if ( ! CheckFileAccess(tmp_fname, "ReadOnly") )
            {
                Log_Error_Message(tr("<span style=\"color:#FF0000\">Error: No Read Access to ... </span>") + tmp_fname );
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
            Log_Error_Message(tr("<span style=\"color:#FF0000\">Problem with mesh geometry file, number of elements </span>") + element_count );
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
        if (current_index_comboBoxPlotVariable ==  0) PlotParameter = "outq";    //outflow
        if (current_index_comboBoxPlotVariable ==  1) PlotParameter = "inq";     //inflow
        if (current_index_comboBoxPlotVariable ==  2) PlotParameter = "store";   //storage
        if (current_index_comboBoxPlotVariable ==  3) PlotParameter = "surfq";    //surfaceflow
        if (current_index_comboBoxPlotVariable ==  4) PlotParameter = "baseq";    //baseflow
        if (current_index_comboBoxPlotVariable ==  5) PlotParameter = "surfql";   //surfaceflow left
        if (current_index_comboBoxPlotVariable ==  6) PlotParameter = "surfqr";   //surfaceflow right
        if (current_index_comboBoxPlotVariable ==  7) PlotParameter = "baseql";   //baseflow left
        if (current_index_comboBoxPlotVariable ==  8) PlotParameter = "baseqr";   //baseflow right
        if (current_index_comboBoxPlotVariable ==  9) PlotParameter = "seep";    //seepage bed
        if (current_index_comboBoxPlotVariable == 10) PlotParameter = "rboutq";   //bed outflow
        if (current_index_comboBoxPlotVariable == 11) PlotParameter = "rbinq";    //bed inflow
        if (current_index_comboBoxPlotVariable == 12) PlotParameter = "rbstore"; //bed storage
        if (current_index_comboBoxPlotVariable == 13) PlotParameter = "rbbase";  //bed baseflow
        if (current_index_comboBoxPlotVariable == 14) PlotParameter = "rbbasel"; //bed baseflow left
        if (current_index_comboBoxPlotVariable == 15) PlotParameter = "rbbaser"; //bed baseflow right

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
        Time_Values time_steps = Get_Time_Steps(filename_at_zero, river_count, true);  //Note use of river_count

        int time_step1 = time_steps.time_step1;
        int time_step2 = time_steps.time_step2;
        int time_step = time_step2 - time_step1;
        if( time_step <=0 )
        {
            Log_Error_Message(tr("<span style=\"color:#FF0000\">Problem with time_step </span>") + QString::number(time_step)  );
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
            datax[j].resize(river_count);  //Note use of river_count
            datay[j].resize(river_count);  //Note use of river_count
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
                for (int j=0; j < river_count; j++) //Note use of river_count
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

        TempString = river_shape_filename;
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
            Log_Error_Message("Unable To Add New Attribute Ele To DBF File... </span>" + dbfFileName );
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
                Log_Error_Message("Unable To Add New Attribute To DBF File... </span>" + dbfFileName );
                ui->pushButtonRun->setText("Run");
                return;
            }
            else
            {
                Log_Message(tr("Added New Attribute #")+QString::number(fields[i+1])+ tr(" ")+Legends[i]+tr(" To DBF File... </span>")+dbfFileName+tr("<br>"));
            }
        }

        for(int j=0; j < river_count; j++) //Note use of river_count
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
            for(int j=0; j < river_count; j++) //Note use of river_count
            {
                tempInt = DBFWriteDoubleAttribute(DBF, j, fields[i+1], datay[i][j]);
                if ( tempInt == 0 )
                {
                    Log_Error_Message("Unable To Write Attribute To DBF File... </span>" + dbfFileName  );
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

        ProjectIOStringList << "RiverSpatial" << project_folder << project_name;
        ProjectIOStringList << QString::number(current_index_comboBoxPlotVariable);
        ProjectIOStringList << QString::number(start_time) << QString::number(stop_time) << QString::number(current_index_comboBoxStartStop) << QString::number(num_breaks);
        ProjectIOStringList << river_shape_filename;
        ProjectIOStringList << dbfFileName;
        WriteModuleLine(filename_open_project, ProjectIOStringList);
        ProjectIOStringList.clear();

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update Message box and Reset buttons
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Clear_Log();

        Log_Message(tr("<br><b>River Spatial Analysis Processing Completed.</b>")+tr("<br>"));

        ui->pushButtonRun->setText("Run");
        ui->pushButtonRun->setDefault(false);
        ui->pushButtonClose->setDefault(true);
        ui->pushButtonClose->setFocus();

    } catch (...) {
        qDebug() << "Error: RiverSpatial::on_pushButtonRiverShapeFile_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Help button event
// TODO, Need cataract server back online
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RiverSpatial::on_pushButtonClose_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start RiverSpatial::on_pushButtonClose_clicked()";

    try {
        close();
    } catch (...) {
        qDebug() << "Error: RiverSpatial::on_pushButtonClose_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Help button event
// TODO, Need cataract server back online
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RiverSpatial::on_pushButtonHelp_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start RiverSpatial::on_pushButtonHelp_clicked()";

    try {
        //        LogsString = tr("");
        //        if ( ! QDesktopServices::openUrl(QUrl("http://cataract.cee.psu.edu/PIHM/index.php/PIHMgis_3.0#Spatial_Analysis:_River_Elements")) )
        //            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Load HTTP Link ... </span>")+tr("<br>"));
        //        ui->textBrowserLogs->setHtml(LogsString);
        //        ui->textBrowserLogs->repaint();
    } catch (...) {
        qDebug() << "Error: RiverSpatial::on_pushButtonHelp_clicked() is returning w/o checking";
    }
}
