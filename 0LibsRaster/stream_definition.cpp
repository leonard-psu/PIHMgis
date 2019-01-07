#include <QDebug>
#include <stdio.h>

#include "lsm.h"
#include "gridio.h"
#include "globals.h"


// User interface to PIHMgis v3.5
extern PIHMgisDialog *main_window;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// stream_definition
// Used in streamgrids
// method = 1 => Area Threshold
// method = 2 => strahler order Threshold
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int stream_definition(QString aread8File, QString rivFile, int method, int threshold)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start stream_definition";

    try {

        if(aread8File == nullptr)
        {
            main_window->Log_Message("[stream_definition] Error[-1000] Invalid aread8File " );
            return -1000;
        }
        if(rivFile == nullptr)
        {
            main_window->Log_Message("[stream_definition] Error[-1001] Invalid rivFile " );
            return -1001;
        }

        if(aread8File.length() < 1)
        {
            main_window->Log_Message("[stream_definition] Error[-1002] Invalid aread8File " );
            return -1002;
        }
        if(rivFile.length() < 1)
        {
            main_window->Log_Message("[stream_definition] Error[-1003] Invalid rivFile " );
            return -1003;
        }

        if(method==1)
        {

            int err = gridread(aread8File,(void ***)&elev,RPFLTDTYPE,&nx,&ny,&dx,&dy,bndbox,&csize,&mval,&filetype);

            if(err != 0)
            {
                main_window->Log_Message("[stream_definition] Error[-2000] grid read failed " + aread8File);
                return(err);
            }

            if(elev == nullptr)
            {
                main_window->Log_Message("[stream_definition] Error[-2001] elev is null " + aread8File);
                return -2001;
            }

            for(int i=0; i < nx; i++)
            {
                for(int j=0; j < ny; j++)
                {
                    if(elev[i][j] >= threshold)
                    {
                        elev[i][j] = 1;
                    }
                    else
                    {
                        elev[i][j] = mval;
                    }
                }
            }

            main_window->Log_Message("[stream_definition] Writing output " + aread8File);

            err = gridwrite(rivFile,(void **)elev,RPFLTDTYPE,nx,ny,dx,dy,bndbox,csize,mval,filetype);

            free(elev);
            elev = nullptr;

            if(err != 0)
            {
                main_window->Log_Message("[stream_definition] grid write failed " + aread8File);
                return(err);
            }

        }
        else if(method==2)
        {
            main_window->Log_Message("[stream_definition] Method 2 not yet implemented " + aread8File);
        }
        else
        {
            main_window->Log_Message("[stream_definition] Method not found " + aread8File);
        }

    }
    catch (...)
    {
        qDebug() << "Error: stream_definition is returning w/o checking";
        return -9000;
    }

    return(0);
}


