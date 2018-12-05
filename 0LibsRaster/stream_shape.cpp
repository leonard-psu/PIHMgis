#include <QDebug>
#include <stdio.h>
#include "lsm.h"
#include "./../0LibsShape/shapefil.h"
#include "globals.h"


#define MAX 8 // MAX => No. of converging cells to one cell

//int streamSegmentationShp(char *rivFile, char *fdrFile, char *rivShpFile, char *rivDbfFile);
//int streamGenShp(float **riv, short **fdr, int i, int j, int*);
int streamGenShp(float **riv, short **fdr, int i, int j);
void swapPts(double *ptx, double *pty, double *ptz, int numPts);
void findIJShp(short **fdr, int i, int j, int *mIJ);
int findCellShp(float **riv, short **fdr, int i, int j, int (*cell)[2]); 
int getNumPts(float **riv, int nx, int ny);

int old1Fdr, old2Fdr;
//Global Variables for shp api
double *ptx, *pty, *ptz;
int nVertices;
int numPts;
SHPHandle shp; 
DBFHandle dbf; 
SHPObject *obj;
int Att; 
int recordNum;

// User interface to PIHMgis v3.5
extern PIHMgisDialog *main_window;

// Segments the rivers 
int stream_shape(char *rivFile, char *fdrFile, char *rivShpFile, char *rivDbfFile)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start stream_shape";

    try {
        //FILE *fp;
        int err, err1, err2, err3;
        int i, j, fdr;
        int mIJ[2];

        int mii;
        int mcell[MAX][2];
        int mtemp;
        int mlocnVertices;

        //int num = 1;

        shp = SHPCreate(rivShpFile, SHPT_ARC);
        if (shp == nullptr)
        {
            main_window->Log_Message("[stream_shape] Error rivShpFile is NULL. Returning 43.");
            return 43;
        }

        dbf = DBFCreate(rivDbfFile);
        if (dbf == nullptr)
        {
            main_window->Log_Message("[stream_shape] Error rivDbfFile is NULL. Returning 44.");
            return 44;
        }

        Att = DBFAddField(dbf, "SegNum", FTInteger, 5, 0);
        if ( Att == -1 )
        {
            main_window->Log_Message("[stream_shape] Error DBFAddField is NULL. Returning 46.");
            return 46;
        }

        err1=gridread(fdrFile,(void ***)&dir,RPSHRDTYPE,&nx,&ny,&dx,&dy,bndbox,&csize,&mval,&filetype);
        err2=gridread(rivFile,(void ***)&elev,RPFLTDTYPE,&nx,&ny,&dx,&dy,bndbox,&csize,&mval,&filetype);
        err3=gridread(rivFile,(void ***)&slope,RPFLTDTYPE,&nx,&ny,&dx,&dy,bndbox,&csize,&mval,&filetype);
        printf("%d %d %f %f\n",nx, ny, slope[4][2], slope[2][5]); //getchar(); getchar();

        numPts = getNumPts(elev, nx, ny);
        printf("total pts= %d\n", numPts); //getchar(); getchar();
        ptx = (double *)malloc(numPts*sizeof(double));
        pty = (double *)malloc(numPts*sizeof(double));
        ptz = (double *)malloc(numPts*sizeof(double));

        for(i=0; i<nx; i++)
        { //i => Column : nx => col
            for(j=0; j<ny; j++)
            { //j => Row : ny => row
                //printf("= %d\n",elev[i][j]);
                if(elev[i][j]==1)
                {
                    fdr=dir[i][j];
                    //printf("= %d\n",fdr);
                    findIJShp(dir,i,j,mIJ); //Find outlet
                    //printf("IJ= %d %d %d\n",mIJ[0], mIJ[1],elev[mIJ[0]][mIJ[1]]);
                    //getchar();
                    if(elev[mIJ[0]][mIJ[1]] != 1 )
                    { // outlet found
                        printf("Outlet -> %d\t%d\t%f\n",mIJ[0], mIJ[1],elev[mIJ[0]][mIJ[1]]);
                        //getchar();

                        mtemp=findCellShp(elev, dir, i, j, mcell);
                        for(mii=0; mii<mtemp; mii++)
                        {
                            mlocnVertices=0;
                            ptx[mlocnVertices] = bndbox[0] + (csize/2.0) + i*csize;
                            pty[mlocnVertices] = bndbox[3] - (csize/2.0) - j*csize;
                            ptz[mlocnVertices] = 0.0;

                            old1Fdr = old2Fdr;
                            old2Fdr = dir[i][j];
                            nVertices = 1;
                            //streamGenShp(elev, dir, i, j);
                            streamGenShp(elev, dir, mcell[mii][0], mcell[mii][1]);
                        }
                    }
                }
            }
        }
        //err = gridwrite(segFile,(void **)slope,RPFLTDTYPE,nx,ny,dx,dy,bndbox,csize,mval,filetype);
        SHPClose(shp);
        DBFClose(dbf);

        err = err1 + err2 + err3;
        return(err);

    } catch (...) {
        qDebug() << "Error: stream_shape is returning w/o checking";
        return 50;
    }

}

