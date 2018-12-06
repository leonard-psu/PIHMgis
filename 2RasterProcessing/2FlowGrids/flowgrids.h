#ifndef FLOWGRIDS_H
#define FLOWGRIDS_H

#include <QDialog>

namespace Ui {
class FlowGrids;
}

class FlowGrids : public QDialog
{
    Q_OBJECT

public:
    explicit FlowGrids(QWidget *parent = 0, QString filename_open_project = "No Project Provided");
    ~FlowGrids();


private slots:
    void on_pushButtonFillPits_clicked();

    void on_pushButtonsFlowDirGrid_clicked();

    void on_pushButtonFlowAccGrid_clicked();

    void on_pushButtonRun_clicked();

    void on_pushButtonClose_clicked();

    void on_pushButtonHelp_clicked();

    void pushButtonSetFocus();


private:

    bool Check_Fillpit_Input(QString file);
    bool Check_FlowDir_Output(QString file, bool color_and_message_if_exists );
    bool Check_FlowAcc_Output(QString file, bool color_and_message_if_exists );

    void Clear_Log();
    void Log_Error_Message(QString message);
    void Log_Message(QString message);

    bool Load_Project_Settings();

    Ui::FlowGrids *ui;
    QString filename_open_project;
    QString LogsString;

};

#endif // FLOWGRIDS_H
