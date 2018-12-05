#include <QDebug>
#include <iostream>
#include <iomanip>

#include "./../0LibsShape/shapefil.h"
#include "globals.h"

using namespace std;

// User interface to PIHMgis v3.5
extern PIHMgisDialog *main_window;

int merge_lines(const char** shpFileNames, const char** dbfFileNames, int fileCount, const char *newshpFileName, const char *newdbfFileName)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start merge_lines";

    try {

        int recordCount = 0;
        SHPObject *obj;

        SHPHandle newshp = SHPCreate(newshpFileName, SHPT_ARC);
        if(newshp == nullptr)
        {
            main_window->Log_Message("[merge_lines] Error newshpFileName is NULL. Returning 20.");
            return 20;
        }
        DBFHandle newdbf = DBFCreate(newdbfFileName);
        if(newdbf == nullptr)
        {
            main_window->Log_Message("[merge_lines] Error newdbfFileName is NULL. Returning 20.");
            return 20;
        }

        if ( newshp == nullptr || newdbf == nullptr )
            return 20;

        int fld = DBFAddField(newdbf, "ID", FTInteger, 5, 0);

        if ( fld == -1 )
            return 25;

        int k=0;

        for(int i=0; i<fileCount; i++)
        {
            std::cout<<"\n-->"<<shpFileNames[i];
            SHPHandle shp = SHPOpen(shpFileNames[i], "rb");
            if(shp == nullptr)
            {
                main_window->Log_Message("[merge_lines] Error shpFileName is NULL. Returning 36.");
                return 36;
            }

            DBFHandle dbf = DBFOpen(dbfFileNames[i], "rb");
            if(dbf == nullptr)
            {
                main_window->Log_Message("[merge_lines] Error dbfFileNames is NULL. Returning 36.");
                return 36;
            }

            if ( shp == nullptr || dbf == nullptr )
                return 36;

            int InfoShpType;
            SHPGetInfo (shp, nullptr, &InfoShpType, nullptr, nullptr);
            if ( InfoShpType != SHPT_ARC )
            {
                cout << "Not a SHPT_ARC: ... " << shpFileNames[i] << "\n";
                cout << "SHAPE TYPE = " << InfoShpType << "\n";
                return InfoShpType;
            }

            recordCount = DBFGetRecordCount(dbf);

            for(int j=0; j<recordCount; j++)
            {
                obj = SHPReadObject(shp, j);
                if ( obj->nVertices > 2 )
                    return 53;
                if ( SHPWriteObject(newshp, -1, obj) < 0 )
                    return 55;
                if ( ! DBFWriteIntegerAttribute(newdbf, k++, fld, j+1) )
                    return 57;
            }

            SHPClose(shp);
            DBFClose(dbf);
        }

        SHPClose(newshp);
        DBFClose(newdbf);

        return 0;

    } catch (...) {
        qDebug() << "Error: merge_lines is returning w/o checking";
         return 580;
    }

}
