#ifndef TINSHAPELAYER_H
#define TINSHAPELAYER_H

#include <QDialog>

namespace Ui {
class TINShapeLayer;
}

class TINShapeLayer : public QDialog
{
    Q_OBJECT

public:
    explicit TINShapeLayer(QWidget *parent = 0, QString filename_open_project = "");
    ~TINShapeLayer();

    QString LogsString;
    //QStringList ProjectIOStringList;

private slots:
    void on_pushButtonElementFile_clicked();

    void on_pushButtonNodeFile_clicked();

    void on_pushButtonTINFile_clicked();

    void on_pushButtonRun_clicked();

    void on_pushButtonClose_clicked();

    void on_pushButtonHelp_clicked();

    void pushButtonSetFocus();


private:

    void Clear_Log();

    bool Load_Project_Settings();

    bool Check_Element_Input(QString file);

    bool Check_Node_Input(QString file);

    bool Check_TinShape_Output(QString file, bool message);


    Ui::TINShapeLayer *ui;
    QString filename_open_project;

};

#endif // TINSHAPELAYER_H
