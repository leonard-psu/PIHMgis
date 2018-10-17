#ifndef STREAMGRIDS_H
#define STREAMGRIDS_H

#include <QDialog>

namespace Ui {
class StreamGrids;
}

class StreamGrids : public QDialog
{
    Q_OBJECT

public:
    explicit StreamGrids(QWidget *parent = 0, QString filename_open_project = "");
    ~StreamGrids();

    QString LogsString;

private slots:
    void on_pushButtonFlowAccGrids_clicked();

    void on_pushButtonStreamGrids_clicked();

    void on_pushButtonSuggestMe_clicked();

    void on_pushButtonRun_clicked();

    void on_pushButtonClose_clicked();

    void on_pushButtonHelp_clicked();

    void on_lineEditThreshold_textChanged();

    void pushButtonSetFocus();

private:


    void Clear_Log();

    bool Check_FlowAccGrids_Input(QString file);

    bool Check_Threshold_Input(QString threshold);

    bool Check_StreamGrids_Output(QString file, bool color_and_message_if_exists);

    bool Load_Project_Settings();

    Ui::StreamGrids *ui;

    QString filename_open_project;

};

#endif // STREAMGRIDS_H
