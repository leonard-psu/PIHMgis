#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>

#include "initdatafile.h"
#include "ui_initdatafile.h"

#include "0LibsIO/IOProjectFile.h"
#include "globals.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// InitDataFile Constructor
// Parent is Main Window, filename is the open project text file used to store project details
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
InitDataFile::InitDataFile(QWidget *parent, QString filename) :
    QDialog(parent),
    ui(new Ui::InitDataFile)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start InitDataFile";

    try {
        ui->setupUi(this);

        filename_open_project = filename;
        bool found_file = false;

        QFile ProjectFile(filename_open_project);
        if ( ! ProjectFile.open(QIODevice::ReadOnly | QIODevice::Text) )
        {
            Log_Error_Message("Unable to Open File: " + filename_open_project + tr("<br>"));
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
        qDebug() << "Error: InitDataFile is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// InitDataFile Deconstructor
// Todo: Check for memory leaks
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
InitDataFile::~InitDataFile()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ~InitDataFile";

    try {
        delete ui;
    } catch (...) {
        qDebug() << "Error: ~InitDataFile is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Load_Project_Settings
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool InitDataFile::Load_Project_Settings()
{
    if (print_debug_messages)
        qDebug() << "INFO: InitDataFile::Load_Project_Settings()";

    try {

        ui->radioButtonMeters->setChecked(false);
        ui->radioButtonPercent->setChecked(true);

        ui->lineEditInterception->setText(QString("0"));
        ui->lineEditSnow->setText(QString("0"));
        ui->lineEditSurface->setText(QString("0"));
        ui->lineEditSoilMoisture->setText(QString("40"));
        ui->lineEditGroundwater->setText(QString("40"));
        ui->lineEditRiver->setText(QString("40"));
        ui->lineEditRiverbed->setText(QString("40"));

        //Data Model INPUT File Name
        QStringList ModuleStringList = ReadModuleLine(filename_open_project,tr("TINShapeLayer"));
        if ( ModuleStringList.length() > 0  )
        {
            QString  TempFileName = ModuleStringList.at(3);
            TempFileName = TempFileName.right(TempFileName.length()-TempFileName.lastIndexOf("/")-1);

            TempFileName.replace( QString(".shp"), QString(".mesh") );
            QString mesh_file = user_pihmgis_root_folder+"/4DataModelLoader/"+TempFileName;
            Check_MeshData_Input(mesh_file);

            TempFileName.replace( QString(".mesh"), QString(".riv") );
            QString riv_file = user_pihmgis_root_folder+"/4DataModelLoader/"+TempFileName;
            Check_RivData_Input(riv_file);
        }

        ModuleStringList = ReadModuleLine(filename_open_project,tr("MeshDataFile"));
        if ( ModuleStringList.length() > 0  )
        {
            Check_MeshData_Input(ModuleStringList.at(8));
        }

        ModuleStringList = ReadModuleLine(filename_open_project,tr("RivDataFile"));
        if ( ModuleStringList.length() > 0  )
        {
            Check_RivData_Input(ModuleStringList.at(6));
        }

        //Data Model OUTPUT File Name
        ModuleStringList = ReadModuleLine(filename_open_project,tr("TINShapeLayer"));
        if ( ModuleStringList.length() > 0  )
        {
            QString TempFileName = ModuleStringList.at(3);
            TempFileName = TempFileName.right(TempFileName.length()-TempFileName.lastIndexOf("/")-1);
            TempFileName.replace( QString(".shp"), QString(".init") );

            QString init_file = user_pihmgis_root_folder+"/4DataModelLoader/"+TempFileName;
            Check_InitData_Output(init_file,true);
        }

        ModuleStringList = ReadModuleLine(filename_open_project,tr("MeshDataFile"));
        if ( ModuleStringList.length() > 0  )
        {
            QString TempFileName = ModuleStringList.at(9);
            QString init_file = user_pihmgis_root_folder+"/4DataModelLoader/"+TempFileName+".init";
            Check_InitData_Output(init_file,true);
        }
        //End: Set Defaults


        //Start: Fill Form If Module Has Been Run Previously

        ModuleStringList = ReadModuleLine(filename_open_project,tr("InitDataFile"));
        if ( ModuleStringList.length() > 0 )
        {
            if (ModuleStringList.at(8).toInt() == 2)
            {
                ui->radioButtonMeters->setChecked(false);
                ui->radioButtonPercent->setChecked(true);
            }
            else
            {
                ui->radioButtonMeters->setChecked(true);
                ui->radioButtonPercent->setChecked(false);
            }

            Check_Interception_Input(ModuleStringList.at(1));
            Check_Snow_Input(ModuleStringList.at(2));
            Check_Surface_Input(ModuleStringList.at(3));
            Check_SoilMoisture_Input(ModuleStringList.at(4));
            Check_Groundwater_Input(ModuleStringList.at(5));
            Check_River_Input(ModuleStringList.at(6));
            Check_Riverbed_Input(ModuleStringList.at(7));

            Check_MeshData_Input(ModuleStringList.at(9));
            Check_RivData_Input(ModuleStringList.at(10));

            Check_InitData_Output(ModuleStringList.at(11), true);

        }

        //End: Fill Form If Module Has Been Run Previously
        pushButtonSetFocus();

    } catch (...) {
        qDebug() << "Error: InitDataFile::Load_Project_Settings is returning w/o checking";
        return false;
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to clear message log
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InitDataFile::Clear_Log()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start InitDataFile::Clear_Log()";

    try {

        LogsString = tr("");
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

    } catch (...) {
        qDebug() << "Error: InitDataFile::Clear_Log() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to focus button selection (needed for users w/o mouse)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InitDataFile::pushButtonSetFocus()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start InitDataFile::pushButtonSetFocus()";

    try {

        ui->pushButtonMeshDataFile->setDefault(false);
        ui->pushButtonRivDataFile->setDefault(false);
        ui->pushButtonInitDataFile->setDefault(false);

        if (ui->lineEditInterception->text() == nullptr )
        {
            ui->lineEditInterception->setFocus();
            return;
        }

        if (ui->lineEditSnow->text() == nullptr )
        {
            ui->lineEditSnow->setFocus();
            return;
        }

        if (ui->lineEditSurface->text() == nullptr )
        {
            ui->lineEditSurface->setFocus();
            return;
        }

        if (ui->lineEditSoilMoisture->text() == nullptr )
        {
            ui->lineEditSoilMoisture->setFocus();
            return;
        }

        if (ui->lineEditGroundwater->text() == nullptr )
        {
            ui->lineEditGroundwater->setFocus();
            return;
        }

        if (ui->lineEditMeshDataFile->text() == nullptr)
        {
            ui->pushButtonMeshDataFile->setDefault(true);
            ui->pushButtonMeshDataFile->setFocus();
            return;
        }

        if (ui->lineEditRivDataFile->text() == nullptr)
        {
            ui->pushButtonRivDataFile->setDefault(true);
            ui->pushButtonRivDataFile->setFocus();
            return;
        }

        if (ui->lineEditInitDataFile->text() == nullptr)
        {
            ui->pushButtonInitDataFile->setDefault(true);
            ui->pushButtonInitDataFile->setFocus();
            return;
        }

        ui->pushButtonRun->setDefault(true);
        ui->pushButtonRun->setFocus();

    } catch (...) {
        qDebug() << "Error: InitDataFile::pushButtonSetFocus() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Check Interception File exists (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool InitDataFile::Check_Interception_Input(QString value)
{

    if(print_debug_messages)
        qDebug() << "INFO: Check_Interception_Input()";

    bool result = false;

    try {

        //TODO ui->lineEditInterception->setValidator( new QIntValidator(0,1,this) );

        if(value.isNull() || value.isEmpty() )
        {
            ui->lineEditInterception->setStyleSheet("color: red;");
            ui->lineEditInterception->setText("Missing");
            result = false;
        }
        else if(value == QString("Missing"))
        {
            result = false;
        }
        else
        {
            ui->lineEditInterception->setText(value);
            result = true; //For now assume validators work
        }


    } catch (...) {
        qDebug() << "Error: Check_Interception_Input is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Check Snow File exists (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool InitDataFile::Check_Snow_Input(QString value)
{

    if(print_debug_messages)
        qDebug() << "INFO: Check_Snow_Input()";

    bool result = false;

    try {
        //TODO ui->lineEditSnow->setValidator( new QIntValidator(0,1,this) );

        if(value.isNull() || value.isEmpty() )
        {
            ui->lineEditSnow->setStyleSheet("color: red;");
            ui->lineEditSnow->setText("Missing");
            result = false;
        }
        else if(value == QString("Missing"))
        {
            result = false;
        }
        else
        {
            ui->lineEditSnow->setText(value);
            result = true; //For now assume validators work
        }


    } catch (...) {
        qDebug() << "Error: Check_Snow_Input is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Check Surface File exists (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool InitDataFile::Check_Surface_Input(QString value)
{

    if(print_debug_messages)
        qDebug() << "INFO: Check_Surface_Input()";

    bool result = false;

    try {
        //TODO ui->lineEditSurface->setValidator( new QIntValidator(0,1,this) );

        if(value.isNull() || value.isEmpty() )
        {
            ui->lineEditSurface->setStyleSheet("color: red;");
            ui->lineEditSurface->setText("Missing");
            result = false;
        }
        else if(value == QString("Missing"))
        {
            result = false;
        }
        else
        {
            ui->lineEditSurface->setText(value);
            result = true; //For now assume validators work
        }

    } catch (...) {
        qDebug() << "Error: Check_Surface_Input is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Check SoilMoisture File exists (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool InitDataFile::Check_SoilMoisture_Input(QString value)
{

    if(print_debug_messages)
        qDebug() << "INFO: Check_SoilMoisture_Input()";

    bool result = false;

    try {

        //TODO ui->lineEditSoilMoisture->setValidator( new QIntValidator(0,1,this) );

        if(value.isNull() || value.isEmpty() )
        {
            ui->lineEditSoilMoisture->setStyleSheet("color: red;");
            ui->lineEditSoilMoisture->setText("Missing");
            result = false;
        }
        else if(value == QString("Missing"))
        {
            result = false;
        }
        else
        {
            ui->lineEditSoilMoisture->setText(value);
            result = true; //For now assume validators work
        }

    } catch (...) {
        qDebug() << "Error: Check_SoilMoisture_Input is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Check Groundwater File exists (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool InitDataFile::Check_Groundwater_Input(QString value){

    if(print_debug_messages)
        qDebug() << "INFO: Check_Groundwater_Input()";

    bool result = false;

    try {

        //TODO ui->lineEditGroundwater->setValidator( new QIntValidator(0,1,this) );

        if(value.isNull() || value.isEmpty() )
        {
            ui->lineEditGroundwater->setStyleSheet("color: red;");
            ui->lineEditGroundwater->setText("Missing");
            result = false;
        }
        else if(value == QString("Missing"))
        {
            result = false;
        }
        else
        {
            ui->lineEditGroundwater->setText(value);
            result = true; //For now assume validators work
        }

    } catch (...) {
        qDebug() << "Error: Check_Groundwater_Input is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Check River File exists (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool InitDataFile::Check_River_Input(QString value)
{

    if(print_debug_messages)
        qDebug() << "INFO: Check_River_Input()";

    bool result = false;

    try {


        //TODO ui->lineEditRiver->setValidator( new QIntValidator(0,1,this) );

        if(value.isNull() || value.isEmpty() )
        {
            ui->lineEditRiver->setStyleSheet("color: red;");
            ui->lineEditRiver->setText("Missing");
            result = false;
        }
        else if(value == QString("Missing"))
        {
            result = false;
        }
        else
        {
            ui->lineEditRiver->setText(value);
            result = true; //For now assume validators work
        }

    } catch (...) {
        qDebug() << "Error: Check_River_Input is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Check Riverbed File exists (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool InitDataFile::Check_Riverbed_Input(QString value)
{

    if(print_debug_messages)
        qDebug() << "INFO: Check_Riverbed_Input()";

    bool result = false;

    try {

        //TODO ui->lineEditRiverbed->setValidator( new QIntValidator(0,1,this) );

        if(value.isNull() || value.isEmpty() )
        {
            ui->lineEditRiverbed->setStyleSheet("color: red;");
            ui->lineEditRiverbed->setText("Missing");
            result = false;
        }
        else if(value == QString("Missing"))
        {
            result = false;
        }
        else
        {
            ui->lineEditRiverbed->setText(value);
            result = true; //For now assume validators work
        }


    } catch (...) {
        qDebug() << "Error: Check_Riverbed_Input is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Check MeshData File exists (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool InitDataFile::Check_MeshData_Input(QString file)
{

    if(print_debug_messages)
        qDebug() << "INFO: Check_MeshData_Input()";

    bool result = false;

    try {

        if(  fileExists(file) )
        {
            ui->lineEditMeshDataFile->setStyleSheet("color: black;");
            ui->lineEditMeshDataFile->setText(file);
            result = true;
        }
        else
        {
            ui->lineEditMeshDataFile->setStyleSheet("color: red;");
            ui->lineEditMeshDataFile->setText(file);

            Log_Error_Message("Missing Mesh input file: " + file +tr("<br>"));

            result = false;
        }

    } catch (...) {
        qDebug() << "Error: Check_MeshData_Input is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Check RivData File exists (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool InitDataFile::Check_RivData_Input(QString file)
{

    if(print_debug_messages)
        qDebug() << "INFO: Check_RivData_Input()";

    bool result = false;

    try {

        if(  fileExists(file) )
        {
            ui->lineEditRivDataFile->setStyleSheet("color: black;");
            ui->lineEditRivDataFile->setText(file);
            result = true;
        }
        else
        {
            ui->lineEditRivDataFile->setStyleSheet("color: red;");
            ui->lineEditRivDataFile->setText(file);

            Log_Error_Message("Missing River input file: " + file +tr("<br>"));

            result = false;
        }

    } catch (...) {
        qDebug() << "Error: Check_RivData_Input is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to assist if Check_InitData_Output OUTPUT file exists (returns true) or does not (returns false)
// Will color red and warning if exists with color_and_message_if_exists=true
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool InitDataFile::Check_InitData_Output(QString file, bool color_and_message_if_exists)
{

    if(print_debug_messages)
        qDebug() << "INFO: Check_InitData_Output()";

    bool result = false;

    try {

        if(  fileExists(file) )
        {
            if(color_and_message_if_exists)
            {
                Log_Warning_Message("InitData output already exists: " + file +tr(" You may need to delete thise file.<br>"));
            }

            ui->lineEditInitDataFile->setStyleSheet("color: red;");
            ui->lineEditInitDataFile->setText(file);
            result = true;
        }
        else
        {
            ui->lineEditInitDataFile->setStyleSheet("color: black;");
            ui->lineEditInitDataFile->setText(file);

            result = false;
        }

    } catch (...) {
        qDebug() << "Error: InitDataFile::Check_InitData_Output is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button MeshData Clicked Event (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InitDataFile::on_pushButtonMeshDataFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start InitDataFile::on_pushButtonMeshDataFile_clicked()";

    try {

        Clear_Log();

        QString MeshDataFileName = QFileDialog::getOpenFileName(this, "Mesh Data File Name", user_pihmgis_root_folder+"/4DataModelLoader","Mesh Data File(*.mesh)");

        if ( MeshDataFileName != nullptr)
        {
            Check_MeshData_Input(MeshDataFileName);
            pushButtonSetFocus();
        }


    } catch (...) {
        qDebug() << "Error: InitDataFile::on_pushButtonMeshDataFile_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button RivData Clicked Event (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InitDataFile::on_pushButtonRivDataFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start InitDataFile::on_pushButtonRivDataFile_clicked()";

    try {

        Clear_Log();

        QString RivDataFileName = QFileDialog::getOpenFileName(this, "Riv Data File Name", user_pihmgis_root_folder+"/4DataModelLoader","Riv Data File(*.riv)");

        if ( RivDataFileName != nullptr)
        {
            Check_RivData_Input(RivDataFileName);
            pushButtonSetFocus();
        }


    } catch (...) {
        qDebug() << "Error: InitDataFile::on_pushButtonRivDataFile_clicked is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button InitData Clicked Event (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InitDataFile::on_pushButtonInitDataFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start InitDataFile::on_pushButtonInitDataFile_clicked()";

    try {

        Clear_Log();

        QString InitDataFileName = QFileDialog::getSaveFileName(this, "Choose Init Data File Name", user_pihmgis_root_folder+"/4DataModelLoader","Init Data File(*.init)");
        QString tempString = InitDataFileName;
        if ( InitDataFileName != nullptr)
        {
            if( ! (tempString.toLower()).endsWith(".init") )
            {
                tempString.append(".init");
                InitDataFileName = tempString;
            }
            Check_InitData_Output(InitDataFileName, true);

            pushButtonSetFocus();
        }

    } catch (...) {
        qDebug() << "Error: InitDataFile::on_pushButtonInitDataFile_clicked is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button Interception Clicked Event (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InitDataFile::on_lineEditInterception_textChanged(const QString &arg1)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start InitDataFile::on_lineEditInterception_textChanged()";

    try {
        Check_Interception_Input(arg1);
    } catch (...) {
        qDebug() << "Error: InitDataFile::on_lineEditInterception_textChanged is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button Snow Clicked Event (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InitDataFile::on_lineEditSnow_textChanged(const QString &arg1)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start InitDataFile::on_lineEditSnow_textChanged()";

    try {
        Check_Snow_Input(arg1);
    } catch (...) {
        qDebug() << "Error: InitDataFile::on_lineEditSnow_textChanged is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button Surface Clicked Event (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InitDataFile::on_lineEditSurface_textChanged(const QString &arg1)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start InitDataFile::on_lineEditSurface_textChanged()";

    try {
        Check_Surface_Input(arg1);

    } catch (...) {
        qDebug() << "Error: InitDataFile::on_lineEditSurface_textChanged is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button SoilMoisture Clicked Event (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InitDataFile::on_lineEditSoilMoisture_textChanged(const QString &arg1)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start InitDataFile::on_lineEditSoilMoisture_textChanged()";

    try {
        Check_SoilMoisture_Input(arg1);

    } catch (...) {
        qDebug() << "Error: InitDataFile::on_lineEditSoilMoisture_textChanged is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button Groundwater Clicked Event (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InitDataFile::on_lineEditGroundwater_textChanged(const QString &arg1)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start InitDataFile::on_lineEditGroundwater_textChanged()";

    try {
        Check_Groundwater_Input(arg1);
    } catch (...) {
        qDebug() << "Error: InitDataFile::on_lineEditGroundwater_textChanged is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button River Clicked Event (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InitDataFile::on_lineEditRiver_textChanged(const QString &arg1)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start InitDataFile::on_lineEditRiver_textChanged()";

    try {
        Check_River_Input(arg1);

    } catch (...) {
        qDebug() << "Error: InitDataFile::on_lineEditRiver_textChanged is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button RiverBed Clicked Event (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InitDataFile::on_lineEditRiverbed_textChanged(const QString &arg1)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start InitDataFile::on_lineEditRiverbed_textChanged()";

    try {
        Check_Riverbed_Input(arg1);

    } catch (...) {
        qDebug() << "Error: InitDataFile::on_lineEditRiverbed_textChanged is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button radioButton Clicked Event (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InitDataFile::on_radioButtonMeters_toggled(bool checked)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start InitDataFile::on_radioButtonMeters_toggled()";

    try {
        ui->lineEditSoilMoisture->setStyleSheet("color: black;");
        ui->lineEditGroundwater->setStyleSheet("color: black;");
        ui->lineEditRiver->setStyleSheet("color: black;");
        ui->lineEditRiverbed->setStyleSheet("color: black;");

        pushButtonSetFocus();
    } catch (...) {
        qDebug() << "Error: InitDataFile::on_radioButtonMeters_toggled is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button radioButton Percent Clicked Event (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InitDataFile::on_radioButtonPercent_toggled(bool checked)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start InitDataFile::on_radioButtonPercent_toggled()";

    try {
        ui->lineEditSoilMoisture->setStyleSheet("color: black;");
        ui->lineEditGroundwater->setStyleSheet("color: black;");
        ui->lineEditRiver->setStyleSheet("color: black;");
        ui->lineEditRiverbed->setStyleSheet("color: black;");

        pushButtonSetFocus();
    } catch (...) {
        qDebug() << "Error: InitDataFile::on_radioButtonPercent_toggled is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to create init_data_file
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int InitDataFile::init_data_file(QString Interception, QString Snow, QString Surface, QString SoilMoisture, QString Groundwater,
                                 QString River, QString Riverbed, int MetersOrPercent,
                                 QString MeshDataFileName, QString RivDataFileName, QString InitDataFileName)
{

    if(print_debug_messages)
        qDebug() << "INFO: Start InitDataFile::init_data_file()";

    try {

        if(print_debug_messages)
        {
            qDebug() << "Interception = " << Interception;
            qDebug() << "Snow = " << Snow;
            qDebug() << "Surface = " << Surface;
            qDebug() << "SoilMoisture = " << SoilMoisture;
            qDebug() << "Groundwater = " << Groundwater;
            qDebug() << "River = " << River;
            qDebug() << "Riverbed = " << Riverbed;
            qDebug() << "MetersOrPercent = " << MetersOrPercent;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Load Data from Files
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        QFile MeshDataFile(MeshDataFileName);
        if ( ! MeshDataFile.open(QIODevice::ReadOnly | QIODevice::Text) )
            return 404;
        QTextStream MeshDataFileTextStream(&MeshDataFile);

        QFile RivDataFile(RivDataFileName);
        if ( ! RivDataFile.open(QIODevice::ReadOnly | QIODevice::Text) )
            return 409;
        QTextStream RivDataFileTextStream(&RivDataFile);

        QFile InitDataFile(InitDataFileName);
        if ( ! InitDataFile.open(QIODevice::WriteOnly | QIODevice::Text) )
            return 414;
        QTextStream InitDataFileTextStream(&InitDataFile);

        int NumTINs, NumNodes, NumRiverSegs, NumRiverShapes;
        int TempInt;
        double TempDouble, SurfaceElevation, BedElevation;
        QString TempString;

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Using Percent
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        if ( MetersOrPercent == 2 )
        {
            MeshDataFileTextStream >> NumTINs;
            MeshDataFileTextStream >> NumNodes;

            int **TINnodes;
            TINnodes = new int*[NumTINs];
            for (int i=0; i<NumTINs; i++)
                TINnodes[i] = new int [3];


            double *NodeDepths, *TINDepths;
            NodeDepths = new double [NumNodes];
            TINDepths  = new double [NumTINs];


            for (int i=0; i<NumTINs; i++)
            {
                MeshDataFileTextStream >> TempInt;
                MeshDataFileTextStream >> TINnodes[i][0];
                MeshDataFileTextStream >> TINnodes[i][1];
                MeshDataFileTextStream >> TINnodes[i][2];
                MeshDataFileTextStream >> TempInt;
                MeshDataFileTextStream >> TempInt;
                MeshDataFileTextStream >> TempInt;
            }
            for (int i=0; i<NumNodes; i++)
            {
                MeshDataFileTextStream >> TempInt;
                MeshDataFileTextStream >> TempDouble;
                MeshDataFileTextStream >> TempDouble;

                MeshDataFileTextStream >> BedElevation;
                MeshDataFileTextStream >> SurfaceElevation;

                NodeDepths[i] = SurfaceElevation - BedElevation;

                if ( NodeDepths[i] < 0 )
                    return 455;
            }

            RivDataFileTextStream >> NumRiverSegs;

            int **RiverSegNodes, *RiverSegShape;
            double *RiverDepths;

            RiverSegNodes = new int*[NumRiverSegs];
            for (int i=0; i<NumRiverSegs; i++)
                RiverSegNodes[i] = new int [2];
            RiverSegShape = new int [NumRiverSegs];

            for (int i=0; i<NumRiverSegs; i++)
            {
                RivDataFileTextStream >> TempInt;
                RivDataFileTextStream >> RiverSegNodes[i][0];
                RivDataFileTextStream >> RiverSegNodes[i][1];
                RivDataFileTextStream >> TempInt;
                RivDataFileTextStream >> TempInt; RivDataFileTextStream >> TempInt;
                RivDataFileTextStream >> TempInt; RivDataFileTextStream >> TempInt; RivDataFileTextStream >> RiverSegShape[i];
                RivDataFileTextStream >> TempInt; RivDataFileTextStream >> TempInt;
            }
            RivDataFileTextStream >> TempString;
            RivDataFileTextStream >> NumRiverShapes;

            RiverDepths = new double [NumRiverShapes];
            for (int i=0; i<NumRiverShapes; i++)
            {
                RivDataFileTextStream >> TempInt;
                RivDataFileTextStream >> RiverDepths[i];
            }

            for (int i=0; i<NumTINs; i++)
            {

                qDebug() << Interception << " " << Snow << " " << Surface << " " << SoilMoisture.toDouble();
                qDebug() << NodeDepths[ TINnodes[i][0]-1 ];
                qDebug() << NodeDepths[ TINnodes[i][1]-1 ];
                qDebug() << NodeDepths[ TINnodes[i][2]-1 ];

                InitDataFileTextStream << Interception << "\t";
                InitDataFileTextStream << Snow << "\t";
                InitDataFileTextStream << Surface << "\t";
                InitDataFileTextStream << ( SoilMoisture.toDouble() / 100.0 ) * ( ( NodeDepths[ TINnodes[i][0]-1 ] + NodeDepths[ TINnodes[i][1]-1 ] + NodeDepths[ TINnodes[i][2]-1 ] ) / 3.0 ) << "\t";
                InitDataFileTextStream << ( Groundwater.toDouble()  / 100.0 ) * ( ( NodeDepths[ TINnodes[i][0]-1 ] + NodeDepths[ TINnodes[i][1]-1 ] + NodeDepths[ TINnodes[i][2]-1 ] ) / 3.0 ) << "\n";
            }
            for (int i=0; i<NumRiverSegs; i++)
            {
                InitDataFileTextStream << ( River.toDouble()    / 100.0 ) * ( RiverDepths[ RiverSegShape[i]-1 ] ) << "\t";
                InitDataFileTextStream << ( Riverbed.toDouble() / 100.0 ) * ( ( NodeDepths[ RiverSegNodes[i][0]-1 ] + NodeDepths[ RiverSegNodes[i][1]-1 ] ) / 2 - RiverDepths[ RiverSegShape[i]-1 ] ) << "\n";
            }

            delete [] NodeDepths;
            delete [] TINDepths;
            for (int i=0; i<NumTINs; i++)
                delete [] TINnodes[i];
            delete [] TINnodes;
            for (int i=0; i<NumRiverSegs; i++)
                delete [] RiverSegNodes[i];
            delete [] RiverSegNodes;
            delete [] RiverSegShape;
            delete [] RiverDepths;
        }
        else
        {

            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            // Using Meters
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            MeshDataFileTextStream >> NumTINs;
            RivDataFileTextStream  >> NumRiverSegs;
            for (int i=0; i<NumTINs; i++)
            {
                InitDataFileTextStream << Interception << "\t";
                InitDataFileTextStream << Snow << "\t";
                InitDataFileTextStream << Surface << "\t";
                InitDataFileTextStream << SoilMoisture << "\t";
                InitDataFileTextStream << Groundwater << "\n";
            }
            for (int i=0; i<NumRiverSegs; i++)
            {
                InitDataFileTextStream << River << "\t";
                InitDataFileTextStream << Riverbed << "\n";
            }
        }

        MeshDataFile.close();
        RivDataFile.close();
        InitDataFile.close();

    } catch (...) {
        qDebug() << "Error: InitDataFile::init_data_file is returning w/o checking";
    }

    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check Log_Error_Message
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InitDataFile::Log_Warning_Message(QString message)
{
    try {
        LogsString.append(tr("<span style=\"color:#FF0000\">Warning: ") + message + " </span>")+tr("<br>");
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();
    } catch (...) {
        qDebug() << "Error: Log_Error_Message is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check Log_Error_Message
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InitDataFile::Log_Error_Message(QString message)
{
    try {
        LogsString.append(tr("<span style=\"color:#FF0000\">Error: ") + message + " </span>")+tr("<br>");
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();
    } catch (...) {
        qDebug() << "Error: Log_Error_Message is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Run Button Clicked Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InitDataFile::on_pushButtonRun_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start InitDataFile::on_pushButtonRun_clicked()";

    try {

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Clear Log
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Clear_Log();

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check inputs
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        QString input_Interception = ui->lineEditInterception->text();
        QString input_Snow_Input = ui->lineEditSnow->text();
        QString input_Surface_Input = ui->lineEditSurface->text();
        QString input_SoilMoisture_Input = ui->lineEditSoilMoisture->text();
        QString input_Groundwater_Input = ui->lineEditGroundwater->text();
        QString input_River_Input = ui->lineEditRiver->text();
        QString input_Riverbed_Input = ui->lineEditRiverbed->text();

        QString input_MeshData_Input = ui->lineEditMeshDataFile->text();
        QString input_RivData_Input = ui->lineEditRivDataFile->text();

        int MetersOrPercent = 2;
        if ( ui->radioButtonMeters->isChecked() )
            MetersOrPercent = 1;
        if ( ui->radioButtonPercent->isChecked() )
            MetersOrPercent = 2;

        bool checked_input = Check_Interception_Input(input_Interception);
        if(!checked_input)
        {
            Log_Error_Message("Interception Input File or Value Missing " + input_Interception );
            return;
        }
        checked_input = Check_Snow_Input(input_Interception);
        if(!checked_input)
        {
            Log_Error_Message("Snow Input File or Value Missing " + input_Snow_Input );
            return;
        }
        checked_input = Check_Surface_Input(input_Surface_Input);
        if(!checked_input)
        {
            Log_Error_Message("Surface Input File or Value Missing " + input_Surface_Input );
            return;
        }
        checked_input = Check_SoilMoisture_Input(input_SoilMoisture_Input);
        if(!checked_input)
        {
            Log_Error_Message("SoilMoisture Input File or Value Missing " + input_SoilMoisture_Input );
            return;
        }
        checked_input = Check_Groundwater_Input(input_Groundwater_Input);
        if(!checked_input)
        {
            Log_Error_Message("Groundwater Input File or Value Missing " + input_Groundwater_Input );
            return;
        }
        checked_input = Check_River_Input(input_River_Input);
        if(!checked_input)
        {
            Log_Error_Message("Groundwater Input File or Value Missing " + input_River_Input );
            return;
        }
        checked_input = Check_Riverbed_Input(input_Riverbed_Input);
        if(!checked_input)
        {
            Log_Error_Message("Groundwater Input Riverbed or Value Missing " + input_Riverbed_Input );
            return;
        }
        checked_input = Check_MeshData_Input(input_MeshData_Input);
        if(!checked_input)
        {
            Log_Error_Message("MeshData Input Riverbed or Value Missing " + input_MeshData_Input );
            return;
        }
        checked_input = Check_RivData_Input(input_RivData_Input);
        if(!checked_input)
        {
            Log_Error_Message("MeshData Input Riverbed or Value Missing " + input_RivData_Input );
            return;
        }
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // CheckFileAccess
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        if ( !CheckFileAccess(input_MeshData_Input, "ReadOnly") )
        {
            Log_Error_Message("No Read Access to MeshData Input File or Value Missing " + input_MeshData_Input );
            return;
        }
        if ( !CheckFileAccess(input_RivData_Input, "ReadOnly") )
        {
            Log_Error_Message("No Read Access to RivData Input File or Value Missing " + input_RivData_Input );
            return;
        }
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check Output and Write Access
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QString output_InitData = ui->lineEditInitDataFile->text();

        bool checked_output = Check_InitData_Output(output_InitData, true);
        if(checked_output)
        {
            return;
        }
        if ( ! CheckFileAccess(output_InitData, "WriteOnly") )
        {
            Log_Error_Message("No Write Access to " + output_InitData + tr("<br>"));
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Running INIT Data File
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        LogsString.append("Running Init Data File ... <br>");
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();


        int ErrorInit = init_data_file(input_Interception,
                                       input_Snow_Input,
                                       input_Surface_Input,
                                       input_SoilMoisture_Input,
                                       input_Groundwater_Input,
                                       input_River_Input,
                                       input_Riverbed_Input,
                                       MetersOrPercent,
                                       input_MeshData_Input,
                                       input_RivData_Input,
                                       output_InitData );

        if( ErrorInit != 0 )
        {
            Log_Error_Message("Init Data File Processing Failed " + tr("<br>"));
            Log_Error_Message("Init error return code: " + QString::number(ErrorInit) + tr("<br>"));
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update Project file
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QStringList ProjectIOStringList;

        ProjectIOStringList << "InitDataFile"
                            << input_Interception
                            << input_Snow_Input
                            << input_Surface_Input
                            << input_SoilMoisture_Input
                            << input_Groundwater_Input
                            << input_River_Input
                            << input_Riverbed_Input;

        if ( ui->radioButtonMeters->isChecked() )
            ProjectIOStringList << "1";

        if ( ui->radioButtonPercent->isChecked() )
            ProjectIOStringList << "2";

        ProjectIOStringList << input_MeshData_Input << input_RivData_Input << output_InitData;

        WriteModuleLine(filename_open_project, ProjectIOStringList);
        ProjectIOStringList.clear();

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update Message box
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Clear_Log();

        LogsString.append(tr("<br><b>Init Data File Processing Complete.</b>")+tr("<br>"));
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

        ui->pushButtonRun->setDefault(false);
        ui->pushButtonClose->setDefault(true);
        ui->pushButtonClose->setFocus();


    } catch (...) {
        qDebug() << "Error: InitDataFile::on_pushButtonRun_clicked is returning w/o checking";
    }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Close button event
// TODO, Decide on keeping button next highlights or not
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InitDataFile::on_pushButtonClose_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start InitDataFile::on_pushButtonClose_clicked()";

    try {
        //QStringList default_params; default_params << "WORKFLOW5" << "IBCX";
        //QMetaObject::invokeMethod(parent(),"set_defaults",Q_ARG(QStringList,default_params));
        close();
    } catch (...) {
        qDebug() << "Error: InitDataFile::on_pushButtonClose_clicked is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Help button event
// TODO, Need cataract server back online
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InitDataFile::on_pushButtonHelp_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start InitDataFile::on_pushButtonHelp_clicked()";

    try {
        //        LogsString = tr("");
        //        if ( ! QDesktopServices::openUrl(QUrl("http://cataract.cee.psu.edu/PIHM/index.php/PIHMgis_3.0#init_Data_File")) )
        //            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Load HTTP Link ... </span>")+tr("<br>"));
        //        ui->textBrowserLogs->setHtml(LogsString);
        //        ui->textBrowserLogs->repaint();
    } catch (...) {
        qDebug() << "Error: InitDataFile::on_pushButtonHelp_clicked is returning w/o checking";
    }
}
