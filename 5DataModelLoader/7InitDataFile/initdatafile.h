#ifndef INITDATAFILE_H
#define INITDATAFILE_H

#include <QDialog>

namespace Ui {
class InitDataFile;
}

class InitDataFile : public QDialog
{
    Q_OBJECT

public:
    explicit InitDataFile(QWidget *parent = 0, QString filename_open_project = "");
    ~InitDataFile();

    QString LogsString;

private slots:
    void on_pushButtonMeshDataFile_clicked();

    void on_pushButtonRivDataFile_clicked();

    void on_pushButtonInitDataFile_clicked();

    void on_pushButtonRun_clicked();

    void on_pushButtonClose_clicked();

    void on_pushButtonHelp_clicked();

    void pushButtonSetFocus();

    void on_lineEditInterception_textChanged(const QString &arg1);

    void on_lineEditSnow_textChanged(const QString &arg1);

    void on_lineEditSurface_textChanged(const QString &arg1);

    void on_lineEditSoilMoisture_textChanged(const QString &arg1);

    void on_lineEditGroundwater_textChanged(const QString &arg1);

    void on_lineEditRiver_textChanged(const QString &arg1);

    void on_lineEditRiverbed_textChanged(const QString &arg1);

    void on_radioButtonMeters_toggled(bool checked);

    void on_radioButtonPercent_toggled(bool checked);

private:

    int init_data_file(QString Interception, QString Snow, QString Surface, QString SoilMoisture, QString Groundwater,
                       QString River, QString Riverbed, int MetersOrPercent,
                       QString MeshDataFileName, QString RivDataFileName, QString InitDataFileName);

    void Clear_Log();

    bool Load_Project_Settings();
    void Log_Warning_Message(QString message);
    void Log_Error_Message(QString message);


    bool Check_Interception_Input(QString value);
    bool Check_Snow_Input(QString value);
    bool Check_Surface_Input(QString value);
    bool Check_SoilMoisture_Input(QString value);
    bool Check_Groundwater_Input(QString value);
    bool Check_River_Input(QString value);
    bool Check_Riverbed_Input(QString value);

    bool Check_MeshData_Input(QString file);
    bool Check_RivData_Input(QString file);

    bool Check_InitData_Output(QString file, bool message);



    Ui::InitDataFile *ui;
    QString filename_open_project;


};

#endif // INITDATAFILE_H
