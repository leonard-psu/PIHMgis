#include <QDebug>
#include "main.h"
#include "globals.h"

// User interface to PIHMgis v3.5
PIHMgisDialog *main_window;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to display message on main window
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Print_Message_To_Main_Dialog(QString message)
{
    if(main_window != nullptr)
    {
        main_window->Log_Message(message);
    }
    else
    {
        //Last resort, print to console window
         qDebug() << message;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Check if value is Numeric
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Is_String_Integer(QString input)
{
    if(print_debug_messages)
        qDebug() << "INFO: Is_String_Numeric()";

    bool result = false;

    try {

        bool integer_check = false;
        bool double_check = false;
        bool float_check = false;
        bool long_check = false;

        //input.toDouble(&result);
        input.toInt(&integer_check);
        input.toDouble(&double_check);
        input.toFloat(&float_check);
        input.toLong(&long_check);

        if(integer_check)
            result = true;
        if(double_check)
            result = true;
        if(float_check)
            result = true;
        if(long_check)
            result = true;

    }
    catch (...) {
        qDebug() << "Error: Is_String_Numeric. Assuming value is false;";
        result = false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Check if value is Numeric
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool fileExists(QString path) {

    if(print_debug_messages)
        qDebug() << "INFO: fileExists()";

    try {

        QFileInfo check_file(path);

        // check if file exists and if yes: Is it really a file and no directory?
        if (check_file.exists() && check_file.isFile()) {
            return true;
        } else {
            return false;
        }

    } catch (...) {
        qDebug() << "Error: fileExists. Assuming value is false;";
    }
    return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get file size
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
qint64 file_Size(QString path){

    if(print_debug_messages)
        qDebug() << "INFO: file_Size()";

    try {

        QFileInfo check_file(path);

        // check if file exists and if yes: Is it really a file and no directory?
        if (check_file.exists() && check_file.isFile())
        {
            return check_file.size();
        } else {
            return -1;
        }

    } catch (...) {
        qDebug() << "Error: file_Size. Providing -100 value";
        return -100;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Main function. Start QApplication and main dialog window
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
    try {

        qDebug() << "Starting PIHMgis v3.5";

        QApplication a(argc, argv);

        main_window = new PIHMgisDialog();
        main_window->show();

        return a.exec();

    } catch (...) {
        qDebug() << "Error Starting PIHMgis v3.5";
    }
}
