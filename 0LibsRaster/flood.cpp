// flood.c
// Program to implement flooding algorithm to assign flow directions and fill
// pits/pools in a DEM.  Uses ESRI arcview format IO files.  Modified from
// setdir2.c
// David G Tarboton
// Utah State University
//
// SINMAP package version 0.1 9/2/97

#include <QDebug>
#include "lsm.h"
#include "gridio.h"
#include "globals.h"


// User interface to PIHMgis v3.5
extern PIHMgisDialog *main_window;

int addstack(int i, int j);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Called by Fillpits
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int flood(QString demfile, QString newfile)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start flood";

    try {

        //Check input names
        if(demfile == nullptr)
        {
            main_window->Log_Message("[flood] Error[-1000] Invalid demfile ");
            return -1000;
        }
//        if(pointfile == nullptr)
//        {
//            main_window->Log_Message("[flood] Error[-1001] Invalid pointfile ");
//            return -1001;
//        }
        if(newfile == nullptr)
        {
            main_window->Log_Message("[flood] Error[-1002] Invalid newfile ");
            return -1002;
        }

        if(demfile.length() < 1)
        {
            main_window->Log_Message("[flood] Error[-1003] Invalid demfile " + demfile);
            return -1003;
        }
//        if(pointfile.length() < 1)
//        {
//            main_window->Log_Message("[flood] Error[-1004] Invalid pointfile " + pointfile);
//            return -1004;
//        }
        if(newfile.length() < 1)
        {
            main_window->Log_Message("[flood] Error[-1005] Invalid newfile " + newfile);
            return -1005;
        }

        // define directions
        d1[1]=0; d1[2]= -1; d1[3]= -1; d1[4]= -1; d1[5]=0; d1[6]=1; d1[7]=1; d1[8]=1;
        d2[1]=1; d2[2]=1; d2[3]=0; d2[4]= -1; d2[5]= -1; d2[6]= -1; d2[7]=0; d2[8]=1;

        int err = gridread(demfile,(void ***)&elev,RPFLTDTYPE,&nx,&ny,&dx,&dy,bndbox,&csize,&mval,&filetype);

        if(err != 0)
        {
            main_window->Log_Message("[flood] Error[-1006] grid read failed. Error code " + QString::number(err) + " for file " + demfile);
            return(err);
        }

        // allocate  dir and stack arrays
        dir = (short **) matalloc(nx, ny, RPSHRDTYPE);
        if(dir == nullptr)
        {
            main_window->Log_Message("[flood] Error[-1007] dir failed ");
            return -1007;
        }

        apool = (short **) matalloc(nx, ny, RPSHRDTYPE);
        if(apool == nullptr)
        {
            main_window->Log_Message("[flood] Error[-1008] apool failed ");
            return -1008;
        }

        istack = (int) (nx * ny * 0.1);
        pstack=istack;
        if(istack <= 0)
        {
            main_window->Log_Message("[flood] Error[-1009] Invalid istack value of " + QString::number(istack) );
            return -1009;
        }

        dn = (short *)malloc(sizeof(short) * istack);
        if(dn == nullptr)
        {
            main_window->Log_Message("[flood] Error[-1010] dn failed ");
            return -1010;
        }

        is = (short *)malloc(sizeof(short) * istack);
        if(is == nullptr)
        {
            main_window->Log_Message("[flood] Error[-1011] is failed ");
            free(dn);
            return -1011;
        }

        js = (short *)malloc(sizeof(short) * istack);
        if(js == nullptr)
        {
            main_window->Log_Message("[flood] Error[-1012] js failed ");
            free(dn);
            free(is);

            return -1012;
        }

        ipool = (short *)malloc(sizeof(short) * pstack);
        if(ipool == nullptr)
        {
            main_window->Log_Message("[flood] Error[-1013] ipool failed ");
            free(dn);
            free(is);
            free(js);

            return -1013;
        }

        jpool = (short *)malloc(sizeof(short) * pstack);
        if(jpool == nullptr)
        {
            main_window->Log_Message("[flood] Error[-1014] jpool failed ");
            free(dn);
            free(is);
            free(js);
            free(ipool);

            return -1014;
        }

        i1=0;
        i2=0;
        n1=nx;
        n2=ny;  /*  full grid  */

        if(print_debug_messages)
        {
            main_window->Log_Message("[flood] Grid size: " + QString::number(n1) + " x " + QString::number(n2));
        }

        int setdf_result = setdf(mval);

        //Clean up
        free(dn);
        free(is);
        free(js);
        free(ipool);
        free(jpool);
        free(apool[0]);
        free(apool);

        if(setdf_result != 0)
        {
            main_window->Log_Message("[flood] Error[-2000] setdf failed ");
            return -2000;
        }


        // filetype=0;  0=ASCII 1=ARCVIEW proprietary

        main_window->Log_Message("[flood] Writing output");

        QByteArray newfname = newfile.toLatin1();
        char *newfile_char = newfname.data();

        err = gridwrite(newfile_char,(void **)elev,RPFLTDTYPE,nx,ny,dx,dy,bndbox,csize,mval,filetype);
        if(err != 0)
        {
            main_window->Log_Message("[flood] Error[2001] gridwrite failed ");
            return(err);
        }


    } catch (...) {

        qDebug() << "Error: flood is returning w/o checking";
    }

    return(0);  /*  ALL OK return from flood  */
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// setdf
// Called by flood above
// Note uses global variables dir, elev
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int setdf(float mval)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start setdf";

    int err = 0;

    try {

        if(dir == nullptr)
        {
            main_window->Log_Message("[setdf] Error[1000] dir is null ");
            return 1000;
        }

        if(elev == nullptr)
        {
            main_window->Log_Message("[setdf] Error[1001] elev is null ");
            return 1001;
        }

        int n,nflat,ni,ip,imin,jn,in,np1,nt = 0;
        float fact[9], per = 1.0;

        //  Initialize boundaries
        for(int i = i1; i < n1; i++)
        {
            dir[i][i2] = -1;
            dir[i][n2-1] = -1;
        }

        for(int i = i2; i < n2; i++)
        {
            dir[i1][i] = -1;
            dir[n1-1][i] = -1;
        }

        // initialize internal pointers
        for(int i = i2+1; i < n2-1; i++)
        {
            for(int j = i1+1; j < n1-1; j++)
            {
                if(elev[j][i] <= mval)
                    dir[j][i]= -1;
                else
                    dir[j][i] = 0;
            }
        }

        bool error_found = false;
        // Direction factors
        for(int k = 1; k <= 8; k++)
        {
            float bottom = sqrt(d1[k]*dy*d1[k]*dy+d2[k]*d2[k]*dx*dx);
            if(bottom <= 0)
            {
                error_found = true;
            }
            else if (isnan(bottom))
            {
                error_found = true;
            }
            else
            {
                fact[k] = (float)(1.0/bottom);
            }
        }

        if(error_found)
        {
            main_window->Log_Message("[setdf] Error[1002] Invalid value created with fact calculations ");
            return 1002;
        }

        //Set positive slope directions - store unresolved on stack

        bool error_set = false;
        bool error_addstack = false;
        nis=0;
        for(int i = i2+1; i < n2-1; i++)
        {
            for(int j = i1+1; j < n1-1; j++)
            {
                if(elev[j][i] > mval)
                {
                    err = set(i,j,fact,mval);
                    if(err != 0)
                        error_set = true;
                }

                // Put unresolved pixels on stack
                if(dir[j][i] == 0)
                {
                    err = addstack(i,j);
                    if(err != 0)
                        error_addstack = true;
                }
            }
        }

        if(error_addstack)
        {
            main_window->Log_Message("[setdf] Error[1003] Add stack error. Aborting...  ");
            return 1003;
        }

        if(error_set)
        {
            main_window->Log_Message("[setdf] Error[1004] Set error. Aborting...  ");
            return 1004;
        }

        nflat = nis;

        // routine to drain flats to neighbors
        imin = vdn(nflat);
        n = nis;

        main_window->Log_Message("[setdf] Number of pits to resolve: " + QString::number(n));

        np1 = n;
        nt = np1 * (1-per/100);

        // initialize apool to zero
        for(int i = i2; i < n2; i++)
        {
            for(int j = i1; j < n1; j++)
            {
                apool[j][i] = 0;
            }
        }

        bool pool_error_found = false;
        error_addstack = false;
        error_set = false;

        while(nis > 0)
        {
            int i = is[imin];
            int j = js[imin];

            pooln = 1;
            npool = 0;
            nf = 0;     // reset flag to that new min elev is found
            int err_pool = pool(i,j);  // Recursive call on unresolved point with lowest elevation
            if(err_pool != 0)
            {
                pool_error_found = true;
                nis = -1;
            }

            if(!pool_error_found)
            {
                for(ip = 1; ip <= npool; ip++)
                {
                    i = ipool[ip];
                    j = jpool[ip];

                    for(int k = 1; k <= 8; k++)
                    {
                        jn = j + d2[k];
                        in = i + d1[k];

                        if(apool[jn][in] != pooln)  //  neighbor not in pool
                        {
                            et = max2(elev[j][i],elev[jn][in]);

                            if(nf == 0)  // this is the first edge found
                            {
                                emin=et;
                                nf=1;
                            }
                            else
                            {
                                if(emin > et)
                                {
                                    emin = et;
                                }
                            }
                        }
                    }
                }

                //  Fill the pool
                for(int k = 1; k <= npool; k++)
                {
                    i = ipool[k];
                    j = jpool[k];

                    if(elev[j][i] <= emin)
                    {
                        if(dir[j][i] > 0)   // Can be in pool, but not flat
                        {
                            dir[j][i] = 0;

                            // Add to stack
                            err = addstack(i,j);
                            if(err != 0)
                            {
                                error_addstack = true;
                                nis = -1;
                            }
                        }

                        for(ip=1; ip <=8; ip++)
                        {
                            jn = j+d2[ip];
                            in = i+d1[ip];
                            if(elev[jn][in] > elev[j][i] && dir[jn][in] > 0)
                            {
                                dir[jn][in] = 0;

                                err = addstack(in,jn);
                                if(err != 0)
                                {
                                    error_addstack = true;
                                    nis = -1;
                                }
                            }
                        }

                        elev[j][i] =emin;

                    }
                    apool[j][i]=0;  // Reinitialize for next time round
                }

                // reset unresolved stack
                ni=0;
                for(ip = 1; ip <= nis; ip++)
                {
                    err = set(is[ip], js[ip], fact, mval);
                    if(err != 0)
                    {
                        error_set = false;
                        nis = -1;
                    }

                    if(dir[js[ip]][is[ip]] == 0)  // still on stack
                    {
                        ni++;
                        is[ni] = is[ip];
                        js[ni] = js[ip];
                    }
                }

                n = nis;
                imin = vdn(ni);

                if(nis < nt)
                {
                    main_window->Log_Message("[setdf] Percentage done: " + QString::number(per));

                    per = per+1;
                    nt = np1*(1-per/100);
                }

            } //if(!pool_error_found)

        }  //end of while

        if(error_addstack)
        {
            main_window->Log_Message("[setdf] Error[1004] Add stack error. Aborting...  ");
            return 1004;
        }

        if(error_set)
        {
            main_window->Log_Message("[setdf] Error[1005] Set error. Aborting...  ");
            return 1005;
        }


    } catch (...)
    {
        qDebug() << "Error: setdf is returning w/o checking";
    }

    return(err);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// vdn
