#ifndef CHECKPROJECT_H
#define CHECKPROJECT_H

#include <QDialog>

namespace Ui {
class CheckProject;
}

class CheckProject : public QDialog
{
    Q_OBJECT

public:
    explicit CheckProject(QWidget *parent = nullptr, QString folder = "");
    ~CheckProject();

private slots:
    void on_pushButtonClose_clicked();

    void on_pushButtonRecheck_clicked();

private:
    void Clear_Log();
    void Log_Error_Message(QString message);
    void Log_Message(QString message);

    int check_pihmgis_project_exists(QString folder);


    Ui::CheckProject *ui;
    QString LogsString;
    QString user_project_folder;

};

#endif // CHECKPROJECT_H
