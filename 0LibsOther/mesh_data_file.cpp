#include <iostream>
#include <iomanip>
#include <math.h>

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>

#include "0LibsOther/raster_grid_value.h"
#include "globals.h"

using namespace std;

// User interface to PIHMgis v3.5
extern PIHMgisDialog *main_window;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Important function to create PIHM mesh file
// This function has not been tested rigously.
// Known issues include the following:
// (1) GDAL versions behaviour slightly differently.
// (2) No extent checking
// (3) No checking of values. Are they reasonable?
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int mesh_data_file(QString SurfaceFilename, QString SubsurfaceFileName, QString EleFileName, QString NodeFileName, QString NeighFileName, QString MeshDataFileName, bool CheckBoxSubSurface)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start mesh_data_file";

    try {

        QFile EleFile(EleFileName);
        if ( ! EleFile.open(QIODevice::ReadOnly | QIODevice::Text) )
        {
            main_window->Log_Message("[mesh_data_file] Error[18] opening Element file.");
            return 18;
        }

        QTextStream EleFileTextStream(&EleFile);

        QFile NodeFile(NodeFileName);
        if ( ! NodeFile.open(QIODevice::ReadOnly | QIODevice::Text) )
        {
            main_window->Log_Message("[mesh_data_file] Error[23] opening Node file.");
            return 23;
        }

        QTextStream NodeFileTextStream(&NodeFile);

        QFile NeighFile(NeighFileName);
        if ( ! NeighFile.open(QIODevice::ReadOnly | QIODevice::Text) )
        {
            main_window->Log_Message("[mesh_data_file] Error[28] opening Neigh file.");
            return 28;
        }
        QTextStream NeighFileTextStream(&NeighFile);

        QFile MeshDataFile(MeshDataFileName);
        if ( ! MeshDataFile.open(QIODevice::WriteOnly | QIODevice::Text) )
        {
            main_window->Log_Message("[mesh_data_file] Error[32] opening Mesh file.");
            return 32;
        }
        QTextStream MeshDataFileTextStream(&MeshDataFile);

        GDALDataset *SurfElev, *SubSurfElev;
        double sRanges[6], bRanges[6];

        GDALAllRegister();
        SurfElev = (GDALDataset *)GDALOpen(qPrintable(SurfaceFilename), GA_ReadOnly);
        if ( SurfElev == nullptr )
        {
            main_window->Log_Message("[mesh_data_file] Error[44] opening SurfElev file.");
            return 44;
        }
        getExtent(SurfElev, sRanges);

        if( CheckBoxSubSurface == false )
        {
            SubSurfElev = (GDALDataset *)GDALOpen(qPrintable(SubsurfaceFileName), GA_ReadOnly);
            if ( SubSurfElev == nullptr )
            {
                main_window->Log_Message("[mesh_data_file] Error[51] opening SubSurfElev file.");
                return 51;
            }

            getExtent(SubSurfElev, bRanges);
        }

        int temp = -1;
        int NumEle = -1, NumNode = -1, NumNeigh = -1;

        EleFileTextStream   >> NumEle;   EleFileTextStream   >> temp; EleFileTextStream  >> temp;
        NodeFileTextStream  >> NumNode;  NodeFileTextStream  >> temp; NodeFileTextStream >> temp; NodeFileTextStream >> temp;
        NeighFileTextStream >> NumNeigh; NeighFileTextStream >> temp;

        MeshDataFileTextStream << NumEle << "\t" << NumNode << "\n";

        if(NumEle < 1 || NumEle > 100000) //100000 is a guess for now
        {
            main_window->Log_Message("[mesh_data_file] Error[52] Invalid Number of Elements.");
            return 52;
        }
        if(NumNode < 1 || NumNode > 100000) //100000 is a guess for now
        {
            main_window->Log_Message("[mesh_data_file] Error[53] Invalid Number of Nodes.");
            return 53;
        }
        if(NumNeigh < 1 || NumNeigh > 100000) //100000 is a guess for now
        {
            main_window->Log_Message("[mesh_data_file] Error[54] Invalid Number of Neighs.");
            return 54;
        }

        int index = -9999;
        int node0 = -9999, node1 = -9999, node2 = -9999, nabr0 = -9999, nabr1 = -9999, nabr2 = -9999;
        for(int i=0; i<NumEle; i++)
        {
            EleFileTextStream>>index;
            EleFileTextStream>>node0;
            EleFileTextStream>>node1;
            EleFileTextStream>>node2;
            NeighFileTextStream>>temp;
            NeighFileTextStream>>nabr0;
            NeighFileTextStream>>nabr1;
            NeighFileTextStream>>nabr2;
            MeshDataFileTextStream<<index<<"\t"<<node0<<"\t"<<node1<<"\t"<<node2<<"\t"<<(nabr0<0?0:nabr0)<<"\t"<<(nabr1<0?0:nabr1)<<"\t"<<(nabr2<0?0:nabr2)<<"\n";
        }

        bool error_found = false;
        double X= -9999, Y= -9999, Zmin= -9999, Zmax = -9999;
        for(int i=0; i<NumNode; i++)
        {
            NodeFileTextStream >> index;
            NodeFileTextStream >> X;
            NodeFileTextStream >> Y;
            NodeFileTextStream >> temp;
            //Zmin = getRasterValue(bElev, 1, X, Y, bRanges);
            Zmax = raster_grid_value(SurfElev, 1, X, Y, sRanges);
            if(Zmax == -9999)
            {
                error_found = true;
            }

            if( CheckBoxSubSurface == false )
            {
                Zmin = raster_grid_value(SubSurfElev, 1, X, Y, bRanges);
                if(Zmin == -9999)
                {
                    error_found = true;
                }
            }
            else
            {
                Zmin = Zmax-(SubsurfaceFileName).toDouble();
            }

            MeshDataFileTextStream.setRealNumberNotation(QTextStream::FixedNotation);
            MeshDataFileTextStream<<index<<"\t";

            MeshDataFileTextStream.setRealNumberNotation(QTextStream::FixedNotation);
            MeshDataFileTextStream.setRealNumberPrecision(20);
            MeshDataFileTextStream<<X<<"\t"; //<<setprecision(20)

            MeshDataFileTextStream.setRealNumberNotation(QTextStream::FixedNotation);
            MeshDataFileTextStream.setRealNumberPrecision(20);
            MeshDataFileTextStream<<Y<<"\t"; //<<setprecision(20)

            MeshDataFileTextStream.setRealNumberNotation(QTextStream::FixedNotation);
            MeshDataFileTextStream.setRealNumberPrecision(15);
            MeshDataFileTextStream<<Zmin<<"\t"; //<<setprecision(15)

            MeshDataFileTextStream.setRealNumberNotation(QTextStream::FixedNotation);
            MeshDataFileTextStream.setRealNumberPrecision(15);
            MeshDataFileTextStream<<Zmax<<"\n"; //<<setprecision(15)
        }

        EleFile.close();
        NodeFile.close();
        NeighFile.close();
        MeshDataFile.close();

        if(error_found)
        {
            main_window->Log_Message("[mesh_data_file] Invalid mesh file created!");
        }

    } catch (...) {

        qDebug() << "Error: mesh_data_file is returning 0";

    }

    return 0;
}

