#include <iomanip>
#include <math.h>

#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDebug>

#include "interpolate_river_nodes_elev.h"
#include "./../0LibsShape/shapefil.h"
#include "globals.h"

#define PI 3.14
#define distPt(p1, p2) fabs(p1.x-p2.x)+fabs(p1.y-p2.y)
#define distXY(x1, y1, x2, y2) fabs(x1-x2)+fabs(y1-y2)
#define distPtXY(p, x, y) fabs(p.x-x)+fabs(p.y-y)

using namespace std;

// User interface to PIHMgis v3.5
extern PIHMgisDialog *main_window;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Calculate Slope between two points
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double SLOPEa(Point p1, Point p2)
{
    //if(print_debug_messages)
    //    qDebug() << "INFO: SLOPEa";

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
// Function to adjust river nodes with mesh nodes and river slopes
// This function has not been tested rigously.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int interpolate_river_nodes_elev(QString shpFileName, QString dbfFileName, QString EleFileName, QString NodeFileName, QString NeighFileName, QString OldMeshFileName, QString NewMeshFileName, QString DecompRiverFileNameShp, QString DecompRiverFileNameDbf)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start interpolate_river_nodes_elev";

    try {

        QFile EleFile(EleFileName);
        if ( EleFile.open(QIODevice::ReadOnly | QIODevice::Text) == false)
        {
            main_window->Log_Message("[interpolate_river_nodes_elev] Error[-1000] opening Element file.");
            return -1000;
        }

        QTextStream EleFileTextStream(&EleFile);

        QFile NodeFile(NodeFileName);
        if ( NodeFile.open(QIODevice::ReadOnly | QIODevice::Text) == false)
        {
            main_window->Log_Message("[interpolate_river_nodes_elev] Error[-1001] opening Node file. ");
            EleFile.close();
            return -1001;
        }

        QTextStream NodeFileTextStream(&NodeFile);

        QFile NeighFile(NeighFileName);
        if ( NeighFile.open(QIODevice::ReadOnly | QIODevice::Text) == false )
        {
            main_window->Log_Message("[interpolate_river_nodes_elev] Error[-1002] opening Neigh file.");
            EleFile.close();
            NodeFile.close();
            return -1002;
        }

        QTextStream NeighFileTextStream(&NeighFile);

        QFile OldMeshFile(OldMeshFileName);
        if ( OldMeshFile.open(QIODevice::ReadOnly | QIODevice::Text) == false )
        {
            main_window->Log_Message("[interpolate_river_nodes_elev] Error[-1003] opening OldMesh file.");
            EleFile.close();
            NodeFile.close();
            NeighFile.close();
            return -1003;
        }

        QTextStream OldMeshFileTextStream(&OldMeshFile);

        QFile NewMeshFile(NewMeshFileName);
        if ( NewMeshFile.open(QIODevice::WriteOnly | QIODevice::Text) == false)
        {
            main_window->Log_Message("[interpolate_river_nodes_elev] Error[-1004] opening NewMesh file.");
            EleFile.close();
            NodeFile.close();
            NeighFile.close();
            OldMeshFile.close();
            return -1004;
        }

        QTextStream NewMeshFileTextStream(&NewMeshFile);
        SHPHandle shp = SHPOpen(qPrintable(shpFileName), "rb");
        if(shp == nullptr)
        {
            main_window->Log_Message("[interpolate_river_nodes_elev] Error[-1005] shpFileName is NULL.");
            EleFile.close();
            NodeFile.close();
            NeighFile.close();
            OldMeshFile.close();
            NewMeshFile.close();
            return -1005;
        }

        DBFHandle dbf = DBFOpen(qPrintable(dbfFileName), "rb");
        if(dbf == nullptr)
        {
            main_window->Log_Message("[interpolate_river_nodes_elev] Error[-1006] dbfFileName is NULL.");
            EleFile.close();
            NodeFile.close();
            NeighFile.close();
            OldMeshFile.close();
            NewMeshFile.close();
            SHPClose(shp);
            return -1006;
        }

        SHPHandle newshp = SHPCreate(qPrintable(DecompRiverFileNameShp), SHPT_ARC);
        if(newshp == nullptr)
        {
            main_window->Log_Message("[interpolate_river_nodes_elev] Error[-1007] DecompRiverFileNameShp is NULL. ");
            EleFile.close();
            NodeFile.close();
            NeighFile.close();
            OldMeshFile.close();
            NewMeshFile.close();
            SHPClose(shp);
            DBFClose(dbf);
            return -1007;
        }

        DBFHandle newdbf = DBFCreate(qPrintable(DecompRiverFileNameDbf));
        if(newdbf == nullptr)
        {
            main_window->Log_Message("[interpolate_river_nodes_elev] Error[-1008] DecompRiverFileNameDbf is NULL. ");
            EleFile.close();
            NodeFile.close();
            NeighFile.close();
            OldMeshFile.close();
            NewMeshFile.close();
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            return -1008;
        }

        int left = DBFAddField(newdbf, "LeftEle", FTInteger, 10, 0);
        int right= DBFAddField(newdbf, "RightEle", FTInteger, 10, 0);

        if ( left < 0 || right < 0 )
        {
            main_window->Log_Message("[interpolate_river_nodes_elev] Error[-1009] Add field count (left, right) don't match. ");
            EleFile.close();
            NodeFile.close();
            NeighFile.close();
            OldMeshFile.close();
            NewMeshFile.close();
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);
            return -1009;
        }

        int NumNode;
        NodeFileTextStream >> NumNode;
        bool error_found = false;

        if ( NumNode < 1 )
        {
            main_window->Log_Message("[interpolate_river_nodes_elev] Error[-1010] Invalid Number of Nodes < 1. ");
            error_found = true;
        }

        if ( NumNode > 500000 ) //500000 is a guess
        {
            main_window->Log_Message("[interpolate_river_nodes_elev] Error[-1011] Invalid Number of Nodes > 500000. ");
            error_found = true;
        }

        if(error_found)
        {
            EleFile.close();
            NodeFile.close();
            NeighFile.close();
            OldMeshFile.close();
            NewMeshFile.close();
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);
            return -1011;
        }

        int temp;
        Point* node = new Point[NumNode+1];
        if( node == nullptr)
        {
            main_window->Log_Message("[interpolate_river_nodes_elev] Error[-1012] node is nullptr. ");
            EleFile.close();
            NodeFile.close();
            NeighFile.close();
            OldMeshFile.close();
            NewMeshFile.close();
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);
            return -1012;
        }

        NodeFileTextStream >> temp;
        NodeFileTextStream >> temp;
        NodeFileTextStream >> temp;

        for(int i=1; i <= NumNode; i++)
        {
            NodeFileTextStream >> temp;
            NodeFileTextStream >> node[i].x;
            NodeFileTextStream >> node[i].y;
            NodeFileTextStream >> temp;
        }

        int NumEle;
        EleFileTextStream >> NumEle;

        error_found = false;
        if ( NumEle < 1 )
        {
            main_window->Log_Message("[interpolate_river_nodes_elev] Error[-1013] Invalid Number of Elements < 1 ");
            error_found = true;
        }

        if ( NumEle > 500000 ) //500000 is a guess
        {
            main_window->Log_Message("[interpolate_river_nodes_elev] Error[-1014] Invalid Number of Elements > 500000 ");
            error_found = true;
        }

        if ( error_found )
        {
            EleFile.close();
            NodeFile.close();
            NeighFile.close();
            OldMeshFile.close();
            NewMeshFile.close();
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);
            delete [] node;

            return -1014;
        }

        int** element = new int*[NumEle+1];
        if(element == nullptr)
        {
            main_window->Log_Message("[interpolate_river_nodes_elev] Error[-1015] element is null ");
            EleFile.close();
            NodeFile.close();
            NeighFile.close();
            OldMeshFile.close();
            NewMeshFile.close();
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);
            delete [] node;

            return -1015;
        }

        EleFileTextStream >> temp;
        EleFileTextStream >> temp;

        error_found = false;
        for(int i = 1; i <= NumEle; i++)
        {
            element[i] = new int[3];

            if(element[i] == nullptr)
            {
                error_found = true;
            }
            else
            {
                EleFileTextStream >> temp;
                EleFileTextStream >> element[i][0];
                EleFileTextStream >> element[i][1];
                EleFileTextStream >> element[i][2];
            }
        }

        if(error_found)
        {
            main_window->Log_Message("[interpolate_river_nodes_elev] Error[-1016] element is null ");
            EleFile.close();
            NodeFile.close();
            NeighFile.close();
            OldMeshFile.close();
            NewMeshFile.close();
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);
            delete [] node;
            delete [] element; //Note no attempt to delete all

            return -1016;
        }

        int NumNeigh;
        NeighFileTextStream >> NumNeigh;

        error_found = false;
        if ( NumNeigh < 1 )
        {
            main_window->Log_Message("[interpolate_river_nodes_elev] Error[-1017] Invalid Number of Neigh nodes. ");
            error_found = true;
        }
        if ( NumNeigh > 500000 )
        {
            main_window->Log_Message("[interpolate_river_nodes_elev] Error[-1018] Invalid Number of Neigh nodes. ");
            error_found = true;
        }

        if ( error_found )
        {
            EleFile.close();
            NodeFile.close();
            NeighFile.close();
            OldMeshFile.close();
            NewMeshFile.close();
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);
            delete [] node;
            node = nullptr;

            //Free the array of pointers
            delete[] element;
            element = nullptr;

            return -1018;
        }


        int** neighbour = new int*[NumNeigh+1];

        if(neighbour == nullptr)
        {
            main_window->Log_Message("[interpolate_river_nodes_elev] Error[-1019] neighbour failed. ");

            EleFile.close();
            NodeFile.close();
            NeighFile.close();
            OldMeshFile.close();
            NewMeshFile.close();
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);
            delete [] node;
            node = nullptr;

            //Free the array of pointers
            delete[] element;
            element = nullptr;

            return -1018;
        }

        NeighFileTextStream >> temp;
        error_found = false;

        for(int i = 1; i <= NumNeigh; i++)
        {
            neighbour[i] = new int[3];

            if(neighbour[i] == nullptr)
            {
                error_found = true;
            }
            else
            {
                NeighFileTextStream >> temp;
                NeighFileTextStream >> neighbour[i][0];
                NeighFileTextStream >> neighbour[i][1];
                NeighFileTextStream >> neighbour[i][2];
            }
        }

        if ( error_found )
        {
            main_window->Log_Message("[interpolate_river_nodes_elev] Error[-1020] neighbour failed. ");

            EleFile.close();
            NodeFile.close();
            NeighFile.close();
            OldMeshFile.close();
            NewMeshFile.close();
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);
            delete [] node;
            node = nullptr;

            //Free the array of pointers
            delete[] element;
            element = nullptr;

            //No attempt to delete neighbour[i]
            delete[] neighbour;
            neighbour = nullptr;

            return -1020;
        }

        int RIV_NumEle, RIV_NumNode;
        OldMeshFileTextStream >> RIV_NumEle;
        OldMeshFileTextStream >> RIV_NumNode;
        NewMeshFileTextStream << RIV_NumEle << "\t" << RIV_NumNode;

        error_found = false;
        if ( RIV_NumEle < 1 )
        {
            main_window->Log_Message("[interpolate_river_nodes_elev] Error[-1021] Invalid Number of river elements < 1. ");
            error_found = true;
        }

        if ( RIV_NumEle > 500000 ) //500000 is a guess
        {
            main_window->Log_Message("[interpolate_river_nodes_elev] Error[-1021] Invalid Number of river elements > 500000. ");
            error_found = true;
        }

        if ( error_found )
        {
            EleFile.close();
            NodeFile.close();
            NeighFile.close();
            OldMeshFile.close();
            NewMeshFile.close();
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);
            delete [] node;
            node = nullptr;

            //Free the array of pointers
            delete[] element;
            element = nullptr;

            delete[] neighbour;
            neighbour = nullptr;

            return -1021;
        }


        QString RIV_line;
        for(int RIV_i = 0; RIV_i < RIV_NumEle+1; RIV_i++)
        {
            RIV_line = OldMeshFileTextStream.readLine();
            NewMeshFileTextStream << RIV_line << "\n";
        }

        error_found = false;
        if ( RIV_NumNode < 1 )
        {
            main_window->Log_Message("[interpolate_river_nodes_elev] Error[-1022] Invalid Number of river nodes < 1. ");
            error_found = true;
        }

        if ( RIV_NumNode > 500000 ) //500000 is a guess
        {
            main_window->Log_Message("[interpolate_river_nodes_elev] Error[-1023] Invalid Number of river nodes > 500000. ");
            error_found = true;
        }

        if ( error_found )
        {
            EleFile.close();
            NodeFile.close();
            NeighFile.close();
            OldMeshFile.close();
            NewMeshFile.close();
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);
            delete [] node;
            node = nullptr;

            //Free the array of pointers
            delete[] element;
            element = nullptr;

            delete[] neighbour;
            neighbour = nullptr;

            return -1023;
        }

        double** RIV_para = new double*[RIV_NumNode+1];

        if ( RIV_para == nullptr )
        {
            main_window->Log_Message("[interpolate_river_nodes_elev] Error[-1024] RIV_para is null. ");

            EleFile.close();
            NodeFile.close();
            NeighFile.close();
            OldMeshFile.close();
            NewMeshFile.close();
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);
            delete [] node;
            node = nullptr;

            //Free the array of pointers
            delete[] element;
            element = nullptr;

            delete[] neighbour;
            neighbour = nullptr;

            return -1024;
        }

        int RIV_dummy;
        error_found = false;

        for(int RIV_i = 1; RIV_i <= RIV_NumNode; RIV_i++)
        {
            RIV_para[RIV_i] = new double[4];

            if( RIV_para[RIV_i] == nullptr)
            {
                error_found = true;
            }
            else
            {
                OldMeshFileTextStream >> RIV_dummy;
                for(int RIV_j=0; RIV_j<4; RIV_j++)
                {
                    OldMeshFileTextStream >> RIV_para[RIV_i][RIV_j];
                }
            }
        }

        if ( error_found )
        {
            main_window->Log_Message("[interpolate_river_nodes_elev] Error[-1025] RIV_para is null. ");

            EleFile.close();
            NodeFile.close();
            NeighFile.close();
            OldMeshFile.close();
            NewMeshFile.close();
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);
            delete [] node;
            node = nullptr;

            //Free the array of pointers
            delete[] element;
            element = nullptr;

            delete[] neighbour;
            neighbour = nullptr;

            //No attempt to delete riv par elements
            delete[] RIV_para;

            return -1025;
        }

        int** nodeInEle = new int*[NumNode+1]; //tells you : this (node present in which elements)

        if ( nodeInEle == nullptr )
        {
            main_window->Log_Message("[interpolate_river_nodes_elev] Error[-1026] nodeInEle is null. ");

            EleFile.close();
            NodeFile.close();
            NeighFile.close();
            OldMeshFile.close();
            NewMeshFile.close();
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);
            delete [] node;
            node = nullptr;

            //Free the array of pointers
            delete[] element;
            element = nullptr;

            delete[] neighbour;
            neighbour = nullptr;

            delete[] nodeInEle;
            nodeInEle = nullptr;

            return -1026;
        }

        int* nodeInEleCount = new int[NumNode+1];

        if ( nodeInEleCount == nullptr )
        {
            main_window->Log_Message("[interpolate_river_nodes_elev] Error[-1027] nodeInEleCount is null. ");

            EleFile.close();
            NodeFile.close();
            NeighFile.close();
            OldMeshFile.close();
            NewMeshFile.close();
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);
            delete [] node;
            node = nullptr;

            //Free the array of pointers
            delete[] element;
            element = nullptr;

            delete[] neighbour;
            neighbour = nullptr;

            delete[] nodeInEle;
            nodeInEle = nullptr;

            delete[] nodeInEleCount;

            return -1027;
        }

        error_found = false;
        for(int i=1; i <= NumNode; i++)
        {
            nodeInEle[i] = new int[20]; //TODO how was 20 decided?
            if(nodeInEle[i] == nullptr)
                error_found = true;

            nodeInEleCount[i] = 0;
        }

        if ( error_found )
        {
            main_window->Log_Message("[interpolate_river_nodes_elev] Error[-1028] nodeInEle is null. ");

            EleFile.close();
            NodeFile.close();
            NeighFile.close();
            OldMeshFile.close();
            NewMeshFile.close();
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);
            delete [] node;
            node = nullptr;

            //Free the array of pointers
            delete[] element;
            element = nullptr;

            delete[] neighbour;
            neighbour = nullptr;

            delete[] RIV_para;
            RIV_para = nullptr;

            delete[] nodeInEle;
            delete[] nodeInEleCount;


            return -1028;
        }

        for(int i=1; i<=NumEle; i++)
        {
            for(int j=0; j<3; j++)
            {
                nodeInEle[element[i][j]][nodeInEleCount[element[i][j]]++] = i;
            }
        }

        int** neighNode = new int*[NumNode+1]; //tells you which nodes are neighbours to i-th node

        if ( neighNode == nullptr )
        {
            main_window->Log_Message("[interpolate_river_nodes_elev] Error[-1029] neighNode is null. ");

            EleFile.close();
            NodeFile.close();
            NeighFile.close();
            OldMeshFile.close();
            NewMeshFile.close();
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);
            delete [] node;
            node = nullptr;

            //Free the array of pointers
            delete[] element;
            element = nullptr;

            delete[] neighbour;
            neighbour = nullptr;

            delete[] RIV_para;
            RIV_para = nullptr;

            delete[] nodeInEle;
            nodeInEle = nullptr;

            return -1029;
        }

        int* neighNodeCount = new int[NumNode+1];

        if ( neighNodeCount == nullptr )
        {
            main_window->Log_Message("[interpolate_river_nodes_elev] Error[-1030] neighNode is null. ");

            EleFile.close();
            NodeFile.close();
            NeighFile.close();
            OldMeshFile.close();
            NewMeshFile.close();
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);
            delete [] node;
            node = nullptr;

            //Free the array of pointers
            delete[] element;
            element = nullptr;

            delete[] neighbour;
            neighbour = nullptr;

            delete[] RIV_para;
            RIV_para = nullptr;

            delete[] nodeInEle;
            nodeInEle = nullptr;

            delete[] nodeInEleCount;
            nodeInEleCount = nullptr;

            return -1030;
        }

        error_found = false;
        for(int i = 1; i <= NumNode; i++)
        {
            neighNode[i] = new int[100]; //TODO How was 100 decided?
            if(neighNode[i] == nullptr)
                error_found = true;

            neighNodeCount[i] = 0;
        }

        if ( error_found )
        {
            main_window->Log_Message("[interpolate_river_nodes_elev] Error[-1031] neighNode is null. ");

            EleFile.close();
            NodeFile.close();
            NeighFile.close();
            OldMeshFile.close();
            NewMeshFile.close();
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);
            delete [] node;
            node = nullptr;

            //Free the array of pointers
            delete[] element;
            element = nullptr;

            delete[] neighbour;
            neighbour = nullptr;

            delete[] RIV_para;
            RIV_para = nullptr;

            delete[] nodeInEle;
            nodeInEle = nullptr;

            delete[] nodeInEleCount;
            nodeInEleCount = nullptr;

            return -1031;
        }

        for(int i=1; i <= NumNode; i++)
        {
            for(int j=0; j < nodeInEleCount[i]; j++)
            {
                for(int k=0; k < 3; k++)
                {
                    if(i != element[nodeInEle[i][j]][k])
                        neighNode[i][neighNodeCount[i]++]=element[nodeInEle[i][j]][k];
                }
            }
        }

        int LeftRight[2]; // To store left and right element #
        int recordCount = DBFGetRecordCount(dbf);

        if ( recordCount < 1 )
        {
            main_window->Log_Message("[interpolate_river_nodes_elev] Error[-1032] Invalid recordCount from DBFGetRecordCount. ");
            EleFile.close();
            NodeFile.close();
            NeighFile.close();
            OldMeshFile.close();
            NewMeshFile.close();
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(newshp);
            DBFClose(newdbf);
            delete [] node;
            node = nullptr;

            //Free the array of pointers
            delete[] element;
            element = nullptr;

            delete[] neighbour;
            neighbour = nullptr;

            delete[] RIV_para;
            RIV_para = nullptr;

            delete[] nodeInEle;
            nodeInEle = nullptr;

            delete[] neighNode;
            neighNode = nullptr;

            delete[] nodeInEleCount;
            nodeInEleCount = nullptr;

            return -1032;
        }


        int record = 0;
        double X[2], Y[2], Z[2];
        Z[0] = 0.0; Z[1] = 0.0;
        Point pt1, pt2;
        int numPt = 0;
        double oldDist, slope;
        int RIV_numPt1, RIV_numPt2 = 0;

        error_found = false;

        for(int i = 0; i < recordCount; i++)
        {
            SHPObject* shpObj = SHPReadObject(shp, i);
            if(shpObj == nullptr)
            {
                main_window->Log_Message("[interpolate_river_nodes_elev] Error[2000] Invalid SHPReadObject. ");
                error_found = true;
                break;
            }
            else
            {
                pt1.x = shpObj->padfX[0];
                pt1.y = shpObj->padfY[0];
                pt2.x = shpObj->padfX[shpObj->nVertices-1];
                pt2.y = shpObj->padfY[shpObj->nVertices-1];
                slope = SLOPEa(pt1, pt2);

                int Val = -1;
                for(int j=1; j<=NumNode; j++)
                {
                    //was here Val=j;
                    if(distPt(pt1, node[j]) < 0.001)
                    {
                        Val=j;
                        break;
                    }
                }
                if( Val < 0 )
                {
                    main_window->Log_Message("[interpolate_river_nodes_elev] Error[2001] Did not find pt1. ");
                    error_found = true;
                    break;
                }

                numPt = Val;
                RIV_numPt1 = Val;
                Val = -1;

                for(int j=1; j<=NumNode; j++)
                {
                    if(distPt(pt2, node[j]) < 0.001)
                    {
                        Val=j;
                        break;
                    }
                }

                if( Val < 0 )
                {
                    main_window->Log_Message("[interpolate_river_nodes_elev] Error[2002] Did not find pt1. ");
                    error_found = true;
                    break;
                }
                RIV_numPt2 = Val;

                //if(RIV_para[RIV_numPt1][3]<RIV_para[RIV_numPt2][3])
                //{
                //    qDebug() <<"\nSegment Number "<<i<<" Node# "<<RIV_numPt1<<","<<RIV_numPt2<<":"<<RIV_para[RIV_numPt1][3]-RIV_para[RIV_numPt2][3]<<"\n";
                //}

                if( numPt < 0 || numPt >= NumNode )
                {
                    main_window->Log_Message("[interpolate_river_nodes_elev] Error[2003] Did not find pt1. ");
                    error_found = true;
                    break;
                }

                oldDist = distPt(node[numPt], pt2);

                while( distPt(pt2, node[numPt]) > 0.001 )
                {
                    int j= -1, k= -1, l = -1;
                    bool found = false;
                    for(j=0; j<neighNodeCount[numPt]; j++)
                    {
                        if(fabs(slope-SLOPEa(node[numPt], node[neighNode[numPt][j]])) < 0.01)
                        {
                            found = true;
                            break;
                        }
                    }

                    if ( found == false )
                    {
                        main_window->Log_Message("[interpolate_river_nodes_elev] Error[3000] Split River File Nodes Did *NOT* Match With The Mesh Nodes. ");
                        main_window->Log_Message("[interpolate_river_nodes_elev] Error[3000] Perhaps River File Was Edited But Not Used In Merge Vector Layers. ");
                        error_found = true;
                    }
                    else
                    {
                        RIV_para[neighNode[numPt][j]][3]=((distPt(pt1,node[neighNode[numPt][j]]))/(distPt(pt1,pt2)))*(RIV_para[RIV_numPt2][3]-RIV_para[RIV_numPt1][3])+RIV_para[RIV_numPt1][3];

                        X[0] = node[numPt].x;
                        Y[0] = node[numPt].y;
                        X[1] = node[neighNode[numPt][j]].x;
                        Y[1] = node[neighNode[numPt][j]].y;
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
                        if(newobj == nullptr)
                        {
                            main_window->Log_Message("[interpolate_river_nodes_elev] Error[3001] SHPCreateSimpleObject failed. ");
                            error_found = true;
                        }
                        else
                        {
                            if ( SHPWriteObject(newshp, -1, newobj) < 0 )
                            {
                                main_window->Log_Message("[interpolate_river_nodes_elev] Error[3002] SHPWriteObject failed. ");
                                error_found = true;
                            }

                            if ( ! DBFWriteIntegerAttribute(newdbf, record, left, LeftRight[0]) )
                            {
                                main_window->Log_Message("[interpolate_river_nodes_elev] Error[3003] DBFWriteIntegerAttribute left failed. ");
                                error_found = true;
                            }

                            if ( ! DBFWriteIntegerAttribute(newdbf, record, right, LeftRight[1]) )
                            {
                                main_window->Log_Message("[interpolate_river_nodes_elev] Error[3004] DBFWriteIntegerAttribute right failed. ");
                                error_found = true;
                            }
                        }

                        record++;

                        if(j < 0)
                        {
                            main_window->Log_Message("[interpolate_river_nodes_elev] Error[3005] Invalid j value. ");
                            error_found = true;
                        }

                        if(j > 500000) //500000 is a guess
                        {
                            main_window->Log_Message("[interpolate_river_nodes_elev] Error[3006] Invalid j value. ");
                            error_found = true;
                        }

                        if(!error_found)
                        {
                            numPt = neighNode[numPt][j];
                            oldDist = distPt(node[numPt], pt2);
                        }
                    }
                }
            }

        } //End of for(int i=0; i<recordCount; i++)

        if(error_found)
        {
            main_window->Log_Message("[interpolate_river_nodes_elev] Error(s) [3007] in while loop. ");
            error_found = true;
        }
        else {

            for(int RIV_i = 1; RIV_i <= RIV_NumNode; RIV_i++)
            {
                NewMeshFileTextStream.setRealNumberNotation(QTextStream::FixedNotation);
                NewMeshFileTextStream << RIV_i << "\t";

                NewMeshFileTextStream.setRealNumberNotation(QTextStream::FixedNotation);
                NewMeshFileTextStream.setRealNumberPrecision(20);
                NewMeshFileTextStream << RIV_para[RIV_i][0] << "\t"; // << setprecision(20)

                NewMeshFileTextStream.setRealNumberNotation(QTextStream::FixedNotation);
                NewMeshFileTextStream.setRealNumberPrecision(20);
                NewMeshFileTextStream << RIV_para[RIV_i][1] << "\t"; // << setprecision(20)

                NewMeshFileTextStream.setRealNumberNotation(QTextStream::FixedNotation);
                NewMeshFileTextStream.setRealNumberPrecision(15);
                NewMeshFileTextStream << RIV_para[RIV_i][2] << "\t"; // << setprecision(15)

                NewMeshFileTextStream.setRealNumberNotation(QTextStream::FixedNotation);
                NewMeshFileTextStream.setRealNumberPrecision(15);
                NewMeshFileTextStream << RIV_para[RIV_i][3] << "\n"; // << setprecision(15)
            }
        }

        //Close Files
        SHPClose(shp);
        DBFClose(dbf);
        SHPClose(newshp);
        DBFClose(newdbf);

        EleFile.close();
        NodeFile.close();
        NeighFile.close();
        OldMeshFile.close();
        NewMeshFile.close();

        //Delete new arrays

        delete[] node;
        node = nullptr;

        //Free the array of pointers
        delete[] element;
        element = nullptr;

        delete[] neighbour;
        neighbour = nullptr;

        delete[] RIV_para;
        RIV_para = nullptr;

        delete[] nodeInEle;
        nodeInEle = nullptr;

        delete[] nodeInEleCount;
        nodeInEleCount = nullptr;

        delete[] neighNode;
        neighNode = nullptr;

        delete[] neighNodeCount;
        neighNodeCount = nullptr;

    } catch (...) {
        qDebug() << "Error: interpolate_river_nodes_elev [PROBLEM HERE, need to investigate further]";
        main_window->Log_Message("Error: interpolate_river_nodes_elev [PROBLEM HERE, need to investigate further]");
    }

    return 0;
}
