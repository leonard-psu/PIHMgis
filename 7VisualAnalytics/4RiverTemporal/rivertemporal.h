#ifndef RIVERTEMPORAL_H
#define RIVERTEMPORAL_H

#include <QDialog>
#include "globals.h"

namespace Ui {
class RiverTemporal;
}

class RiverTemporal : public QDialog
{
    Q_OBJECT

public:
    explicit RiverTemporal(QWidget *parent = 0, QString filename_open_project = "");
    ~RiverTemporal();

    QString LogsString;

private slots:
    void on_pushButtonRun_clicked();

    void on_pushButtonClose_clicked();

    void on_pushButtonOutputDataFolder_clicked();

    void on_pushButtonHelp_clicked();

    void on_comboBoxModelSegments_currentIndexChanged(int index);

    void on_lineEditOutputDataFolder_textChanged(const QString &arg1);

    void on_lineEditDataKey_textChanged(const QString &arg1);

    void pushButtonSetFocus();

    void on_comboBoxPlotVariable_currentIndexChanged(int index);

    void on_lineEditModelSegments_textChanged(const QString &arg1);

private:

    void Clear_Log();
    void Log_Error_Message(QString message);
    void Log_Message(QString message);

    void verifyInputOutputFile();

    bool Load_Project_Settings();

    bool Check_OutputFolder_Location(QString folder);
    bool Check_Project_Name_Input(QString value);
    bool Check_ModelSegments_Input(QString value);

    int Get_Element_Count(QString element_filename, bool message);
    int Get_River_Count(QString river_filename, bool message);
    Time_Values Get_Time_Steps(QString filename, int num_elements, bool message);

    Ui::RiverTemporal *ui;
    QString filename_open_project;

};

#endif // RIVERTEMPORAL_H
