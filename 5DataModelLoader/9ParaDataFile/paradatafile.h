#ifndef PARADATAFILE_H
#define PARADATAFILE_H

#include <QDialog>

namespace Ui {
class ParaDataFile;
}

class ParaDataFile : public QDialog
{
    Q_OBJECT

public:
    explicit ParaDataFile(QWidget *parent = 0, QString filename_open_project = "");
    ~ParaDataFile();

    QString LogsString;

private slots:
    void on_pushButtonParaDataFile_clicked();

    void on_pushButtonRun_clicked();

    void on_pushButtonClose_clicked();

    void on_pushButtonHelp_clicked();

    void pushButtonSetFocus();



private:
    int para_data_file(QString filename);

    bool Check_Para_Output(QString file, bool message);

    void Clear_Log();

    bool Load_Project_Settings();
    void Log_Error_Message(QString message);

    Ui::ParaDataFile *ui;
    QString filename_open_project;

};

#endif // PARADATAFILE_H
