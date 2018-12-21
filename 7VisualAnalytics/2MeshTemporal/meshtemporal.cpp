#include <QApplication>
#include <QMainWindow>

#include "meshtemporal.h"
#include "ui_meshtemporal.h"

#include "7VisualAnalytics/QCustomPlot/qcustomplot.h"
#include "7VisualAnalytics/QCustomPlotMainWindow/qcustomplotmainwindow.h"
#include "0LibsIO/IOProjectFile.h"
#include "globals.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MeshTemporal Constructor
// Parent is Main Window, filename is the open project text file used to store project details
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MeshTemporal::MeshTemporal(QWidget *parent, QString filename) :
    QDialog(parent),
    ui(new Ui::MeshTemporal)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshTemporal";

    try {
        ui->setupUi(this);

        filename_open_project = filename;
        bool found_file = false;

        QAction *PrintAction = new QAction(tr("&Save..."),this);
        PrintAction->setShortcut(tr("Ctrl+S"));
        connect(PrintAction,SIGNAL(triggered()),this,SLOT(on_pushButtonRun_clicked()));

        QFile ProjectFile(filename_open_project);
        if ( ! ProjectFile.open(QIODevice::ReadOnly | QIODevice::Text) )
        {
            Log_Error_Message("Unable to Open File: </span>" + filename_open_project );
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
        qDebug() << "Error: MeshTemporal is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MeshTemporal Deconstructor
// Todo: Check for memory leaks
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MeshTemporal::~MeshTemporal()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ~MeshTemporal";

    try {
        delete ui;
    } catch (...) {
        qDebug() << "Error: ~MeshTemporal is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check Log_Error_Message
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MeshTemporal::Log_Error_Message(QString message)
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
void MeshTemporal::Log_Message(QString message)
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
bool MeshTemporal::Load_Project_Settings()
{
    if (print_debug_messages)
        qDebug() << "INFO: MeshTemporal::Load_Project_Settings()";

    try {

        QStringList ModuleStringList = ReadModuleLine(filename_open_project,tr("PIHMSimulation"));
        if ( ModuleStringList.length() > 0  )
        {
            QString TempFileName = ModuleStringList.at(4);
            Check_OutputFolder_Location(TempFileName);

            TempFileName = ModuleStringList.at(2);
            Check_Project_Name_Input(TempFileName);
        }

        // ** Start: Fill Form If Module Has Been Run Previously

        ModuleStringList = ReadModuleLine(filename_open_project,tr("MeshTemporal"));

        if ( ModuleStringList.length() > 0 )
        {
            Check_OutputFolder_Location(ModuleStringList.at(1));
            Check_Project_Name_Input(ModuleStringList.at(2));
            Check_ModelSegments_Input(ModuleStringList.at(5));
        }

        verifyInputOutputFile();
        pushButtonSetFocus();

    } catch (...) {
        qDebug() << "Error: MeshTemporal::Load_Project_Settings is returning w/o checking";
        return false;
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to clear message log
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MeshTemporal::Clear_Log()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshTemporal::Clear_Log()";

    try {

        LogsString = tr("");
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

    } catch (...) {
        qDebug() << "Error: MeshTemporal::Clear_Log() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Check OutputFolder File exists (INPUT Location of Model)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool MeshTemporal::Check_OutputFolder_Location(QString folder)
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
bool MeshTemporal::Check_Project_Name_Input(QString value){

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
bool MeshTemporal::Check_ModelSegments_Input(QString value){

    if(print_debug_messages)
        qDebug() << "INFO: Check_ModelSegments_Input()";

    bool result = false;

    try {

        if(value.isNull() || value.isEmpty())
        {
            ui->lineEditModelSegments->setStyleSheet("color: red;");
            ui->lineEditModelSegments->setText("Missing");
            result = false;
        }
        else if(value == QString("Missing"))
        {
            ui->lineEditModelSegments->setStyleSheet("color: red;");
            result = false;
        }
        else
        {
            ui->lineEditModelSegments->setStyleSheet("color: black;");
            ui->lineEditModelSegments->setText(value);
            result = true;
        }

    } catch (...) {
        qDebug() << "Error: Check_ModelSegments_Input is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button OutputDataFolder Clicked Event (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MeshTemporal::on_pushButtonOutputDataFolder_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshTemporal::on_pushButtonOutputDataFolder_clicked()";

    try {

        Clear_Log();

        QString OutputDataFolder = QFileDialog::getExistingDirectory(this, "PIHM Input Data Folder", user_pihmgis_root_folder+"/5PIHMSimulation", 0);

        if( OutputDataFolder != nullptr )
        {
            Check_OutputFolder_Location(OutputDataFolder);
            pushButtonSetFocus();
        }

    } catch (...) {
        qDebug() << "Error: MeshTemporal::on_pushButtonOutputDataFolder_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check entered value for ModelSegments
// TODO
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MeshTemporal::on_comboBoxModelSegments_currentIndexChanged(int index)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshTemporal::on_comboBoxModelSegments_currentIndexChanged()";

    try {
        if ( index == 2 || index == 4 )
            ui->lineEditModelSegments->hide();
        else
            ui->lineEditModelSegments->show();

        pushButtonSetFocus();
    } catch (...) {
        qDebug() << "Error: MeshTemporal::on_comboBoxModelSegments_currentIndexChanged() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check entered value for OutputDataFolder
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MeshTemporal::on_lineEditOutputDataFolder_textChanged(const QString &arg1)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshTemporal::on_lineEditOutputDataFolder_textChanged()";

    try {
        bool checked = Check_OutputFolder_Location(arg1);
        if(checked)
            verifyInputOutputFile();
    } catch (...) {
        qDebug() << "Error: MeshTemporal::on_lineEditOutputDataFolder_textChanged() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check entered value for Project Name
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MeshTemporal::on_lineEditDataKey_textChanged(const QString &arg1)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshTemporal::on_lineEditDataKey_textChanged()";

    try {
        bool checked = Check_Project_Name_Input(arg1);
        if(checked)
            verifyInputOutputFile();
    } catch (...) {
        qDebug() << "Error: MeshTemporal::on_lineEditDataKey_textChanged() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check entered value for ModelSegments
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MeshTemporal::on_lineEditModelSegments_textChanged(const QString &arg1)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshTemporal::on_lineEditModelSegments_textChanged()";

    try {
        bool checked = Check_ModelSegments_Input(arg1);
        if(checked)
            verifyInputOutputFile();
    } catch (...) {
        qDebug() << "Error: MeshTemporal::on_lineEditModelSegments_textChanged() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check entered value for PlotVariable
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MeshTemporal::on_comboBoxPlotVariable_currentIndexChanged(int index)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshTemporal::on_comboBoxPlotVariable_currentIndexChanged()";

    try {
        verifyInputOutputFile();
    } catch (...) {
        qDebug() << "Error: MeshTemporal::on_comboBoxPlotVariable_currentIndexChanged() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to validate inputs and outputs
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MeshTemporal::verifyInputOutputFile()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshTemporal::verifyInputOutputFile()";

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
            Log_Message(tr("<span style=\"color:#FF0000\">ERROR: Folder Does Not Exist ... </span>") + output_data_folder + tr("<br>"));
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
            Log_Message(tr("<span style=\"color:#FF0000\">ERROR: Para File Does Not Exist ... </span>")+ para_filename +tr("<br>"));
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
                Log_Message(tr("<span style=\"color:#FF0000\">ERROR: Output File Does Not Exist ... </span>") + tmp_filename +tr("<br>"));
            }
            else
            {
                Log_Message(tr("Output File Exists ... ") + tmp_filename +tr("<br>"));
            }
        }

        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

    } catch (...) {
        qDebug() << "Error: MeshTemporal::verifyInputOutputFile() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to focus button selection (needed for users w/o mouse)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MeshTemporal::pushButtonSetFocus()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshTemporal::pushButtonSetFocus()";

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

        if (ui->comboBoxModelSegments->currentIndex() == 0 || ui->comboBoxModelSegments->currentIndex() == 1 || ui->comboBoxModelSegments->currentIndex() == 3)
        {
            if (ui->lineEditModelSegments->text() == nullptr)
            {
                ui->lineEditModelSegments->setFocus();
                return;
            }
        }

        ui->pushButtonRun->setDefault(true);
        ui->pushButtonRun->setFocus();

    } catch (...) {
        qDebug() << "Error: MeshTemporal::pushButtonSetFocus() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get Number of elements in Mesh file
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MeshTemporal::Get_Element_Count(QString element_filename, bool message)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshTemporal::Get_Element_Count()";

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
        qDebug() << "Error: MeshTemporal::Get_Element_Count() is returning w/o checking";

    }

    return element_count;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get Number of River Segments in RIV file
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MeshTemporal::Get_River_Count(QString river_filename, bool message)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshTemporal::Get_River_Count()";

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
        qDebug() << "Error: MeshTemporal::Get_River_Count() is returning w/o checking";

    }

    return river_count;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get time step
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Time_Values MeshTemporal::Get_Time_Steps(QString filename, int num_elements, bool message)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshTemporal::Get_Time_Step()";

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

        //if(message)
        //    qDebug() << "Time Step1 = " << TIMESTEP1 << "\n";

        for (int i=0; i < num_elements+1; i++)
        {
            TempFileTextStream >> TempDouble;
            //if(message)
            //    qDebug() << TempDouble << ", ";
        }
        TempFileTextStream >> TIMESTEP2;
        TempFile.close();

        //if(message)
        //    qDebug() << "\nTime Step2 = " << TIMESTEP2 << "\n";

        //time_step = TIMESTEP2 - TIMESTEP1;
        //if(message) qDebug() << "Time Step = " << time_step << "\n";
        result.time_step1 = TIMESTEP1;
        result.time_step2 = TIMESTEP2;

    }
    catch (...)
    {
        result.time_step1 = -1;
        result.time_step2 = -1;
        qDebug() << "Error: MeshTemporal::Get_Time_Step() is returning w/o checking";
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Run Button Clicked Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MeshTemporal::on_pushButtonRun_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshTemporal::on_pushButtonRun_clicked()";

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
        QString output_base_filename = project_folder + "/" + project_name;
        QString river_filename = output_base_filename + ".riv";
        QString mesh_filename = output_base_filename + ".mesh";

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
        if (current_index_comboBoxPlotVariable ==  0) PlotParameter = "Surface Storage"; //outflow
        if (current_index_comboBoxPlotVariable ==  1) PlotParameter = "Soil Moisture Storage"; //inflow
        if (current_index_comboBoxPlotVariable ==  2) PlotParameter = "Groundwater Storage";    //storage
        if (current_index_comboBoxPlotVariable ==  3) PlotParameter = "Interception Storage"; //surfaceflow
        if (current_index_comboBoxPlotVariable ==  4) PlotParameter = "Snowpack Storage"; //baseflow
        if (current_index_comboBoxPlotVariable ==  5) PlotParameter = "Evapotranspiration"; //surfaceflow left
        if (current_index_comboBoxPlotVariable ==  6) PlotParameter = "Interception Loss"; //surfaceflow right
        if (current_index_comboBoxPlotVariable ==  7) PlotParameter = "Transpiration"; //baseflow left
        if (current_index_comboBoxPlotVariable ==  8) PlotParameter = "Evaporation from Ground"; //baseflow right
        if (current_index_comboBoxPlotVariable ==  9) PlotParameter = "Infiltration"; //seepage bed
        if (current_index_comboBoxPlotVariable == 10) PlotParameter = "Recharge"; //bed outflow

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Setup time properties
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QString filename_at_zero = output_base_filename + extensions_list.at(0);
        Time_Values time_steps = Get_Time_Steps(filename_at_zero, element_count, true);
        QString time_step_units = tr("years");

        int time_step1 = time_steps.time_step1;
        int time_step2 = time_steps.time_step2;
        int time_step = time_step2 - time_step1;
        if( time_step <=0 )
        {
            Log_Error_Message(tr("<span style=\"color:#FF0000\">Problem with time_step </span>") + QString::number(time_step)  );
            return;
        }

        if ( time_step/(60*24*365)      >= 1 ) { time_step = 60*24*365; time_step_units = tr("years");   }
        else if ( time_step/(60*24*30)  >= 1 ) { time_step = 60*24*30;  time_step_units = tr("months");  }
        else if ( time_step/(60*24*7)   >= 1 ) { time_step = 60*24*7;   time_step_units = tr("weeks");   }
        else if ( time_step/(60*24*1)   >= 1 ) { time_step = 60*24*1;   time_step_units = tr("days");    }
        else if ( time_step/(60*1*1)    >= 1 ) { time_step = 60*1*1;    time_step_units = tr("hours");   }
        else if ( time_step/(1*1*1)     >= 1 ) { time_step = 1*1*1;     time_step_units = tr("minutes"); }

        Log_Message("time_step = " + QString::number( time_step) );
        Log_Message("time_step_units  = " + time_step_units );

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Get Number of time steps
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        int num_time_steps = 999999999;
        int temp_int = 0;

        for (int i=0; i<extensions_list.length(); i++)
        {
            QFile TempFile;
            QTextStream TempFileTextStream;
            QString TempQString;

            temp_int = 0;
            TempFile.setFileName(output_base_filename + extensions_list.at(i));
            TempFile.open(QIODevice::ReadOnly | QIODevice::Text);
            TempFileTextStream.setDevice(&TempFile);

            while ( ! TempFileTextStream.atEnd() )
            {
                TempQString = TempFileTextStream.readLine();
                temp_int++;
            }

            if (temp_int < num_time_steps)
                num_time_steps = temp_int;

            TempFile.close();
        }

        Log_Message("Number Time Steps = " + QString::number(num_time_steps) );
        if (num_time_steps < 2)
        {
            Log_Error_Message("Not enough data points to plot </span>" + QString::number(num_time_steps) );
            return;
        }
        if( num_time_steps >= 999999) //999999999  //TODO calculate available memory
        {
            Log_Error_Message("Too many data points to plot </span>" + QString::number(num_time_steps) );
            return;
        }
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Get Number of Model Segments
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        int index_model_segments = ui->comboBoxModelSegments->currentIndex();
        QString string_model_segments = ui->lineEditModelSegments->text();

        QStringList ModelSegments;
        if ( index_model_segments == 2 || index_model_segments == 4 )
        {
            for (int i=1; i<= element_count; i++)
                ModelSegments << QString::number(i);
        }
        else
        {
            ModelSegments = string_model_segments.split(QRegExp("\\s+"),QString::SkipEmptyParts);
        }

        Log_Message("Index of Model Segments = " + QString::number(index_model_segments) );
        Log_Message("Number of Segments = " + QString::number(ModelSegments.length()) );

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Get Segments for Graph(s)
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        int num_graphs = ModelSegments.length();
        if ( num_graphs < 1 )
        {
            Log_Error_Message("Model Segments Input Missing </span>" );
            return;
        }

        error_found = false;
        for (int i=0; i < num_graphs; i++)
        {
            int id = ModelSegments.at(i).toInt();
            if(id > element_count)
            {
                Log_Error_Message("Segment ID " + QString::number(id) + " greater than Max Segments (" + QString::number(element_count)+tr(")</span>") );
                error_found = true;
            }
        }
        if ( error_found)
        {
            Log_Error_Message("Issue(s) with Segments ID</span>" );
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Setup Labels
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        QString WindowTitle = tr("Mesh Time Series  ::  ") + PlotParameter;
        QString XLabel = tr("Time steps (") + time_step_units + tr(")");
        QString YLabel = ui->comboBoxPlotVariable->currentText();
        if ( PlotParameter.contains("Storage",Qt::CaseInsensitive) )
        {
            YLabel = YLabel + tr(" (m)");
        }
        else
        {
            YLabel = YLabel + tr(" (m/day)");
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Setup Legend
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QVector<QString> Legends(num_graphs);
        QVector<QVector<double>> datax(num_graphs), datay(num_graphs);
        for (int j=0; j < num_graphs; j++)
        {
            datax[j].resize(num_time_steps);
            datay[j].resize(num_time_steps);
        }

        for (int i=0; i < num_graphs; i++)
            Legends[i] = tr("Segment ") + ModelSegments.at(i);

        if(index_model_segments > 0)
            Legends[0] = ui->comboBoxModelSegments->currentText();

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Read Data
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ui->pushButtonRun->setText("Reading data for graphs");

        QFile DataFile;
        QTextStream DataFileTextStream;
        QString DataString;
        QStringList Data;

        for (int i=0; i < extensions_list.length(); i++)
        {
            DataFile.setFileName(output_base_filename + extensions_list.at(i));
            DataFile.open(QIODevice::ReadOnly | QIODevice::Text);
            DataFileTextStream.setDevice(&DataFile);

            int k=0;
            while ( ! DataFileTextStream.atEnd() )
            {
                DataString = DataFileTextStream.readLine();
                Data = DataString.split(QRegExp("\\s+"),QString::SkipEmptyParts);
                for (int j=0; j < num_graphs; j++)
                {
                    datax[j][k] = Data.at(0).toDouble() / time_step;
                    datay[j][k] = datay[j][k] + Data.at(ModelSegments.at(j).toInt()).toDouble();
                    //qDebug() << i << "," << j << "," << k << "," << ModelSegments.at(j).toInt() << ", "<< datax[j][k] << "," << datay[j][k] << "\n";
                }
                k++;
            }
            DataFile.close();
        }

        if ( index_model_segments != 0 )
        {
            if( num_graphs > 1 )
            {
                for (int i=0; i < num_time_steps; i++)
                {
                    for (int j=1; j < num_graphs; j++)
                    {
                        datay[0][i] += datay[j][i];
                    }
                    if( index_model_segments == 1 || index_model_segments == 2)
                        datay[0][i] = datay[0][i] / num_graphs;
                }
            }
            num_graphs = 1; //Why do this? As for loop below
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Setup Plot Window
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        QCustomPlotMainWindow *window = new QCustomPlotMainWindow;
        QCustomPlot *customPlot = new QCustomPlot;

        window->setCentralWidget(customPlot);

        QFont tickLabelFont = font();
        tickLabelFont.setPointSize(12);
        customPlot->xAxis->setTickLabelFont(tickLabelFont);
        customPlot->yAxis->setTickLabelFont(tickLabelFont);

        customPlot->xAxis2->setVisible(true);
        customPlot->yAxis2->setVisible(true);
        customPlot->xAxis2->setTicks(false);
        customPlot->yAxis2->setTicks(false);
        customPlot->xAxis2->setTickLabels(false);
        customPlot->yAxis2->setTickLabels(false);

        QPen gridPen = QPen();
        gridPen.setStyle(Qt::SolidLine);
        gridPen.setColor(QColor(200,200,200,255));
        customPlot->xAxis->grid()->setPen(gridPen);
        customPlot->yAxis->grid()->setPen(gridPen);

        customPlot->xAxis->grid()->setSubGridVisible(true);
        customPlot->yAxis->grid()->setSubGridVisible(true);

        QFont legendFont = font();
        legendFont.setPointSize(11);
        customPlot->legend->setFont(legendFont);
        customPlot->legend->setVisible(true);

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Create graph and assign data to it:
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QVector<double> x(num_time_steps), y(num_time_steps);

        double xmin=9E9, xmax=-9E9, ymin=9E9, ymax=-9E9;
        for (int j=0; j < num_graphs; j++)  //Why do this? As for loop above
        {
            for (int i=0; i < num_time_steps; i++)
            {
                x[i] = datax[j][i];
                y[i] = datay[j][i];
                if (x[i] < xmin) xmin = x[i];
                if (y[i] < ymin) ymin = y[i];
                if (x[i] > xmax) xmax = x[i];
                if (y[i] > ymax) ymax = y[i];
            }

            customPlot->addGraph();
            customPlot->graph(j)->setPen(QPen(QColor(rand()%255,rand()%255,rand()%255,255)));
            customPlot->graph(j)->setData(x, y);
            customPlot->graph(j)->setName(Legends[j]);
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Assign Labels to Axes
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QFont labelFont = font();
        labelFont.setPointSize(14);
        labelFont.setBold(true);
        labelFont.setCapitalization(QFont::AllUppercase);

        customPlot->xAxis->setLabelFont(labelFont);
        customPlot->yAxis->setLabelFont(labelFont);
        customPlot->xAxis->setLabel(XLabel);
        customPlot->yAxis->setLabel(YLabel);
        customPlot->xAxis->setRange(xmin, xmax);
        customPlot->yAxis->setRange(ymin, ymax);
        //customPlot->graph(0)->rescaleAxes();
        customPlot->replot();

        customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
        customPlot->setInteraction(QCP::iMultiSelect, true);

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update Project file
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QStringList ProjectIOStringList;

        ProjectIOStringList << "MeshTemporal" << project_folder << project_name;
        ProjectIOStringList << QString::number(index_model_segments);
        ProjectIOStringList << QString::number(current_index_comboBoxPlotVariable);
        ProjectIOStringList << string_model_segments;
        WriteModuleLine(filename_open_project, ProjectIOStringList);
        ProjectIOStringList.clear();

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update Message box and Reset buttons
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Clear_Log();

        ui->pushButtonRun->setText("Run");
        ui->pushButtonRun->setDefault(false);
        ui->pushButtonClose->setDefault(true);
        ui->pushButtonClose->setFocus();

        window->setWindowTitle(WindowTitle);
        window->show();

    } catch (...) {
        qDebug() << "Error: MeshTemporal::on_pushButtonRun_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Help button event
// TODO, Need cataract server back online
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MeshTemporal::on_pushButtonClose_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshTemporal::on_pushButtonClose_clicked()";

    try {
        close();
    } catch (...) {
        qDebug() << "Error: MeshTemporal::on_pushButtonClose_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Help button event
// TODO, Need cataract server back online
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MeshTemporal::on_pushButtonHelp_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshTemporal::on_pushButtonHelp_clicked()";

    try {
        //        LogsString = tr("");
        //        if ( ! QDesktopServices::openUrl(QUrl("http://cataract.cee.psu.edu/PIHM/index.php/PIHMgis_3.0#Temporal_Analysis:_Mesh_Elements")) )
        //            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Load HTTP Link ... </span>")+tr("<br>"));
        //        ui->textBrowserLogs->setHtml(LogsString);
        //        ui->textBrowserLogs->repaint();
    } catch (...) {
        qDebug() << "Error: MeshTemporal::on_pushButtonHelp_clicked() is returning w/o checking";
    }
}
