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
    explicit DissolvePolygons(QWidget *parent = 0, QString filename_open_project = "");
    ~DissolvePolygons();

    QString LogsString;
    //QStringList ProjectIOStringList;


private slots:

    void on_pushButtonAdd_clicked();

    void on_pushButtonRemove_clicked();

    void on_pushButtonClear_clicked();

    void on_pushButtonRun_clicked();

    void on_pushButtonClose_clicked();

    void on_pushButtonHelp_clicked();

    void pushButtonSetFocus();

    void Clear_Log();

    bool Check_File_Valid(QString file);

    bool Load_Project_Settings();


private:
    Ui::DissolvePolygons *ui;
    QString filename_open_project;

};

#endif // DISSOLVEPOLYGONS_H
