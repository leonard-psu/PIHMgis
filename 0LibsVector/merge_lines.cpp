#include <QDebug>
#include <iostream>
#include <iomanip>

#include "./../0LibsShape/shapefil.h"
#include "globals.h"

using namespace std;

// User interface to PIHMgis v3.5
extern PIHMgisDialog *main_window;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// merge_lines
// Used in 3VectorProcessing
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int merge_lines(QStringList shpFileNames, QStringList dbfFileNames, QString qnewshpFileName, QString qnewdbfFileName)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start merge_lines";

    try {


        if(shpFileNames.empty())
        {
            main_window->Log_Message("[merge_lines] Error[-1000] shpFileNames.empty().");
            return -1000;
        }

        if(dbfFileNames.empty())
        {
            main_window->Log_Message("[merge_lines] Error[-1001] dbfFileNames.empty().");
            return -1001;
        }

        int fileCount = shpFileNames.count();
        int fileCount2 = dbfFileNames.count();

        if(fileCount != fileCount2)
        {
            main_window->Log_Message("[merge_lines] Error[-1002] shpFileNames.count != dbfFileNames.count");
            return -1002;
        }

        if(fileCount < 1)
        {
            main_window->Log_Message("[merge_lines] Error[-1003] shpFileNames.count < 1");
            return -1003;
        }

        if(fileCount2 < 1)
        {
            main_window->Log_Message("[merge_lines] Error[-1004] dbfFileNames.count < 1");
            return -1004;
        }

        if(qnewshpFileName == nullptr)
        {
            main_window->Log_Message("[merge_lines] Error[-1005] Invalid qnewshpFileName.");
            return -1005;
        }

        if(qnewdbfFileName == nullptr)
        {
            main_window->Log_Message("[merge_lines] Error[-1006] Invalid qnewdbfFileName.");
            return -1006;
        }

        if(qnewshpFileName.length() < 1)
        {
            main_window->Log_Message("[merge_lines] Error[-1007] Invalid qnewshpFileName.");
            return -1007;
        }

        if(qnewdbfFileName.length() < 1)
        {
            main_window->Log_Message("[merge_lines] Error[-1008] Invalid qnewdbfFileName.");
            return -1008;
        }

        QByteArray fname = qnewshpFileName.toLatin1();
        char *newshpFileName = fname.data();
        QByteArray fname1 = qnewdbfFileName.toLatin1();
        char *newdbfFileName = fname1.data();

        int recordCount = 0;
        SHPObject *obj;

        SHPHandle newshp = SHPCreate(newshpFileName, SHPT_ARC);
        if(newshp == nullptr)
        {
            main_window->Log_Message("[merge_lines] Error[-1009] newshpFileName is NULL. ");
            return -1009;
        }

        DBFHandle newdbf = DBFCreate(newdbfFileName);
        if(newdbf == nullptr)
        {
            main_window->Log_Message("[merge_lines] Error[-1010] newdbfFileName is NULL. ");
            SHPClose(newshp);
            return -1010;
        }

        int fld = DBFAddField(newdbf, "ID", FTInteger, 5, 0);
        if(fld < 0)
        {
            main_window->Log_Message("[merge_lines] Error[-1011] Add field ID failed. ");
            SHPClose(newshp);
            DBFClose(newdbf);
            return -1011;
        }

        int k=0;

        bool error_found = false;
        bool record_error_found = false;
        bool split_error_found = false;


        for(int i = 0; i < fileCount; i++)
        {
            QByteArray fname = shpFileNames[i].toLatin1();
            char *tmpshpFileName = fname.data();
            QByteArray fname1 = dbfFileNames[i].toLatin1();
            char *tmpdbfFileName = fname1.data();

            SHPHandle shp = SHPOpen(tmpshpFileName, "rb");

            if(shp == nullptr)
            {
                main_window->Log_Message("[merge_lines] Error[-2001] shpFileName is NULL. File: " + QString(shpFileNames[i]));
                error_found = true;
            }

            if(error_found == false) //Note any previous error means nothing will happen next
            {
                DBFHandle dbf = DBFOpen(tmpdbfFileName, "rb");
                if(dbf == nullptr)
                {
                    main_window->Log_Message("[merge_lines] Error[-2002] dbfFileNames is NULL. File: " + QString(dbfFileNames[i]));
                    SHPClose(shp);
                    error_found = true;
                }

                if(error_found == false) //Note any previous error means nothing will happen next
                {
                    int InfoShpType;
                    SHPGetInfo (shp, nullptr, &InfoShpType, nullptr, nullptr);

                    if ( InfoShpType != SHPT_ARC )
                    {
                        main_window->Log_Message("[merge_lines] Error[-2003] Not a SHPT_ARC. File: " + QString(shpFileNames[i]));
                        main_window->Log_Message("[merge_lines] Error[-2004] SHAPE TYPE = " +QString::number(InfoShpType));
                        error_found = true;
                        SHPClose(shp);
                        DBFClose(dbf);
                    }

                    if(error_found == false)
                    {
                        recordCount = DBFGetRecordCount(dbf);

                        if(recordCount < 1)
                        {
                            main_window->Log_Message("[merge_lines] Error[-2005] DBFGetRecordCount Invalid value. File: " + QString(shpFileNames[i]));
                            record_error_found = true;
                        }
                        else
                        {
                            for(int j = 0; j < recordCount; j++)
                            {
                                obj = SHPReadObject(shp, j);

                                if(obj == nullptr)
                                {
                                    main_window->Log_Message("[merge_lines] Error[-2006] SHPReadObject is null. File: " + QString(shpFileNames[i]));
                                    record_error_found = true;
                                }
                                else {

                                    if ( obj->nVertices > 2 )
                                    {
                                        main_window->Log_Message("[merge_lines] Error[-2007] SHPReadObject nVertices > 2. You need to split file: " + QString(shpFileNames[i]));
                                        record_error_found = true;
                                        split_error_found = true;
                                    }

                                    if(record_error_found == false)
                                    {
                                        if ( SHPWriteObject(newshp, -1, obj) < 0 )
                                        {
                                            main_window->Log_Message("[merge_lines] Error[-2008] SHPWriteObject failed. File: " + QString(shpFileNames[i]));
                                            record_error_found = true;
                                        }

                                        if(record_error_found == false)
                                        {
                                            if ( ! DBFWriteIntegerAttribute(newdbf, k++, fld, j+1) )
                                            {
                                                main_window->Log_Message("[merge_lines] Error[-2009] DBFWriteIntegerAttribute failed. File: " + QString(shpFileNames[i]));
                                                record_error_found = true;
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        SHPClose(shp);
                        DBFClose(dbf);
                    }
                }
            }
        }

        if(error_found == false)
        {
            SHPClose(newshp);
            DBFClose(newdbf);
        }

        if(split_error_found)
        {
            main_window->Log_Message("[merge_lines] Error[-9000] User needs to split input file(s). Check log file.");
            return -9000;
        }

        if(record_error_found)
        {
            main_window->Log_Message("[merge_lines] Error[-9001] Record error(s). User needs to check with GIS");
            return -9001;
        }

        if(error_found)
        {
            main_window->Log_Message("[merge_lines] Error[-9002] Found error(s). User needs to check with GIS");
            return -9002;
        }

        return 0;

    } catch (...)
    {
        qDebug() << "Error: merge_lines is returning w/o checking";
        return -5000;
    }

}
