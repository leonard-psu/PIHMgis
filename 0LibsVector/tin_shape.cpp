#include <QString>
#include <QObject>
#include <QDebug>

#include <fstream>
#include <iomanip>
#include "./../0LibsShape/shapefil.h"
#include "globals.h"

using namespace std;

// User interface to PIHMgis v3.5
extern PIHMgisDialog *main_window;

struct TS_Point
{
    double x,y;
};
struct TS_Element
{
    int p1, p2, p3;
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// tin_shape
// Used in domain decomposition
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int tin_shape(QString qeleFileName, QString qnodeFileName, QString qshpFileName, QString qdbfFileName)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start tin_shape";

    try {

        if(qeleFileName == nullptr)
        {
            main_window->Log_Message("[tin_shape] Error[-1000] Invalid qeleFileName.");
            return -1000;
        }

        if(qnodeFileName == nullptr)
        {
            main_window->Log_Message("[tin_shape] Error[-1001] Invalid qnodeFileName.");
            return -1001;
        }

        if(qshpFileName == nullptr)
        {
            main_window->Log_Message("[tin_shape] Error[-1003] Invalid qshpFileName.");
            return -1003;
        }

        if(qdbfFileName == nullptr)
        {
            main_window->Log_Message("[tin_shape] Error[-1004] Invalid qdbfFileName.");
            return -1004;
        }

        if(qeleFileName.length() < 1)
        {
            main_window->Log_Message("[tin_shape] Error[-1005] Invalid qeleFileName.");
            return -1005;
        }

        if(qnodeFileName.length() < 1)
        {
            main_window->Log_Message("[tin_shape] Error[-1006] Invalid qnodeFileName.");
            return -1006;
        }

        if(qshpFileName.length() < 1)
        {
            main_window->Log_Message("[tin_shape] Error[-1007] Invalid qshpFileName.");
            return -1007;
        }

        if(qdbfFileName.length() < 1)
        {
            main_window->Log_Message("[tin_shape] Error[-1008] Invalid qdbfFileName.");
            return -1008;
        }

        QByteArray fname = qeleFileName.toLatin1();
        char *eleFileName = fname.data();
        QByteArray fname1 = qnodeFileName.toLatin1();
        char *nodeFileName = fname1.data();
        QByteArray fname2 = qshpFileName.toLatin1();
        char *shpFileName = fname2.data();
        QByteArray fname3 = qdbfFileName.toLatin1();
        char *dbfFileName = fname3.data();

        std::ifstream eleFile;
        std::ifstream nodeFile;


        eleFile.open(eleFileName);
        if ( !eleFile.is_open())
        {
            main_window->Log_Message("[tin_shape] Error[-1009] failed to open eleFile");
            return -1009;
        }

        nodeFile.open(nodeFileName);
        if ( !nodeFile.is_open())
        {
            main_window->Log_Message("[tin_shape] Error[-1010] nodeFile to open nodeFile");
            eleFile.close();
            return -1010;
        }

        int temp = 0;
        int countEle = 0;
        int countNode = 0;

        eleFile >> countEle;
        eleFile >> temp;
        eleFile >> temp;

        if( countEle <= 0 )
        {
            main_window->Log_Message("[tin_shape] Error[-1011] Invalid countEle <= 0.");
            eleFile.close();
            nodeFile.close();
            return -1011;
        }

        if( countEle > 500000 ) //500000 is a guess
        {
            main_window->Log_Message("[tin_shape] Error[-1012] Invalid countEle > 500000.");
            eleFile.close();
            nodeFile.close();
            return -1012;
        }

        TS_Element* ele = new TS_Element[countEle];
        if( ele == nullptr )
        {
            main_window->Log_Message("[tin_shape] Error[-1013] ele null");
            eleFile.close();
            nodeFile.close();
            return -1013;
        }

        nodeFile >> countNode;
        nodeFile >> temp;
        nodeFile >> temp;
        nodeFile >> temp;

        if( countNode <= 0 )
        {
            main_window->Log_Message("[tin_shape] Error[-1011] Invalid countNode <= 0.");
            eleFile.close();
            nodeFile.close();
            delete[] ele;
            return -1014;
        }

        if( countNode > 500000 ) //500000 is a guess
        {
            main_window->Log_Message("[tin_shape] Error[-1012] Invalid countNode > 500000.");
            eleFile.close();
            nodeFile.close();
            delete[] ele;
            return -1015;
        }


        TS_Point* nodes = new TS_Point[countNode];
        if( nodes == nullptr )
        {
            main_window->Log_Message("[tin_shape] Error[-1016] nodes null");
            eleFile.close();
            nodeFile.close();
            delete[] ele;
            return -1016;
        }

        main_window->Log_Message("[tin_shape] Reading " + QString::number(countEle) + " Elements");

        for(int i = 0; i < countEle; i++)
        {
            eleFile >> temp;
            eleFile >> ele[i].p1;
            eleFile >> ele[i].p2;
            eleFile >> ele[i].p3;
        }

        main_window->Log_Message("[tin_shape] Reading " + QString::number(countNode) + " Nodes");

        for(int i = 0; i < countNode; i++)
        {
            nodeFile >> temp;
            nodeFile >> setprecision(20) >> nodes[i].x;
            nodeFile >> setprecision(20) >> nodes[i].y;
            nodeFile >> temp;
        }

        main_window->Log_Message("[tin_shape] Writing Shapefile");

        SHPHandle newShp = SHPCreate(shpFileName, SHPT_POLYGON);
        if(newShp == nullptr)
        {
            main_window->Log_Message("[tin_shape] Error[-1017] SHPCreate failed.");
            eleFile.close();
            nodeFile.close();
            delete[] ele;
            delete[] nodes;
            return -1017;
        }

        bool error_found = false;
        double px[4], py[4], pz[4], pm[4];
        for(int i = 0; i < countEle; i++)
        {
            setprecision(20);
            px[0] = nodes[ele[i].p1-1].x;
            px[1] = nodes[ele[i].p2-1].x;
            px[2] = nodes[ele[i].p3-1].x;
            px[3] = nodes[ele[i].p1-1].x;

            py[0] = nodes[ele[i].p1-1].y;
            py[1] = nodes[ele[i].p2-1].y;
            py[2] = nodes[ele[i].p3-1].y;
            py[3] = nodes[ele[i].p1-1].y;

            pz[0] = 0;
            pz[1] = 0;
            pz[2] = 0;
            pz[3] = 0;
            pm[0] = 0;
            pm[1] = 0;
            pm[2] = 0;
            pm[3] = 0;

            int panPartStart[1], panPartType[1];
            panPartStart[0]= 0;
            panPartType[0] = 5;

            if(!error_found)
            {
                SHPObject* shpObj = SHPCreateObject(SHPT_POLYGON, i, 1, panPartStart, nullptr, 4, px, py, pz, pm);
                if(shpObj == nullptr)
                {
                    main_window->Log_Message("[tin_shape] Error[-2000] SHPObject failed at index " + QString::number(i));
                    error_found = true;
                }
                else
                {
                    SHPComputeExtents(shpObj);

                    int err = SHPWriteObject(newShp, -1, shpObj);
                    if( err < 0)
                    {
                        main_window->Log_Message("[tin_shape] Error[-2001] SHPWriteObject failed at index " + QString::number(i));
                        error_found = true;
                    }

                    //Clean up
                    SHPDestroyObject(shpObj);
                }
            }
        }

        SHPClose(newShp);

        if(error_found)
        {
            main_window->Log_Message("[tin_shape] Error[-2002] Error found creating shapefile.");
            eleFile.close();
            nodeFile.close();
            delete[] ele;
            delete[] nodes;
            return -2002;
        }

        //Creates .dbf file
        main_window->Log_Message("[tin_shape] Writing dbf file");

        DBFHandle newDbf = DBFCreate(dbfFileName);
        if ( newDbf == nullptr )
        {
            main_window->Log_Message("[tin_shape] Error[-2003] Error found creating shapefile.");
            eleFile.close();
            nodeFile.close();
            delete[] ele;
            delete[] nodes;
            return -2003;
        }

        int err = DBFAddField(newDbf, "Ele_ID", FTInteger, 9, 0);
        if ( err < 0 )
        {
            main_window->Log_Message("[tin_shape] Error[-2004] DBFAddField failed.");
            eleFile.close();
            nodeFile.close();
            delete[] ele;
            delete[] nodes;
            return -2004;
        }


        error_found = false;
        for(int i = 0; i <  countEle; i++)
        {
            int err = DBFWriteIntegerAttribute(newDbf, i, 0, i+1);

            if ( err < 0 )
            {
                main_window->Log_Message("[tin_shape] Error[-2005] DBFWriteIntegerAttribute failed at index " + QString::number(i));
                error_found = true;
                break;
            }
        }

        //Clean up
        DBFClose(newDbf);
        eleFile.close();
        nodeFile.close();
        delete[] ele;
        delete[] nodes;

        if(error_found)
        {
            main_window->Log_Message("[tin_shape] Error[-2006] Error(s) happened during dbd file creation ");
            return -2006;
        }

    }
    catch (...) {

        qDebug() << "Error: tin_shape is returning w/o checking";
        return -9000;
    }

    return 0;
}
