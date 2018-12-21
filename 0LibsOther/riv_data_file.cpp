#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QDir>
#include <qmath.h>
#include <iostream>

#include "riv_data_file.h"
#include "./0LibsShape/shapefil.h"
#include "globals.h"

#define PI                      3.14159265359
#define distPt(p1, p2)          fabs(p1.x-p2.x)+fabs(p1.y-p2.y)
#define distXY(x1, y1, x2, y2)  fabs(x1-x2)+fabs(y1-y2)
#define distPtXY(p, x, y)       fabs(p.x-x)+fabs(p.y-y)

// User interface to PIHMgis v3.5
extern PIHMgisDialog *main_window;

QString riv_temp_fname = "/rivtemp.dbf";  //Note keep forward slash

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Calculate Slope between two points
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double SLOPE(Point p1, Point p2)
{
    if(print_many_messages)
        qDebug() << "INFO: Start SLOPE";

    double delX = p2.x - p1.x;
    double delY = delX==0?p2.y - p1.y + 0.0000001:p2.y - p1.y;

    if(delX<0.0 && delY>0.0)
        return 90 + (180.0/PI)*atan(fabs(delY)/fabs(delX));
    else if(delX<=0.0 && delY<=0.0)
        return 180 + (180.0/PI)*atan(fabs(delY)/fabs(delX));
    else if(delX>0.0 && delY<0.0)
        return -90 + (180.0/PI)*atan(fabs(delY)/fabs(delX));
    else
        return 0 + (180.0/PI)*atan(fabs(delY)/fabs(delX));

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Evaluate if two points are equal
// Zero means the point is not equal. One means the points are equal.
// Warning: Precision is a problem
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int IsEqualPoint( Point p1, Point p2 )
{
    if(print_many_messages)
        qDebug() << "INFO: Start IsEqualPoint";

    bool is_x_Equal = fabs(p1.x - p2.x) <= epsilon;
    bool is_y_Equal = fabs(p1.y - p2.y) <= epsilon;

    if(is_x_Equal && is_y_Equal)
        return 1;
    else
        return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Create River file from shapefile and TIN
// This function has not been tested rigously.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RiverFromTIN(QString RiverShpFileName, QString RiverDbfFileName, QString EleFileName, QString NodeFileName, QString NeighFileName, QString xRiverShpFileName, QString xRiverDbfFileName)
{

    if(print_debug_messages)
        qDebug() << "INFO: Start RiverFromTIN";

    try {

        QFile EleFile(EleFileName);
        if ( ! EleFile.open(QIODevice::ReadOnly | QIODevice::Text) )
        {
            main_window->Log_Message("[RiverFromTIN] Error[34] opening Element file.");
            return 34;
        }

        QTextStream EleFileTextStream(&EleFile);

        QFile NodeFile(NodeFileName);
        if ( ! NodeFile.open(QIODevice::ReadOnly | QIODevice::Text) )
        {
            main_window->Log_Message("[RiverFromTIN] Error[39] opening Node file.");
            return 39;
        }

        QTextStream NodeFileTextStream(&NodeFile);

        QFile NeighFile(NeighFileName);
        if ( ! NeighFile.open(QIODevice::ReadOnly | QIODevice::Text) )
        {
            main_window->Log_Message("[RiverFromTIN] Error[44] opening Neigh file.");
            return 44;
        }

        QTextStream NeighFileTextStream(&NeighFile);

        SHPHandle RiverShpHandle = SHPOpen(qPrintable(RiverShpFileName), "rb");
        if(RiverShpHandle == nullptr)
        {
            main_window->Log_Message("[RiverFromTIN] Error[51] RiverShpFileName is NULL.");
            return 51;
        }

        DBFHandle RiverDbfHandle = DBFOpen(qPrintable(RiverDbfFileName), "rb");
        if(RiverDbfHandle == nullptr)
        {
            SHPClose(RiverShpHandle);
            main_window->Log_Message("[RiverFromTIN] Error[51] RiverDbfHandle is NULL.");
            return 51;
        }

        SHPHandle xRiverShpHandle = SHPCreate(qPrintable(xRiverShpFileName), SHPT_ARC);
        if(xRiverShpHandle == nullptr)
        {
            SHPClose(RiverShpHandle);
            DBFClose(RiverDbfHandle);
            main_window->Log_Message("[RiverFromTIN] Error[57] xRiverShpHandle is NULL.");
            return 57;
        }

        DBFHandle xRiverDbfHandle = DBFCreate(qPrintable(xRiverDbfFileName));
        if(xRiverDbfHandle == nullptr)
        {
            SHPClose(RiverShpHandle);
            DBFClose(RiverDbfHandle);
            SHPClose(xRiverShpHandle);
            main_window->Log_Message("[RiverFromTIN] Error[57] xRiverDbfHandle is NULL.");
            return 57;
        }

        int LeftEle = DBFAddField(xRiverDbfHandle, "LeftEle",     FTInteger, 10, 0);
        if(LeftEle < 0)
        {
            SHPClose(RiverShpHandle);
            DBFClose(RiverDbfHandle);
            SHPClose(xRiverShpHandle);
            DBFClose(xRiverDbfHandle);
            main_window->Log_Message("[RiverFromTIN] Error[58] DBFAddField LeftEle.");
            return 58;
        }

        int RightEle = DBFAddField(xRiverDbfHandle, "RightEle",    FTInteger, 10, 0);
        if(RightEle < 0)
        {
            SHPClose(RiverShpHandle);
            DBFClose(RiverDbfHandle);
            SHPClose(xRiverShpHandle);
            DBFClose(xRiverDbfHandle);
            main_window->Log_Message("[RiverFromTIN] Error[59] DBFAddField RightEle.");
            return 59;
        }

        int FrmEleNode = DBFAddField(xRiverDbfHandle, "FrmEleNode",  FTInteger, 10, 0);
        if(FrmEleNode < 0)
        {
            SHPClose(RiverShpHandle);
            DBFClose(RiverDbfHandle);
            SHPClose(xRiverShpHandle);
            DBFClose(xRiverDbfHandle);
            main_window->Log_Message("[RiverFromTIN] Error[60] DBFAddField FrmEleNode.");
            return 60;
        }

        int ToEleNode = DBFAddField(xRiverDbfHandle, "ToEleNode",   FTInteger, 10, 0);
        if(ToEleNode < 0)
        {
            SHPClose(RiverShpHandle);
            DBFClose(RiverDbfHandle);
            SHPClose(xRiverShpHandle);
            DBFClose(xRiverDbfHandle);
            main_window->Log_Message("[RiverFromTIN] Error[61] DBFAddField ToEleNode.");
            return 61;
        }

        int TempInt = -1;
        int NumNode = -1;

        NodeFileTextStream >> NumNode;

        if(NumNode < 1)
        {
            SHPClose(RiverShpHandle);
            DBFClose(RiverDbfHandle);
            SHPClose(xRiverShpHandle);
            DBFClose(xRiverDbfHandle);
            main_window->Log_Message("[RiverFromTIN] Error[62] NumNode < 1.");
            return 62;
        }
        if(NumNode > 250000) //250000 is a guess
        {
            SHPClose(RiverShpHandle);
            DBFClose(RiverDbfHandle);
            SHPClose(xRiverShpHandle);
            DBFClose(xRiverDbfHandle);
            main_window->Log_Message("[RiverFromTIN] Error[62] NumNode > 250000.");
            return 62;
        }

        if(print_debug_messages)
            main_window->Log_Message("[RiverFromTIN] Start: Creating Point Array.");

        Point* node = new Point[NumNode+1];
        if(node == nullptr)
        {
            SHPClose(RiverShpHandle);
            DBFClose(RiverDbfHandle);
            SHPClose(xRiverShpHandle);
            DBFClose(xRiverDbfHandle);
            main_window->Log_Message("[RiverFromTIN] Error[63] node.");
            return 63;
        }

        NodeFileTextStream >> TempInt; NodeFileTextStream >> TempInt; NodeFileTextStream >> TempInt;

        for(int i = 1; i <= NumNode; i++)
        {
            NodeFileTextStream >> TempInt;
            NodeFileTextStream >> node[i].x;
            NodeFileTextStream >> node[i].y;
            NodeFileTextStream >> TempInt;
        }

        if(print_debug_messages)
            main_window->Log_Message("[RiverFromTIN] Finished: Creating Point Array.");

        int NumEle = -1;
        EleFileTextStream >> NumEle;
        if(NumEle < 1)
        {
            SHPClose(RiverShpHandle);
            DBFClose(RiverDbfHandle);
            SHPClose(xRiverShpHandle);
            DBFClose(xRiverDbfHandle);

            delete [] node;
            main_window->Log_Message("[RiverFromTIN] Error[64] Invalid NumEle < 1.");

            return 64;
        }
        if(NumEle > 250000) //250000 is a guess
        {
            SHPClose(RiverShpHandle);
            DBFClose(RiverDbfHandle);
            SHPClose(xRiverShpHandle);
            DBFClose(xRiverDbfHandle);

            delete [] node;
            main_window->Log_Message("[RiverFromTIN] Error[64] Invalid NumEle > 250000.");

            return 64;
        }

        if(print_debug_messages)
            main_window->Log_Message("[RiverFromTIN] Start: Creating Element Array.");


        int** element = new int*[NumEle+1];
        if(element == nullptr)
        {
            SHPClose(RiverShpHandle);
            DBFClose(RiverDbfHandle);
            SHPClose(xRiverShpHandle);
            DBFClose(xRiverDbfHandle);

            delete [] node;
            main_window->Log_Message("[RiverFromTIN] Error[65] element is NULL");

            return 65;
        }

        EleFileTextStream >> TempInt; EleFileTextStream >> TempInt;

        for(int i=1; i<=NumEle; i++)
        {
            element[i] = new int[3];

            EleFileTextStream >> TempInt;
            EleFileTextStream >> element[i][0];
            EleFileTextStream >> element[i][1];
            EleFileTextStream >> element[i][2];
        }

        if(print_debug_messages)
            main_window->Log_Message("[RiverFromTIN] Finished: Creating Element Array.");

        int NumNeigh = -1;
        NeighFileTextStream >> NumNeigh;
        if(NumNeigh < 1)
        {
            SHPClose(RiverShpHandle);
            DBFClose(RiverDbfHandle);
            SHPClose(xRiverShpHandle);
            DBFClose(xRiverDbfHandle);

            delete [] node;
            for(int i=1; i <= NumEle; i++)
            {
                delete [] element[i];
            }
            delete [] element;
            main_window->Log_Message("[RiverFromTIN] Error[66] Invalid NumNeigh < 1.");

            return 66;
        }

        if(NumNeigh > 250000) //250000 is a guess
        {
            SHPClose(RiverShpHandle);
            DBFClose(RiverDbfHandle);
            SHPClose(xRiverShpHandle);
            DBFClose(xRiverDbfHandle);

            delete [] node;
            for(int i=1; i <= NumEle; i++)
            {
                delete [] element[i];
            }
            delete [] element;
            main_window->Log_Message("[RiverFromTIN] Error[66] Invalid NumNeigh > 250000.");

            return 66;
        }

        if(print_debug_messages)
            main_window->Log_Message("[RiverFromTIN] Start: Creating Neighbour Array.");

        int** neighbour = new int*[NumNeigh+1];
        if(neighbour == nullptr)
        {
            SHPClose(RiverShpHandle);
            DBFClose(RiverDbfHandle);
            SHPClose(xRiverShpHandle);
            DBFClose(xRiverDbfHandle);

            delete [] node;
            for(int i=1; i <= NumEle; i++)
            {
                delete [] element[i];
            }
            delete [] element;
            main_window->Log_Message("[RiverFromTIN] Error[67] neighbour is NULL");

            return 67;
        }

        NeighFileTextStream >> TempInt;

        for(int i=1; i <= NumNeigh; i++)
        {
            neighbour[i] = new int[3];

            NeighFileTextStream >> TempInt;
            NeighFileTextStream >> neighbour[i][0];
            NeighFileTextStream >> neighbour[i][1];
            NeighFileTextStream >> neighbour[i][2];
        }

        if(print_debug_messages)
            main_window->Log_Message("[RiverFromTIN] Finished: Creating Neighbour Array.");


        if(print_debug_messages)
            main_window->Log_Message("[RiverFromTIN] Start: Creating nodeInEle Array.");


        int** nodeInEle      = new int*[NumNode+1]; //tells you : this (node present in which elements)
        int*  nodeInEleCount = new int[NumNode+1];
        if(nodeInEle == nullptr)
        {
            SHPClose(RiverShpHandle);
            DBFClose(RiverDbfHandle);
            SHPClose(xRiverShpHandle);
            DBFClose(xRiverDbfHandle);

            delete [] node;
            for(int i=1; i <= NumEle; i++)
            {
                delete [] element[i];
            }
            delete [] element;

            for(int i=1; i <= NumNeigh; i++)
            {
                delete [] neighbour[i];
            }
            delete [] neighbour;
            main_window->Log_Message("[RiverFromTIN] Error[68] nodeInEle is NULL");

            return 68;
        }
        if(nodeInEleCount == nullptr)
        {
            SHPClose(RiverShpHandle);
            DBFClose(RiverDbfHandle);
            SHPClose(xRiverShpHandle);
            DBFClose(xRiverDbfHandle);

            delete [] node;
            for(int i=1; i <= NumEle; i++)
            {
                delete [] element[i];
            }
            delete [] element;

            for(int i=1; i <= NumNeigh; i++)
            {
                delete [] neighbour[i];
            }
            delete [] neighbour;
            main_window->Log_Message("[RiverFromTIN] Error[69] nodeInEleCount is NULL");

            return 69;
        }

        for(int i=1; i<=NumNode; i++)
        {
            nodeInEle[i] = new int[20];
            nodeInEleCount[i] = 0;
        }

        for(int i=1; i<=NumEle; i++)
        {
            for(int j=0; j<3; j++)
            {
                nodeInEle[element[i][j]][nodeInEleCount[element[i][j]]++] = i;
            }
        }

        if(print_debug_messages)
            main_window->Log_Message("[RiverFromTIN] Finished: Creating nodeInEle Array.");

        if(print_debug_messages)
            main_window->Log_Message("[RiverFromTIN] Start: Creating neighNode Array.");

        int** neighNode     = new int*[NumNode+1]; //tells you which nodes are neighbours to i-th node
        int* neighNodeCount = new int[NumNode+1];
        if(neighNode == nullptr)
        {
            SHPClose(RiverShpHandle);
            DBFClose(RiverDbfHandle);
            SHPClose(xRiverShpHandle);
            DBFClose(xRiverDbfHandle);

            delete [] node;
            for(int i=1; i <= NumEle; i++)
            {
                delete [] element[i];
            }
            delete [] element;

            for(int i=1; i <= NumNeigh; i++)
            {
                delete [] neighbour[i];
            }
            delete [] neighbour;

            for(int i=1; i<=NumNode; i++)
            {
                delete [] nodeInEle[i];
            }
            delete [] nodeInEle;
            delete [] nodeInEleCount;
            main_window->Log_Message("[RiverFromTIN] Error[70] neighNode is NULL");

            return 70;
        }

        if(neighNodeCount == nullptr)
        {
            SHPClose(RiverShpHandle);
            DBFClose(RiverDbfHandle);
            SHPClose(xRiverShpHandle);
            DBFClose(xRiverDbfHandle);

            delete [] node;
            for(int i=1; i <= NumEle; i++)
            {
                delete [] element[i];
            }
            delete [] element;

            for(int i=1; i <= NumNeigh; i++)
            {
                delete [] neighbour[i];
            }
            delete [] neighbour;

            for(int i=1; i<=NumNode; i++)
            {
                delete [] nodeInEle[i];
            }
            delete [] nodeInEle;
            delete [] nodeInEleCount;
            main_window->Log_Message("[RiverFromTIN] Error[71] neighNodeCount is NULL");

            return 71;
        }

        for(int i=1; i<=NumNode; i++)
        {
            neighNode[i] = new int[100];
            neighNodeCount[i] = 0;
        }

        for(int i=1; i<=NumNode; i++)
        {
            for(int j=0; j<nodeInEleCount[i]; j++)
            {
                for(int k=0; k<3; k++)
                {
                    if( i != element[nodeInEle[i][j]][k] )
                        neighNode[i][neighNodeCount[i]++] = element[nodeInEle[i][j]][k];
                }
            }
        }

        if(print_debug_messages)
            main_window->Log_Message("[RiverFromTIN] Start: Finished neighNode Array.");

        if(print_debug_messages)
            main_window->Log_Message("[RiverFromTIN] Start: Creating Shapefile.");

        int FromTo[2];
        int LeftRight[2];
        bool error_found = false;

        int recordCount = DBFGetRecordCount(RiverDbfHandle);
        if( recordCount < 1)
        {
            error_found = true;
        }
        else {

            int record = 0;
            double X[2], Y[2], Z[2];
            Z[0] = 0.0; Z[1] = 0.0;
            Point pt1, pt2;
            int numPt;
            double oldDist, slope;

            for(int i=0; i < recordCount; i++)
            {
                SHPObject* shpObj = SHPReadObject(RiverShpHandle, i);
                if(shpObj != nullptr)
                {
                    pt1.x = shpObj->padfX[0];
                    pt1.y = shpObj->padfY[0];
                    pt2.x = shpObj->padfX[shpObj->nVertices-1];
                    pt2.y = shpObj->padfY[shpObj->nVertices-1];
                    slope = SLOPE(pt1, pt2);

                    Point pt;
                    int j = -100;

                    for(j=1; j <= NumNode; j++)
                    {
                        double test = distPt(pt1, node[j]);
                        // qDebug() << "j " << j << " " <<  test;

                        if( test < 0.001)
                            break;
                    }
                    if( j == -100)
                    {
                        error_found = true;
                    }

                    if(!error_found)
                    {
                        numPt = j;

                        if ( j > NumNode)
                        {
                            error_found = true;
                        }
                        if( numPt < 0 )
                        {
                            error_found = true;
                        }
                        else {

//                            if(print_many_messages)
//                            {
//                                qDebug() << "[RiverFromTIN] NumNode " << NumNode;
//                                qDebug() << "[RiverFromTIN] The J value used is " << j <<" (" <<pt1.x << "," << pt1.y <<") ";
//                                qDebug() << "[RiverFromTIN] node[j] " << j <<" (" <<node[j].x << "," << node[j].y <<") ";
//                            }
                        }

                        if(!error_found)
                        {
                            oldDist = distPt(node[numPt], pt2);

                            while(distPt(pt2, node[numPt]) > 0.001)
                            {
                                int j, k, l;
                                for(j=0; j < neighNodeCount[numPt]; j++)
                                {
//                                    if(print_many_messages)
//                                    {
//                                        qDebug() << "[RiverFromTIN] NumNode ";
//                                        qDebug() <<  "x= " << node[numPt].x << " y= " << node[numPt].y << "\n";
//                                        qDebug() <<  "x= " << node[neighNode[numPt][j]].x << " y= " << node[neighNode[numPt][j]].y << "\n";
//                                        qDebug() <<  "slope2= " << SLOPE(node[numPt], node[neighNode[numPt][j]]) << "\n";
//                                        qDebug() <<  "del slope= " << slope-SLOPE(node[numPt], node[neighNode[numPt][j]]) << "\n";
//                                        qDebug() <<  "=" << oldDist << "\n";
//                                        qDebug() <<  "=" << distPt(node[neighNode[numPt][j]], pt2) << "\n";
//                                    }

                                    if(fabs(slope-SLOPE(node[numPt], node[neighNode[numPt][j]])) < 0.001)
                                        break;
                                }

                                //if(print_debug_messages)
                                //    std::cout << numPt << " " << neighNode[numPt][j] << "\n";

                                X[0] = node[numPt].x;
                                Y[0] = node[numPt].y;
                                X[1] = node[neighNode[numPt][j]].x;
                                Y[1] = node[neighNode[numPt][j]].y;
                                FromTo[0]=numPt;
                                FromTo[1]=neighNode[numPt][j];
                                int m =0;
                                for(k=0; k<nodeInEleCount[numPt]; k++)
                                {
                                    for(l=0; l<nodeInEleCount[neighNode[numPt][j]]; l++)
                                    {
                                        if(nodeInEle[numPt][k] == nodeInEle[neighNode[numPt][j]][l])
                                            LeftRight[m++] = nodeInEle[numPt][k];
                                    }
                                }

                                SHPObject* newobj = SHPCreateSimpleObject(SHPT_ARC, 2, X, Y, Z);
                                if(newobj != nullptr)
                                {
                                    int check = SHPWriteObject(xRiverShpHandle, -1, newobj);
                                    if(check < 0)
                                        error_found = true;
                                    check = DBFWriteIntegerAttribute(xRiverDbfHandle, record, LeftEle,  LeftRight[0]);
                                    if(check < 0)
                                        error_found = true;
                                    check = DBFWriteIntegerAttribute(xRiverDbfHandle, record, RightEle, LeftRight[1]);
                                    if(check < 0)
                                        error_found = true;
                                    check = DBFWriteIntegerAttribute(xRiverDbfHandle, record, FrmEleNode, FromTo[0]);
                                    if(check < 0)
                                        error_found = true;
                                    check = DBFWriteIntegerAttribute(xRiverDbfHandle, record, ToEleNode,   FromTo[1]);
                                    if(check < 0)
                                        error_found = true;
                                }
                                else {
                                    error_found = true;
                                }
                                record++;

                                numPt = neighNode[numPt][j];
                                oldDist = distPt(node[numPt], pt2);

                            } //End of while(distPt(pt2, node[numPt]) > 0.001)
                        }
                    }
                }
                else
                {
                    error_found = true;
                }
            }

        }

        SHPClose(RiverShpHandle);
        DBFClose(RiverDbfHandle);
        SHPClose(xRiverShpHandle);
        DBFClose(xRiverDbfHandle);

        ///////////////////////////////////////////////////////////////
        // Clean up
        ///////////////////////////////////////////////////////////////

        delete [] node;

        for(int i=1; i <= NumEle; i++)
        {
            delete [] element[i];
        }
        delete [] element;

        for(int i=1; i <= NumNeigh; i++)
        {
            delete [] neighbour[i];
        }
        delete [] neighbour;

        for(int i=1; i<=NumNode; i++)
        {
            delete [] nodeInEle[i];
        }
        delete [] nodeInEle;
        delete [] nodeInEleCount;

        for(int i=1; i<=NumNode; i++)
        {
            delete [] neighNode[i];
        }
        delete [] neighNode;
        delete [] neighNodeCount;


        ///////////////////////////////////////////////////////////////
        if(error_found)
        {
            main_window->Log_Message("[RiverFromTIN] ERROR: Creating Shapefile.");
            return -9999;
        }
        else {
            main_window->Log_Message("[RiverFromTIN] Finished: Creating Shapefile.");
        }


    } catch (...) {
        qDebug() << "Error: RiverFromTIN is returning zero w/o checking";
        return -5000;
    }

    return 0;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper function to Add FID to River Shapefile (required)
// This function has not been tested rigously.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AddFID(QString RiverDbfFileName)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AddFID";

    try {

        DBFHandle RiverDbfHandle = DBFOpen(qPrintable(RiverDbfFileName), "rb");
        if ( RiverDbfHandle == nullptr )
        {
            main_window->Log_Message("[AddFID] Error[283] RiverDbfFileName is NULL. ");
            return 283;
        }

        int TempInt = -1;
        int fieldCount  = DBFGetFieldCount(RiverDbfHandle);
        int recordCount = DBFGetRecordCount(RiverDbfHandle);

        if ( fieldCount  <= 0 )
        {
            DBFClose(RiverDbfHandle);
            main_window->Log_Message("[AddFID] Error[284] Invalid field count <= 0. ");
            return 284;
        }
        if ( fieldCount  > 1000 ) //1000 is a guess
        {
            DBFClose(RiverDbfHandle);
            main_window->Log_Message("[AddFID] Error[284] Invalid field count > 1000. ");
            return 284;
        }

        if ( recordCount  <= 0 )
        {
            DBFClose(RiverDbfHandle);
            main_window->Log_Message("[AddFID] Error[285] Invalid record count <= 0. ");
            return 285;
        }
        if ( recordCount > 250000 ) //250000 is a guess
        {
            DBFClose(RiverDbfHandle);
            main_window->Log_Message("[AddFID] Error[285] Invalid record count > 250000. ");
            return 285;
        }

        QString TempDbfFileName = user_pihmgis_root_folder + user_pihmgis_project_folder + riv_temp_fname;

        DBFHandle TempDbfHandle = DBFCreate(qPrintable(TempDbfFileName));
        if ( TempDbfHandle == nullptr )
        {
            main_window->Log_Message("[AddFID] Error[293] TempDbfFileName is NULL. ");
            return 293;
        }

        int width[1], decimals[1];
        char fieldName[50]; //Increased from 20 to 50. May not be enough.
        DBFFieldType fieldType;

        int RivIDField = DBFAddField(TempDbfHandle, "RivID", FTInteger, 6, 0);
        if ( RivIDField  < 0 )
        {
            DBFClose(RiverDbfHandle);
            DBFClose(TempDbfHandle);
            main_window->Log_Message("[AddFID] Error[293] Unable to create RivID field. ");
            return 293;
        }

        bool error_found = false;
        for (int i=0; i<fieldCount; i++)
        {
            fieldType = DBFGetFieldInfo(RiverDbfHandle, i, fieldName, width, decimals);
            TempInt = DBFAddField(TempDbfHandle, fieldName, fieldType, width[0], decimals[0]);

            if(TempInt < 0)
            {
                error_found = true;
            }
        }

        if(error_found)
        {
            DBFClose(RiverDbfHandle);
            DBFClose(TempDbfHandle);
            main_window->Log_Message("[AddFID] Error[294] Issues with adding fields to " + RiverDbfFileName);
            return 294;
        }

        error_found = false;
        int iValue;
        double fValue;
        const char * cValue;
        for (int i=0; i<recordCount; i++)
        {
            for (int j=0; j<fieldCount; j++)
            {
                fieldType = DBFGetFieldInfo(RiverDbfHandle, j, fieldName, width, decimals);
                if(fieldType == FTString)
                {
                    cValue = DBFReadStringAttribute(RiverDbfHandle, i, j);
                    TempInt = DBFWriteStringAttribute(TempDbfHandle, i, j+1, cValue);
                    if(TempInt < 0)
                    {
                        error_found = true;
                    }
                }
                else if(fieldType == FTInteger)
                {
                    iValue = DBFReadIntegerAttribute(RiverDbfHandle, i, j);
                    TempInt = DBFWriteIntegerAttribute(TempDbfHandle, i, j+1, iValue);
                    if(TempInt < 0)
                    {
                        error_found = true;
                    }
                }
                else if(fieldType == FTDouble)
                {
                    fValue = DBFReadDoubleAttribute(RiverDbfHandle, i, j);
                    TempInt = DBFWriteDoubleAttribute(TempDbfHandle, i, j+1, fValue);
                    if(TempInt < 0)
                    {
                        error_found = true;
                    }
                }
            }
            TempInt = DBFWriteIntegerAttribute(TempDbfHandle, i, 0, i+1);
            if(TempInt < 0)
            {
                error_found = true;
            }
        }


        DBFClose(RiverDbfHandle);
        DBFClose(TempDbfHandle);

        bool check = QFile::remove(RiverDbfFileName);
        if(check)
        {
            main_window->Log_Message("[AddFID] Error Unable to remove " + RiverDbfFileName);
            return -9999;
        }

        check = QFile::copy(TempDbfFileName, RiverDbfFileName);
        if(check)
        {
            main_window->Log_Message("[AddFID] Error Unable to copy " + TempDbfFileName + " to " + RiverDbfFileName);
            return -9999;
        }

        check =QFile::remove(TempDbfFileName);
        if(check)
        {
            main_window->Log_Message("[AddFID] Error Unable to remove " + TempDbfFileName );
            return -9999;
        }

        ///////////////////////////////////////////////////////////////
        if(error_found)
        {
            main_window->Log_Message("[AddFID] ERROR: Creating Shapefile.");
            return -9999;
        }
        else {
            main_window->Log_Message("[AddFID] Finished: Creating Shapefile.");
        }

    } catch (...) {
        qDebug() << "Error: AddFID is returning w/o checking";
        return -5000;
    }

    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper function to Add From and To Fields in River Shapefile
// This function has not been tested rigously.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AddToFromNode( QString RiverShpFileName, QString RiverDbfFileName )
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AddToFromNode";

    try {

        SHPHandle RiverShpHandle = SHPOpen( qPrintable(RiverShpFileName), "rb");
        if(RiverShpHandle == nullptr)
        {
            main_window->Log_Message("[AddToFromNode] Error RiverShpFileName is NULL. Returning 365.");
            return 365;
        }

        DBFHandle RiverDbfHandle = DBFOpen( qPrintable(RiverDbfFileName), "rb");
        if(RiverDbfHandle == nullptr)
        {
            SHPClose(RiverShpHandle);
            main_window->Log_Message("[AddToFromNode] Error RiverDbfFileName is NULL. Returning 365.");
            return 365;
        }

        QString TempDbfFileName = user_pihmgis_root_folder + user_pihmgis_project_folder + riv_temp_fname;

        DBFHandle TempDbfHandle = DBFCreate( qPrintable(TempDbfFileName) );
        if ( TempDbfHandle == nullptr )
        {
            SHPClose(RiverShpHandle);
            DBFClose(RiverDbfHandle);
            main_window->Log_Message("[AddToFromNode] Error TempDbfFileName is NULL. Returning 372.");
            return 372;
        }

        int TempInt = -100;

        int fieldCount  = DBFGetFieldCount(RiverDbfHandle);
        if(fieldCount < 1)
        {
            SHPClose(RiverShpHandle);
            DBFClose(RiverDbfHandle);
            DBFClose(TempDbfHandle);
            main_window->Log_Message("[AddToFromNode] Error[373] fieldCount < 1. ");
            return 373;
        }

        if(fieldCount > 1000)
        {
            SHPClose(RiverShpHandle);
            DBFClose(RiverDbfHandle);
            DBFClose(TempDbfHandle);
            main_window->Log_Message("[AddToFromNode] Error[373] fieldCount > 1000. ");
            return 373;
        }

        int recordCount = DBFGetRecordCount(RiverDbfHandle);
        if(recordCount < 1)
        {
            SHPClose(RiverShpHandle);
            DBFClose(RiverDbfHandle);
            DBFClose(TempDbfHandle);
            main_window->Log_Message("[AddToFromNode] Error[374] recordCount < 1. ");
            return 374;
        }

        if(recordCount > 250000)
        {
            SHPClose(RiverShpHandle);
            DBFClose(RiverDbfHandle);
            DBFClose(TempDbfHandle);
            main_window->Log_Message("[AddToFromNode] Error[374] recordCount > 250000. ");
            return 374;
        }

        if(print_debug_messages)
        {
            main_window->Log_Message("[AddToFromNode] Copying Existing Records ...");
        }

        bool error_found = false;
        int width[1], decimals[1];
        char fieldName[50]; //Changed from 20 to 50
        DBFFieldType fieldType;

        for (int i=0; i < fieldCount; i++)
        {
            fieldType = DBFGetFieldInfo(RiverDbfHandle, i, fieldName, width, decimals);
            TempInt   = DBFAddField(TempDbfHandle, fieldName, fieldType, width[0], decimals[0]);
            if(TempInt < 0)
            {
                main_window->Log_Message("[AddToFromNode] Issue with value generated by Field type " + QString(fieldName));
                error_found = true;
            }
        }

        if(error_found)
        {
            SHPClose(RiverShpHandle);
            DBFClose(RiverDbfHandle);
            DBFClose(TempDbfHandle);
            main_window->Log_Message("[AddToFromNode] Error[375] Issues with adding fields to " + RiverDbfFileName);
            return 375;
        }

        int fromField = DBFAddField(TempDbfHandle, "FromNode", FTInteger, 6, 0);
        if ( fromField < 0 )
        {
            SHPClose(RiverShpHandle);
            DBFClose(RiverDbfHandle);
            DBFClose(TempDbfHandle);

            main_window->Log_Message("[AddToFromNode] Error[376] fromField < 0. " + RiverDbfFileName);
            return 376;
        }

        int toField   = DBFAddField(TempDbfHandle, "ToNode",   FTInteger, 6, 0);
        if ( toField < 0 )
        {
            SHPClose(RiverShpHandle);
            DBFClose(RiverDbfHandle);
            DBFClose(TempDbfHandle);

            main_window->Log_Message("[AddToFromNode] Error[377] Error toField < 0. " + RiverDbfFileName);
            return 377;
        }

        error_found = false;
        TempInt = -1;
        int iValue = -1;
        double fValue = -1;
        const char *cValue;
        for (int i=0; i < recordCount; i++)
        {
            for (int j=0; j < fieldCount; j++)
            {
                TempInt = -1;

                fieldType = DBFGetFieldInfo(RiverDbfHandle, j, fieldName, width, decimals);
                if(fieldType == FTString)
                {
                    cValue  = DBFReadStringAttribute(RiverDbfHandle, i, j);
                    TempInt = DBFWriteStringAttribute(TempDbfHandle, i, j, cValue);
                }
                else if(fieldType == FTInteger)
                {
                    iValue  = DBFReadIntegerAttribute(RiverDbfHandle, i, j);
                    TempInt = DBFWriteIntegerAttribute(TempDbfHandle, i, j, iValue);
                }
                else if(fieldType == FTDouble)
                {
                    fValue  = DBFReadDoubleAttribute(RiverDbfHandle, i, j);
                    TempInt = DBFWriteDoubleAttribute(TempDbfHandle, i, j, fValue);
                }
                else {
                    main_window->Log_Message("[AddToFromNode] Field type ignored (may not be bad) " + QString(fieldName));
                    TempInt = 1; //So warning below is not generated
                }

                if ( TempInt < 1 )
                {
                    main_window->Log_Message("[AddToFromNode] Issue with value generated by Field type " + QString(fieldName));
                    error_found = true;
                }
            }
        }

        if(error_found)
        {
            main_window->Log_Message("[AddToFromNode] WARNING Issues found parsing river shapefile. Check logs ...");
            //return 426; Are they serious errors???
        }

        if(print_debug_messages)
        {
            main_window->Log_Message("[AddToFromNode] Computing FromNode and ToNode ...");
        }

        Point *nodes = new Point[recordCount*2];
        if ( nodes == nullptr )
        {
            SHPClose(RiverShpHandle);
            DBFClose(RiverDbfHandle);
            DBFClose(TempDbfHandle);
            main_window->Log_Message("[AddToFromNode] nodes == nullptr. Returning 398.");
            return 398;
        }

        int ptCount = 0;
        TempInt = -1;
        error_found = false;

        for(int i=0; i<recordCount; i++)
        {
            SHPObject *obj = SHPReadObject(RiverShpHandle, i);
            if( obj != nullptr)
            {
                Point TempPoint;

                for (int k=0; k<2; k++)
                {
                    TempInt = -1; //For error debugging
                    TempPoint.x = obj->padfX[k];
                    TempPoint.y = obj->padfY[k];
                    int j = ptCount-1;

                    while( IsEqualPoint(TempPoint, nodes[j]) != 1 && j >= 0 )
                        j--;

                    if(j == -1)
                    {
                        nodes[ptCount].x=obj->padfX[k];
                        nodes[ptCount].y=obj->padfY[k];
                        ptCount++;

                        if(k == 0)
                            TempInt = DBFWriteIntegerAttribute(TempDbfHandle,i,fromField,ptCount);
                        else
                            TempInt = DBFWriteIntegerAttribute(TempDbfHandle,i,toField,ptCount);
                    }
                    else
                    {
                        if(k == 0)
                            TempInt = DBFWriteIntegerAttribute(TempDbfHandle,i,fromField,j+1);
                        else
                            TempInt = DBFWriteIntegerAttribute(TempDbfHandle,i,toField,j+1);
                    }

                    if ( TempInt < 1 )
                    {
                        error_found = true;
                        main_window->Log_Message("[AddToFromNode] WARNING with writing from and to fields at " + QString::number(i) );
                    }
                }
            }
        }

        if(error_found)
        {
            main_window->Log_Message("[AddToFromNode] WARNING Issues found writing river shapefile. Check logs ...");
            //return 426; Are they serious errors???
        }

        SHPClose(RiverShpHandle);
        DBFClose(RiverDbfHandle);
        DBFClose(TempDbfHandle);

        if(print_debug_messages)
        {
            main_window->Log_Message("[AddToFromNode] Finalizing DBF File ..");
        }

        //Clean up memory
        delete [] nodes;


        bool check = QFile::remove(RiverDbfFileName);
        if(check)
        {
            main_window->Log_Message("[AddToFromNode] Error Unable to remove " + RiverDbfFileName);
            return -9999;
        }

        check = QFile::copy(TempDbfFileName, RiverDbfFileName);
        if(check)
        {
            main_window->Log_Message("[AddToFromNode] Error Unable to copy " + TempDbfFileName + " to " + RiverDbfFileName);
            return -9999;
        }

        check =QFile::remove(TempDbfFileName);
        if(check)
        {
            main_window->Log_Message("[AddToFromNode] Error Unable to remove " + TempDbfFileName );
            return -9999;
        }


        if(error_found)
        {
            return -9999;
        }


    } catch (...) {
        qDebug() << "Error: AddToFromNode is returning w/o checking";
        return -5000;
    }

    return 0;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper function to Add Strahler Stream Order in River Shapefile
// This function has not been tested rigously.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AddStrahlerStreamOrder( QString RiverShpFileName, QString RiverDbfFileName )
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AddStrahlerStreamOrder";

    try {

        SHPHandle RiverShpHandle = SHPOpen(qPrintable(RiverShpFileName), "rb");
        if(RiverShpHandle == nullptr)
        {
            main_window->Log_Message("[AddStrahlerStreamOrder] Error RiverShpHandle is NULL. Returning 521.");
            return 521;
        }

        DBFHandle RiverDbfHandle = DBFOpen(qPrintable(RiverDbfFileName), "rb");
        if(RiverDbfHandle == nullptr)
        {
            main_window->Log_Message("[AddStrahlerStreamOrder] Error RiverDbfFileName is NULL. Returning 521.");
            return 521;
        }

        if(print_debug_messages)
        {
            main_window->Log_Message("[AddStrahlerStreamOrder] Checking Required Fields ...");
        }

        int fromField = DBFGetFieldIndex(RiverDbfHandle, "FromNode");
        if (fromField == -1)
        {
            main_window->Log_Message("[AddStrahlerStreamOrder] Error[513]: FromNode field does *NOT* exist");
            return 513;
        }

        int toField = DBFGetFieldIndex(RiverDbfHandle, "ToNode");
        if (toField == -1)
        {
            main_window->Log_Message("[AddStrahlerStreamOrder] Error[520]: ToNode field does *NOT* exist");
            return 520;
        }

        QString TempDbfFileName = user_pihmgis_root_folder + user_pihmgis_project_folder + riv_temp_fname;

        DBFHandle TempDbfHandle = DBFCreate( qPrintable(TempDbfFileName) );
        if(TempDbfHandle == nullptr)
        {
            main_window->Log_Message("[AddStrahlerStreamOrder] Error[521] TempDbfHandle is NULL.");
            return 521;
        }

        int TempInt = -1;
        int fieldCount  = DBFGetFieldCount(RiverDbfHandle);
        int recordCount = DBFGetRecordCount(RiverDbfHandle);

        if(print_debug_messages)
        {
            main_window->Log_Message("[AddStrahlerStreamOrder] Copying Existing Records ...");
        }

        bool error_found = false;
        int width[1], decimals[1];
        char fieldName[50]; //from 20 to 50
        DBFFieldType fieldType;

        for (int i=0; i < fieldCount; i++)
        {
            fieldType = DBFGetFieldInfo(RiverDbfHandle, i, fieldName, width, decimals);
            TempInt   = DBFAddField(TempDbfHandle, fieldName, fieldType, width[0], decimals[0]);

            if ( TempInt < 1 )
            {
                main_window->Log_Message("[AddStrahlerStreamOrder] Issue with value generated by Field type " + QString(fieldName));
                error_found = true;
            }
        }

        if(error_found)
        {
            main_window->Log_Message("[AddStrahlerStreamOrder] Error[522] Errors found creating dbf fields in " + TempDbfFileName);
            return 522;
        }

        int StrahlerStreamOrder = DBFAddField(TempDbfHandle, "StrOrder", FTInteger, 6, 0);
        if ( StrahlerStreamOrder < 1 )
        {
            main_window->Log_Message("[AddStrahlerStreamOrder] Issue with adding StrOrderField in " + QString(fieldName));
            return 523;
        }


        error_found = false;
        int iValue;
        double fValue;
        const char * cValue;
        for (int i=0; i < recordCount; i++)
        {
            for (int j=0; j<fieldCount; j++)
            {
                TempInt = -1;
                fieldType = DBFGetFieldInfo(RiverDbfHandle, j, fieldName, width, decimals);
                if(fieldType == FTString)
                {
                    cValue = DBFReadStringAttribute(RiverDbfHandle, i, j);
                    TempInt = DBFWriteStringAttribute(TempDbfHandle, i, j, cValue);
                }
                else if(fieldType == FTInteger)
                {
                    iValue = DBFReadIntegerAttribute(RiverDbfHandle, i, j);
                    TempInt = DBFWriteIntegerAttribute(TempDbfHandle, i, j, iValue);
                }
                else if(fieldType == FTDouble)
                {
                    fValue = DBFReadDoubleAttribute(RiverDbfHandle, i, j);
                    TempInt = DBFWriteDoubleAttribute(TempDbfHandle, i, j, fValue);
                }

                if ( TempInt < 1 )
                {
                    main_window->Log_Message("[AddStrahlerStreamOrder] Issue with value generated by Field type " + QString(fieldName));
                    error_found = true;
                }
            }
        }

        if(error_found)
        {
            main_window->Log_Message("[AddStrahlerStreamOrder] WARNING Issues found writing StrahlerStreamOrder shapefile. Check logs ...");
            //return 524; Are they serious errors???
        }

        if(print_debug_messages)
        {
            main_window->Log_Message("[AddStrahlerStreamOrder] Computing Strahler Stream Order ...");
        }

        int (*toArray)[5] = new int[2*recordCount][5];
        int *count = new int [2*recordCount];

        for (int i=0; i<2*recordCount; i++)
            count[i]=0;

        for(int i=0; i < recordCount; i++)
        {
            TempInt = DBFReadIntegerAttribute(RiverDbfHandle, i, toField);

            if ( TempInt < 0 )
            {
                main_window->Log_Message("[AddStrahlerStreamOrder] Invalid Index with ToField ");
                error_found = true;
            }
            else
            {
                if( DBFReadIntegerAttribute(RiverDbfHandle,toArray[TempInt][count[TempInt]-1],fromField) != DBFReadIntegerAttribute(RiverDbfHandle,i,fromField))
                    toArray[TempInt][count[TempInt]++]=i;
            }
        }

        if(error_found)
        {
            main_window->Log_Message("[AddStrahlerStreamOrder] WARNING Strahler Stream Order issues with ToField check logs...");
        }
        error_found = false;

        for(int i=recordCount-1; i>=0; i--)
        {
            TempInt = DBFReadIntegerAttribute(RiverDbfHandle, i, toField);

            if ( TempInt < 0 )
            {
                main_window->Log_Message("[AddStrahlerStreamOrder] Invalid Index with ToField ");
                error_found = true;
            }
            else
            {
                if( DBFReadIntegerAttribute(RiverDbfHandle,toArray[TempInt][count[TempInt]-1],fromField) != DBFReadIntegerAttribute(RiverDbfHandle,i,fromField))
                    toArray[TempInt][count[TempInt]++]=i;
            }
        }

        if(error_found)
        {
            main_window->Log_Message("[AddStrahlerStreamOrder] WARNING Strahler Stream Order issues with ToField check logs...");
        }

        error_found = false;
        int UPDATE = 1;
        int loopCount = 0;
        int max1, max2, from, to, so;

        while(UPDATE == 1)
        {
            UPDATE = 0;
            loopCount++;

            for(int i=0; i<recordCount; i++)
            {
                int TempInt = DBFReadIntegerAttribute(TempDbfHandle, i, fromField);

                if(TempInt >= 0)
                {
                    if(count[TempInt] == 0)
                    {
                        int dwrite = DBFWriteIntegerAttribute(TempDbfHandle, i, StrahlerStreamOrder, 1);
                        if(dwrite < 0)
                            error_found = true;
                    }
                    else if(count[TempInt] == 1)
                    {
                        TempInt = DBFReadIntegerAttribute(TempDbfHandle, i, fromField);
                        if(TempInt >= 0)
                        {
                            TempInt = toArray[TempInt][0];

                            if(DBFReadIntegerAttribute(TempDbfHandle, TempInt, StrahlerStreamOrder) != DBFReadIntegerAttribute(TempDbfHandle, i, StrahlerStreamOrder))
                                UPDATE = 1;

                            int dwrite = DBFWriteIntegerAttribute(TempDbfHandle, i, StrahlerStreamOrder, DBFReadIntegerAttribute(TempDbfHandle, TempInt, StrahlerStreamOrder));
                            if(dwrite < 0)
                                error_found = true;
                        }
                        else
                        {
                            error_found = true;
                        }
                    }
                    else
                    {
                        from = DBFReadIntegerAttribute(TempDbfHandle, i, fromField);

                        if( from >= 0)
                        {
                            max1=0; max2=0;

                            for(int j=0; j<count[TempInt]; j++)
                            {
                                to = toArray[from][j]; //cout<<"  to = "<<to<<"\t";
                                so = DBFReadIntegerAttribute(TempDbfHandle, to, StrahlerStreamOrder);// cout<<"  so = "<<so<<"\n";
                                if(so >= max1)
                                {
                                    max2=max1;
                                    max1=so;
                                }
                            }
                            if(max1 == max2)
                            {
                                if(DBFReadIntegerAttribute(TempDbfHandle, i, StrahlerStreamOrder) != max1+1)
                                    UPDATE = 1;

                                int dwrite = DBFWriteIntegerAttribute(TempDbfHandle, i, StrahlerStreamOrder, max1+1);
                                if(dwrite < 0)
                                    error_found = true;
                            }
                            else
                            {
                                if(DBFReadIntegerAttribute(TempDbfHandle, i, StrahlerStreamOrder) != max1)
                                    UPDATE = 1;

                                int dwrite = DBFWriteIntegerAttribute(TempDbfHandle, i, StrahlerStreamOrder, max1);
                                if(dwrite < 0)
                                    error_found = true;
                            }
                        }
                        else
                        {
                            error_found = true;
                        }
                    }

                }
                else {
                    error_found = true;
                }
            }
        }

        SHPClose(RiverShpHandle);
        DBFClose(RiverDbfHandle);
        DBFClose(TempDbfHandle);

        //Clean up memory
        delete [] count;
        delete [] toArray;

        if(error_found)
        {
            main_window->Log_Message("[AddStrahlerStreamOrder] WARNING Issues found when creating Strahler Stream Order shapefile. Check logs...");
        }

        bool check = QFile::remove(RiverDbfFileName);
        if(check)
        {
            main_window->Log_Message("[AddStrahlerStreamOrder] Error Unable to remove " + RiverDbfFileName);
            return -9999;
        }

        check = QFile::copy(TempDbfFileName, RiverDbfFileName);
        if(check)
        {
            main_window->Log_Message("[AddStrahlerStreamOrder] Error Unable to copy " + TempDbfFileName + " to " + RiverDbfFileName);
            return -9999;
        }

        check =QFile::remove(TempDbfFileName);
        if(check)
        {
            main_window->Log_Message("[AddStrahlerStreamOrder] Error Unable to remove " + TempDbfFileName );
            return -9999;
        }

    } catch (...) {
        qDebug() << "Error: AddStrahlerStreamOrder is returning w/o checking";
        return -5000;
    }

    return 0;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper function to Add Down Segments in River Shapefile
// This function has not been tested rigously.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AddDownSegment(QString RiverDbfFileName, QString BoundaryCondition)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start AddDownSegment";

    try {

        int TempInt;

        DBFHandle RiverDbfHandle = DBFOpen(qPrintable(RiverDbfFileName), "rb");
        if ( RiverDbfHandle == nullptr )
        {
            main_window->Log_Message("[AddDownSegment] Error[692] RiverDbfFileName is NULL.");
            return 692;
        }

        int RivID = DBFGetFieldIndex(RiverDbfHandle, "RivID");
        if( RivID < 0)
        {
            main_window->Log_Message("[AddDownSegment] Error[695] RivID field does *NOT* exist.");
            return 695;
        }

        int FROM_NODE = DBFGetFieldIndex(RiverDbfHandle, "FromNode");
        if( FROM_NODE < 0)
        {
            main_window->Log_Message("[AddDownSegment] Error[704] RivID FromNode does *NOT* exist.");
            return 704;
        }

        int TO_NODE = DBFGetFieldIndex(RiverDbfHandle, "ToNode");
        if( TO_NODE == -1)
        {
            main_window->Log_Message("[AddDownSegment] Error[711] RivID ToNode does *NOT* exist.");
            return 711;
        }


        QString TempDbfFileName = user_pihmgis_root_folder + user_pihmgis_project_folder + riv_temp_fname;

        DBFHandle TempDbfHandle = DBFCreate( qPrintable(TempDbfFileName) );
        if ( TempDbfHandle == nullptr )
        {
            main_window->Log_Message("[AddDownSegment] Error[723] TempDbfHandle is NULL. " + TempDbfFileName);
            return 723;
        }

        int fieldCount  = DBFGetFieldCount(RiverDbfHandle);
        if ( fieldCount <= 0 )
        {
            main_window->Log_Message("[AddDownSegment] Error[724] Invalid field count <= 0. " + RiverDbfFileName);
            return 724;
        }

        if ( fieldCount > 1000 )
        {
            main_window->Log_Message("[AddDownSegment] Error[724] Invalid field count > 1000. " + RiverDbfFileName);
            return 724;
        }

        int recordCount = DBFGetRecordCount(RiverDbfHandle);
        if ( recordCount <= 0 )
        {
            main_window->Log_Message("[AddDownSegment] Error[725] Invalid record count.  <= 0" + RiverDbfFileName);
            return 725;
        }

        if ( recordCount > 250000 ) //250000 is a guess
        {
            main_window->Log_Message("[AddDownSegment] Error[725] Invalid record count > 250000. " + RiverDbfFileName);
            return 725;
        }

        if(print_debug_messages)
        {
            main_window->Log_Message("[AddDownSegment] Copying Existing Records ...");
        }

        bool error_found = false;
        int width[1], decimals[1];
        char fieldName[50]; //Changed from 20 to 50
        DBFFieldType fieldType;

        for (int i=0; i < fieldCount; i++)
        {
            fieldType = DBFGetFieldInfo(RiverDbfHandle, i, fieldName, width, decimals);
            TempInt   = DBFAddField(TempDbfHandle, fieldName, fieldType, width[0], decimals[0]);

            if ( TempInt < 0 )
            {
                error_found = true;
                main_window->Log_Message("[AddDownSegment] Issue with value generated by Field type " + QString(fieldName));

            }
        }

        if ( error_found )
        {
            main_window->Log_Message("[AddDownSegment] Error[726] Issues with adding fields to " + TempDbfFileName);
            return 726;
        }

        int DownSegmt = DBFAddField(TempDbfHandle, "DownSegmt", FTInteger, 6, 0);

        if ( DownSegmt < 0 )
        {
            main_window->Log_Message("[AddDownSegment] Error[726] Issues with adding DownSegmt to " + TempDbfFileName);
            return 744;
        }

        int iValue;
        double fValue;
        const char * cValue;
        for (int i=0; i<recordCount; i++)
        {
            for (int j=0; j<fieldCount; j++)
            {
                TempInt = -1;
                fieldType = DBFGetFieldInfo(RiverDbfHandle, j, fieldName, width, decimals);
                if(fieldType == FTString)
                {
                    cValue = DBFReadStringAttribute(RiverDbfHandle, i, j);
                    TempInt = DBFWriteStringAttribute(TempDbfHandle, i, j, cValue);
                }
                else if(fieldType == FTInteger)
                {
                    iValue = DBFReadIntegerAttribute(RiverDbfHandle, i, j);
                    TempInt = DBFWriteIntegerAttribute(TempDbfHandle, i, j, iValue);
                }
                else if(fieldType == FTDouble)
                {
                    fValue = DBFReadDoubleAttribute(RiverDbfHandle, i, j);
                    TempInt = DBFWriteDoubleAttribute(TempDbfHandle, i, j, fValue);
                }
                else {
                    main_window->Log_Message("[AddDownSegment] WARNING Ignoring field " + QString(fieldName));
                    TempInt = 1; //So warning below is not generated
                }

                if ( TempInt < 1 )
                {
                    main_window->Log_Message("[AddDownSegment] Issue with value generated by Field type " + QString(fieldName));
                    error_found = true;
                }
            }
        }

        if(error_found)
        {
            main_window->Log_Message("[AddDownSegment] WARNING Issues found parsing shapefile. Check logs ...");
            //return 745; Are they serious errors???
        }

        if(print_debug_messages)
        {
            main_window->Log_Message("[AddDownSegment] Computing Down Segments Records ...");
        }

        error_found = false;
        int j = 0;
        for(int i=0; i < recordCount; i++)
        {
            TempInt = -1;
            j=0;
            while((DBFReadIntegerAttribute(RiverDbfHandle,i,TO_NODE) != DBFReadIntegerAttribute(RiverDbfHandle,j,FROM_NODE) && j<recordCount))
            {
                j++;
            }

            if( j < recordCount)
            {
                TempInt = DBFWriteIntegerAttribute(TempDbfHandle, i, fieldCount, DBFReadIntegerAttribute(RiverDbfHandle, j, RivID));
            }
            else
            {
                int BC = BoundaryCondition.toInt();
                TempInt = DBFWriteIntegerAttribute(TempDbfHandle, i, fieldCount, BC);
            }

            if ( TempInt < 0 )
            {
                main_window->Log_Message("[AddDownSegment] Invalid Index with ToField ");
                error_found = true;
            }
        }


        DBFClose(RiverDbfHandle);
        DBFClose(TempDbfHandle);

        if(error_found)
        {
            main_window->Log_Message("[AddDownSegment] WARNING Issues found Computing Down Segments. Check logs...");
        }

        if(print_debug_messages)
        {
            main_window->Log_Message("[AddDownSegment] Finalizing DBF File ...");
        }

        bool check = QFile::remove(RiverDbfFileName);
        if(check)
        {
            main_window->Log_Message("[AddFID] Error Unable to remove " + RiverDbfFileName);
            return -9999;
        }

        check = QFile::copy(TempDbfFileName, RiverDbfFileName);
        if(check)
        {
            main_window->Log_Message("[AddFID] Error Unable to copy " + TempDbfFileName + " to " + RiverDbfFileName);
            return -9999;
        }

        check =QFile::remove(TempDbfFileName);
        if(check)
        {
            main_window->Log_Message("[AddFID] Error Unable to remove " + TempDbfFileName );
            return -9999;
        }


    } catch (...) {
        qDebug() << "Error: AddDownSegment is returning w/o checking";
        return -5000;
    }

    return 0;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper function to create River Shapefile
// This function has not been tested rigously.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Riv_File( QString RiverDbfFileName, QString RivDataFileName )
{
    if(print_debug_messages)
        qDebug() << "INFO: Start Riv_File";

    try {

        if(RiverDbfFileName.length() < 1)
        {
            main_window->Log_Message("[Riv_File] Invalid RiverDbfFileName " + RiverDbfFileName);
            return 800;
        }

        if(RivDataFileName.length() < 1)
        {
            main_window->Log_Message("[Riv_File] Invalid RiverDbfFileName " + RivDataFileName);
            return 801;
        }

        DBFHandle RiverDbfHandle = DBFOpen(qPrintable(RiverDbfFileName), "rb");

        if ( RiverDbfHandle == NULL )
        {
            main_window->Log_Message("[Riv_File] Error[827] RiverDbfFileName is NULL.");
            return 827;
        }

        if(print_debug_messages)
        {
            main_window->Log_Message("[Riv_File] Checking Requirent Fields ...");
        }

        int RivID = DBFGetFieldIndex(RiverDbfHandle, "RivID");
        if( RivID < 0 )
        {
            main_window->Log_Message("[Riv_File] Error[835]: RivID field does *NOT* exist ...");
            return 835;
        }

        int LeftEle = DBFGetFieldIndex(RiverDbfHandle, "LeftEle");
        if( LeftEle < 0 )
        {
            main_window->Log_Message("[Riv_File] Error[842]: LeftEle field does *NOT* exist ...");
            return 842;
        }

        int RightEle = DBFGetFieldIndex(RiverDbfHandle, "RightEle");
        if( RightEle == -1)
        {
            main_window->Log_Message("[Riv_File] Error[849]: RightEle field does *NOT* exist ...");
            return 849;
        }

        int FrmEleNode = DBFGetFieldIndex(RiverDbfHandle, "FrmEleNode");
        if( FrmEleNode == -1)
        {
            main_window->Log_Message("[Riv_File] Error[856]: FrmEleNode field does *NOT* exist ...");
            return 856;
        }

        int ToEleNode = DBFGetFieldIndex(RiverDbfHandle, "ToEleNode");
        if( ToEleNode == -1)
        {
            main_window->Log_Message("[Riv_File] Error[863]: ToEleNode field does *NOT* exist ...");
            return 863;
        }

        int DownSegmt = DBFGetFieldIndex(RiverDbfHandle, "DownSegmt");
        if( DownSegmt == -1)
        {
            main_window->Log_Message("[Riv_File] Error[870]: DownSegmt field does *NOT* exist ...");
            return 870;
        }

        int StrOrder = DBFGetFieldIndex(RiverDbfHandle, "StrOrder");
        if( StrOrder == -1)
        {
            main_window->Log_Message("[Riv_File] Error[877]: StrOrder field does *NOT* exist ...");
            return 877;
        }

        QFile RivDataFile(RivDataFileName);
        if ( ! RivDataFile.open(QIODevice::WriteOnly | QIODevice::Text) )
        {
            main_window->Log_Message("[Riv_File] Error[882]: Unable to open riv data file " + RivDataFileName);
            return 882;
        }

        QTextStream RivDataFileTextStream(&RivDataFile);

        int NumRivSeg = DBFGetRecordCount( RiverDbfHandle );
        RivDataFileTextStream << NumRivSeg << "\n";

        if( NumRivSeg <= 0)
        {
            RivDataFile.close();
            main_window->Log_Message("[Riv_File] Error[883]: Invalid Number of River Segments <= 0 " + QString::number(NumRivSeg));
            return 883;
        }

        if( NumRivSeg > 250000) //250000 is a guess
        {
            RivDataFile.close();
            main_window->Log_Message("[Riv_File] Error[883]: Invalid Number of River Segments > 250000" + QString::number(NumRivSeg));
            return 883;
        }

        int Order = -9999;
        int maxOrder = -1;

        for (int c=0; c < NumRivSeg; c++)
        {
            RivDataFileTextStream << DBFReadIntegerAttribute(RiverDbfHandle, c, RivID)      <<"\t";
            RivDataFileTextStream << DBFReadIntegerAttribute(RiverDbfHandle, c, FrmEleNode) <<"\t";
            RivDataFileTextStream << DBFReadIntegerAttribute(RiverDbfHandle, c, ToEleNode)  <<"\t";
            RivDataFileTextStream << DBFReadIntegerAttribute(RiverDbfHandle, c, DownSegmt)  <<"\t";
            RivDataFileTextStream << DBFReadIntegerAttribute(RiverDbfHandle, c, LeftEle)    <<"\t";
            RivDataFileTextStream << DBFReadIntegerAttribute(RiverDbfHandle, c, RightEle)   <<"\t";
            Order = DBFReadIntegerAttribute(RiverDbfHandle, c, StrOrder);
            RivDataFileTextStream << Order <<"\t"; //Shape
            RivDataFileTextStream << Order <<"\t"; //Material
            RivDataFileTextStream << Order <<"\t"; //IC
            RivDataFileTextStream << "0"   <<"\t"; //BC
            RivDataFileTextStream << "0"   <<"\n"; //Res

            if(maxOrder < Order)
                maxOrder = Order;
        }

        RivDataFileTextStream << "Shape\t" << maxOrder << "\n";
        for(int c=1; c<=maxOrder; c++)
        {
            RivDataFileTextStream << c << "\t" << //index
                                     0.5*c << "\t" << //depth
                                     "1"   << "\t" << //interpOrder
                                     2.0*c << "\n"; //width
        }

        RivDataFileTextStream << "Material\t" << maxOrder << "\n";
        for(int c=1; c<=maxOrder; c++)
        {
            RivDataFileTextStream<< c << "\t" <<    //index
                                    "4.63E-07" << "\t" <<               //n
                                    "0.6"      << "\t" <<               //cwr
                                    "0.1"      << "\t" <<               //Kh
                                    "1.0"      << "\t" <<               //Kv
                                    "1"        << "\n";                 //BedDepth
        }

        RivDataFileTextStream << "IC\t" << maxOrder << "\n";
        for(int c=1; c<=maxOrder; c++)
        {
            RivDataFileTextStream << c << "\t" <<   //index
                                     0.25*c << "\n";                     //rivIC
        }

        RivDataFileTextStream<<"BC\t"      <<"0"     <<"\n";
        RivDataFileTextStream<<"RES\t"     <<"0"     <<"\n";

        RivDataFile.close();

    } catch (...) {
        qDebug() << "Error: Riv_File is returning w/o checking";
        return -5000;
    }

    return 0;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Import function to create River Shapefile
// This function has not been tested rigously.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int riv_data_file( QString EleFileName, QString NodeFileName, QString NeighFileName,
                   QString RiverShpFileName, QString RiverDbfFileName,
                   QString xRiverShpFileName, QString xRiverDbfFileName,
                   QString BoundaryCondition,
                   QString RivDataFileName
                   )
{

    if(print_debug_messages)
        qDebug() << "INFO: Start riv_data_file";

    try {

        QString TempDbfFileName = user_pihmgis_root_folder + user_pihmgis_project_folder + riv_temp_fname;
        if(QFile::exists(TempDbfFileName))
        {
            main_window->Log_Message("[riv_data_file] WARNING/ERROR Temp file already exists " + TempDbfFileName);

            //If the file exists, could mean a few problems. Hence, user must decide on how to proceed outside PIHMgis.
            //For example, does the user have multiple PIHMgis sessions running?
            //Did a previous execution failed?
            return -9000;
        }

        //Check input names
        if(RiverShpFileName.length() < 1)
        {
            main_window->Log_Message("[riv_data_file] Invalid RiverShpFileName " + RiverShpFileName);
            return -9001;
        }
        if(RiverDbfFileName.length() < 1)
        {
            main_window->Log_Message("[riv_data_file] Invalid RiverDbfFileName " + RiverDbfFileName);
            return -9002;
        }
        if(EleFileName.length() < 1)
        {
            main_window->Log_Message("[riv_data_file] Invalid EleFileName " + EleFileName);
            return -9003;
        }
        if(NodeFileName.length() < 1)
        {
            main_window->Log_Message("[riv_data_file] Invalid NodeFileName " + NodeFileName);
            return -9004;
        }
        if(NeighFileName.length() < 1)
        {
            main_window->Log_Message("[riv_data_file] Invalid NeighFileName " + NeighFileName);
            return -9005;
        }
        if(xRiverShpFileName.length() < 1)
        {
            main_window->Log_Message("[riv_data_file] Invalid xRiverShpFileName " + xRiverShpFileName);
            return -9006;
        }
        if(xRiverDbfFileName.length() < 1)
        {
            main_window->Log_Message("[riv_data_file] Invalid xRiverDbfFileName " + xRiverDbfFileName);
            return -9007;
        }

        if(print_debug_messages)
        {
            main_window->Log_Message("[riv_data_file] Extracting River Data From TINs ... ");
        }

        int ReturnFlag = RiverFromTIN(
                    RiverShpFileName,
                    RiverDbfFileName,
                    EleFileName,
                    NodeFileName,
                    NeighFileName,
                    xRiverShpFileName,
                    xRiverDbfFileName);


        if ( ReturnFlag != 0 )
        {
            main_window->Log_Message("[riv_data_file] RiverFromTIN Failed with error code " + QString::number(ReturnFlag));
            return ReturnFlag;
        }
        else
        {
            main_window->Log_Message("[riv_data_file] Extracting River Data From TINs ... Complete ");
        }

        /////////////////////////////////////////////////////////////////////////////////
        // ** River IDs
        if(print_debug_messages)
        {
            main_window->Log_Message("[riv_data_file] Adding River IDs ... ");
        }

        ReturnFlag = AddFID( xRiverDbfFileName );

        if ( ReturnFlag != 0 )
        {
            main_window->Log_Message("[riv_data_file] AddFID Failed with error code " + QString::number(ReturnFlag));
            return ReturnFlag;
        }
        else
        {
            main_window->Log_Message("[riv_data_file] Adding River IDs ... Complete");
        }

        /////////////////////////////////////////////////////////////////////////////////
        // ** River FromNode and ToNode
        if(print_debug_messages)
        {
            main_window->Log_Message("[riv_data_file] Processing River FromNode & ToNodes ... ");
        }

        ReturnFlag = AddToFromNode( xRiverShpFileName, xRiverDbfFileName );

        if ( ReturnFlag != 0 )
        {
            main_window->Log_Message("[riv_data_file] AddToFromNode Failed with error code " + QString::number(ReturnFlag));
            return ReturnFlag;
        }
        else
        {
            main_window->Log_Message("[riv_data_file] Processing River FromNode & ToNodes ... Complete");
        }

        /////////////////////////////////////////////////////////////////////////////////
        // ** Strahler Stream Order
        if(print_debug_messages)
        {
            main_window->Log_Message("[riv_data_file] Processing Strahler Stream Order ... ");
        }

        ReturnFlag = AddStrahlerStreamOrder( xRiverShpFileName, xRiverDbfFileName );

        if ( ReturnFlag != 0 )
        {
            main_window->Log_Message("[riv_data_file] AddStrahlerStreamOrder Failed with error code " + QString::number(ReturnFlag));
            return ReturnFlag;
        }
        else
        {
            main_window->Log_Message("[riv_data_file] Processing Strahler Stream Order ... Complete ");
        }

        /////////////////////////////////////////////////////////////////////////////////
        // ** Down Segment
        if(print_debug_messages)
        {
            main_window->Log_Message("[riv_data_file] Processing Down Segment ... ");
        }

        ReturnFlag = AddDownSegment(xRiverDbfFileName, BoundaryCondition );

        if ( ReturnFlag != 0 )
        {
            main_window->Log_Message("[riv_data_file] AddDownSegment Failed with error code " + QString::number(ReturnFlag));
            return ReturnFlag;
        }
        else
        {
            main_window->Log_Message("[riv_data_file] Processing Down Segment ... Complete ");
        }

        /////////////////////////////////////////////////////////////////////////////////
        // ** Riv File
        if(print_debug_messages)
        {
            main_window->Log_Message("[riv_data_file] Processing Riv File ... ");
        }

        ReturnFlag = Riv_File( xRiverDbfFileName, RivDataFileName );

        if ( ReturnFlag != 0 )
        {
            main_window->Log_Message("[riv_data_file] Riv_File Failed with error code " + QString::number(ReturnFlag));
            return ReturnFlag;
        }
        else
        {
            main_window->Log_Message("[riv_data_file] Processing Riv File ... Complete ");
        }

    } catch (...) {
        qDebug() << "Error: riv_data_file is returning w/o checking";
        return -5000;
    }

    return 0;
}
