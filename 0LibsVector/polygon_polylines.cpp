/* Current version of code assumes a polygon intersects just once with the other polygon for EFFICIENCY purpose */

#include <QDebug>

#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>

#include "polygon_polylines.h"
#include "./../0LibsShape/shapefil.h"
#include "globals.h"

using namespace std;

// User interface to PIHMgis v3.5
extern PIHMgisDialog *main_window;

//#define dist(x1,y1,x2,y2) sqrt(pow((x1-x2),2) + pow((y1-y2),2))  
#define dist(x1,y1,x2,y2) fabs(x1-x2)+fabs(y1-y2)  

double polygon_epilson = 0.001;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// sortArray
// Used in polygon_polylines
// Not recursive, returning error codes
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int sortArray(int ***junction, int* jctCount, int recordCount)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ReadModuleLine";

    try {

        bool error_jctCount_found = false;

        if(junction == nullptr)
        {
            main_window->Log_Message("[sortArray] Error[-1000] junction is null.");
            return -1000;
        }

        if(jctCount == nullptr)
        {
            main_window->Log_Message("[sortArray] Error[-1001] jctCount is null.");
            return -1001;
        }

        if(recordCount < 0 )
        {
            main_window->Log_Message("[sortArray] Error[-1002] recordCount < 0.");
            return -1002;
        }

        if(recordCount > 500000 ) //500000 is a guess
        {
            main_window->Log_Message("[sortArray] Error[-1003] recordCount> 500000.");
            return -1003;
        }


        int temp = 0;
        int a, b, c, d = 0;

        for(int i = 0; i < recordCount; i++)
        {
            if(jctCount[i] < 0)
            {
                main_window->Log_Message("[sortArray] Error[-1004] jctCount[i] < 0");
                error_jctCount_found = true;
            }
            if(jctCount[i] > 500000 ) //500000 is a guess
            {
                main_window->Log_Message("[sortArray] Error[-1005] jctCount[i] > 500000 ) ");
                error_jctCount_found = true;
            }

            if(!error_jctCount_found)
            {
                for(int j = 0; j < jctCount[i]; j++)
                {
                    for(int k = 0; k < j; k++)
                    {
                        //TODO Error checking maybe required here.

                        if(junction[i][j][1] < junction[i][k][1])
                        {
                            temp = junction[i][j][2];
                            junction[i][j][2] = junction[i][k][2];
                            junction[i][k][2] = temp;

                            temp = junction[i][j][1];
                            junction[i][j][1] = junction[i][k][1];
                            junction[i][k][1] = temp;

                            temp = junction[i][j][0];
                            junction[i][j][0] = junction[i][k][0];
                            junction[i][k][0] = temp;
                        }
                    }
                }
            }

            if(jctCount[i]-1 < 0)
            {
                main_window->Log_Message("[sortArray] Error[-2000] jctCount[i] - 1 < 0");
                error_jctCount_found = true;
            }
            if(jctCount[i]-1 > 500000 ) //500000 is a guess
            {
                main_window->Log_Message("[sortArray] Error[-2001] jctCount[i]- 1  > 500000 ) ");
                error_jctCount_found = true;
            }

            if(!error_jctCount_found)
            {
                for(int j=0; j < jctCount[i]-1; j++)
                {
                    if(junction[i][j][1]==junction[i][j+1][1])
                    {
                        if(junction[i][j][0]<junction[i][j+1][0])
                        {
                            int k=j+1;
                            temp = junction[i][j][2];
                            junction[i][j][2] = junction[i][k][2];
                            junction[i][k][2] = temp;

                            temp = junction[i][j][1];
                            junction[i][j][1] = junction[i][k][1];
                            junction[i][k][1] = temp;

                            temp = junction[i][j][0];
                            junction[i][j][0] = junction[i][k][0];
                            junction[i][k][0] = temp;
                        }
                    }
                }
            }

            if(jctCount[i] >= 2)
            {
                a = junction[i][jctCount[i]-2][0];
                b = junction[i][jctCount[i]-2][1];
                c = junction[i][jctCount[i]-1][0];
                d = junction[i][jctCount[i]-1][1];

                if(c<=a && b<=d)
                {
                    junction[i][jctCount[i]-1][0] = d;
                    junction[i][jctCount[i]-1][1] = c;
                }
            }
        }

        if(error_jctCount_found)
            return -2000;


    } catch (...) {
        qDebug() << "Error: sortArray is returning w/o checking";
        return -5000;
    }

    return 0;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// polygon_polylines
