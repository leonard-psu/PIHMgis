#include <QDebug>
#include <iostream>
#include <iomanip>

#include "simplify_polyline.h"
#include "simplify_shape.h"

#include "./../0LibsShape/shapefil.h"
#include "globals.h"

using namespace std;

// User interface to PIHMgis v3.5
extern PIHMgisDialog *main_window;
extern bool simplify_polyline_success; //Not ideal, need to use to keep simple


int simplify_shape(QString qshpFileName, QString qdbfFileName, QString qnewshpFileName, QString qnewdbfFileName, double tolerance)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start simplify_shape";

    try {

        if(qshpFileName == nullptr)
        {
            main_window->Log_Message("[simplify_shape] Error[-1000] Invalid qshpFileName.");
            return -1000;
        }

        if(qdbfFileName == nullptr)
        {
            main_window->Log_Message("[simplify_shape] Error[-1001] Invalid qdbfFileName.");
            return -1001;
        }

        if(qnewshpFileName == nullptr)
        {
            main_window->Log_Message("[simplify_shape] Error[-1003] Invalid qnewshpFileName.");
            return -1003;
        }

        if(qnewdbfFileName == nullptr)
        {
            main_window->Log_Message("[simplify_shape] Error[-1004] Invalid qnewdbfFileName.");
            return -1004;
        }

        if(qshpFileName.length() < 1)
        {
            main_window->Log_Message("[simplify_shape] Error[-1005] Invalid qshpFileName.");
            return -1005;
        }

        if(qdbfFileName.length() < 1)
        {
            main_window->Log_Message("[simplify_shape] Error[-1006] Invalid qdbfFileName.");
            return -1006;
        }

        if(qnewshpFileName.length() < 1)
        {
            main_window->Log_Message("[simplify_shape] Error[-1007] Invalid qnewshpFileName.");
            return -1007;
        }

        if(qnewdbfFileName.length() < 1)
        {
            main_window->Log_Message("[simplify_shape] Error[-1008] Invalid qnewdbfFileName.");
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
            main_window->Log_Message("[simplify_shape] Error[-1009] shpFileName is NULL.");
            return -1009;
        }

        DBFHandle dbf = DBFOpen(dbfFileName, "rb");
        if(dbf == nullptr)
        {
            main_window->Log_Message("[simplify_shape] Error[-1010] dbfFileName is NULL.");
            SHPClose(shp);
            return -1010;
        }

        int InfoShpType = 0;
        SHPGetInfo (shp, nullptr, &InfoShpType, nullptr, nullptr);

        if ( InfoShpType != SHPT_ARC )
        {
            main_window->Log_Message("[simplify_shape] Error[-1011] Not a SHPT_ARC: " + qshpFileName);
            main_window->Log_Message("[simplify_shape] Error[-1011] SHAPE TYPE : " + QString::number(InfoShpType));

            SHPClose(shp);
            DBFClose(dbf);

            return InfoShpType;
        }

        int recordCount = 0;
        int shpType = 0;

        SHPObject *obj1 = SHPReadObject(shp, 0);
        if(obj1 == nullptr)
        {
            main_window->Log_Message("[simplify_shape] Error[-1012] SHPReadObject failed.");
            SHPClose(shp);
            DBFClose(dbf);
            return -1012;
        }

        shpType = obj1->nSHPType;
        recordCount = DBFGetRecordCount(dbf);
        if(recordCount <= 0)
        {
            main_window->Log_Message("[simplify_shape] Error[-1013] recordCount <= 0");
            SHPClose(shp);
            DBFClose(dbf);
            return -1013;
        }

        if(recordCount > 500000) //500000 is a guess
        {
            main_window->Log_Message("[simplify_shape] Error[-1014] recordCount > 500000");
            SHPClose(shp);
            DBFClose(dbf);
            return -1014;
        }

        int fld = DBFGetFieldIndex(dbf, "ARCID");
        if(fld < 0)
        {
            main_window->Log_Message("[simplify_shape] Error[-1015] Invalid DBFGetFieldIndex < 0");
            SHPClose(shp);
            DBFClose(dbf);
            return -1015;
        }

        SHPHandle newshp = SHPCreate(newshpFileName, shpType);
        if(newshp == nullptr)
        {
            main_window->Log_Message("[simplify_shape] Error[-1016] SHPCreate failed");
            SHPClose(shp);
            DBFClose(dbf);
            return -1016;
        }

        DBFHandle newdbf = DBFCreate(newdbfFileName);
        if(newdbf == nullptr)
        {
            main_window->Log_Message("[simplify_shape] Error[-1017] DBFCreate failed");
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            return -1017;
        }

        int arcidField = DBFAddField(newdbf, "ARCID", FTInteger, 5, 0);
        if(arcidField < 0)
        {
            main_window->Log_Message("[simplify_shape] Error[-1018] DBFAddField failed");
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);

            return -1018;
        }

        bool error_found = false;

        for(int i = 0; i < recordCount; i++)
        {
            SHPObject* obj = SHPReadObject(shp, i);
            if(obj == nullptr)
            {
                main_window->Log_Message("[simplify_shape] Error[-2000] SHPReadObject failed");
                error_found = true;
                break;
            }

            if(obj->nVertices <= 0)
            {
                main_window->Log_Message("[simplify_shape] Error[-2001] obj->nVertices <= 0");
                error_found = true;
                break;
            }

            if(obj->nVertices > 500000) //500000 is a guess
            {
                main_window->Log_Message("[simplify_shape] Error[-2002] obj->nVertices > 500000");
                error_found = true;
                break;
            }

            Point* pts = new Point[obj->nVertices];
            if(pts == nullptr)
            {
                main_window->Log_Message("[simplify_shape] Error[-2003] Point failed");
                error_found = true;
                break;
            }

            int *marker= new int[obj->nVertices];
            if(marker == nullptr)
            {
                main_window->Log_Message("[simplify_shape] Error[-2004] Point failed");
                error_found = true;
                delete[] pts;
                break;
            }

            for(int j = 0; j < obj->nVertices; j++)
            {
                marker[j] = 0;
                pts[j].x = obj->padfX[j];
                pts[j].y = obj->padfY[j];
            }

            marker[0] = 1;
            simplify_polyline(pts, 0, obj->nVertices-1, tolerance, marker);

            //Used global variable
            if(!simplify_polyline_success)
            {
                error_found = true;
                main_window->Log_Message("[simplify_shape] Error[-2005] simplify_polyline failed");
                delete[] pts;
                delete[] marker;
                break;
            }

            marker[obj->nVertices - 1] = 1;

            int count = 0;
            for(int j = 0; j < obj->nVertices; j++)
            {
                count = count + marker[j];
            }

            if(count <= 0)
            {
                error_found = true;
                main_window->Log_Message("[simplify_shape] Error[-2006] count <= 0");
                delete[] pts;
                delete[] marker;
                break;
            }

            double *X = new double[count];
            if(X == nullptr)
            {
                main_window->Log_Message("[simplify_shape] Error[-2007] X is null");
                error_found = true;
                delete[] pts;
                delete[] marker;
                break;
            }

            double *Y = new double[count];
            if(Y == nullptr)
            {
                main_window->Log_Message("[simplify_shape] Error[-2008] Y is null");
                error_found = true;
                delete[] pts;
                delete[] marker;
                delete[] X;
                break;
            }

            double *Z = new double[count];
            if(Z == nullptr)
            {
                main_window->Log_Message("[simplify_shape] Error[-2009] Z is null");
                error_found = true;
                delete[] pts;
                delete[] marker;
                delete[] X;
                delete[] Y;
                break;
            }

            int k=0;
            for(int j = 0; j < obj->nVertices; j++)
            {
                if(marker[j] == 1)
                {
                    X[k] = pts[j].x;
                    Y[k] = pts[j].y;
                    Z[k] = 0;
                    k++;
                }
            }

            SHPObject *newobj = SHPCreateSimpleObject(shpType, count, X, Y, Z);
            if(newobj == nullptr)
            {
                main_window->Log_Message("[simplify_shape] Error[-2010] newobj is null");
                error_found = true;
                delete[] pts;
                delete[] marker;
                delete[] X;
                delete[] Y;
                break;
            }

            SHPComputeExtents(newobj);

            if ( SHPWriteObject(newshp, -1, newobj) < 0 )
            {
                main_window->Log_Message("[simplify_shape] Error[-2011] SHPWriteObject failed");
                error_found = true;
                delete[] pts;
                delete[] marker;
                delete[] X;
                delete[] Y;
                break;
            }

            int arcid = DBFReadIntegerAttribute(dbf, i, fld);

            if ( ! DBFWriteIntegerAttribute(newdbf, i, arcidField, arcid) )
            {
                main_window->Log_Message("[simplify_shape] Error[-2012] DBFWriteIntegerAttribute failed");
                error_found = true;
                delete[] pts;
                delete[] marker;
                delete[] X;
                delete[] Y;
                break;
            }

            //Clean up
            delete[] pts;
            delete[] marker;
            delete[] X;
            delete[] Y;
        }


        SHPClose(shp);
        DBFClose(dbf);

        SHPClose(newshp);
        DBFClose(newdbf);

        if(error_found)
        {
            main_window->Log_Message("[simplify_shape] Error[-3000] Error found during process. User needs to check shapefile");
            return -3000;
        }


    }
    catch (...)
    {
        qDebug() << "Error: simplify_shape is returning w/o checking";
        return -5000;
    }

    return 0;
}


