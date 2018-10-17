#ifndef MESHDATAFILE_H
#define MESHDATAFILE_H

#include <QDialog>

namespace Ui {
class MeshDataFile;
}

class MeshDataFile : public QDialog
{
    Q_OBJECT

public:
    explicit MeshDataFile(QWidget *parent = 0, QString filename_open_project = "");
    ~MeshDataFile();

    QString LogsString;

private slots:
    void on_pushButtonElementFile_clicked();

    void on_pushButtonNodeFile_clicked();

    void on_pushButtonNeighbourFile_clicked();

    void on_pushButtonRiverFile_clicked();

    void on_pushButtonSurfaceElevationFile_clicked();

    void on_pushButtonSubsurfaceThickness_clicked();

    void on_pushButtonMeshDataFile_clicked();

    void on_pushButtonRun_clicked();

    void on_pushButtonClose_clicked();

    void on_pushButtonHelp_clicked();

    void pushButtonSetFocus();

    void on_checkBoxSubsurfaceThickness_toggled(bool checked);

private:

    void Clear_Log();

    bool Load_Project_Settings();

    bool Check_ElementFile_Input(QString file);

    bool Check_NodeFile_Input(QString file);

    bool Check_NeighbourFile_Input(QString file);

    bool Check_RiverFile_Input(QString file);

    bool Check_SurfaceElevationFile_Input(QString file);

    bool Check_SubsurfaceThickness_Input(QString file);

    bool Check_MeshData_Output(QString file, bool message);

    Ui::MeshDataFile *ui;
    QString filename_open_project;

};

#endif // MESHDATAFILE_H
