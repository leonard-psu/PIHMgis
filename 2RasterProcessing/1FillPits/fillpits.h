#ifndef FILLPITS_H
#define FILLPITS_H

#include <QDialog>

namespace Ui {
class FillPits;
}

class FillPits : public QDialog
{
    Q_OBJECT

public:
    explicit FillPits(QWidget *parent = 0, QString filename_open_project = "");
    ~FillPits();
    QString LogsString;


private slots:
    void on_pushButtonDEM_clicked();

    void on_pushButtonFillPits_clicked();

    void on_pushButtonRun_clicked();

    void on_pushButtonClose_clicked();

    void on_pushButtonHelp_clicked();

    void pushButtonSetFocus();


private:

    bool Check_DEM_Input(QString dem);

    bool Check_Fillpit_Output(QString fillpits, bool message );

    void Clear_Log();

    bool Load_Project_Settings();

    Ui::FillPits *ui;
    QString filename_open_project;
};

#endif // FILLPITS_H
