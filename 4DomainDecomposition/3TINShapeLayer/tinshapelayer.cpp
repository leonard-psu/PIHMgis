#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>

#include "tinshapelayer.h"
#include "ui_tinshapelayer.h"

#include "0LibsIO/IOProjectFile.h"
#include "0LibsVector/tin_shape.h"
#include "globals.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TINShapeLayer Constructor
// Parent is Main Window, filename is the open project text file used to store project details
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TINShapeLayer::TINShapeLayer(QWidget *parent, QString filename) :
    QDialog(parent),
    ui(new Ui::TINShapeLayer)
{

    if(print_debug_messages)
        qDebug() << "INFO: Start TINShapeLayer";

    try {
        ui->setupUi(this);

        filename_open_project = filename;
        bool found_file = false;

        QFile ProjectFile(filename_open_project);
        if ( ProjectFile.open(QIODevice::ReadOnly | QIODevice::Text) == false)
        {
            Log_Error_Message("Unable to Open File: " + filename_open_project );
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
        qDebug() << "Error: TINShapeLayer is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TINShapeLayer Deconstructor
// Todo: Check for memory leaks
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TINShapeLayer::~TINShapeLayer()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ~TINShapeLayer";

    try {
        delete ui;
    } catch (...) {
        qDebug() << "Error: ~TINShapeLayer is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Load_Project_Settings
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool TINShapeLayer::Load_Project_Settings()
{
    try {

        QStringList ModuleStringList = ReadModuleLine(filename_open_project,tr("DelaunayTriangulation"));
        if ( ModuleStringList.length() > 0  )
        {
            QString TempFileName = ModuleStringList.at(1);
            TempFileName.replace( QString(".poly"), QString(".1.ele") );
            Check_Element_Input( TempFileName );

            TempFileName.replace( QString(".1.ele"), QString(".1.node") );
            bool valid = Check_Node_Input( TempFileName );

            if(valid)
            {
                TempFileName.replace( QString(".1.node"), QString("") );

                if ( ModuleStringList.at(2).length() > 0 )
                {
                    TempFileName.append( QString("_q") + ModuleStringList.at(2) );
                }

                if ( ModuleStringList.at(3).length() > 0 )
                {
                    TempFileName.append( QString("_a") + ModuleStringList.at(3) );
                }

                //Will overwrite previous merge file if I don't add _tin
                TempFileName.append("_tin.shp");
                Check_TinShape_Output(TempFileName,true);

            }
        }

        ModuleStringList = ReadModuleLine(filename_open_project,tr("TINShapeLayer"));

        if ( ModuleStringList.length() > 0 )
        {
            QString ElementFileName = ModuleStringList.at(1);
            QString NodeFileName = ModuleStringList.at(2);
            QString TINFileName = ModuleStringList.at(3);

            Check_Element_Input( ElementFileName );
            Check_Node_Input( NodeFileName );
            Check_TinShape_Output(TINFileName,true);
        }

    } catch (...) {
        qDebug() << "Error: TINShapeLayer::Load_Project_Settings is returning w/o checking";
        return false;
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Check Element File exists (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool TINShapeLayer::Check_Element_Input(QString file){

    if(print_debug_messages)
        qDebug() << "INFO: Check_Element_Input()";

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

            Log_Message("Warning: Element input file missing: " + file );

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
bool TINShapeLayer::Check_Node_Input(QString file){

    if(print_debug_messages)
        qDebug() << "INFO: Check_Node_Input()";

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

            Log_Message("Warning: Node input file missing: " + file );

            result = false;
        }

    } catch (...) {
        qDebug() << "Error: Check_Node_Input is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to assist if CatchmentPolygon OUTPUT file exists (returns true) or does not (returns false)
// Will color red and warning if exists with color_and_message_if_exists=true
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool TINShapeLayer::Check_TinShape_Output(QString file, bool color_and_message_if_exists){

    if(print_debug_messages)
        qDebug() << "INFO: Check_TinShape_Output()";

    bool result = false;

    try {

        if( fileExists(file) )
        {
            if(color_and_message_if_exists)
            {
                Log_Message("Warning: Tinshape output already exists: " + file + " You may need to delete these files.");
            }

            ui->lineEditTINFile->setStyleSheet("color: red;");
            ui->lineEditTINFile->setText(file);
            result = true;
        }
        else
        {
            ui->lineEditTINFile->setStyleSheet("color: black;");
            ui->lineEditTINFile->setText(file);

            result = false;
        }

    } catch (...) {
        qDebug() << "Error: Check_TinShape_Output is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to clear message log
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TINShapeLayer::Clear_Log()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start TINShapeLayer::Clear_Log()";

    try {

        LogsString = tr("");
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

    } catch (...) {
        qDebug() << "Error: TINShapeLayer::Clear_Log() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check Log_Error_Message
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TINShapeLayer::Log_Error_Message(QString message)
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
void TINShapeLayer::Log_Message(QString message)
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
void TINShapeLayer::pushButtonSetFocus()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start TINShapeLayer::pushButtonSetFocus()";

    try {
        ui->pushButtonElementFile->setDefault(false);
        ui->pushButtonNodeFile->setDefault(false);
        ui->pushButtonTINFile->setDefault(false);
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

        if (ui->lineEditTINFile->text() == nullptr)
        {
            ui->pushButtonTINFile->setDefault(true);
            ui->pushButtonTINFile->setFocus();
            return;
        }

        ui->pushButtonRun->setDefault(true);
        ui->pushButtonRun->setFocus();
    } catch (...) {
        qDebug() << "Error:  TINShapeLayer::pushButtonSetFocus() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button Element Clicked Event (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TINShapeLayer::on_pushButtonElementFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start TINShapeLayer::on_pushButtonElementFile_clicked()";

    try {

        Clear_Log();

        QString EleFileName = QFileDialog::getOpenFileName(this, "Ele (.1.ele) File", user_pihmgis_root_folder +tr("/3DomainDecomposition"), "Ele File(*.ele)");
        if ( EleFileName.isNull() == false)
        {
            if( EleFileName.isEmpty() == false)
            {
                Check_Element_Input(EleFileName);

                pushButtonSetFocus();
            }
        }
        //else do nothing

    } catch (...) {
        qDebug() << "Error:  TINShapeLayer::on_pushButtonElementFile_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button Node Clicked Event (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TINShapeLayer::on_pushButtonNodeFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start TINShapeLayer::on_pushButtonNodeFile_clicked()";

    try {

        QString NodeFileName = QFileDialog::getOpenFileName(this, "Node (.1.node) File", user_pihmgis_root_folder+tr("/3DomainDecomposition"), "Node File(*.node)");
        if ( NodeFileName.isNull() == false)
        {
            if( NodeFileName.isEmpty() == false)
            {
                Check_Node_Input(NodeFileName);

                pushButtonSetFocus();
            }
        }
        //else do nothing

    } catch (...) {
        qDebug() << "Error:  TINShapeLayer::on_pushButtonNodeFile_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button TIN Clicked Event (OUTPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TINShapeLayer::on_pushButtonTINFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start TINShapeLayer::on_pushButtonTINFile_clicked()";

    try {

        Clear_Log();

        QString TINShapeFileName = QFileDialog::getSaveFileName(this, "Choose TIN Shape File Name", user_pihmgis_root_folder +"/3DomainDecomposition","Shape File(*.shp)");

        if ( TINShapeFileName.isNull() == false)
        {
            if( TINShapeFileName.isEmpty() == false)
            {
                QString tempString = TINShapeFileName;
                if( (tempString.toLower()).endsWith(".shp") == false)
                {
                    tempString.append(".shp");
                    TINShapeFileName = tempString;
                }

                Check_TinShape_Output(TINShapeFileName, true);

                pushButtonSetFocus();
            }
        }
        //else do nothing


    } catch (...) {
        qDebug() << "Error:  TINShapeLayer::on_pushButtonTINFile_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Run Button Clicked Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TINShapeLayer::on_pushButtonRun_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start TINShapeLayer::on_pushButtonRun_clicked()";

    try {

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Clear Log
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Clear_Log();

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check inputs
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QString element_input_filename  = ui->lineEditElementFile->text();
        QString node_input_filename     = ui->lineEditNodeFile->text();
        QString tinshape_input_filename = ui->lineEditTINFile->text();

        bool ElementCheck = Check_Element_Input(element_input_filename);
        if(ElementCheck == false)
        {
            Log_Error_Message("Element (.1.ele) Input File Missing ");
            return;
        }

        bool NodeCheck = Check_Node_Input(node_input_filename);
        if(NodeCheck == false)
        {
            Log_Error_Message("Node (.1.node) Input File Missing ");
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Does output already exist?
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool TinShapeCheck = Check_TinShape_Output(tinshape_input_filename, false);
        if(TinShapeCheck)
        {
            Log_Error_Message("CatchmentPolygon TIN Shape already exists ");
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check file access
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if ( CheckFileAccess(element_input_filename, "ReadOnly") == false)
        {
            Log_Error_Message("No Read Access to ... " + element_input_filename );
            return;
        }

        if ( CheckFileAccess(node_input_filename, "ReadOnly") == false)
        {
            Log_Error_Message("No Read Access to ... " + node_input_filename );
            return;
        }

        if ( CheckFileAccess(tinshape_input_filename, "WriteOnly") == false)
        {
            Log_Error_Message("No Write Access to ... " + tinshape_input_filename);
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Running Catchment Polygon
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Log_Message("Running TIN Shape Layer ... ");
        Log_Message(element_input_filename );
        Log_Message(node_input_filename);

        QString TINShpFileName, TINDbfFileName;
        TINShpFileName = tinshape_input_filename;
        TINDbfFileName = TINShpFileName;
        TINDbfFileName.replace( QString(".shp"), QString(".dbf") );

        Log_Message(TINDbfFileName);
        Log_Message(TINDbfFileName);

        int ErrorTIN = tin_shape(element_input_filename, node_input_filename,TINShpFileName, TINDbfFileName);
        if( ErrorTIN != 0 )
        {
            Log_Error_Message("TIN Shape Layer Processing Failed ... " );
            Log_Error_Message("RETURN CODE: ... " + QString::number(ErrorTIN) );
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check output filenames
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TinShapeCheck = Check_TinShape_Output(tinshape_input_filename, false);
        if(TinShapeCheck == false)
        {
            Log_Error_Message("TinShape failed, file does not exist: " + tinshape_input_filename );
            return;
        }

        qint64 size = file_Size(tinshape_input_filename);
        if( size < 1)
        {
            Log_Error_Message("CatchmentPolygon failed, invalid file size: " + QString::number(size) );
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update Project file
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QStringList ProjectIOStringList;
        ProjectIOStringList << "TINShapeLayer" << ui->lineEditElementFile->text() << ui->lineEditNodeFile->text() << ui->lineEditTINFile->text();
        WriteModuleLine(filename_open_project, ProjectIOStringList);
        ProjectIOStringList.clear();

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update Message box
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Log_Message("TIN Shape Layer Processing Completed.");

        ui->pushButtonRun->setDefault(false);
        ui->pushButtonClose->setDefault(true);
        ui->pushButtonClose->setFocus();

    } catch (...) {
        qDebug() << "Error:  TINShapeLayer::on_pushButtonRun_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Close button event
// TODO, Decide on keeping button next highlights or not
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TINShapeLayer::on_pushButtonClose_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start TINShapeLayer::on_pushButtonClose_clicked()";

    try {
        //QStringList default_params; default_params << "WORKFLOW5";// << "WORKFLOW8";
        // QMetaObject::invokeMethod(parent(),"set_defaults",Q_ARG(QStringList,default_params));
        close();
    } catch (...) {
        qDebug() << "Error:  TINShapeLayer::on_pushButtonClose_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Help button event
// TODO, Need cataract server back online
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TINShapeLayer::on_pushButtonHelp_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start TINShapeLayer::on_pushButtonHelp_clicked()";

    try {
        //        LogsString = tr("");
        //        if ( ! QDesktopServices::openUrl(QUrl("http://cataract.cee.psu.edu/PIHM/index.php/PIHMgis_3.0#TIN_Shape_Layer")) )
        //            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Load HTTP Link ... </span>")+tr("<br>"));
        //        ui->textBrowserLogs->setHtml(LogsString);
        //        ui->textBrowserLogs->repaint();
    } catch (...) {
        qDebug() << "Error:  TINShapeLayer::on_pushButtonHelp_clicked() is returning w/o checking";
    }
}
