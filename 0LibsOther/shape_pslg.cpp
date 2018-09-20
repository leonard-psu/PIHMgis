#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>

#include <QString>
#include <QDebug>

#include "./../0LibsShape/shapefil.h"
#include "globals.h"


using namespace std;

struct Point{
    double x,y;
    int serialNum;
};

struct Line{
    int pt1, pt2;
};


int searchPoint(Point* pointArray, double coord1, double coord2, int *temp, int pointCounter)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start searchPoint";

    try {

        for(int i=0;i<pointCounter;i++){
            if(fabs(pointArray[i].x - coord1) < epsilon && fabs(pointArray[i].y - coord2) < epsilon)
            {
                *temp=i;
                //std::cout<<"++++++++++++++++++++++++++ "<<i<<"\n";
                return 1;
            }
        }

    } catch (...) {
        qDebug() << "Error: searchPoint is returning w/o checking";
    }

    return 0;
}


int shape_pslg(const char* constFileName, const char* outputFileName, QString *tempLogString)
{
    try {

        if(print_debug_messages)
            qDebug() << "INFO: Start shape_pslg";

        //tempLogString->append("Running Read Topology ... <br>");

        //SHPInfo* currentHandle = SHPOpen("/root/Desktop/testData/q20.shp","r+");
        cout<<"File: "<<constFileName<<"\n";
        SHPHandle thisObj = SHPOpen(constFileName,"r+");
        if(thisObj == nullptr)
            return 53;

        int numEntities, shapeType;
        double minBound[4], maxBound[4];
        //SHPGetInfo(thisObj, &numEntities, &shapeType, thisObj->adBoundsMin,thisObj->adBoundsMax);
        SHPGetInfo(thisObj, &numEntities, &shapeType, minBound, maxBound);

        if ( shapeType != SHPT_ARC )
        {
            cout << "Not a SHPT_ARC: ... " << constFileName << "\n";
            cout << "SHAPE TYPE = " << shapeType << "\n";
            return shapeType;
        }

        std::cout<<"============ SHAPE FILE DETAILS===============\n";
        std::cout<<"Number of Entities:"<<numEntities<<"\n"<<"Shapefile type:"<<shapeType<<"\n"<<"Minimum Bound "<<minBound<<"\n"<<"Maximum Bound "<<maxBound<<"\n";



        std::cout<<thisObj->adBoundsMin[0]<<"\n";
        std::cout<<thisObj->adBoundsMax[0]<<"\n";


        tempLogString->append("Reading Nodes ... <br>");
        Line* lineArray = new Line[numEntities];

        Point* pointArray = new Point[2*numEntities];

        int lineCounter=0;
        int pointCounter=0;
        int tempPt;


        SHPObject* thisObjHandle;
        for(int i=0; i<numEntities; i++)
        {
            thisObjHandle  = SHPReadObject(thisObj, i);
            if ( thisObjHandle->nVertices > 2 )
            {

                tempLogString->append(QString("<span style=\"color:#FF0000\">ERROR: Shape File Not Split Line </span>")+QString("<br>"));
                return 93;
            }
            std::cout<<"Read Object # "<<i<<"\n";


            // Line Pt 1
            if(pointCounter!=0 && searchPoint(pointArray,thisObjHandle->padfX[0],thisObjHandle->padfY[0],&tempPt, pointCounter)){
                lineArray[lineCounter].pt1=tempPt;
            }
            else
            {
                if(thisObjHandle == nullptr)
                    cout<<"testNULL\n";


                pointArray[pointCounter].x=thisObjHandle->padfX[0]; pointArray[pointCounter].y=thisObjHandle->padfY[0];
                lineArray[lineCounter].pt1=pointCounter;
                ++pointCounter;
            }
            std::cout<<"Line Pt 2\n";
            // Line Pt 2
            if(pointCounter!=0 && searchPoint(pointArray,thisObjHandle->padfX[1],thisObjHandle->padfY[1],&tempPt, pointCounter))
            {
                lineArray[lineCounter].pt2=tempPt;
            }
            else
            {
                pointArray[pointCounter].x=thisObjHandle->padfX[1]; pointArray[pointCounter].y=thisObjHandle->padfY[1];
                lineArray[lineCounter].pt2=pointCounter;
                ++pointCounter;
            }
            ++lineCounter;

            std::cout<<"++++++++++++++++++++++++++++ LINE COUNTER:"<<lineCounter<<"\n"; //getchar(); getchar();
        }


        tempLogString->append("Writing PSLG (.poly) File ... <br>");

        ofstream fp;
        fp.open(outputFileName);

        fp<<pointCounter<<" "<<"2"<<" "<<"0"<<" "<<" "<<"0"<<"\n";
        for(int i=0; i<pointCounter; i++)
        {
            fp<<i+1<<" "<<setprecision (20)<<pointArray[i].x<<" "<<setprecision (20)<<pointArray[i].y<<"\n";
        }
        fp<<"\n";
        fp<<numEntities<<" "<<"0"<<"\n";
        for(int i=0;i<numEntities;i++)
        {
            fp<<i+1<<" "<<lineArray[i].pt1+1<<" "<<lineArray[i].pt2+1<<"\n";
        }
        fp<<"0"<<"\n";
        fp.close();


        SHPClose(thisObj);


    } catch (...) {
        qDebug() << "Error: shape_pslg is returning w/o checking";
    }

    return 0;

}
