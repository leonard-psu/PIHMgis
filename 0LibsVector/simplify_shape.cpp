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

int simplify_shape(const char *shpFileName, const char *dbfFileName, const char *newshpFileName, const char *newdbfFileName, double tolerance)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start simplify_shape";

    try {

        cout<<"Simplifying "<<shpFileName<<"...";

        SHPHandle shp = SHPOpen(shpFileName, "rb");
        if(shp == nullptr)
        {
            main_window->Log_Message("[simplify_shape] Error shpFileName is NULL. Returning 20.");
            return 20;
        }

        DBFHandle dbf = DBFOpen(dbfFileName, "rb");
        if(dbf == nullptr)
        {
            main_window->Log_Message("[simplify_shape] Error dbfFileName is NULL. Returning 20.");
            return 20;
        }

        if ( shp == nullptr || dbf == nullptr )
            return 20;

        int InfoShpType = 0;
        SHPGetInfo (shp, nullptr, &InfoShpType, nullptr, nullptr);

        if ( InfoShpType != SHPT_ARC )
        {
            cout << "Not a SHPT_ARC: ... " << shpFileName << "\n";
            cout << "SHAPE TYPE = " << InfoShpType << "\n";
            return InfoShpType;
        }

        int recordCount, shpType = 0;

        SHPObject *obj1 = SHPReadObject(shp, 0);
        shpType=obj1->nSHPType;
        recordCount=DBFGetRecordCount(dbf);

        int fld = DBFGetFieldIndex(dbf, "ARCID");

        //cout<<"recordCount= "<<recordCount<<"\n";
        //cout<<"shpType= "<<shpType<<"\n";

        SHPHandle newshp = SHPCreate(newshpFileName, shpType);
        if(newshp == nullptr)
        {
            main_window->Log_Message("[simplify_shape] Error newshpFileName is NULL. Returning 46.");
            return 46;
        }
        DBFHandle newdbf = DBFCreate(newdbfFileName);
        if(newdbf == nullptr)
        {
            main_window->Log_Message("[simplify_shape] Error newdbfFileName is NULL. Returning 46.");
            return 46;
        }

        if ( newshp == nullptr || newdbf == nullptr )
            return 46;

        int arcidField = DBFAddField(newdbf, "ARCID", FTInteger, 5, 0);

        if ( arcidField == -1 )
            return 51;

        for(int i=0; i<recordCount; i++)
        {
            SHPObject* obj = SHPReadObject(shp, i);

            Point* pts = new Point[obj->nVertices];
            int *marker= new int[obj->nVertices];

            for(int j=0; j<obj->nVertices; j++)
            {
                marker[j]=0;
                pts[j].x=obj->padfX[j];
                pts[j].y=obj->padfY[j];
            }

            marker[0]=1;
            simplify_polyline(pts, 0, obj->nVertices-1, tolerance, marker);//, 0);
            marker[obj->nVertices-1]=1;

            int count=0;
            for(int j=0; j<obj->nVertices; j++)
            {
                count=count+marker[j];
            }

            double *X = new double[count];
            double *Y = new double[count];
            double *Z = new double[count];

            int k=0;
            for(int j=0; j<obj->nVertices; j++)
            {
                if(marker[j]==1)
                {
                    X[k]=pts[j].x;
                    Y[k]=pts[j].y;
                    Z[k]=0;
                    k++;
                }
            }
            SHPObject *newobj = SHPCreateSimpleObject(shpType, count, X, Y, Z);
            SHPComputeExtents(newobj);
            if ( SHPWriteObject(newshp, -1, newobj) < 0 )
                return 85;

            int arcid = DBFReadIntegerAttribute(dbf, i, fld);
            if ( ! DBFWriteIntegerAttribute(newdbf, i, arcidField, arcid) )
                return 89;
        }
        cout<<"Done!\n\n";

        SHPClose(shp);
        DBFClose(dbf);

        SHPClose(newshp);
        DBFClose(newdbf);

    } catch (...) {
        qDebug() << "Error: simplify_shape is returning w/o checking";
    }

    return 0;
}


