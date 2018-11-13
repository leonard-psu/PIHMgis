#ifndef LcDATAFILE_H
#define LcDATAFILE_H

#include <QDialog>

namespace Ui {
class LcDataFile;
}

class LcDataFile : public QDialog
{
    Q_OBJECT

public:
    explicit LcDataFile(QWidget *parent = 0, QString filename_open_project = "");
    ~LcDataFile();

    QString LogsString;

private slots:
    void on_pushButtonLcClassFile_clicked();

    void on_pushButtonLcDataFile_clicked();

    void on_pushButtonRun_clicked();

    void on_pushButtonClose_clicked();

    void on_pushButtonHelp_clicked();

    void pushButtonSetFocus();

    void on_lineEditLcClassFile_textEdited(const QString &arg1);

    void on_lineEditLcDataFile_textEdited(const QString &arg1);

private:

    void Clear_Log();
    void Log_Warning_Message(QString message);
    void Log_Error_Message(QString message);

    bool Load_Project_Settings();

    bool Check_LCTexture_Input(QString file);
    bool Check_LCData_Output(QString file, bool message);


    Ui::LcDataFile *ui;
    QString filename_open_project;

};

#endif // LcDATAFILE_H
