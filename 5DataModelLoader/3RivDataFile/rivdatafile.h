#ifndef RIVDATAFILE_H
#define RIVDATAFILE_H

#include <QDialog>

namespace Ui {
class RivDataFile;
}

class RivDataFile : public QDialog
{
    Q_OBJECT

public:
    explicit RivDataFile(QWidget *parent = 0, QString filename_open_project = "No Project Provided");
    ~RivDataFile();

private slots:

    void on_pushButtonElementFile_clicked();

    void on_pushButtonNodeFile_clicked();

    void on_pushButtonNeighbourFile_clicked();

    void on_pushButtonRiverFile_clicked();

    void on_pushButtonRivDataFile_clicked();

    void on_pushButtonRun_clicked();

    void on_pushButtonClose_clicked();

    void on_pushButtonHelp_clicked();

    void pushButtonSetFocus();

private:

    void Clear_Log();
    void Log_Warning_Message(QString message);
    void Log_Error_Message(QString message);
    void Log_Message(QString message);

    bool Load_Project_Settings();

    bool Check_Element_Input(QString file);
    bool Check_Node_Input(QString file);
    bool Check_Neighbor_Input(QString file);
    bool Check_RiverShape_Input(QString file);

    bool Check_RiverData_Output(QString file, bool message);


    Ui::RivDataFile *ui;
    QString filename_open_project;
    QString LogsString;

};

#endif // RIVDATAFILE_H
