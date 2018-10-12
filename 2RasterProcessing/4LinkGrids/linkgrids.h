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
    explicit LinkGrids(QWidget *parent = 0, QString filename_open_project = "");
    ~LinkGrids();

    QString LogsString;

private slots:
    void on_pushButtonStreamGrids_clicked();

    void on_pushButtonFlowDirGrids_clicked();

    void on_pushButtonLinkGrids_clicked();

    void on_pushButtonRun_clicked();

    void on_pushButtonClose_clicked();

    void on_pushButtonHelp_clicked();

    void pushButtonSetFocus();

    void Clear_Log();

    bool Check_StreamGrids_Input(QString file);

    bool Check_FlowDirGrids_Input(QString file);

    bool Check_LinkGrids_Output(QString file, bool color_and_message_if_exists);

    bool Load_Project_Settings();


private:
    Ui::LinkGrids *ui;
    QString filename_open_project;

};

#endif // LINKGRIDS_H
