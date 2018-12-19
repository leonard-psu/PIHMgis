#include <QDebug>
#include <stdio.h>
#include "lsm.h"
#include "./../0LibsShape/shapefil.h"
#include "globals.h"


#define MAX 8 // MAX => No. of converging cells to one cell

int streamGenShp(float **riv, short **fdr, int i, int j);
int swapPts(double *ptx, double *pty, double *ptz, int numPts);
int findIJShp(short **fdr, int i, int j, int *mIJ);
int findCellShp(float **riv, short **fdr, int i, int j, int (*cell)[2]); 
int getNumPts(float **riv, int nx, int ny);

int old1Fdr, old2Fdr;
//Global Variables for shp api
double *ptx, *pty, *ptz;
int nVertices;
int numPts;
SHPHandle shp; 
DBFHandle dbf; 

// User interface to PIHMgis v3.5
extern PIHMgisDialog *main_window;

int global_Att_index; //Att Index in Shapefile

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Segments the rivers
// Used in Stream Polyline
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int stream_shape(QString qrivFile, QString qfdrFile, QString qrivShpFile, QString qrivDbfFile)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start stream_shape";

    try {

        if(qrivFile == nullptr)
        {
            main_window->Log_Message("[stream_shape] Error[-1000] Invalid qrivFile.");
            return -1000;
        }
        if(qfdrFile == nullptr)
        {
            main_window->Log_Message("[stream_shape] Error[-1001] Invalid qfdrFile.");
            return -1001;
        }
        if(qrivShpFile == nullptr)
        {
            main_window->Log_Message("[stream_shape] Error[-1002] Invalid qrivShpFile.");
            return -1002;
        }
        if(qrivDbfFile == nullptr)
        {
            main_window->Log_Message("[stream_shape] Error[-1003] Invalid qrivDbfFile.");
            return -1003;
        }

        if(qrivFile.length() < 1)
        {
            main_window->Log_Message("[stream_shape] Error[-1000] Invalid qrivFile.");
            return -1000;
        }
        if(qfdrFile.length() < 1)
        {
            main_window->Log_Message("[stream_shape] Error[-1001] Invalid qfdrFile.");
            return -1001;
        }
        if(qrivShpFile.length() < 1)
        {
            main_window->Log_Message("[stream_shape] Error[-1002] Invalid qrivShpFile.");
            return -1002;
        }
        if(qrivDbfFile.length() < 1)
        {
            main_window->Log_Message("[stream_shape] Error[-1003] Invalid qrivDbfFile.");
            return -1003;
        }

        QByteArray fname = qrivFile.toLatin1();
        char *rivFile = fname.data();
        QByteArray fname1 = qfdrFile.toLatin1();
        char *fdrFile = fname1.data();
        QByteArray fname2 = qrivShpFile.toLatin1();
        char *rivShpFile = fname2.data();
        QByteArray fname3 = qrivDbfFile.toLatin1();
        char *rivDbfFile = fname3.data();

        shp = SHPCreate(rivShpFile, SHPT_ARC);
        if (shp == nullptr)
        {
            main_window->Log_Message("[stream_shape] Error[43] rivShpFile is NULL. ");
            return 43;
        }

        dbf = DBFCreate(rivDbfFile);
        if (dbf == nullptr)
        {
            main_window->Log_Message("[stream_shape] Error[44] rivDbfFile is NULL. ");
            return 44;
        }

        global_Att_index= DBFAddField(dbf, "SegNum", FTInteger, 5, 0);
        if ( global_Att_index < 0 )
        {
            main_window->Log_Message("[stream_shape] Error[46] DBFAddField is NULL. ");
            return 46;
        }

        int err1 = gridread(fdrFile,(void ***)&dir,RPSHRDTYPE,&nx,&ny,&dx,&dy,bndbox,&csize,&mval,&filetype);
        if(err1 != 0)
        {
            main_window->Log_Message("[stream_shape] Error[-1004] Failed to open file " + qfdrFile);
            return -1004;
        }

        int err2 = gridread(rivFile,(void ***)&elev,RPFLTDTYPE,&nx,&ny,&dx,&dy,bndbox,&csize,&mval,&filetype);
        if(err2 != 0)
        {
            main_window->Log_Message("[stream_shape] Error[-1005] Failed to open file " + qrivFile);
            return -1005;
        }

        int err3 = gridread(rivFile,(void ***)&slope,RPFLTDTYPE,&nx,&ny,&dx,&dy,bndbox,&csize,&mval,&filetype);
        if(err3 != 0)
        {
            main_window->Log_Message("[stream_shape] Error[-1006] Failed to open file " + qrivFile);
            return -1006;
        }

        numPts = getNumPts(elev, nx, ny);
        if(numPts <= 0)
        {
            main_window->Log_Message("[stream_shape] Error[-1007] Invalid number of points " + QString::number(numPts));
            return -1007;
        }

        ptx = (double *)malloc(numPts * sizeof(double));
        if(ptx == nullptr)
        {
            main_window->Log_Message("[stream_shape] Error[-1008] ptx is  nullptr" );
            return -1008;
        }

        pty = (double *)malloc(numPts * sizeof(double));
        if(pty == nullptr)
        {
            main_window->Log_Message("[stream_shape] Error[-1009] pty is  nullptr" );
            free(ptx);
            return -1009;
        }

        ptz = (double *)malloc(numPts * sizeof(double));
        if(ptz == nullptr)
        {
            main_window->Log_Message("[stream_shape] Error[-1010] ptz is  nullptr" );
            free(ptx);
            free(pty);
            return -1010;
        }
        if(nx <= 0)
        {
            main_window->Log_Message("[stream_shape] Error[-1011] Invalid nx " + QString::number(nx));
            return -1011;
        }
        if(ny <= 0)
        {
            main_window->Log_Message("[stream_shape] Error[-1012] Invalid ny " + QString::number(ny));
            return -1012;
        }
        if(nx > 500000) //500000 is a guess
        {
            main_window->Log_Message("[stream_shape] Error[-1013] Invalid nx " + QString::number(nx));
            return -1013;
        }
        if(ny > 500000) //500000 is a guess
        {
            main_window->Log_Message("[stream_shape] Error[-1014] Invalid ny " + QString::number(ny));
            return -1014;
        }

        bool error_findIJShp = false;
        bool error_findCellShp = false;
        bool error_streamGenShp = false;
        int mIJ[2];
        int mcell[MAX][2];
        int mlocnVertices;
        int recordNum;

        for(int i = 0; i < nx; i++) //i => Column : nx => col
        {
            for(int j = 0; j < ny; j++) //j => Row : ny => row
            {
                if(elev[i][j]==1)
                {
                    int fdr = dir[i][j];

                    int err = findIJShp(dir,i,j,mIJ); //Find outlet

                    if( err == 0)
                    {
                        if(elev[mIJ[0]][mIJ[1]] != 1 ) // outlet found
                        {
                            if(print_debug_messages)
                            {
                                main_window->Log_Message("[stream_shape] Outlet ->  " + QString::number(mIJ[0]) + " " +  QString::number(mIJ[1]) + " " +  QString::number(elev[mIJ[0]][mIJ[1]]));
                            }

                            int mtemp = findCellShp(elev, dir, i, j, mcell);

                            if( mtemp < 0)
                            {
                                error_findCellShp = true;
                            }
                            else {

                                for(int mii=0; mii < mtemp; mii++)
                                {
                                    mlocnVertices=0;
                                    ptx[mlocnVertices] = bndbox[0] + (csize/2.0) + i*csize;
                                    pty[mlocnVertices] = bndbox[3] - (csize/2.0) - j*csize;
                                    ptz[mlocnVertices] = 0.0;

                                    old1Fdr = old2Fdr;
                                    old2Fdr = dir[i][j];
                                    nVertices = 1;

                                    int err = streamGenShp(elev, dir, mcell[mii][0], mcell[mii][1]);
                                    if ( err != 0)
                                    {
                                        error_streamGenShp = true;
                                    }
                                }

                            }
                        }
                    }
                    else {
                        error_findIJShp = true;
                    }
                }
            }
        }

        SHPClose(shp);
        DBFClose(dbf);

        //Clean up
        free(ptx);
        free(pty);
        free(ptz);

        if(error_findIJShp)
        {
            main_window->Log_Message("[stream_shape] Error[-1015] during find ijshp");
            return -1015;
        }
        if(error_findCellShp)
        {
            main_window->Log_Message("[stream_shape] Error[-10156] during find cell");
            return -1016;
        }
        if(error_streamGenShp)
        {
            main_window->Log_Message("[stream_shape] Error[-1017] during streamGenShp");
            return -1017;
        }

        return(0);

    } catch (...) {
        qDebug() << "Error: stream_shape is returning w/o checking";
        return -9000;
    }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Recursively generates the river segments starting from outlet(i,j)
