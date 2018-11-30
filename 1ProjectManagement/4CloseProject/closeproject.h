#ifndef CLOSEPROJECT_H
#define CLOSEPROJECT_H

#include <QDialog>

namespace Ui
{
    class CloseProject;
}

class CloseProject : public QDialog
{
    Q_OBJECT

public:
    CloseProject(QWidget *parent = 0, QString filename_open_project = "None");
    ~CloseProject();

    bool user_closed_project();

private slots:
    void on_pushButtonHelp_clicked();
    void on_pushButtonClose_clicked();

    void on_pushButtonCloseProject_clicked();

private:

    void Clear_Log();
    bool Load_Project_Settings();

    Ui::CloseProject *ui;
    QString filename_open_project;
    QString LogsString;

    bool user_wants_project_closed;

};

#endif // CLOSEPROJECT_H
