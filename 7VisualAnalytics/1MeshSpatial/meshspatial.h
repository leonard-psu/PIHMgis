#ifndef MESHSPATIAL_H
#define MESHSPATIAL_H

#include <QDialog>

namespace Ui {
class MeshSpatial;
}

struct Time_Values
{
    int time_step1;
    int time_step2;

};

class MeshSpatial : public QDialog
{
    Q_OBJECT

public:
    explicit MeshSpatial(QWidget *parent = 0, QString filename_open_project = "");
    ~MeshSpatial();

    QString LogsString;

private slots:
    void on_pushButtonOutputDataFolder_clicked();

    void on_lineEditOutputDataFolder_textChanged(const QString &arg1);

    void on_lineEditDataKey_textChanged(const QString &arg1);

    void on_comboBoxPlotVariable_currentIndexChanged(int index);

    void pushButtonSetFocus();

    void on_comboBoxStartStop_currentIndexChanged(int index);

    void on_pushButtonMeshShapeFile_clicked();

    void on_pushButtonRun_clicked();

    void on_pushButtonClose_clicked();

    void on_pushButtonHelp_clicked();

    void on_lineEditMeshShapeFile_textChanged(const QString &arg1);

private:


    void Clear_Log();
    void Log_Error_Message(QString message);
    void Log_Message(QString message);


    void verifyInputOutputFile();

    bool Check_OutputFolder_Location(QString folder);
    bool Check_Project_Name_Input(QString file);
    bool Check_Mesh_Input(QString file);
    bool Check_ShapeFile_Output(QString file_name_without_extension, bool delete_files);

    bool Load_Project_Settings();
    bool Load_Para_Input(QString file, int index);

    int Get_Element_Count(QString element_filename, bool message);
    int Get_River_Count(QString river_filename, bool message);
    Time_Values Get_Time_Steps(QString filename, int num_elements, bool message);


    Ui::MeshSpatial *ui;
    QString filename_open_project;

};

#endif // MESHSPATIAL_H
