#include <QDebug>
#include <iostream>
#include <iomanip>

#include "./../0LibsShape/shapefil.h"
#include "globals.h"

using namespace std;

// User interface to PIHMgis v3.5
extern PIHMgisDialog *main_window;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// polyline_splitlines
// Used in 3Vector Processing
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int polyline_splitlines(QString qshpFileName, QString qdbfFileName, QString qnewshpFileName, QString qnewdbfFileName)
{

    if(print_debug_messages)
        qDebug() << "INFO: Start polyline_splitlines";

    try {

        if(qshpFileName == nullptr)
        {
            main_window->Log_Message("[polyline_splitlines] Error[-1000] Invalid qshpFileName.");
            return -1000;
        }

        if(qdbfFileName == nullptr)
        {
            main_window->Log_Message("[polyline_splitlines] Error[-1001] Invalid qdbfFileName.");
            return -1001;
        }

        if(qnewshpFileName == nullptr)
        {
            main_window->Log_Message("[polyline_splitlines] Error[-1003] Invalid qnewshpFileName.");
            return -1003;
        }

        if(qnewdbfFileName == nullptr)
        {
            main_window->Log_Message("[polyline_splitlines] Error[-1004] Invalid qnewdbfFileName.");
            return -1004;
        }

        if(qshpFileName.length() < 1)
        {
            main_window->Log_Message("[polyline_splitlines] Error[-1005] Invalid qshpFileName.");
            return -1005;
        }

        if(qdbfFileName.length() < 1)
        {
            main_window->Log_Message("[polyline_splitlines] Error[-1006] Invalid qdbfFileName.");
            return -1006;
        }

        if(qnewshpFileName.length() < 1)
        {
            main_window->Log_Message("[polyline_splitlines] Error[-1007] Invalid qnewshpFileName.");
            return -1007;
        }

        if(qnewdbfFileName.length() < 1)
        {
            main_window->Log_Message("[polyline_splitlines] Error[-1008] Invalid qnewdbfFileName.");
            return -1008;
        }

        QByteArray fname = qshpFileName.toLatin1();
        char *shpFileName = fname.data();
        QByteArray fname1 = qdbfFileName.toLatin1();
        char *dbfFileName = fname1.data();
        QByteArray fname2 = qnewshpFileName.toLatin1();
        char *newshpFileName = fname2.data();
        QByteArray fname3 = qnewdbfFileName.toLatin1();
        char *newdbfFileName = fname3.data();


        SHPHandle shp = SHPOpen(shpFileName, "rb");
        if(shp == nullptr)
        {
            main_window->Log_Message("[polyline_splitlines] Error[-1009] SHPOpen failed. File: " + qshpFileName);
            return -1009;
        }

        DBFHandle dbf = DBFOpen(dbfFileName, "rb");
        if(dbf == nullptr)
        {
            main_window->Log_Message("[polyline_splitlines] Error[-1010] DBFOpen failed. File: " + qdbfFileName);
            SHPClose(shp);
            return -1010;

        }

        int InfoShpType = 0;

        SHPGetInfo (shp, nullptr, &InfoShpType, nullptr, nullptr);
        if ( InfoShpType != SHPT_ARC )
        {
            main_window->Log_Message("[polyline_splitlines] Error[-1011] Not a SHPT_ARC. File: " + qshpFileName);
            main_window->Log_Message("[polyline_splitlines] SHAPE TYPE = " + qshpFileName);
            SHPClose(shp);
            DBFClose(dbf);

            return -1011;
        }

        SHPHandle newshp = SHPCreate(newshpFileName, SHPT_ARC);
        if(newshp == nullptr)
        {
            main_window->Log_Message("[polyline_splitlines] Error[-1012] SHPCreate failed. File: " + qnewshpFileName);
            SHPClose(shp);
            DBFClose(dbf);

            return -1012;
        }

        DBFHandle newdbf = DBFCreate(newdbfFileName);
        if(newdbf == nullptr)
        {
            main_window->Log_Message("[polyline_splitlines] Error[-1013] DBFCreate failed. File: " + qnewdbfFileName);
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);

            return -1013;
        }

        int fld = DBFAddField(newdbf, "ID", FTInteger, 5, 0);
        if ( fld < 0 )
        {
            main_window->Log_Message("[polyline_splitlines] Error[-1014] DBFAddField failed. File: " + qnewdbfFileName);
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);

            return -1014;
        }

        int recordCount = DBFGetRecordCount(dbf);
        if ( recordCount < 0 )
        {
            main_window->Log_Message("[polyline_splitlines] Error[-1015] recordCount < 0. File: " + qdbfFileName);
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);

            return -1015;
        }

        if ( recordCount > 500000 ) //500000 is a guess
        {
            main_window->Log_Message("[polyline_splitlines] Error[-1016] 500000 is a guess. File: " + qdbfFileName);
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);

            return -1016;
        }

        double X[2], Y[2], Z[2];

        bool error_found = false;
        int k=0;
        for(int i = 0; i < recordCount; i++)
        {
            SHPObject *obj = SHPReadObject(shp, i);
            if ( obj != nullptr )
            {
                if ( obj->nVertices < 0 )
                {
                    main_window->Log_Message("[polyline_splitlines] Error[-1017] obj->nVertices < 0");
                    error_found = true;
                }

                if ( obj->nVertices > 500000 ) //500000 is a guess
                {
                    main_window->Log_Message("[polyline_splitlines] Error[-1018] obj->nVertices > 500000");
                    error_found = true;
                }

                if( !error_found )
                {
                    for(int j = 0; j < obj->nVertices-1; j++)
                    {
                        X[0] = obj->padfX[j];
                        X[1] = obj->padfX[j+1];
                        Y[0] = obj->padfY[j];
                        Y[1] = obj->padfY[j+1];
                        Z[0] = 0;
                        Z[1] = 0;

                        SHPObject *newobj = SHPCreateSimpleObject(SHPT_ARC, 2, X, Y, Z);
                        if ( newobj != nullptr )
                        {
                            if ( SHPWriteObject(newshp, -1, newobj) < 0 )
                            {
                                main_window->Log_Message("[polyline_splitlines] Error[-1019] SHPWriteObject failed");
                                error_found = true;
                            }

                            if(!error_found)
                            {
                                if ( ! DBFWriteIntegerAttribute(newdbf, k++, fld, i+1) )
                                {
                                    main_window->Log_Message("[polyline_splitlines] Error[-1020] DBFWriteIntegerAttribute failed");
                                    error_found = true;
                                }
                            }
                        }
                        else
                        {
                            main_window->Log_Message("[polyline_splitlines] Error[-1018] SHPCreateSimpleObject failed");
                            error_found = true;
                        }
                    }
                }
            }
            else
            {
                main_window->Log_Message("[polyline_splitlines] Error[-1100] SHPReadObject failed");
                error_found = true;
            }
        }

        SHPClose(shp);
        DBFClose(dbf);
        SHPClose(newshp);
        DBFClose(newdbf);

        if(error_found)
        {
            main_window->Log_Message("[polyline_splitlines] Error[-2000] Error(s) found");
            return -2000;
        }

    }
    catch (...)
    {
        qDebug() << "Error: polyline_splitlines is returning w/o checking";
        return -5000;
    }

    return 0;
}
