#ifndef READTOPOLOGY_H
#define READTOPOLOGY_H

#include <QDialog>

namespace Ui {
class ReadTopology;
}

class ReadTopology : public QDialog
{
    Q_OBJECT

public:
    explicit ReadTopology(QWidget *parent = 0, QString filename_open_project = "");
    ~ReadTopology();

    QString LogsString;
    //QStringList ProjectIOStringList;

private slots:
    void on_pushButtonMerge_clicked();

    void on_pushButtonPSLG_clicked();

    void on_pushButtonRun_clicked();

    void on_pushButtonClose_clicked();

    void on_pushButtonHelp_clicked();

    void pushButtonSetFocus();

    void Clear_Log();

    bool Load_Project_Settings();

    bool Check_File_Valid(QString file);

    bool Check_MergeVector_Input(QString file);

    bool Check_PSLG_Output(QString file, bool message);


private:
    Ui::ReadTopology *ui;

    QString filename_open_project;

};

#endif // READTOPOLOGY_H
