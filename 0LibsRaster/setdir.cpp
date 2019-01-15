// C version of setdir.c. This does not fill pits, it is intended for use AFTER
// d8.c which fills pits.  Input is a dem file name.  Output is
// slope and dinf angle files.   This version implements Garbrecht flow directions
// for flats.

// David G Tarboton
// Utah State University

#include <QDebug>
#include "lsm.h"
#include "globals.h"
#include <cmath>

// This include declares all necessary global variables
int incfall(int n, float *elev1, short *s1,int **spos, int iter, int *sloc);
int incrise(int n, float *elev1, short *s2,int **spos, int iter, int *sloc);
int set2(int i,int j,float *fact,float *elev1, float *elev2, int iter, int **spos, short *s);
int flatrout(int n,int *sloc, short *s,int **spos,int iter,float *elev1,float *elev2, float *fact, int ns);
int sloped8(void);


// User interface to PIHMgis v3.5
extern PIHMgisDialog *main_window;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// setdird8
// Visit Taudem website for details.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int setdird8(QString demfile, QString pfile, QString slopefile)
{ 
    if(print_debug_messages)
        qDebug() << "INFO: Start setdird8";

    try {

        //Check input names
        if(demfile == nullptr)
        {
            main_window->Log_Message("[setdird8] Error[-1000] Invalid demfile " );
            return -1000;
        }
        if(pfile == nullptr)
        {
            main_window->Log_Message("[setdird8] Error[-1001] Invalid pointfile " );
            return -1001;
        }
        if(slopefile == nullptr)
        {
            main_window->Log_Message("[setdird8] Error[-1002] Invalid newfile " );
            return -1002;
        }

        if(demfile.length() < 1)
        {
            main_window->Log_Message("[setdird8] Error[-1003] Invalid demfile " + demfile);
            return -1003;
        }
        if(pfile.length() < 1)
        {
            main_window->Log_Message("[setdird8] Error[-1004] Invalid pointfile " + pfile);
            return -1004;
        }
        if(slopefile.length() < 1)
        {
            main_window->Log_Message("[setdird8] Error[-1005] Invalid newfile " + slopefile);
            return -1005;
        }

        int err,filetype = 0;
        float mval;
        double bndbox[4],csize;

        /* define directions */
        d1[1]=0; d1[2]= -1; d1[3]= -1; d1[4]= -1; d1[5]=0; d1[6]=1; d1[7]=1; d1[8]=1;
        d2[1]=1; d2[2]=1; d2[3]=0; d2[4]= -1; d2[5]= -1; d2[6]= -1; d2[7]=0; d2[8]=1;

        err = gridread(demfile,(void ***)&elev,RPFLTDTYPE,&nx,&ny,&dx,&dy, bndbox,&csize,&mval,&filetype);

        if(err != 0)
        {
            main_window->Log_Message("[setdird8] Error[" + QString::number(err) + "] gridread Failed  ");

            free(elev[0]);
            free(elev);
            return(err);
        }

        //  allocate  dir and stack arrays
        dir = (short **) matalloc(nx, ny, RPSHRDTYPE);
        if(dir == nullptr)
        {
            main_window->Log_Message("[setdird8] Error[-2000] matalloc failed  ");

            free(elev[0]);
            free(elev);
            return(err);
        }

        i1=0;
        i2=0;
        n1=nx;
        n2=ny;  //full grid

        err = setdfnoflood(mval);
        if(err != 0)
        {
            main_window->Log_Message("[setdird8] Error[-2001] setdfnoflood failed  ");

            free(elev[0]);
            free(elev);
            free(dir[0]);
            free(dir);
            return(err);
        }

        err = gridwrite(pfile,(void **)dir,RPSHRDTYPE,nx,ny,dx,dy,bndbox,csize,-1,filetype);
        if(err != 0)
        {
            main_window->Log_Message("[setdird8] Error[-2002] gridwrite failed  ");

            free(elev[0]);
            free(elev);
            free(dir[0]);
            free(dir);
            return(err);
        }

        // allocate memory for slope
        slope = (float **) matalloc(nx, ny, RPFLTDTYPE);
        if(slope == nullptr)
        {
            main_window->Log_Message("[setdird8] Error[-2003] slope failed  ");

            free(elev[0]);
            free(elev);
            free(dir[0]);
            free(dir);
            return(err);
        }

        err = sloped8();
        if(err != 0)
        {
            main_window->Log_Message("[setdird8] Error[-2004] sloped8 failed  ");

            free(elev[0]);
            free(elev);
            free(dir[0]);
            free(dir);
            return(err);
        }

        err = gridwrite(slopefile,(void **)slope,RPFLTDTYPE,nx,ny,dx,dy,bndbox,csize,-1.,filetype);
        if (err != 0)
        {
            main_window->Log_Message("[setdird8] Error[-2005] gridwrite failed  ");
            free(elev[0]);
            free(elev);
            free(dir[0]);
            free(dir);
            free(slope[0]);
            free(slope);
            return(err);
        }


        //Clean up
        free(elev[0]);
        free(elev);
        free(dir[0]);
        free(dir);
        free(slope[0]);
        free(slope);


    } catch (...) {
        qDebug() << "Error: setdird8 is returning w/o checking";
        return -9000;
    }

    return(0);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This version is stripped of pit filling
// Visit Taudem website for details.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int setdfnoflood(float mval)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start setdfnoflood";

    try {
        int ip, n, iter = 0;
        float fact[9];
        short *s;  //  variables for flat draining
        int **spos, *sloc;
        float *elev2;

        if(dir == nullptr)
        {
            main_window->Log_Message("[setdfnoflood] Error[-1000] dir nullptr ");
            return -1000;
        }
        if(elev == nullptr)
        {
            main_window->Log_Message("[setdfnoflood] Error[-1001] elev nullptr ");
            return -1001;
        }
        if(d1 == nullptr)
        {
            main_window->Log_Message("[setdfnoflood] Error[-1002] d1 nullptr ");
            return -1002;
        }
        if(d2 == nullptr)
        {
            main_window->Log_Message("[setdfnoflood] Error[-1003] d2 nullptr ");
            return -1003;
        }
        if(fact == nullptr)
        {
            main_window->Log_Message("[setdfnoflood] Error[-1004] fact nullptr ");
            return -1004;
        }
        if(elev == nullptr)
        {
            main_window->Log_Message("[setdfnoflood] Error[-1005] elev nullptr ");
            return -1005;
        }

        // Initialize boundaries
        for(int i = i1; i< n1; i++)
        {
            dir[i][0] = -1;
            dir[i][n2-1] = -1;
        }

        for(int i = i2; i < n2; i++)
        {
            dir[0][i]= -1;
            dir[n1-1][i]= -1;
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
        for(int k=1; k<= 8; k++)
        {
            float bottom = sqrt(d1[k]*dy*d1[k]*dy+d2[k]*d2[k]*dx*dx);
            if(bottom <= 0)
            {
                error_found = true;
            }
            else if (std::isnan(bottom))
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
            main_window->Log_Message("[setdfnoflood] Error[-2000] error found calculating fact ");
            return -2000;
        }

        error_found = false;
        // Set positive slope directions
        n=0;
        for(int i = i2+1; i < n2-1; i++)
        {
            for(int j = i1+1; j < n1-1; j++)
            {
                if(elev[j][i] > mval)
                {
                    int err = set(i,j,fact,mval);
                    if( err != 0)
                    {
                        error_found = true;
                    }

                    if(dir[j][i] == 0)
                        n++;
                }
            }
        }

        if(error_found)
        {
            main_window->Log_Message("[setdfnoflood] Error[-3000] error with set ");
            return -3000;
        }

        if(n > 0)
        {

            iter=1;

            main_window->Log_Message("[setdfnoflood] Resolving " + QString::number(n) + "Flats, Iteration: " + QString::number(iter));

            spos = (int **) matalloc(nx, ny, RPINTDTYPE);
            if(spos == nullptr)
            {
                main_window->Log_Message("[setdfnoflood] Error[-1004] spos nullptr ");
                return -3004;
            }

            dn = (short *)malloc(sizeof(short) * n);
            if(dn == nullptr)
            {
                main_window->Log_Message("[setdfnoflood] Error[-1005] dn nullptr ");
                return -3005;
            }

            is = (short *)malloc(sizeof(short) * n);
            if(is == nullptr)
            {
                main_window->Log_Message("[setdfnoflood] Error[-1006] is nullptr ");
                free(dn);
                return -3006;
            }

            js = (short *)malloc(sizeof(short) * n);
            if(js == nullptr)
            {
                main_window->Log_Message("[setdfnoflood] Error[-1007] js nullptr ");
                free(dn);
                free(is);

                return -3007;
            }

            s = (short *)malloc(sizeof(short) * n);
            if(s == nullptr)
            {
                main_window->Log_Message("[setdfnoflood] Error[-1008] s nullptr ");
                free(dn);
                free(is);
                free(js);

                return -3008;
            }

            sloc = (int *)malloc(sizeof(int) * n);
            if(sloc == nullptr)
            {
                main_window->Log_Message("[setdfnoflood] Error[-1009] sloc nullptr ");
                free(dn);
                free(is);
                free(js);
                free(s);
                return -3009;
            }

            elev2 = (float *)malloc(sizeof(float) *n);
            if(elev2 == nullptr)
            {
                main_window->Log_Message("[setdfnoflood] Error[-1010] elev2 nullptr ");
                free(dn);
                free(is);
                free(js);
                free(s);
                free(sloc);

                return -3010;
            }

            //  Put unresolved pixels on stack
            ip=0;
            for(int i=i2; i< n2; i++)
            {
                for(int j=i1; j<n1; j++)
                {
                    spos[j][i]=-1;   // Initialize stack position
                    if(dir[j][i] == 0)
                    {
                        is[ip] = i;
                        js[ip] = j;
                        dn[ip] = 0;
                        sloc[ip] = ip;

                        // Initialize the stage 1 array for flat routing
                        s[ip] = 1;
                        spos[j][i] = ip;  // Pointer for back tracking
                        ip++;

                        if(ip > n)
                        {
                            main_window->Log_Message("[setdfnoflood] PROBLEM - Stack logic");
                        }

                    }
                }
            }

            int err = flatrout(n,sloc,s,spos,iter,elev2,elev2,fact,n);
            if(err != 0)
            {
                main_window->Log_Message("[setdfnoflood] Error[-1011] flatrout failed ");

                free(spos[0]);
                free(spos);
                free(elev2);
                free(dn);
                free(is);
                free(js);
                free(s);
                free(sloc);
                return -3011;
            }


            //  The direction 9 was used to flag pits.  Set these to 0
            for(int i = i2; i < n2; i++)
            {
                for(int j = i1; j < n1; j++)
                {
                    if(dir[j][i] == 9)
                        dir[j][i]=0;
                }

            }

            free(spos[0]);
            free(spos);
            free(elev2);
            free(dn);
            free(is);
            free(js);
            free(s);
            free(sloc);

            main_window->Log_Message("[setdfnoflood] Done iteration " + QString::number(iter) + " Flats resolved " + QString::number(n));

        } // End if n > 0

    } catch (...) {
        qDebug() << "Error: setdir is returning w/o checking";
        return -9000;
    }

    return(0);

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// flatrout
// Visit Taudem website for details.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int flatrout(int n, int *sloc, short *s, int **spos, int iter, float *elev1, float *elev2, float *fact, int ns)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start flatrout";

    try {

        if(sloc == nullptr)
        {
            main_window->Log_Message("[flatrout] Error[-1000] sloc nullptr ");
            return -1000;
        }
        if(s == nullptr)
        {
            main_window->Log_Message("[flatrout] Error[-1001] s nullptr ");
            return -1001;
        }
        if(spos == nullptr)
        {
            main_window->Log_Message("[flatrout] Error[-1002] spos nullptr ");
            return -1002;
        }
        if(elev1 == nullptr)
        {
            main_window->Log_Message("[flatrout] Error[-1003] elev1 nullptr ");
            return -1003;
        }
        if(elev2 == nullptr)
        {
            main_window->Log_Message("[flatrout] Error[-1004] elev2 nullptr ");
            return -1004;
        }
        if(fact == nullptr)
        {
            main_window->Log_Message("[flatrout] Error[-1005] fact nullptr ");
            return -1005;
        }

        int ip,nu, *sloc2,ipp = 0;
        float *elev3;

        int err = incfall(n,elev1,s,spos,iter,sloc);
        if(err != 0)
        {
            main_window->Log_Message("[flatrout] Error[-1006] incfall failed ");
            return -1006;
        }

        for(ip = 0; ip < n; ip++)
        {
            elev2[sloc[ip]] = (float)(s[sloc[ip]]);
            s[sloc[ip]] = 0;   // Initialize for pass 2
        }

        err = incrise(n,elev1,s,spos,iter,sloc);
        if(err != 0)
        {
            main_window->Log_Message("[flatrout] Error[-1007] incrise failed ");
            return -1007;
        }

        for(ip = 0; ip < n; ip++)
        {
            elev2[sloc[ip]] += (float)(s[sloc[ip]]);
        }

        bool error_found = false;
        nu=0;
        for(ip = 0; ip < n; ip++)
        {
            err = set2(is[sloc[ip]],js[sloc[ip]],fact,elev1,elev2,iter,spos,s);
            if( err != 0)
            {
                error_found = true;
            }
            if(dir[js[sloc[ip]]][is[sloc[ip]]] == 0)
            {
                nu++;
            }
        }

        if(error_found)
        {
            main_window->Log_Message("[flatrout] Error[-1007] incrise failed ");
            return -1007;
        }


        if(nu > 0)
        {
            //  Iterate Recursively
            //  Now resolve flats following the Procedure of Garbrecht and Martz, Journal of Hydrology, 1997.

            iter = iter+1;

            main_window->Log_Message("[flatrout] Resolving " + QString::number(nu) + " Flats, Iteration: " + QString::number(iter));

            sloc2 = (int *)malloc(sizeof(int) * nu);
            if(sloc2 == nullptr)
            {
                main_window->Log_Message("[flatrout] Error[-1008] sloc2 nullptr ");
                return -1008;
            }

            elev3 = (float *)malloc(sizeof(float) *ns);
            if(elev3 == nullptr)
            {
                main_window->Log_Message("[flatrout] Error[-1009] elev3 nullptr ");
                free(sloc2);
                return -1009;
            }

            //  Initialize elev3
            for(ip = 0; ip < ns; ip++)
            {
                elev3[ip] = 0.0;
            }

            //  Put unresolved pixels on new stacks - keeping in same positions

            ipp=0;
            for(ip=0; ip<n; ip++)
            {
                if(dir[js[sloc[ip]]][is[sloc[ip]]] == 0)
                {
                    sloc2[ipp] = sloc[ip];

                    // Initialize the stage 1 array for flat routing
                    s[sloc[ip]] = 1;
                    ipp++;

                    if(ipp > nu)
                    {
                        main_window->Log_Message("[flatrout] PROBLEM - Stack logic ");
                        error_found = true;
                    }

                }
                else
                {
                    s[sloc[ip]] = -1;  // Used to designate out of remaining flat on higher iterations
                }

                dn[sloc[ip]] = 0;  //  Reinitialize for next time round.
            }

            err = flatrout(nu,sloc2,s,spos,iter,elev2,elev3,fact,ns);

            free(sloc2);
            free(elev3);

            if(err != 0)
            {
                main_window->Log_Message("[flatrout] Error[-1008] flatrout failed ");
                return -1008;
            }

            if(error_found)
            {
                main_window->Log_Message("[flatrout] Error[-1009] logic failure ");
                return -1009;
            }

            main_window->Log_Message("[flatrout] Done iteration " + QString::number(iter) + " Flats resolved: " + QString::number(n));

        } //  end if nu > 0


    } catch (...)
    {
        qDebug() << "Error: flatrout is returning w/o checking";
        return -5000;
    }

    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// incfall
// Visit Taudem website for details.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int incfall(int n, float *elev1, short *s1, int **spos, int iter, int *sloc)
{
    if(print_many_messages)
        qDebug() << "INFO: Start incfall";

    try {

        if(elev1 == nullptr)
        {
            main_window->Log_Message("[incfall] Error[-1000] elev1 nullptr ");
            return -1000;
        }
        if(s1 == nullptr)
        {
            main_window->Log_Message("[incfall] Error[-1001] s1 nullptr ");
            return -1001;
        }
        if(spos == nullptr)
        {
            main_window->Log_Message("[incfall] Error[-1002] spos nullptr ");
            return -1002;
        }
        if(sloc == nullptr)
        {
            main_window->Log_Message("[incfall] Error[-1003] sloc nullptr ");
            return -1003;
        }
        if(d1 == nullptr)
        {
            main_window->Log_Message("[incfall] Error[-1004] d1 nullptr ");
            return -1004;
        }
        if(d2 == nullptr)
        {
            main_window->Log_Message("[incfall] Error[-1005] d2 nullptr ");
            return -1005;
        }
        if(elev == nullptr)
        {
            main_window->Log_Message("[incfall] Error[-1006] elev nullptr ");
            return -1006;
        }
        if(is == nullptr)
        {
            main_window->Log_Message("[incfall] Error[-1007] is nullptr ");
            return -1007;
        }
        if(is == nullptr)
        {
            main_window->Log_Message("[incfall] Error[-1008] is nullptr ");
            return -1008;
        }

        // This routine implements drainage towards lower areas - stage 1
        int done=0,donothing,k,ip,ninc,nincold,spn = 0;
        short st=1,i,j,in,jn = 0;
        float ed = 0;
        nincold= -1;

        while(done < 1)
        {
            done=1;
            ninc=0;

            for(ip = 0; ip < n; ip++)
            {
                // if adjacent to same level or lower that drains or adjacent to pixel with s1 < st and dir not set do nothing
                donothing = 0;
                j = js[sloc[ip]];
                i = is[sloc[ip]];

                for(k = 1; k <= 8; k++)
                {
                    jn = j + d2[k];
                    in = i + d1[k];

                    spn = spos[jn][in];

                    if(iter <= 1)
                    {
                        ed = elev[j][i] - elev[jn][in];
                    }
                    else
                    {
                        ed = elev1[sloc[ip]] - elev1[spn];
                    }

                    if(ed >= 0.0 && dir[jn][in] != 0)
                    {
                        donothing = 1;  // If neighbor drains
                    }

                    if(spn >= 0)     // if neighbor is in flat
                    {
                        if(s1[spn] >= 0 && s1[spn] < st && dir[jn][in]  == 0)
                        {
                            donothing = 1;   //   Incremented
                        }
                    }

                }

                if(donothing == 0)
                {
                    s1[sloc[ip]]++;
                    ninc++;
                    done=0;
                }

            }   // End of loop over all flats

            st=st+1;

            if(print_many_messages)
            {
                main_window->Log_Message("[flatrout] Incfall " + QString::number(ninc) + " " + QString::number(n));
            }

            if(ninc == nincold)
            {
                done = 1;
                if(print_many_messages)
                {
                    main_window->Log_Message("[flatrout] There are pits remaining, direction will not be set ");
                }

                // Set the direction of these pits to 9 to flag them
                for(ip = 0; ip < n; ip++)  //  loop 2 over all flats
                {
                    // if adjacent to same level or lower that drains or adjacent to pixel with s1 < st and dir not set do nothing

                    donothing = 0;
                    j = js[sloc[ip]];
                    i = is[sloc[ip]];

                    for(k = 1; k <= 8; k++)
                    {
                        jn = j + d2[k];
                        in = i + d1[k];

                        spn = spos[jn][in];
                        if(iter <= 1)
                        {
                            ed = elev[j][i] - elev[jn][in];
                        }
                        else
                        {
                            ed = elev1[sloc[ip]] - elev1[spn];
                        }

                        if(ed >= 0.0 && dir[jn][in] != 0)
                        {
                            donothing = 1;  // If neighbor drains
                        }

                        if(spn >= 0)     // if neighbor is in flat   */
                        {
                            // If neighbor is not being Incremented
                            if(s1[spn] >= 0 && s1[spn] < st && dir[jn][in]  == 0)
                            {
                                donothing = 1;
                            }
                        }
                    }

                    if(donothing == 0)
                    {
                        dir[j][i] = 9;
                    }

                }   // End of loop 2 over all flats
            }

            nincold = ninc;

        }  //  End of while done loop


    } catch (...)
    {
        qDebug() << "Error: incfall is returning w/o checking";
        return -5000;
    }

    return 0;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// incrise
// Visit Taudem website for details.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int incrise(int n, float *elev1, short *s2,int **spos, int iter, int *sloc)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start incrise";

    try {

        if(elev1 == nullptr)
        {
            main_window->Log_Message("[incrise] Error[-1000] elev1 nullptr ");
            return -1000;
        }
        if(s2 == nullptr)
        {
            main_window->Log_Message("[incrise] Error[-1001] s2 nullptr ");
            return -1001;
        }
        if(spos == nullptr)
        {
            main_window->Log_Message("[incrise] Error[-1002] spos nullptr ");
            return -1002;
        }
        if(sloc == nullptr)
        {
            main_window->Log_Message("[incrise] Error[-1003] sloc nullptr ");
            return -1003;
        }
        if(is == nullptr)
        {
            main_window->Log_Message("[incrise] Error[-1004] is nullptr ");
            return -1004;
        }
        if(js == nullptr)
        {
            main_window->Log_Message("[incrise] Error[-1005] js nullptr ");
            return -1005;
        }
        if(elev == nullptr)
        {
            main_window->Log_Message("[incrise] Error[-1006] elev nullptr ");
            return -1006;
        }
        if(dn == nullptr)
        {
            main_window->Log_Message("[incrise] Error[-1007] dn nullptr ");
            return -1007;
        }
        if(d1 == nullptr)
        {
            main_window->Log_Message("[incrise] Error[-1008] d1 nullptr ");
            return -1008;
        }
        if(d2 == nullptr)
        {
            main_window->Log_Message("[incrise] Error[-1009] d2 nullptr ");
            return -1009;
        }

        // This routine implements stage 2 drainage away from higher ground dn is used to flag pixels still being incremented

        int done=0,ip,k,ninc,nincold,spn = 0;
        float ed;
        short i,j,in,jn;
        nincold=0;

        while(done < 1)
        {
            done=1;
            ninc=0;

            for(ip=0; ip < n; ip++)
            {
                for(k=1; k <= 8; k++)
                {
                    j = js[sloc[ip]];
                    i = is[sloc[ip]];
                    jn = j + d2[k];
                    in = i + d1[k];
                    spn = spos[jn][in];

                    if(iter <= 1)
                    {
                        ed = elev[j][i] - elev[jn][in];
                    }
                    else
                    {
                        ed = elev1[sloc[ip]] - elev1[spn];
                    }

                    if(ed < 0.0)
                    {
                        dn[sloc[ip]] = 1;
                    }

                    if(spn >=0)
                    {
                        if(s2[spn] > 0)
                        {
                            dn[sloc[ip]] = 1;
                        }
                    }
                }
            }

            for(ip = 0; ip < n; ip++)
            {
                s2[sloc[ip]] = s2[sloc[ip]] + dn[sloc[ip]];
                ninc = ninc + dn[sloc[ip]];

                if(dn[sloc[ip]] == 0)
                {
                    done=0;  //  if still some not being incremented continue looping
                }
            }

            if(print_many_messages)
            {
                main_window->Log_Message("[incrise] Progress " + QString::number(ninc) + " " + QString::number(n));
            }

            if(ninc == nincold)
            {
                done = 1;   // If there are no new cells incremented stop - this is the case when a flat has no higher ground around it.
            }

            nincold=ninc;

        }

    }
    catch (...)
    {
        qDebug() << "Error: incrise is returning w/o checking";
        return -5000;
    }

    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// set2
// Visit Taudem website for details.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int set2(int i,int j,float *fact,float *elev1, float *elev2, int iter, int **spos, short *s)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start set2";

    try {

        if(fact == nullptr)
        {
            main_window->Log_Message("[set2] Error[-1000] fact nullptr ");
            return -1000;
        }
        if(elev1 == nullptr)
        {
            main_window->Log_Message("[set2] Error[-1001] elev1 nullptr ");
            return -1001;
        }
        if(elev2 == nullptr)
        {
            main_window->Log_Message("[set2] Error[-1002] elev2 nullptr ");
            return -1002;
        }
        if(spos == nullptr)
        {
            main_window->Log_Message("[set2] Error[-1003] spos nullptr ");
            return -1003;
        }
        if(s == nullptr)
        {
            main_window->Log_Message("[set2] Error[-1004] s nullptr ");
            return -1004;
        }
        if(elev == nullptr)
        {
            main_window->Log_Message("[set2] Error[-1005] elev nullptr ");
            return -1005;
        }
        if(dir == nullptr)
        {
            main_window->Log_Message("[set2] Error[-1006] dir nullptr ");
            return -1006;
        }
        if(d1 == nullptr)
        {
            main_window->Log_Message("[set2] Error[-1007] d1 nullptr ");
            return -1007;
        }
        if(d2 == nullptr)
        {
            main_window->Log_Message("[set2] Error[-1008] d2 nullptr ");
            return -1008;
        }
        if(fact == nullptr)
        {
            main_window->Log_Message("[set2] Error[-1009] fact nullptr ");
            return -1009;
        }

        float slope,slope2,smax,ed = 0;
        int k,spn,sp,kflat = 0;
        short in,jn;
        smax = 0.0;
        sp = spos[j][i];

        for(k = 1; k <= 8; k++)
        {
            jn = j + d2[k];
            in = i + d1[k];
            spn = spos[jn][in];

            if(iter <= 1)
            {
                ed = elev[j][i] - elev[jn][in];
            }
            else
            {
                ed = elev1[sp] - elev1[spn];
            }

            slope = fact[k] * ed;

            if(spn < 0 || s[spn] < 0)
            {
                //The neighbor is outside the flat set.
                ed = 0.0;
            }
            else
            {
                ed = elev2[spn];
            }

            slope2 = fact[k] * (elev2[sp] - ed);

            if(slope2 > smax && slope >= 0.0)  // Only if latest iteration slope is positive and previous iteration slope flat
            {
                smax = slope2;
                dir[j][i] = k;
            }
        }

    } catch (...) {

        qDebug() << "Error: set2 is returning w/o checking";
        return -5000;
    }

    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// sloped8
// Visit Taudem website for details.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int sloped8(void )
{
    if(print_many_messages)
        qDebug() << "INFO: Start sloped8";

    try {

        if(d1 == nullptr)
        {
            main_window->Log_Message("[sloped8] Error[-1000] d1 is null   ");
            return -1000;
        }
        if(d2 == nullptr)
        {
            main_window->Log_Message("[sloped8] Error[-1001] d2 is null   ");
            return -1001;
        }
        if(elev == nullptr)
        {
            main_window->Log_Message("[sloped8] Error[-1002] elev is null   ");
            return -1002;
        }
        if(dir == nullptr)
        {
            main_window->Log_Message("[sloped8] Error[-1003] dir is null   ");
            return -1003;
        }
        if(slope == nullptr)
        {
            main_window->Log_Message("[sloped8] Error[-1004] slope is null   ");
            return -1004;
        }
        if(d1 == nullptr)
        {
            main_window->Log_Message("[sloped8] Error[-1005] d1 nullptr ");
            return -1005;
        }
        if(d2 == nullptr)
        {
            main_window->Log_Message("[sloped8] Error[-1006] d2 nullptr ");
            return -1006;
        }


        int in,jn = 0;
        float fact[9],ed;

        bool error_found = false;
        //  Direction factors
        for(int k=1; k<= 8; k++)
        {
            float bottom = sqrt(d1[k]*dy*d1[k]*dy+d2[k]*d2[k]*dx*dx);
            if(bottom <= 0)
            {
                error_found = true;
            }
            else if (std::isnan(bottom))
            {
                error_found = true;
            }
            else
            {
                fact[k]= (float) (1.0/bottom);
            }
        }

        if(error_found)
        {
            main_window->Log_Message("[sloped8] Error[-1005] Invalid bottom value  ");
            return -1005;
        }

        for(int i = i2; i< n2; i++)
        {
            for(int j = i1; j < n1; j++)
            {
                if(dir[j][i] > 0)
                {
                    jn = j + d2[dir[j][i]];
                    in = i + d1[dir[j][i]];
                    ed = elev[j][i] - elev[jn][in];
                    slope[j][i]= ed * fact[dir[j][i]] ;
                }
                else
                    slope[j][i]= -1.0;
            }
        }

    }
    catch (...)
    {
        main_window->Log_Message("[sloped8] Error[-9000] sloped8 is returning w/o checking  ");
        return -5000;
    }

    return 0;
}
