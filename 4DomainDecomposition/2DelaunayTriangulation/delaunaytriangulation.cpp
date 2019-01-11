#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>

#include "delaunaytriangulation.h"
#include "ui_delaunaytriangulation.h"

#include "0LibsIO/IOProjectFile.h"
//#include "0LibsOther/triangle_shewchuk.h"
//Triangle software (compiled) must be provided by user.
#include "globals.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DelaunayTriangulation Constructor
// Parent is Main Window, filename is the open project text file used to store project details
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DelaunayTriangulation::DelaunayTriangulation(QWidget *parent, QString filename) :
    QDialog(parent),
    ui(new Ui::DelaunayTriangulation)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start DelaunayTriangulation";

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

        QIntValidator* Angle_validator = new QIntValidator(1,34,this);
        QIntValidator* Area_validator = new QIntValidator(1,999999999,this);

        ui->lineEditAngle->setValidator(Angle_validator);
        ui->lineEditArea->setValidator(Area_validator);

        if(found_file)
        {
            Load_Project_Settings();
        }

        pushButtonSetFocus();

    } catch (...) {
        qDebug() << "Error: DelaunayTriangulation is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DelaunayTriangulation Deconstructor
// Todo: Check for memory leaks
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DelaunayTriangulation::~DelaunayTriangulation()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ~DelaunayTriangulation";

    try {
        delete ui;
    } catch (...) {
        qDebug() << "Error: ~DelaunayTriangulation is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Load_Project_Settings
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool DelaunayTriangulation::Load_Project_Settings()
{
    try {

        ui->lineEditAngle->blockSignals(true);
        ui->lineEditArea->blockSignals(true);
        ui->lineEditOthers->blockSignals(true);

        ui->checkBoxAngle->setChecked(false);
        ui->checkBoxArea->setChecked(false);
        ui->checkBoxOthers->setChecked(false);

        ui->lineEditAngle->setDisabled(true);
        ui->lineEditArea->setDisabled(true);
        ui->lineEditOthers->setDisabled(true);

        QStringList ModuleStringList;

        ModuleStringList = ReadModuleLine(filename_open_project,tr("ReadTopology"));
        if ( ModuleStringList.length() > 0  )
        {
            QString filename = ModuleStringList.at(2);
            bool PSLG_check = Check_PSLG_Input(filename);
        }

        ModuleStringList = ReadModuleLine(filename_open_project,tr("DelaunayTriangulation"));
        if ( ModuleStringList.length() > 0 )
        {
            QString filename = ModuleStringList.at(1);
            QString Angle = ModuleStringList.at(2);
            QString Area = ModuleStringList.at(3);
            QString Others = ModuleStringList.at(4);

            bool PSLG_check = Check_PSLG_Input(filename);
            bool Angle_check = Check_Angle(Angle, false);
            bool Area_check = Check_Area(Area, false);
            bool Others_check = Check_Others(Others, false);

            QString output_filename = filename;
            output_filename.replace( QString(".poly"), QString(".1.poly") );
            Check_TIN_Output(output_filename,true);
            QString output_filename2 = filename;
            output_filename2.replace( QString(".poly"), QString(".1.ele") );
            Check_TIN_Output(output_filename2,true);

        }

        ui->lineEditAngle->blockSignals(false);
        ui->lineEditArea->blockSignals(false);
        ui->lineEditOthers->blockSignals(false);

        pushButtonSetFocus();

    } catch (...) {
        qDebug() << "Error: PolylineToLines::Load_Project_Settings is returning w/o checking";
        return false;
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to clear message log
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DelaunayTriangulation::Clear_Log()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start DelaunayTriangulation::Clear_Log()";

    try {

        LogsString = tr("");
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

    } catch (...) {
        qDebug() << "Error: DelaunayTriangulation::Clear_Log() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check Log_Error_Message
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DelaunayTriangulation::Log_Error_Message(QString message)
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
void DelaunayTriangulation::Log_Message(QString message)
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
// Helper function for PSLG (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool DelaunayTriangulation::Check_PSLG_Input(QString file)
{
    if(print_debug_messages)
        qDebug() << "INFO: Check_PSLG_Input()";

    bool result = false;

    try {

        if( fileExists(file) )
        {
            ui->lineEditPSLG->setStyleSheet("color: black;");
            ui->lineEditPSLG->setText(file);
            result = true;
        }
        else
        {
            ui->lineEditPSLG->setStyleSheet("color: red;");
            ui->lineEditPSLG->setText(file);

            Log_Message("Warning: Poly input does not exist " + file );
            result = false;
        }

    } catch (...) {
        qDebug() << "Error: Check_PSLG_Input is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper function to check Angle (INPUT)
//TODO Add logic to check values
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool DelaunayTriangulation::Check_Angle(QString value, bool message){
    if(print_debug_messages)
        qDebug() << "INFO: Check_Angle()";

    bool result = false;

    try {

        if(value.length() > 0 )
        {
            //Using Qt Validator to check value
            ui->checkBoxAngle->setChecked(true);
            ui->lineEditAngle->setText(value);
            ui->lineEditAngle->setStyleSheet("color: black;");
            result = true;
        }
        else
        {
            if(message)
            {
                Log_Message("WARNING: Invalid Angle value. ");
            }
            result = false;
        }

    } catch (...) {
        qDebug() << "Error: Check_Angle is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper function to check Area (INPUT)
//TODO Add logic to check values
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool DelaunayTriangulation::Check_Area(QString value, bool message){

    if(print_debug_messages)
        qDebug() << "INFO: Check_Area()";

    bool result = false;

    try {

        if(value.length() > 0 )
        {
            //Using Qt Validator to check value
            ui->checkBoxArea->setChecked(true);
            ui->lineEditArea->setText(value);
            ui->lineEditArea->setStyleSheet("color: black;");
            result = true;
        }
        else
        {
            if(message)
            {
                Log_Message("WARNING: Invalid Area value. ");
            }
            result = false;
        }

    } catch (...) {
        qDebug() << "Error: Check_Area is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper function to check Others (INPUT)
//TODO Add logic to check values
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool DelaunayTriangulation::Check_Others(QString value, bool message)
{
    if(print_debug_messages)
        qDebug() << "INFO: Check_Others()";

    bool result = false;

    try {

        if(value.length() > 0 )
        {
            //Using Qt Validator to check value
            ui->checkBoxOthers->setChecked(true);
            ui->lineEditOthers->setText(value);
            ui->lineEditOthers->setStyleSheet("color: black;");
            result = true;
        }
        else
        {
            if(message)
            {
                Log_Message("WARNING: Invalid Others value. ");
            }
            result = false;
        }

    } catch (...) {
        qDebug() << "Error: Check_Others is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to focus button selection (needed for users w/o mouse)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DelaunayTriangulation::pushButtonSetFocus()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start DelaunayTriangulation::pushButtonSetFocus()";

    try {
        ui->pushButtonPSLG->setDefault(false);
        ui->pushButtonRun->setDefault(false);

        if (ui->lineEditPSLG->text() == nullptr)
        {
            ui->pushButtonPSLG->setDefault(true);
            ui->pushButtonPSLG->setFocus();
            return;
        }

        ui->pushButtonRun->setDefault(true);
        ui->pushButtonRun->setFocus();

    } catch (...) {
        qDebug() << "Error: DelaunayTriangulation::pushButtonSetFocus() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button Clicked Event for PSLG (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DelaunayTriangulation::on_pushButtonPSLG_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start DelaunayTriangulation::on_pushButtonPSLG_clicked()";

    try {

        Clear_Log();

        QString PSLGFileName = QFileDialog::getOpenFileName(this, "PSLG (.poly) File", user_pihmgis_root_folder + tr("/3DomainDecomposition"), "PSLG File(*.poly *.POLY)");

        if ( PSLGFileName.isNull() == false)
        {
            if( PSLGFileName.isEmpty() == false)
            {
                Check_PSLG_Input(PSLGFileName);

                pushButtonSetFocus();
            }
        }
        //else do nothing

    } catch (...) {
        qDebug() << "Error: DelaunayTriangulation::on_pushButtonPSLG_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Checkbox Clicked Event for Angle (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DelaunayTriangulation::on_checkBoxAngle_toggled(bool checked)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start DelaunayTriangulation::on_checkBoxAngle_toggled()";

    try {

        if ( checked )
        {
            ui->lineEditAngle->setDisabled(false);
        }
        else
        {
            ui->lineEditAngle->setDisabled(true);
        }

    } catch (...) {
        qDebug() << "Error: DelaunayTriangulation::on_checkBoxAngle_toggled() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Checkbox Clicked Event for Area (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DelaunayTriangulation::on_checkBoxArea_toggled(bool checked)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start DelaunayTriangulation::on_checkBoxArea_toggled()";

    try {

        if ( checked )
        {
            ui->lineEditArea->setDisabled(false);
        }
        else
        {
            ui->lineEditArea->setDisabled(true);
        }

    } catch (...) {
        qDebug() << "Error: DelaunayTriangulation::on_checkBoxArea_toggled() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Checkbox Clicked Event for Others (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DelaunayTriangulation::on_checkBoxOthers_toggled(bool checked)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start DelaunayTriangulation::on_checkBoxOthers_toggled()";

    try {

        if ( checked )
        {
            ui->lineEditOthers->setDisabled(false);
        }
        else
        {
            ui->lineEditOthers->setDisabled(true);
        }

    } catch (...) {
        qDebug() << "Error: DelaunayTriangulation::on_checkBoxOthers_toggled() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Text Changed Event for Angle (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DelaunayTriangulation::on_lineEditAngle_textChanged(const QString &arg1)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start DelaunayTriangulation::on_lineEditAngle_textChanged()";

    try {

        QString value = ui->lineEditAngle->text();
        Check_Angle(value, true);

    } catch (...) {
        qDebug() << "Error: DelaunayTriangulation::on_lineEditAngle_textChanged() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Text Changed Event for Area (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DelaunayTriangulation::on_lineEditArea_textChanged(const QString &arg1)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start DelaunayTriangulation::on_lineEditArea_textChanged()";

    try {

        QString value = ui->lineEditArea->text();
        Check_Area(value, true);

    } catch (...) {
        qDebug() << "Error: DelaunayTriangulation::on_lineEditArea_textChanged() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Text Changed Event for Others (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DelaunayTriangulation::on_lineEditOthers_textChanged(const QString &arg1)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start DelaunayTriangulation::on_lineEditOthers_textChanged()";

    try {

        QString value = ui->lineEditOthers->text();
        Check_Others(value, true);

    } catch (...) {
        qDebug() << "Error: DelaunayTriangulation::on_lineEditOthers_textChanged() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to assist if input file exists (returns true) or does not (returns false)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool DelaunayTriangulation::Check_File_Valid(QString file)
{
    if(print_debug_messages)
        qDebug() << "INFO: Check_File_Valid()";

    bool result = false;

    try {

        bool fileExists = QFileInfo::exists(file) && QFileInfo(file).isFile();
        return fileExists;

    } catch (...) {
        qDebug() << "Error: Check_File_Valid is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Run Button Clicked Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DelaunayTriangulation::on_pushButtonRun_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start DelaunayTriangulation::on_pushButtonRun_clicked()";

    try {

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Clear Log
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Clear_Log();

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check inputs
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QString PSLG_filename              = ui->lineEditPSLG->text();
        QString input_angle                = ui->lineEditAngle->text();
        QString input_area                 = ui->lineEditArea->text();
        QString input_others               = ui->lineEditOthers->text();
        QString filename_triangle_software = ui->lineEditFIND->text();

        bool TriangleCheck = Check_Triangle_Software_Input(filename_triangle_software);
        if(TriangleCheck == false)
        {
            Log_Error_Message("TRIANGLE Software Input File Missing ");
            return;
        }

        bool PSLGCheck = Check_PSLG_Input(PSLG_filename);
        if(PSLGCheck == false)
        {
            Log_Error_Message("PSLG Input File Missing ");
            return;
        }

        if( ui->checkBoxAngle->isChecked() )
        {
            bool angle_check = Check_Angle(input_angle, true);
            if(angle_check == false)
            {
                Log_Error_Message("Missing Angle Quality Constraint ... ");
                return;
            }
        }

        if( ui->checkBoxArea->isChecked())
        {
            bool area_check = Check_Area(input_area, true);
            if(area_check == false)
            {
                Log_Error_Message("Missing Area Quality Constraint ... ");
                return;
            }
        }

        if( ui->checkBoxOthers->isChecked())
        {
            bool area_check = Check_Others(input_others, true);
            if(area_check == false)
            {
                Log_Error_Message("Missing Other Options ... ");
                return;
            }
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Does output already exist?
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QString output_filename = PSLG_filename;
        output_filename.replace( QString(".poly"), QString(".1.poly") );
        QString output_filename2 = PSLG_filename;
        output_filename2.replace( QString(".poly"), QString(".1.ele") );

        bool file_exists = Check_File_Valid(output_filename);
        if(file_exists)
        {
            Log_Error_Message("PSLG Output File Exists " + output_filename );
            return;
        }

        file_exists = Check_File_Valid(output_filename2);
        if(file_exists)
        {
            Log_Error_Message("PSLG Output File Exists " + output_filename2 );
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check file access
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //        if ( ! CheckFileAccess(PSLG_filename, "ReadOnly") )
        //        {
        //            LogsString.append(tr("<span style=\"color:#FF0000\">Error: No Read Access to ... </span>") + PSLG_filename + tr("<br>"));
        //            return;
        //        }
        //PROBLEM CREATES FILE HERE
        //        if ( ! CheckFileAccess(output_filename, "WriteOnly") )
        //        {
        //            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: No Write Access ... </span>") + output_filename + tr("<br>"));
        //            return;
        //        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Running TRIANGLE
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        Log_Message("Running Delaunay Triangulation ... ");

        QString ExecString, OptsString, NameString;
        ExecString = "TRIANGLE";
        OptsString = "-nV";

        if( ui->checkBoxAngle->isChecked() )
        {
            OptsString.append(tr("q")+ui->lineEditAngle->text());
        }

        if( ui->checkBoxArea->isChecked() )
        {
            OptsString.append(tr("a")+ui->lineEditArea->text());
        }

        if( ui->checkBoxOthers->isChecked() )
        {
            OptsString.append(ui->lineEditOthers->text());
        }

        NameString = PSLG_filename;

        QProcess Triangle_Process;
        QString command = filename_triangle_software + " " + OptsString + " " + NameString;

        Log_Message("Input: " + command);

        Triangle_Process.start(command);
        Triangle_Process.waitForFinished();
        int ErrorTri = Triangle_Process.exitCode();
        QString output(Triangle_Process.readAllStandardOutput());

        Log_Message("Output: " + output);

        if(ErrorTri != 0)
        {
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check output filenames
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        file_exists = Check_File_Valid(output_filename);
        if(file_exists == false)
        {
            Log_Error_Message("PSLG Output File not generated " + output_filename );
            return;
        }

        qint64 size = file_Size(output_filename);
        if( size < 1)
        {
            Log_Error_Message("PSLG Poly Output failed, invalid file size: " + QString::number(size) );
            return;
        }

        file_exists = Check_File_Valid(output_filename2);
        if(file_exists == false)
        {
            Log_Error_Message("PSLG Output File not generated  " + output_filename2 );
            return;
        }

        size = file_Size(output_filename2);
        if( size < 1)
        {
            Log_Error_Message("PSLG Ele Output failed, invalid file size: " + QString::number(size) );
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update Project file
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QStringList ProjectIOStringList;

        ProjectIOStringList << "DelaunayTriangulation" << PSLG_filename;

        if( ui->checkBoxAngle->isChecked() )
        {
            ProjectIOStringList << ui->lineEditAngle->text();
        }
        else
        {
            ProjectIOStringList << "";
        }

        if( ui->checkBoxArea->isChecked() )
        {
            ProjectIOStringList << ui->lineEditArea->text();
        }
        else
        {
            ProjectIOStringList << "";
        }

        if( ui->checkBoxOthers->isChecked() )
        {
            ProjectIOStringList << ui->lineEditOthers->text();
        }
        else
        {
            ProjectIOStringList << "";
        }

        WriteModuleLine(filename_open_project, ProjectIOStringList);
        ProjectIOStringList.clear();

        // READ THE NUMBER OF TRIANGLES FROM .1.ELE FILE AND PRINT ON THE LOG
        int NumTINs = -1;
        QString EleFileName = PSLG_filename;
        EleFileName.replace(QString(".poly"), QString(".1.ele"));

        QFile EleFile(EleFileName);
        bool opened = EleFile.open(QIODevice::ReadOnly | QIODevice::Text);
        if(opened == false)
        {
            Log_Error_Message("Failed to open " + EleFileName);
            return;
        }

        QTextStream EleFileTextStream(&EleFile);
        EleFileTextStream >> NumTINs;
        EleFile.close();

        Log_Message("Total Number of Triangular Elements: " + QString::number(NumTINs) );

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update Message box
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //Clear_Log();

        Log_Message("Delaunay Triangulation Processing Completed.");

        ui->pushButtonRun->setDefault(false);
        ui->pushButtonClose->setDefault(true);
        ui->pushButtonClose->setFocus();


    } catch (...) {
        qDebug() << "Error: DelaunayTriangulation::on_pushButtonRun_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Close button event
// TODO, Decide on keeping button next highlights or not
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DelaunayTriangulation::on_pushButtonClose_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start DelaunayTriangulation::on_pushButtonClose_clicked()";

    try {
        //QStringList default_params; default_params << "WORKFLOW4" << "TINSHP";
        //QMetaObject::invokeMethod(parent(),"set_defaults",Q_ARG(QStringList,default_params));
        close();
    } catch (...) {
        qDebug() << "Error: DelaunayTriangulation::on_pushButtonClose_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Help button event
// TODO, Need cataract server back online
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DelaunayTriangulation::on_pushButtonHelp_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start DelaunayTriangulation::on_pushButtonHelp_clicked()";

    try {
        //        LogsString = tr("");
        //        if ( ! QDesktopServices::openUrl(QUrl("http://cataract.cee.psu.edu/PIHM/index.php/PIHMgis_3.0#Triangulation")) )
        //            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Load HTTP Link ... </span>")+tr("<br>"));
        //        ui->textBrowserLogs->setHtml(LogsString);
        //        ui->textBrowserLogs->repaint();
    } catch (...) {
        qDebug() << "Error: DelaunayTriangulation::on_pushButtonHelp_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper function for TRIANGLE SOFTWARE (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool DelaunayTriangulation::Check_Triangle_Software_Input(QString file)
{
    if(print_debug_messages)
        qDebug() << "INFO: Check_Triangle_Software_Input()";

    bool result = false;

    try {

        if( fileExists(file) )
        {
            ui->lineEditFIND->setStyleSheet("color: black;");
            ui->lineEditFIND->setText(file);

            result = true;
        }
        else
        {
            ui->lineEditFIND->setStyleSheet("color: red;");
            ui->lineEditFIND->setText(file);

            result = false;
        }


    } catch (...) {
        qDebug() << "Error: Check_Triangle_Software_Input is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FIND button event used to specify path of TRIANGLE SOFTWARE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DelaunayTriangulation::on_pushButtonFIND_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start DelaunayTriangulation::on_pushButtonFIND_clicked()";

    try {

        Clear_Log();

        QString fileName = QFileDialog::getOpenFileName(this,
                                                        "Triangle.exe or Triangle ",
                                                        user_pihmgis_root_folder + tr("/Software"),
                                                        "All files (*.*) ;; Triangle File(*.exe)");
        if ( fileName.isNull() == false)
        {
            if( fileName.isEmpty() == false)
            {
                Check_Triangle_Software_Input(fileName);
                pushButtonSetFocus();
            }
        }
        //else do nothing

    } catch (...) {
        qDebug() << "Error: DelaunayTriangulation::on_pushButtonFIND_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Text Changed Event for TRIANGLE SOFTWARE (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DelaunayTriangulation::on_lineEditFIND_textChanged(const QString &arg1)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start DelaunayTriangulation::on_lineEditFIND_textChanged()";

    try {

        QString value = ui->lineEditFIND->text();
        Check_Triangle_Software_Input(value);

    } catch (...) {
        qDebug() << "Error: DelaunayTriangulation::on_lineEditFIND_textChanged() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to assist if CatchmentPolygon OUTPUT file exists (returns true) or does not (returns false)
// Will color red and warning if exists with color_and_message_if_exists=true
// NOTE only display message in window as Triangle software appends .1.ele and .1.node to filename input
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool DelaunayTriangulation::Check_TIN_Output(QString file, bool color_and_message_if_exists)
{
    if(print_debug_messages)
        qDebug() << "INFO: Check_TIN_Output()";

    bool result = false;

    try {

        if( fileExists(file) )
        {
            if(color_and_message_if_exists)
            {
                Log_Message("Warning: Output already exists: " + file + " You may need to delete these files.");
            }

            result = true;
        }
        else
        {
            result = false;
        }


    } catch (...) {
        qDebug() << "Error: Check_TIN_Output is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Text Changed Event for TRIANGLE SOFTWARE (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DelaunayTriangulation::on_pushButtonFIND_clicked(bool checked)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start DelaunayTriangulation::on_pushButtonFIND_clicked()";

    try {

        Clear_Log();

        QString fileName = QFileDialog::getOpenFileName(this,
                                                        "Triangle.exe or Triangle ",
                                                        user_pihmgis_root_folder + tr("/Software"),
                                                        "All files (*.*) ;; Triangle File(*.exe)");
        if ( fileName.isNull() == false)
        {
            if( fileName.isEmpty() == false)
            {
                Check_Triangle_Software_Input(fileName);

                pushButtonSetFocus();
            }
        }
        //else do nothing

    } catch (...) {
        qDebug() << "Error: DelaunayTriangulation::on_pushButtonFIND_clicked() is returning w/o checking";
    }
}

