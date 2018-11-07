#ifndef IMPORTPROJECT_H
#define IMPORTPROJECT_H

#include <QDialog>

namespace Ui
{
    class ImportProject;
}

class ImportProject : public QDialog
{
    Q_OBJECT

public:
    ImportProject(QWidget *parent = 0);
    ~ImportProject();
    QString LogsString;

private slots:
    void on_pushButtonHelp_clicked();
    void on_pushButtonImport_clicked();
    void on_pushButtonClose_clicked();
    void on_pushButtonProject_clicked();


    void on_pushButtonProject_DataFolder_clicked();

private:
    void Clear_Log();
    void Log_Error_Message(QString message);
    void Log_Message(QString message);

    QStringList Find_Project_Directories(QString input_file_name, QString basefolder);
    QMap<QString,QString> Get_Map_Directories(QString input_file_name, QString basefolder);
    QString Find_File_In_Base_Folder(QString input_string,  QString data_folder);


    bool Find_Replace_All_Project_Directories(QString input_file_name, QString basefolder, QString output_file_name);
    bool Find_Replace_Only_Project_Directories(QString input_file_name, QString basefolder, QString only_folder, QString output_file_name);

    QStringList Get_Folder_List(const QString& str);

    Ui::ImportProject *ui;

    QString filename_open_project;

};

#endif // IMPORTPROJECT_H
