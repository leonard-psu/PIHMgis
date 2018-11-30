#ifndef INSPECTPROJECT_H
#define INSPECTPROJECT_H

#include <QDialog>

namespace Ui {
class InspectProject;
}

class InspectProject : public QDialog
{
    Q_OBJECT

public:
    explicit InspectProject(QWidget *parent = nullptr, QString filename_open_project = "None");
    ~InspectProject();

private slots:
    void on_pushButton_FIND_clicked();

    void on_pushButton_OK_clicked();

    void on_pushButton_CLEAR_clicked();

private:
    bool Load_Project_Settings();
    void Clear_Search(bool reset_find);

    Ui::InspectProject *ui;
    QString filename_open_project;
    QString LogsString;
    QString last_search;


};

#endif // INSPECTPROJECT_H
