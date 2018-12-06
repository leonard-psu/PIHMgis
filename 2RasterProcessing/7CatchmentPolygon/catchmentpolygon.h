#ifndef CATCHMENTPOLYGON_H
#define CATCHMENTPOLYGON_H

#include <QDialog>

namespace Ui {
class CatchmentPolygon;
}

class CatchmentPolygon : public QDialog
{
    Q_OBJECT

public:
    explicit CatchmentPolygon(QWidget *parent = 0, QString filename_open_project = "No Project Provided");
    ~CatchmentPolygon();


private slots:

    void on_pushButtonCatchmentGrids_clicked();

    void on_pushButtonCatchmentPolygon_clicked();

    void on_pushButtonRun_clicked();

    void on_pushButtonClose_clicked();

    void on_pushButtonHelp_clicked();

    void pushButtonSetFocus();

private:

    void Clear_Log();
    void Log_Error_Message(QString message);
    void Log_Message(QString message);

    bool Check_CatchmentGrids_Input(QString file);
    bool Check_CatchmentPolygon_Output(QString file, bool color_and_message_if_exists);

    bool Load_Project_Settings();

    Ui::CatchmentPolygon *ui;
    QString filename_open_project;
    QString LogsString;

};

#endif // CATCHMENTPOLYGON_H
