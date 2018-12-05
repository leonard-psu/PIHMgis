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

int compareSlope(Lines *a, Lines *b)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start compareSlope";

    try {
        if(b->x2-b->x1 !=0 && a->x2-a->x1 !=0)
        {
            if(fabs(fabs((b->y2-b->y1)/(b->x2-b->x1))-fabs((a->y2-a->y1)/(a->x2-a->x1))) < epsilon )
                return 1;
            else
                return 0;
        }
        else
        {
            if(fabs(b->x2-b->x1)-fabs(a->x2-a->x1) < epsilon)
                return 1;
            else
                return 0;
        }

    } catch (...) {
        qDebug() << "Error: compareSlope is returning w/o checking";
        return -100;
    }
}

int compareLines(Lines *a, Lines *b)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start compareLines";

    try {
        if(fabs(a->x1-b->x1)<epsilon && fabs(a->y1-b->y1)<epsilon)
        {
            if(fabs(a->x2-b->x2)<epsilon && fabs(a->y2-b->y2)<epsilon)
                return 1;
            else
                return 0;
        }
        else if(fabs(a->x1-b->x2)<epsilon && fabs(a->y1-b->y2)<epsilon)
        {
            if(fabs(a->x2-b->x1)<epsilon && fabs(a->y2-b->y1)<epsilon)
                return 1;
            else
                return 0;
        }
        /*
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
        return 0;
    }
}

inline int doesIntersect(Lines *l, double x1, double y1)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start doesIntersect";

    try {
        double a=sqrt(pow(l->x1-l->x2,2)+pow(l->y1-l->y2,2));
        double b=sqrt(pow(l->x1-x1,2)+pow(l->y1-y1,2));
        double c=sqrt(pow(l->x2-x1,2)+pow(l->y2-y1,2));
        double s=(a+b+c)/2;

        if(fabs(a-b-c)<epsilon && b>epsilon && c>epsilon)
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

int dissolve(const char* shpFileName, const char* dbfFileName, const char *newshpFileName, const char *newdbfFileName)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start dissolve";

    try {
        int recordCount = 0;

        SHPHandle shp = SHPOpen(shpFileName, "rb");    
        if(shp == nullptr)
        {
            main_window->Log_Message("[dissolve] Error shpFileName is NULL. Returning 79.");
            return 79;
        }

        DBFHandle dbf = DBFOpen(dbfFileName, "rb");
        if(dbf == nullptr)
        {
            main_window->Log_Message("[dissolve] Error dbfFileName is NULL. Returning 79.");
            return 79;
        }

        if ( shp == nullptr || dbf == nullptr )
            return 79;

        int InfoShpType;
        SHPGetInfo (shp, nullptr, &InfoShpType, nullptr, nullptr);
        if ( InfoShpType != SHPT_POLYGON )
        {
            cout << "Not a SHPT_POLYGON: ... " << shpFileName << "\n";
            cout << "SHAPE TYPE = " << InfoShpType << "\n";
            return InfoShpType;
        }

        SHPHandle newshp = SHPCreate(newshpFileName, SHPT_POLYGON);
        if(newshp == nullptr)
        {
            main_window->Log_Message("[dissolve] Error newshpFileName is NULL. Returning 94.");
            return 94;
        }
        DBFHandle newdbf = DBFCreate(newdbfFileName);
        if(newdbf == nullptr)
        {
            main_window->Log_Message("[dissolve] Error newdbfFileName is NULL. Returning 94.");
            return 94;
        }

        if ( newshp == nullptr || newdbf == nullptr )
            return 94;

        int PolyID  = DBFAddField(newdbf,  "PolyID", FTInteger, 5, 0);
        if ( PolyID == -1 )
            return 97;

        recordCount = DBFGetRecordCount(dbf);

        SHPObject **obj = new SHPObject*[recordCount];
        int vertices; int totalLines=0;
        Lines **lines; int **lineFlag;
        double *dfXMax, *dfXMin, *dfYMax, *dfYMin;
        lines = (Lines **)malloc(recordCount*sizeof(Lines *));
        lineFlag = (int **)malloc(recordCount*sizeof(int *));
        dfXMax = (double *)malloc(recordCount*sizeof(double));
        dfXMin = (double *)malloc(recordCount*sizeof(double));
        dfYMax = (double *)malloc(recordCount*sizeof(double));
        dfYMin = (double *)malloc(recordCount*sizeof(double));

        int *numLines;
        numLines=(int *)malloc(recordCount*sizeof(int));
        //1 Read each polygon and store points in form of lines
        for(int i=0; i<recordCount; i++)
        {
            vertices = 0;
            obj[i] = SHPReadObject(shp, i);
            dfXMax[i]=obj[i]->dfXMax; dfXMin[i]=obj[i]->dfXMin;
            dfYMax[i]=obj[i]->dfYMax; dfYMin[i]=obj[i]->dfYMin;
            cout<<"poly= "<<i<<" vertices= "<<obj[i]->nVertices<<"\n";
            vertices=obj[i]->nVertices;
            numLines[i]=vertices-1;
            totalLines+=numLines[i];
            lines[i]= (Lines *)malloc(vertices*20*sizeof(Lines));
            lineFlag[i]=(int *)malloc(vertices*20*sizeof(int));
            for(int j=0; j<vertices-1; j++)
            {
                lines[i][j].x1=obj[i]->padfX[j];
                lines[i][j].y1=obj[i]->padfY[j];
                lines[i][j].x2=obj[i]->padfX[j+1];
                lines[i][j].y2=obj[i]->padfY[j+1];
                lineFlag[i][j]=1;
            }
        } //1 done!

        cout<<"vertices= "<<vertices<<"\n";
        cout<<"totalLines1= "<<totalLines<<"\n";

        //1.1 Find intersections and insert a line
        //double fa, fb;
        double minX, maxX, minY, maxY;
        for(int i=0; i<recordCount; i++)
        {
            cout<<"done 1.1 poly "<<i<<"\n";
            for(int k=i+1; k<recordCount; k++)
            {
                if(i==k) continue;
                if((dfXMax[i]<dfXMin[k] || dfXMax[k]<dfXMin[i] || dfYMax[i]<dfYMin[k] || dfYMax[k]<dfYMin[i]))
                    continue;

                cout<<"k = "<<k<<"\n";
                for(int j=0; j<numLines[i]; j++)
                {
                    for(int l=0; l<numLines[k]; l++)
                    {
                        //if(compareLines(&(lines[i][j]), &(lines[k][l]))!=1){
                        if(lines[i][j].x1>lines[i][j].x2)
                        {
                            minX=lines[i][j].x2;
                            maxX=lines[i][j].x1;
                        }
                        else
                        {
                            minX=lines[i][j].x1;
                            maxX=lines[i][j].x2;
                        }

                        if(lines[i][j].y1>lines[i][j].y2)
                        {
                            minY=lines[i][j].y2;
                            maxY=lines[i][j].y1;
                        }
                        else
                        {
                            minY=lines[i][j].y1;
                            maxY=lines[i][j].y2;
                        }

                        if(lines[k][l].x1>=minX && lines[k][l].x1<=maxX && lines[k][l].y1>=minY && lines[k][l].y1<=maxY)
                        {
                            //if(lines[k][l].x1>dfXMin[i] && lines[k][l].x1<dfXMax[i] && lines[k][l].y1>dfYMin[i] && lines[k][l].y1<dfYMax[i]){
                            if(doesIntersect(&(lines[i][j]), lines[k][l].x1, lines[k][l].y1)==1)
                            {
                                lines[i][numLines[i]].x1=lines[k][l].x1;
                                lines[i][numLines[i]].y1=lines[k][l].y1;
                                lines[i][numLines[i]].x2=lines[i][j].x2;
                                lines[i][numLines[i]].y2=lines[i][j].y2;
                                lineFlag[i][numLines[i]]=1;
                                numLines[i]++; totalLines++;
                                lines[i][j].x2=lines[k][l].x1;
                                lines[i][j].y2=lines[k][l].y1;
                                continue;
                            }
                        }
                        if(lines[k][l].x2>=minX && lines[k][l].x2<=maxX && lines[k][l].y2>=minY && lines[k][l].y2<=maxY)
                        {
                            //if(lines[k][l].x2>dfXMin[i] && lines[k][l].x2<dfXMax[i] && lines[k][l].y2>dfYMin[i] && lines[k][l].y2<dfYMax[i]){
                            if(doesIntersect(&(lines[i][j]), lines[k][l].x2, lines[k][l].y2)==1)
                            {
                                lines[i][numLines[i]].x1=lines[k][l].x2;
                                lines[i][numLines[i]].y1=lines[k][l].y2;
                                lines[i][numLines[i]].x2=lines[i][j].x2;
                                lines[i][numLines[i]].y2=lines[i][j].y2;
                                lineFlag[i][numLines[i]]=1;
                                numLines[i]++; totalLines++;
                                lines[i][j].x2=lines[k][l].x2;
                                lines[i][j].y2=lines[k][l].y2;
                                continue;
                            }
                        }

                        if(lines[k][l].x1>lines[k][l].x2)
                        {
                            minX=lines[k][l].x2;
                            maxX=lines[k][l].x1;
                        }
                        else
                        {
                            minX=lines[k][l].x1;
                            maxX=lines[k][l].x2;
                        }

                        if(lines[k][l].y1>lines[k][l].y2)
                        {
                            minY=lines[k][l].y2;
                            maxY=lines[k][l].y1;
                        }
                        else
                        {
                            minY=lines[k][l].y1;
                            maxY=lines[k][l].y2;
                        }

                        if(lines[i][j].x1>=minX && lines[i][j].x1<=maxX && lines[i][j].y1>=minY && lines[i][j].y1<=maxY)
                        {
                            //if(lines[i][j].x1>dfXMin[k] && lines[i][j].x1<dfXMax[k] && lines[i][j].y1>dfYMin[k] && lines[i][j].y1<dfYMax[k]){
                            if(doesIntersect(&(lines[k][l]), lines[i][j].x1, lines[i][j].y1)==1)
                            {
                                lines[k][numLines[k]].x1=lines[i][j].x1;
                                lines[k][numLines[k]].y1=lines[i][j].y1;
                                lines[k][numLines[k]].x2=lines[k][l].x2;
                                lines[k][numLines[k]].y2=lines[k][l].y2;
                                lineFlag[k][numLines[k]]=1;
                                numLines[k]++; totalLines++;
                                lines[k][l].x2=lines[i][j].x1;
                                lines[k][l].y2=lines[i][j].y1;
                                continue;
                            }
                        }
                        if(lines[i][j].x2>=minX && lines[i][j].x2<=maxX && lines[i][j].y2>=minY && lines[i][j].y2<=maxY)
                        {
                            //if(lines[i][j].x2>dfXMin[k] && lines[i][j].x2<dfXMax[k] && lines[i][j].y2>dfYMin[k] && lines[i][j].y2<dfYMax[k]){
                            if(doesIntersect(&(lines[k][l]), lines[i][j].x2, lines[i][j].y2)==1)
                            {
                                lines[k][numLines[k]].x1=lines[i][j].x2;
                                lines[k][numLines[k]].y1=lines[i][j].y2;
                                lines[k][numLines[k]].x2=lines[k][l].x2;
                                lines[k][numLines[k]].y2=lines[k][l].y2;
                                lineFlag[k][numLines[k]]=1;
                                numLines[k]++; totalLines++;
                                lines[k][l].x2=lines[i][j].x2;
                                lines[k][l].y2=lines[i][j].y2;
                                continue;
                            }
                        }
                        //}
                    }
                }
            }
        }

        cout<<"totalLines2= "<<totalLines<<"\n";

        //2 Delete common lines
        int totalLines3=totalLines;
        for(int i=0; i<recordCount; i++)
        {
            cout<<"done 2 poly "<<i<<"\n";
            for(int j=0; j<numLines[i]; j++)
            {
                for(int k=i+1; k<recordCount; k++)
                {
                    for(int l=0; l<numLines[k]; l++)
                    {
                        if(compareLines(&(lines[i][j]), &(lines[k][l]))==1)
                        {
                            lineFlag[i][j]=0;
                            lineFlag[k][l]=0;
                            totalLines3=totalLines3-2;
                        }
                    }
                }
            }
        }// 2 done!
        cout<<"totalLines3= "<<totalLines3<<"\n";

        int tempCount;
        for(int i=0; i<recordCount; i++)
        {
            tempCount=0;
            for(int j=0; j<numLines[i]; j++)
            {
                if(lineFlag[i][j]!=0)
                    tempCount++;
            }
            cout<<".poly= "<<i<<" lines= "<<tempCount<<"\n";
        }

        //3 Store polygon's lines in one place
        Lines *newlines; int count=0;
        newlines = (Lines *)malloc(totalLines*2*sizeof(Lines));
        for(int i=0; i<recordCount; i++)
        {
            for(int j=0; j<numLines[i]; j++)
            {
                if(lineFlag[i][j]!=0)
                {
                    newlines[count].x1=lines[i][j].x1;
                    newlines[count].y1=lines[i][j].y1;
                    newlines[count].x2=lines[i][j].x2;
                    newlines[count].y2=lines[i][j].y2;
                    count++;
                }
            }
        }//3 done!
        cout<<"count= "<<count<<"\n";

        //4 Collect all the points
        double *X; X = (double *)malloc(count*3*sizeof(double));//new double[totalLines*2];
        double *Y; Y = (double *)malloc(count*3*sizeof(double));//new double[totalLines*2];
        double *Z; Z = (double *)malloc(count*3*sizeof(double));//new double[totalLines*2];
        int numPoints=0;
        cout<<"Assembling points... ";
        //getchar(); getchar();

        X[0]=newlines[0].x1;
        Y[0]=newlines[0].y1;
        Z[0]=0.0;
        numPoints++;
        X[1]=newlines[0].x2; Y[1]=newlines[0].y2; Z[1]=0.0;
        numPoints++;
        //cout<<X[0]<<","<<Y[0]<<" + "<<X[1]<<","<<Y[1]<<"\n";
        int currentline=0;
        double ptx=X[1];
        double pty=Y[1];
        int finished=1;

        while(finished==1)
        {
            finished=0;
            for(int i=0; i<count; i++)
            {
                if (i!=currentline)
                {
                    if(fabs(ptx-newlines[i].x1)<epsilon && fabs(pty-newlines[i].y1)<epsilon)
                    {
                        X[numPoints]=newlines[i].x2;
                        Y[numPoints]=newlines[i].y2;
                        //cout<<"currentline= "<<currentline<<" i= "<<i<<"n"; getchar(); getchar();
                        ptx=newlines[i].x2;
                        pty=newlines[i].y2;
                        Z[numPoints]=0.0;
                        numPoints++;
                        currentline=i;
                        if(i==0)
                        {
                            finished=0;
                            numPoints--;
                        }
                        else
                            finished=1;

                        //cout<<numPoints<<"\n";
                        //cout<<"break\n";
                        break;
                    }
                    else if(fabs(ptx-newlines[i].x2)<epsilon && fabs(pty-newlines[i].y2)<epsilon)
                    {
                        X[numPoints]=newlines[i].x1;
                        Y[numPoints]=newlines[i].y1;
                        //cout<<"currentline= "<<currentline<<" i= "<<i<<"n"; getchar(); getchar();
                        ptx=newlines[i].x1;
                        pty=newlines[i].y1;
                        Z[numPoints]=0.0;
                        numPoints++;
                        currentline=i;
                        if(i==0)
                        {
                            finished=0;
                            numPoints--;
                        }
                        else
                            finished=1;

                        //cout<<numPoints<<"\n";
                        //cout<<"break\n";
                        break;
                    }
                }
            }
        }
        cout<<"done\n";

        SHPObject *newobj;
        newobj = SHPCreateSimpleObject(SHPT_POLYGON, numPoints, X, Y, Z);
        if ( SHPWriteObject(newshp, -1, newobj) < 0 )
            return 503;
        if ( ! DBFWriteIntegerAttribute(newdbf, 0,   PolyID,  1) )
            return 505;
        SHPClose(shp);
        DBFClose(dbf);

        SHPClose(newshp);
        DBFClose(newdbf);

        //SHPClose(ptshp);
        //DBFClose(ptdbf);

    } catch (...) {
        qDebug() << "Error: dissolve is returning w/o checking";
    }

    return 0;
}
