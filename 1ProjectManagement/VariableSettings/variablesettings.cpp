#include "variablesettings.h"
#include "ui_variablesettings.h"

#include "globals.h"

#include "QDebug"

extern double dissolve_epsilon;


VariableSettings::VariableSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VariableSettings)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start VariableSettings";

    try {

        ui->setupUi(this);
        ui->doubleSpinBox_dissolve->setValue(dissolve_epsilon);

    }
    catch (...)
    {
        qDebug() << "Error: VariableSettings is returning w/o checking";

    }

}

VariableSettings::~VariableSettings()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ~VariableSettings";

    try {

        delete ui;

    }
    catch (...)
    {
        qDebug() << "Error: ~VariableSettings is returning w/o checking";

    }

}


void VariableSettings::on_doubleSpinBox_dissolve_valueChanged(double arg1)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start on_doubleSpinBox_dissolve_valueChanged";

    try {

        //Default float dissolve_epsilon = 0.000001f;
        dissolve_epsilon = arg1;

    }
    catch (...)
    {
        qDebug() << "Error: on_doubleSpinBox_dissolve_valueChanged is returning w/o checking";

    }

}
