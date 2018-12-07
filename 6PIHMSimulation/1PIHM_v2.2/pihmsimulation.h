#ifndef PIHMSimulation_H
#define PIHMSimulation_H

#include <QDialog>

#include "6PIHMSimulation/PIHMThread/PIHMThread.h"

namespace Ui {
class PIHMSimulation;
}

class PIHMSimulation : public QDialog
{
    Q_OBJECT

public:
    explicit PIHMSimulation(QWidget *parent = 0, QString filename_open_project = "No Project Provided");
    ~PIHMSimulation();


public slots:
    void onValueChanged(int);
    void onPIHM_StatusChanged(std::string value);
    void onPIHM_Finished(bool);
    void onPIHM_Failed();

signals:
    void PIHMThread_Results(QString message);


private slots:
    void on_pushButtonInputDataFolder_clicked();

    void on_pushButtonRun_clicked();

    void on_pushButtonClose_clicked();

    void on_pushButtonHelp_clicked();

    void pushButtonSetFocus();

    void on_progressBar_valueChanged(int value);

    void updateProgressBarValue(int value);

    void PIHMThreadFinished();

    void on_lineEditInputDataFolder_textChanged(const QString &arg1);

    void on_lineEditDataKey_textChanged(const QString &arg1);

    void on_pushButtonCheckInputs_clicked();


    void on_pushButton_Stop_clicked();

private:

    void Clear_Log();
    bool Load_Project_Settings();
    void Log_Error_Message(QString message);
    void Log_Warning_Message(QString message);
    void Log_Message(QString message);

    bool Check_InputDataFolder(QString folder);
    bool Check_DataKey(QString value);
    bool Check_PIHM_Project_Inputs(QString base_folder, QString project_name, bool return_on_error);
    bool CopyInputFiles(QString output_folder, QString input_folder, QString project_name, bool delete_existing_output_file);

    int CheckInputFileAccess(QString folder, QString project_name, QString extension, bool message);
    int CopyInputFile(QString output_folder, QString input_folder, QString project_name, QString file_extension, bool delete_existing_output_file);

    void verifyInputOutputFile();

    void PIHMThread_Delete();

    PIHMThread *mThread;

    Ui::PIHMSimulation *ui;
    QString LogsString;
    QString filename_open_project;
    QString ModelVersion = "PIHM v2.2"; //Constant for now
    bool pihm_running;

};

#endif // PIHMSimulation_H
