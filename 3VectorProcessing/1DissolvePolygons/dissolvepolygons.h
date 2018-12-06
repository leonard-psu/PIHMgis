#ifndef DISSOLVEPOLYGONS_H
#define DISSOLVEPOLYGONS_H

#include <QDialog>
#include <QException>

namespace Ui {
class DissolvePolygons;
}

class DissolvePolygons : public QDialog
{
    Q_OBJECT

public:
    explicit DissolvePolygons(QWidget *parent = 0, QString filename_open_project = "No Project Provided");
    ~DissolvePolygons();


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

    Ui::DissolvePolygons *ui;
    QString filename_open_project;
    QString LogsString;

};

#endif // DISSOLVEPOLYGONS_H
