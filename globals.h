#ifndef GLOBALS_H
#define GLOBALS_H

#include <QDir>
#include <QDebug>


static bool print_debug_messages = false;  //Print to console window
static bool print_log_messages = true;     //Print to widget log window (Only important messages)

static float epsilon = 0.000001f;

extern QString user_pihmgis_root_folder;
extern QString user_pihmgis_project_folder;

extern bool fileExists(QString path);
extern qint64 file_Size(QString path);


struct Time_Values
{
    int time_step1;
    int time_step2;

};

void Print_Message_To_Main_Dialog(QString message);

#endif // GLOBALS_H
