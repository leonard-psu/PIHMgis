#ifndef SOILDATAFILE_H
#define SOILDATAFILE_H

#include <QDialog>

namespace Ui {
class SoilDataFile;
}

class SoilDataFile : public QDialog
{
    Q_OBJECT

public:
    explicit SoilDataFile(QWidget *parent = 0, QString filename_open_project = "");
    ~SoilDataFile();

    QString LogsString;
    QStringList ProjectIOStringList;

private slots:
    void on_pushButtonSoilTextureFile_clicked();

    void on_pushButtonSoilDataFile_clicked();

    void on_pushButtonRun_clicked();

    void on_pushButtonClose_clicked();

    void on_pushButtonHelp_clicked();

    void pushButtonSetFocus();


private:

    void Clear_Log();

    bool Load_Project_Settings();

    bool Check_SoilTexture_Input(QString file);

    bool Check_SoilData_Output(QString file, bool message);



    Ui::SoilDataFile *ui;
    QString filename_open_project;

};

#endif // SOILDATAFILE_H
