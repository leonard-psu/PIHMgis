#ifndef POLYGONTOPOLYLINES_H
#define POLYGONTOPOLYLINES_H

#include <QDialog>

namespace Ui {
class PolygonToPolylines;
}

class PolygonToPolylines : public QDialog
{
    Q_OBJECT

public:
    explicit PolygonToPolylines(QWidget *parent = 0, QString filename_open_project = "No Project Provided");
    ~PolygonToPolylines();


private slots:

    void on_pushButtonAdd_clicked();

    void on_pushButtonRemove_clicked();

    void on_pushButtonClear_clicked();

    void on_pushButtonRun_clicked();

    void on_pushButtonClose_clicked();

    void on_pushButtonHelp_clicked();

    void pushButtonSetFocus();


private:

    void Clear_Log();
    void Log_Error_Message(QString message);
    void Log_Message(QString message);

    bool Check_File_Valid(QString file);

    bool Load_Project_Settings();

    Ui::PolygonToPolylines *ui;
    QString filename_open_project;
    QString LogsString;

};

#endif // POLYGONTOPOLYLINES_H
