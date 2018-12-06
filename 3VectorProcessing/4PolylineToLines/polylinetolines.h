#ifndef POLYLINETOLINES_H
#define POLYLINETOLINES_H

#include <QDialog>

namespace Ui {
class PolylineToLines;
}

class PolylineToLines : public QDialog
{
    Q_OBJECT

public:
    explicit PolylineToLines(QWidget *parent = 0, QString filename_open_project = "No Project Provided");
    ~PolylineToLines();


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

    bool Load_Project_Settings();

    bool Check_File_Valid(QString file);


    Ui::PolylineToLines *ui;
    QString filename_open_project;
    QString LogsString;

};

#endif // POLYLINETOLINES_H
