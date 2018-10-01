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
    explicit CatchmentGrids(QWidget *parent = 0, QString filename_open_project = "");
    ~CatchmentGrids();

    QString LogsString;
    //QStringList ProjectIOStringList;

private slots:
    void on_pushButtonLinkGrids_clicked();

    void on_pushButtonFlowDirGrids_clicked();

    void on_pushButtonCatchmentGrids_clicked();

    void on_pushButtonRun_clicked();

    void on_pushButtonClose_clicked();

    void on_pushButtonHelp_clicked();

    void pushButtonSetFocus();

    void Clear_Log();

    bool Check_LinkGrids_Input(QString file);

    bool Check_FlowDirGrids_Input(QString file);

    bool Check_CatchmentGrids_Output(QString file, bool message);


private:
    Ui::CatchmentGrids *ui;
    QString filename_open_project;

};

#endif // CATCHMENTGRIDS_H
