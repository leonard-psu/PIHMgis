#ifndef LINKGRIDS_H
#define LINKGRIDS_H

#include <QDialog>

namespace Ui {
class LinkGrids;
}

class LinkGrids : public QDialog
{
    Q_OBJECT

public:
    explicit LinkGrids(QWidget *parent = 0, QString filename_open_project = "No Project Provided");
    ~LinkGrids();


private slots:
    void on_pushButtonStreamGrids_clicked();

    void on_pushButtonFlowDirGrids_clicked();

    void on_pushButtonLinkGrids_clicked();

    void on_pushButtonRun_clicked();

    void on_pushButtonClose_clicked();

    void on_pushButtonHelp_clicked();

    void pushButtonSetFocus();


private:

    void Clear_Log();
    void Log_Error_Message(QString message);
    void Log_Message(QString message);

    bool Check_StreamGrids_Input(QString file);
    bool Check_FlowDirGrids_Input(QString file);
    bool Check_LinkGrids_Output(QString file, bool color_and_message_if_exists);

    bool Load_Project_Settings();

    Ui::LinkGrids *ui;

    QString filename_open_project;
    QString LogsString;

};

#endif // LINKGRIDS_H
