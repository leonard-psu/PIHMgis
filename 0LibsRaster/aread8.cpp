//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Program to compute area contributing to each pixel from pointers using recursive algorithm
// Created by David G Tarboton
// File: aread8.c
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <QDebug>
#include <iostream>
#include "lsm.h"
#include "globals.h"


// User interface to PIHMgis v3.5
extern PIHMgisDialog *main_window;

int **arr;    // Global array with area results
void darea(int, int);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// For Help and documentation visit http://hydrology.usu.edu/taudem/taudem5/index.html
// Error checking added.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int aread8(char *pfile,char *afile, double x, double y, int doall)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start aread8";

    if(pfile == nullptr)
    {
        main_window->Log_Message("[aread8] Error[1000] Invalid file.");
        return 1000;
    }

    int i,j,err,row,col;
    err = 0;

    // define directions
    d1[1]=0; d1[2]= -1; d1[3]= -1; d1[4]= -1; d1[5]=0; d1[6]=1; d1[7]=1; d1[8]=1;
    d2[1]=1; d2[2]=1; d2[3]=0; d2[4]= -1; d2[5]= -1; d2[6]= -1; d2[7]=0; d2[8]=1;

    if(print_debug_messages)
        main_window->Log_Message("[aread8] Starting gridread");

    // read pointers
    err = gridread(pfile,(void ***)&dir,RPSHRDTYPE,&nx,&ny,&dx,&dy,bndbox,&csize,&ndv,&filetype);

    if(print_debug_messages)
        main_window->Log_Message("[aread8] Finished gridread");

    if(err != 0)
    {
        main_window->Log_Message("[aread8] gridread failed");
        goto ERROR1;
    }

    //  Allocate area memory
    arr = (int **) matalloc(nx, ny, RPINTDTYPE);
    if(arr == nullptr)
    {
        main_window->Log_Message("[aread8] Error[1000] matalloc failed.");
        goto ERROR1;
    }

    // initialize area array to 0, -1 on boundary
    for(i=0; i < ny; i++)
    {
        for(j=0; j < nx; j++)
        {
            if(i!=0 && i!=ny-1 && j!=0 && j!=nx-1 && dir[j][i]!= -1)
                arr[j][i]=0;
            else
                arr[j][i]= -1;
        }
    }

    //  Only compute area's for designated location
    if(doall == 0)
    {
        col= (int)floor((x-bndbox[0])/csize);
        row= (int)floor((bndbox[3]-y)/csize);
        if(row <0 || row > ny || col < 0 || col > nx)
        {
            main_window->Log_Message("[aread8] WARNING Given coords out of area - whole area will be calculated.");
            row=0;
            col=0;
        }
    }
    else
    {
        row=0;
        col=0;
    }

    if(row > 0 && col > 0)
    {
        // call drainage area subroutine for pixel to zero on
        darea(row,col);
    }
    else
    {
        // call drainage area subroutine for each area
        // work from middle outwards to avoid deep recursions

        for(i = ny/2; i < ny-1; i++)
        {
            for(j=nx/2; j<nx-1; j++)
                darea(i,j);

            for(j=nx/2-1; j>=1; j--)
                darea(i,j);
        }

        for(i = ny/2-1; i >= 1; i--)
        {
            for(j = nx/2; j < nx-1; j++)
                darea(i,j);

            for(j = nx/2-1; j >= 1; j--)
                darea(i,j);
        }
    }

    // write out areas
    err = gridwrite(afile, (void **)arr,RPINTDTYPE,nx,ny,dx,dy,bndbox,csize, -1., filetype);

    if(err != 0)
    {
        main_window->Log_Message("[aread8] Error, gridwrite failed");
    }

    //Clean up
    free(arr[0]);
    free(arr);

ERROR1:
    free(dir[0]);
    free(dir);

    return(err);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// For Help and documentation visit http://hydrology.usu.edu/taudem/taudem5/index.html
// function to compute area recursively
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void darea(int i, int j)
{
    if(print_many_messages)
        qDebug() << "INFO: Start darea";

    if(arr == nullptr)
    {
        main_window->Log_Message("[darea] Error arr is NULL");
        return;
    }

    if(dir == nullptr)
    {
        main_window->Log_Message("[darea] Error dir is NULL");
        return;
    }

    //Defined in "lsm.h"
    if(d1 == nullptr)
    {
        main_window->Log_Message("[darea] Error d1 is NULL");
        return;
    }

    //Defined in "lsm.h"
    if(d2 == nullptr)
    {
        main_window->Log_Message("[darea] Error d2 is NULL");
        return;
    }

    int in,jn,k,con=0;

    // con is a flag that signifies possible contaminatin of area due to edge effects
    if(arr[j][i] == 0)
    {
        // not on boundary
        if(i!=0 && i!=ny-1 && j!=0 && j!=nx-1 && dir[j][i]!= -1)   
        {
            arr[j][i] = 1;

            for(k=1; k<=8; k++)
            {
                in = i + d1[k];
                jn = j + d2[k];

                // test if neighbor drains towards cell excluding boundaryies
                if(dir[jn][in] > 0 && (dir[jn][in]-k==4||dir[jn][in]-k==-4))
                {
                    darea(in,jn);

                    if(arr[jn][in] < 0)
                    {
                        con = -1;
                    }
                    else
                    {
                        arr[j][i] = arr[j][i] + arr[jn][in];
                    }
                }

                if(dir[jn][in] < 0)
                {
                    con = -1;
                }
            }
        }
    }
}
