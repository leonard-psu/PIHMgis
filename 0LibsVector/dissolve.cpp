#include <QDebug>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>

#include "dissolve.h"
#include "./../0LibsShape/shapefil.h"
#include "globals.h"

using namespace std;

// User interface to PIHMgis v3.5
extern PIHMgisDialog *main_window;

// User can now change this value, which I observed is necessary.
// As demonstrated here: https://doi.org/10.1016/j.envsoft.2014.07.015
double dissolve_epsilon = 0.000001f;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// compare slopes of two lines
// HAS been used in compareLines (commented out).
// TODO Keeping code for now, until testing finished
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int compareSlope(Lines *a, Lines *b)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start compareSlope";

    try {

        //TODO check if lines are null

        if(b->x2 - b->x1 != 0 && a->x2 - a->x1 != 0)
        {
            if(fabs(fabs((b->y2 - b->y1)/(b->x2 - b->x1)) - fabs((a->y2 - a->y1)/(a->x2 - a->x1))) < dissolve_epsilon )
                return 1;
            else
                return 0;
        }
        else
        {
            if(fabs(b->x2 - b->x1) - fabs(a->x2 - a->x1) < dissolve_epsilon)
                return 1;
            else
                return 0;
        }

    } catch (...) {
        qDebug() << "Error: compareSlope is returning w/o checking";
        return -9000;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// compare lines
// Used in dissolve below
// TODO: Decide on Slope option
// TODO: Error checking on null lines
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int compareLines(Lines *a, Lines *b)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start compareLines";

    try {
        if(fabs(a->x1 - b->x1) < dissolve_epsilon && fabs(a->y1 - b->y1) < dissolve_epsilon)
        {
            if(fabs(a->x2 - b->x2) < dissolve_epsilon && fabs(a->y2 - b->y2) < dissolve_epsilon)
                return 1;
            else
                return 0;
        }
        else if(fabs(a->x1 - b->x2) < dissolve_epsilon && fabs(a->y1 - b->y2) < dissolve_epsilon)
        {
            if(fabs(a->x2 - b->x1) < dissolve_epsilon && fabs(a->y2 - b->y1) < dissolve_epsilon)
                return 1;
            else
                return 0;
        }
        /* KEEP CODE FOR NOW
        else if(compareSlope(a,b)==1){
                if(fabs(a->x1-b->x1)<0.0001 && fabs(a->y1-b->y1)<0.0001 && ((a->x1-a->x2)/(b->x1-b->x2)>0 || (a->y1-a->y2)/(b->y1-b->y2)>0))
                        return 1;
                if(fabs(a->x1-b->x2)<0.0001 && fabs(a->y1-b->y2)<0.0001 && ((a->x1-a->x2)/(b->x2-b->x1)>0 || (a->y1-a->y2)/(b->y2-b->y1)>0))
                        return 1;
                if(fabs(a->x2-b->x1)<0.0001 && fabs(a->y2-b->y1)<0.0001 && ((a->x2-a->x1)/(b->x1-b->x2)>0 || (a->y2-a->y1)/(b->y1-b->y2)>0))
                        return 1;
                if(fabs(a->x2-b->x2)<0.0001 && fabs(a->y2-b->y2)<0.0001 && ((a->x2-a->x1)/(b->x2-b->x1)>0 || (a->y2-a->y1)/(b->y2-b->y1)>0))
                        return 1;
                else
                        return 0;
        }*/
        else
            return 0;


    } catch (...) {
        qDebug() << "Error: compareLines is returning w/o checking";
        return -9000;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Does point and line interesect?
// Used in dissolve below
// TODO: Error checking on null lines
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline int doesIntersect(Lines *l, double x1, double y1)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start doesIntersect";

    try
    {
        double a = sqrt(pow(l->x1 - l->x2, 2) + pow(l->y1 - l->y2, 2));
        double b = sqrt(pow(l->x1 - x1, 2) +    pow(l->y1 - y1, 2));
        double c = sqrt(pow(l->x2 - x1, 2) +    pow(l->y2 - y1, 2));
        double s = (a+b+c)/2;

        if(fabs(a-b-c) < dissolve_epsilon && b > dissolve_epsilon && c > dissolve_epsilon)
            return 1;
        else
            return 0;
        /*
        if(s*(s-a)*(s-b)*(s-c)<0.0001)
                return 1;
        else
                return 0;*/
    } catch (...) {
        qDebug() << "Error: doesIntersect is returning w/o checking";
        return 0;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Dissolve
// TODO Where does 20 come from???
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int dissolve(QString qshpFileName, QString qdbfFileName, QString qnewshpFileName, QString qnewdbfFileName)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start dissolve";

    try {


        if(qshpFileName == nullptr)
        {
            main_window->Log_Message("[dissolve] Error[-1000] Invalid qshpFileName.");
            return -1000;
        }
        if(qdbfFileName == nullptr)
        {
            main_window->Log_Message("[dissolve] Error[-1001] Invalid qdbfFileName.");
            return -1001;
        }
        if(qnewshpFileName == nullptr)
        {
            main_window->Log_Message("[dissolve] Error[-1002] Invalid qnewshpFileName.");
            return -1002;
        }
        if(qnewdbfFileName == nullptr)
        {
            main_window->Log_Message("[dissolve] Error[-1003] Invalid qnewdbfFileName.");
            return -1003;
        }

        if(qshpFileName.length() < 1)
        {
            main_window->Log_Message("[dissolve] Error[-1004] Invalid qshpFileName.");
            return -1004;
        }
        if(qdbfFileName.length() < 1)
        {
            main_window->Log_Message("[dissolve] Error[-1005] Invalid qdbfFileName.");
            return -1005;
        }
        if(qnewshpFileName.length() < 1)
        {
            main_window->Log_Message("[dissolve] Error[-1006] Invalid qnewshpFileName.");
            return -1006;
        }
        if(qnewdbfFileName.length() < 1)
        {
            main_window->Log_Message("[dissolve] Error[-1007] Invalid qnewdbfFileName.");
            return -1007;
        }

        QByteArray fname = qshpFileName.toLatin1();
        char *shpFileName = fname.data();
        QByteArray fname1 = qdbfFileName.toLatin1();
        char *dbfFileName = fname1.data();
        QByteArray fname2 = qnewshpFileName.toLatin1();
        char *newshpFileName = fname2.data();
        QByteArray fname3 = qnewdbfFileName.toLatin1();
        char *newdbfFileName = fname3.data();

        int recordCount = 0;

        SHPHandle shp = SHPOpen(shpFileName, "rb");
        if(shp == nullptr)
        {
            main_window->Log_Message("[dissolve] Error[-1008] shpFileName is NULL. ");
            return -1008;
        }

        DBFHandle dbf = DBFOpen(dbfFileName, "rb");
        if(dbf == nullptr)
        {
            main_window->Log_Message("[dissolve] Error[-1009] dbfFileName is NULL. ");
            SHPClose(shp);
            return -1009;
        }

        int InfoShpType;
        SHPGetInfo (shp, nullptr, &InfoShpType, nullptr, nullptr);
        if ( InfoShpType != SHPT_POLYGON )
        {
            main_window->Log_Message("[dissolve] Error[-1010] Not a SHPT_POLYGON. SHAPE TYPE = " + QString::number(InfoShpType));
            SHPClose(shp);
            DBFClose(dbf);
            return -1010;
        }

        SHPHandle newshp = SHPCreate(newshpFileName, SHPT_POLYGON);
        if(newshp == nullptr)
        {
            main_window->Log_Message("[dissolve] Error[-1011] newshpFileName is NULL.");
            SHPClose(shp);
            DBFClose(dbf);
            return -1011;
        }
        DBFHandle newdbf = DBFCreate(newdbfFileName);
        if(newdbf == nullptr)
        {
            main_window->Log_Message("[dissolve] Error[-1012] newdbfFileName is NULL. ");
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            return -1012;
        }

        int PolyID  = DBFAddField(newdbf,  "PolyID", FTInteger, 5, 0);
        if ( PolyID < 0 )
        {
            main_window->Log_Message("[dissolve] Error[-1013] Failed to add PolyID field. ");
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);
            return -1013;
        }
        if ( PolyID > 5000 ) //5000 is a guess
        {
            main_window->Log_Message("[dissolve] Error[-1014] Failed to add PolyID field. ");
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);
            return -1014;
        }

        recordCount = DBFGetRecordCount(dbf);
        if ( recordCount <= 0 )
        {
            main_window->Log_Message("[dissolve] Error[-1015] recordCount <= 0. ");
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);
            return -1015;
        }
        if ( recordCount > 500000 ) //500000 is a guess
        {
            main_window->Log_Message("[dissolve] Error[-1016] recordCount > 500000. ");
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);
            return -1016;
        }

        //if(print_many_messages)
        //{
        main_window->Log_Message("[dissolve] recordCount = " + QString::number(recordCount));
        //}

        SHPObject **obj = new SHPObject*[recordCount];
        if ( obj == nullptr )
        {
            main_window->Log_Message("[dissolve] Error[-2000] SHPObject is null. ");
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);
            return -2000;
        }

        int vertices = -1;
        int totalLines = 0;
        Lines **lines;
        int **lineFlag;
        int *numLines;

        double *dfXMax, *dfXMin, *dfYMax, *dfYMin;

        lines = (Lines **)malloc(recordCount * sizeof(Lines *));
        if ( lines == nullptr)
        {
            main_window->Log_Message("[dissolve] Error[-2001] lines is null" );
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);
            delete[] obj;
            return -2001;
        }
        lineFlag = (int **)malloc(recordCount * sizeof(int *));
        if ( lineFlag == nullptr)
        {
            main_window->Log_Message("[dissolve] Error[-2002] lineFlag is null" );
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);
            delete[] obj;
            free(lines);
            return -2002;
        }
        dfXMax = (double *)malloc(recordCount * sizeof(double));
        if ( dfXMax == nullptr)
        {
            main_window->Log_Message("[dissolve] Error[-2003] dfXMax is null" );
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);
            delete[] obj;
            free(lines);
            free(lineFlag);

            return -2003;
        }
        dfXMin = (double *)malloc(recordCount * sizeof(double));
        if ( dfXMin == nullptr)
        {
            main_window->Log_Message("[dissolve] Error[-2004] dfXMin is null" );
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);
            delete[] obj;
            free(lines);
            free(lineFlag);
            free(dfXMax);

            return -2004;
        }
        dfYMax = (double *)malloc(recordCount * sizeof(double));
        if ( dfYMax == nullptr)
        {
            main_window->Log_Message("[dissolve] Error[-2005] dfYMax is null" );
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);
            delete[] obj;
            free(lines);
            free(lineFlag);
            free(dfXMax);
            free(dfXMin);

            return -2005;
        }
        dfYMin = (double *)malloc(recordCount * sizeof(double));
        if ( dfYMin == nullptr)
        {
            main_window->Log_Message("[dissolve] Error[-2006] dfYMin is null" );
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);
            delete[] obj;
            free(lines);
            free(lineFlag);
            free(dfXMax);
            free(dfXMin);
            free(dfYMin);

            return -2006;
        }
        numLines = (int *)malloc(recordCount * sizeof(int));
        if ( numLines == nullptr)
        {
            main_window->Log_Message("[dissolve] Error[-2007] numLines is null" );
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);
            delete[] obj;
            free(lines);
            free(lineFlag);
            free(dfXMax);
            free(dfXMin);
            free(dfYMin);
            free(numLines);

            return -2007;
        }

        bool error_found = false;
        bool line_error_found = false;
        bool lineFlag_error_found = false;

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////
        //1 Read each polygon and store points in form of lines
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////
        for(int i=0; i < recordCount; i++)
        {
            main_window->Log_Message("[dissolve] Read = " + QString::number(i));

            vertices = 0;
            obj[i] = SHPReadObject(shp, i);
            if( obj[i] == nullptr)
            {
                main_window->Log_Message("[dissolve] read polygon, SHPread failed");
                error_found = true;
            }

            if(error_found == false)
            {
                dfXMax[i] = obj[i]->dfXMax;
                dfXMin[i] = obj[i]->dfXMin;
                dfYMax[i] = obj[i]->dfYMax;
                dfYMin[i] = obj[i]->dfYMin;

                vertices = obj[i]->nVertices;
                numLines[i] = vertices-1;
                totalLines += numLines[i];

                lines[i] = (Lines *)malloc(vertices * 20 * sizeof(Lines)); //Where does 20 come from?
                if ( lines[i] == nullptr)
                {
                    line_error_found = true;
                }

                if(line_error_found == false)
                {
                    lineFlag[i] = (int *)malloc(vertices * 20 * sizeof(int));  //Where does 20 come from?

                    if ( lineFlag[i] == nullptr)
                    {
                        lineFlag_error_found = true;
                    }

                    if(lineFlag_error_found == false)
                    {
                        for(int j=0; j < vertices-1; j++)
                        {
                            lines[i][j].x1 = obj[i]->padfX[j];
                            lines[i][j].y1 = obj[i]->padfY[j];
                            lines[i][j].x2 = obj[i]->padfX[j+1];
                            lines[i][j].y2 = obj[i]->padfY[j+1];
                            lineFlag[i][j] = 1;
                        }
                    }

                }
            }

        } //1 done!

        if ( error_found )
        {
            main_window->Log_Message("[dissolve] Error[-3000] SHPReadObject null. ");
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);
            delete[] obj;
            free(lines);
            free(lineFlag);
            free(dfXMax);
            free(dfXMin);
            free(dfYMin);
            free(numLines);
            return -3000;
        }
        if ( line_error_found)
        {
            main_window->Log_Message("[dissolve] Error[-3001] line malloc null. ");
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);
            delete[] obj;
            free(lines);
            free(lineFlag);
            free(dfXMax);
            free(dfXMin);
            free(dfYMin);
            free(numLines);
            return -3001;
        }
        if ( lineFlag_error_found)
        {
            main_window->Log_Message("[dissolve] Error[-3002] line flag malloc null. ");
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);
            delete[] obj;
            free(lines);
            free(lineFlag);
            free(dfXMax);
            free(dfXMin);
            free(dfYMin);
            free(numLines);
            return -3002;
        }
        if ( vertices <= 0 )
        {
            main_window->Log_Message("[dissolve] Error[-3003] recordCount <= 0. ");
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);
            delete[] obj;
            free(lines);
            free(lineFlag);
            free(dfXMax);
            free(dfXMin);
            free(dfYMin);
            free(numLines);
            return -3003;
        }
        if ( recordCount > 500000 ) //500000 is a guess
        {
            main_window->Log_Message("[dissolve] Error[-3004] recordCount > 500000. ");
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);
            delete[] obj;
            free(lines);
            free(lineFlag);
            free(dfXMax);
            free(dfXMin);
            free(dfYMin);
            free(numLines);
            return -3004;
        }

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////
        //1.1 Find intersections and insert a line
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////
        double minX, maxX, minY, maxY;

        for(int i = 0; i < recordCount; i++)
        {
            for(int k = i+1; k < recordCount; k++)
            {
                if(i==k)
                    continue;

                if((dfXMax[i] < dfXMin[k] || dfXMax[k] < dfXMin[i] || dfYMax[i] < dfYMin[k] || dfYMax[k] < dfYMin[i]))
                    continue;

                for(int j=0; j  <numLines[i]; j++)
                {
                    for(int l=0; l<numLines[k]; l++)
                    {
                        if(lines[i][j].x1 > lines[i][j].x2)
                        {
                            minX = lines[i][j].x2;
                            maxX = lines[i][j].x1;
                        }
                        else
                        {
                            minX = lines[i][j].x1;
                            maxX = lines[i][j].x2;
                        }

                        if(lines[i][j].y1 > lines[i][j].y2)
                        {
                            minY = lines[i][j].y2;
                            maxY = lines[i][j].y1;
                        }
                        else
                        {
                            minY = lines[i][j].y1;
                            maxY = lines[i][j].y2;
                        }

                        if(lines[k][l].x1 >= minX && lines[k][l].x1 <= maxX && lines[k][l].y1 >= minY && lines[k][l].y1 <= maxY)
                        {
                            if(doesIntersect(&(lines[i][j]), lines[k][l].x1, lines[k][l].y1) == 1)
                            {
                                lines[i][numLines[i]].x1 = lines[k][l].x1;
                                lines[i][numLines[i]].y1 = lines[k][l].y1;
                                lines[i][numLines[i]].x2 = lines[i][j].x2;
                                lines[i][numLines[i]].y2 = lines[i][j].y2;
                                lineFlag[i][numLines[i]] = 1;
                                numLines[i]++;
                                totalLines++;
                                lines[i][j].x2 = lines[k][l].x1;
                                lines[i][j].y2 = lines[k][l].y1;
                                continue;
                            }
                        }

                        if(lines[k][l].x2 >= minX && lines[k][l].x2 <= maxX && lines[k][l].y2 >= minY && lines[k][l].y2 <= maxY)
                        {
                            if(doesIntersect(&(lines[i][j]), lines[k][l].x2, lines[k][l].y2) == 1)
                            {
                                lines[i][numLines[i]].x1 = lines[k][l].x2;
                                lines[i][numLines[i]].y1 = lines[k][l].y2;
                                lines[i][numLines[i]].x2 = lines[i][j].x2;
                                lines[i][numLines[i]].y2 = lines[i][j].y2;
                                lineFlag[i][numLines[i]] = 1;
                                numLines[i]++;
                                totalLines++;
                                lines[i][j].x2 = lines[k][l].x2;
                                lines[i][j].y2 = lines[k][l].y2;
                                continue;
                            }
                        }

                        if(lines[k][l].x1 > lines[k][l].x2)
                        {
                            minX = lines[k][l].x2;
                            maxX = lines[k][l].x1;
                        }
                        else
                        {
                            minX = lines[k][l].x1;
                            maxX = lines[k][l].x2;
                        }

                        if(lines[k][l].y1 > lines[k][l].y2)
                        {
                            minY = lines[k][l].y2;
                            maxY = lines[k][l].y1;
                        }
                        else
                        {
                            minY = lines[k][l].y1;
                            maxY = lines[k][l].y2;
                        }

                        if(lines[i][j].x1 >= minX && lines[i][j].x1 <= maxX && lines[i][j].y1 >= minY && lines[i][j].y1 <= maxY)
                        {
                            if(doesIntersect(&(lines[k][l]), lines[i][j].x1, lines[i][j].y1) == 1)
                            {
                                lines[k][numLines[k]].x1 = lines[i][j].x1;
                                lines[k][numLines[k]].y1 = lines[i][j].y1;
                                lines[k][numLines[k]].x2 = lines[k][l].x2;
                                lines[k][numLines[k]].y2 = lines[k][l].y2;
                                lineFlag[k][numLines[k]] = 1;
                                numLines[k]++;
                                totalLines++;
                                lines[k][l].x2 = lines[i][j].x1;
                                lines[k][l].y2 = lines[i][j].y1;
                                continue;
                            }
                        }

                        if(lines[i][j].x2 >= minX && lines[i][j].x2 <= maxX && lines[i][j].y2 >= minY && lines[i][j].y2 <= maxY)
                        {
                            if(doesIntersect(&(lines[k][l]), lines[i][j].x2, lines[i][j].y2)==1)
                            {
                                lines[k][numLines[k]].x1 = lines[i][j].x2;
                                lines[k][numLines[k]].y1 = lines[i][j].y2;
                                lines[k][numLines[k]].x2 = lines[k][l].x2;
                                lines[k][numLines[k]].y2 = lines[k][l].y2;
                                lineFlag[k][numLines[k]] = 1;
                                numLines[k]++;
                                totalLines++;
                                lines[k][l].x2 = lines[i][j].x2;
                                lines[k][l].y2 = lines[i][j].y2;
                                continue;
                            }
                        }
                    }
                }
            }
        }

        if ( totalLines <= 0 )
        {
            main_window->Log_Message("[dissolve] Error[-4000] totalLines <= 0. ");
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);
            delete[] obj;
            free(lines);
            free(lineFlag);
            free(dfXMax);
            free(dfXMin);
            free(dfYMin);
            free(numLines);
            return -4000;
        }
        if ( totalLines > 500000 ) //500000 is a guess
        {
            main_window->Log_Message("[dissolve] Error[-4001] totalLines > 500000. ");
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);
            delete[] obj;
            free(lines);
            free(lineFlag);
            free(dfXMax);
            free(dfXMin);
            free(dfYMin);
            free(numLines);
            return -4001;
        }

        main_window->Log_Message("[dissolve] totalLines = " + QString::number(totalLines));

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////
        //2 Delete common lines
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////
        int totalLines3 = totalLines;
        for(int i = 0; i < recordCount; i++)
        {
            for(int j = 0; j < numLines[i]; j++)
            {
                for(int k=i+1; k < recordCount; k++)
                {
                    for(int l=0; l < numLines[k]; l++)
                    {
                        if(compareLines(&(lines[i][j]), &(lines[k][l]))==1)
                        {
                            lineFlag[i][j] = 0;
                            lineFlag[k][l] = 0;
                            totalLines3 = totalLines3-2;
                        }
                    }
                }
            }
        }

        main_window->Log_Message("[dissolve] totalLines3 = " + QString::number(totalLines3));

        int tempCount;
        for(int i = 0; i < recordCount; i++)
        {
            tempCount=0;
            for(int j = 0; j < numLines[i]; j++)
            {
                if(lineFlag[i][j] != 0)
                    tempCount++;
            }
            //cout<<".poly= "<<i<<" lines= "<<tempCount<<"\n";
        }

        main_window->Log_Message("[dissolve] tempCount = " + QString::number(tempCount));

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////
        //3 Store polygon's lines in one place
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////
        Lines *newlines;
        int count=0;
        newlines = (Lines *)malloc(totalLines * 2 * sizeof(Lines));
        if ( newlines == nullptr )
        {
            main_window->Log_Message("[dissolve] Error[-4002] newlines is null ");
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);
            delete[] obj;
            free(lines);
            free(lineFlag);
            free(dfXMax);
            free(dfXMin);
            free(dfYMin);
            free(numLines);
            return -4002;
        }


        for(int i = 0; i < recordCount; i++)
        {
            for(int j = 0; j < numLines[i]; j++)
            {
                if(lineFlag[i][j] != 0)
                {
                    newlines[count].x1=lines[i][j].x1;
                    newlines[count].y1=lines[i][j].y1;
                    newlines[count].x2=lines[i][j].x2;
                    newlines[count].y2=lines[i][j].y2;
                    count++;
                }
            }
        }

        main_window->Log_Message("[dissolve] count = " + QString::number(count));

        if ( count <= 0 )
        {
            main_window->Log_Message("[dissolve] Error[-4003] count <= 0. ");
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);
            delete[] obj;
            free(lines);
            free(lineFlag);
            free(dfXMax);
            free(dfXMin);
            free(dfYMin);
            free(numLines);
            return -4003;
        }
        if ( count > 500000 ) //500000 is a guess
        {
            main_window->Log_Message("[dissolve] Error[-4004] count > 500000. ");
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);
            delete[] obj;
            free(lines);
            free(lineFlag);
            free(dfXMax);
            free(dfXMin);
            free(dfYMin);
            free(numLines);
            return -4004;
        }

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////
        //4 Collect all the points
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////
        double *X;
        double *Y;
        double *Z;

        int count_factor = 3;
        X = (double *)malloc(count*count_factor*sizeof(double));
        if ( X == nullptr )
        {
            main_window->Log_Message("[dissolve] Error[-4005] X is null ");
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);
            delete[] obj;
            free(lines);
            free(lineFlag);
            free(dfXMax);
            free(dfXMin);
            free(dfYMin);
            free(numLines);
            return -4005;
        }
        Y = (double *)malloc(count*count_factor*sizeof(double));
        if ( Y == nullptr )
        {
            main_window->Log_Message("[dissolve] Error[-4006] Y is null ");
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);
            delete[] obj;
            free(lines);
            free(lineFlag);
            free(dfXMax);
            free(dfXMin);
            free(dfYMin);
            free(numLines);
            return -4006;
        }
        Z = (double *)malloc(count*count_factor*sizeof(double));
        if ( Z == nullptr )
        {
            main_window->Log_Message("[dissolve] Error[-4007] Z is null ");
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);
            delete[] obj;
            free(lines);
            free(lineFlag);
            free(dfXMax);
            free(dfXMin);
            free(dfYMin);
            free(numLines);
            return -4007;
        }

        int numPoints = 0;
        X[0] = newlines[0].x1;
        Y[0] = newlines[0].y1;
        Z[0] = 0.0;
        numPoints++;
        X[1] = newlines[0].x2;
        Y[1] = newlines[0].y2;
        Z[1] = 0.0;
        numPoints++;
        int currentline = 0;
        double ptx = X[1];
        double pty = Y[1];
        int finished=1;

        error_found = false;
        dissolve_epsilon = 0.01;

        while(finished == 1)
        {
            finished=0;

            for(int i=0; i < count; i++)
            {
                if (i != currentline)
                {

                    bool test1 = false;
                    bool test2 = false;
                    if ( fabs(ptx - newlines[i].x1) )
                        test1 = true;

                    if ( fabs(pty - newlines[i].y1) )
                        test2 = true;

                    if( test1 && test2)
                        main_window->Log_Message( QString::number( i ) + " " + QString::number(ptx ) + " " + QString::number(pty ) );

                    if(fabs(ptx - newlines[i].x1) < dissolve_epsilon && fabs(pty - newlines[i].y1) < dissolve_epsilon)
                    {
                        if( numPoints < 0 )
                        {
                            main_window->Log_Message("[dissolve] [ERROR -6001] Invalid numPoints = " + QString::number(numPoints));
                            finished=0;
                            error_found = true;
                            break;
                        }
                        else if( numPoints < count*count_factor)
                        {
                            X[numPoints] = newlines[i].x2;
                            Y[numPoints] = newlines[i].y2;
                            ptx = newlines[i].x2;
                            pty = newlines[i].y2;
                            Z[numPoints] = 0.0;
                            numPoints++;
                            currentline = i;
                            if(i==0)
                            {
                                finished=0;
                                numPoints--;
                            }
                            else
                                finished=1;
                        }
                        else
                        {
                            main_window->Log_Message("[dissolve] [ERROR -6002] Invalid numPoints = " + QString::number(numPoints) + " > " + QString::number(count*count_factor));
                            finished=0;
                            error_found = true;
                            break;
                        }

                        if(i==0)
                        {
                            finished=0;
                            numPoints--;
                        }
                        else
                        {
                            finished=1;
                        }

                        break;
                    }
                    else if(fabs(ptx - newlines[i].x2) < dissolve_epsilon && fabs(pty - newlines[i].y2) < dissolve_epsilon)
                    {
                        if( numPoints < 0 )
                        {
                            main_window->Log_Message("[dissolve] [ERROR -6003] Invalid numPoints = " + QString::number(numPoints));
                            finished=0;
                            error_found = true;
                            break;
                        }
                        else if( numPoints < count*count_factor)
                        {
                            X[numPoints] = newlines[i].x1;
                            Y[numPoints] = newlines[i].y1;
                            ptx = newlines[i].x1;
                            pty = newlines[i].y1;
                            Z[numPoints] = 0.0;
                            numPoints++;
                            currentline = i;
                        }
                        else
                        {
                            main_window->Log_Message("[dissolve] [ERROR -6004] Invalid numPoints = " + QString::number(numPoints) + " > " + QString::number(count*count_factor));
                            finished=0;
                            error_found = true;
                            break;
                        }

                        if(i==0)
                        {
                            finished=0;
                            numPoints--;
                        }
                        else
                        {
                            finished=1;
                        }

                        break;
                    }
                }
            }
        }

        main_window->Log_Message("[dissolve] numPoints = " + QString::number(numPoints));

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////
        SHPObject *newobj = SHPCreateSimpleObject(SHPT_POLYGON, numPoints, X, Y, Z);
        if ( newobj == nullptr )
        {
            main_window->Log_Message("[dissolve] Error[-5000] newobj is null ");
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);
            delete[] obj;
            free(lines);
            free(lineFlag);
            free(dfXMax);
            free(dfXMin);
            free(dfYMin);
            free(numLines);
            return -5000;
        }

        if ( SHPWriteObject(newshp, -1, newobj) < 0 )
        {
            main_window->Log_Message("[dissolve] Error[-5001] SHPWriteObject failed ");
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);
            delete[] obj;
            free(lines);
            free(lineFlag);
            free(dfXMax);
            free(dfXMin);
            free(dfYMin);
            free(numLines);
            return -5001;
        }

        if ( DBFWriteIntegerAttribute(newdbf, 0,   PolyID,  1) == false)
        {
            main_window->Log_Message("[dissolve] Error[-5002] DBFWriteIntegerAttribute failed ");
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);
            delete[] obj;
            free(lines);
            free(lineFlag);
            free(dfXMax);
            free(dfXMin);
            free(dfYMin);
            free(numLines);
            return -5002;
        }

        //Clean up

        SHPClose(shp);
        DBFClose(dbf);
        SHPClose(newshp);
        DBFClose(newdbf);

        SHPDestroyObject(newobj);

        if(Z != nullptr)
        {
            free(Z);
            Z = nullptr;
        }
        if(Y != nullptr)
        {
            free(Y);
            Y = nullptr;
        }
        if(X != nullptr)
        {
            free(X);
            X = nullptr;
        }
        if(newlines != nullptr)
        {
            free(newlines);
            newlines = nullptr;
        }
        for(int i=0; i < recordCount; i++)
        {
            free(lines[i]);
            free(lineFlag[i]);
        }
        if(lines != nullptr)
        {
            free(lines);
            lines = nullptr;
        }
        if(lineFlag != nullptr)
        {
            free(lineFlag);
            lineFlag = nullptr;
        }
        if(numLines != nullptr)
        {
            free(numLines);
            numLines = nullptr;
        }
        if(dfYMin != nullptr)
        {
            free(dfYMin);
            dfYMin = nullptr;
        }
        if(dfXMax != nullptr)
        {
            free(dfXMax);
            dfXMax = nullptr;
        }
        if(dfYMax != nullptr)
        {
            free(dfYMax);
            dfYMax = nullptr;
        }
        if(dfXMin != nullptr)
        {
            free(dfXMin);
            dfXMin = nullptr;
        }
        if(obj != nullptr)
        {
            delete[] obj;
            obj = nullptr;
        }

        if(error_found)
        {
            return -6000;
        }

    }
    catch (...)
    {
        qDebug() << "Error: dissolve is returning w/o checking";
        return -9000;
    }

    return 0;
}

