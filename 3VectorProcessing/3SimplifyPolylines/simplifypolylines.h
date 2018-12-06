#ifndef SIMPLIFYPOLYLINES_H
#define SIMPLIFYPOLYLINES_H

#include <QDialog>

namespace Ui {
class SimplifyPolylines;
}

class SimplifyPolylines : public QDialog
{
    Q_OBJECT

public:
    explicit SimplifyPolylines(QWidget *parent = 0, QString filename_open_project = "No Project Provided");
    ~SimplifyPolylines();

    int DEMResolution;

public slots:

    void pushButtonSetFocus();

private slots:
    void on_pushButtonAdd_clicked();

    void on_pushButtonRemove_clicked();

    void on_pushButtonClear_clicked();

    void on_pushButtonRun_clicked();

    void on_pushButtonClose_clicked();

    void on_pushButtonHelp_clicked();

    void on_tableWidget_cellChanged(int row, int column);

private:

    void Clear_Log();
    void Log_Error_Message(QString message);
    void Log_Message(QString message);

    bool Load_Project_Settings();

    bool Check_File_Valid(QString file);

    Ui::SimplifyPolylines *ui;
    QString filename_open_project;
    QString LogsString;

};

#endif // SIMPLIFYPOLYLINES_H
