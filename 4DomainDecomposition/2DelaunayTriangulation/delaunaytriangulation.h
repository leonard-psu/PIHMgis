#ifndef DELAUNAYTRIANGULATION_H
#define DELAUNAYTRIANGULATION_H

#include <QDialog>

namespace Ui {
class DelaunayTriangulation;
}

class DelaunayTriangulation : public QDialog
{
    Q_OBJECT

public:
    explicit DelaunayTriangulation(QWidget *parent = 0, QString filename_open_project = "");
    ~DelaunayTriangulation();

    QString LogsString;
    //QStringList ProjectIOStringList;

private slots:
    void on_pushButtonPSLG_clicked();

    void on_checkBoxAngle_toggled(bool checked);

    void on_checkBoxArea_toggled(bool checked);

    void on_checkBoxOthers_toggled(bool checked);

    void on_lineEditAngle_textChanged(const QString &arg1);

    void on_lineEditArea_textChanged(const QString &arg1);

    void on_lineEditOthers_textChanged(const QString &arg1);

    void on_pushButtonRun_clicked();

    void on_pushButtonClose_clicked();

    void on_pushButtonHelp_clicked();

    void pushButtonSetFocus();

    void Clear_Log();

    bool Load_Project_Settings();

    bool Check_PSLG_Input(QString file);

    bool Check_Angle(QString file, bool message);

    bool Check_Area(QString file, bool message);

    bool Check_Others(QString file, bool message);

    bool Check_File_Valid(QString file);

    void on_pushButtonFIND_clicked();

    bool Check_Triangle_Software_Input(QString file);

    void on_lineEditFIND_textChanged(const QString &arg1);

    bool Check_TIN_Output(QString file, bool message);


private:
    Ui::DelaunayTriangulation *ui;
    QString filename_open_project;

};

#endif // DELAUNAYTRIANGULATION_H
