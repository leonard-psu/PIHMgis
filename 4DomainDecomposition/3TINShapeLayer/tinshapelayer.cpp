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

        if(  fileExists(file) )
        {
            ui->lineEditElementFile->setStyleSheet("color: black;");
            ui->lineEditElementFile->setText(file);
            result = true;
        }
        else
        {
            ui->lineEditElementFile->setStyleSheet("color: rgb(180, 0, 0);");
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
bool TINShapeLayer::Check_Node_Input(QString file){

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
            ui->lineEditNodeFile->setStyleSheet("color: rgb(180, 0, 0);");
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
// Helper Function to assist if CatchmentPolygon OUTPUT file exists (returns true) or does not (returns false)
// Will color red and warning if exists with color_and_message_if_exists=true
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool TINShapeLayer::Check_TinShape_Output(QString file, bool color_and_message_if_exists){

    if(print_debug_messages)
        qDebug() << "INFO: Check_TinShape_Output()";

    bool result = false;

    try {

        if(  fileExists(file) )
        {
            if(color_and_message_if_exists)
            {
                LogsString.append(tr("<span style=\"color:#FF0000\">Warning: Tinshape output already exists: </span>") + file +tr(" You may need to delete these files.<br>"));
                ui->textBrowserLogs->setHtml(LogsString);
                ui->textBrowserLogs->repaint();
                ui->lineEditTINFile->setStyleSheet("color: rgb(180, 0, 0);");
            }

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
        if ( EleFileName.length() > 0)
        {
            Check_Element_Input(EleFileName);

            pushButtonSetFocus();
        }

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
        if ( NodeFileName != nullptr)
        {
            Check_Node_Input(NodeFileName);

            pushButtonSetFocus();
        }

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

        if ( TINShapeFileName != nullptr)
        {
            QString tempString = TINShapeFileName;
            if( ! (tempString.toLower()).endsWith(".shp") )
            {
                tempString.append(".shp");
                TINShapeFileName = tempString;
            }

            Check_TinShape_Output(TINShapeFileName, true);

            pushButtonSetFocus();
        }


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
        QString element_input_filename = ui->lineEditElementFile->text();
        QString node_input_filename = ui->lineEditNodeFile->text();
        QString tinshape_input_filename = ui->lineEditTINFile->text();


        bool ElementCheck = Check_Element_Input(element_input_filename);
        if(!ElementCheck)
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Element (.1.ele) Input File Missing </span>")+tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
            return;
        }
        bool NodeCheck = Check_Node_Input(node_input_filename);
        if(!NodeCheck)
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Node (.1.node) Input File Missing </span>")+tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Does output already exist?
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool TinShapeCheck = Check_TinShape_Output(tinshape_input_filename, false);
        if(TinShapeCheck)
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: CatchmentPolygon TIN Shape already exists </span>")+tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check file access
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if ( ! CheckFileAccess(element_input_filename, "ReadOnly") )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Read Access ... </span>") + element_input_filename + tr("<br>"));
            return;
        }

        if ( ! CheckFileAccess(node_input_filename, "ReadOnly") )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Read Access ... </span>") + node_input_filename + tr("<br>"));
            return;
        }

        if ( ! CheckFileAccess(tinshape_input_filename, "WriteOnly") )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Write Access ... </span>") + tinshape_input_filename + tr("<br>"));
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Running Catchment Polygon
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        LogsString.append("Running TIN Shape Layer ... <br>");
        LogsString.append(element_input_filename + "<br>");
        LogsString.append(node_input_filename + "<br>");


        QString TINShpFileName, TINDbfFileName;
        TINShpFileName = tinshape_input_filename;
        TINDbfFileName = TINShpFileName;
        TINDbfFileName.replace( QString(".shp"), QString(".dbf") );

        LogsString.append(TINDbfFileName + "<br>");
        LogsString.append(TINDbfFileName + "<br>");

        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();


        int ErrorTIN = tin_shape((char *)qPrintable(element_input_filename), (char *)qPrintable(node_input_filename), (char *)qPrintable(TINShpFileName), (char *)qPrintable(TINDbfFileName), &LogsString);
        if( ErrorTIN != 0 )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: TIN Shape Layer Processing Failed ... </span>")+tr("<br>"));
            LogsString.append(tr("<span style=\"color:#FF0000\">RETURN CODE: ... </span>")+QString::number(ErrorTIN)+tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check output filenames
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        TinShapeCheck = Check_TinShape_Output(tinshape_input_filename, false);
        if(!TinShapeCheck)
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">Error: TinShape failed, file does not exist: </span>") + TinShapeCheck +tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
            return;
        }

        qint64 size = file_Size(tinshape_input_filename);
        if( size < 1)
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">Error: CatchmentPolygon failed, invalid file size: </span>") + size +tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
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
        //Clear_Log();

        LogsString.append(tr("<br><b>TIN Shape Layer Processing Completed.</b>")+tr("<br>"));
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

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
