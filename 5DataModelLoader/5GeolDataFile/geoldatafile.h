#ifndef GEOLDATAFILE_H
#define GEOLDATAFILE_H

#include <QDialog>

namespace Ui {
class GeolDataFile;
}

class GeolDataFile : public QDialog
{
    Q_OBJECT

public:
    explicit GeolDataFile(QWidget *parent = 0, QString filename_open_project = "");
    ~GeolDataFile();

    QString LogsString;

private slots:
    void on_pushButtonGeolTextureFile_clicked();

    void on_pushButtonGeolDataFile_clicked();

    void on_pushButtonRun_clicked();

    void on_pushButtonClose_clicked();

    void on_pushButtonHelp_clicked();

    void pushButtonSetFocus();


    void on_lineEditGeolTextureFile_textEdited(const QString &arg1);

    void on_lineEditGeolDataFile_textEdited(const QString &arg1);

private:

    void Clear_Log(); 
    void Log_Warning_Message(QString message);
    void Log_Error_Message(QString message);

    bool Load_Project_Settings();

    bool Check_GeolTexture_Input(QString file);
    bool Check_GeolData_Output(QString file, bool message);


    Ui::GeolDataFile *ui;
    QString filename_open_project;

};

#endif // GEOLDATAFILE_H
