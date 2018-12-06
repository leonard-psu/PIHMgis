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
    explicit DelaunayTriangulation(QWidget *parent = 0, QString filename_open_project = "No Project Provided");
    ~DelaunayTriangulation();

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

    void on_pushButtonFIND_clicked(bool checked);

private:

    void Clear_Log();
    void Log_Error_Message(QString message);
    void Log_Message(QString message);

    bool Load_Project_Settings();

    bool Check_PSLG_Input(QString file);
    bool Check_Angle(QString file, bool message);
    bool Check_Area(QString file, bool message);
    bool Check_Others(QString file, bool message);
    bool Check_File_Valid(QString file);
    bool Check_Triangle_Software_Input(QString file);
    bool Check_TIN_Output(QString file, bool message);

    void on_pushButtonFIND_clicked();
    void on_lineEditFIND_textChanged(const QString &arg1);

    Ui::DelaunayTriangulation *ui;
    QString filename_open_project;
    QString LogsString;

};

#endif // DELAUNAYTRIANGULATION_H
