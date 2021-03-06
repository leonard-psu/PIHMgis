#include <QtGui>
#include <QString>

#include "IOProjectFile.h"
#include "globals.h"

// User interface to PIHMgis v3.5
extern PIHMgisDialog *main_window;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper function to READ/Search for content in project file
// Note, Messages are reported to both main window and console, as these are serious errors.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
QStringList ReadModuleLine(QString ProjectFileName, QString Module)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ReadModuleLine";

    try {

        QFile ProjectFile(ProjectFileName);
        if( !ProjectFile.exists() )
        {
            main_window->Log_Message("[ReadModuleLine] File does not exist: " + ProjectFileName);
            QStringList NullStringList;
            return NullStringList;
        }

        bool fcheck = ProjectFile.open(QIODevice::ReadOnly | QIODevice::Text);
        if(fcheck == false)
        {
            main_window->Log_Message("[ReadModuleLine] Error opening file: " + ProjectFileName);
            QStringList NullStringList;
            return NullStringList;
        }

        QTextStream ProjectFileTextStream(&ProjectFile);
        QString ProjectFileLineString;
        QStringList ProjectFileLineStringList;
        QStringList result;

        while ( ! ProjectFileTextStream.atEnd() )
        {
            ProjectFileLineString     = ProjectFileTextStream.readLine();
            ProjectFileLineStringList = ProjectFileLineString.split(",");

            if ( ProjectFileLineStringList.at(0) == Module )
            {
                //org return ProjectFileLineStringList;
                result = ProjectFileLineStringList;
                break;
            }
        }

        ProjectFile.close();
        return result;

    } catch (...) {

        main_window->Log_Message("Warning [ReadModuleLine] ReadModuleLine is returning NullStringList");
        QStringList NullStringList;
        return NullStringList;
    }

    if(print_debug_messages)
        main_window->Log_Message("Warning [ReadModuleLine] ReadModuleLine is returning NullStringList");

    QStringList NullStringList;
    return NullStringList;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper function to WRITE/Append for content in project file
// Note use of temporary file creation
// Note, Messages are reported to both main window and console, as these are serious errors.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool WriteModuleLine(QString ProjectFileName, QStringList WriteStringList)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start WriteModuleLine";

    try {

        QString Module;
        Module = WriteStringList.at(0);

        QString TempProjectFileName = user_pihmgis_root_folder + user_pihmgis_project_folder + "/TempProjectFile.txt";

        bool fcheck = QFile::remove(TempProjectFileName);
        if( fcheck == false )
        {
            if(print_many_messages)
            {
                main_window->Log_Message("[WriteModuleLine] Warning failed to remove Temporary Project File: " + TempProjectFileName);
            }
        }

        if ( QFile::copy(ProjectFileName, TempProjectFileName) == false)
        {
            main_window->Log_Message("[WriteModuleLine] Unable to Copy Project File to Temporary Project File: " + TempProjectFileName);
            return false;
        }

        QFile ProjectFile(ProjectFileName);
        fcheck = ProjectFile.open(QIODevice::WriteOnly | QIODevice::Text);
        if( fcheck == false )
        {
            main_window->Log_Message("[WriteModuleLine] Failed to open ProjectFile: " + ProjectFileName);
            return false;
        }

        QTextStream ProjectFileTextStream(&ProjectFile);
        QFile TempProjectFile(TempProjectFileName);
        fcheck = TempProjectFile.open(QIODevice::ReadOnly | QIODevice::Text);
        if( fcheck == false )
        {
            main_window->Log_Message("[WriteModuleLine] Failed to open TempProjectFile: " + TempProjectFileName);
            return false;
        }

        QTextStream TempProjectFileTextStream(&TempProjectFile);

        QString ProjectFileLineString;
        QStringList ProjectFileLineStringList;

        while ( ! TempProjectFileTextStream.atEnd() )
        {
            ProjectFileLineString     = TempProjectFileTextStream.readLine();
            ProjectFileLineStringList = ProjectFileLineString.split(",");

            if ( ProjectFileLineStringList.at(0) == Module )
            {
                ProjectFileTextStream << "#" << ProjectFileLineString << endl;
                break;
            }

            ProjectFileTextStream << ProjectFileLineString << endl;
        }

        for (int i=0 ; i < WriteStringList.size(); i++)
        {
            ProjectFileTextStream << WriteStringList.at(i) << ",";
        }

        ProjectFileTextStream << endl;

        while ( ! TempProjectFileTextStream.atEnd() )
        {
            ProjectFileTextStream << TempProjectFileTextStream.readLine() << endl;
        }

        fcheck = QFile::remove(TempProjectFileName);
        if( fcheck == false )
        {
            if(print_many_messages)
            {
                main_window->Log_Message("[WriteModuleLine] Warning failed to remove TempProjectFile: " + TempProjectFileName);
            }
        }

        ProjectFile.close();

        return true;

    } catch (...) {

        qDebug() << "Error: WriteModuleLine is returning NullStringList";
        return false;
    }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper function to DELETE content in project file
