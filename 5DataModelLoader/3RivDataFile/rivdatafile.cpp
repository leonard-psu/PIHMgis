#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>

#include "rivdatafile.h"
#include "ui_rivdatafile.h"

#include "0LibsIO/IOProjectFile.h"
#include "0LibsOther/riv_data_file.h"
#include "globals.h"

extern QString riv_temp_fname; // "/rivtemp.dbf";  //Note keep forward slash

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RivDataFile Constructor
// Parent is Main Window, filename is the open project text file used to store project details
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RivDataFile::RivDataFile(QWidget *parent, QString filename) :
    QDialog(parent),
    ui(new Ui::RivDataFile)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start RivDataFile";

    try {
        ui->setupUi(this);

        filename_open_project = filename;
        bool found_file = false;

        QFile ProjectFile(filename_open_project);
        if ( ! ProjectFile.open(QIODevice::ReadOnly | QIODevice::Text) )
        {
            Log_Error_Message(tr("<span style=\"color:#FF0000\">ERROR: Unable to Open File: </span>") + filename_open_project + tr("<br>"));
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
        qDebug() << "Error: RivDataFile is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RivDataFile Deconstructor
// Todo: Check for memory leaks
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RivDataFile::~RivDataFile()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ~RivDataFile";

    try {
        delete ui;
    } catch (...) {
        qDebug() << "Error: ~RivDataFile is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Load_Project_Settings
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool RivDataFile::Load_Project_Settings()
{
    if (print_debug_messages)
        qDebug() << "INFO: RivDataFile::Load_Project_Settings()";

    try {

        QStringList ModuleStringList;

        // Data Model OUTPUT File Name
        ModuleStringList = ReadModuleLine(filename_open_project,tr("TINShapeLayer"));
        if ( ModuleStringList.length() > 0  )
        {
            QString TempFileName = ModuleStringList.at(3);
            TempFileName = TempFileName.right(TempFileName.length()-TempFileName.lastIndexOf("/")-1);
            TempFileName.replace( QString(".shp"), QString(".riv") );

            QString output_filename = user_pihmgis_root_folder+"/4DataModelLoader/"+TempFileName;
            Check_RiverData_Output(output_filename,true);
        }

        ModuleStringList = ReadModuleLine(filename_open_project,tr("MeshDataFile"));
        if ( ModuleStringList.length() > 0  )
        {
            QString TempFileName = ModuleStringList.at(9);
            QString output_filename = user_pihmgis_root_folder+"/4DataModelLoader/"+TempFileName+".riv";
            Check_RiverData_Output(output_filename,true);
        }

        ModuleStringList = ReadModuleLine(filename_open_project,tr("TINShapeLayer"));
        if ( ModuleStringList.length() > 0  )
        {
            QString ElementFileName = ModuleStringList.at(1);
            QString NodeName = ModuleStringList.at(2);

            Check_Element_Input(ElementFileName);
            Check_Node_Input(NodeName);

            QString TempFileName = ModuleStringList.at(2);
            TempFileName.replace( QString(".1.node"), QString(".1.neigh") );
            Check_Neighbor_Input(TempFileName);
        }

        ModuleStringList = ReadModuleLine(filename_open_project,tr("MergeVectorLayers"));
        if ( ModuleStringList.length() > 0  )
        {
            Check_RiverShape_Input(ModuleStringList.at(1));
        }

        ui->radioButtonZeroDepth->setChecked(true);
        // End: Set Defaults


        // Start: Fill Form If Module Has Been Run Previously

        ModuleStringList = ReadModuleLine(filename_open_project,tr("RivDataFile"));
        if ( ModuleStringList.length() > 0 )
        {
            Check_Element_Input(ModuleStringList.at(1));
            Check_Node_Input(ModuleStringList.at(2));
            Check_Neighbor_Input(ModuleStringList.at(3));
            Check_RiverShape_Input(ModuleStringList.at(4));

            if ( ModuleStringList.at(5).toInt() == -1 ) ui->radioButtonDirichlet->setChecked(true);
            if ( ModuleStringList.at(5).toInt() == -2 ) ui->radioButtonNeumann->setChecked(true);
            if ( ModuleStringList.at(5).toInt() == -3 ) ui->radioButtonZeroDepth->setChecked(true);
            if ( ModuleStringList.at(5).toInt() == -4 ) ui->radioButtonCriticalDepth->setChecked(true);

            Check_RiverData_Output(ModuleStringList.at(6), true);
        }
        // End: Fill Form If Module Has Been Run Previously

        pushButtonSetFocus();

    } catch (...) {
        qDebug() << "Error: RivDataFile::Load_Project_Settings is returning w/o checking";
        return false;
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to clear message log
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RivDataFile::Clear_Log()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start RivDataFile::Clear_Log()";

    try {

        LogsString = tr("");
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

    } catch (...) {
        qDebug() << "Error: RivDataFile::Clear_Log() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to focus button selection (needed for users w/o mouse)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RivDataFile::pushButtonSetFocus()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start RivDataFile::pushButtonSetFocus()";

    try {
        ui->pushButtonElementFile->setDefault(false);
        ui->pushButtonNodeFile->setDefault(false);
        ui->pushButtonNeighbourFile->setDefault(false);
        ui->pushButtonRiverFile->setDefault(false);
        ui->pushButtonRivDataFile->setDefault(false);
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

        if (ui->lineEditRivDataFile->text() == nullptr)
        {
            ui->pushButtonRivDataFile->setDefault(true);
            ui->pushButtonRivDataFile->setFocus();
            return;
        }

        ui->pushButtonRun->setDefault(true);
        ui->pushButtonRun->setFocus();

    } catch (...) {
        qDebug() << "Error: RivDataFile::pushButtonSetFocus() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Check Element File exists (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool RivDataFile::Check_Element_Input(QString file)
{
    if(print_debug_messages)
        qDebug() << "INFO: Check_Element_Input()";

    bool result = false;

    try {

        if(  fileExists(file) )
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
        qDebug() << "Error: Check_Element_Input is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Check Node File exists (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool RivDataFile::Check_Node_Input(QString file)
{
    if(print_debug_messages)
        qDebug() << "INFO: Check_Node_Input()";

    bool result = false;

    try {

        if(  fileExists(file) )
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
        qDebug() << "Error: Check_Node_Input is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Check Neighbor File exists (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool RivDataFile::Check_Neighbor_Input(QString file)
{
    if(print_debug_messages)
        qDebug() << "INFO: Check_Neighbor_Input()";

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
        qDebug() << "Error: Check_Neighbor_Input is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Check Element File exists (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool RivDataFile::Check_RiverShape_Input(QString file)
{
    if(print_debug_messages)
        qDebug() << "INFO: Check_RiverShape_Input()";

    bool result = false;

    try {

        if(  fileExists(file) )
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
        qDebug() << "Error: Check_RiverShape_Input is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to assist if Check_RiverData_Output OUTPUT file exists (returns true) or does not (returns false)
// Will color red and warning if exists with color_and_message_if_exists=true
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool RivDataFile::Check_RiverData_Output(QString file, bool color_and_message_if_exists)
{
    if(print_debug_messages)
        qDebug() << "INFO: Check_RiverData_Output()";

    bool result = false;

    try {

        if(  fileExists(file) )
        {
            if(color_and_message_if_exists)
            {
                Log_Warning_Message(tr("<span style=\"color:#FF0000\">Warning: RiverData output already exists: </span>") + file +tr(" You may need to delete these files.<br>"));
            }

            ui->lineEditRivDataFile->setStyleSheet("color: red;");
            ui->lineEditRivDataFile->setText(file);
            result = true;
        }
        else
        {
            ui->lineEditRivDataFile->setStyleSheet("color: black;");
            ui->lineEditRivDataFile->setText(file);
            result = false;
        }

    } catch (...) {
        qDebug() << "Error: MeshDataFile::Check_RiverData_Output is returning w/o checking";
        result = false;
    }

    return result;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button Element Clicked Event (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RivDataFile::on_pushButtonElementFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start RivDataFile::on_pushButtonElementFile_clicked()";

    try {

        Clear_Log();

        QString EleFileName = QFileDialog::getOpenFileName(this, "Ele (.1.ele) File", user_pihmgis_root_folder +tr("/3DomainDecomposition"), "Ele File(*.ele)");
        if ( EleFileName != nullptr)
        {
            Check_Element_Input(EleFileName);
            pushButtonSetFocus();
        }

    } catch (...) {
        qDebug() << "Error: RivDataFile::on_pushButtonElementFile_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button Node Clicked Event (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RivDataFile::on_pushButtonNodeFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start RivDataFile::on_pushButtonNodeFile_clicked()";

    try {

        Clear_Log();

        QString NodeFileName = QFileDialog::getOpenFileName(this, "Node (.1.node) File", user_pihmgis_root_folder+tr("/3DomainDecomposition"), "Node File(*.node)");
        if ( NodeFileName != nullptr)
        {
            Check_Node_Input(NodeFileName);
            pushButtonSetFocus();
        }

    } catch (...) {
        qDebug() << "Error: RivDataFile::on_pushButtonNodeFile_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button Neighbour Clicked Event (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RivDataFile::on_pushButtonNeighbourFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start RivDataFile::on_pushButtonNeighbourFile_clicked()";

    try {

        Clear_Log();

        QString NeighFileName = QFileDialog::getOpenFileName(this, "Neighbor (.1.Neigh) File", user_pihmgis_root_folder+tr("/3DomainDecomposition"), "Neigh File(*.neigh)");
        if ( NeighFileName != nullptr)
        {
            Check_Neighbor_Input(NeighFileName);
            pushButtonSetFocus();
        }

    } catch (...) {
        qDebug() << "Error: RivDataFile::on_pushButtonNeighbourFile_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button RiverFile Clicked Event (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RivDataFile::on_pushButtonRiverFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start RivDataFile::on_pushButtonRiverFile_clicked()";

    try {

        Clear_Log();

        QString RiverFileName = QFileDialog::getOpenFileName(this, "River Split ShapeFile", user_pihmgis_root_folder+tr("/2VectorProcessing"), "River Split ShapeFile(*.shp)");
        if ( RiverFileName != nullptr)
        {
            Check_RiverShape_Input(RiverFileName);
            pushButtonSetFocus();
        }

    } catch (...) {
        qDebug() << "Error: RivDataFile::on_pushButtonRiverFile_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button RivData Clicked Event (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RivDataFile::on_pushButtonRivDataFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start RivDataFile::on_pushButtonRivDataFile_clicked()";

    try {

        Clear_Log();

        QString RivDataFileName = QFileDialog::getSaveFileName(this, "Choose Riv Data File Name", user_pihmgis_root_folder+"/4DataModelLoader","Riv Data File(*.riv)");
        QString tempString = RivDataFileName;
        if ( RivDataFileName != nullptr)
        {
            ui->lineEditRivDataFile->setStyleSheet("color: black;");

            if( ! (tempString.toLower()).endsWith(".riv") )
            {
                tempString.append(".riv");
                RivDataFileName = tempString;
            }
            Check_RiverData_Output(RivDataFileName, true);

            pushButtonSetFocus();
        }


    } catch (...) {
        qDebug() << "Error: RivDataFile::on_pushButtonRivDataFile_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check Log_Error_Message
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RivDataFile::Log_Warning_Message(QString message)
{
    try {
        LogsString.append(tr("<span style=\"color:#FF0000\">Warning: ") + message + " </span>")+tr("<br>");
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

        if(redirect_debug_messages_to_log)
        {
            ((PIHMgisDialog*)this->parent())->Log_Message(tr("<span style=\"color:#000000\"> ") + message + " </span>" + tr("<br>"));
        }

    } catch (...) {
        qDebug() << "Error: Log_Error_Message is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check Log_Error_Message
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RivDataFile::Log_Error_Message(QString message)
{
    try {
        LogsString.append(tr("<span style=\"color:#FF0000\">Error: ") + message + " </span>" +tr("<br>"));
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

        if(redirect_debug_messages_to_log)
        {
            ((PIHMgisDialog*)this->parent())->Log_Message(tr("<span style=\"color:#FF0000\">Error: ") + message + " </span>" + tr("<br>"));
        }

    } catch (...) {
        qDebug() << "Error: Log_Error_Message is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check Log_Error_Message
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RivDataFile::Log_Message(QString message)
{
    try {
        LogsString.append(tr("<span style=\"color:#000000\"> ") + message + " </span>" + tr("<br>"));
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

        if(redirect_debug_messages_to_log)
        {
            ((PIHMgisDialog*)this->parent())->Log_Message(tr("<span style=\"color:#000000\"> ") + message + " </span>" + tr("<br>"));
        }

    } catch (...) {
        qDebug() << "Error: Log_Message is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Run Button Clicked Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RivDataFile::on_pushButtonRun_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start RivDataFile::on_pushButtonRun_clicked()";

    try {

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Clear Log
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Clear_Log();

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check inputs
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QString input_Element_filename = ui->lineEditElementFile->text();
        QString input_Node_filename = ui->lineEditNodeFile->text();
        QString input_Neighbour_filename = ui->lineEditNeighbourFile->text();
        QString input_River_filename = ui->lineEditRiverFile->text();
        QString BoundaryCondition;

        if ( ui->radioButtonDirichlet->isChecked() )        BoundaryCondition = QString("-1");
        if ( ui->radioButtonNeumann->isChecked() )          BoundaryCondition = QString("-2");
        if ( ui->radioButtonZeroDepth->isChecked() )        BoundaryCondition = QString("-3");
        if ( ui->radioButtonCriticalDepth->isChecked() )    BoundaryCondition = QString("-4");

        bool checked_element = Check_Element_Input(input_Element_filename);
        if(!checked_element)
        {
            Log_Error_Message("Element (.1.ele) Input File Missing </span>");
            return;
        }

        bool checked_node = Check_Node_Input(input_Node_filename);
        if(!checked_node)
        {
            Log_Error_Message("Node (.1.node) Input File Missing </span>");
            return;
        }

        bool checked_neighbour = Check_Neighbor_Input(input_Neighbour_filename);
        if(!checked_neighbour)
        {
            Log_Error_Message("Neighbor (.1.Neigh) Input File Missing </span>");
            return;
        }

        bool checked_river = Check_RiverShape_Input(input_River_filename);
        if(!checked_river)
        {
            Log_Error_Message("River (*.shp) Input File Missing </span>");
            return;
        }
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check Outputs
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QString output_RivData_filename = ui->lineEditRivDataFile->text();

        bool output_check = Check_RiverData_Output(output_RivData_filename, true);
        if(output_check)
        {
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check file access
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if ( ! CheckFileAccess(input_Element_filename, "ReadOnly") )
        {
            Log_Error_Message("ERROR: No Read Access ... </span>" + input_Element_filename  );
            return;
        }
        if ( ! CheckFileAccess(input_Node_filename, "ReadOnly") )
        {
            Log_Error_Message("ERROR: No Read Access ... </span>" + input_Node_filename  );
            return;
        }
        if ( ! CheckFileAccess(input_Neighbour_filename, "ReadOnly") )
        {
            Log_Error_Message("ERROR: No Read Access ... </span>" + input_Neighbour_filename  );
            return;
        }
        if ( ! CheckFileAccess(input_River_filename, "ReadOnly") )
        {
            Log_Error_Message("ERROR: No Read Access ... </span>" + input_River_filename  );
            return;
        }
        if ( ! CheckFileAccess(output_RivData_filename, "WriteOnly") )
        {
            Log_Error_Message("ERROR: No Write Access ... </span>" + output_RivData_filename  );
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Running Riv Data File
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        Log_Message("Running Riv Data File ... <br>");

        QString RiverShpFileName, RiverDbfFileName, xRiverShpFileName, xRiverDbfFileName;

        RiverShpFileName = input_River_filename;
        RiverDbfFileName = RiverShpFileName;
        RiverDbfFileName = RiverDbfFileName.replace( QString(".shp"), QString(".dbf") );

        xRiverShpFileName = RiverShpFileName;
        xRiverShpFileName = xRiverShpFileName.replace( QString(".shp"), QString("_riv.shp") );
        xRiverDbfFileName = xRiverShpFileName;
        xRiverDbfFileName = xRiverDbfFileName.replace( QString(".shp"), QString(".dbf") );

        int ErrorRiv = riv_data_file( input_Element_filename, input_Node_filename, input_Neighbour_filename,
                                      RiverShpFileName, RiverDbfFileName,
                                      xRiverShpFileName, xRiverDbfFileName,
                                      BoundaryCondition,
                                      output_RivData_filename
                                      );

        if(ErrorRiv == -9000) //This means the temp file already exists
        {
            QString TempDbfFileName = user_pihmgis_root_folder + user_pihmgis_project_folder + riv_temp_fname;
            QMessageBox::information(this, tr("User must correct"), tr("A temporary file already exists. ""The file was *NOT* removed as the file maybe in use."));
            return;
        }

        if( ErrorRiv != 0 )
        {
            Log_Error_Message(tr("<span style=\"color:#FF0000\">ERROR: Riv Data File Processing Failed ... </span>")+tr("<br>"));
            Log_Error_Message(tr("<span style=\"color:#FF0000\">RETURN CODE RIV: ... </span>")+QString::number(ErrorRiv)+tr("<br>"));
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update Project file
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QStringList ProjectIOStringList;

        ProjectIOStringList << "RivDataFile" << input_Element_filename << input_Node_filename << input_Neighbour_filename << input_River_filename << BoundaryCondition << output_RivData_filename;
        WriteModuleLine(filename_open_project, ProjectIOStringList);
        ProjectIOStringList.clear();

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update Message box
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Clear_Log();

        Log_Message(tr("<br><b>Riv Data File Processing Complete.</b>")+tr("<br>"));

        ui->pushButtonRun->setDefault(false);
        ui->pushButtonClose->setDefault(true);
        ui->pushButtonClose->setFocus();


    } catch (...) {
        qDebug() << "Error: RivDataFile::on_pushButtonRun_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Close button event
// TODO, Decide on keeping button next highlights or not
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RivDataFile::on_pushButtonClose_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start RivDataFile::on_pushButtonClose_clicked()";

    try {
        //QStringList default_params; default_params << "WORKFLOW5" << "SOIL";
        //QMetaObject::invokeMethod(parent(),"set_defaults",Q_ARG(QStringList,default_params));
        close();
    } catch (...) {
        qDebug() << "Error: RivDataFile::on_pushButtonClose_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Help button event
// TODO, Need cataract server back online
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RivDataFile::on_pushButtonHelp_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start RivDataFile::on_pushButtonHelp_clicked()";

    try {
        //        LogsString = tr("");
        //        if ( ! QDesktopServices::openUrl(QUrl("http://cataract.cee.psu.edu/PIHM/index.php/PIHMgis_3.0#riv_Data_File")) )
        //            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Load HTTP Link ... </span>")+tr("<br>"));
        //        ui->textBrowserLogs->setHtml(LogsString);
        //        ui->textBrowserLogs->repaint();
    } catch (...) {
        qDebug() << "Error: RivDataFile::on_pushButtonHelp_clicked() is returning w/o checking";
    }
}
