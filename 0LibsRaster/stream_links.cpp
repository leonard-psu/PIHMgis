#include <QDebug>
#include <stdio.h>
#include "lsm.h"
#include "globals.h"

#define MAX 8
// MAX => No. of converging cells to one cell

int streamGen(float **riv, short **fdr, int i, int j, int*);
int findIJ(short **fdr, int i, int j, int *mIJ);
int findCell(float **riv, short **fdr, int i, int j, int (*cell)[2]); 

int numNodes_Seg=0;  //Used in stream links and streamGen
FILE *fpNode_Seg;  //Used in stream links and streamGen

// User interface to PIHMgis v3.5
extern PIHMgisDialog *main_window;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Segments the rivers
// Used in Link Grids
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int stream_links(QString qrivFile, QString qfdrFile, QString qsegFile, QString qnodeFile)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start stream_links";

    try {

        if(qrivFile == nullptr)
        {
            main_window->Log_Message("[stream_links] Error[1000] Invalid qrivFile.");
            return 1000;
        }
        if(qfdrFile == nullptr)
        {
            main_window->Log_Message("[stream_links] Error[1001] Invalid qfdrFile.");
            return 1001;
        }
        if(qnodeFile == nullptr)
        {
            main_window->Log_Message("[stream_links] Error[1002] Invalid qnodeFile.");
            return 1002;
        }
        if(qrivFile.length() < 1)
        {
            main_window->Log_Message("[stream_links] Error[1000] Invalid qrivFile.");
            return 1000;
        }
        if(qfdrFile.length() < 1)
        {
            main_window->Log_Message("[stream_links] Error[1001] Invalid qfdrFile.");
            return 1001;
        }
        if(qnodeFile.length() < 1)
        {
            main_window->Log_Message("[stream_links] Error[1002] Invalid qnodeFile.");
            return 1002;
        }

        QByteArray fname = qrivFile.toLatin1();
        char *rivFile = fname.data();
        QByteArray fname1 = qfdrFile.toLatin1();
        char *fdrFile = fname1.data();
        QByteArray fname2 = qsegFile.toLatin1();
        char *segFile = fname2.data();
        QByteArray fname3 = qnodeFile.toLatin1();
        char *nodeFile = fname3.data();

        int i, j, fdr = 0;
        int mIJ[2];
        int num = 1;

        if(dir == nullptr)
        {
            main_window->Log_Message("[stream_links] dir is null ");
            return -1000;
        }
        if(elev == nullptr)
        {
            main_window->Log_Message("[stream_links] elev is null ");
            return -1001;
        }
        if(mIJ == nullptr)
        {
            main_window->Log_Message("[stream_links] mIJ is null ");
            return -1002;
        }

        fpNode_Seg = fopen(nodeFile, "w");

        if(fpNode_Seg == nullptr)
        {
            main_window->Log_Message("[stream_links] Failed to open file " + qnodeFile);
            return -1003;
        }

        fprintf(fpNode_Seg, "\n");

        int err1 = gridread(fdrFile,(void ***)&dir,RPSHRDTYPE,&nx,&ny,&dx,&dy,bndbox,&csize,&mval,&filetype);
        if(err1 != 0)
        {
            main_window->Log_Message("[stream_links] Error[-1004] Failed to open file " + qfdrFile);
            return -1004;
        }

        int err2 = gridread(rivFile,(void ***)&elev,RPFLTDTYPE,&nx,&ny,&dx,&dy,bndbox,&csize,&mval,&filetype);
        if(err2 != 0)
        {
            main_window->Log_Message("[stream_links] Error[-1005] Failed to open file " + qrivFile);
            return -1005;
        }

        int err3 = gridread(rivFile,(void ***)&slope,RPFLTDTYPE,&nx,&ny,&dx,&dy,bndbox,&csize,&mval,&filetype);
        if(err3 != 0)
        {
            main_window->Log_Message("[stream_links] Error[-1006] Failed to open file " + qrivFile);
            return -1006;
        }

        bool error_found = false;

        for(i = 0; i < nx; i++) //i => Column : nx => col
        {
            for(j = 0; j < ny; j++) //j => Row : ny => row
            {
                if(elev[i][j] == 1)
                {
                    fdr = dir[i][j];
                    int err = findIJ(dir,i,j,mIJ); //Find outlet

                    if( err < 0)
                    {
                        fclose(fpNode_Seg);
                        main_window->Log_Message("[stream_links] Error[-1007] findIJ failed " + qsegFile);
                        return -1007;

                    }
                    else
                    {
                        if(elev[mIJ[0]][mIJ[1]] != 1 ) // outlet found
                        {
                            printf("Outlet -> %d %d\n",mIJ[0], mIJ[1]);
                            numNodes_Seg++;

                            fprintf(fpNode_Seg, "\n%d\t%d", i, j); // i => col :: j = > row
                            int err = streamGen(elev, dir, i, j, &num);
                            if( err < 0)
                            {
                                fclose(fpNode_Seg);
                                main_window->Log_Message("[stream_links] Error[-1008] streamGen failed " + qsegFile);
                                return -1008;
                            }
                        }
                    } //else
                } //if(elev[i][j] == 1)
            } // for(j = 0; j < ny; j++) //j => Row : ny => row
        } //for(i = 0; i < nx; i++) //i => Column : nx => col

        rewind(fpNode_Seg);
        fprintf(fpNode_Seg, "%d\n", numNodes_Seg);
        fclose(fpNode_Seg);

        int err4 = gridwrite(segFile,(void **)slope,RPFLTDTYPE,nx,ny,dx,dy,bndbox,csize,mval,filetype);
        if(err4 != 0)
        {
            main_window->Log_Message("[stream_links] Error[-1009] Grid Write failed " + qsegFile);
            return -1009;
        }

        int err = err1 + err2 + err3 + err4;

        return(err);

    } catch (...) {
        qDebug() << "Error: stream_links is returning w/o checking";
        return -9000;
    }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Recursively generates the river segments starting from outlet(i,j)
