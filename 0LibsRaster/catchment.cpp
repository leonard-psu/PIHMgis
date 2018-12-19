#include <QDebug>

#include <stdio.h>
#include "lsm.h"
#include "globals.h"


// User interface to PIHMgis v3.5
extern PIHMgisDialog *main_window;

int findIJCat(short **fdr, int i, int j, int *mIJ);

int trace(float **seg, short int **fdr, float **cat, int i, int j);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Called by CatchmentGrids
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int catchment(QString segFile, QString fdrFile, QString catFile){

    if(print_debug_messages)
        qDebug() << "INFO: Start catchment";

    try {

        if(segFile == nullptr)
        {
            main_window->Log_Message("[catchment] Error[1000] Invalid segFile.");
            return 1000;
        }
        if(fdrFile == nullptr)
        {
            main_window->Log_Message("[catchment] Error[1001] Invalid fdrFile.");
            return 1001;
        }
        if(catFile == nullptr)
        {
            main_window->Log_Message("[catchment] Error[1002] Invalid catFile.");
            return 1002;
        }
        if(segFile.length() < 1)
        {
            main_window->Log_Message("[catchment] Error[1000] Invalid segFile.");
            return 1000;
        }
        if(fdrFile.length() < 1)
        {
            main_window->Log_Message("[catchment] Error[1001] Invalid fdrFile.");
            return 1001;
        }
        if(catFile.length() < 1)
        {
            main_window->Log_Message("[catchment] Error[1002] Invalid catFile.");
            return 1002;
        }

        int mIJ[2];
        int err, err1, err2, err3, err4;

        err1 = gridread(fdrFile,(void ***)&dir,RPSHRDTYPE,&nx,&ny,&dx,&dy,bndbox,&csize,&mval,&filetype);
        if(err1 != 0)
        {
            main_window->Log_Message("[catchment] Error[1003] Failed to read fdrFile " + QString(fdrFile));
            return 1003;
        }

        err2 = gridread(segFile,(void ***)&elev,RPFLTDTYPE,&nx,&ny,&dx,&dy,bndbox,&csize,&mval,&filetype);
        if(err2 != 0)
        {
            main_window->Log_Message("[catchment] Error[1004] Failed to read elev segFile " + QString(segFile));
            return 1004;
        }

        err3 = gridread(segFile,(void ***)&slope,RPFLTDTYPE,&nx,&ny,&dx,&dy,bndbox,&csize,&mval,&filetype);
        if(err3 != 0)
        {
            main_window->Log_Message("[catchment] Error[1005] Failed to read slope segFile " + QString(segFile));
            return 1005;
        }

        for(int i=0; i < nx; i++)
        {
            for(int j=0; j < ny; j++)
            {
                if(slope[i][j] < 0)
                    slope[i][j] = 0;
            }
        }

        bool trace_error_found = false;
        bool findij_error_found = false;
        for(int i=0; i < nx; i++)
        {
            for(int j=0; j < ny; j++)
            {
                if(slope[i][j] == 0 && dir[i][j] != -1)
                {
                    int result2 = findIJCat(dir, i, j, mIJ);
                    if( result2 == -9999)
                    {
                        findij_error_found = true;
                    }

                    int result = trace(elev, dir, slope, mIJ[0], mIJ[1]);
                    if( result != -9999)
                    {
                        slope[i][j] = result;
                    }
                    else {
                        trace_error_found = true;
                    }
                }
            }
        }

        if(trace_error_found && findij_error_found)
        {
            main_window->Log_Message("[catchment] Error[1006] Errors found with trace and findIJCat");
            return 1006;
        }
        if(trace_error_found )
        {
            main_window->Log_Message("[catchment] Error[1007] Errors found with trace");
            return 1007;
        }
        if(findij_error_found)
        {
            main_window->Log_Message("[catchment] Error[1008] Errors found with findIJCat");
            return 1008;
        }

        err4 = gridwrite(catFile,(void **)slope,RPFLTDTYPE,nx,ny,dx,dy,bndbox,csize,mval,filetype);
        if(err4 != 0)
        {
            main_window->Log_Message("[catchment] Error[1009] Failed to write catFile " + QString(catFile));
            return 1009;
        }

        return 0;

    }
    catch (...)
    {
        qDebug() << "Error: catchment ";
    }

    return 1010;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Called by catchment (above)
// Since used as a recursive function, I'm using -9999 as error code check
// Used findIJCat function (below)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int trace(float **seg, short int **fdr, float **cat, int i, int j){

    if(print_many_messages)
        qDebug() << "INFO: Start trace";

    try {

        if(seg == nullptr)
        {
            main_window->Log_Message("[trace] Error seg is null ");
            return -9999;
        }
        if(fdr == nullptr)
        {
            main_window->Log_Message("[trace] Error fdr is null ");
            return -9999;
        }
        if(cat == nullptr)
        {
            main_window->Log_Message("[trace] Error cat is null ");
            return -9999;
        }
        if(i < 0)
        {
            main_window->Log_Message("[trace] Invalid i index < 0 ");
            return -9999;
        }
        if(i > 250000) //250000 is a guess
        {
            main_window->Log_Message("[trace] Invalid i index > 250000 ");
            return -9999;
        }
        if(j < 0)
        {
            main_window->Log_Message("[trace] Invalid j index < 0 ");
            return -9999;
        }
        if(j > 250000) //250000 is a guess
        {
            main_window->Log_Message("[trace] Invalid j index > 250000 ");
            return -9999;
        }

        int mIJ[2];

        if(seg[i][j] > 0)
        {
            return seg[i][j];
        }
        else if(cat[i][j] != 0)
        {
            return cat[i][j];
        }
        else if(fdr[i][j] == -1)
        {
            return fdr[i][j];
        }
        else
        {
            int result1 = findIJCat(fdr, i, j, mIJ);
            if(result1 == -9999)
            {
                main_window->Log_Message("[trace] findIJCat failed ");
                return -9999;
            }

            int result2 = trace(seg, fdr, cat, mIJ[0], mIJ[1]);
            if(result2 == -9999)
            {
                main_window->Log_Message("[trace] trace failed ");
                return -9999;
            }
            else
            {
                cat[i][j] = result2;
            }

        }

        return cat[i][j];

    } catch (...) {
        qDebug() << "Error: trace is returning w/o checking return -9999;";
    }

    return -9999;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Called by trace (above)
// Since used as a recursive function, I'm using -9999 as error code check
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int findIJCat(short **fdr, int i, int j, int *mIJ){

    if(print_many_messages)
        qDebug() << "INFO: Start findIJCat";

    try {

        if(fdr == nullptr)
        {
            main_window->Log_Message("[findIJCat] Error fdr is null ");
            return -9999;
        }
        if(mIJ == nullptr)
        {
            main_window->Log_Message("[findIJCat] Error mIJ is null ");
            return -9999;
        }

        //////////////////////////////////////////////////////////////////
        //Find i index
        //////////////////////////////////////////////////////////////////
        if(fdr[i][j] == 4 || fdr[i][j] == 5 || fdr[i][j] == 6)
        {
            mIJ[0] = i-1;
        }
        else if(fdr[i][j] == 2 || fdr[i][j] == 1 || fdr[i][j] == 8)
        {
            mIJ[0] = i+1;
        }
        else
        {
            mIJ[0] = i;
        }

        //////////////////////////////////////////////////////////////////
        //Find j index
        //////////////////////////////////////////////////////////////////
        if(fdr[i][j] == 4 || fdr[i][j] == 3 || fdr[i][j] == 2)
        {
            mIJ[1] = j-1;
        }
        else if(fdr[i][j] == 6 || fdr[i][j] == 7 || fdr[i][j] == 8)
        {
            mIJ[1] = j+1;
        }
        else
        {
            mIJ[1] = j;
        }

    } catch (...) {
        qDebug() << "Error: findIJCat is returning w/o checking";
        return -9999;
    }

    return 0 ;
}
