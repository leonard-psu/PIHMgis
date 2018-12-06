#ifndef STREAMPOLYLINE_H
#define STREAMPOLYLINE_H

#include <QDialog>

namespace Ui {
class StreamPolyline;
}

class StreamPolyline : public QDialog
{
    Q_OBJECT

public:
    explicit StreamPolyline(QWidget *parent = 0, QString filename_open_project = "No Project Provided");
    ~StreamPolyline();


private slots:

    void on_pushButtonStreamGrids_clicked();

    void on_pushButtonFlowDirGrids_clicked();

    void on_pushButtonStreamPolyline_clicked();

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
    bool Check_StreamPolyline_Output(QString file, bool color_and_message_if_exists);

    bool Load_Project_Settings();

    Ui::StreamPolyline *ui;
    QString filename_open_project;
    QString LogsString;

};

#endif // STREAMPOLYLINE_H
