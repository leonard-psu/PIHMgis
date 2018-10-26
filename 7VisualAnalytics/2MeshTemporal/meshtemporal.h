#ifndef MESHTEMPORAL_H
#define MESHTEMPORAL_H

#include <QDialog>
#include "globals.h"

namespace Ui {
class MeshTemporal;
}


class MeshTemporal : public QDialog
{
    Q_OBJECT

public:
    explicit MeshTemporal(QWidget *parent = 0, QString filename_open_project = "");
    ~MeshTemporal();

    QString LogsString;

private slots:
    void on_pushButtonOutputDataFolder_clicked();

    void on_comboBoxModelSegments_currentIndexChanged(int index);

    void on_lineEditOutputDataFolder_textChanged(const QString &arg1);

    void on_lineEditDataKey_textChanged(const QString &arg1);

    void on_comboBoxPlotVariable_currentIndexChanged(int index);

    void pushButtonSetFocus();

    void on_pushButtonRun_clicked();

    void on_pushButtonClose_clicked();

    void on_pushButtonHelp_clicked();

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

    Ui::MeshTemporal *ui;
    QString filename_open_project;

};

#endif // MESHTEMPORAL_H
