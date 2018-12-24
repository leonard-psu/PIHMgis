#ifndef POLYGON_POLYLINE
#define POLYGON_POLYLINE

#include "./../0LibsShape/shapefil.h"
#include <QString>

// Current version of code assumes a polygon intersects just once with the other polygon for EFFICIENCY purpose

int sortArray(int ***junction, int* jctCount, int recordCount);

int polygon_polylines(QString shpFileName, QString dbfFileName, QString newshpFileName, QString newdbfFileName);


#endif