// Used in 3Vector Processing
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int polygon_polylines(QString qshpFileName, QString qdbfFileName, QString qnewshpFileName, QString qnewdbfFileName)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ReadModuleLine";

    try {

        if(qshpFileName == nullptr)
        {
            main_window->Log_Message("[polygon_polylines] Error[-1000] Invalid qshpFileName.");
            return -1000;
        }

        if(qdbfFileName == nullptr)
        {
            main_window->Log_Message("[polygon_polylines] Error[-1001] Invalid qdbfFileName.");
            return -1001;
        }

        if(qnewshpFileName == nullptr)
        {
            main_window->Log_Message("[polygon_polylines] Error[-1003] Invalid qnewshpFileName.");
            return -1003;
        }

        if(qnewdbfFileName == nullptr)
        {
            main_window->Log_Message("[polygon_polylines] Error[-1004] Invalid qnewdbfFileName.");
            return -1004;
        }

        if(qshpFileName.length() < 1)
        {
            main_window->Log_Message("[polygon_polylines] Error[-1005] Invalid qshpFileName.");
            return -1005;
        }

        if(qdbfFileName.length() < 1)
        {
            main_window->Log_Message("[polygon_polylines] Error[-1006] Invalid qdbfFileName.");
            return -1006;
        }

        if(qnewshpFileName.length() < 1)
        {
            main_window->Log_Message("[polygon_polylines] Error[-1007] Invalid qnewshpFileName.");
            return -1007;
        }

        if(qnewdbfFileName.length() < 1)
        {
            main_window->Log_Message("[polygon_polylines] Error[-1008] Invalid qnewdbfFileName.");
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


        int recordCount = 0;
        SHPHandle shp = SHPOpen(shpFileName, "rb");
        if(shp == nullptr)
        {
            main_window->Log_Message("[polygon_polylines] Error[-1009] SHPOpen failed to open " + qshpFileName);
            return -1009;
        }

        DBFHandle dbf = DBFOpen(dbfFileName, "rb");
        if(dbf == nullptr)
        {
            main_window->Log_Message("[polygon_polylines] Error[-1010] DBFOpen failed to open " + qdbfFileName);
            SHPClose(shp);
            return -1010;
        }

        SHPHandle newshp = SHPCreate(newshpFileName, SHPT_ARC);
        if(newshp == nullptr)
        {
            main_window->Log_Message("[polygon_polylines] Error[-1011] SHPOpen failed to open " + qnewshpFileName);

            SHPClose(shp);
            DBFClose(dbf);
            return -1011;
        }

        DBFHandle newdbf = DBFCreate(newdbfFileName);
        if(newdbf == nullptr)
        {
            main_window->Log_Message("[polygon_polylines] Error[-1012] DBFOpen failed to open " + qnewdbfFileName);

            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);

            return -1012;
        }

        int InfoShpType = 0;
        SHPGetInfo (shp, nullptr, &InfoShpType, nullptr, nullptr);
        if ( InfoShpType != SHPT_POLYGON )
        {
            main_window->Log_Message("[polygon_polylines] Error[-1013] Not a SHPT_POLYGON: " + qshpFileName);
            main_window->Log_Message("[polygon_polylines] Error[-1013] SHAPE TYPE =: " + QString::number(InfoShpType));

            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);

            return -1013;
        }

        int field  = DBFAddField(newdbf, "Field", FTInteger, 5, 0);
        if ( field < 0 )
        {
            main_window->Log_Message("[polygon_polylines] Error[-1014] DBFAddField failed to add field: " + qdbfFileName);

            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);

            return -1014;
        }

        SHPObject *obj1, *obj2;

        recordCount = DBFGetRecordCount(dbf);
        if ( recordCount < 0 )
        {
            main_window->Log_Message("[polygon_polylines] Error[-1014] DBFGetRecordCount Invalid recordCount: " + QString::number(recordCount));

            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);

            return -1015;
        }

        if ( recordCount > 500000 ) //500000 is a guess
        {
            main_window->Log_Message("[polygon_polylines] Error[-1016] DBFGetRecordCount Invalid recordCount > 500000: " + QString::number(recordCount));

            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);

            return -1016;
        }

        int ***junction = new int**[recordCount];
        if ( junction  == nullptr)
        {
            main_window->Log_Message("[polygon_polylines] Error[-1017] junction is null " );

            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);

            return -1017;
        }

        bool error_found = false;

        for(int i=0; i < recordCount; i++)
        {
            junction[i] = new int*[30];   //Where does 30 come from?

            if ( junction  == nullptr)
            {
                error_found = true;
            }

            if( !error_found )
            {
                for(int j=0; j < 30; j++)  //Where does 30 come from?
                {
                    junction[i][j] = new int[3]; //Where does 3 come from?
                    if ( junction[i][j]  == nullptr)
                    {
                        error_found = true;
                    }
                }
            }
        }

        if ( error_found )
        {
            main_window->Log_Message("[polygon_polylines] Error[-1018] junction is null " );

            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);

            //Clean up
            for(int i=0; i < recordCount; i++)
            {
                for(int j=0; j < 30; j++) //Where does 30 come from?
                {
                    delete junction[i][j];
                }
            }

            delete[] junction;

            return -1018;
        }

        /////////////////////////////////////////////////////////////////////////////////

        int *vertex    = new int[recordCount];
        if ( vertex == nullptr )
        {
            main_window->Log_Message("[polygon_polylines] Error[-1019] vertex is null " );
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);

            //Clean up
            for(int i=0; i < recordCount; i++)
            {
                for(int j=0; j < 30; j++) //Where does 30 come from?
                {
                    delete junction[i][j];
                }
            }

            delete[] junction;

            return -1019;
        }

        /////////////////////////////////////////////////////////////////////////////////
        int *jctCount  = new int[recordCount];
        if ( jctCount == nullptr )
        {
            main_window->Log_Message("[polygon_polylines] Error[-1020] jctCount is null " );

            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);

            //Clean up
            for(int i=0; i < recordCount; i++)
            {
                for(int j=0; j < 30; j++) //Where does 30 come from?
                {
                    delete junction[i][j];
                }
            }

            delete[] junction;

            return -1020;
        }


        int jct1[2];
        int jct2[2];
        double x1, x2, x3, x4, y1, y2, y3, y4 = 0;
        int *pts1, *pts2, pts1count, pts2count;

        error_found = false;
        for( int i = 0; i < recordCount; i++)
        {
            obj1 = SHPReadObject(shp, i);
            if ( obj1 == nullptr )
            {
                error_found = true;
            }

            if(!error_found)
            {
                vertex[i] = obj1->nVertices;
                jctCount[i] = 0;

                for( int j = 0; j < i; j++)
                {
                    obj2 = SHPReadObject(shp, j);
                    if ( obj2 == nullptr )
                    {
                        error_found = true;
                    }

                    if(!error_found)
                    {
                        int ii, jj, iii, jjj = 0;
                        int ptcount = 0;
                        int breakFlag = 0;

                        if(!((obj1->dfXMax<obj2->dfXMin)||(obj2->dfXMax<obj1->dfXMin)||(obj1->dfYMax<obj2->dfYMin)||(obj2->dfYMax<obj1->dfYMin)))
                        {
                            if ( obj1->nVertices < 1 )
                            {
                                error_found = true;
                            }
                            if ( obj1->nVertices > 500000 ) //500000 is a guess
                            {
                                error_found = true;
                            }
                            if ( obj2->nVertices < 1 )
                            {
                                error_found = true;
                            }
                            if ( obj2->nVertices > 500000 ) //500000 is a guess
                            {
                                error_found = true;
                            }

                            if(!error_found)
                            {
                                //Decide potential intersecting polygon
                                pts1 = new int[obj1->nVertices];
                                if ( pts1 == nullptr )
                                {
                                    error_found = true;
                                }

                                pts2 = new int[obj2->nVertices];
                                if ( pts2 == nullptr )
                                {
                                    error_found = true;
                                }

                                pts1count = 0;
                                pts2count = 0;

                                if(!error_found)
                                {
                                    //Find points of poly 1 falling in the bounding rectangle of the polygon 2
                                    for(int p1=0; p1 < obj1->nVertices-1; p1++)
                                    {
                                        if( (obj2->dfXMin-1<=obj1->padfX[p1]&&obj1->padfX[p1]<=obj2->dfXMax+1) && (obj2->dfYMin-1<=obj1->padfY[p1]&&obj1->padfY[p1]<=obj2->dfYMax+1))
                                        {
                                            pts1[pts1count++] = p1;
                                        }
                                    }

                                    //Find points of poly 2 falling in the bounding rectangle of the polygon 1
                                    for(int p2=0; p2 < obj2->nVertices-1; p2++)
                                    {
                                        if( (obj1->dfXMin-1<=obj2->padfX[p2]&&obj2->padfX[p2]<=obj1->dfXMax+1) && (obj1->dfYMin-1<=obj2->padfY[p2]&&obj2->padfY[p2]<=obj1->dfYMax+1))
                                        {
                                            pts2[pts2count++] = p2;
                                        }
                                    }

                                    for(iii = 0; iii < pts1count; iii++)
                                    {
                                        for(jjj = 0; jjj < pts2count; jjj++)
                                        {
                                            ii = pts1[iii];
                                            jj = pts2[jjj];
                                            x1 = obj1->padfX[ii];
                                            x2 = obj2->padfX[jj];
                                            y1 = obj1->padfY[ii];
                                            y2 = obj2->padfY[jj];

                                            if(dist(x1,y1,x2,y2) < polygon_epilson)
                                            {
                                                x1 = ii==obj1->nVertices-1?obj1->padfX[1]:obj1->padfX[ii+1];
                                                x2 = ii==0?obj1->padfX[obj1->nVertices-2]:obj1->padfX[ii-1];
                                                x3 = jj==obj2->nVertices-1?obj2->padfX[1]:obj2->padfX[jj+1];
                                                x4 = jj==0?obj2->padfX[obj2->nVertices-2]:obj2->padfX[jj-1];

                                                y1 = ii==obj1->nVertices-1?obj1->padfY[1]:obj1->padfY[ii+1];
                                                y2 = ii==0?obj1->padfY[obj1->nVertices-2]:obj1->padfY[ii-1];
                                                y3 = jj==obj2->nVertices-1?obj2->padfY[1]:obj2->padfY[jj+1];
                                                y4 = jj==0?obj2->padfY[obj2->nVertices-2]:obj2->padfY[jj-1];

                                                if((dist(x1, y1, x3, y3) < polygon_epilson))
                                                {
                                                    if(dist(x2, y2, x4, y4) >= polygon_epilson)
                                                    {
                                                        //jct found
                                                        jct1[ptcount] = ii;
                                                        jct2[ptcount] = jj;
                                                        ptcount++;
                                                        //printf("\n%d %d -- %d %d",i,ii,j,jj);
                                                    }
                                                }
                                                if((dist(x1, y1, x4, y4) < polygon_epilson))
                                                {
                                                    if(dist(x2, y2, x3, y3) >= polygon_epilson)
                                                    {
                                                        //jct found
                                                        jct1[ptcount] = ii;
                                                        jct2[ptcount] = jj;
                                                        ptcount++;
                                                        //printf("\n%d %d -- %d %d",i,ii,j,jj);
                                                    }
                                                }
                                                if((dist(x2, y2, x4, y4) < polygon_epilson))
                                                {
                                                    if( dist(x1, y1, x3, y3)>= polygon_epilson)
                                                    {
                                                        //jct found
                                                        jct1[ptcount] = ii;
                                                        jct2[ptcount] = jj;
                                                        ptcount++;
                                                        //printf("\n%d %d -- %d %d",i,ii,j,jj);
                                                    }
                                                }
                                                if((dist(x2, y2, x3, y3) < polygon_epilson))
                                                {
                                                    if( dist(x1, y1, x4, y4) >= polygon_epilson)
                                                    {
                                                        //jct found
                                                        jct1[ptcount] = ii;
                                                        jct2[ptcount] = jj;
                                                        ptcount++;
                                                        //printf("\n%d %d -- %d %d",i,ii,j,jj);
                                                    }
                                                }
                                                //cout<<"\nptcount= "<<ptcount<<"\n";

                                            }

                                            //This assumes a polygon interects just once with the other polygon
                                            if(ptcount==2)
                                            {
                                                breakFlag=1;
                                                break;
                                            }
                                        }

                                        //This assumes a polygon interects just once with the other polygon
                                        if(breakFlag==1)
                                            break;
                                    }
                                }

                                if(ptcount==2)
                                {
                                    junction[i][jctCount[i]][0] = jct1[0]<jct1[1]?jct1[0]:jct1[1];
                                    junction[i][jctCount[i]][1] = jct1[0]<jct1[1]?jct1[1]:jct1[0];
                                    junction[i][jctCount[i]][2] = 1;
                                    jctCount[i]++;

                                    junction[j][jctCount[j]][0] = jct2[0]<jct2[1]?jct2[0]:jct2[1];
                                    junction[j][jctCount[j]][1] = jct2[0]<jct2[1]?jct2[1]:jct2[0];
                                    junction[j][jctCount[j]][2] = 0;
                                    jctCount[j]++;

                                }
                            }
                        }
                    }
                }
            }
        }

        ///////////////////////////////////////////////////////////////////////////////////////////////
        if ( error_found )
        {
            main_window->Log_Message("[polygon_polylines] Error[-1021] Error found at one or more multiple locations " );

            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);

            //Clean up
            for(int i=0; i < recordCount; i++)
            {
                for(int j=0; j < 30; j++) //Where does 30 come from?
                {
                    delete junction[i][j];
                }
            }

            delete[] junction;

            return -1021;
        }
        ///////////////////////////////////////////////////////////////////////////////////////////////

        error_found = false;
        for(int i=0; i < recordCount; i++)
        {
            obj1 = SHPReadObject(shp, i);
            if(obj1 == nullptr)
            {
                error_found = true;
            }
            else
            {
                if(jctCount[i]==0)
                {
                    jctCount[i] = 1;
                    junction[i][0][0] = 0;
                    junction[i][0][1] = obj1->nVertices-1;
                    junction[i][0][2] = 1;
                }
            }
        }

        if ( error_found )
        {
            main_window->Log_Message("[polygon_polylines] Error[-1022] Error found SHPReadObject " );

            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);

            //Clean up
            for(int i=0; i < recordCount; i++)
            {
                for(int j=0; j < 30; j++) //Where does 30 come from?
                {
                    delete junction[i][j];
                }
            }

            delete[] junction;

            return -1022;
        }
        ///////////////////////////////////////////////////////////////////////////////////////////////

        int err = sortArray(junction, jctCount, recordCount);

        if ( err != 0 )
        {
            main_window->Log_Message("[polygon_polylines] Error[-1023] sortArray failed " );

            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);

            //Clean up
            for(int i=0; i < recordCount; i++)
            {
                for(int j=0; j < 30; j++) //Where does 30 come from?
                {
                    delete junction[i][j];
                }
            }

            delete[] junction;

            return -1023;
        }

        ///////////////////////////////////////////////////////////////////////////////////////////////

        int record=0, start = 0, end = 0;
        error_found = false;

        SHPObject *newobj;

        for(int i=0; i < recordCount; i++)
        {
            obj1 = SHPReadObject(shp, i);

            if( obj1 == nullptr)
            {
                main_window->Log_Message("[polygon_polylines] Error[-1024] SHPReadObject failed" );
                error_found = true;
            }

            if( !error_found)
            {
                int nodes = obj1->nVertices;

                if( nodes <= 0)
                {
                    main_window->Log_Message("[polygon_polylines] Error[-2000] nodes <= 0" );
                    error_found = true;
                }
                if( nodes > 500000) //500000 is a guess
                {
                    main_window->Log_Message("[polygon_polylines] Error[-2001] nodes > 500000" );
                    error_found = true;
                }

                double *X= new double[nodes];
                if( X == nullptr)
                {
                    main_window->Log_Message("[polygon_polylines] Error[-2002] X is null" );
                    error_found = true;
                }

                if(!error_found)
                {
                    double *Y= new double[nodes];
                    if( Y == nullptr)
                    {
                        main_window->Log_Message("[polygon_polylines] Error[-2003] Y is null" );
                        delete [] X;
                        error_found = true;
                    }

                    if(!error_found)
                    {
                        double *Z= new double[nodes];
                        if( Z == nullptr)
                        {
                            main_window->Log_Message("[polygon_polylines] Error[-2004] Z is null" );

                            delete [] X;
                            delete [] Y;
                            error_found = true;
                        }

                        if(!error_found)
                        {
                            int vertices = 0;

                            if(junction[i][jctCount[i]-1][1] < junction[i][jctCount[i]-1][0])
                            {
                                if(junction[i][jctCount[i]-1][2] == 1)
                                {
                                    if(junction[i][jctCount[i]-1][1] != 0)
                                    {
                                        //cout<<"0"<<" "<<junction[i][jctCount[i]-1][1]<<" | ";
                                        /**********************************************************/
                                        start = 0;
                                        end = junction[i][jctCount[i]-1][1];
                                        vertices = 0;

                                        if(end < 0)
                                        {
                                            main_window->Log_Message("[polygon_polylines] Error[-2005] end < 0" );
                                            error_found = true;
                                        }
                                        if(end > 500000) //500000 is a guess
                                        {
                                            main_window->Log_Message("[polygon_polylines] Error[-2006] end > 500000" );
                                            error_found = true;
                                        }
                                        if(start > end)
                                        {
                                            main_window->Log_Message("[polygon_polylines] Error[-2007] start > end" );
                                            error_found = true;
                                        }

                                        if(!error_found)
                                        {
                                            for(int i = start; i <= end; i++)
                                            {
                                                X[vertices] = obj1->padfX[i];
                                                Y[vertices] = obj1->padfY[i];
                                                Z[vertices] = 0;
                                                vertices++;
                                            }

                                            newobj = SHPCreateSimpleObject(SHPT_ARC, vertices, X, Y, Z);
                                            if( newobj == nullptr)
                                            {
                                                main_window->Log_Message("[polygon_polylines] Error[-2008] SHPCreateSimpleObject failed" );
                                                error_found = true;
                                            }

                                            if(!error_found)
                                            {
                                                if ( SHPWriteObject(newshp, -1, newobj) < 0 )
                                                {
                                                    main_window->Log_Message("[polygon_polylines] Error[-2009] SHPWriteObject failed" );
                                                    error_found = true;
                                                }

                                                if ( ! DBFWriteIntegerAttribute(newdbf, record, field, record+1) )
                                                {
                                                    main_window->Log_Message("[polygon_polylines] Error[-2010] DBFWriteIntegerAttribute failed" );
                                                    error_found = true;
                                                }
                                                else
                                                {
                                                    record++;
                                                }

                                            }
                                            /**********************************************************/
                                        }
                                    }
                                    //cout<<junction[i][jctCount[i]-1][0]<<" "<<vertex[i]-1<<" | ";
                                    /**********************************************************/

                                    start = junction[i][jctCount[i]-1][0];
                                    end = vertex[i]-1;
                                    vertices = 0;

                                    if(start < 0)
                                    {
                                        main_window->Log_Message("[polygon_polylines] Error[-3000] start < 0" );
                                        error_found = true;
                                    }
                                    if(end < 0)
                                    {
                                        main_window->Log_Message("[polygon_polylines] Error[-3001] end < 0" );
                                        error_found = true;
                                    }
                                    if(start > end)
                                    {
                                        main_window->Log_Message("[polygon_polylines] Error[-3002] start > end" );
                                        error_found = true;
                                    }

                                    if(!error_found)
                                    {
                                        for(int i = start; i <= end; i++)
                                        {
                                            X[vertices]=obj1->padfX[i];
                                            Y[vertices]=obj1->padfY[i];
                                            Z[vertices]=0;
                                            vertices++;
                                        }

                                        newobj = SHPCreateSimpleObject(SHPT_ARC, vertices, X, Y, Z);
                                        if(newobj == nullptr)
                                        {
                                            main_window->Log_Message("[polygon_polylines] Error[-3003] SHPCreateSimpleObject failed" );
                                            error_found = true;
                                        }
                                        else
                                        {

                                            if ( SHPWriteObject(newshp, -1, newobj) < 0 )
                                            {
                                                main_window->Log_Message("[polygon_polylines] Error[-3004] SHPWriteObject failed " );
                                                error_found = true;
                                            }

                                            if(!error_found)
                                            {
                                                if ( ! DBFWriteIntegerAttribute(newdbf, record, field, record+1) )
                                                {
                                                    main_window->Log_Message("[polygon_polylines] Error[-3005] DBFWriteIntegerAttribute failed " );
                                                    error_found = true;
                                                }
                                                else
                                                {
                                                    record++;
                                                }
                                            }
                                        }
                                        /**********************************************************/
                                    }
                                }

                                if(junction[i][0][0]>junction[i][jctCount[i]-1][1])
                                {
                                    //cout<<junction[i][jctCount[i]-1][1]<<" "<<junction[i][0][0]<<" | ";
                                    /**********************************************************/
                                    start = junction[i][jctCount[i]-1][1];
                                    end = junction[i][0][0];
                                    vertices = 0;

                                    if(start < 0)
                                    {
                                        main_window->Log_Message("[polygon_polylines] Error[-4000] start < 0" );
                                        error_found = true;
                                    }
                                    if(end < 0)
                                    {
                                        main_window->Log_Message("[polygon_polylines] Error[-4001] end < 0" );
                                        error_found = true;
                                    }
                                    if(start > end)
                                    {
                                        main_window->Log_Message("[polygon_polylines] Error[-4002] start > end" );
                                        error_found = true;
                                    }

                                    if(!error_found)
                                    {

                                        for(int i=start; i <= end; i++)
                                        {
                                            X[vertices] = obj1->padfX[i];
                                            Y[vertices] = obj1->padfY[i];
                                            Z[vertices] = 0;
                                            vertices++;
                                        }

                                        newobj = SHPCreateSimpleObject(SHPT_ARC, vertices, X, Y, Z);
                                        if(newobj == nullptr)
                                        {
                                            main_window->Log_Message("[polygon_polylines] Error[-4003] SHPCreateSimpleObject failed" );
                                            error_found = true;
                                        }
                                        else
                                        {
                                            if ( SHPWriteObject(newshp, -1, newobj) < 0 )
                                            {
                                                main_window->Log_Message("[polygon_polylines] Error[-4004] SHPWriteObject failed" );
                                                error_found = true;
                                            }

                                            if(!error_found)
                                            {
                                                if ( ! DBFWriteIntegerAttribute(newdbf, record, field, record+1) )
                                                {
                                                    main_window->Log_Message("[polygon_polylines] Error[-4005] DBFWriteIntegerAttribute failed" );
                                                    error_found = true;
                                                }
                                                else
                                                {
                                                    record++;
                                                }
                                            }
                                        }

                                    }
                                    /**********************************************************/
                                }
                            }
                            else
                            {
                                if(junction[i][0][0] != 0)
                                {
                                    //cout<<"0"<<" "<<junction[i][0][0]<<" | ";
                                    /**********************************************************/
                                    start = 0;
                                    end = junction[i][0][0];
                                    vertices = 0;

                                    if(start < 0)
                                    {
                                        main_window->Log_Message("[polygon_polylines] Error[-5000] start < 0" );
                                        error_found = true;
                                    }
                                    if(end < 0)
                                    {
                                        main_window->Log_Message("[polygon_polylines] Error[-5001] end < 0" );
                                        error_found = true;
                                    }
                                    if(start > end)
                                    {
                                        main_window->Log_Message("[polygon_polylines] Error[-5002] start > end" );
                                        error_found = true;
                                    }

                                    if(!error_found)
                                    {
                                        for(int i = start; i <= end; i++)
                                        {
                                            X[vertices] = obj1->padfX[i];
                                            Y[vertices] = obj1->padfY[i];
                                            Z[vertices] = 0;
                                            vertices++;
                                        }

                                        newobj = SHPCreateSimpleObject(SHPT_ARC, vertices, X, Y, Z);
                                        if(newobj == nullptr)
                                        {
                                            main_window->Log_Message("[polygon_polylines] Error[-5003] SHPCreateSimpleObject failed" );
                                            error_found = true;
                                        }
                                        else
                                        {
                                            if ( SHPWriteObject(newshp, -1, newobj) < 0 )
                                            {
                                                main_window->Log_Message("[polygon_polylines] Error[-5004] SHPWriteObject failed" );
                                                error_found = true;
                                            }

                                            if ( ! DBFWriteIntegerAttribute(newdbf, record, field, record+1) )
                                            {
                                                main_window->Log_Message("[polygon_polylines] Error[-5005] DBFWriteIntegerAttribute failed" );
                                                error_found = true;
                                            }
                                            else
                                            {
                                                record++;
                                            }

                                        }
                                    }
                                    /**********************************************************/
                                }

                                if(junction[i][jctCount[i]-1][2]==1)
                                {
                                    //cout<<junction[i][jctCount[i]-1][0]<<" "<<junction[i][jctCount[i]-1][1]<<" | ";
                                    /**********************************************************/
                                    start = junction[i][jctCount[i]-1][0];
                                    end = junction[i][jctCount[i]-1][1];
                                    vertices = 0;

                                    if(start < 0)
                                    {
                                        main_window->Log_Message("[polygon_polylines] Error[-6000] start < 0" );
                                        error_found = true;
                                    }
                                    if(end < 0)
                                    {
                                        main_window->Log_Message("[polygon_polylines] Error[-6001] end < 0" );
                                        error_found = true;
                                    }
                                    if(start > end)
                                    {
                                        main_window->Log_Message("[polygon_polylines] Error[-6002] start > end" );
                                        error_found = true;
                                    }

                                    if(!error_found)
                                    {
                                        for(int i = start; i <= end; i++)
                                        {
                                            X[vertices] = obj1->padfX[i];
                                            Y[vertices] = obj1->padfY[i];
                                            Z[vertices] = 0;
                                            vertices++;
                                        }

                                        newobj = SHPCreateSimpleObject(SHPT_ARC, vertices, X, Y, Z);
                                        if(newobj == nullptr)
                                        {
                                            main_window->Log_Message("[polygon_polylines] Error[-6003] SHPCreateSimpleObject failed" );
                                            error_found = true;
                                        }
                                        else
                                        {

                                            if ( SHPWriteObject(newshp, -1, newobj) < 0 )
                                            {
                                                main_window->Log_Message("[polygon_polylines] Error[-6004] SHPWriteObject failed" );
                                                error_found = true;
                                            }

                                            if(!error_found)
                                            {
                                                if ( ! DBFWriteIntegerAttribute(newdbf, record, field, record+1) )
                                                {
                                                    main_window->Log_Message("[polygon_polylines] Error[-6005] DBFWriteIntegerAttribute failed" );
                                                    error_found = true;
                                                }
                                                else
                                                {
                                                    record++;
                                                }
                                            }
                                        }
                                    }
                                    /**********************************************************/
                                }

                                if(junction[i][jctCount[i]-1][1]<vertex[i]-1)
                                {
                                    //cout<<junction[i][jctCount[i]-1][1]<<" "<<vertex[i]-1<<" | ";
                                    /**********************************************************/
                                    start = junction[i][jctCount[i]-1][1];
                                    end = vertex[i]-1;
                                    vertices = 0;

                                    if(start < 0)
                                    {
                                        main_window->Log_Message("[polygon_polylines] Error[-7000] start < 0" );
                                        error_found = true;
                                    }
                                    if(end < 0)
                                    {
                                        main_window->Log_Message("[polygon_polylines] Error[-7001] end < 0" );
                                        error_found = true;
                                    }
                                    if(start > end)
                                    {
                                        main_window->Log_Message("[polygon_polylines] Error[-7002] start > end" );
                                        error_found = true;
                                    }

                                    if(!error_found)
                                    {

                                        for(int i = start; i <= end; i++)
                                        {
                                            X[vertices] = obj1->padfX[i];
                                            Y[vertices] = obj1->padfY[i];
                                            Z[vertices] = 0;
                                            vertices++;
                                        }

                                        newobj = SHPCreateSimpleObject(SHPT_ARC, vertices, X, Y, Z);
                                        if(newobj == nullptr)
                                        {
                                            main_window->Log_Message("[polygon_polylines] Error[-8003] SHPCreateSimpleObject failed" );
                                            error_found = true;
                                        }
                                        else
                                        {
                                            if ( SHPWriteObject(newshp, -1, newobj) < 0 )
                                            {
                                                main_window->Log_Message("[polygon_polylines] Error[-8004] SHPWriteObject failed" );
                                                error_found = true;
                                            }

                                            if(!error_found)
                                            {
                                                if ( ! DBFWriteIntegerAttribute(newdbf, record, field, record+1) )
                                                {
                                                    main_window->Log_Message("[polygon_polylines] Error[-8005] DBFWriteIntegerAttribute failed" );
                                                    error_found = true;
                                                }
                                                else
                                                {
                                                    record++;
                                                }
                                            }
                                        }
                                    }
                                    /**********************************************************/
                                }
                            }

                            for(int j = 0; j < jctCount[i]-1; j++)
                            {
                                if(junction[i][j][2]==1)
                                {
                                    //cout<<junction[i][j][0]<<" "<<junction[i][j][1]<<" | ";
                                    /**********************************************************/
                                    start = junction[i][j][0];
                                    end = junction[i][j][1];
                                    vertices = 0;


                                    if(start < 0)
                                    {
                                        main_window->Log_Message("[polygon_polylines] Error[-9000] start < 0" );
                                        error_found = true;
                                    }
                                    if(end < 0)
                                    {
                                        main_window->Log_Message("[polygon_polylines] Error[-9001] end < 0" );
                                        error_found = true;
                                    }
                                    if(start > end)
                                    {
                                        main_window->Log_Message("[polygon_polylines] Error[-9002] start > end" );
                                        error_found = true;
                                    }

                                    if(!error_found)
                                    {
                                        for(int i = start; i <= end; i++)
                                        {
                                            X[vertices]=obj1->padfX[i];
                                            Y[vertices]=obj1->padfY[i];
                                            Z[vertices]=0;
                                            vertices++;
                                        }

                                        newobj = SHPCreateSimpleObject(SHPT_ARC, vertices, X, Y, Z);

                                        if(newobj == nullptr)
                                        {
                                            main_window->Log_Message("[polygon_polylines] Error[-9003] SHPCreateSimpleObject failed" );
                                            error_found = true;
                                        }
                                        else
                                        {
                                            if ( SHPWriteObject(newshp, -1, newobj) < 0 )
                                            {
                                                main_window->Log_Message("[polygon_polylines] Error[-9004] SHPWriteObject failed" );
                                                error_found = true;
                                            }

                                            if(!error_found)
                                            {
                                                if ( ! DBFWriteIntegerAttribute(newdbf, record, field, record+1) )
                                                {
                                                    main_window->Log_Message("[polygon_polylines] Error[-9005] DBFWriteIntegerAttribute failed" );
                                                    error_found = true;
                                                }
                                                else
                                                {
                                                    record++;
                                                }
                                            }
                                        }
                                    }
                                    /**********************************************************/
                                }

                                if(junction[i][j][1]<junction[i][j+1][0])
                                {
                                    //cout<<junction[i][j][1]<<" "<<junction[i][j+1][0]<<" | ";
                                    /**********************************************************/
                                    start = junction[i][j][1];
                                    end = junction[i][j+1][0];
                                    vertices = 0;

                                    if(start < 0)
                                    {
                                        main_window->Log_Message("[polygon_polylines] Error[-9100] start < 0" );
                                        error_found = true;
                                    }
                                    if(end < 0)
                                    {
                                        main_window->Log_Message("[polygon_polylines] Error[-9101] end < 0" );
                                        error_found = true;
                                    }
                                    if(start > end)
                                    {
                                        main_window->Log_Message("[polygon_polylines] Error[-9102] start > end" );
                                        error_found = true;
                                    }

                                    if(!error_found)
                                    {
                                        for(int i = start; i <= end; i++)
                                        {
                                            X[vertices] = obj1->padfX[i];
                                            Y[vertices] = obj1->padfY[i];
                                            Z[vertices] = 0;
                                            vertices++;
                                        }

                                        newobj = SHPCreateSimpleObject(SHPT_ARC, vertices, X, Y, Z);

                                        if(newobj == nullptr)
                                        {
                                            main_window->Log_Message("[polygon_polylines] Error[-9103] SHPCreateSimpleObject failed" );
                                            error_found = true;
                                        }
                                        else
                                        {
                                            if ( SHPWriteObject(newshp, -1, newobj) < 0 )
                                            {
                                                main_window->Log_Message("[polygon_polylines] Error[-9104] SHPWriteObject failed" );
                                                error_found = true;
                                            }

                                            if(!error_found)
                                            {
                                                if ( ! DBFWriteIntegerAttribute(newdbf, record, field, record+1) )
                                                {
                                                    main_window->Log_Message("[polygon_polylines] Error[-9105] DBFWriteIntegerAttribute failed" );
                                                    error_found = true;
                                                }
                                                else
                                                {
                                                    record++;
                                                }
                                            }
                                        }

                                    }
                                    /**********************************************************/
                                }
                            }
                        }
                    }
                }
            }
        }

        //////////////////////////////////////////////////////////////////////////////////////////
        //TODO Memory leaks here with X,Y, Z and other locations
        if ( error_found )
        {
            main_window->Log_Message("[polygon_polylines] Error[-9999] Error(s) found during shapefile creation " );

            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);

            //Clean up
            for(int i=0; i < recordCount; i++)
            {
                for(int j=0; j < 30; j++) //Where does 30 come from?
                {
                    delete junction[i][j];
                }
            }

            delete[] junction;

            return -9999;
        }


        SHPClose(shp);
        DBFClose(dbf);
        SHPClose(newshp);
        DBFClose(newdbf);

        //Clean up
        for(int i=0; i < recordCount; i++)
        {
            for(int j=0; j < 30; j++) //Where does 30 come from?
            {
                delete junction[i][j];
            }
        }

        delete[] junction;



    } catch (...) {
        qDebug() << "Error: polygon_polylines is returning w/o checking";
    }

    return(0);
}	



