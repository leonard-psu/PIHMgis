#ifndef GLOBALS_H
#define GLOBALS_H

#include <QDir>
#include <QDebug>


static bool print_debug_messages = true;
static float epsilon = 0.000001f;

extern QString user_pihmgis_root_folder;
extern QString user_pihmgis_project_folder;

extern bool fileExists(QString path);
extern qint64 file_Size(QString path);

#endif // GLOBALS_H
