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
    explicit CatchmentPolygon(QWidget *parent = 0, QString filename_open_project = "");
    ~CatchmentPolygon();

    QString LogsString;
    //QStringList ProjectIOStringList;

private slots:
    void on_pushButtonCatchmentGrids_clicked();

    void on_pushButtonCatchmentPolygon_clicked();

    void on_pushButtonRun_clicked();

    void on_pushButtonClose_clicked();

    void on_pushButtonHelp_clicked();

    void pushButtonSetFocus();

    void Clear_Log();

    bool Check_CatchmentGrids_Input(QString file);

    bool Check_CatchmentPolygon_Output(QString file, bool message);


private:
    Ui::CatchmentPolygon *ui;
    QString filename_open_project;

};

#endif // CATCHMENTPOLYGON_H