// Recursively generates the river segments starting from outlet(i,j)
int streamGenShp(float **riv, short **fdr, int i, int j)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start streamGenShp";

    try {
        int flag = 0;
        static int num = 1;
        int stop = 0;
        int ii = -1;
        int cell[MAX][2];
        int temp = -1;
        int locnVertices = -1;

        printf("\n0 StreamGen -> %d",num);
        //printf("StreamGen-> %d %d\n",i, j);
        //getchar();
        old2Fdr = 0;
        //sequenceFlag = 0;
        locnVertices = nVertices;

        while(stop == 0)
        {
            temp=findCellShp(riv, fdr, i, j, cell);
            //printf("temp= %d\n",temp);
            //printf("--> %d\n", locnVertices); //getchar(); getchar();
            //printf("%f %f %f\n", bndbox[0], bndbox[1], csize);
            ptx[locnVertices] = bndbox[0] + (csize/2.0) + i*csize;
            pty[locnVertices] = bndbox[3] - (csize/2.0) - j*csize;
            ptz[locnVertices] = 0.0;
            //printf("%f %f %f\n", ptx[locnVertices], pty[locnVertices], ptz[locnVertices]);
            locnVertices++;

            slope[i][j]=num;
            //getchar(); getchar();
            if(temp==0)
            {
                //write polyline
                swapPts(ptx, pty, ptz, locnVertices);
                obj = SHPCreateSimpleObject(SHPT_ARC, locnVertices, ptx, pty, ptz);
                if ( SHPWriteObject(shp, -1, obj) < 0 )
                {
                    printf("Exception 140");
                    return 140;
                }
                recordNum = num-1;
                printf(" \nDebug 152 recordNum = %d ",recordNum);
                if ( ! DBFWriteIntegerAttribute(dbf, recordNum, Att, num) )
                {
                    printf(" Unable to Write Record %d %d ",recordNum,num);
                    return 143;
                }
                //printf("shp# %d\n", num);
                //printf("1pts = %d\n", locnVertices); getchar(); getchar();
                (num)++;
                return 0;
            }
            else if(temp==1)
            {
                old1Fdr = fdr[i][j];
                i=cell[0][0];
                j=cell[0][1];
                //old1Fdr = old2Fdr;
                old2Fdr = fdr[i][j];
                if(old1Fdr==old2Fdr)
                {
                    locnVertices--;
                    //ptx[locnVertices-1] = ptx[locnVertices];
                    //pty[locnVertices-1] = pty[locnVertices];
                }
            }
            else
            {// => temp>1)
                //write polyline
                //printf("2pts = %d\n", locnVertices); getchar(); getchar();
                swapPts(ptx, pty, ptz, locnVertices);
                obj = SHPCreateSimpleObject(SHPT_ARC, locnVertices, ptx, pty, ptz);
                //printf("2pts = %d\n", locnVertices); getchar(); getchar();
                if ( SHPWriteObject(shp, -1, obj) < 0 )
                {
                    printf("Exception 168");
                    return 168;
                }
                recordNum = num-1;
                if ( ! DBFWriteIntegerAttribute(dbf, recordNum, Att, num) )
                    return 171;
                //printf("shp# %d\n", num);
                //printf("2pts = %d\n", locnVertices); getchar(); getchar();
                stop = 1;
                (num)++;
                //printf("%f\n",num);
                if(temp>1)
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
                        flag = streamGenShp(riv, fdr, cell[ii][0], cell[ii][1]);

                        if ( flag > 0 )
                            return flag;
                    }
                }
            }
        }
        return flag;

    } catch (...) {
        qDebug() << "Error: streamGenShp is returning w/o checking";
        return -500;
    }

}

