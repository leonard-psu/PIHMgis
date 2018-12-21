#ifndef VARIABLESETTINGS_H
#define VARIABLESETTINGS_H

#include <QDialog>

namespace Ui {
class VariableSettings;
}

class VariableSettings : public QDialog
{
    Q_OBJECT

public:
    explicit VariableSettings(QWidget *parent = nullptr);
    ~VariableSettings();

private slots:

    void on_doubleSpinBox_dissolve_valueChanged(double arg1);

private:
    Ui::VariableSettings *ui;
};

#endif // VARIABLESETTINGS_H
