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
    explicit FlowGrids(QWidget *parent = 0, QString filename_open_project = "");
    ~FlowGrids();

    QString LogsString;
    //QStringList ProjectIOStringList;

private slots:
    void on_pushButtonFillPits_clicked();

    void on_pushButtonsFlowDirGrid_clicked();

    void on_pushButtonFlowAccGrid_clicked();

    void on_pushButtonRun_clicked();

    void on_pushButtonClose_clicked();

    void on_pushButtonHelp_clicked();

    void pushButtonSetFocus();


    bool Check_Fillpit_Intput(QString file);

    bool Check_FlowDir_Output(QString file, bool message );

    bool Check_FlowAcc_Output(QString file, bool message );

    void Clear_Log();


private:
    Ui::FlowGrids *ui;
    QString filename_open_project;

};

#endif // FLOWGRIDS_H