// Finds down-stream cell index 
void findIJShp(short **fdr, int i, int j, int *mIJ)
{
    //if(print_debug_messages)
    //    qDebug() << "INFO: Start findIJShp";

    try {
        // i => column : j => row
        //printf("fdr= %d %d %d\n",i,j,fdr[i][j]);
        if(fdr[i][j]==4 || fdr[i][j]==5 || fdr[i][j]==6)
            mIJ[0]=i-1;
        else if(fdr[i][j]==2 || fdr[i][j]==1 || fdr[i][j]==8)
            mIJ[0]=i+1;
        else
            mIJ[0]=i;

        if(fdr[i][j]==4 || fdr[i][j]==3 || fdr[i][j]==2)
            mIJ[1]=j-1;
        else if(fdr[i][j]==6 || fdr[i][j]==7 || fdr[i][j]==8)
            mIJ[1]=j+1;
        else
            mIJ[1]=j;

    } catch (...) {
        qDebug() << "Error: findIJShp is returning w/o checking";
    }

    return;


}

// Finds ALL the up-stream/draining cells index 
int findCellShp(float **riv, short **dir, int i, int j, int (*cell)[2])
{
    //if(print_debug_messages)
    //    qDebug() << "INFO: Start findCellShp";

    try {
        int ii, jj = -1;
        int cellCount=0;
        //int fdr;
        int mIJ[2];
        //printf("i= %d j= %d\n",i,j);
        for(ii=i-1; ii<=i+1; ii++)
        { //col
            for(jj=j-1; jj<=j+1; jj++)
            { //row
                //printf("ii= %d jj= %d\n",ii, jj);
                if((ii!=i || jj!=j) && riv[ii][jj]==1)
                {
                    //fdr=dir[ii][jj];
                    findIJShp(dir, ii, jj, mIJ);
                    //printf("%d %d\n", mIJ[0], mIJ[1]);
                    if(mIJ[0]==i && mIJ[1]==j)
                    {
                        cell[cellCount][0]=ii;
                        cell[cellCount][1]=jj;
                        cellCount++;
                        //printf("-> %d %d\n", ii, jj);
                        //printf("here\n");
                    }
                }
            }
        }
        //getchar(); getchar();
        return cellCount;

    } catch (...) {
        qDebug() << "Error: findCellShp is returning w/o checking";
    }
}

int getNumPts(float **riv, int nx, int ny)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start getNumPts";

    try {

        int i, j, num=0;
        printf("debug getNumPts\n"); //getchar(); getchar();
        for(i=0; i<nx; i++)
        {
            for(j=0; j<ny; j++)
            {
                if(riv[i][j]==1)
                    num++;
            }
        }
        printf("debug getNumPts OUT\n"); //getchar(); getchar();
        return num;

    } catch (...) {
        qDebug() << "Error: getNumPts is returning w/o checking";
        return -500;
    }
}

void swapPts(double *ptx, double *pty, double *ptz, int numPts)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start swapPts";

    try {

        double temp = 0;
        for(int i=0; i<numPts/2; i++)
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

    } catch (...) {
        qDebug() << "Error: swapPts is returning w/o checking";
    }
}