// Used in Stream Links (above)
// Uses global variables
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int streamGen(float **riv, short **fdr, int i, int j, int *num)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start streamGen";

    try {

        if(slope == nullptr)
        {
            main_window->Log_Message("[streamGen] slope is null ");
            return -1000;
        }

        int stop = 0;
        int ii = 0;
        int cell[MAX][2];
        int temp = 0;

        while(stop == 0)
        {
            temp = findCell(riv, fdr, i, j, cell);
            if( temp < 0)
            {
                main_window->Log_Message("[streamGen] findCell failed ");
                return -1001;
            }

            slope[i][j] = *num;

            if(temp==0)
            {
                (*num)++;
                return 0;
            }
            else if(temp==1)
            {
                i = cell[0][0];
                j = cell[0][1];
            }
            else
            {
                stop = 1;
                (*num)++;

                if(temp > 1)
                {
                    for(ii=0; ii<temp; ii++)
                    {
                        numNodes_Seg++;
                        fprintf(fpNode_Seg, "\n%d\t%d", cell[ii][0], cell[ii][1]); // i => col :: j = > row

                        int err = streamGen(riv, fdr, cell[ii][0], cell[ii][1],num);

                        if(err < 0)
                        {
                            main_window->Log_Message("[streamGen] Error generated by streamGen. User needs to check. ");
                            //Not stopping. Need to test to determine if necessary.
                        }
                    }
                }
            }
        }

        return 0;

    } catch (...) {
        qDebug() << "Error: streamGen is returning w/o checking";
        return -9000;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Finds down-stream cell index
// Used in Stream Links (above) and FindCell (below)
// Uses global variables
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int findIJ(short **fdr, int i, int j, int *mIJ)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start findIJ";

    try {

        if(fdr == nullptr)
        {
            main_window->Log_Message("[findIJ] fdr is null ");
            return -1000;
        }
        if(mIJ == nullptr)
        {
            main_window->Log_Message("[findIJ] mIJ is null ");
            return -1001;
        }

        // i => column : j => row

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

        return 0;

    } catch (...)
    {
        qDebug() << "Error: findIJ is returning w/o checking";
        return -9000;
    }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Finds ALL the up-stream/draining cells index 
// Error checking: returning negative values means something is wrong
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int findCell(float **riv, short **dir, int i, int j, int (*cell)[2])
{
    if(print_debug_messages)
        qDebug() << "INFO: Start findCell";

    try {

        if(riv == nullptr)
        {
            main_window->Log_Message("[findCell] riv is null ");
            return -1000;
        }
        if(dir == nullptr)
        {
            main_window->Log_Message("[findCell] dir is null ");
            return -1001;
        }

        int ii, jj = -100;
        int cellCount=0;
        int mIJ[2];
        bool error_found = false;

        for(ii=i-1; ii<=i+1; ii++)
        { //col
            for(jj=j-1; jj<=j+1; jj++)
            { //row

                if((ii!=i || jj!=j) && riv[ii][jj]==1)
                {
                    int err = findIJ(dir, ii, jj, mIJ);
                    if( err < 0)
                    {
                        error_found = true;
                    }

                    if(!error_found)
                    {
                        if(mIJ[0]==i && mIJ[1]==j)
                        {
                            cell[cellCount][0]=ii;
                            cell[cellCount][1]=jj;
                            cellCount++;
                        }
                    }
                }
            }
        }

        if(error_found)
        {
            main_window->Log_Message("[findCell] Error found ");
            return -1002;
        }

        return cellCount;

    } catch (...)
    {
        qDebug() << "Error: findCell is returning w/o checking";
        return -5000;
    }

}