// Used in stream_shape (above)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int streamGenShp(float **riv, short **fdr, int i, int j)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start streamGenShp";

    try {

        if(riv == nullptr)
        {
            main_window->Log_Message("[streamGenShp] Error[-1000] riv is null.");
            return -1000;
        }
        if(fdr == nullptr)
        {
            main_window->Log_Message("[streamGenShp] Error[-1001] fdr is null.");
            return -1001;
        }
        if(ptx == nullptr)
        {
            main_window->Log_Message("[streamGenShp] Error[-1002] ptx is null.");
            return -1002;
        }
        if(pty == nullptr)
        {
            main_window->Log_Message("[streamGenShp] Error[-1003] pty is null.");
            return -1003;
        }
        if(ptz == nullptr)
        {
            main_window->Log_Message("[streamGenShp] Error[-1004] ptz is null.");
            return -1004;
        }

        static int num = 1;
        int stop = 0;
        int ii = -1;
        int cell[MAX][2];
        int temp = -1;
        int locnVertices = -1;

        old2Fdr = 0;
        locnVertices = nVertices;

        while(stop == 0)
        {
            temp = findCellShp(riv, fdr, i, j, cell);

            if( temp >= 0)
            {
                ptx[locnVertices] = bndbox[0] + (csize/2.0) + i*csize;
                pty[locnVertices] = bndbox[3] - (csize/2.0) - j*csize;
                ptz[locnVertices] = 0.0;

                locnVertices++;

                slope[i][j] = num;

                if(temp==0)
                {
                    int err= swapPts(ptx, pty, ptz, locnVertices);
                    if(err != 0)
                    {
                        main_window->Log_Message("[streamGenShp] Error[-1005] swapPts failed.");
                        return -1005;
                    }

                    SHPObject *obj = SHPCreateSimpleObject(SHPT_ARC, locnVertices, ptx, pty, ptz);
                    if(obj == nullptr)
                    {
                        main_window->Log_Message("[streamGenShp] Error[-1006] SHPCreateSimpleObject failed.");
                        return -1006;
                    }

                    if ( SHPWriteObject(shp, -1, obj) < 0 )
                    {
                        main_window->Log_Message("[streamGenShp] Error[-1007] SHPWriteObject failed. ");
                        return -1007;
                    }

                    int recordNum = num-1;

                    if ( ! DBFWriteIntegerAttribute(dbf, recordNum, global_Att_index, num) )
                    {
                        main_window->Log_Message("[streamGenShp] Error[-1008] Unable to Write Record " + QString::number(recordNum) + " " + QString::number(num));
                        return -1008;
                    }

                    (num)++;

                    return 0;
                }
                else if(temp==1)
                {
                    old1Fdr = fdr[i][j];
                    i=cell[0][0];
                    j=cell[0][1];

                    old2Fdr = fdr[i][j];

                    if(old1Fdr==old2Fdr)
                    {
                        locnVertices--;
                    }
                }
                else //write polyline
                {
                    int err=  swapPts(ptx, pty, ptz, locnVertices);
                    if(err != 0)
                    {
                        main_window->Log_Message("[streamGenShp] Error[-1009] swapPts failed.");
                        return -1009;
                    }

                    SHPObject *obj = SHPCreateSimpleObject(SHPT_ARC, locnVertices, ptx, pty, ptz);
                    if(obj == nullptr)
                    {
                        main_window->Log_Message("[streamGenShp] Error[-1010] SHPCreateSimpleObject failed.");
                        return -1010;
                    }

                    if ( SHPWriteObject(shp, -1, obj) < 0 )
                    {
                        main_window->Log_Message("[streamGenShp] Error[-1011] SHPCreateSimpleObject failed.");
                        return -1011;
                    }

                    int recordNum = num-1;

                    if ( ! DBFWriteIntegerAttribute(dbf, recordNum, global_Att_index, num) )
                    {
                        main_window->Log_Message("[streamGenShp] Error[-1012] DBFWriteIntegerAttribute failed.");
                        return -1012;
                    }

                    stop = 1;
                    (num)++;

                    if(temp > 1 )
                    {
                        // Write polyline
                        for(ii=0; ii<temp; ii++)
                        {
                            // Add previous (junction) point to the list pos#0
                            locnVertices=0;

                            ptx[locnVertices] = bndbox[0] + (csize/2.0) + i*csize;
                            pty[locnVertices] = bndbox[3] - (csize/2.0) - j*csize;
                            ptz[locnVertices] = 0.0;

                            old1Fdr = old2Fdr;
                            old2Fdr = fdr[i][j];

                            // set global # of vertices to 1
                            nVertices=1;
                            int err = streamGenShp(riv, fdr, cell[ii][0], cell[ii][1]);

                            if ( err != 0 )
                                return err;
                        }
                    }
                }

            }
            else {
                main_window->Log_Message("[streamGenShp] findCellShp failed. ");
                //TODO validate
            }
        }

        return 0;

    } catch (...) {
        qDebug() << "Error: streamGenShp is returning w/o checking";
        return -9000;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Finds down-stream cell index
// Used in stream_shape (above) and findCellShp (below)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int findIJShp(short **fdr, int i, int j, int *mIJ)
{
    if(print_many_messages)
        qDebug() << "INFO: Start findIJShp";

    try {

        if(fdr == nullptr)
        {
            main_window->Log_Message("[findIJShp] Error[-1000] fdr is null.");
            return -1000;
        }
        if(mIJ == nullptr)
        {
            main_window->Log_Message("[findIJShp] Error[-1001] mIJ is null.");
            return -1001;
        }

        if(fdr[i][j]==4 || fdr[i][j]==5 || fdr[i][j]==6)
        {
            mIJ[0] = i-1;
        }
        else if(fdr[i][j]==2 || fdr[i][j]==1 || fdr[i][j]==8)
        {
            mIJ[0] = i+1;
        }
        else
        {
            mIJ[0] = i;
        }

        if(fdr[i][j]==4 || fdr[i][j]==3 || fdr[i][j]==2)
        {
            mIJ[1] = j-1;
        }
        else if(fdr[i][j]==6 || fdr[i][j]==7 || fdr[i][j]==8)
        {
            mIJ[1] = j+1;
        }
        else
        {
            mIJ[1] = j;
        }

    } catch (...) {
        qDebug() << "Error: findIJShp is returning w/o checking";
        return -9000;
    }

    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Finds ALL the up-stream/draining cells index
// Used in stream_shape (above)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int findCellShp(float **riv, short **dir, int i, int j, int (*cell)[2])
{
    if(print_many_messages)
        qDebug() << "INFO: Start findCellShp";

    try {

        if(riv == nullptr)
        {
            main_window->Log_Message("[findCellShp] Error[-1000] riv is null.");
            return -1000;
        }
        if(dir == nullptr)
        {
            main_window->Log_Message("[findCellShp] Error[-1001] dir is null.");
            return -1001;
        }

        int ii, jj = -1;
        int cellCount = 0;
        int mIJ[2];

        for(ii = i-1; ii <= i+1; ii++) //col
        {
            for(jj = j-1; jj <= j+1; jj++) //row
            {
                if((ii != i || jj != j) && riv[ii][jj] == 1)
                {
                    int err = findIJShp(dir, ii, jj, mIJ);

                    if( err == 0) //no error
                    {
                        if(mIJ[0] == i && mIJ[1] == j)
                        {
                            cell[cellCount][0]=ii;
                            cell[cellCount][1]=jj;
                            cellCount++;
                        }
                    }
                    else {
                        main_window->Log_Message("[findCellShp] Error[-1002] findIJShp failed.");
                        return -1002;
                    }
                }
            }
        }

        return cellCount;

    } catch (...)
    {
        qDebug() << "Error: findCellShp is returning w/o checking";
        return -9000;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// getNumPts
// Used in stream_shape (above)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int getNumPts(float **riv, int nx, int ny)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start getNumPts";

    try {

        if(riv == nullptr)
        {
            main_window->Log_Message("[getNumPts] Error[-1000] riv is null.");
            return -1000;
        }

        int num=0;

        for(int i = 0; i < nx; i++)
        {
            for(int j = 0; j < ny; j++)
            {
                if(riv[i][j] == 1)
                    num++;
            }
        }

        return num;

    } catch (...) {
        qDebug() << "Error: getNumPts is returning w/o checking";
        return -9000;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// swapPts
// Used in stream_shape (above)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int swapPts(double *ptx, double *pty, double *ptz, int numPts)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start swapPts";

    try {

        if(ptx == nullptr)
        {
            main_window->Log_Message("[swapPts] Error[-1000] ptx is null.");
            return -1000;
        }
        if(pty == nullptr)
        {
            main_window->Log_Message("[swapPts] Error[-1001] pty is null.");
            return -1001;
        }
        if(ptz == nullptr)
        {
            main_window->Log_Message("[swapPts] Error[-1002] ptz is null.");
            return -1002;
        }
        if(numPts <= 1)
        {
            main_window->Log_Message("[swapPts] Error[-1003] numPts <= 1");
            return -1003;
        }

        double temp = 0;
        for(int i=0; i < numPts/2; i++)
        {
            temp = ptx[i];
            ptx[i] = ptx[numPts-1-i];
            ptx[numPts-1-i] = temp;

            temp = pty[i];
            pty[i] = pty[numPts-1-i];
            pty[numPts-1-i] = temp;

            temp = ptz[i];
            ptz[i] = ptz[numPts-1-i];
            ptz[numPts-1-i] = temp;

        }

        return 0;

    } catch (...) {
        qDebug() << "Error: swapPts is returning w/o checking";
        return -9000;
    }
}
