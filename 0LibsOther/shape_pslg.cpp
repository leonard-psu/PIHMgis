#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>

#include <QString>
#include <QDebug>

#include "./../0LibsShape/shapefil.h"
#include "globals.h"


using namespace std;

// User interface to PIHMgis v3.5
extern PIHMgisDialog *main_window;

struct Point{
    double x,y;
    int serialNum;
};

struct Line{
    int pt1, pt2;
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper function searchPoint
// Used in shape_pslg function below
// epsilon value may not be valid (needs testing with different datasets)
// *temp is assigned counter value
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool searchPoint(Point* pointArray, double coord1, double coord2, int *temp, int pointCounter)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start searchPoint";

    try {

        if(pointArray == nullptr)
        {
            main_window->Log_Message("[searchPoint] Error[false] pointArray is NULL.");
            return false;
        }

        for(int i=0; i< pointCounter;i++)
        {
            if(fabs(pointArray[i].x - coord1) < epsilon && fabs(pointArray[i].y - coord2) < epsilon)
            {
                *temp = i;
                return true;
            }
        }

    } catch (...) {
        qDebug() << "Error: searchPoint is returning w/o checking";
    }

    return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Writes Unsplit Shape Line data to text file
// Used in ReadTopology
// Note use of LogString to return messages to use in modal dialog
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int shape_pslg(const char* constFileName, const char* outputFileName, QString *tempLogString)
{
    try {

        if(print_debug_messages)
            qDebug() << "INFO: Start shape_pslg";

        if(constFileName == nullptr)
        {
            main_window->Log_Message("[shape_pslg] Error[50] constFileName is NULL ");
            return 50;
        }

        if(outputFileName == nullptr)
        {
            main_window->Log_Message("[shape_pslg] Error[51] outputFileName is NULL ");
            return 51;
        }

        if(tempLogString == nullptr)
        {
            main_window->Log_Message("[shape_pslg] Error[52] LogString is NULL ");
            return 52;
        }

        SHPHandle thisObj = SHPOpen(constFileName,"r+");

        if(thisObj == nullptr)
        {
            main_window->Log_Message("[shape_pslg] Error[53] Failed to open shapefile " + QString(constFileName));
            return 53;
        }

        int numEntities = -1;
        int shapeType;
        double minBound[4], maxBound[4];

        SHPGetInfo(thisObj, &numEntities, &shapeType, minBound, maxBound);

        if ( shapeType != SHPT_ARC )
        {
            main_window->Log_Message("[shape_pslg] Error[54] Incorrect shapefile type (expecting SHPT_ARC) from " + QString(constFileName));
            return shapeType;
        }

        if (print_debug_messages)
        {
            QString message = "Number of Entities:" + QString::number(numEntities) + "\n";
            message += "Shapefile type:" + QString::number(shapeType) + "\n";
            message += "Minimum Bound [0]" + QString::number(minBound[0]) + "\n";
            message += "Minimum Bound [1]" + QString::number(minBound[1]) + "\n";
            message += "Minimum Bound [2]" + QString::number(minBound[2]) + "\n";
            message += "Minimum Bound [3]" + QString::number(minBound[3]) + "\n";
            message += "Maximum Bound [0]" + QString::number(maxBound[0]) + "\n";
            message += "Maximum Bound [1]" + QString::number(maxBound[1]) + "\n";
            message += "Maximum Bound [2]" + QString::number(maxBound[2]) + "\n";
            message += "Maximum Bound [3]" + QString::number(maxBound[3]) + "\n";
        }

        if ( numEntities < 1 )
        {
            main_window->Log_Message("[shape_pslg] Error[55] Invalid number of entities, found " + QString::number(numEntities));
            return 55;
        }
        if ( numEntities > 250000 ) //250000 is a guess
        {
            main_window->Log_Message("[shape_pslg] Error[55] Too many entities, found " + QString::number(numEntities));
            return 56;
        }

        tempLogString->append("[shape_pslg] Reading Nodes ... <br>"+ QString(constFileName));

        Line* lineArray = new Line[numEntities];
        Point* pointArray = new Point[2*numEntities];

        int lineCounter=0;
        int pointCounter=0;
        int tempPt = -1;
        bool error_found_93 = false; //To minimize error outputs
        bool error_found_94 = false; //To minimize error outputs

        SHPObject* thisObjHandle;
        for(int i=0; i < numEntities; i++)
        {
            thisObjHandle  = SHPReadObject(thisObj, i);
            if(thisObjHandle == nullptr)
            {
                error_found_93 = true;
            }
            else {

                if ( thisObjHandle->nVertices > 2 )
                {
                    error_found_94 = true;
                    if(print_many_messages)
                    {
                        main_window->Log_Message("[shape_pslg] UNSplit Line Found at " + QString::number(i));
                    }
                }
                else
                {
                    if(print_many_messages)
                    {
                        main_window->Log_Message("[shape_pslg] Read Object # " + QString::number(i));
                    }

                    // Line Pt 1
                    bool found_pt1 = searchPoint(pointArray, thisObjHandle->padfX[0], thisObjHandle->padfY[0], &tempPt, pointCounter);
                    if(pointCounter !=0 && found_pt1)
                    {
                        lineArray[lineCounter].pt1 = tempPt;
                    }
                    else
                    {
                        pointArray[pointCounter].x = thisObjHandle->padfX[0];
                        pointArray[pointCounter].y = thisObjHandle->padfY[0];
                        lineArray[lineCounter].pt1 = pointCounter;
                        ++pointCounter;
                    }

                    // Line Pt 2
                    bool found_pt2 = searchPoint(pointArray, thisObjHandle->padfX[1], thisObjHandle->padfY[1], &tempPt, pointCounter);
                    if(pointCounter!=0 && found_pt2)
                    {
                        lineArray[lineCounter].pt2=tempPt;
                    }
                    else
                    {
                        pointArray[pointCounter].x = thisObjHandle->padfX[1];
                        pointArray[pointCounter].y = thisObjHandle->padfY[1];
                        lineArray[lineCounter].pt2=pointCounter;
                        ++pointCounter;
                    }
                    ++lineCounter;

                    if(print_many_messages)
                    {
                        main_window->Log_Message("[shape_pslg] Line Counter # " + QString::number(lineCounter));
                    }
                }
            }
        } //End of for(int i=0; i < numEntities; i++)

        if(error_found_93)
        {
            SHPClose(thisObj);
            delete [] lineArray;
            delete [] pointArray;

            tempLogString->append("[shape_pslg] Error[93] SHPReadObject NULL object");
            main_window->Log_Message("[shape_pslg] Error[93] SHPReadObject NULL object");
        }

        if(error_found_94 )
        {
            SHPClose(thisObj);
            delete [] lineArray;
            delete [] pointArray;

            tempLogString->append("[shape_pslg] Error[94] Found Unsplit Lines. User needs to split lines.");
            main_window->Log_Message("[shape_pslg] Error[94] Found Unsplit Lines. User needs to split lines.");
        }

        tempLogString->append("[shape_pslg] Writing PSLG (.poly) File ... <br>"+ QString(constFileName));
        main_window->Log_Message("[shape_pslg] Writing PSLG (.poly) File ... <br>"+ QString(constFileName));

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

        //Memory Cleanup
        delete [] lineArray;
        delete [] pointArray;

    } catch (...) {
        qDebug() << "Error: shape_pslg is returning w/o checking";
        return -5000;
    }

    return 0;

}
