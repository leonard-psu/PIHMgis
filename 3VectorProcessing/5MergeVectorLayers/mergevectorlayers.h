#ifndef MERGEVECTORLAYERS_H
#define MERGEVECTORLAYERS_H

#include <QDialog>

namespace Ui {
class MergeVectorLayers;
}

class MergeVectorLayers : public QDialog
{
    Q_OBJECT

public:
    explicit MergeVectorLayers(QWidget *parent = 0, QString filename_open_project = "No Project Provided");
    ~MergeVectorLayers();


private slots:
    void on_pushButtonAdd_clicked();

    void on_pushButtonRemove_clicked();

    void on_pushButtonClear_clicked();

    void on_pushButtonMergeLayer_clicked();

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
    bool Check_MergeLayer_Output(QString file, bool color_and_message_if_exists);

    Ui::MergeVectorLayers *ui;
    QString filename_open_project;
    QString LogsString;

};

#endif // MERGEVECTORLAYERS_H
