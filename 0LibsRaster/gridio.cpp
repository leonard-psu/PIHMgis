//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// gridio.c
//
// I/O routines for terrain stability mapping
//
// David Tarboton
// Utah Water Research Laboratory
// Utah State University
// Logan, UT, 84322-8200
// U. S. A.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <QDebug>
#include <stdio.h>
#include <string.h>

#include "gridio.h"
#include "globals.h"


// User interface to PIHMgis v3.5
extern PIHMgisDialog *main_window;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// readline from file
// Used in gridread
// Note uses '\n' as string determination
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int readline(FILE *fp,char *fline)
{
    // if(print_many_messages)
    //     qDebug() << "INFO: Start readline";

    try {

        if(fp == nullptr)
        {
            main_window->Log_Message("[readline] Error[-1000] fp = null");
            return -1000;
        }
        if(fline == nullptr)
        {
            main_window->Log_Message("[readline] Error[-1001] fline = null");
            return -1001;
        }

        int i = 0, ch;

        for(i = 0; i< MAXLN; i++)
        {
            ch = getc(fp);

            if(ch == EOF)
            {
                *(fline+i) = '\0';
                return(EOF);
            }
            else
            {
                *(fline+i) = (char)ch;
            }

            if((char)ch == '\n')
            {
                *(fline+i) = '\0';
                return(0);
            }

        }

    } catch (...) {
        qDebug() << "Error: readline is returning w/o checking [PROBLEM HERE]";
        return -5000;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// matalloc(...) allocates memory for matrix navigation pointer
// and for matrix data, then returns matrix navigation pointer
// Modification of matrixalloc by DGT to not use so many pointers
// 7/1/97
// Used in aread8, flood, gridio, setdir
// Note: Modified to return nullptr on errors
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void **matalloc(int nx,int ny,int datatype)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start matalloc";

    void **mat;

    try {

        if(nx <= 0)
        {
            main_window->Log_Message("[matalloc] Invalid nx <= 0. Returning null pointer");
            return nullptr;
        }
        if(ny <= 0)
        {
            main_window->Log_Message("[matalloc] Invalid ny <= 0. Returning null pointer");
            return nullptr;
        }
        if(datatype <= 0)
        {
            main_window->Log_Message("[matalloc] Invalid datatype. Returning null pointer");
            return nullptr;
        }

        int arrsize = 0;
        void *data;
        int **imat;
        short **smat;
        float **fmat;

        /* allocate memory for array navigation pointers */
        if(datatype == 1)
        {
            mat = (void **)malloc(sizeof(short *)*(nx));
            arrsize = sizeof(short)*(nx)*(ny);
        }
        else if(datatype == 2)
        {
            mat = (void **)malloc(sizeof(int *)*(nx));
            arrsize = sizeof(int)*(nx)*(ny);
        }
        else if(datatype == 3)
        {
            mat = (void **)malloc(sizeof(float *)*(nx));
            arrsize = sizeof(float)*(nx)*(ny);
        }
        else
        {
            main_window->Log_Message("[matalloc] Unhandled datatype. Returning null pointer");
            return nullptr;
        }

        if(mat == nullptr)
        {
            main_window->Log_Message("[matalloc] Error: Cannot allocate memory for matrix navigation pointers.");
            main_window->Log_Message("[matalloc] nx = " + QString::number(nx) + " ny = " + QString::number(ny));
            return nullptr;
        }

        if(arrsize <= 0)
        {
            main_window->Log_Message("[matalloc] Error: Invalid arrsize.");
            main_window->Log_Message("[matalloc] nx = " + QString::number(nx) + " ny = " + QString::number(ny));
            return nullptr;
        }

        data = malloc(arrsize);

        if(data == nullptr)
        {
            main_window->Log_Message("[matalloc] Cannot allocate memory for matrix of dimension.");
            main_window->Log_Message("[matalloc] nx = " + QString::number(nx) + " ny = " + QString::number(ny));
            return nullptr;
        }

        switch(datatype)
        {
        case 1:
            smat = (short **)mat;
            for(int i=0; i<(nx); i++)
            {
                smat[i] = &(((short *)(data))[i*(ny)]);
            }
            break;
        case 2:
            imat = (int **)mat;
            for(int i=0; i<(nx); i++)
            {
                imat[i] = &(((int *)(data))[i*(ny)]);
            }
            break;
        case 3:
            fmat = (float **)mat;
            for(int i=0; i<(nx); i++)
            {
                fmat[i] = &(((float *)(data))[i*(ny)]);
            }
            break;
        default:
            main_window->Log_Message("[matalloc] Unhandled datatype. Returning null pointer");
            return nullptr;
            break;
        }


    } catch (...) {
        qDebug() << "Error: matalloc is returning nullptr";
        return nullptr;
    }

    return(mat);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// gridread
// Used in aread8, catchment, catchment_shape, flood, gridio, setdir, and others....
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int gridread(QString file, void ***data, int datatype, int *nx, int *ny,
             float *dx, float *dy, double bndbox[4], double *csize, float *nodata, int *filetype)
{

    if(print_debug_messages)
        qDebug() << "INFO: Start gridread";

    try {

        //Check input names
        if(file == nullptr)
        {
            main_window->Log_Message("[gridread] Error[-1000] file null" );
            return -1000;
        }

        if(file.length() < 1)
        {
            main_window->Log_Message("[gridread] Error[-1001] Invalid file " + file);
            return -1001;
        }

        FILE *fp;

        int hdrlines = 0;
        float value= 0;
        char fline[MAXLN], keyword[21], utmetag, utmntag;
        float **farr;
        int **iarr;
        short **sarr;
        double utme,utmn;

        QByteArray fname = file.toLatin1();
        char *file_char = fname.data();

        *filetype=0;
        fp = fopen(file_char,"r");
        if(fp == nullptr)
        {
            main_window->Log_Message("[gridread] Error[-1002] Cannot open input file " + fname);
            return -1002;
        }

        // read ARC-Info header
        while(1)
        {
            readline(fp, fline);

            if(!isalpha(*fline) || *fline == '-')
                break;

            hdrlines++;

            sscanf(fline,"%s %f",keyword,&value);

            if(strcmp(keyword,"ncols") == 0 || strcmp(keyword,"NCOLS") == 0)
            {
                *nx = (int)value;
            }
            else if(strcmp(keyword,"nrows") == 0 || strcmp(keyword,"NROWS") == 0)
            {
                *ny = (int)value;
            }
            else if(strcmp(keyword,"xllcenter") == 0 || strcmp(keyword,"XLLCENTER") == 0)
            {
                utmetag = 'c';
                utme = value;
            }
            else if(strcmp(keyword,"xllcorner") == 0 || strcmp(keyword,"XLLCORNER") == 0)
            {
                utmetag = 'e';
                utme = value;
            }
            else if(strcmp(keyword,"yllcenter") == 0 || strcmp(keyword,"YLLCENTER") == 0)
            {
                utmntag = 'c';
                utmn = value;
            }
            else if(strcmp(keyword,"yllcorner") == 0 || strcmp(keyword,"YLLCORNER") == 0)
            {
                utmntag = 'e';
                utmn = value;
            }
            else if(strcmp(keyword,"cellsize") == 0 || strcmp(keyword,"CELLSIZE") == 0)
            {
                *dx = *dy = value;
                *csize = (double) value;
            }
            else if(strcmp(keyword,"nodata_value") == 0 || strcmp(keyword,"NODATA_VALUE") == 0 || strcmp(keyword,"NODATA_value") == 0)
            {
                *nodata = value;
            }
        }

        // Adjust utme and utmn if necessary (we store center of reference cell)
        if(utmetag == 'e')
            utme = utme + *dx/2;

        if(utmntag == 'e')
            utmn = utmn + *dy/2;

        bndbox[0] = utme - *csize/2.;
        bndbox[1] = utmn - *csize/2.;
        bndbox[2] = bndbox[0] + *csize * (*nx);
        bndbox[3] = bndbox[1] + *csize * (*ny);

        //Position file pointer for ARC-Info file to beginning of image data
        rewind(fp);

        for(int i=0; i<hdrlines; i++)
        {
            readline(fp, fline);
        }

        //Convert depending on datatype
        if(datatype == RPSHRDTYPE)
        {
            sarr = (short **) matalloc(*nx, *ny, datatype);
            if(sarr == nullptr)
            {
                main_window->Log_Message("[gridread] Error[-2001] matalloc failed.");
                fclose(fp);
                fp = nullptr;
                return -2001;
            }

            //Read in the ARC-Info file
            for(int i=0; i< *ny; i++)
            {
                for(int j=0; j< *nx; j++)
                {
                    fscanf(fp,"%hd",&sarr[j][i]);
                }
            }
            *data = (void **) sarr;
        }
        else if(datatype == RPINTDTYPE)
        {
            iarr = (int **) matalloc(*nx, *ny, datatype);
            if(iarr == nullptr)
            {
                main_window->Log_Message("[gridread] Error[-2002] matalloc failed.");
                fclose(fp);
                fp = nullptr;
                return -2002;
            }

            for(int i=0; i< *ny; i++)
            {
                for(int j=0; j< *nx; j++)
                {
                    fscanf(fp,"%d",&iarr[j][i]);
                }
            }
            *data = (void **) iarr;
        }
        else if(datatype == RPFLTDTYPE)
        {
            farr = (float **) matalloc(*nx, *ny, datatype);
            if(farr == nullptr)
            {
                main_window->Log_Message("[gridread] Error[-2003] matalloc failed.");
                fclose(fp);
                fp = nullptr;
                return -2003;
            }

            // read in the ARC-Info file
            for(int i=0; i< *ny; i++)
            {
                for(int j=0; j< *nx; j++)
                {

                    fscanf(fp,"%f",&farr[j][i]);
                }
            }
            *data = (void **) farr;
        }
        else
        {
            main_window->Log_Message("[gridread] Error[1005] unknown datatype " + QString::number(datatype));
            fclose(fp);
            fp = nullptr;
            return(1005);
        }

        fclose(fp);
        fp = nullptr;

    }
    catch (...)
    {
        qDebug() << "Error: gridread is returning w/o checking";
        return(5000);
    }

    return(0);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// gridwrite
// Used in aread8, catchment, flood, gridio, setdir, and others....
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int gridwrite(QString qfile, void **data, int datatype, int nx, int ny, float dx,
              float dy, double bndbox[4], double csize, float nodata, int filetype)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start gridwrite";

    try{

        //Check input names
        if(qfile == nullptr)
        {
            main_window->Log_Message("[gridwrite] Error[-1000] Invalid file ");
            return -1000;
        }
        if(qfile.length() < 1)
        {
            main_window->Log_Message("[gridwrite] Error[-1001] Invalid file " + qfile);
            return -1001;
        }
        if(nx < 1)
        {
            main_window->Log_Message("[gridwrite] Error[-1002] Invalid nx < 1 ");
            return -1002;
        }
        if(ny < 1)
        {
            main_window->Log_Message("[gridwrite] Error[-1003] Invalid ny < 1 ");
            return -1003;
        }


        FILE *fp;

        QByteArray fname = qfile.toLatin1();
        char *file = fname.data();

        float **farr;
        int **iarr;
        short **sarr;
        double utme,utmn;
        bool error_found = false;

        //  File types are 0=ASCII 1= ARCVIEW grid via the ESRI Application Programmers Interface
        if(filetype == 0)   // ASCII FILE
        {
            // open ARC-Info file
            fp = fopen(file,"w");

            if(fp == nullptr)
            {
                main_window->Log_Message("[gridwrite] Error[-2000] Cannot open output file   " + qfile);
                return -2000;
            }

            // write ARC-Info header
            fprintf(fp,"ncols         %d\n",nx);
            fprintf(fp,"nrows         %d\n",ny);
            utme = bndbox[0]+dx*0.5;
            utmn = bndbox[1]+dy*0.5;
            fprintf(fp,"xllcenter     %f\n",utme);
            fprintf(fp,"yllcenter     %f\n",utmn);
            fprintf(fp,"cellsize      %f\n",csize);
            fprintf(fp,"nodata_value  %g\n",nodata);

            // write raster data to ARC/INFO file
            // convert depending on datatype
            if(datatype == RPSHRDTYPE)
            {
                sarr = (short **) data;
                if(sarr == nullptr)
                {
                    main_window->Log_Message("[gridwrite] Error[-2001] data is null.");
                    error_found = true;
                }

                if(!error_found)
                {
                    for(int i=0; i< ny; i++)
                    {
                        for(int j=0; j< nx; j++)
                        {
                            fprintf(fp,"%hd ",sarr[j][i]);

                            if((j+1) % LINELEN == 0)
                                fprintf(fp,"\n");
                        }
                        fprintf(fp,"\n");
                    }
                }
            }
            else if(datatype == RPINTDTYPE)
            {
                iarr = (int **) data;
                if(iarr == nullptr)
                {
                    main_window->Log_Message("[gridwrite] Error[-2002] data is null.");
                    error_found = true;
                }

                if(!error_found)
                {
                    for(int i=0; i< ny; i++)
                    {
                        for(int j=0; j< nx; j++)
                        {
                            fprintf(fp,"%d ",iarr[j][i]);

                            if((j+1) % LINELEN == 0)
                                fprintf(fp,"\n");
                        }
                        fprintf(fp,"\n");
                    }
                }
            }
            else if(datatype == RPFLTDTYPE)
            {
                farr = (float **) data;
                if(farr == nullptr)
                {
                    main_window->Log_Message("[gridwrite] Error[-2003] data is null.");
                    error_found = true;
                }

                if(!error_found)
                {
                    for(int i=0; i< ny; i++)
                    {
                        for(int j=0; j< nx; j++)
                        {
                            fprintf(fp,"%g ",farr[j][i]);

                            if((j+1) % LINELEN == 0)
                                fprintf(fp,"\n");
                        }
                        fprintf(fp,"\n");
                    }
                }
            }
            else
            {
                main_window->Log_Message("[gridwrite] Error[-2003] Unknown datatype  " + QString::number(datatype));
                error_found = true;
            }

            fclose(fp);
        }
        else {

            main_window->Log_Message("[gridwrite] Error[-3000] Invalid file type ");
            fclose(fp);
            return -3000;
        }

        if(error_found)
        {
            main_window->Log_Message("[gridwrite] Error[-3001] Error(s) found while wrting data ");
            return -3001;
        }


    } catch (...) {
        qDebug() << "Error: gridwrite is returning w/o checking";
        return -9000;
    }

    return(0);
}




