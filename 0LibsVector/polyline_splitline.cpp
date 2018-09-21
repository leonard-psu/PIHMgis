#include <QDebug>
#include <iostream>
#include <iomanip>

#include "./../0LibsShape/shapefil.h"
#include "globals.h"

using namespace std;

int polyline_splitlines(const char* shpFileName, const char* dbfFileName, const char* newshpFileName, const char* newdbfFileName)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start polyline_splitlines";

    try {

        SHPHandle shp = SHPOpen(shpFileName, "rb");
        DBFHandle dbf = DBFOpen(dbfFileName, "rb");

        if ( shp == nullptr || dbf == nullptr )
            return 14;
        //cout<<shpFileName<<"\n";

        int InfoShpType = 0;

        SHPGetInfo (shp, nullptr, &InfoShpType, nullptr, nullptr);
        if ( InfoShpType != SHPT_ARC )
        {
            cout << "Not a SHPT_ARC: ... " << shpFileName << "\n";
            cout << "SHAPE TYPE = " << InfoShpType << "\n";
            return InfoShpType;
        }

        SHPHandle newshp = SHPCreate(newshpFileName, SHPT_ARC);
        DBFHandle newdbf = DBFCreate(newdbfFileName);

        if ( newshp == nullptr || newdbf == nullptr )
            return 30;

        int fld = DBFAddField(newdbf, "ID", FTInteger, 5, 0);

        if ( fld == -1 )
            return 35;

        int recordCount = DBFGetRecordCount(dbf);

        double X[2], Y[2], Z[2];
        int k=0;
        for(int i=0; i<recordCount; i++)
        {
            SHPObject *obj = SHPReadObject(shp, i);

            for(int j=0; j<obj->nVertices-1; j++)
            {
                X[0]=obj->padfX[j];	X[1]=obj->padfX[j+1];
                Y[0]=obj->padfY[j]; Y[1]=obj->padfY[j+1];
                Z[0]=0; Z[1]=0;

                SHPObject *newobj = SHPCreateSimpleObject(SHPT_ARC, 2, X, Y, Z);
                if ( SHPWriteObject(newshp, -1, newobj) < 0 )
                    return 49;

                if ( ! DBFWriteIntegerAttribute(newdbf, k++, fld, i+1) )
                    return 51;
            }
        }

        SHPClose(shp);
        DBFClose(dbf);
        SHPClose(newshp);
        DBFClose(newdbf);

    } catch (...) {
        qDebug() << "Error: polyline_splitlines is returning w/o checking";
    }
    return 0;
}
