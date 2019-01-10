#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>

#include "meshdatafile.h"
#include "ui_meshdatafile.h"

#include "0LibsIO/IOProjectFile.h"
#include "0LibsOther/mesh_data_file.h"
#include "0LibsOther/interpolate_river_nodes_elev.h"
#include "globals.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MeshDataFile Constructor
// Parent is Main Window, filename is the open project text file used to store project details
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MeshDataFile::MeshDataFile(QWidget *parent, QString filename) :
    QDialog(parent),
    ui(new Ui::MeshDataFile)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshDataFile";

    try {
        ui->setupUi(this);

        filename_open_project = filename;
        bool found_file = false;

        QFile ProjectFile(filename_open_project);
        if ( ProjectFile.open(QIODevice::ReadOnly | QIODevice::Text) == false )
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
        qDebug() << "Error: SimplifyPolyMeshDataFilelines is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MeshDataFile Deconstructor
// Todo: Check for memory leaks
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MeshDataFile::~MeshDataFile()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ~MeshDataFile";

    try {
        delete ui;
    } catch (...) {
        qDebug() << "Error: ~MeshDataFile() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Load_Project_Settings
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool MeshDataFile::Load_Project_Settings()
{
    if (print_debug_messages)
        qDebug() << "INFO: MeshDataFile::Load_Project_Settings()";

    try {

        QStringList ModuleStringList = ReadModuleLine(filename_open_project,tr("TINShapeLayer"));
        if ( ModuleStringList.length() > 0  )
        {
            QString input_Element_filename = ModuleStringList.at(1);
            QString input_Node_filename = ModuleStringList.at(2);
            Check_ElementFile_Input(input_Element_filename);
            Check_NodeFile_Input(input_Node_filename);

            QString TempFileName = input_Node_filename;
            TempFileName.replace( QString(".1.node"), QString(".1.neigh") );
            Check_NeighbourFile_Input(TempFileName);

            TempFileName = ModuleStringList.at(3);
            TempFileName = TempFileName.right(TempFileName.length()-TempFileName.lastIndexOf("/")-1);
            TempFileName.replace( QString(".shp"), QString(".mesh") );

            QString output_filename = user_pihmgis_root_folder+"/4DataModelLoader/"+TempFileName;
            Check_MeshData_Output(output_filename, true);
        }

        ModuleStringList = ReadModuleLine(filename_open_project,tr("MergeVectorLayers"));
        if ( ModuleStringList.length() > 0  )
        {
            QString input_River_filename = ModuleStringList.at(1);
            Check_RiverFile_Input(input_River_filename);
        }

        ModuleStringList = ReadModuleLine(filename_open_project,tr("FillPits"));
        if ( ModuleStringList.length() > 0  )
        {
            QString input_SurfaceElevation_filename = ModuleStringList.at(2);
            Check_SurfaceElevationFile_Input(input_SurfaceElevation_filename);
        }

        ui->checkBoxSubsurfaceThickness->setChecked(true);
        ui->doubleSpinBoxSubSurface->setValue(5.0);

        ModuleStringList = ReadModuleLine(filename_open_project,tr("MeshDataFile"));
        if ( ModuleStringList.length() > 0 )
        {
            QString input_Element_filename = ModuleStringList.at(1);
            QString input_Node_filename = ModuleStringList.at(2);
            QString input_Neighbour_filename = ModuleStringList.at(3);
            QString input_River_filename = ModuleStringList.at(4);
            QString input_SurfaceElevation_filename = ModuleStringList.at(5);

            int checkBoxSubsurfaceThickness = ModuleStringList.at(6).toInt();
            QString input_Subsurface_value = ModuleStringList.at(7);
            QString output_filename = ModuleStringList.at(8);

            Check_ElementFile_Input(input_Element_filename);
            Check_NodeFile_Input(input_Node_filename);
            Check_NeighbourFile_Input(input_Neighbour_filename);
            Check_RiverFile_Input(input_River_filename);
            Check_SurfaceElevationFile_Input(input_SurfaceElevation_filename);

            if(checkBoxSubsurfaceThickness == 1)
            {
                ui->checkBoxSubsurfaceThickness->setChecked(true);
                ui->doubleSpinBoxSubSurface->setValue(input_Subsurface_value.toDouble());
            }
            else
            {
                Check_SubsurfaceThickness_Input(input_Subsurface_value);
            }

            Check_MeshData_Output(output_filename, true);
        }

        pushButtonSetFocus();

    } catch (...) {
        qDebug() << "Error: MeshDataFile::Load_Project_Settings is returning w/o checking";
        return false;
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Check Element File exists (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool MeshDataFile::Check_ElementFile_Input(QString file){

    if(print_debug_messages)
        qDebug() << "INFO: Check_ElementFile_Input()";

    bool result = false;

    try {

        if( fileExists(file) )
        {
            ui->lineEditElementFile->setStyleSheet("color: black;");
            ui->lineEditElementFile->setText(file);
            result = true;
        }
        else
        {
            ui->lineEditElementFile->setStyleSheet("color: red;");
            ui->lineEditElementFile->setText(file);

            result = false;
        }

    } catch (...) {
        qDebug() << "Error: Check_ElementFile_Input is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Check Node File exists (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool MeshDataFile::Check_NodeFile_Input(QString file){

    if(print_debug_messages)
        qDebug() << "INFO: Check_NodeFile_Input()";

    bool result = false;

    try {

        if( fileExists(file) )
        {
            ui->lineEditNodeFile->setStyleSheet("color: black;");
            ui->lineEditNodeFile->setText(file);
            result = true;
        }
        else
        {
            ui->lineEditNodeFile->setStyleSheet("color: red;");
            ui->lineEditNodeFile->setText(file);

            result = false;
        }

    } catch (...) {
        qDebug() << "Error: Check_NodeFile_Input is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Check NeighbourFile File exists (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool MeshDataFile::Check_NeighbourFile_Input(QString file){

    if(print_debug_messages)
        qDebug() << "INFO: Check_NeighbourFile_Input()";

    bool result = false;

    try {

        if(  fileExists(file) )
        {
            ui->lineEditNeighbourFile->setStyleSheet("color: black;");
            ui->lineEditNeighbourFile->setText(file);
            result = true;
        }
        else
        {
            ui->lineEditNeighbourFile->setStyleSheet("color: red;");
            ui->lineEditNeighbourFile->setText(file);
            result = false;
        }

    } catch (...) {
        qDebug() << "Error: Check_NeighbourFile_Input is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Check RiverFile File exists (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool MeshDataFile::Check_RiverFile_Input(QString file){

    if(print_debug_messages)
        qDebug() << "INFO: Check_RiverFile_Input()";

    bool result = false;

    try {

        if( fileExists(file) )
        {
            ui->lineEditRiverFile->setStyleSheet("color: black;");
            ui->lineEditRiverFile->setText(file);
            result = true;
        }
        else
        {
            ui->lineEditRiverFile->setStyleSheet("color: red;");
            ui->lineEditRiverFile->setText(file);
            result = false;
        }

    } catch (...) {
        qDebug() << "Error: Check_RiverFile_Input is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Check SurfaceElevation File exists (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool MeshDataFile::Check_SurfaceElevationFile_Input(QString file){

    if(print_debug_messages)
        qDebug() << "INFO: Check_SurfaceElevationFile_Input()";

    bool result = false;

    try {

        if( fileExists(file) )
        {
            ui->lineEditSurfaceElevationFile->setStyleSheet("color: black;");
            ui->lineEditSurfaceElevationFile->setText(file);
            result = true;
        }
        else
        {
            ui->lineEditSurfaceElevationFile->setStyleSheet("color: red;");
            ui->lineEditSurfaceElevationFile->setText(file);
            result = false;
        }


    } catch (...) {
        qDebug() << "Error: Check_SurfaceElevationFile_Input is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Check SubsurfaceThickness File exists (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool MeshDataFile::Check_SubsurfaceThickness_Input(QString file){

    if(print_debug_messages)
        qDebug() << "INFO: Check_SubsurfaceThickness_Input()";

    bool result = false;

    try {

        if( fileExists(file) )
        {
            ui->lineEditSubsurfaceThickness->setStyleSheet("color: black;");
            ui->lineEditSubsurfaceThickness->setText(file);
            result = true;
        }
        else
        {
            ui->lineEditSubsurfaceThickness->setStyleSheet("color: red;");
            ui->lineEditSubsurfaceThickness->setText(file);
            result = false;
        }

    } catch (...) {
        qDebug() << "Error: Check_SubsurfaceThickness_Input is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to assist if Check_MeshData_Output OUTPUT file exists (returns true) or does not (returns false)
// Will color red and warning if exists with color_and_message_if_exists=true
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool MeshDataFile::Check_MeshData_Output(QString file, bool color_and_message_if_exists){

    if(print_debug_messages)
        qDebug() << "INFO: Check_MeshData_Output()";

    bool result = false;

    try {

        if( fileExists(file) )
        {
            if(color_and_message_if_exists)
            {
                Log_Message("Warning: MeshData output already exists: " + file + " You may need to delete these files.");
            }

            ui->lineEditMeshDataFile->setStyleSheet("color: red;");
            ui->lineEditMeshDataFile->setText(file);
            result = true;
        }
        else
        {
            ui->lineEditMeshDataFile->setStyleSheet("color: black;");
            ui->lineEditMeshDataFile->setText(file);

            result = false;
        }

    } catch (...) {
        qDebug() << "Error: MeshDataFile::Check_MeshData_Output is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to clear message log
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MeshDataFile::Clear_Log()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshDataFile::Clear_Log()";

    try {

        LogsString = tr("");
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

    } catch (...) {
        qDebug() << "Error: MeshDataFile::Clear_Log() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check Log_Error_Message
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MeshDataFile::Log_Error_Message(QString message)
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
void MeshDataFile::Log_Message(QString message)
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
// Helper Function to focus button selection (needed for users w/o mouse)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MeshDataFile::pushButtonSetFocus()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshDataFile::pushButtonSetFocus()";

    try {

        ui->pushButtonElementFile->setDefault(false);
        ui->pushButtonNodeFile->setDefault(false);
        ui->pushButtonNeighbourFile->setDefault(false);
        ui->pushButtonRiverFile->setDefault(false);
        ui->pushButtonSurfaceElevationFile->setDefault(false);
        ui->pushButtonSubsurfaceThickness->setDefault(false);
        ui->pushButtonRun->setDefault(false);

        if (ui->lineEditElementFile->text() == nullptr)
        {
            ui->pushButtonElementFile->setDefault(true);
            ui->pushButtonElementFile->setFocus();
            return;
        }

        if (ui->lineEditNodeFile->text() == nullptr)
        {
            ui->pushButtonNodeFile->setDefault(true);
            ui->pushButtonNodeFile->setFocus();
            return;
        }

        if (ui->lineEditNeighbourFile->text() == nullptr)
        {
            ui->pushButtonNeighbourFile->setDefault(true);
            ui->pushButtonNeighbourFile->setFocus();
            return;
        }

        if (ui->lineEditRiverFile->text() == nullptr)
        {
            ui->pushButtonRiverFile->setDefault(true);
            ui->pushButtonRiverFile->setFocus();
            return;
        }

        if (ui->lineEditSurfaceElevationFile->text() == nullptr)
        {
            ui->pushButtonSurfaceElevationFile->setDefault(true);
            ui->pushButtonSurfaceElevationFile->setFocus();
            return;
        }

        if (ui->lineEditSubsurfaceThickness->text() == nullptr)
        {
            ui->pushButtonSubsurfaceThickness->setDefault(true);
            ui->pushButtonSubsurfaceThickness->setFocus();
            return;
        }

        ui->pushButtonRun->setDefault(true);
        ui->pushButtonRun->setFocus();

    } catch (...) {
        qDebug() << "Error: MeshDataFile::pushButtonSetFocus() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button Element Clicked Event (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MeshDataFile::on_pushButtonElementFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshDataFile::on_pushButtonElementFile_clicked()";

    try {

        Clear_Log();

        QString EleFileName = QFileDialog::getOpenFileName(this, "Ele (.1.ele) File", user_pihmgis_root_folder+tr("/3DomainDecomposition"), "Ele File(*.ele)");
        if ( EleFileName.isNull() == false)
        {
            if( EleFileName.isEmpty() == false)
            {
                Check_ElementFile_Input(EleFileName);
                pushButtonSetFocus();
            }
        }
        //else do nothing

    } catch (...) {
        qDebug() << "Error: MeshDataFile::on_pushButtonElementFile_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button Node Clicked Event (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MeshDataFile::on_pushButtonNodeFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshDataFile::on_pushButtonNodeFile_clicked()";

    try {

        Clear_Log();

        QString NodeFileName = QFileDialog::getOpenFileName(this, "Node (.1.node) File", user_pihmgis_root_folder+tr("/3DomainDecomposition"), "Node File(*.node)");
        if ( NodeFileName.isNull() == false)
        {
            if( NodeFileName.isEmpty() == false)
            {
                Check_NodeFile_Input(NodeFileName);
                pushButtonSetFocus();
            }
        }
        //else do nothing

    } catch (...) {
        qDebug() << "Error: SimplifyPolylines is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button Neighbour Clicked Event (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MeshDataFile::on_pushButtonNeighbourFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshDataFile::on_pushButtonNeighbourFile_clicked()";

    try {

        Clear_Log();

        QString NeighFileName = QFileDialog::getOpenFileName(this, "Neighbor (.1.Neigh) File", user_pihmgis_root_folder + tr("/3DomainDecomposition"), "Neigh File(*.neigh)");
        if ( NeighFileName.isNull() == false)
        {
            if( NeighFileName.isEmpty() == false)
            {
                Check_NeighbourFile_Input(NeighFileName);
                pushButtonSetFocus();
            }
        }
        //else do nothing

    } catch (...) {
        qDebug() << "Error: SimplifyPolylines is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button River Clicked Event (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MeshDataFile::on_pushButtonRiverFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshDataFile::on_pushButtonRiverFile_clicked()";

    try {

        Clear_Log();

        QString RiverFileName = QFileDialog::getOpenFileName(this, "River Split ShapeFile", user_pihmgis_root_folder+tr("/2VectorProcessing"), "River Split ShapeFile(*.shp)");
        if ( RiverFileName.isNull() == false)
        {
            if( RiverFileName.isEmpty() == false)
            {
                Check_RiverFile_Input(RiverFileName);
                pushButtonSetFocus();
            }
        }
        //else do nothing

    } catch (...) {
        qDebug() << "Error: on_pushButtonRiverFile_clicked is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button SurfaceElevation Clicked Event (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MeshDataFile::on_pushButtonSurfaceElevationFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshDataFile::on_pushButtonSurfaceElevationFile_clicked()";

    try {

        Clear_Log();

        QString SurfaceElevationFileName = QFileDialog::getOpenFileName(this, "Surface Elevation Raster", user_pihmgis_root_folder +tr("/1RasterProcessing"), "Surface Elevation Raster(*.adf *.asc)");

        if ( SurfaceElevationFileName.isNull() == false)
        {
            if( SurfaceElevationFileName.isEmpty() == false)
            {
                Check_SurfaceElevationFile_Input(SurfaceElevationFileName);
                pushButtonSetFocus();
            }
        }
        //else do nothing

    } catch (...) {
        qDebug() << "Error: on_pushButtonSurfaceElevationFile_clicked is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button SubsurfaceThickness Clicked Event (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MeshDataFile::on_pushButtonSubsurfaceThickness_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshDataFile::on_pushButtonSubsurfaceThickness_clicked()";

    try {

        Clear_Log();

        QString SubsurfaceElevationFileName = QFileDialog::getOpenFileName(this, "Sub-surface Elevation Raster", user_pihmgis_root_folder, "Sub-surface Elevation Raster(*.adf *.asc)");

        if ( SubsurfaceElevationFileName.isNull() == false)
        {
            if( SubsurfaceElevationFileName.isEmpty() == false)
            {
                ui->checkBoxSubsurfaceThickness->setChecked(false);
                Check_SubsurfaceThickness_Input(SubsurfaceElevationFileName);

                pushButtonSetFocus();
            }
        }
        //else do nothing

    } catch (...) {
        qDebug() << "Error: on_pushButtonSubsurfaceThickness_clicked is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button MeshData Clicked Event (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MeshDataFile::on_pushButtonMeshDataFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshDataFile::on_pushButtonMeshDataFile_clicked()";

    try {

        Clear_Log();

        QString MeshDataFileName = QFileDialog::getSaveFileName(this, "Choose Mesh Data File Name", user_pihmgis_root_folder +"/4DataModelLoader","Mesh Data File(*.mesh)");
        QString tempString = MeshDataFileName;
        if ( MeshDataFileName.isNull() == false)
        {
            if( MeshDataFileName.isEmpty() == false)
            {
                if( (tempString.toLower()).endsWith(".mesh") == false)
                {
                    tempString.append(".mesh");
                    MeshDataFileName = tempString;
                }

                Check_MeshData_Output(MeshDataFileName, true);
                pushButtonSetFocus();
            }
        }
        //else do nothing

    } catch (...) {
        qDebug() << "Error: on_pushButtonMeshDataFile_clicked is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Run Button Clicked Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MeshDataFile::on_pushButtonRun_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshDataFile::on_pushButtonRun_clicked()";

    try {

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Clear Log
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Clear_Log();

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check inputs
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QString input_Element_filename          = ui->lineEditElementFile->text();
        QString input_Node_filename             = ui->lineEditNodeFile->text();
        QString input_Neighbour_filename        = ui->lineEditNeighbourFile->text();
        QString input_River_filename            = ui->lineEditRiverFile->text();
        QString input_SurfaceElevation_filename = ui->lineEditSurfaceElevationFile->text();

        int checkBoxSubsurfaceThickness = ui->checkBoxSubsurfaceThickness->isChecked();
        QString input_Subsurface_value = ui->lineEditSubsurfaceThickness->text();

        bool checked_element = Check_ElementFile_Input(input_Element_filename);
        if(checked_element == false)
        {
            Log_Error_Message("Element (.1.ele) Input File Missing ");
            return;
        }

        bool checked_node = Check_NodeFile_Input(input_Node_filename);
        if(checked_node == false)
        {
            Log_Error_Message("Node (.1.node) Input File Missing ");
            return;
        }

        bool checked_neighbour = Check_NeighbourFile_Input(input_Neighbour_filename);
        if(checked_neighbour == false)
        {
            Log_Error_Message("Neighbor (.1.Neigh) Input File Missing ");
            return;
        }

        bool checked_river = Check_RiverFile_Input(input_River_filename);
        if(checked_river == false)
        {
            Log_Error_Message("River Split ShapeFile (*.shp) Input File Missing ");
            return;
        }

        if(checkBoxSubsurfaceThickness == 1)
        {
            //Do nothing
        }
        else
        {
            bool checked_surface = Check_SurfaceElevationFile_Input(input_SurfaceElevation_filename);
            if(checked_surface == false)
            {
                Log_Error_Message("Surface Elevation Raster (*.adf *.asc) Input File Missing ");
                return;
            }
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check Outputs
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QString output_filename = ui->lineEditMeshDataFile->text();

        bool output_check = Check_MeshData_Output(output_filename, true);
        if(output_check)
        {
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check file access
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if ( CheckFileAccess(input_Element_filename, "ReadOnly") == false)
        {
            Log_Error_Message("No Read Access to ... " + input_Element_filename);
            return;
        }

        if ( CheckFileAccess(input_Node_filename, "ReadOnly") == false)
        {
            Log_Error_Message("No Read Access to ... " + input_Node_filename);
            return;
        }

        if ( CheckFileAccess(input_Neighbour_filename, "ReadOnly") == false)
        {
            Log_Error_Message("No Read Access to ... " + input_Neighbour_filename );
            return;
        }

        if ( CheckFileAccess(input_River_filename, "ReadOnly") == false)
        {
            Log_Error_Message("No Read Access to ... " + input_River_filename );
            return;
        }

        if(checkBoxSubsurfaceThickness == 0)
        {
            if ( CheckFileAccess(input_SurfaceElevation_filename, "ReadOnly") == false)
            {
                Log_Error_Message("No Read Access to ... " + input_SurfaceElevation_filename );
                return;
            }
        }

        if ( CheckFileAccess(output_filename, "WriteOnly") == false)
        {
            Log_Error_Message("No Write Access to ... " + output_filename );
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Running Mesh Data File
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Log_Message("Running Mesh Data File ... ");

        int ErrorMesh = mesh_data_file(input_SurfaceElevation_filename,
                                       input_Subsurface_value,
                                       input_Element_filename,
                                       input_Node_filename,
                                       input_Neighbour_filename,
                                       output_filename,
                                       checkBoxSubsurfaceThickness);
        if( ErrorMesh != 0 )
        {
            Log_Error_Message("Mesh Data File Processing Failed ... ");
            Log_Error_Message("RETURN CODE MESH: ... " + QString::number(ErrorMesh));
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Running For River Data File
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QString RiverFileNameShp, RiverFileNameDbf;
        RiverFileNameShp = input_River_filename;
        RiverFileNameDbf = RiverFileNameShp;
        RiverFileNameDbf.replace( QString(".shp"), QString(".dbf") );

        QString MshRiverFileNameShp, MshRiverFileNameDbf;
        MshRiverFileNameShp = input_River_filename;
        MshRiverFileNameShp.replace( QString(".shp"), QString("_msh.shp") );

        MshRiverFileNameDbf = MshRiverFileNameShp;
        MshRiverFileNameDbf.replace( QString("_msh.shp"), QString("_msh.dbf") );

        QString OldMeshFileName, NewMeshFileName;
        NewMeshFileName = output_filename;
        OldMeshFileName = NewMeshFileName;
        OldMeshFileName.replace( QString(".mesh"), QString(".mesh.0") );

        //We know it shouldn't exist from above check, so will ignore failure.
        //TODO remove, but need to validate
        bool removed = QFile::remove(OldMeshFileName);
        bool renamed = QFile::rename(NewMeshFileName, OldMeshFileName);
        if(renamed == false)
        {
            Log_Error_Message("Failed to rename file " + NewMeshFileName);
            return;
        }

        int ErrorInterp = interpolate_river_nodes_elev(
                    RiverFileNameShp,
                    RiverFileNameDbf,
                    input_Element_filename,
                    input_Node_filename,
                    input_Neighbour_filename,
                    OldMeshFileName,
                    NewMeshFileName,
                    MshRiverFileNameShp,
                    MshRiverFileNameDbf );

        if( ErrorInterp != 0 )
        {
            Log_Error_Message("River Data File Processing Failed ... ");
            Log_Error_Message("RETURN CODE INTERP: ... " + QString::number(ErrorInterp) );
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Get Project Value
        // TODO Should this be a user parameter?
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QString ProjectID = output_filename;
        ProjectID = ProjectID.right( ProjectID.length() - ProjectID.lastIndexOf("/") - 1);
        ProjectID.chop(5);

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update Project file
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QStringList ProjectIOStringList;
        ProjectIOStringList << "MeshDataFile" << input_Element_filename << input_Node_filename << input_Neighbour_filename << input_River_filename << input_SurfaceElevation_filename << QString::number(ui->checkBoxSubsurfaceThickness->isChecked()) << ui->lineEditSubsurfaceThickness->text() << output_filename << ProjectID << MshRiverFileNameShp;
        WriteModuleLine(filename_open_project, ProjectIOStringList);
        ProjectIOStringList.clear();

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update Message box
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Clear_Log();

        Log_Message("Mesh Data File Processing Completed.");

        ui->pushButtonRun->setDefault(false);
        ui->pushButtonClose->setDefault(true);
        ui->pushButtonClose->setFocus();

    } catch (...) {
        qDebug() << "Error: on_pushButtonRun_clicked is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Close button event
// TODO, Decide on keeping button next highlights or not
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MeshDataFile::on_pushButtonClose_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshDataFile::on_pushButtonClose_clicked()";

    try {
        //QStringList default_params; default_params << "WORKFLOW5" << "ATTX";
        //QMetaObject::invokeMethod(parent(),"set_defaults",Q_ARG(QStringList,default_params));
        this->close();
    } catch (...) {
        qDebug() << "Error: on_pushButtonClose_clicked is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Help button event
// TODO, Need cataract server back online
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MeshDataFile::on_pushButtonHelp_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshDataFile::on_pushButtonHelp_clicked()";

    try {
        //        LogsString = tr("");
        //        if ( ! QDesktopServices::openUrl(QUrl("http://cataract.cee.psu.edu/PIHM/index.php/PIHMgis_3.0#mesh_Data_File")) )
        //            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Load HTTP Link ... </span>")+tr("<br>"));
        //        ui->textBrowserLogs->setHtml(LogsString);
        //        ui->textBrowserLogs->repaint();
    } catch (...) {
        qDebug() << "Error: on_pushButtonHelp_clicked is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to toggle subsurface methods
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MeshDataFile::on_checkBoxSubsurfaceThickness_toggled(bool checked)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshDataFile::on_checkBoxSubsurfaceThickness_toggled()";

    try {
        if ( checked == true )
        {
            ui->lineEditSubsurfaceThickness->setDisabled(true);
            ui->pushButtonSubsurfaceThickness->setDisabled(true);
            ui->doubleSpinBoxSubSurface->setDisabled(false);
        }
        else
        {
            ui->lineEditSubsurfaceThickness->setDisabled(false);
            ui->pushButtonSubsurfaceThickness->setDisabled(false);
            ui->lineEditSubsurfaceThickness->setText("");          //RESET
            ui->doubleSpinBoxSubSurface->setDisabled(true);
        }

    } catch (...) {
        qDebug() << "Error: on_checkBoxSubsurfaceThickness_toggled is returning w/o checking";
    }
}
