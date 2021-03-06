#ifndef CALIBDATAFILE_H
#define CALIBDATAFILE_H

#include <QDialog>

namespace Ui {
class CalibDataFile;
}

class CalibDataFile : public QDialog
{
    Q_OBJECT

public:
    explicit CalibDataFile(QWidget *parent = 0, QString filename_open_project = "No Project Provided");
    ~CalibDataFile();


private slots:
    void on_pushButtonCalibDataFile_clicked();

    void on_pushButtonRun_clicked();

    void on_pushButtonClose_clicked();

    void on_pushButtonHelp_clicked();

    void pushButtonSetFocus();

private:

    int calib_data_file(QString filename);

    void Clear_Log();
    void Log_Warning_Message(QString message);
    void Log_Error_Message(QString message);
    void Log_Message(QString message);

    bool Load_Project_Settings();

    bool Check_Calib_Output(QString file, bool color_and_message_if_exists);


    Ui::CalibDataFile *ui;
    QString filename_open_project;
    QString LogsString;

};

#endif // CALIBDATAFILE_H
