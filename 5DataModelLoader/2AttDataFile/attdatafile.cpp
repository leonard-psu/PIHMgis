#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>

#include "attdatafile.h"
#include "ui_attdatafile.h"

#include "0LibsIO/IOProjectFile.h"
#include "0LibsOther/att_data_file.h"
#include "globals.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// AttDataFile Constructor
// Parent is Main Window, filename is the open project text file used to store project details
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AttDataFile::AttDataFile(QWidget *parent, QString filename) :
    QDialog(parent),
    ui(new Ui::AttDataFile)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile";

    try {
        ui->setupUi(this);

        input_width_one = 501;
        input_width_two = 250;

        filename_open_project = filename;
        bool found_file = false;
        finished_loading_files = false;

        QFile ProjectFile(filename_open_project);
        if ( ! ProjectFile.open(QIODevice::ReadOnly | QIODevice::Text) )
        {
            Log_Error_Message("ERROR: Unable to Open File: </span>" + filename_open_project );
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

        finished_loading_files = true;
        pushButtonSetFocus();


    } catch (...) {
        qDebug() << "Error: AttDataFile is returning w/o checking";
    }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// AttDataFile Deconstructor
// Todo: Check for memory leaks
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AttDataFile::~AttDataFile()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ~AttDataFile";

    try {
        delete ui;
    } catch (...) {
        qDebug() << "Error: ~AttDataFile is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Load_Project_Settings
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool AttDataFile::Load_Project_Settings()
{
    if (print_debug_messages)
        qDebug() << "INFO: AttDataFile::Load_Project_Settings()";

    try {

        QStringList ModuleStringList;
        QString TempFileName;
        bool already_displayed_message = false;

        // Data Model OUTPUT File Name
        ModuleStringList = ReadModuleLine(filename_open_project,tr("TINShapeLayer"));
        if ( ModuleStringList.length() > 0  )
        {
            TempFileName = ModuleStringList.at(3);
            TempFileName = TempFileName.right(TempFileName.length()-TempFileName.lastIndexOf("/")-1);
            TempFileName.replace( QString(".shp"), QString(".att") );

            QString output_filename = user_pihmgis_root_folder + "/4DataModelLoader/" + TempFileName;
            already_displayed_message = Check_Att_Output(output_filename, true);
        }

        ModuleStringList = ReadModuleLine(filename_open_project,tr("MeshDataFile"));
        if ( ModuleStringList.length() > 0  )
        {
            TempFileName = ModuleStringList.at(9);
            QString output_filename = user_pihmgis_root_folder + "/4DataModelLoader/" + TempFileName;
            if(already_displayed_message)
                Check_Att_Output(output_filename, false);
            else
                already_displayed_message = Check_Att_Output(output_filename, true);
        }

        ui->tabWidget->setCurrentIndex( 0 );

        ModuleStringList = ReadModuleLine(filename_open_project,tr("TINShapeLayer"));
        if ( ModuleStringList.length() > 0  )
        {
            TempFileName = ModuleStringList.at(3);
            AttDataFile::Check_TINShape_Input(TempFileName);
        }

        on_checkBoxPrecipitation_toggled(true);
        on_checkBoxTemperature_toggled(true);
        on_checkBoxRelativeHumidity_toggled(true);
        on_checkBoxWindVelocity_toggled(true);
        on_checkBoxSolarRadiation_toggled(true);
        on_checkBoxVaporPressure_toggled(true);

        on_checkBoxSoilClasses_toggled(true);
        on_checkBoxGeologyClasses_toggled(true);
        on_checkBoxMacropores_toggled(true);
        on_checkBoxLandCoverClasses_toggled(true);
        on_checkBoxMeltRegions_toggled(true);
        on_checkBoxSourcesSinks_toggled(true);

        on_checkBoxInterception_toggled(true);
        on_checkBoxSnowCover_toggled(true);
        on_checkBoxSurfaceStorage_toggled(true);
        on_checkBoxSoilMoisture_toggled(true);
        on_checkBoxGroundwater_toggled(true);
        on_checkBoxBoundaryCondition_toggled(true);

        ui->checkBoxPrecipitation->setChecked(true);            ui->lineEditPrecipitationFile->setText( QString( "1" ) );
        ui->checkBoxTemperature->setChecked(true);              ui->lineEditTemperatureFile->setText( QString( "1" ) );
        ui->checkBoxRelativeHumidity->setChecked(true);         ui->lineEditRelativeHumidityFile->setText( QString( "1" ) );
        ui->checkBoxWindVelocity->setChecked(true);             ui->lineEditWindVelocityFile->setText( QString( "1" ) );
        ui->checkBoxSolarRadiation->setChecked(true);           ui->lineEditSolarRadiationFile->setText( QString( "1" ) );
        ui->checkBoxVaporPressure->setChecked(true);            ui->lineEditVaporPressureFile->setText( QString( "1" ) );

        ui->checkBoxSoilClasses->setChecked(true);              ui->lineEditSoilClassesFile->setText( QString( "1" ) );
        ui->checkBoxGeologyClasses->setChecked(true);           ui->lineEditGeologyClassesFile->setText( QString( "1" ) );
        ui->checkBoxMacropores->setChecked(true);               ui->lineEditMacroporesFile->setText( QString( "1" ) );
        ui->checkBoxLandCoverClasses->setChecked(true);         ui->lineEditLandCoverClassesFile->setText( QString( "1" ) );
        ui->checkBoxMeltRegions->setChecked(true);              ui->lineEditMeltRegionsFile->setText( QString( "1" ) );
        ui->checkBoxSourcesSinks->setChecked(true);             ui->lineEditSourcesSinksFile->setText( QString( "0" ) );

        ui->checkBoxInterception->setChecked(true);             ui->lineEditInterceptionFile->setText( QString( "0" ) );
        ui->checkBoxSnowCover->setChecked(true);                ui->lineEditSnowCoverFile->setText( QString( "0" ) );
        ui->checkBoxSurfaceStorage->setChecked(true);           ui->lineEditSurfaceStorageFile->setText( QString( "0" ) );
        ui->checkBoxSoilMoisture->setChecked(true);             ui->lineEditSoilMoistureFile->setText( QString( "0" ) );
        ui->checkBoxGroundwater->setChecked(true);              ui->lineEditGroundwaterFile->setText( QString( "0" ) );
        ui->checkBoxBoundaryCondition->setChecked(true);        ui->lineEditBoundaryConditionFile->setText( QString( "0" ) );

        // End: Set Defaults

        // Start: Fill Form If Module Has Been Run Previously

        ModuleStringList = ReadModuleLine(filename_open_project,tr("AttDataFile"));

        if ( ModuleStringList.length() > 0 )
        {
            ui->checkBoxPrecipitation->setChecked(ModuleStringList.at(2).toInt());
            ui->checkBoxTemperature->setChecked(ModuleStringList.at(4).toInt());
            ui->checkBoxRelativeHumidity->setChecked(ModuleStringList.at(6).toInt());
            ui->checkBoxWindVelocity->setChecked(ModuleStringList.at(8).toInt());
            ui->checkBoxSolarRadiation->setChecked(ModuleStringList.at(10).toInt());
            ui->checkBoxVaporPressure->setChecked(ModuleStringList.at(12).toInt());

            ui->checkBoxSoilClasses->setChecked(ModuleStringList.at(14).toInt());
            ui->checkBoxGeologyClasses->setChecked(ModuleStringList.at(16).toInt());
            ui->checkBoxMacropores->setChecked(ModuleStringList.at(18).toInt());
            ui->checkBoxLandCoverClasses->setChecked(ModuleStringList.at(20).toInt());
            ui->checkBoxMeltRegions->setChecked(ModuleStringList.at(22).toInt());
            ui->checkBoxSourcesSinks->setChecked(ModuleStringList.at(24).toInt());

            ui->checkBoxInterception->setChecked(ModuleStringList.at(26).toInt());
            ui->checkBoxSnowCover->setChecked(ModuleStringList.at(28).toInt());
            ui->checkBoxSurfaceStorage->setChecked(ModuleStringList.at(30).toInt());
            ui->checkBoxSoilMoisture->setChecked(ModuleStringList.at(32).toInt());
            ui->checkBoxGroundwater->setChecked(ModuleStringList.at(34).toInt());
            ui->checkBoxBoundaryCondition->setChecked(ModuleStringList.at(36).toInt());


            Check_PrecipitationFileorValue(ModuleStringList.at(1));
            Check_TemperatureFileorValue(ModuleStringList.at(3));
            Check_RelativeHumidityFileorValue(ModuleStringList.at(5));
            Check_WindVelocityFileorValue(ModuleStringList.at(7));
            Check_SolarRadiationFileorValue(ModuleStringList.at(9));
            Check_VaporPressureFileorValue(ModuleStringList.at(11));

            Check_SoilClassesFileorValue(ModuleStringList.at(13));
            Check_GeologyClassesFileorValue(ModuleStringList.at(15));
            Check_MacroporesFileorValue(ModuleStringList.at(17));
            Check_LandCoverClassesFileorValue(ModuleStringList.at(19));
            Check_MeltRegionsFileorValue(ModuleStringList.at(21));
            Check_SourcesSinksFileorValue(ModuleStringList.at(23));

            Check_InterceptionFileorValue(ModuleStringList.at(25));
            Check_SnowCoverFileorValue(ModuleStringList.at(27));
            Check_SurfaceStorageFileorValue(ModuleStringList.at(29));
            Check_SoilMoistureFileorValue(ModuleStringList.at(31));
            Check_GroundwaterFileorValue(ModuleStringList.at(33));
            Check_BoundaryConditionFileorValue(ModuleStringList.at(35));

            Check_TINShape_Input(ModuleStringList.at(37));

            if(already_displayed_message)
                Check_Att_Output(ModuleStringList.at(38), false);
            else
                Check_Att_Output(ModuleStringList.at(38), true);
        }

        pushButtonSetFocus();

    } catch (...) {
        qDebug() << "Error: AttDataFile::Load_Project_Settings is returning w/o checking";
        return false;
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to clear message log
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::Clear_Log()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile::Clear_Log()";

    try {

        LogsString = tr("");
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

    } catch (...) {
        qDebug() << "Error: AttDataFile::Clear_Log() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check Log_Error_Message
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::Log_Error_Message(QString message)
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
void AttDataFile::Log_Message(QString message)
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
// Helper Function to focus button selection (needed for users w/o mouse)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::pushButtonSetFocus()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile::pushButtonSetFocus()";

    try {
        ui->pushButtonPrecipitationFile->setDefault(false);
        ui->pushButtonTemperatureFile->setDefault(false);
        ui->pushButtonRelativeHumidityFile->setDefault(false);
        ui->pushButtonWindVelocityFile->setDefault(false);
        ui->pushButtonSolarRadiationFile->setDefault(false);
        ui->pushButtonVaporPressureFile->setDefault(false);

        ui->pushButtonSoilClassesFile->setDefault(false);
        ui->pushButtonGeologyClassesFile->setDefault(false);
        ui->pushButtonMacroporesFile->setDefault(false);
        ui->pushButtonLandCoverClassesFile->setDefault(false);
        ui->pushButtonMeltRegionsFile->setDefault(false);
        ui->pushButtonSourcesSinksFile->setDefault(false);

        ui->pushButtonInterceptionFile->setDefault(false);
        ui->pushButtonSnowCoverFile->setDefault(false);
        ui->pushButtonSurfaceStorageFile->setDefault(false);
        ui->pushButtonSoilMoistureFile->setDefault(false);
        ui->pushButtonGroundwaterFile->setDefault(false);
        ui->pushButtonBoundaryConditionFile->setDefault(false);

        ui->pushButtonTINShapeLayerFile->setDefault(false);
        ui->pushButtonAttDataFile->setDefault(false);

        ui->pushButtonRun->setDefault(false);

        if (ui->lineEditPrecipitationFile->text() == nullptr)
        {
            ui->pushButtonPrecipitationFile->setDefault(true);
            ui->pushButtonPrecipitationFile->setFocus();
            return;
        }
        if (ui->lineEditTemperatureFile->text() == nullptr)
        {
            ui->pushButtonTemperatureFile->setDefault(true);
            ui->pushButtonTemperatureFile->setFocus();
            return;
        }
        if (ui->lineEditRelativeHumidityFile->text() == nullptr)
        {
            ui->pushButtonRelativeHumidityFile->setDefault(true);
            ui->pushButtonRelativeHumidityFile->setFocus();
            return;
        }
        if (ui->lineEditWindVelocityFile->text() == nullptr)
        {
            ui->pushButtonWindVelocityFile->setDefault(true);
            ui->pushButtonWindVelocityFile->setFocus();
            return;
        }
        if (ui->lineEditSolarRadiationFile->text() == nullptr)
        {
            ui->pushButtonSolarRadiationFile->setDefault(true);
            ui->pushButtonSolarRadiationFile->setFocus();
            return;
        }
        if (ui->lineEditVaporPressureFile->text() == nullptr)
        {
            ui->pushButtonVaporPressureFile->setDefault(true);
            ui->pushButtonVaporPressureFile->setFocus();
            return;
        }

        if (ui->lineEditSoilClassesFile->text() == nullptr)
        {
            ui->pushButtonSoilClassesFile->setDefault(true);
            ui->pushButtonSoilClassesFile->setFocus();
            return;
        }
        if (ui->lineEditGeologyClassesFile->text() == nullptr)
        {
            ui->pushButtonGeologyClassesFile->setDefault(true);
            ui->pushButtonGeologyClassesFile->setFocus();
            return;
        }
        if (ui->lineEditMacroporesFile->text() == nullptr)
        {
            ui->pushButtonMacroporesFile->setDefault(true);
            ui->pushButtonMacroporesFile->setFocus();
            return;
        }
        if (ui->lineEditLandCoverClassesFile->text() == nullptr)
        {
            ui->pushButtonLandCoverClassesFile->setDefault(true);
            ui->pushButtonLandCoverClassesFile->setFocus();
            return;
        }
        if (ui->lineEditMeltRegionsFile->text() == nullptr)
        {
            ui->pushButtonMeltRegionsFile->setDefault(true);
            ui->pushButtonMeltRegionsFile->setFocus();
            return;
        }
        if (ui->lineEditSourcesSinksFile->text() == nullptr)
        {
            ui->pushButtonSourcesSinksFile->setDefault(true);
            ui->pushButtonSourcesSinksFile->setFocus();
            return;
        }

        if (ui->lineEditInterceptionFile->text() == nullptr)
        {
            ui->pushButtonInterceptionFile->setDefault(true);
            ui->pushButtonInterceptionFile->setFocus();
            return;
        }
        if (ui->lineEditSnowCoverFile->text() == nullptr)
        {
            ui->pushButtonSnowCoverFile->setDefault(true);
            ui->pushButtonSnowCoverFile->setFocus();
            return;
        }
        if (ui->lineEditSurfaceStorageFile->text() == nullptr)
        {
            ui->pushButtonSurfaceStorageFile->setDefault(true);
            ui->pushButtonSurfaceStorageFile->setFocus();
            return;
        }
        if (ui->lineEditSoilMoistureFile->text() == nullptr)
        {
            ui->pushButtonSoilMoistureFile->setDefault(true);
            ui->pushButtonSoilMoistureFile->setFocus();
            return;
        }
        if (ui->lineEditGroundwaterFile->text() == nullptr)
        {
            ui->pushButtonGroundwaterFile->setDefault(true);
            ui->pushButtonGroundwaterFile->setFocus();
            return;
        }
        if (ui->lineEditBoundaryConditionFile->text() == nullptr)
        {
            ui->pushButtonBoundaryConditionFile->setDefault(true);
            ui->pushButtonBoundaryConditionFile->setFocus();
            return;
        }

        if (ui->lineEditTINShapeLayerFile->text() == nullptr)
        {
            ui->pushButtonTINShapeLayerFile->setDefault(true);
            ui->pushButtonTINShapeLayerFile->setFocus();
            return;
        }
        if (ui->lineEditAttDataFile->text() == nullptr)
        {
            ui->pushButtonAttDataFile->setDefault(true);
            ui->pushButtonAttDataFile->setFocus();
            return;
        }

        ui->pushButtonRun->setDefault(true);
        ui->pushButtonRun->setFocus();
    } catch (...) {
        qDebug() << "Error: AttDataFile::pushButtonSetFocus() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to assist if Check_Att_Output OUTPUT file exists (returns true) or does not (returns false)
// Will color red and warning if exists with color_and_message_if_exists=true
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool AttDataFile::Check_Att_Output(QString file, bool color_and_message_if_exists){

    if(print_debug_messages)
        qDebug() << "INFO: Check_Att_Output()";

    bool result = false;

    try {

        if(  fileExists(file) )
        {
            if(color_and_message_if_exists)
            {
                Log_Error_Message(" Att output already exists: " + file +tr(" You may need to delete these files.<br>"));
            }

            ui->lineEditAttDataFile->setStyleSheet("color: red;");
            ui->lineEditAttDataFile->setText(file);
            result = true;
        }
        else
        {
            ui->lineEditAttDataFile->setStyleSheet("color: black;");
            ui->lineEditAttDataFile->setText(file);

            result = false;
        }

    } catch (...) {
        qDebug() << "Error: AttDataFile::Check_Att_Output is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Check TINShape File exists (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool AttDataFile::Check_TINShape_Input(QString file){

    if(print_debug_messages)
        qDebug() << "INFO: Check_TINShape_Input()";

    bool result = false;

    try {

        if(  fileExists(file) )
        {
            ui->lineEditTINShapeLayerFile->setStyleSheet("color: black;");
            ui->lineEditTINShapeLayerFile->setText(file);
            result = true;
        }
        else
        {
            ui->lineEditTINShapeLayerFile->setStyleSheet("color: red;");
            ui->lineEditTINShapeLayerFile->setText(file);

            Log_Error_Message(" Tin Shape file not found: " + file +tr(" <br>"));

            result = false;
        }


    } catch (...) {
        qDebug() << "Error: Check_TINShape_Input is returning w/o checking";
        result = false;
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// Helper Function to Check if value is Numeric
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//bool AttDataFile::Is_String_Integer(QString input)
//{
//    if(print_debug_messages)
//        qDebug() << "INFO: Is_String_Numeric()";

//    bool result = false;

//    try {

//        //input.toDouble(&result);
//        input.toInt(&result);
//    }
//    catch (...) {
//        qDebug() << "Error: Is_String_Numeric. Assuming value is false;";
//        result = false;
//    }

//    return result;
//}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Check if value is Numeric
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool AttDataFile::Is_String_Integer(QString input)
{
    if(print_debug_messages)
        qDebug() << "INFO: Is_String_Numeric()";

    bool result = false;

    try {

        bool integer_check = false;
        bool double_check = false;
        bool float_check = false;
        bool long_check = false;

        //input.toDouble(&result);
        input.toInt(&integer_check);
        input.toDouble(&double_check);
        input.toFloat(&float_check);
        input.toLong(&long_check);

        if(integer_check)
            result = true;
        if(double_check)
            result = true;
        if(float_check)
            result = true;
        if(long_check)
            result = true;

    }
    catch (...) {
        qDebug() << "Error: Is_String_Numeric. Assuming value is false;";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Check Precipitation File exists (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool AttDataFile::Check_PrecipitationFileorValue(QString value){

    if(print_debug_messages)
        qDebug() << "INFO: Check_PrecipitationFileorValue()";

    bool result = false;

    try {

        if(ui->checkBoxPrecipitation->isChecked())
        {
            if(value.isNull() || value.isEmpty() )
            {
                ui->lineEditPrecipitationFile->setStyleSheet("color: red;");
                ui->lineEditPrecipitationFile->setText("Missing");
                result = false;
            }
            else if(value == QString("Missing"))
            {
                result = false;
            }
            else
            {
                result = true; //For now assume validators work
            }
        }
        else //is a file name to check
        {
            if(  fileExists(value) )
            {
                ui->lineEditPrecipitationFile->setStyleSheet("color: black;");
                ui->lineEditPrecipitationFile->setText(value);
                result = true;
            }
            else
            {
                ui->lineEditPrecipitationFile->setStyleSheet("color: red;");
                ui->lineEditPrecipitationFile->setText(value);

                bool num_check = Is_String_Integer(value);
                if(!num_check)
                {
                    if(value.isNull() || value.isEmpty() )
                    {
                        //do nothing
                    }
                    else
                    {
                        Log_Error_Message(" Precipitation File not found: " + value  );
                    }
                }

                result = false;
            }
        }

    } catch (...) {
        qDebug() << "Error: Check_PrecipitationFile is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Check Temperature File exists (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool AttDataFile::Check_TemperatureFileorValue(QString value){

    if(print_debug_messages)
        qDebug() << "INFO: Check_TemperatureFile()";

    bool result = false;

    try {

        if(ui->checkBoxTemperature->isChecked())
        {
            if(value.isNull() || value.isEmpty())
            {
                ui->lineEditTemperatureFile->setStyleSheet("color: red;");
                ui->lineEditTemperatureFile->setText("Missing");
                result = false;
            }
            else if(value == QString("Missing"))
            {
                result = false;
            }
            else
            {
                result = true; //For now assume validators work
            }

        }
        else //is a file name to check
        {
            if(  fileExists(value) )
            {
                ui->lineEditTemperatureFile->setStyleSheet("color: black;");
                ui->lineEditTemperatureFile->setText(value);
                result = true;
            }
            else
            {
                ui->lineEditTemperatureFile->setStyleSheet("color: red;");
                ui->lineEditTemperatureFile->setText(value);

                bool num_check = Is_String_Integer(value);
                if(!num_check)
                {
                    if(value.isNull() || value.isEmpty() )
                    {
                        //do nothing
                    }
                    else
                    {
                        Log_Error_Message(" Temperature File not found: " + value );
                    }
                }

                result = false;
            }
        }

    } catch (...) {
        qDebug() << "Error: Check_TemperatureFile is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Check RelativeHumidity File exists (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool AttDataFile::Check_RelativeHumidityFileorValue(QString value){

    if(print_debug_messages)
        qDebug() << "INFO: Check_RelativeHumidityFile()";

    bool result = false;

    try {

        if(ui->checkBoxRelativeHumidity->isChecked())
        {
            if(value.isNull() || value.isEmpty())
            {
                ui->lineEditRelativeHumidityFile->setStyleSheet("color: red;");
                ui->lineEditRelativeHumidityFile->setText("Missing");
                result = false;
            }
            else if(value == QString("Missing"))
            {
                result = false;
            }
            else
            {
                result = true; //For now assume validators work
            }

        }
        else //is a file name to check
        {
            if( fileExists(value) )
            {
                ui->lineEditRelativeHumidityFile->setStyleSheet("color: black;");
                ui->lineEditRelativeHumidityFile->setText(value);
                result = true;
            }
            else
            {
                ui->lineEditRelativeHumidityFile->setStyleSheet("color: red;");
                ui->lineEditRelativeHumidityFile->setText(value);

                bool num_check = Is_String_Integer(value);
                if(!num_check)
                {
                    if(value.isNull() || value.isEmpty() )
                    {
                        //do nothing
                    }
                    else
                    {
                        Log_Error_Message(" RelativeHumidity File not found: " + value  );
                    }
                }

                result = false;
            }
        }
    } catch (...) {
        qDebug() << "Error: Check_RelativeHumidityFile is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Check WindVelocity File exists (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool AttDataFile::Check_WindVelocityFileorValue(QString value){

    if(print_debug_messages)
        qDebug() << "INFO: Check_WindVelocityFile()";

    bool result = false;

    try {

        if(ui->checkBoxWindVelocity->isChecked())
        {
            if(value.isNull() || value.isEmpty())
            {
                ui->lineEditWindVelocityFile->setStyleSheet("color: red;");
                ui->lineEditWindVelocityFile->setText("Missing");
                result = false;
            }
            else if(value == QString("Missing"))
            {
                result = false;
            }
            else
            {
                result = true; //For now assume validators work
            }

        }
        else //is a file name to check
        {
            if(  fileExists(value) )
            {
                ui->lineEditWindVelocityFile->setStyleSheet("color: black;");
                ui->lineEditWindVelocityFile->setText(value);
                result = true;
            }
            else
            {
                ui->lineEditWindVelocityFile->setStyleSheet("color: red;");
                ui->lineEditWindVelocityFile->setText(value);

                bool num_check = Is_String_Integer(value);
                if(!num_check)
                {
                    if(value.isNull() || value.isEmpty() )
                    {
                        //do nothing
                    }
                    else
                    {
                        Log_Error_Message(" WindVelocity File not found: " + value  );
                    }
                }

                result = false;
            }
        }

    } catch (...) {
        qDebug() << "Error: Check_WindVelocityFile is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Check SolarRadiation File exists (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool AttDataFile::Check_SolarRadiationFileorValue(QString value){

    if(print_debug_messages)
        qDebug() << "INFO: Check_SolarRadiationFile()";

    bool result = false;

    try {

        if(ui->checkBoxSolarRadiation->isChecked())
        {
            if(value.isNull() || value.isEmpty())
            {
                ui->lineEditSolarRadiationFile->setStyleSheet("color: red;");
                ui->lineEditSolarRadiationFile->setText("Missing");
                result = false;
            }
            else if(value == QString("Missing"))
            {
                result = false;
            }
            else
            {
                result = true; //For now assume validators work
            }

        }
        else //is a file name to check
        {
            if(  fileExists(value) )
            {
                ui->lineEditSolarRadiationFile->setStyleSheet("color: black;");
                ui->lineEditSolarRadiationFile->setText(value);
                result = true;
            }
            else
            {
                ui->lineEditSolarRadiationFile->setStyleSheet("color: red;");
                ui->lineEditSolarRadiationFile->setText(value);

                bool num_check = Is_String_Integer(value);
                if(!num_check)
                {
                    if(value.isNull() || value.isEmpty() )
                    {
                        //do nothing
                    }
                    else
                    {
                        Log_Error_Message(" SolarRadiation File not found: " + value  );
                    }
                }

                result = false;
            }
        }

    } catch (...) {
        qDebug() << "Error: Check_SolarRadiationFile is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Check VaporPressure File exists (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool AttDataFile::Check_VaporPressureFileorValue(QString value){

    if(print_debug_messages)
        qDebug() << "INFO: Check_VaporPressureFile()";

    bool result = false;

    try {

        if(ui->checkBoxVaporPressure->isChecked())
        {
            if(value.isNull() || value.isEmpty())
            {
                ui->lineEditVaporPressureFile->setStyleSheet("color: red;");
                ui->lineEditVaporPressureFile->setText("Missing");
                result = false;
            }
            else if(value == QString("Missing"))
            {
                result = false;
            }
            else
            {
                result = true; //For now assume validators work
            }

        }
        else //is a file name to check
        {
            if(  fileExists(value) )
            {
                ui->lineEditVaporPressureFile->setStyleSheet("color: black;");
                ui->lineEditVaporPressureFile->setText(value);
                result = true;
            }
            else
            {
                ui->lineEditVaporPressureFile->setStyleSheet("color: red;");
                ui->lineEditVaporPressureFile->setText(value);

                bool num_check = Is_String_Integer(value);
                if(!num_check)
                {
                    if(value.isNull() || value.isEmpty() )
                    {
                        //do nothing
                    }
                    else
                    {
                        Log_Error_Message(" VaporPressure File not found: " + value  );
                    }
                }

                result = false;
            }
        }

    } catch (...) {
        qDebug() << "Error: Check_VaporPressureFile is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Check SoilClasses File exists (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool AttDataFile::Check_SoilClassesFileorValue(QString value){

    if(print_debug_messages)
        qDebug() << "INFO: Check_SoilClassesFile()";

    bool result = false;

    try {

        if(ui->checkBoxSoilClasses->isChecked())
        {
            if(value.isNull() || value.isEmpty())
            {
                ui->lineEditSoilClassesFile->setStyleSheet("color: red;");
                ui->lineEditSoilClassesFile->setText("Missing");
                result = false;
            }
            else if(value == QString("Missing"))
            {
                result = false;
            }
            else
            {
                result = true; //For now assume validators work
            }

        }
        else //is a file name to check
        {
            if(  fileExists(value) )
            {
                ui->lineEditSoilClassesFile->setStyleSheet("color: black;");
                ui->lineEditSoilClassesFile->setText(value);
                result = true;
            }
            else
            {
                ui->lineEditSoilClassesFile->setStyleSheet("color: red;");
                ui->lineEditSoilClassesFile->setText(value);

                bool num_check = Is_String_Integer(value);
                if(!num_check)
                {
                    if(value.isNull() || value.isEmpty() )
                    {
                        //do nothing
                    }
                    else
                    {
                        Log_Error_Message(" Soil Classes File not found: " + value  );
                    }
                }

                result = false;
            }
        }

    } catch (...) {
        qDebug() << "Error: Check_SoilClassesFile is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Check GeologyClasses File exists (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool AttDataFile::Check_GeologyClassesFileorValue(QString value){

    if(print_debug_messages)
        qDebug() << "INFO: Check_GeologyClassesFile()";

    bool result = false;

    try {

        if(ui->checkBoxGeologyClasses->isChecked())
        {
            if(value.isNull() || value.isEmpty())
            {
                ui->lineEditGeologyClassesFile->setStyleSheet("color: red;");
                ui->lineEditGeologyClassesFile->setText("Missing");
                result = false;
            }
            else if(value == QString("Missing"))
            {
                result = false;
            }
            else
            {
                result = true; //For now assume validators work
            }

        }
        else //is a file name to check
        {
            if(  fileExists(value) )
            {
                ui->lineEditGeologyClassesFile->setStyleSheet("color: black;");
                ui->lineEditGeologyClassesFile->setText(value);
                result = true;
            }
            else
            {
                ui->lineEditGeologyClassesFile->setStyleSheet("color: red;");
                ui->lineEditGeologyClassesFile->setText(value);

                bool num_check = Is_String_Integer(value);
                if(!num_check)
                {
                    if(value.isNull() || value.isEmpty() )
                    {
                        //do nothing
                    }
                    else
                    {
                        Log_Error_Message(" Geology Classes File not found: " + value  );
                    }
                }

                result = false;
            }
        }

    } catch (...) {
        qDebug() << "Error: Check_GeologyClassesFile is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Check Macropores File exists (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool AttDataFile::Check_MacroporesFileorValue(QString value){

    if(print_debug_messages)
        qDebug() << "INFO: Check_MacroporesFile()";

    bool result = false;

    try {

        if(ui->checkBoxMacropores->isChecked())
        {
            if(value.isNull() || value.isEmpty())
            {
                ui->lineEditMacroporesFile->setStyleSheet("color: red;");
                ui->lineEditMacroporesFile->setText("Missing");
                result = false;
            }
            else if(value == QString("Missing"))
            {
                result = false;
            }
            else
            {
                result = true; //For now assume validators work
            }

        }
        else //is a file name to check
        {
            if(  fileExists(value) )
            {
                ui->lineEditMacroporesFile->setStyleSheet("color: black;");
                ui->lineEditMacroporesFile->setText(value);
                result = true;
            }
            else
            {
                ui->lineEditMacroporesFile->setStyleSheet("color: red;");
                ui->lineEditMacroporesFile->setText(value);

                bool num_check = Is_String_Integer(value);
                if(!num_check)
                {
                    if(value.isNull() || value.isEmpty() )
                    {
                        //do nothing
                    }
                    else
                    {
                        Log_Error_Message(" Macropores File not found: " + value  );
                    }
                }

                result = false;
            }
        }

    } catch (...) {
        qDebug() << "Error: Check_MacroporesFile is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Check LandCover File exists (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool AttDataFile::Check_LandCoverClassesFileorValue(QString value){

    if(print_debug_messages)
        qDebug() << "INFO: Check_LandCoverClassesFile()";

    bool result = false;

    try {

        if(ui->checkBoxLandCoverClasses->isChecked())
        {
            if(value.isNull() || value.isEmpty())
            {
                ui->lineEditLandCoverClassesFile->setStyleSheet("color: red;");
                ui->lineEditLandCoverClassesFile->setText("Missing");
                result = false;
            }
            else if(value == QString("Missing"))
            {
                result = false;
            }
            else
            {
                result = true; //For now assume validators work
            }

        }
        else //is a file name to check
        {
            if(  fileExists(value) )
            {
                ui->lineEditLandCoverClassesFile->setStyleSheet("color: black;");
                ui->lineEditLandCoverClassesFile->setText(value);
                result = true;
            }
            else
            {
                ui->lineEditLandCoverClassesFile->setStyleSheet("color: red;");
                ui->lineEditLandCoverClassesFile->setText(value);

                bool num_check = Is_String_Integer(value);
                if(!num_check)
                {
                    if(value.isNull() || value.isEmpty() )
                    {
                        //do nothing
                    }
                    else
                    {
                        Log_Error_Message(" LandCover Classes File not found: " + value  );
                    }
                }

                result = false;
            }
        }

    } catch (...) {
        qDebug() << "Error: Check_LandCoverClassesFile is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Check MeltRegions File exists (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool AttDataFile::Check_MeltRegionsFileorValue(QString value){

    if(print_debug_messages)
        qDebug() << "INFO: Check_MeltRegionsFile()";

    bool result = false;

    try {

        if(ui->checkBoxMeltRegions->isChecked())
        {
            if(value.isNull() || value.isEmpty())
            {
                ui->lineEditMeltRegionsFile->setStyleSheet("color: red;");
                ui->lineEditMeltRegionsFile->setText("Missing");
                result = false;
            }
            else if(value == QString("Missing"))
            {
                result = false;
            }
            else
            {
                result = true; //For now assume validators work
            }

        }
        else //is a file name to check
        {
            if(  fileExists(value) )
            {
                ui->lineEditMeltRegionsFile->setStyleSheet("color: black;");
                ui->lineEditMeltRegionsFile->setText(value);
                result = true;
            }
            else
            {
                ui->lineEditMeltRegionsFile->setStyleSheet("color: red;");
                ui->lineEditMeltRegionsFile->setText(value);

                bool num_check = Is_String_Integer(value);
                if(!num_check)
                {
                    if(value.isNull() || value.isEmpty() )
                    {
                        //do nothing
                    }
                    else
                    {
                        Log_Error_Message(" MeltRegions File not found: " + value );
                    }
                }

                result = false;
            }
        }

    } catch (...) {
        qDebug() << "Error: Check_MeltRegionsFile is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Check SourcesSinks File exists (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool AttDataFile::Check_SourcesSinksFileorValue(QString value){

    if(print_debug_messages)
        qDebug() << "INFO: Check_SourcesSinksFile()";

    bool result = false;

    try {

        if(ui->checkBoxSourcesSinks->isChecked())
        {
            if(value.isNull() || value.isEmpty())
            {
                ui->lineEditSourcesSinksFile->setStyleSheet("color: red;");
                ui->lineEditSourcesSinksFile->setText("Missing");
                result = false;
            }
            else if(value == QString("Missing"))
            {
                result = false;
            }
            else
            {
                result = true; //For now assume validators work
            }

        }
        else //is a file name to check
        {
            if(  fileExists(value) )
            {
                ui->lineEditSourcesSinksFile->setStyleSheet("color: black;");
                ui->lineEditSourcesSinksFile->setText(value);
                result = true;
            }
            else
            {
                ui->lineEditSourcesSinksFile->setStyleSheet("color: red;");
                ui->lineEditSourcesSinksFile->setText(value);

                bool num_check = Is_String_Integer(value);
                if(!num_check)
                {
                    if(value.isNull() || value.isEmpty() )
                    {
                        //do nothing
                    }
                    else
                    {
                        Log_Error_Message(" SourcesSinks File not found: " + value  );
                    }
                }

                result = false;
            }
        }

    } catch (...) {
        qDebug() << "Error: Check_SourcesSinksFile is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Check Interception File exists (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool AttDataFile::Check_InterceptionFileorValue(QString value){

    if(print_debug_messages)
        qDebug() << "INFO: Check_InterceptionFile()";

    bool result = false;

    try {

        if(ui->checkBoxInterception->isChecked())
        {
            if(value.isNull() || value.isEmpty())
            {
                ui->lineEditInterceptionFile->setStyleSheet("color: red;");
                ui->lineEditInterceptionFile->setText("Missing");
                result = false;
            }
            else if(value == QString("Missing"))
            {
                result = false;
            }
            else
            {
                result = true; //For now assume validators work
            }

        }
        else //is a file name to check
        {
            if(  fileExists(value) )
            {
                ui->lineEditInterceptionFile->setStyleSheet("color: black;");
                ui->lineEditInterceptionFile->setText(value);
                result = true;
            }
            else
            {
                ui->lineEditInterceptionFile->setStyleSheet("color: red;");
                ui->lineEditInterceptionFile->setText(value);

                bool num_check = Is_String_Integer(value);
                if(!num_check)
                {
                    if(value.isNull() || value.isEmpty() )
                    {
                        //do nothing
                    }
                    else
                    {
                        Log_Error_Message(" Interception File not found: " + value );
                    }
                }

                result = false;
            }
        }

    } catch (...) {
        qDebug() << "Error: Check_InterceptionFile is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Check SnowCover File exists (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool AttDataFile::Check_SnowCoverFileorValue(QString value){

    if(print_debug_messages)
        qDebug() << "INFO: Check_SnowCoverFile()";

    bool result = false;

    try {

        if(ui->checkBoxSnowCover->isChecked())
        {
            if(value.isNull() || value.isEmpty())
            {
                ui->lineEditSnowCoverFile->setStyleSheet("color: red;");
                ui->lineEditSnowCoverFile->setText("Missing");
                result = false;
            }
            else if(value == QString("Missing"))
            {
                result = false;
            }
            else
            {
                result = true; //For now assume validators work
            }

        }
        else //is a file name to check
        {
            if(  fileExists(value) )
            {
                ui->lineEditSnowCoverFile->setStyleSheet("color: black;");
                ui->lineEditSnowCoverFile->setText(value);
                result = true;
            }
            else
            {
                ui->lineEditSnowCoverFile->setStyleSheet("color: red;");
                ui->lineEditSnowCoverFile->setText(value);

                bool num_check = Is_String_Integer(value);
                if(!num_check)
                {
                    if(value.isNull() || value.isEmpty() )
                    {
                        //do nothing
                    }
                    else
                    {
                        Log_Error_Message(" SnowCover File not found: " + value  );
                    }
                }

                result = false;
            }
        }

    } catch (...) {
        qDebug() << "Error: Check_SnowCoverFile is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Check SurfaceStorage File exists (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool AttDataFile::Check_SurfaceStorageFileorValue(QString value){

    if(print_debug_messages)
        qDebug() << "INFO: Check_SurfaceStorageFile()";

    bool result = false;

    try {

        if(ui->checkBoxSurfaceStorage->isChecked())
        {
            if(value.isNull() || value.isEmpty())
            {
                ui->lineEditSurfaceStorageFile->setStyleSheet("color: red;");
                ui->lineEditSurfaceStorageFile->setText("Missing");
                result = false;
            }
            else if(value == QString("Missing"))
            {
                result = false;
            }
            else
            {
                result = true; //For now assume validators work
            }

        }
        else //is a file name to check
        {
            if(  fileExists(value) )
            {
                ui->lineEditSurfaceStorageFile->setStyleSheet("color: black;");
                ui->lineEditSurfaceStorageFile->setText(value);
                result = true;
            }
            else
            {
                ui->lineEditSurfaceStorageFile->setStyleSheet("color: red;");
                ui->lineEditSurfaceStorageFile->setText(value);

                bool num_check = Is_String_Integer(value);
                if(!num_check)
                {
                    if(value.isNull() || value.isEmpty() )
                    {
                        //do nothing
                    }
                    else
                    {
                        Log_Error_Message(" SurfaceStorage File not found: " + value  );
                    }
                }

                result = false;
            }
        }

    } catch (...) {
        qDebug() << "Error: Check_SurfaceStorageFile is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Check SoilMoisture File exists (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool AttDataFile::Check_SoilMoistureFileorValue(QString value){

    if(print_debug_messages)
        qDebug() << "INFO: Check_SoilMoistureFile()";

    bool result = false;

    try {

        if(ui->checkBoxSoilMoisture->isChecked())
        {
            if(value.isNull() || value.isEmpty())
            {
                ui->lineEditSoilMoistureFile->setStyleSheet("color: red;");
                ui->lineEditSoilMoistureFile->setText("Missing");
                result = false;
            }
            else if(value == QString("Missing"))
            {
                result = false;
            }
            else
            {
                result = true; //For now assume validators work
            }

        }
        else //is a file name to check
        {
            if(  fileExists(value) )
            {
                ui->lineEditSoilMoistureFile->setStyleSheet("color: black;");
                ui->lineEditSoilMoistureFile->setText(value);
                result = true;
            }
            else
            {
                ui->lineEditSoilMoistureFile->setStyleSheet("color: red;");
                ui->lineEditSoilMoistureFile->setText(value);

                bool num_check = Is_String_Integer(value);
                if(!num_check)
                {
                    if(value.isNull() || value.isEmpty() )
                    {
                        //do nothing
                    }
                    else
                    {
                        Log_Error_Message(" SoilMoisture File not found: " + value  );
                    }
                }

                result = false;
            }
        }

    } catch (...) {
        qDebug() << "Error: Check_SoilMoistureFile is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Check Groundwater File exists (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool AttDataFile::Check_GroundwaterFileorValue(QString value){

    if(print_debug_messages)
        qDebug() << "INFO: Check_GroundwaterFile()";

    bool result = false;

    try {

        if(ui->checkBoxGroundwater->isChecked())
        {
            if(value.isNull() || value.isEmpty())
            {
                ui->lineEditGroundwaterFile->setStyleSheet("color: red;");
                ui->lineEditGroundwaterFile->setText("Missing");
                result = false;
            }
            else if(value == QString("Missing"))
            {
                result = false;
            }
            else
            {
                result = true; //For now assume validators work
            }

        }
        else //is a file name to check
        {
            if(  fileExists(value) )
            {
                ui->lineEditGroundwaterFile->setStyleSheet("color: black;");
                ui->lineEditGroundwaterFile->setText(value);
                result = true;
            }
            else
            {
                ui->lineEditGroundwaterFile->setStyleSheet("color: red;");
                ui->lineEditGroundwaterFile->setText(value);

                bool num_check = Is_String_Integer(value);
                if(!num_check)
                {
                    if(value.isNull() || value.isEmpty() )
                    {
                        //do nothing
                    }
                    else
                    {
                        Log_Error_Message(" Groundwater File not found: " + value  );
                    }
                }

                result = false;
            }
        }

    } catch (...) {
        qDebug() << "Error: Check_GroundwaterFile is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Check BoundaryCondition File exists (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool AttDataFile::Check_BoundaryConditionFileorValue(QString value){

    if(print_debug_messages)
        qDebug() << "INFO: Check_BoundaryConditionFile()";

    bool result = false;

    try {

        if(ui->checkBoxBoundaryCondition->isChecked())
        {
            if(value.isNull() || value.isEmpty())
            {
                ui->lineEditBoundaryConditionFile->setStyleSheet("color: red;");
                ui->lineEditBoundaryConditionFile->setText("Missing");
                result = false;
            }
            else if(value == QString("Missing"))
            {
                result = false;
            }
            else
            {
                result = true; //For now assume validators work
            }

        }
        else //is a file name to check
        {
            if(  fileExists(value) )
            {
                ui->lineEditBoundaryConditionFile->setStyleSheet("color: black;");
                ui->lineEditBoundaryConditionFile->setText(value);
                result = true;
            }
            else
            {
                ui->lineEditBoundaryConditionFile->setStyleSheet("color: red;");
                ui->lineEditBoundaryConditionFile->setText(value);

                bool num_check = Is_String_Integer(value);
                if(!num_check)
                {
                    if(value.isNull() || value.isEmpty() )
                    {
                        //do nothing
                    }
                    else
                    {
                        Log_Error_Message(" BoundaryCondition File not found: " + value  );
                    }
                }

                result = false;
            }
        }

    } catch (...) {
        qDebug() << "Error: Check_BoundaryConditionFile is returning w/o checking";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button Precipitation Clicked Event (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::on_pushButtonPrecipitationFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile::on_pushButtonPrecipitationFile_clicked()";

    try {

        Clear_Log();

        QString RasterFileName = QFileDialog::getOpenFileName(this, "Precipitation Raster", user_pihmgis_root_folder, "Precipitation Raster(*.adf *.asc)");

        if ( RasterFileName != nullptr)
        {
            Check_PrecipitationFileorValue(RasterFileName);

            pushButtonSetFocus();
        }

    } catch (...) {
        qDebug() << "Error: AttDataFile::on_pushButtonPrecipitationFile_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button Temperature Clicked Event (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::on_pushButtonTemperatureFile_clicked()
{

    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile::on_pushButtonTemperatureFile_clicked()";

    try {

        Clear_Log();

        QString RasterFileName = QFileDialog::getOpenFileName(this, "Temperature Raster", user_pihmgis_root_folder, "Temperature Raster(*.adf *.asc)");

        if ( RasterFileName != nullptr)
        {
            Check_TemperatureFileorValue(RasterFileName);

            pushButtonSetFocus();
        }

    } catch (...) {
        qDebug() << "Error: AttDataFile::on_pushButtonTemperatureFile_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button RelativeHumidity Clicked Event (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::on_pushButtonRelativeHumidityFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile::on_pushButtonRelativeHumidityFile_clicked()";

    try {

        Clear_Log();

        QString RasterFileName = QFileDialog::getOpenFileName(this, "Relative Humidity Raster", user_pihmgis_root_folder, "Relative Humidity Raster(*.adf *.asc)");

        if ( RasterFileName != nullptr)
        {
            Check_RelativeHumidityFileorValue(RasterFileName);

            pushButtonSetFocus();
        }

    } catch (...) {
        qDebug() << "Error: AttDataFile::on_pushButtonRelativeHumidityFile_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button WindVelocity Clicked Event (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::on_pushButtonWindVelocityFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile::on_pushButtonWindVelocityFile_clicked()";

    try {

        Clear_Log();

        QString RasterFileName = QFileDialog::getOpenFileName(this, "Wind Velocity Raster", user_pihmgis_root_folder, "Wind Velocity Raster(*.adf *.asc)");

        if ( RasterFileName != nullptr)
        {
            Check_WindVelocityFileorValue(RasterFileName);

            pushButtonSetFocus();
        }

    } catch (...) {
        qDebug() << "Error: AttDataFile::on_pushButtonWindVelocityFile_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button SolarRadiation Clicked Event (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::on_pushButtonSolarRadiationFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile::on_pushButtonSolarRadiationFile_clicked()";

    try {

        Clear_Log();

        QString RasterFileName = QFileDialog::getOpenFileName(this, "Solar Radiation Raster", user_pihmgis_root_folder, "Solar Radiation Raster(*.adf *.asc)");

        if ( RasterFileName != nullptr)
        {
            Check_SolarRadiationFileorValue(RasterFileName);

            pushButtonSetFocus();
        }

    } catch (...) {
        qDebug() << "Error: AttDataFile::on_pushButtonSolarRadiationFile_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button VaporPressure Clicked Event (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::on_pushButtonVaporPressureFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile::on_pushButtonVaporPressureFile_clicked()";

    try {

        QString RasterFileName = QFileDialog::getOpenFileName(this, "Vapor Pressure Raster", user_pihmgis_root_folder, "Vapor Pressure Raster(*.adf *.asc)");

        if ( RasterFileName != nullptr)
        {
            Check_VaporPressureFileorValue(RasterFileName);

            pushButtonSetFocus();
        }

    } catch (...) {
        qDebug() << "Error: AttDataFile::on_pushButtonVaporPressureFile_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button SoilClasses Clicked Event (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::on_pushButtonSoilClassesFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile::on_pushButtonSoilClassesFile_clicked()";

    try {

        Clear_Log();

        QString RasterFileName = QFileDialog::getOpenFileName(this, "Soil Classes Raster", user_pihmgis_root_folder, "Soil Classes Raster(*.adf *.asc)");

        if ( RasterFileName != nullptr)
        {
            Check_SoilClassesFileorValue(RasterFileName);

            pushButtonSetFocus();
        }

    } catch (...) {
        qDebug() << "Error: AttDataFile::on_pushButtonSoilClassesFile_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button GeologyClasses Clicked Event (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::on_pushButtonGeologyClassesFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile::on_pushButtonGeologyClassesFile_clicked()";

    try {

        Clear_Log();

        QString RasterFileName = QFileDialog::getOpenFileName(this, "Geology Classes Raster", user_pihmgis_root_folder, "Geology Classes Raster(*.adf *.asc)");

        if ( RasterFileName != nullptr)
        {
            Check_GeologyClassesFileorValue(RasterFileName);

            pushButtonSetFocus();
        }

    } catch (...) {
        qDebug() << "Error: AttDataFile::on_pushButtonGeologyClassesFile_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button Macropores Clicked Event (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::on_pushButtonMacroporesFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile::on_pushButtonMacroporesFile_clicked()";

    try {

        QString RasterFileName = QFileDialog::getOpenFileName(this, "Macropores Raster", user_pihmgis_root_folder, "Macropores Raster(*.adf *.asc)");

        if ( RasterFileName != nullptr)
        {
            Check_MacroporesFileorValue(RasterFileName);

            pushButtonSetFocus();
        }

    } catch (...) {
        qDebug() << "Error: AttDataFile::on_pushButtonMacroporesFile_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button LandCoverClasses Clicked Event (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::on_pushButtonLandCoverClassesFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile::on_pushButtonLandCoverClassesFile_clicked()";

    try {

        Clear_Log();

        QString RasterFileName = QFileDialog::getOpenFileName(this, "Land-cover Raster", user_pihmgis_root_folder, "Land-cover Raster(*.adf *.asc)");

        if ( RasterFileName != nullptr)
        {
            Check_LandCoverClassesFileorValue(RasterFileName);

            pushButtonSetFocus();
        }

    } catch (...) {
        qDebug() << "Error: AttDataFile::on_pushButtonLandCoverClassesFile_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button MeltRegions Clicked Event (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::on_pushButtonMeltRegionsFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile::on_pushButtonMeltRegionsFile_clicked()";

    try {

        Clear_Log();

        QString RasterFileName = QFileDialog::getOpenFileName(this, "Melt Regions Raster", user_pihmgis_root_folder, "Melt Regions Raster(*.adf *.asc)");

        if ( RasterFileName != nullptr)
        {
            Check_MeltRegionsFileorValue(RasterFileName);

            pushButtonSetFocus();
        }

    } catch (...) {
        qDebug() << "Error: AttDataFile::on_pushButtonMeltRegionsFile_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button SourcesSinks Clicked Event (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::on_pushButtonSourcesSinksFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile::on_pushButtonSourcesSinksFile_clicked()";

    try {

        Clear_Log();

        QString RasterFileName = QFileDialog::getOpenFileName(this, "Sources-Sinks Raster", user_pihmgis_root_folder, "Sources-Sinks Raster(*.adf *.asc)");

        if ( RasterFileName != nullptr)
        {
            Check_SourcesSinksFileorValue(RasterFileName);

            pushButtonSetFocus();
        }

    } catch (...) {
        qDebug() << "Error: AttDataFile::on_pushButtonSourcesSinksFile_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button Interception Clicked Event (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::on_pushButtonInterceptionFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile::on_pushButtonInterceptionFile_clicked()";

    try {

        Clear_Log();

        QString RasterFileName = QFileDialog::getOpenFileName(this, "Interception Raster", user_pihmgis_root_folder, "Interception Raster(*.adf *.asc)");

        if ( RasterFileName != nullptr)
        {
            Check_InterceptionFileorValue(RasterFileName);

            pushButtonSetFocus();
        }

    } catch (...) {
        qDebug() << "Error: AttDataFile::on_pushButtonInterceptionFile_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button SnowCover Clicked Event (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::on_pushButtonSnowCoverFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile::on_pushButtonSnowCoverFile_clicked()";

    try {

        Clear_Log();

        QString RasterFileName = QFileDialog::getOpenFileName(this, "Snow Cover Raster", user_pihmgis_root_folder, "Snow Cover Raster(*.adf *.asc)");

        if ( RasterFileName != nullptr)
        {
            Check_SnowCoverFileorValue(RasterFileName);

            pushButtonSetFocus();
        }

    } catch (...) {
        qDebug() << "Error: AttDataFile::on_pushButtonSnowCoverFile_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button SurfaceStorage Clicked Event (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::on_pushButtonSurfaceStorageFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile::on_pushButtonSurfaceStorageFile_clicked()";

    try {

        Clear_Log();

        QString RasterFileName = QFileDialog::getOpenFileName(this, "Surface-water Raster", user_pihmgis_root_folder, "Surface-water Raster(*.adf *.asc)");

        if ( RasterFileName != nullptr)
        {
            Check_SurfaceStorageFileorValue(RasterFileName);

            pushButtonSetFocus();
        }

    } catch (...) {
        qDebug() << "Error: AttDataFile::on_pushButtonSurfaceStorageFile_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button SoilMoisture Clicked Event (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::on_pushButtonSoilMoistureFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile::on_pushButtonSoilMoistureFile_clicked()";

    try {

        Clear_Log();

        QString RasterFileName = QFileDialog::getOpenFileName(this, "Soil Moisture Raster", user_pihmgis_root_folder, "Soil Moisture Raster(*.adf *.asc)");

        if ( RasterFileName != nullptr)
        {
            Check_SoilMoistureFileorValue(RasterFileName);

            pushButtonSetFocus();
        }

    } catch (...) {
        qDebug() << "Error: AttDataFile::on_pushButtonSoilMoistureFile_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button Groundwater Clicked Event (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::on_pushButtonGroundwaterFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile::on_pushButtonGroundwaterFile_clicked()";

    try {

        Clear_Log();

        QString RasterFileName = QFileDialog::getOpenFileName(this, "Groundwater Raster", user_pihmgis_root_folder, "Groundwater Raster(*.adf *.asc)");

        if ( RasterFileName != nullptr)
        {
            Check_GroundwaterFileorValue(RasterFileName);

            pushButtonSetFocus();
        }

    } catch (...) {
        qDebug() << "Error: AttDataFile::on_pushButtonGroundwaterFile_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button BoundaryConditionFile Clicked Event (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::on_pushButtonBoundaryConditionFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile::on_pushButtonBoundaryConditionFile_clicked()";

    try {

        Clear_Log();

        QString RasterFileName = QFileDialog::getOpenFileName(this, "Boundary Condition Raster", user_pihmgis_root_folder, "Boundary Condition Raster(*.adf *.asc)");

        if ( RasterFileName != nullptr)
        {
            Check_BoundaryConditionFileorValue(RasterFileName);

            pushButtonSetFocus();
        }


    } catch (...) {
        qDebug() << "Error: AttDataFile::on_pushButtonBoundaryConditionFile_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button TINShapeLayer Clicked Event (OUTPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::on_pushButtonTINShapeLayerFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile::on_pushButtonTINShapeLayerFile_clicked()";

    try {

        Clear_Log();

        QString RasterFileName = QFileDialog::getOpenFileName(this, "TIN Shape Layer", user_pihmgis_root_folder+"/3DomainDecomposition/", "TIN Shape Layer(*.shp *.SHP)");

        if ( RasterFileName != nullptr)
        {
            Check_TINShape_Input(RasterFileName);

            pushButtonSetFocus();
        }

    } catch (...) {
        qDebug() << "Error: AttDataFile::on_pushButtonTINShapeLayerFile_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Browse Button TINShapeLayer Clicked Event (OUTPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::on_pushButtonAttDataFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile::on_pushButtonAttDataFile_clicked()";

    try {

        Clear_Log();

        QString DataFileName = QFileDialog::getSaveFileName(this, "Choose Att Data File Name", user_pihmgis_root_folder+"/4DataModelLoader","Att Data File(*.att)");
        QString tempString = DataFileName;
        if ( DataFileName != nullptr)
        {
            if( ! (tempString.toLower()).endsWith(".att") )
            {
                tempString.append(".att");
                DataFileName = tempString;
            }
            Check_Att_Output(DataFileName, true);

            pushButtonSetFocus();
        }

    } catch (...) {
        qDebug() << "Error: AttDataFile::on_pushButtonAttDataFile_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to switch betweem File Browse and Int Value for Precipitation
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::on_checkBoxPrecipitation_toggled(bool checked)
{

    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile::on_checkBoxPrecipitation_toggled()";

    try {
        if ( checked == true )
        {
            ui->textLabelPrecipitation->setTextFormat(Qt::RichText);
            ui->textLabelPrecipitation->setText(QString("<html><head/><body><p>Precipitation <span style=\" vertical-align:super;\">1</span></p></body></html>"));
            ui->lineEditPrecipitationFile->setFixedWidth(input_width_two);
            ui->lineEditPrecipitationFile->setValidator( new QIntValidator(0,1,this) );
            ui->pushButtonPrecipitationFile->setDisabled(true);
            ui->lineEditPrecipitationFile->setText("1"); //Reset to default value
        }
        else
        {
            ui->textLabelPrecipitation->setTextFormat(Qt::RichText);
            ui->textLabelPrecipitation->setText(QString("<html><head/><body><p>Precipitation <span style=\" vertical-align:super;\">2</span></p></body></html>"));
            ui->lineEditPrecipitationFile->setFixedWidth(input_width_one);
            ui->lineEditPrecipitationFile->setValidator( new QRegExpValidator );
            ui->pushButtonPrecipitationFile->setDisabled(false);
            ui->lineEditPrecipitationFile->setText("");
        }

        ui->lineEditPrecipitationFile->setStyleSheet("color: black;");
    } catch (...) {
        qDebug() << "Error: AttDataFile::on_checkBoxPrecipitation_toggled() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to switch betweem File Browse and Int Value for Temperature
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::on_checkBoxTemperature_toggled(bool checked)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile::on_checkBoxTemperature_toggled()";

    try {
        if ( checked == true )
        {
            ui->textLabelTemperature->setTextFormat(Qt::RichText);
            ui->textLabelTemperature->setText(QString("<html><head/><body><p>Temperature <span style=\" vertical-align:super;\">1</span></p></body></html>"));
            ui->lineEditTemperatureFile->setFixedWidth(input_width_two);
            ui->lineEditTemperatureFile->setValidator( new QIntValidator(0,1,this) );
            ui->pushButtonTemperatureFile->setDisabled(true);
            ui->lineEditTemperatureFile->setText("1"); //Reset to default value
        }
        else
        {
            ui->textLabelTemperature->setTextFormat(Qt::RichText);
            ui->textLabelTemperature->setText(QString("<html><head/><body><p>Temperature <span style=\" vertical-align:super;\">2</span></p></body></html>"));
            ui->lineEditTemperatureFile->setFixedWidth(input_width_one);
            ui->lineEditTemperatureFile->setValidator( new QRegExpValidator );
            ui->pushButtonTemperatureFile->setDisabled(false);
            ui->lineEditTemperatureFile->setText(""); //Reset to default value
        }

        ui->lineEditTemperatureFile->setStyleSheet("color: black;");
    } catch (...) {
        qDebug() << "Error: AttDataFile::on_checkBoxTemperature_toggled() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to switch betweem File Browse and Int Value for RelativeHumidity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::on_checkBoxRelativeHumidity_toggled(bool checked)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile::on_checkBoxRelativeHumidity_toggled()";

    try {
        if ( checked == true )
        {
            ui->textLabelRelativeHumidity->setTextFormat(Qt::RichText);
            ui->textLabelRelativeHumidity->setText(QString("<html><head/><body><p>Relative Humidity <span style=\" vertical-align:super;\">1</span></p></body></html>"));
            ui->lineEditRelativeHumidityFile->setFixedWidth(input_width_two);
            ui->lineEditRelativeHumidityFile->setValidator( new QIntValidator(0,1,this) );
            ui->pushButtonRelativeHumidityFile->setDisabled(true);
            ui->lineEditRelativeHumidityFile->setText("1"); //Reset to default value
        }
        else
        {
            ui->textLabelRelativeHumidity->setTextFormat(Qt::RichText);
            ui->textLabelRelativeHumidity->setText(QString("<html><head/><body><p>Relative Humidity <span style=\" vertical-align:super;\">2</span></p></body></html>"));
            ui->lineEditRelativeHumidityFile->setFixedWidth(input_width_one);
            ui->lineEditRelativeHumidityFile->setValidator( new QRegExpValidator );
            ui->pushButtonRelativeHumidityFile->setDisabled(false);
            ui->lineEditRelativeHumidityFile->setText(""); //Reset to default value
        }

        ui->lineEditRelativeHumidityFile->setStyleSheet("color: black;");
    } catch (...) {
        qDebug() << "Error: AttDataFile::on_checkBoxRelativeHumidity_toggled() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to switch betweem File Browse and Int Value for WindVelocity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::on_checkBoxWindVelocity_toggled(bool checked)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile::on_checkBoxWindVelocity_toggled()";

    try {
        if ( checked == true )
        {
            ui->textLabelWindVelocity->setTextFormat(Qt::RichText);
            ui->textLabelWindVelocity->setText(QString("<html><head/><body><p>Wind Velocity <span style=\" vertical-align:super;\">1</span></p></body></html>"));
            ui->lineEditWindVelocityFile->setFixedWidth(input_width_two);
            ui->lineEditWindVelocityFile->setValidator( new QIntValidator(0,1,this) );
            ui->pushButtonWindVelocityFile->setDisabled(true);
            ui->lineEditWindVelocityFile->setText("1"); //Reset to default value
        }
        else
        {
            ui->textLabelWindVelocity->setTextFormat(Qt::RichText);
            ui->textLabelWindVelocity->setText(QString("<html><head/><body><p>Wind Velocity <span style=\" vertical-align:super;\">2</span></p></body></html>"));
            ui->lineEditWindVelocityFile->setFixedWidth(input_width_one);
            ui->lineEditWindVelocityFile->setValidator( new QRegExpValidator );
            ui->pushButtonWindVelocityFile->setDisabled(false);
            ui->lineEditWindVelocityFile->setText(""); //Reset to default value
        }
        ui->lineEditWindVelocityFile->setStyleSheet("color: black;");
    } catch (...) {
        qDebug() << "Error: AttDataFile::on_checkBoxWindVelocity_toggled() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to switch betweem File Browse and Int Value for SolarRadiation
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::on_checkBoxSolarRadiation_toggled(bool checked)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile::on_checkBoxSolarRadiation_toggled()";

    try {
        if ( checked == true )
        {
            ui->textLabelSolarRadiation->setTextFormat(Qt::RichText);
            ui->textLabelSolarRadiation->setText(QString("<html><head/><body><p>Solar Radiation <span style=\" vertical-align:super;\">1</span></p></body></html>"));
            ui->lineEditSolarRadiationFile->setFixedWidth(input_width_two);
            ui->lineEditSolarRadiationFile->setValidator( new QIntValidator(0,1,this) );
            ui->pushButtonSolarRadiationFile->setDisabled(true);
            ui->lineEditSolarRadiationFile->setText("1"); //Reset to default value
        }
        else
        {
            ui->textLabelSolarRadiation->setTextFormat(Qt::RichText);
            ui->textLabelSolarRadiation->setText(QString("<html><head/><body><p>Solar Radiation <span style=\" vertical-align:super;\">2</span></p></body></html>"));
            ui->lineEditSolarRadiationFile->setFixedWidth(input_width_one);
            ui->lineEditSolarRadiationFile->setValidator( new QRegExpValidator );
            ui->pushButtonSolarRadiationFile->setDisabled(false);
            ui->lineEditSolarRadiationFile->setText(""); //Reset to default value
        }
        ui->lineEditSolarRadiationFile->setStyleSheet("color: black;");
    } catch (...) {
        qDebug() << "Error: AttDataFile::on_checkBoxSolarRadiation_toggled() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to switch betweem File Browse and Int Value for VaporPressure
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::on_checkBoxVaporPressure_toggled(bool checked)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile::on_checkBoxVaporPressure_toggled()";

    try {
        if ( checked == true )
        {
            ui->textLabelVaporPressure->setTextFormat(Qt::RichText);
            ui->textLabelVaporPressure->setText(QString("<html><head/><body><p>Vapor Pressure <span style=\" vertical-align:super;\">1</span></p></body></html>"));
            ui->lineEditVaporPressureFile->setFixedWidth(input_width_two);
            ui->lineEditVaporPressureFile->setValidator( new QIntValidator(0,1,this) );
            ui->pushButtonVaporPressureFile->setDisabled(true);
            ui->lineEditVaporPressureFile->setText("1"); //Reset to default value
        }
        else
        {
            ui->textLabelVaporPressure->setTextFormat(Qt::RichText);
            ui->textLabelVaporPressure->setText(QString("<html><head/><body><p>Vapor Pressure <span style=\" vertical-align:super;\">2</span></p></body></html>"));
            ui->lineEditVaporPressureFile->setFixedWidth(input_width_one);
            ui->lineEditVaporPressureFile->setValidator( new QRegExpValidator );
            ui->pushButtonVaporPressureFile->setDisabled(false);
            ui->lineEditVaporPressureFile->setText(""); //Reset to default value
        }
        ui->lineEditVaporPressureFile->setStyleSheet("color: black;");
    } catch (...) {
        qDebug() << "Error: AttDataFile::on_checkBoxVaporPressure_toggled() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to switch betweem File Browse and Int Value for SoilClasses
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::on_checkBoxSoilClasses_toggled(bool checked)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile::on_checkBoxSoilClasses_toggled()";

    try {
        if ( checked == true )
        {
            ui->textLabelSoilClasses->setTextFormat(Qt::RichText);
            ui->textLabelSoilClasses->setText(QString("<html><head/><body><p>Soil Classes <span style=\" vertical-align:super;\">1</span></p></body></html>"));
            ui->lineEditSoilClassesFile->setFixedWidth(input_width_two);
            ui->lineEditSoilClassesFile->setValidator( new QIntValidator(0,1,this) );
            ui->pushButtonSoilClassesFile->setDisabled(true);
            ui->lineEditSoilClassesFile->setText("1"); //Reset to default value
        }
        else
        {
            ui->textLabelSoilClasses->setTextFormat(Qt::RichText);
            ui->textLabelSoilClasses->setText(QString("<html><head/><body><p>Soil Classes <span style=\" vertical-align:super;\">2</span></p></body></html>"));
            ui->lineEditSoilClassesFile->setFixedWidth(input_width_one);
            ui->lineEditSoilClassesFile->setValidator( new QRegExpValidator );
            ui->pushButtonSoilClassesFile->setDisabled(false);
            ui->lineEditSoilClassesFile->setText(""); //Reset to default value
        }
        ui->lineEditSoilClassesFile->setStyleSheet("color: black;");
    } catch (...) {
        qDebug() << "Error: AttDataFile::on_checkBoxSoilClasses_toggled() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to switch betweem File Browse and Int Value for GeologyClasses
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::on_checkBoxGeologyClasses_toggled(bool checked)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile::on_checkBoxGeologyClasses_toggled()";

    try {
        if ( checked == true )
        {
            ui->textLabelGeologyClasses->setTextFormat(Qt::RichText);
            ui->textLabelGeologyClasses->setText(QString("<html><head/><body><p>Geology Classes <span style=\" vertical-align:super;\">1</span></p></body></html>"));
            ui->lineEditGeologyClassesFile->setFixedWidth(input_width_two);
            ui->lineEditGeologyClassesFile->setValidator( new QIntValidator(0,1,this) );
            ui->pushButtonGeologyClassesFile->setDisabled(true);
            ui->lineEditGeologyClassesFile->setText("1"); //Reset to default value
        }
        else
        {
            ui->textLabelGeologyClasses->setTextFormat(Qt::RichText);
            ui->textLabelGeologyClasses->setText(QString("<html><head/><body><p>Geology Classes <span style=\" vertical-align:super;\">2</span></p></body></html>"));
            ui->lineEditGeologyClassesFile->setFixedWidth(input_width_one);
            ui->lineEditGeologyClassesFile->setValidator( new QRegExpValidator );
            ui->pushButtonGeologyClassesFile->setDisabled(false);
            ui->lineEditGeologyClassesFile->setText(""); //Reset to default value
        }
        ui->lineEditGeologyClassesFile->setStyleSheet("color: black;");
    } catch (...) {
        qDebug() << "Error: AttDataFile::on_checkBoxGeologyClasses_toggled() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to switch betweem File Browse and Int Value for Macropores
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::on_checkBoxMacropores_toggled(bool checked)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile::on_checkBoxMacropores_toggled()";

    try {
        if ( checked == true )
        {
            ui->textLabelMacropores->setTextFormat(Qt::RichText);
            ui->textLabelMacropores->setText(QString("<html><head/><body><p>Macropores <span style=\" vertical-align:super;\">1</span></p></body></html>"));
            ui->lineEditMacroporesFile->setFixedWidth(input_width_two);
            ui->lineEditMacroporesFile->setValidator( new QIntValidator(0,1,this) );
            ui->pushButtonMacroporesFile->setDisabled(true);
            ui->lineEditMacroporesFile->setText("1"); //Reset to default value
        }
        else
        {
            ui->textLabelMacropores->setTextFormat(Qt::RichText);
            ui->textLabelMacropores->setText(QString("<html><head/><body><p>Macropores <span style=\" vertical-align:super;\">2</span></p></body></html>"));
            ui->lineEditMacroporesFile->setFixedWidth(input_width_one);
            ui->lineEditMacroporesFile->setValidator( new QRegExpValidator );
            ui->pushButtonMacroporesFile->setDisabled(false);
            ui->lineEditMacroporesFile->setText(""); //Reset to default value
        }
        ui->lineEditMacroporesFile->setStyleSheet("color: black;");
    } catch (...) {
        qDebug() << "Error: AttDataFile::on_checkBoxMacropores_toggled() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to switch betweem File Browse and Int Value for LandCover
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::on_checkBoxLandCoverClasses_toggled(bool checked)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile::on_checkBoxLandCoverClasses_toggled()";

    try {
        if ( checked == true )
        {
            ui->textLabelLandCoverClasses->setTextFormat(Qt::RichText);
            ui->textLabelLandCoverClasses->setText(QString("<html><head/><body><p>Land-cover Classes <span style=\" vertical-align:super;\">1</span></p></body></html>"));
            ui->lineEditLandCoverClassesFile->setFixedWidth(input_width_two);
            ui->lineEditLandCoverClassesFile->setValidator( new QIntValidator(0,1,this) );
            ui->pushButtonLandCoverClassesFile->setDisabled(true);
            ui->lineEditLandCoverClassesFile->setText("1"); //Reset to default value
        }
        else
        {
            ui->textLabelLandCoverClasses->setTextFormat(Qt::RichText);
            ui->textLabelLandCoverClasses->setText(QString("<html><head/><body><p>Land-cover Classes <span style=\" vertical-align:super;\">2</span></p></body></html>"));
            ui->lineEditLandCoverClassesFile->setFixedWidth(input_width_one);
            ui->lineEditLandCoverClassesFile->setValidator( new QRegExpValidator );
            ui->pushButtonLandCoverClassesFile->setDisabled(false);
            ui->lineEditLandCoverClassesFile->setText(""); //Reset to default value
        }
        ui->lineEditLandCoverClassesFile->setStyleSheet("color: black;");

    } catch (...) {
        qDebug() << "Error: AttDataFile::on_checkBoxLandCoverClasses_toggled() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to switch betweem File Browse and Int Value for MeltRegions
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::on_checkBoxMeltRegions_toggled(bool checked)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile::on_checkBoxMeltRegions_toggled()";

    try {

        if ( checked == true )
        {
            ui->textLabelMeltRegions->setTextFormat(Qt::RichText);
            ui->textLabelMeltRegions->setText(QString("<html><head/><body><p>Melt Regions <span style=\" vertical-align:super;\">1</span></p></body></html>"));
            ui->lineEditMeltRegionsFile->setFixedWidth(input_width_two);
            ui->lineEditMeltRegionsFile->setValidator( new QIntValidator(0,1,this) );
            ui->pushButtonMeltRegionsFile->setDisabled(true);
            ui->lineEditMeltRegionsFile->setText("1"); //Reset to default value
        }
        else
        {
            ui->textLabelMeltRegions->setTextFormat(Qt::RichText);
            ui->textLabelMeltRegions->setText(QString("<html><head/><body><p>Melt Regions <span style=\" vertical-align:super;\">2</span></p></body></html>"));
            ui->lineEditMeltRegionsFile->setFixedWidth(input_width_one);
            ui->lineEditMeltRegionsFile->setValidator( new QRegExpValidator );
            ui->pushButtonMeltRegionsFile->setDisabled(false);
            ui->lineEditMeltRegionsFile->setText(""); //Reset to default value
        }
        ui->lineEditMeltRegionsFile->setStyleSheet("color: black;");

    } catch (...) {
        qDebug() << "Error: AttDataFile::on_checkBoxMeltRegions_toggled() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to switch betweem File Browse and Int Value for SourcesSinks
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::on_checkBoxSourcesSinks_toggled(bool checked)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile::on_checkBoxSourcesSinks_toggled()";

    try {
        if ( checked == true )
        {
            ui->textLabelSourcesSinks->setTextFormat(Qt::RichText);
            ui->textLabelSourcesSinks->setText(QString("<html><head/><body><p>Sources-Sinks <span style=\" vertical-align:super;\">1</span></p></body></html>"));
            ui->lineEditSourcesSinksFile->setFixedWidth(input_width_two);
            ui->lineEditSourcesSinksFile->setValidator( new QIntValidator(0,1,this) );
            ui->pushButtonSourcesSinksFile->setDisabled(true);
            ui->lineEditSourcesSinksFile->setText("0"); //Reset to default value
        }
        else
        {
            ui->textLabelSourcesSinks->setTextFormat(Qt::RichText);
            ui->textLabelSourcesSinks->setText(QString("<html><head/><body><p>Sources-Sinks <span style=\" vertical-align:super;\">2</span></p></body></html>"));
            ui->lineEditSourcesSinksFile->setFixedWidth(input_width_one);
            ui->lineEditSourcesSinksFile->setValidator( new QRegExpValidator );
            ui->pushButtonSourcesSinksFile->setDisabled(false);
            ui->lineEditSourcesSinksFile->setText(""); //Reset to default value
        }
        ui->lineEditSourcesSinksFile->setStyleSheet("color: black;");
    } catch (...) {
        qDebug() << "Error: AttDataFile::on_checkBoxSourcesSinks_toggled() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to switch betweem File Browse and Int Value for Interception
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::on_checkBoxInterception_toggled(bool checked)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile::on_checkBoxInterception_toggled()";

    try {
        if ( checked == true )
        {
            ui->textLabelInterception->setTextFormat(Qt::RichText);
            ui->textLabelInterception->setText(QString("<html><head/><body><p>Interception (m) <span style=\" vertical-align:super;\">3</span></p></body></html>"));
            ui->lineEditInterceptionFile->setFixedWidth(input_width_two);
            ui->lineEditInterceptionFile->setValidator( new QDoubleValidator(0.0,100.0,4,this) );
            ui->pushButtonInterceptionFile->setDisabled(true);
            ui->lineEditInterceptionFile->setText("0"); //Reset to default value
        }
        else
        {
            ui->textLabelInterception->setTextFormat(Qt::RichText);
            ui->textLabelInterception->setText(QString("<html><head/><body><p>Interception (m) <span style=\" vertical-align:super;\">3</span></p></body></html>"));
            ui->lineEditInterceptionFile->setFixedWidth(input_width_one);
            ui->lineEditInterceptionFile->setValidator( new QRegExpValidator );
            ui->pushButtonInterceptionFile->setDisabled(false);
            ui->lineEditInterceptionFile->setText(""); //Reset to default value
        }
        ui->lineEditInterceptionFile->setStyleSheet("color: black;");
    } catch (...) {
        qDebug() << "Error: AttDataFile::on_checkBoxInterception_toggled() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to switch betweem File Browse and Int Value for SnowCover
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::on_checkBoxSnowCover_toggled(bool checked)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile::on_checkBoxSnowCover_toggled()";

    try {
        if ( checked == true )
        {
            ui->textLabelSnowCover->setTextFormat(Qt::RichText);
            ui->textLabelSnowCover->setText(QString("<html><head/><body><p>Snow Cover (m) <span style=\" vertical-align:super;\">3</span></p></body></html>"));
            ui->lineEditSnowCoverFile->setFixedWidth(input_width_two);
            ui->lineEditSnowCoverFile->setValidator( new QDoubleValidator(0.0,100.0,4,this) );
            ui->pushButtonSnowCoverFile->setDisabled(true);
            ui->lineEditSnowCoverFile->setText("0"); //Reset to default value
        }
        else
        {
            ui->textLabelSnowCover->setTextFormat(Qt::RichText);
            ui->textLabelSnowCover->setText(QString("<html><head/><body><p>Snow Cover (m) <span style=\" vertical-align:super;\">3</span></p></body></html>"));
            ui->lineEditSnowCoverFile->setFixedWidth(input_width_one);
            ui->lineEditSnowCoverFile->setValidator( new QRegExpValidator );
            ui->pushButtonSnowCoverFile->setDisabled(false);
            ui->lineEditSnowCoverFile->setText(""); //Reset to default value
        }
        ui->lineEditSnowCoverFile->setStyleSheet("color: black;");
    } catch (...) {
        qDebug() << "Error: AttDataFile::on_checkBoxSnowCover_toggled() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to switch betweem File Browse and Int Value for SurfaceStorage
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::on_checkBoxSurfaceStorage_toggled(bool checked)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile::on_checkBoxSurfaceStorage_toggled()";

    try {
        if ( checked == true )
        {
            ui->textLabelSurfaceStorage->setTextFormat(Qt::RichText);
            ui->textLabelSurfaceStorage->setText(QString("<html><head/><body><p>Surface water (m) <span style=\" vertical-align:super;\">3</span></p></body></html>"));
            ui->lineEditSurfaceStorageFile->setFixedWidth(input_width_two);
            ui->lineEditSurfaceStorageFile->setValidator( new QDoubleValidator(0.0,100.0,4,this) );
            ui->pushButtonSurfaceStorageFile->setDisabled(true);
            ui->lineEditSurfaceStorageFile->setText("0"); //Reset to default value
        }
        else
        {
            ui->textLabelSurfaceStorage->setTextFormat(Qt::RichText);
            ui->textLabelSurfaceStorage->setText(QString("<html><head/><body><p>Surface water (m) <span style=\" vertical-align:super;\">3</span></p></body></html>"));
            ui->lineEditSurfaceStorageFile->setFixedWidth(input_width_one);
            ui->lineEditSurfaceStorageFile->setValidator( new QRegExpValidator );
            ui->pushButtonSurfaceStorageFile->setDisabled(false);
            ui->lineEditSurfaceStorageFile->setText(""); //Reset to default value
        }
        ui->lineEditSurfaceStorageFile->setStyleSheet("color: black;");
    } catch (...) {
        qDebug() << "Error: AttDataFile::on_checkBoxSurfaceStorage_toggled() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to switch betweem File Browse and Int Value for SoilMoisture
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::on_checkBoxSoilMoisture_toggled(bool checked)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile::on_checkBoxSoilMoisture_toggled()";

    try {
        if ( checked == true )
        {
            ui->textLabelSoilMoisture->setTextFormat(Qt::RichText);
            ui->textLabelSoilMoisture->setText(QString("<html><head/><body><p>Soil Moisture (m) <span style=\" vertical-align:super;\">3</span></p></body></html>"));
            ui->lineEditSoilMoistureFile->setFixedWidth(input_width_two);
            ui->lineEditSoilMoistureFile->setValidator( new QDoubleValidator(0.0,100.0,4,this) );
            ui->pushButtonSoilMoistureFile->setDisabled(true);
            ui->lineEditSoilMoistureFile->setText("0"); //Reset to default value
        }
        else
        {
            ui->textLabelSoilMoisture->setTextFormat(Qt::RichText);
            ui->textLabelSoilMoisture->setText(QString("<html><head/><body><p>Soil Moisture (m) <span style=\" vertical-align:super;\">3</span></p></body></html>"));
            ui->lineEditSoilMoistureFile->setFixedWidth(input_width_one);
            ui->lineEditSoilMoistureFile->setValidator( new QRegExpValidator );
            ui->pushButtonSoilMoistureFile->setDisabled(false);
            ui->lineEditSoilMoistureFile->setText(""); //Reset to default value
        }
        ui->lineEditSoilMoistureFile->setStyleSheet("color: black;");
    } catch (...) {
        qDebug() << "Error: AttDataFile::on_checkBoxSoilMoisture_toggled() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to switch betweem File Browse and Int Value for Groundwater
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::on_checkBoxGroundwater_toggled(bool checked)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile::on_checkBoxGroundwater_toggled()";

    try {
        if ( checked == true )
        {
            ui->textLabelGroundwater->setTextFormat(Qt::RichText);
            ui->textLabelGroundwater->setText(QString("<html><head/><body><p>Groundwater (m) <span style=\" vertical-align:super;\">3</span></p></body></html>"));
            ui->lineEditGroundwaterFile->setFixedWidth(input_width_two);
            ui->lineEditGroundwaterFile->setValidator( new QDoubleValidator(0.0,100.0,4,this) );
            ui->pushButtonGroundwaterFile->setDisabled(true);
            ui->lineEditGroundwaterFile->setText("0"); //Reset to default value
        }
        else
        {
            ui->textLabelGroundwater->setTextFormat(Qt::RichText);
            ui->textLabelGroundwater->setText(QString("<html><head/><body><p>Groundwater (m) <span style=\" vertical-align:super;\">3</span></p></body></html>"));
            ui->lineEditGroundwaterFile->setFixedWidth(input_width_one);
            ui->lineEditGroundwaterFile->setValidator( new QRegExpValidator );
            ui->pushButtonGroundwaterFile->setDisabled(false);
            ui->lineEditGroundwaterFile->setText(""); //Reset to default value
        }
        ui->lineEditGroundwaterFile->setStyleSheet("color: black;");
    } catch (...) {
        qDebug() << "Error: AttDataFile::on_checkBoxGroundwater_toggled() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to switch betweem File Browse and Int Value for BoundaryCondition
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::on_checkBoxBoundaryCondition_toggled(bool checked)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile::on_checkBoxBoundaryCondition_toggled()";

    try {
        if ( checked == true )
        {
            ui->textLabelBoundaryCondition->setTextFormat(Qt::RichText);
            ui->textLabelBoundaryCondition->setText(QString("<html><head/><body><p>Boundary Condition <span style=\" vertical-align:super;\">1</span></p></body></html>"));
            ui->lineEditBoundaryConditionFile->setFixedWidth(input_width_two);
            ui->lineEditBoundaryConditionFile->setValidator( new QIntValidator(0,1,this) );
            ui->pushButtonBoundaryConditionFile->setDisabled(true);
            ui->lineEditBoundaryConditionFile->setText("0"); //Reset to default value
        }
        else
        {
            ui->textLabelBoundaryCondition->setTextFormat(Qt::RichText);
            ui->textLabelBoundaryCondition->setText(QString("<html><head/><body><p>Boundary Condition <span style=\" vertical-align:super;\">2</span></p></body></html>"));
            ui->lineEditBoundaryConditionFile->setFixedWidth(input_width_one);
            ui->lineEditBoundaryConditionFile->setValidator( new QRegExpValidator );
            ui->pushButtonBoundaryConditionFile->setDisabled(false);
            ui->lineEditBoundaryConditionFile->setText(""); //Reset to default value
        }
        ui->lineEditBoundaryConditionFile->setStyleSheet("color: black;");
    } catch (...) {
        qDebug() << "Error: AttDataFile::on_checkBoxBoundaryCondition_toggled() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check entered value for PrecipitationFile
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::on_lineEditPrecipitationFile_textChanged(const QString &arg1)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile::on_lineEditPrecipitationFile_textChanged()";

    try {
        if(finished_loading_files)
            Check_PrecipitationFileorValue(arg1);
    } catch (...) {
        qDebug() << "Error: AttDataFile::on_lineEditPrecipitationFile_textChanged() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check entered value for TemperatureFile
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::on_lineEditTemperatureFile_textChanged(const QString &arg1)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile::on_lineEditTemperatureFile_textChanged()";

    try {
        if(finished_loading_files)
            Check_TemperatureFileorValue(arg1);
    } catch (...) {
        qDebug() << "Error: AttDataFile::on_lineEditTemperatureFile_textChanged() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check entered value for RelativeHumidity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::on_lineEditRelativeHumidityFile_textChanged(const QString &arg1)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile::on_lineEditRelativeHumidityFile_textChanged()";

    try {
        if(finished_loading_files)
            Check_RelativeHumidityFileorValue(arg1);
    } catch (...) {
        qDebug() << "Error: AttDataFile::on_lineEditRelativeHumidityFile_textChanged() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check entered value for WindVelocity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::on_lineEditWindVelocityFile_textChanged(const QString &arg1)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile::on_lineEditWindVelocityFile_textChanged()";

    try {
        if(finished_loading_files)
            Check_RelativeHumidityFileorValue(arg1);
    } catch (...) {
        qDebug() << "Error: AttDataFile::on_lineEditWindVelocityFile_textChanged() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check entered value for SolarRadiationFile
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::on_lineEditSolarRadiationFile_textChanged(const QString &arg1)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile::on_lineEditSolarRadiationFile_textChanged()";

    try {
        if(finished_loading_files)
            Check_SolarRadiationFileorValue(arg1);
    } catch (...) {
        qDebug() << "Error: AttDataFile::on_lineEditSolarRadiationFile_textChanged() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to switch betweem File Browse and Int Value for VaporPressure
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::on_lineEditVaporPressureFile_textChanged(const QString &arg1)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile::on_lineEditVaporPressureFile_textChanged()";

    try {
        if(finished_loading_files)
            Check_VaporPressureFileorValue(arg1);
    } catch (...) {
        qDebug() << "Error: AttDataFile::on_lineEditVaporPressureFile_textChanged() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check entered value for SoilClasses
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::on_lineEditSoilClassesFile_textChanged(const QString &arg1)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile::on_lineEditSoilClassesFile_textChanged()";

    try {
        if(finished_loading_files)
            Check_SoilClassesFileorValue(arg1);
    } catch (...) {
        qDebug() << "Error: AttDataFile::on_lineEditSoilClassesFile_textChanged() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check entered value for GeologyClasse
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::on_lineEditGeologyClassesFile_textChanged(const QString &arg1)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile::on_lineEditGeologyClassesFile_textChanged()";

    try {
        if(finished_loading_files)
            Check_GeologyClassesFileorValue(arg1);
    } catch (...) {
        qDebug() << "Error: AttDataFile::on_lineEditGeologyClassesFile_textChanged() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check entered value for Macropores
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::on_lineEditMacroporesFile_textChanged(const QString &arg1)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile::on_lineEditMacroporesFile_textChanged()";

    try {
        if(finished_loading_files)
            Check_MacroporesFileorValue(arg1);
    } catch (...) {
        qDebug() << "Error: AttDataFile::on_lineEditMacroporesFile_textChanged() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check entered value for LandCoverClasses
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::on_lineEditLandCoverClassesFile_textChanged(const QString &arg1)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile::on_lineEditLandCoverClassesFile_textChanged()";

    try {
        if(finished_loading_files)
            Check_LandCoverClassesFileorValue(arg1);
    } catch (...) {
        qDebug() << "Error: AttDataFile::on_lineEditLandCoverClassesFile_textChanged() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check entered value for MeltRegions
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::on_lineEditMeltRegionsFile_textChanged(const QString &arg1)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile::on_lineEditMeltRegionsFile_textChanged()";

    try {
        if(finished_loading_files)
            Check_MeltRegionsFileorValue(arg1);
    } catch (...) {
        qDebug() << "Error: AttDataFile::on_lineEditMeltRegionsFile_textChanged() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check entered value for SourcesSinks
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::on_lineEditSourcesSinksFile_textChanged(const QString &arg1)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile::on_lineEditSourcesSinksFile_textChanged()";

    try {
        if(finished_loading_files)
            Check_SourcesSinksFileorValue(arg1);
    } catch (...) {
        qDebug() << "Error: AttDataFile::on_lineEditSourcesSinksFile_textChanged() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check entered value for Interception
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::on_lineEditInterceptionFile_textChanged(const QString &arg1)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile::on_lineEditInterceptionFile_textChanged()";

    try {
        if(finished_loading_files)
            Check_InterceptionFileorValue(arg1);
    } catch (...) {
        qDebug() << "Error: AttDataFile::on_lineEditInterceptionFile_textChanged() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check entered value for SnowCover
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::on_lineEditSnowCoverFile_textChanged(const QString &arg1)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile::on_lineEditSnowCoverFile_textChanged()";

    try {
        if(finished_loading_files)
            Check_SnowCoverFileorValue(arg1);
    } catch (...) {
        qDebug() << "Error: AttDataFile::on_lineEditSnowCoverFile_textChanged() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check entered value for SurfaceStorage
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::on_lineEditSurfaceStorageFile_textChanged(const QString &arg1)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile::on_lineEditSurfaceStorageFile_textChanged()";

    try {
        if(finished_loading_files)
            Check_SurfaceStorageFileorValue(arg1);
    } catch (...) {
        qDebug() << "Error: AttDataFile::on_lineEditSurfaceStorageFile_textChanged() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check entered value for SoilMoisture
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::on_lineEditSoilMoistureFile_textChanged(const QString &arg1)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile::on_lineEditSoilMoistureFile_textChanged()";

    try {
        if(finished_loading_files)
            Check_SoilMoistureFileorValue(arg1);
    } catch (...) {
        qDebug() << "Error: AttDataFile::on_lineEditSoilMoistureFile_textChanged() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check entered value for Groundwater
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::on_lineEditGroundwaterFile_textChanged(const QString &arg1)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile::on_lineEditGroundwaterFile_textChanged()";

    try {
        if(finished_loading_files)
            Check_GroundwaterFileorValue(arg1);
    } catch (...) {
        qDebug() << "Error: AttDataFile::on_lineEditGroundwaterFile_textChanged() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check entered value for BoundaryCondition
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::on_lineEditBoundaryConditionFile_textChanged(const QString &arg1)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile::on_lineEditBoundaryConditionFile_textChanged()";

    try {
        if(finished_loading_files)
            Check_BoundaryConditionFileorValue(arg1);
    } catch (...) {
        qDebug() << "Error: AttDataFile::on_lineEditBoundaryConditionFile_textChanged() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check entered value for TINShape
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::on_lineEditTINShapeLayerFile_textChanged(const QString &arg1)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile::on_lineEditTINShapeLayerFile_textChanged()";

    try {
        if(finished_loading_files)
            Check_TINShape_Input(arg1);
    } catch (...) {
        qDebug() << "Error: AttDataFile::on_lineEditTINShapeLayerFile_textChanged() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check entered value for Att OUTPUT
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::on_lineEditAttDataFile_textChanged(const QString &arg1)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile::on_lineEditAttDataFile_textChanged()";

    try {
        if(finished_loading_files)
            Check_Att_Output(arg1, true);
    } catch (...) {
        qDebug() << "Error: AttDataFile::on_lineEditAttDataFile_textChanged() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check Log_Error_Message
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::Log_Warning_Message(QString message)
{
    try {
        LogsString.append(tr("<span style=\"color:#FF0000\">Warning: ") + message + " </span>")+tr("<br>");
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
// Run Button Clicked Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::on_pushButtonRun_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AttDataFile::on_pushButtonRun_clicked()";

    try {

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Clear Log
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Clear_Log();

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Get CheckBox Input Values
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool checked_PrecipitationFile  = ui->checkBoxPrecipitation->isChecked();
        bool checked_TemperatureFile  = ui->checkBoxTemperature->isChecked();
        bool checked_RelativeHumidityFile = ui->checkBoxRelativeHumidity->isChecked();
        bool checked_WindVelocityFile = ui->checkBoxWindVelocity->isChecked();
        bool checked_SolarRadiationFile = ui->checkBoxSolarRadiation->isChecked();
        bool checked_VaporPressureFile  = ui->checkBoxVaporPressure->isChecked();

        bool checked_SoilClassesFile  = ui->checkBoxSoilClasses->isChecked();
        bool checked_GeologyClassesFile = ui->checkBoxGeologyClasses->isChecked();
        bool checked_MacroporesFile = ui->checkBoxMacropores->isChecked();
        bool checked_LandCoverClassesFile = ui->checkBoxLandCoverClasses->isChecked();
        bool checked_MeltRegionsFile  = ui->checkBoxMeltRegions->isChecked();
        bool checked_SourcesSinksFile = ui->checkBoxSourcesSinks->isChecked();

        bool checked_InterceptionFile = ui->checkBoxInterception->isChecked();
        bool checked_SnowCoverFile = ui->checkBoxSnowCover->isChecked();
        bool checked_SurfaceStorageFile = ui->checkBoxSurfaceStorage->isChecked();
        bool checked_SoilMoistureFile = ui->checkBoxSoilMoisture->isChecked();
        bool checked_GroundwaterFile  = ui->checkBoxGroundwater->isChecked();
        bool checked_BoundaryConditionFile = ui->checkBoxBoundaryCondition->isChecked();

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check inputs and file access
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QString input_filename_TINShape_Input = ui->lineEditTINShapeLayerFile->text();
        bool checked_input = Check_TINShape_Input(input_filename_TINShape_Input);
        if(!checked_input)
        {
            Log_Error_Message("TINShape Input File or Value Missing " + input_filename_TINShape_Input );
            return;
        }
        if ( !CheckFileAccess(input_filename_TINShape_Input, "ReadOnly") )
        {
            Log_Error_Message("No Read Access to TINShape Input File or Value Missing " + input_filename_TINShape_Input );
            return;
        }

        QString input_filename_PrecipitationFile = ui->lineEditPrecipitationFile->text();
        checked_input = Check_PrecipitationFileorValue(input_filename_PrecipitationFile);
        if(!checked_input)
        {
            Log_Error_Message("Precipitation Input File or Value Missing " + input_filename_PrecipitationFile );
            return;
        }
        if ( !checked_PrecipitationFile )
        {
            if ( ! CheckFileAccess(input_filename_PrecipitationFile, "ReadOnly") )
            {
                Log_Error_Message("No Read Access to Precipitation Input File or Value Missing " + input_filename_PrecipitationFile );
                return;
            }
        }

        QString input_filename_TemperatureFile = ui->lineEditTemperatureFile->text();
        checked_input = Check_TemperatureFileorValue(input_filename_TemperatureFile);
        if(!checked_input)
        {
            Log_Error_Message("Temperature Input File or Value Missing " + input_filename_PrecipitationFile );
            return;
        }
        if ( !checked_TemperatureFile )
        {
            if ( ! CheckFileAccess(input_filename_TemperatureFile, "ReadOnly") )
            {
                Log_Error_Message("NO Read Access to Temperature Input File or Value Missing " + input_filename_TemperatureFile );
                return;
            }
        }

        QString input_filename_RelativeHumidityFile = ui->lineEditRelativeHumidityFile->text();
        checked_input = Check_RelativeHumidityFileorValue(input_filename_RelativeHumidityFile);
        if(!checked_input)
        {
            Log_Error_Message("RelativeHumidity Input File or Value Missing " + input_filename_RelativeHumidityFile );
            return;
        }
        if ( !checked_RelativeHumidityFile )
        {
            if ( ! CheckFileAccess(input_filename_RelativeHumidityFile, "ReadOnly") )
            {
                Log_Error_Message("NO Read Access to RelativeHumidity Input File or Value Missing " + input_filename_RelativeHumidityFile );
                return;
            }
        }

        QString input_filename_WindVelocityFile = ui->lineEditWindVelocityFile->text();
        checked_input = Check_WindVelocityFileorValue(input_filename_WindVelocityFile);
        if(!checked_input)
        {
            Log_Error_Message("WindVelocity Input File or Value Missing " + input_filename_WindVelocityFile );
            return;
        }
        if ( !checked_WindVelocityFile )
        {
            if ( ! CheckFileAccess(input_filename_WindVelocityFile, "ReadOnly") )
            {
                Log_Error_Message("NO Read Access to WindVelocity Input File or Value Missing " + input_filename_WindVelocityFile );
                return;
            }
        }

        QString input_filename_SolarRadiationFile = ui->lineEditSolarRadiationFile->text();
        checked_input = Check_SolarRadiationFileorValue(input_filename_SolarRadiationFile);
        if(!checked_input)
        {
            Log_Error_Message("SolarRadiation Input File or Value Missing " + input_filename_SolarRadiationFile );
            return;
        }
        if ( !checked_SolarRadiationFile )
        {
            if ( ! CheckFileAccess(input_filename_SolarRadiationFile, "ReadOnly") )
            {
                Log_Error_Message("NO Read Access to SolarRadiation Input File or Value Missing " + input_filename_SolarRadiationFile );
                return;
            }
        }

        QString input_filename_VaporPressureFile = ui->lineEditVaporPressureFile->text();
        checked_input = Check_VaporPressureFileorValue(input_filename_VaporPressureFile);
        if(!checked_input)
        {
            Log_Error_Message("VaporPressure Input File or Value Missing " + input_filename_VaporPressureFile );
            return;
        }
        if ( !checked_VaporPressureFile )
        {
            if ( ! CheckFileAccess(input_filename_VaporPressureFile, "ReadOnly") )
            {
                Log_Error_Message("NO Read Access to VaporPressure Input File or Value Missing " + input_filename_VaporPressureFile );
                return;
            }
        }

        QString input_filename_SoilClassesFile = ui->lineEditSoilClassesFile->text();
        checked_input = Check_SoilClassesFileorValue(input_filename_SoilClassesFile);
        if(!checked_input)
        {
            Log_Error_Message("SoilClasses Input File or Value Missing " + input_filename_SoilClassesFile );
            return;
        }
        if ( !checked_SoilClassesFile )
        {
            if ( ! CheckFileAccess(input_filename_SoilClassesFile, "ReadOnly") )
            {
                Log_Error_Message("NO Read Access to SoilClasses Input File or Value Missing " + input_filename_SoilClassesFile );
                return;
            }
        }

        QString input_filename_GeologyClassesFile = ui->lineEditGeologyClassesFile->text();
        checked_input = Check_GeologyClassesFileorValue(input_filename_GeologyClassesFile);
        if(!checked_input)
        {
            Log_Error_Message("GeologyClasses Input File or Value Missing " + input_filename_GeologyClassesFile );
            return;
        }
        if ( !checked_GeologyClassesFile )
        {
            if ( ! CheckFileAccess(input_filename_GeologyClassesFile, "ReadOnly") )
            {
                Log_Error_Message("NO Read Access to GeologyClasses Input File or Value Missing " + input_filename_GeologyClassesFile );
                return;
            }
        }

        QString input_filename_MacroporesFile = ui->lineEditMacroporesFile->text();
        checked_input = Check_MacroporesFileorValue(input_filename_MacroporesFile);
        if(!checked_input)
        {
            Log_Error_Message("Macropores Input File or Value Missing " + input_filename_MacroporesFile );
            return;
        }
        if ( !checked_MacroporesFile )
        {
            if ( ! CheckFileAccess(input_filename_MacroporesFile, "ReadOnly") )
            {
                Log_Error_Message("NO Read Access to Macropores Input File or Value Missing " + input_filename_MacroporesFile );
                return;
            }
        }

        QString input_filename_LandCoverClassesFile = ui->lineEditLandCoverClassesFile->text();
        checked_input = Check_LandCoverClassesFileorValue(input_filename_LandCoverClassesFile);
        if(!checked_input)
        {
            Log_Error_Message("LandCover Input File or Value Missing " + input_filename_LandCoverClassesFile );
            return;
        }
        if ( !checked_LandCoverClassesFile )
        {
            if ( ! CheckFileAccess(input_filename_LandCoverClassesFile, "ReadOnly") )
            {
                Log_Error_Message("NO Read Access to LandCover Input File or Value Missing " + input_filename_LandCoverClassesFile );
                return;
            }
        }

        QString input_filename_MeltRegionsFile = ui->lineEditMeltRegionsFile->text();
        checked_input = Check_MeltRegionsFileorValue(input_filename_MeltRegionsFile);
        if(!checked_input)
        {
            Log_Error_Message("MeltRegions Input File or Value Missing " + input_filename_MeltRegionsFile );
            return;
        }
        if ( !checked_MeltRegionsFile )
        {
            if ( ! CheckFileAccess(input_filename_MeltRegionsFile, "ReadOnly") )
            {
                Log_Error_Message("NO Read Access to MeltRegions Input File or Value Missing " + input_filename_MeltRegionsFile );
                return;
            }
        }

        QString input_filename_SourcesSinksFile = ui->lineEditSourcesSinksFile->text();
        checked_input = Check_SourcesSinksFileorValue(input_filename_SourcesSinksFile);
        if(!checked_input)
        {
            Log_Error_Message("SourcesSinks Input File or Value Missing " + input_filename_SourcesSinksFile );
            return;
        }
        if ( !checked_SourcesSinksFile)
        {
            if ( ! CheckFileAccess(input_filename_SourcesSinksFile, "ReadOnly") )
            {
                Log_Error_Message("NO Read Access to SourcesSinks Input File or Value Missing " + input_filename_SourcesSinksFile );
                return;
            }
        }

        QString input_filename_InterceptionFile = ui->lineEditInterceptionFile->text();
        checked_input = Check_InterceptionFileorValue(input_filename_InterceptionFile);
        if(!checked_input)
        {
            Log_Error_Message("Interception Input File or Value Missing " + input_filename_InterceptionFile );
            return;
        }
        if ( !checked_InterceptionFile )
        {
            if ( ! CheckFileAccess(input_filename_InterceptionFile, "ReadOnly") )
            {
                Log_Error_Message("NO Read Access to Interception Input File or Value Missing " + input_filename_InterceptionFile );
                return;
            }
        }

        QString input_filename_SnowCoverFile = ui->lineEditSnowCoverFile->text();
        checked_input = Check_SnowCoverFileorValue(input_filename_SnowCoverFile);
        if(!checked_input)
        {
            Log_Error_Message("SnowCover Input File or Value Missing " + input_filename_SnowCoverFile );
            return;
        }
        if ( !checked_SnowCoverFile )
        {
            if ( ! CheckFileAccess(input_filename_SnowCoverFile, "ReadOnly") )
            {
                Log_Error_Message("NO Read Access to SnowCover Input File or Value Missing " + input_filename_SnowCoverFile );
                return;
            }
        }

        QString input_filename_SurfaceStorageFile = ui->lineEditSurfaceStorageFile->text();
        checked_input = Check_SurfaceStorageFileorValue(input_filename_SurfaceStorageFile);
        if(!checked_input)
        {
            Log_Error_Message("SurfaceStorage Input File or Value Missing " + input_filename_SurfaceStorageFile );
            return;
        }
        if ( !checked_SurfaceStorageFile )
        {
            if ( ! CheckFileAccess(input_filename_SurfaceStorageFile, "ReadOnly") )
            {
                Log_Error_Message("NO Read Access to SurfaceStorage Input File or Value Missing " + input_filename_SurfaceStorageFile );
                return;
            }
        }

        QString input_filename_SoilMoistureFile = ui->lineEditSoilMoistureFile->text();
        checked_input = Check_SoilMoistureFileorValue(input_filename_SoilMoistureFile);
        if(!checked_input)
        {
            Log_Error_Message("SoilMoisture Input File or Value Missing " + input_filename_SoilMoistureFile );
            return;
        }
        if ( !checked_SoilMoistureFile )
        {
            if ( ! CheckFileAccess(input_filename_SoilMoistureFile, "ReadOnly") )
            {
                Log_Error_Message("NO Read Access to SoilMoisture Input File or Value Missing " + input_filename_SoilMoistureFile );
                return;
            }
        }

        QString input_filename_GroundwaterFile = ui->lineEditGroundwaterFile->text();
        checked_input = Check_GroundwaterFileorValue(input_filename_GroundwaterFile);
        if(!checked_input)
        {
            Log_Error_Message("Groundwater Input File or Value Missing " + input_filename_GroundwaterFile );
            return;
        }
        if ( !checked_GroundwaterFile )
        {
            if ( ! CheckFileAccess(input_filename_GroundwaterFile, "ReadOnly") )
            {
                Log_Error_Message("NO Read Access to Groundwater Input File or Value Missing " + input_filename_GroundwaterFile );
                return;
            }
        }

        QString input_filename_BoundaryConditionFile = ui->lineEditBoundaryConditionFile->text();
        checked_input = Check_BoundaryConditionFileorValue(input_filename_BoundaryConditionFile);
        if(!checked_input)
        {
            Log_Error_Message("BoundaryCondition Input File or Value Missing " + input_filename_BoundaryConditionFile );
            return;
        }
        if ( !checked_BoundaryConditionFile )
        {
            if ( ! CheckFileAccess(input_filename_BoundaryConditionFile, "ReadOnly") )
            {
                Log_Error_Message("NO Read Access to BoundaryCondition Input File or Value Missing " + input_filename_BoundaryConditionFile );
                return;
            }
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Check Outputs
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QString output_filename = ui->lineEditAttDataFile->text();

        bool output_check = Check_Att_Output(output_filename, true);
        if(output_check)
        {
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Running Att Data File
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Log_Message("Running Att Data File ... <br>");

        // *** ATT Function Calls
        //int att_data_file(
        //        QString PrecipitationFileName, bool PrecipitationFlag, QString TemperatureFileName,    bool TemperatureFlag,    QString RelativeHumidityFileName, bool RelativeHumidityFlag, QString WindVelocityFileName,     bool WindVelocityFlag,     QString SolarRadiationFileName, bool SolarRadiationFlag, QString VaporPressureFileName,     bool VaporPressureFlag,
        //        QString SoilClassesFileName,   bool SoilClassesFlag,   QString GeologyClassesFileName, bool GeologyClassesFlag, QString MacroporesFileName,       bool MacroporesFlag,       QString LandCoverClassesFileName, bool LandCoverClassesFlag, QString MeltRegionsFileName,    bool MeltRegionsFlag,    QString SourcesSinksFileName,      bool SourcesSinksFlag,
        //        QString InterceptionFileName,  bool InterceptionFlag,  QString SnowCoverFileFileName,  bool SnowCoverFileFlag,  QString SurfaceStorageFileName,   bool SurfaceStorageFlag,   QString SoilMoistureFileName,     bool SoilMoistureFlag,     QString GroundwaterFileName,    bool GroundwaterFlag,    QString BoundaryConditionFileName, bool BoundaryConditionFlag,
        //        QString TINShapeLayerFileName, QString AttDataFileName
        //        );
        int ErrorAtt = att_data_file(
                    input_filename_PrecipitationFile,     checked_PrecipitationFile,
                    input_filename_TemperatureFile,       checked_TemperatureFile,
                    input_filename_RelativeHumidityFile,  checked_RelativeHumidityFile,
                    input_filename_WindVelocityFile,      checked_WindVelocityFile,
                    input_filename_SolarRadiationFile,    checked_SolarRadiationFile,
                    input_filename_VaporPressureFile,     checked_VaporPressureFile,

                    input_filename_SoilClassesFile,       checked_SoilClassesFile,
                    input_filename_GeologyClassesFile,    checked_GeologyClassesFile,
                    input_filename_MacroporesFile,        checked_MacroporesFile,
                    input_filename_LandCoverClassesFile,  checked_LandCoverClassesFile,
                    input_filename_MeltRegionsFile,       checked_MeltRegionsFile,
                    input_filename_SourcesSinksFile,      checked_SourcesSinksFile,

                    input_filename_InterceptionFile,      checked_InterceptionFile,
                    input_filename_SnowCoverFile,         checked_SnowCoverFile,
                    input_filename_SurfaceStorageFile,    checked_SurfaceStorageFile,
                    input_filename_SoilMoistureFile,      checked_SoilMoistureFile,
                    input_filename_GroundwaterFile,       checked_GroundwaterFile,
                    input_filename_BoundaryConditionFile, checked_BoundaryConditionFile,

                    input_filename_TINShape_Input,
                    output_filename

                    );

        if( ErrorAtt != 0 )
        {
            Log_Message(tr("<span style=\"color:#FF0000\">ERROR: Att Data File Processing Failed ... </span>")+tr("<br>"));
            Log_Message(tr("<span style=\"color:#FF0000\">RETURN CODE ATT: ... </span>")+QString::number(ErrorAtt)+tr("<br>"));
            return;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update Project file
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        QStringList ProjectIOStringList;

        ProjectIOStringList << "AttDataFile"
                            << input_filename_PrecipitationFile <<      QString::number( (int) checked_PrecipitationFile )
                            << input_filename_TemperatureFile <<        QString::number( (int) checked_TemperatureFile)
                            << input_filename_RelativeHumidityFile <<   QString::number( (int) checked_RelativeHumidityFile )
                            << input_filename_WindVelocityFile <<       QString::number( (int) checked_WindVelocityFile )
                            << input_filename_SolarRadiationFile <<     QString::number( (int) checked_SolarRadiationFile )
                            << input_filename_VaporPressureFile <<      QString::number( (int) checked_VaporPressureFile )

                            << input_filename_SoilClassesFile <<        QString::number( (int) checked_SoilClassesFile)
                            << input_filename_GeologyClassesFile <<     QString::number( (int) checked_GeologyClassesFile )
                            << input_filename_MacroporesFile <<         QString::number( (int) checked_MacroporesFile)
                            << input_filename_LandCoverClassesFile <<   QString::number( (int) checked_LandCoverClassesFile )
                            << input_filename_MeltRegionsFile <<        QString::number( (int) checked_MeltRegionsFile )
                            << input_filename_SourcesSinksFile <<       QString::number( (int) checked_SourcesSinksFile )

                            << input_filename_InterceptionFile <<       QString::number( (int) checked_InterceptionFile )
                            << input_filename_SnowCoverFile <<          QString::number( (int) checked_SnowCoverFile )
                            << input_filename_SurfaceStorageFile <<     QString::number( (int) checked_SurfaceStorageFile )
                            << input_filename_SoilMoistureFile <<       QString::number( (int) checked_SoilMoistureFile )
                            << input_filename_GroundwaterFile <<        QString::number( (int) checked_GroundwaterFile )
                            << input_filename_BoundaryConditionFile <<  QString::number( (int) checked_BoundaryConditionFile )

                            << input_filename_TINShape_Input <<       output_filename;

        WriteModuleLine(filename_open_project, ProjectIOStringList);
        ProjectIOStringList.clear();

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update Message box
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Clear_Log();

        Log_Message(tr("<br><b>Att Data File Processing Complete.</b>")+tr("<br>"));

        ui->pushButtonRun->setDefault(false);
        ui->pushButtonClose->setDefault(true);
        ui->pushButtonClose->setFocus();


    } catch (...) {
        qDebug() << "Error: AttDataFile::on_pushButtonRun_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Help button event
// TODO, Need cataract server back online
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::on_pushButtonClose_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start on_pushButtonClose_clicked";

    try {
        //QStringList default_params; default_params << "WORKFLOW5" << "RIVX";
        //QMetaObject::invokeMethod(parent(),"set_defaults",Q_ARG(QStringList,default_params));
        close();
    } catch (...) {
        qDebug() << "Error: AttDataFile::on_pushButtonClose_clicked() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Help button event
// TODO, Need cataract server back online
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AttDataFile::on_pushButtonHelp_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start on_pushButtonHelp_clicked";

    try {
        //        LogsString = tr("");
        //        if ( ! QDesktopServices::openUrl(QUrl("http://cataract.cee.psu.edu/PIHM/index.php/PIHMgis_3.0#att_Data_File")) )
        //            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Load HTTP Link ... </span>")+tr("<br>"));
        //        ui->textBrowserLogs->setHtml(LogsString);
        //        ui->textBrowserLogs->repaint();
    } catch (...) {
        qDebug() << "Error: AttDataFile::on_pushButtonHelp_clicked() is returning w/o checking";
    }
}
