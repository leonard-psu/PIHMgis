#ifndef RIVERSPATIAL_H
#define RIVERSPATIAL_H

#include <QDialog>
#include "globals.h"

namespace Ui {
class RiverSpatial;
}

class RiverSpatial : public QDialog
{
    Q_OBJECT

public:
    explicit RiverSpatial(QWidget *parent = 0, QString filename_open_project = "");
    ~RiverSpatial();

    QString LogsString;

private slots:
    void on_pushButtonOutputDataFolder_clicked();

    void on_lineEditOutputDataFolder_textChanged(const QString &arg1);

    void on_lineEditDataKey_textChanged(const QString &arg1);

    void on_comboBoxPlotVariable_currentIndexChanged(int index);

    void pushButtonSetFocus();

    void on_comboBoxStartStop_currentIndexChanged(int index);

    void on_pushButtonRiverShapeFile_clicked();

    void on_pushButtonRun_clicked();

    void on_pushButtonClose_clicked();

    void on_pushButtonHelp_clicked();

    void on_lineEditRiverShapeFile_textChanged(const QString &arg1);

private:

    void Clear_Log();
    void Log_Error_Message(QString message);
    void Log_Message(QString message);

    void verifyInputOutputFile();

    bool Load_Project_Settings();
    bool Load_Para_Input(QString file);
    bool Load_BasedOnProjectName_Input();

    bool Check_OutputFolder_Location(QString folder);
    bool Check_Project_Name_Input(QString value);
    bool Check_RiverShapeFile_Input(QString value);
    bool Check_ShapeFile_Output(QString file_name_without_extension, bool delete_files);

    int Get_Element_Count(QString element_filename, bool message);
    int Get_River_Count(QString river_filename, bool message);
    Time_Values Get_Time_Steps(QString filename, int num_elements, bool message);

    Ui::RiverSpatial *ui;
    QString filename_open_project;

};

#endif // RIVERSPATIAL_H