// Called by setdf above
// Note uses global variables elev, nis
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int vdn(int n)
{
    if(print_many_messages)
        qDebug() << "INFO: Start vdn";


    if(elev == nullptr)
    {
        main_window->Log_Message("[vdn] Error[1000] elev is null ");
        return 1000;
    }

    if(dir == nullptr)
    {
        main_window->Log_Message("[vdn] Error[1001] dir is null ");
        return 1001;
    }

    if(dn == nullptr)
    {
        main_window->Log_Message("[vdn] Error[1002] dn is null ");
        return 1002;
    }

    if(js == nullptr)
    {
        main_window->Log_Message("[vdn] Error[1003] js is null ");
        return 1003;
    }

    if(is == nullptr)
    {
        main_window->Log_Message("[vdn] Error[1004] is is null ");
        return 1004;
    }

    if(d1 == nullptr)
    {
        main_window->Log_Message("[vdn] Error[1005] d1 is null ");
        return 1005;
    }

    if(d2 == nullptr)
    {
        main_window->Log_Message("[vdn] Error[1006] d2 is null ");
        return 1006;
    }

    int imin = 0;
    float ed = 0;
    nis = n;

    do
    {
        n = nis;
        nis = 0;

        for(int ip = 1; ip <= n; ip++)
        {
            dn[ip] = 0;
        }

        for(int k = 1; k <= 7; k = k+2)
        {
            for(int ip = 1; ip <= n; ip++)
            {
                ed = elev[js[ip]][is[ip]] - elev[js[ip] + d2[k]][is[ip] + d1[k]];

                if(ed >= 0.0 && dir[js[ip] + d2[k]][is[ip] + d1[k]] != 0 && dn[ip] == 0)
                {
                    dn[ip] = k;
                }
            }
        }

        for(int k = 2; k <= 8; k = k+2)
        {
            for(int ip = 1; ip <= n; ip++)
            {
                ed = elev[js[ip]][is[ip]] - elev[js[ip] + d2[k]][is[ip] + d1[k]];

                if(ed >= 0.0 && dir[js[ip] + d2[k]][is[ip] + d1[k]] != 0 && dn[ip] == 0)
                {
                    dn[ip]=k;
                }
            }
        }

        imin = 1;  //location of point on stack with lowest elevation

        for(int ip=1; ip <= n; ip++)
        {
            if(dn[ip] > 0)
            {
                dir[js[ip]][is[ip]] = dn[ip];
            }
            else
            {
                nis++;

                is[nis] = is[ip];
                js[nis] = js[ip];

                if( elev[js[nis]][is[nis]] < elev[js[imin]][is[imin]] )
                {
                    imin=nis;
                }
            }
        }

    } while(nis < n);

    return(imin);
}   

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// set
// Called by flood above, setdir
// Note uses global variables elev, dir
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int set(int i,int j,float *fact,float mval)
{
    if(print_many_messages)
        qDebug() << "INFO: Start set";

    try {

        if(dir == nullptr)
        {
            main_window->Log_Message("[set] Error[1000] dir is null ");
            return 1000;
        }

        if(elev == nullptr)
        {
            main_window->Log_Message("[set] Error[1001] elev is null ");
            return 1001;
        }

        if(fact == nullptr)
        {
            main_window->Log_Message("[set] Error[1002] fact is null ");
            return 1002;
        }

        if(d1 == nullptr)
        {
            main_window->Log_Message("[set] Error[1003] d1 is null ");
            return 1003;
        }

        if(d2 == nullptr)
        {
            main_window->Log_Message("[set] Error[1004] d2 is null ");
            return 1004;
        }

        if(i < 0 )
        {
            main_window->Log_Message("[set] Error[1005] Invalid i < 0 ");
            return 1005;
        }

        if(j < 0 )
        {
            main_window->Log_Message("[set] Error[1006] Invalid j < 0 ");
            return 1006;
        }

        float slope,smax = 0;

        dir[j][i] = 0;  // This necessary for repeat passes after level raised
        smax = 0.0;

        for(int k=1; k <= 8; k++)
        {
            if(elev[j + d2[k]][i + d1[k]] <= mval)
            {
                dir[j][i] = -1;
            }

            slope = fact[k] * (elev[j][i] - elev[j + d2[k]][ i + d1[k]]);

            if(slope > smax && dir[j][i] != -1)
            {
                smax=slope;
                dir[j][i]=k;
            }
        }

    } catch (...) {
        qDebug() << "Error: set is returning w/o checking";
        return -9000;

    }

    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// pool
// Called by setdf above
// function to compute pool recursively and at the same time determine the minimum elevation of the edge.
// Note uses global variables apool, dir, npool
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int pool(int i,int j)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start pool";

    try {

        if(i < 0 )
        {
            main_window->Log_Message("[pool] Error[1000] Invalid i < 0 ");
            return 1000;
        }
        if(j < 0 )
        {
            main_window->Log_Message("[pool] Error[1001] Invalid j < 0 ");
            return 1001;
        }
        if(apool == nullptr )
        {
            main_window->Log_Message("[pool] Error[1002] apool is null ");
            return 1002;
        }
        if(ipool == nullptr )
        {
            main_window->Log_Message("[pool] Error[1003] ipool is null ");
            return 1003;
        }
        if(jpool == nullptr)
        {
            main_window->Log_Message("[pool] Error[1004] jpool is null ");
            return 1004;
        }
        if(dir == nullptr )
        {
            main_window->Log_Message("[pool] Error[1005] dir is null ");
            return 1005;
        }
        if(elev == nullptr)
        {
            main_window->Log_Message("[pool] Error[1006] elev is null ");
            return 1006;
        }

        int in,jn,k = 0;

        if(apool[j][i] <= 0)   // not already part of a pool not on boundary
        {
            if(dir[j][i] != -1)  // check only dir since dir was initialized
            {
                apool[j][i] = pooln;  // apool assigned pool number
                npool = npool+1;

                if(npool >= pstack)
                {
                    if(pstack < (nx*ny))
                    {
                        // Try enlarging
                        main_window->Log_Message("[pool] Enlarging pool stack ");

                        pstack = (int) (pstack + nx * ny * 0.1);

                        if(pstack > nx*ny)
                        {
                            main_window->Log_Message("[pool] ERROR[14] Pool stack too large, exiting ");
                            return(14);
                        }

                        ipool = (short *)realloc(ipool, sizeof(short) * pstack);
                        jpool = (short *)realloc(jpool, sizeof(short) * pstack);
                        if(ipool == nullptr || jpool == nullptr)
                        {
                            main_window->Log_Message("[pool] ERROR[15] Cannot reallocate pool stack, exiting ");
                            return(15);
                        }
                    }
                    else
                    {
                        main_window->Log_Message("[pool] ERROR[16] Could not enlarge Pool stack");
                        return(16);
                    }
                }

                ipool[npool] = i;
                jpool[npool] = j;

                for(int k = 1; k <= 8; k++)
                {
                    in = i + d1[k];
                    jn = j + d2[k];

                    // test if neighbor drains towards cell excluding boundaries
                    if((dir[jn][in] > 0 && (dir[jn][in]-k==4||dir[jn][in]-k==-4))
                            || (dir[jn][in] == 0 && elev[jn][in] >= elev[j][i]))
                    {
                        pool(in,jn);
                    }
                }
            }
        }

    } catch (...) {
        qDebug() << "Error: pool is returning w/o checking";
        return -5000;
    }

    return(0);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Return min value
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float min2(float e1,float e2)
{ 
    float em;
    em=e1;
    if(e2 < em)
        em=e2;

    return(em);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Return max value
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float max2(float e1,float e2)
{ 
    float em;
    em=e1;
    if(e2 > em)
        em=e2;
    return(em);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// addstack
// Note uses global variables is, js, dn
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int addstack(int i, int j)
{
    if(print_many_messages)
        qDebug() << "INFO: Start addstack";

    try {

        if(i < 0 )
        {
            main_window->Log_Message("[addstack] Error[1000] Invalid i < 0 ");
            return 1000;
        }

        if(j < 0 )
        {
            main_window->Log_Message("[addstack] Error[1001] Invalid j < 0 ");
            return 1001;
        }

        // Routine to add entry to is, js stack, enlarging if necessary
        nis = nis+1;

        if(nis < 0)
        {
            main_window->Log_Message("[addstack] ERROR[1002] nis < 0 ");
            return 1002;
        }

        if(nis >= istack )
        {
            // Try enlarging
            istack = (int) (istack + nx * ny * 0.1);

            if(istack > nx*ny)
            {
                main_window->Log_Message("[addstack] ERROR[1003] is,js stack too large, exiting ... ");
                return(1003);
            }

            if(istack <= 0)
            {
                main_window->Log_Message("[addstack] ERROR[1004] istack <= 0 ");
                return(1004);
            }

            main_window->Log_Message("[addstack] Enlarging is,js stack ");

            is = (short *)realloc(is, sizeof(short) * istack);
            if(is == nullptr)
            {
                main_window->Log_Message("[addstack] ERROR[1005] is null. Could not enlarge stack.");
                return 1005;
            }

            js = (short *)realloc(js, sizeof(short) * istack);
            if(js == nullptr)
            {
                main_window->Log_Message("[addstack] ERROR[1006] js null. Could not enlarge stack.");
                return 1006;
            }

            dn = (short *)realloc(dn, sizeof(short) * istack);
            if(dn == nullptr)
            {
                main_window->Log_Message("[addstack] ERROR[1007] dn null. Could not enlarge stack.");
                return 1007;
            }
        }

        if(is == nullptr)
        {
            main_window->Log_Message("[addstack] ERROR[1008] is null ");
            return 1008;
        }

        if(js == nullptr)
        {
            main_window->Log_Message("[addstack] ERROR[1009] js null ");
            return 1009;
        }

        is[nis] = i;
        js[nis] = j;


    } catch (...) {
        qDebug() << "Error: addstack is returning w/o checking";
        return -5000;
    }

    return(0);
}

