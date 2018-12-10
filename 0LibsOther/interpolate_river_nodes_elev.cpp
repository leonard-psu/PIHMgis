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
        if ( ! EleFile.open(QIODevice::ReadOnly | QIODevice::Text) )
        {
            main_window->Log_Message("[interpolate_river_nodes_elev] Error[47] opening Element file.");
            return 47;
        }
        QTextStream EleFileTextStream(&EleFile);

        QFile NodeFile(NodeFileName);
        if ( ! NodeFile.open(QIODevice::ReadOnly | QIODevice::Text) )
        {
            main_window->Log_Message("[interpolate_river_nodes_elev] Error[52] opening Node file. ");
            return 52;
        }
        QTextStream NodeFileTextStream(&NodeFile);

        QFile NeighFile(NeighFileName);
        if ( ! NeighFile.open(QIODevice::ReadOnly | QIODevice::Text) )
        {
            main_window->Log_Message("[interpolate_river_nodes_elev] Error[57] opening Neigh file.");
            return 57;
        }
        QTextStream NeighFileTextStream(&NeighFile);

        QFile OldMeshFile(OldMeshFileName);
        if ( ! OldMeshFile.open(QIODevice::ReadOnly | QIODevice::Text) )
        {
            main_window->Log_Message("[interpolate_river_nodes_elev] Error[62] opening OldMesh file.");
            return 62;
        }
        QTextStream OldMeshFileTextStream(&OldMeshFile);

        QFile NewMeshFile(NewMeshFileName);
        if ( ! NewMeshFile.open(QIODevice::WriteOnly | QIODevice::Text) )
        {
            main_window->Log_Message("[interpolate_river_nodes_elev] Error[68] opening NewMesh file.");
            return 68;
        }
        QTextStream NewMeshFileTextStream(&NewMeshFile);


        SHPHandle shp = SHPOpen(qPrintable(shpFileName), "rb");
        if(shp == nullptr)
        {
            main_window->Log_Message("[interpolate_river_nodes_elev] Error[75] shpFileName is NULL.");
            return 75;
        }
        DBFHandle dbf = DBFOpen(qPrintable(dbfFileName), "rb");
        if(dbf == nullptr)
        {
            main_window->Log_Message("[interpolate_river_nodes_elev] Error[75] dbfFileName is NULL.");
            return 75;
        }

        if ( shp == nullptr || dbf == nullptr )
            return 75;

        SHPHandle newshp = SHPCreate(qPrintable(DecompRiverFileNameShp), SHPT_ARC);
        if(newshp == nullptr)
        {
            main_window->Log_Message("[interpolate_river_nodes_elev] Error[81] DecompRiverFileNameShp is NULL. ");
            return 81;
        }

        DBFHandle newdbf = DBFCreate(qPrintable(DecompRiverFileNameDbf));
        if(newdbf == nullptr)
        {
            main_window->Log_Message("[interpolate_river_nodes_elev] Error[81] DecompRiverFileNameDbf is NULL. ");
            return 81;
        }

        if ( newshp == nullptr || newdbf == nullptr )
            return 81;

        int left = DBFAddField(newdbf, "LeftEle", FTInteger, 10, 0);
        int right= DBFAddField(newdbf, "RightEle", FTInteger, 10, 0);

        if ( left == -1 || right == -1 )
        {
            main_window->Log_Message("[interpolate_river_nodes_elev] Error[87] Add field count (left, right) don't match. ");
            return 87;
        }
        if ( left == 0 || right == 0 )
        {
            main_window->Log_Message("[interpolate_river_nodes_elev] Error[87] Add field count (left, right equal zero). ");
            return 87;
        }

        int temp;

        int NumNode;
        NodeFileTextStream >> NumNode;
        if ( NumNode < 1 )
        {
            main_window->Log_Message("[interpolate_river_nodes_elev] Error[88] Invalid Number of Nodes. ");
            return 88;
        }

        Point* node = new Point[NumNode+1];
        NodeFileTextStream >> temp;
        NodeFileTextStream >> temp;
        NodeFileTextStream >> temp;
        for(int i=1; i<=NumNode; i++)
        {
            NodeFileTextStream >> temp;
            NodeFileTextStream >> node[i].x;
            NodeFileTextStream >> node[i].y;
            NodeFileTextStream >> temp;
        }

        int NumEle;
        EleFileTextStream >> NumEle;
        if ( NumEle < 1 )
        {
            main_window->Log_Message("[interpolate_river_nodes_elev] Error[89] Invalid Number of Elements. ");
            return 89;
        }
        int** element = new int*[NumEle+1];
        EleFileTextStream >> temp;
        EleFileTextStream >> temp;
        for(int i=1; i<=NumEle; i++)
        {
            element[i] = new int[3];
            EleFileTextStream >> temp;
            EleFileTextStream >> element[i][0];
            EleFileTextStream >> element[i][1];
            EleFileTextStream >> element[i][2];
        }

        int NumNeigh;
        NeighFileTextStream >> NumNeigh;
        if ( NumEle < 1 )
        {
            main_window->Log_Message("[interpolate_river_nodes_elev] Error[90] Invalid Number of Neigh nodes. ");
            return 90;
        }
        int** neighbour = new int*[NumNeigh+1];
        NeighFileTextStream >> temp;
        for(int i=1; i<=NumNeigh; i++)
        {
            neighbour[i] = new int[3];
            NeighFileTextStream >> temp;
            NeighFileTextStream >> neighbour[i][0];
            NeighFileTextStream >> neighbour[i][1];
            NeighFileTextStream >> neighbour[i][2];
        }

        int RIV_NumEle, RIV_NumNode;
        OldMeshFileTextStream >> RIV_NumEle;
        OldMeshFileTextStream >> RIV_NumNode;
        NewMeshFileTextStream << RIV_NumEle << "\t" << RIV_NumNode;

        if ( RIV_NumEle < 1 )
        {
            main_window->Log_Message("[interpolate_river_nodes_elev] Error[91] Invalid Number of river elements. ");
            return 91;
        }
        QString RIV_line;
        for(int RIV_i=0; RIV_i<RIV_NumEle+1; RIV_i++)
        {
            RIV_line = OldMeshFileTextStream.readLine();
            NewMeshFileTextStream << RIV_line << "\n";
        }

        if ( RIV_NumNode < 1 )
        {
            main_window->Log_Message("[interpolate_river_nodes_elev] Error[92] Invalid Number of river nodes. ");
            return 92;
        }
        double** RIV_para = new double*[RIV_NumNode+1];
        int RIV_dummy;
        for(int RIV_i=1; RIV_i<=RIV_NumNode; RIV_i++)
        {
            RIV_para[RIV_i] = new double[4];
            OldMeshFileTextStream >> RIV_dummy;
            for(int RIV_j=0; RIV_j<4; RIV_j++)
            {
                OldMeshFileTextStream >> RIV_para[RIV_i][RIV_j];
            }
        }


        int** nodeInEle = new int*[NumNode+1]; //tells you : this (node present in which elements)
        int* nodeInEleCount = new int[NumNode+1];
        for(int i=1; i<=NumNode; i++)
        {
            nodeInEle[i] = new int[20];
            nodeInEleCount[i]=0;
        }

        for(int i=1; i<=NumEle; i++)
        {
            for(int j=0; j<3; j++)
            {
                nodeInEle[element[i][j]][nodeInEleCount[element[i][j]]++] = i;
            }
        }

        int** neighNode = new int*[NumNode+1]; //tells you which nodes are neighbours to i-th node
        int* neighNodeCount = new int[NumNode+1];
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
                    if(i != element[nodeInEle[i][j]][k])
                        neighNode[i][neighNodeCount[i]++]=element[nodeInEle[i][j]][k];
                }
            }
        }

        int LeftRight[2]; // To store left and right element #
        int recordCount = DBFGetRecordCount(dbf);

        if ( recordCount < 1 )
        {
            main_window->Log_Message("[interpolate_river_nodes_elev] Error[93] Invalid recordCount from DBFGetRecordCount. ");
            return 93;
        }

        int record = 0;
        double X[2], Y[2], Z[2];
        Z[0] = 0.0; Z[1] = 0.0;
        Point pt1, pt2;
        int numPt = 0;
        double oldDist, slope;
        int RIV_numPt1, RIV_numPt2 = 0;
        bool error_found = false;


        for(int i=0; i<recordCount; i++)
        {
            SHPObject* shpObj = SHPReadObject(shp, i);
            if(shpObj == nullptr)
            {
                main_window->Log_Message("[interpolate_river_nodes_elev] Error[94] Invalid SHPReadObject. ");
                error_found = true;
                break;
            }

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
                main_window->Log_Message("[interpolate_river_nodes_elev] Error[95] Did not find pt1. ");
                error_found = true;
                break;
            }

            numPt = Val;
            RIV_numPt1 = Val;
            Val = -1;

            for(int j=1; j<=NumNode; j++){
                //Val=j;
                if(distPt(pt2, node[j]) < 0.001)
                {
                    Val=j;
                    break;
                }
            }

            if( Val < 0 )
            {
                main_window->Log_Message("[interpolate_river_nodes_elev] Error[96] Did not find pt1. ");
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
                main_window->Log_Message("[interpolate_river_nodes_elev] Error[97] Did not find pt1. ");
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
                    main_window->Log_Message("[interpolate_river_nodes_elev] Error[290] Split River File Nodes Did *NOT* Match With The Mesh Nodes. ");
                    main_window->Log_Message("[interpolate_river_nodes_elev] Error[290] Perhaps River File Was Edited But Not Used In Merge Vector Layers. ");
                    error_found = true;
                    return 290;
                }

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
                    main_window->Log_Message("[interpolate_river_nodes_elev] Error[98] SHPCreateSimpleObject failed. ");
                    error_found = true;
                    return 98;
                }
                if ( SHPWriteObject(newshp, -1, newobj) < 0 )
                {
                    main_window->Log_Message("[interpolate_river_nodes_elev] Error[311] SHPWriteObject failed. ");
                    error_found = true;
                    return 311;
                }
                if ( ! DBFWriteIntegerAttribute(newdbf, record, left, LeftRight[0]) )
                {
                    main_window->Log_Message("[interpolate_river_nodes_elev] Error[313] DBFWriteIntegerAttribute left failed. ");
                    error_found = true;
                    return 313;
                }
                if ( ! DBFWriteIntegerAttribute(newdbf, record, right, LeftRight[1]) )
                {
                    main_window->Log_Message("[interpolate_river_nodes_elev] Error[315] DBFWriteIntegerAttribute right failed. ");
                    error_found = true;
                    return 315;
                }

                record++;

                if(j < 0)
                {
                    main_window->Log_Message("[interpolate_river_nodes_elev] Error[316] Invalid j value. ");
                    error_found = true;
                    return 316;
                }

                numPt = neighNode[numPt][j];
                oldDist = distPt(node[numPt], pt2);
            }

        } //End of for(int i=0; i<recordCount; i++)

        if(error_found)
        {
            //Shouldn't get here, but will use in case code changes latter
            main_window->Log_Message("[interpolate_river_nodes_elev] Error[317] in while loop. ");
            error_found = true;
            return 317;
        }

        for(int RIV_i=1; RIV_i<=RIV_NumNode; RIV_i++)
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

        //Free each sub-array
        for(int i = 0; i < NumEle; i++)
        {
            delete[] element[i];
        }
        //Free the array of pointers
        delete[] element;
        element = nullptr;

        for(int i = 0; i < NumNeigh; i++)
        {
            delete[] neighbour[i];
        }
        delete[] neighbour;
        neighbour = nullptr;

        for(int i = 0; i < RIV_NumNode; i++)
        {
            delete[] RIV_para[i];
        }
        delete[] RIV_para;
        RIV_para = nullptr;

        for(int i = 0; i < NumNode; i++)
        {
            delete[] nodeInEle[i];
        }
        delete[] nodeInEle;
        nodeInEle = nullptr;

        delete[] nodeInEleCount;


        for(int i = 0; i < NumNode; i++)
        {
            delete[] neighNode[i];
        }
        delete[] neighNode;
        neighNode = nullptr;

        delete[] neighNodeCount;

    } catch (...) {
        qDebug() << "Error: interpolate_river_nodes_elev [PROBLEM HERE, need to investigate further]";
        main_window->Log_Message("Error: interpolate_river_nodes_elev [PROBLEM HERE, need to investigate further]");
    }

    return 0;
}
