#ifndef IBCDATAFILE_H
#define IBCDATAFILE_H

#include <QDialog>

namespace Ui {
class IbcDataFile;
}

class IbcDataFile : public QDialog
{
    Q_OBJECT

public:
    explicit IbcDataFile(QWidget *parent = 0, QString filename_open_project = "No Project Provided");
    ~IbcDataFile();


private slots:
    void on_pushButtonIbcDataFile_clicked();

    void on_pushButtonRun_clicked();

    void on_pushButtonClose_clicked();

    void on_pushButtonHelp_clicked();

    void pushButtonSetFocus();


private:

    int  ibc_data_file( QString );

    void Clear_Log();
    void Log_Error_Message(QString message);
    void Log_Message(QString message);

    bool Load_Project_Settings();

    bool Check_IbcData_Output(QString file, bool message); //lineEditIbcDataFile

    Ui::IbcDataFile *ui;
    QString filename_open_project;
    QString LogsString;

};

#endif // IBCDATAFILE_H
