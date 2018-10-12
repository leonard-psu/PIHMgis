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
    explicit PolygonToPolylines(QWidget *parent = 0, QString filename_open_project = "");
    ~PolygonToPolylines();

    QString LogsString;

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
    Ui::PolygonToPolylines *ui;
    QString filename_open_project;

};

#endif // POLYGONTOPOLYLINES_H
