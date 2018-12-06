#ifndef CATCHMENTGRIDS_H
#define CATCHMENTGRIDS_H

#include <QDialog>

namespace Ui {
class CatchmentGrids;
}

class CatchmentGrids : public QDialog
{
    Q_OBJECT

public:
    explicit CatchmentGrids(QWidget *parent = 0, QString filename_open_project = "No Project Provided");
    ~CatchmentGrids();


private slots:
    void on_pushButtonLinkGrids_clicked();

    void on_pushButtonFlowDirGrids_clicked();

    void on_pushButtonCatchmentGrids_clicked();

    void on_pushButtonRun_clicked();

    void on_pushButtonClose_clicked();

    void on_pushButtonHelp_clicked();

    void pushButtonSetFocus();

private:

    void Clear_Log();
    void Log_Error_Message(QString message);
    void Log_Message(QString message);

    bool Check_LinkGrids_Input(QString file);
    bool Check_FlowDirGrids_Input(QString file);
    bool Check_CatchmentGrids_Output(QString file, bool color_and_message_if_exists);

    bool Load_Project_Settings();

    Ui::CatchmentGrids *ui;

    QString filename_open_project;
    QString LogsString;

};

#endif // CATCHMENTGRIDS_H
