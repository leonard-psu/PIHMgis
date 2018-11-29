#ifndef NEWPROJECT_H
#define NEWPROJECT_H

#include <QDialog>
#include <QDate>

namespace Ui
{
    class NewProject;
}

class NewProject : public QDialog
{
    Q_OBJECT

public:
    NewProject(QWidget *parent = 0, QString workspace_folder = "Not provided", QString project_folder = "Not provided", QString project_name = "Not provided");
    ~NewProject();

    QString get_Workspace_Folder();
    QString get_Project_Folder();
    QString get_Project_Name();
    bool get_User_Created_New_Project();

private:
    Ui::NewProject *ui;

private slots:
    void on_pushButtonCreate_clicked();
    void on_pushButtonHelp_clicked();
    void on_pushButtonClose_clicked();
    void on_pushButtonFile_clicked();

private:
    void Clear_Log();
    void Log_Error_Message(QString message);
    void Log_Message(QString message);

    int check_pihmgis_project_exists(QString folder, QString project_folder);
    bool create_default_project_workspace(QString pihmgis_root_folder, QString project_folder);
    bool create_default_PIHMgis_project_file(QString pihmgis_root_folder, QString project_folder, QString name);

    QString LogsString;
    bool did_user_create_new_project;

};

#endif