// Note, Messages are reported to both main window and console, as these are serious errors.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool DeleteModuleLine(QString ProjectFileName, QString Module)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start DeleteModuleLine";

    try {

        QString TempProjectFileName = user_pihmgis_root_folder + user_pihmgis_project_folder + "/TempProjectFile.txt";

        bool fcheck = QFile::remove(TempProjectFileName);
        if( fcheck == false )
        {
            if(print_many_messages)
            {
                main_window->Log_Message("[DeleteModuleLine] Warning failed to remove TempProjectFile: " + TempProjectFileName);
            }
        }

        if ( QFile::copy(ProjectFileName, TempProjectFileName) == false)
        {
            main_window->Log_Message("[DeleteModuleLine] Unable to Copy Project File to Temporary Project File: " + TempProjectFileName);
            return false;
        }

        QFile ProjectFile(ProjectFileName);
        fcheck = ProjectFile.open(QIODevice::WriteOnly | QIODevice::Text);
        if( fcheck == false )
        {
            main_window->Log_Message("[DeleteModuleLine] Failed to open ProjectFileName: " + ProjectFileName);
            return false;
        }

        QTextStream ProjectFileTextStream(&ProjectFile);

        QFile TempProjectFile(TempProjectFileName);

        fcheck = TempProjectFile.open(QIODevice::ReadOnly | QIODevice::Text);
        if( fcheck == false )
        {
            main_window->Log_Message("[DeleteModuleLine] Failed to open ProjectFileName: " + ProjectFileName);
            ProjectFile.close();
            return false;
        }

        QTextStream TempProjectFileTextStream(&TempProjectFile);

        QString ProjectFileLineString;
        QStringList ProjectFileLineStringList;

        while ( ! TempProjectFileTextStream.atEnd() )
        {
            ProjectFileLineString     = TempProjectFileTextStream.readLine();
            ProjectFileLineStringList = ProjectFileLineString.split(",");

            if ( ProjectFileLineStringList.at(0) == Module )
                continue;

            ProjectFileTextStream << ProjectFileLineString << endl;
        }


        ProjectFile.close();

        fcheck = QFile::remove(TempProjectFileName);
        if( fcheck == false )
        {
            if(print_many_messages)
            {
                main_window->Log_Message("[DeleteModuleLine] Warning failed to remove TempProjectFile: " + TempProjectFileName);
            }
        }

        return true;

    } catch (...) {

        qDebug() << "Error: DeleteModuleLine is returning false";
        return false;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper function to Check folder access
// Note, Use of OS defines
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CheckFolderAccess(QString folderName, QString AccessMode)
{
    bool result = false;

    if(print_debug_messages)
        qDebug() << "INFO: Start CheckFolderAccess";

    try {

#if (defined (_WIN32) || defined (_WIN64))
        //http://doc.qt.io/archives/qt-4.8/qfile.html#platform-specific-issues

        if(folderName.contains(QDir::homePath()))
            return true;
#endif
        QFileInfo my_dir(folderName);

        if ( AccessMode == "ReadOnly" )
        {
            if(my_dir.isDir() && my_dir.isReadable())
            {
                result = true;
            }
        }

        if ( AccessMode == "WriteOnly" )
        {
            if(my_dir.isDir() && my_dir.isWritable())
            {
                result = true;
            }
        }

        if ( AccessMode == "ReadWrite" )
        {
            if(my_dir.isDir())
            {
                if(my_dir.isReadable())
                {
                    if(my_dir.isWritable())
                    {
                        result = true;
                    }
                }
            }

        }



    } catch (...) {

        qDebug() << "Error: CheckFolderAccess is returning false";
        return false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper function to Check folder access from FILE PATH
// Note, Use of OS defines
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CheckFolderAccessFromFilePath(QString filenameandpath, QString AccessMode)
{
    bool result = false;

    if(print_debug_messages)
        qDebug() << "INFO: Start CheckFolderAccessFromFilePath";

    try {

#if (defined (_WIN32) || defined (_WIN64))
        //http://doc.qt.io/archives/qt-4.8/qfile.html#platform-specific-issues

        if(filenameandpath.contains(QDir::homePath()))
            return true;

#endif

        QFileInfo fi(filenameandpath);
        QString folderName = fi.dir().canonicalPath();

        QFileInfo my_dir(folderName);

        if ( AccessMode == "ReadOnly" )
        {
            if(my_dir.isDir() && my_dir.isReadable())
            {
                result = true;
            }
        }

        if ( AccessMode == "WriteOnly" )
        {
            if(my_dir.isDir() && my_dir.isWritable())
            {
                result = true;
            }
        }

        if ( AccessMode == "ReadWrite" )
        {
            if(my_dir.isDir())
            {
                if(my_dir.isReadable())
                {
                    if(my_dir.isWritable())
                    {
                        result = true;
                    }
                }
            }
        }

    } catch (...) {

        qDebug() << "Error: CheckFolderAccessFromFilePath is returning false";
        return false;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper function to Check file access.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CheckFileAccess(QString FileName, QString AccessMode)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start CheckFileAccess";

    try {

        QFile File;
        File.setFileName(FileName);

        if ( AccessMode == "ReadOnly" )
        {
            if ( ! File.open(QIODevice::ReadOnly | QIODevice::Text) )
                return false;
        }

        if ( AccessMode == "WriteOnly" )
        {
            if ( ! File.open(QIODevice::WriteOnly | QIODevice::Text) )
                return false;
        }

        if ( AccessMode == "ReadWrite" )
        {
            if ( ! File.open(QIODevice::ReadWrite | QIODevice::Text) )
                return false;
        }

        File.close();

        return true;

    } catch (...) {

        qDebug() << "Error: CheckFileAccess is returning false";
        return false;
    }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper function to Read Line Number.
// Not used. Is this needed for future versions?
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
QString readLineNumber(QString ProjectFileName, int LineNumber)
{
    if(print_many_messages)
        qDebug() << "INFO: Start readLineNumber";

    try {
        QString TempString;
        QFile ProjectFile(ProjectFileName);
        bool fcheck = ProjectFile.open(QIODevice::ReadOnly | QIODevice::Text);
        if( fcheck == false )
        {
            QString TempString;
            main_window->Log_Message("[readLineNumber] Failed to open ProjectFile: " + ProjectFileName);
            return TempString;
        }


        QTextStream ProjectFileTextStream(&ProjectFile);

        for (int i = 0; i < LineNumber; i++)
        {
            TempString = ProjectFileTextStream.readLine();
        }

        ProjectFile.close();

        return TempString;

    } catch (...) {

        QString TempString;
        qDebug() << "Error: readLineNumber is returning empty string";
        return TempString;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper function to WRITE Line Number.
// Not used. Is this needed for future versions?
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool writeLineNumber(QString ProjectFileName, int LineNumber, QString WriteString)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start writeLineNumber";

    try {

        int lineCount=0;
        QString TempString;

        QFile ProjectFile(ProjectFileName);
        bool fcheck = ProjectFile.open(QIODevice::ReadOnly | QIODevice::Text);
        if( fcheck == false )
        {
            main_window->Log_Message("[writeLineNumber] Failed to open ProjectFile: " + ProjectFileName);
            return false;
        }

        QTextStream ProjectFileTextStream(&ProjectFile);

        QString TempProjectFileName = user_pihmgis_root_folder + user_pihmgis_project_folder + "/TempProjectFile.txt";

        QFile TempProjectFile(TempProjectFileName);
        if ( ! TempProjectFile.open(QIODevice::WriteOnly | QIODevice::Text) )
        {
            return false;
        }

        QTextStream TempProjectFileTextStream(&TempProjectFile);

        while ( ! ProjectFileTextStream.atEnd() )
        {
            if(lineCount != 0)
            {
                TempString=ProjectFileTextStream.readLine();
                TempProjectFileTextStream <<"\n"<< TempString;
                lineCount++;
            }
            else
            {
                TempString=ProjectFileTextStream.readLine();
                TempProjectFileTextStream << TempString;
                lineCount++;
            }
        }

        lineCount = 0;
        ProjectFile.close();
        TempProjectFile.close();

        TempProjectFile.open(QIODevice::ReadOnly | QIODevice::Text);

        if ( ! ProjectFile.open(QIODevice::WriteOnly | QIODevice::Text) )
        {
            return false;
        }

        while ( ! TempProjectFileTextStream.atEnd() )
        {
            lineCount++;

            if(lineCount == LineNumber)
            {
                if(lineCount != 1)
                {
                    TempString=TempProjectFileTextStream.readLine();
                    ProjectFileTextStream << "\n" << WriteString;
                }
                else
                {
                    TempString=TempProjectFileTextStream.readLine();
                    ProjectFileTextStream << WriteString;
                }
            }
            else
            {
                if(lineCount != 1)
                {
                    TempString=TempProjectFileTextStream.readLine();
                    ProjectFileTextStream << "\n" << TempString;
                }
                else
                {
                    TempString=TempProjectFileTextStream.readLine();
                    ProjectFileTextStream << TempString;
                }
            }
        }

        if(lineCount < LineNumber)
        {
            for(int i=lineCount; i<LineNumber; i++)
            {
                ProjectFileTextStream <<"\n";
            }

            ProjectFileTextStream <<WriteString;
        }

        TempProjectFile.close();
        ProjectFile.close();

        // TODO remove TempProjectFileName

    }
    catch (...)
    {
        qDebug() << "Error: writeLineNumber is set to false";
        return false;
    }

    return true;

}
