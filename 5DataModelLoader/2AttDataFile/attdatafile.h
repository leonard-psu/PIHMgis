#ifndef ATTDATAFILE_H
#define ATTDATAFILE_H

#include <QDialog>

namespace Ui {
class AttDataFile;
}

class AttDataFile : public QDialog
{
    Q_OBJECT

public:
    explicit AttDataFile(QWidget *parent = 0, QString filename_open_project = "No Project Provided");
    ~AttDataFile();


private slots:

    void on_pushButtonPrecipitationFile_clicked();

    void on_pushButtonTemperatureFile_clicked();

    void on_pushButtonRelativeHumidityFile_clicked();

    void on_pushButtonWindVelocityFile_clicked();

    void on_pushButtonSolarRadiationFile_clicked();

    void on_pushButtonVaporPressureFile_clicked();

    void on_pushButtonSoilClassesFile_clicked();

    void on_pushButtonGeologyClassesFile_clicked();

    void on_pushButtonMacroporesFile_clicked();

    void on_pushButtonLandCoverClassesFile_clicked();

    void on_pushButtonMeltRegionsFile_clicked();

    void on_pushButtonSourcesSinksFile_clicked();

    void on_pushButtonInterceptionFile_clicked();

    void on_pushButtonSnowCoverFile_clicked();

    void on_pushButtonSurfaceStorageFile_clicked();

    void on_pushButtonSoilMoistureFile_clicked();

    void on_pushButtonGroundwaterFile_clicked();

    void on_pushButtonBoundaryConditionFile_clicked();


    void on_pushButtonTINShapeLayerFile_clicked();

    void on_pushButtonAttDataFile_clicked();


    void on_checkBoxPrecipitation_toggled(bool checked);

    void on_checkBoxTemperature_toggled(bool checked);

    void on_checkBoxRelativeHumidity_toggled(bool checked);

    void on_checkBoxWindVelocity_toggled(bool checked);

    void on_checkBoxSolarRadiation_toggled(bool checked);

    void on_checkBoxVaporPressure_toggled(bool checked);

    void on_checkBoxSoilClasses_toggled(bool checked);

    void on_checkBoxGeologyClasses_toggled(bool checked);

    void on_checkBoxMacropores_toggled(bool checked);

    void on_checkBoxLandCoverClasses_toggled(bool checked);

    void on_checkBoxMeltRegions_toggled(bool checked);

    void on_checkBoxSourcesSinks_toggled(bool checked);

    void on_checkBoxInterception_toggled(bool checked);

    void on_checkBoxSnowCover_toggled(bool checked);

    void on_checkBoxSurfaceStorage_toggled(bool checked);

    void on_checkBoxSoilMoisture_toggled(bool checked);

    void on_checkBoxGroundwater_toggled(bool checked);

    void on_checkBoxBoundaryCondition_toggled(bool checked);


    void on_pushButtonRun_clicked();

    void on_pushButtonClose_clicked();

    void on_pushButtonHelp_clicked();


    void pushButtonSetFocus();


    void on_lineEditPrecipitationFile_textChanged(const QString &arg1);

    void on_lineEditTemperatureFile_textChanged(const QString &arg1);

    void on_lineEditRelativeHumidityFile_textChanged(const QString &arg1);

    void on_lineEditWindVelocityFile_textChanged(const QString &arg1);

    void on_lineEditSolarRadiationFile_textChanged(const QString &arg1);

    void on_lineEditVaporPressureFile_textChanged(const QString &arg1);

    void on_lineEditSoilClassesFile_textChanged(const QString &arg1);

    void on_lineEditGeologyClassesFile_textChanged(const QString &arg1);

    void on_lineEditMacroporesFile_textChanged(const QString &arg1);

    void on_lineEditLandCoverClassesFile_textChanged(const QString &arg1);

    void on_lineEditMeltRegionsFile_textChanged(const QString &arg1);

    void on_lineEditSourcesSinksFile_textChanged(const QString &arg1);

    void on_lineEditInterceptionFile_textChanged(const QString &arg1);

    void on_lineEditSnowCoverFile_textChanged(const QString &arg1);

    void on_lineEditSurfaceStorageFile_textChanged(const QString &arg1);

    void on_lineEditSoilMoistureFile_textChanged(const QString &arg1);

    void on_lineEditGroundwaterFile_textChanged(const QString &arg1);

    void on_lineEditBoundaryConditionFile_textChanged(const QString &arg1);

    void on_lineEditTINShapeLayerFile_textChanged(const QString &arg1);

    void on_lineEditAttDataFile_textChanged(const QString &arg1);


private:


    void Clear_Log();
    void Log_Warning_Message(QString message);
    void Log_Error_Message(QString message);
    void Log_Message(QString message);

    bool Load_Project_Settings();

    bool Check_Att_Output(QString file, bool message);

    bool Check_TINShape_Input(QString file);

    bool Check_PrecipitationFileorValue(QString file);
    bool Check_TemperatureFileorValue(QString file);
    bool Check_RelativeHumidityFileorValue(QString file);
    bool Check_WindVelocityFileorValue(QString file);
    bool Check_SolarRadiationFileorValue(QString file);
    bool Check_VaporPressureFileorValue(QString file);

    bool Check_SoilClassesFileorValue(QString file);
    bool Check_GeologyClassesFileorValue(QString file);
    bool Check_MacroporesFileorValue(QString file);
    bool Check_LandCoverClassesFileorValue(QString file);
    bool Check_MeltRegionsFileorValue(QString file);
    bool Check_SourcesSinksFileorValue(QString file);

    bool Check_InterceptionFileorValue(QString file);
    bool Check_SnowCoverFileorValue(QString file);
    bool Check_SurfaceStorageFileorValue(QString file);
    bool Check_SoilMoistureFileorValue(QString file);
    bool Check_GroundwaterFileorValue(QString file);
    bool Check_BoundaryConditionFileorValue(QString file);

    bool Is_String_Integer(QString file);



    Ui::AttDataFile *ui;
    QString filename_open_project;
    QString LogsString;

    int input_width_one = 300; //When user has specified file
    int input_width_two = 100; //When user has value
    bool finished_loading_files = false; //Need this to prevent multiple file error messages

};

#endif // ATTDATAFILE_H
