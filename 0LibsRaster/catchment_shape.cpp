#include <QDir>
#include <QString>
#include <QDebug>

#include <stdio.h>
#include "lsm.h"
#include "./../0LibsShape/shapefil.h"
#include "globals.h"


#define dist(x1, x2) fabs(x1-x2)
#define direction(l1, l2) (fabs(atan(fabs((l1.y2 - l1.y1)/(l1.x2 - l1.x1))) - atan(fabs(( l2.y2 - l2.y1)/(l2.x2 - l2.x1))))<0.001)?0:1;


struct structure{
    double x1, y1; // from point
    double x2, y2; // to   point
    int cl; //catchment it belongs to
};

typedef struct structure LINE;

// User interface to PIHMgis v3.5
extern PIHMgisDialog *main_window;

QString catchment_temp_fname = "/cattemp.shp";  //Note keep forward slash

int sortLine(LINE *lines, int);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Called by CatchmentPolgon
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int catchment_shape(QString catFile, QString nodeFile, QString shpFile,  QString dbfFile)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start catchment_shape";

    try {

        QString TempString = user_pihmgis_root_folder + user_pihmgis_project_folder + catchment_temp_fname;
        if(QFile::exists(TempString))
        {
            main_window->Log_Message("[catchment_shape] WARNING/ERROR Catchment temporary file already exists " + TempString);

            //If the file exists, could mean a few problems. Hence, user must decide on how to proceed outside PIHMgis.
            //For example, does the user have multiple PIHMgis sessions running?
            //Did a previous execution failed?
            return -9000;
        }

        if(catFile == nullptr)
        {
            main_window->Log_Message("[catchment_shape] Error[-1000] Invalid catFile ");
            return -1000;
        }

        if(nodeFile == nullptr)
        {
            main_window->Log_Message("[catchment_shape] Error[-1001] Invalid nodeFile ");
            return -1001;
        }

        if(shpFile == nullptr)
        {
            main_window->Log_Message("[catchment_shape] Error[-1002] Invalid shpFile ");
            return -1002;
        }

        if(dbfFile == nullptr)
        {
            main_window->Log_Message("[catchment_shape] Error[-1003] Invalid dbfFile ");
            return -1003;
        }

        //Check input names
        if(catFile.length() < 1)
        {
            main_window->Log_Message("[catchment_shape] Error[-1004] Invalid catFile " + catFile);
            return -1004;
        }

        if(nodeFile.length() < 1)
        {
            main_window->Log_Message("[catchment_shape] Error[-1005] Invalid nodeFile " + nodeFile);
            return -1005;
        }

        if(shpFile.length() < 1)
        {
            main_window->Log_Message("[catchment_shape] Error[-1006] Invalid shpFile " + shpFile);
            return -1006;
        }

        if(dbfFile.length() < 1)
        {
            main_window->Log_Message("[catchment_shape] Error[-1007] Invalid dbfFile " + dbfFile);
            return -1007;
        }

        int i= 0, j = 0;
        int ShpEntryNumber = 0;
        int maxClass = 0; // stores # of nodes (starting pt of a stream) to process
        int lineDirFlag = 0;
        int startPivot, endPivot, classNum, point[2], count;
        int numPt = 0;
        int recordNum=0;

        int *linesInClass;
        LINE *line;
        SHPObject *obj;
        SHPObject *tempobj;


        SHPHandle shp = SHPCreate( qPrintable(shpFile), SHPT_POLYGON);
        if(shp == nullptr)
        {
            main_window->Log_Message("[catchment_shape] Error[-1008] shpFile is NULL. With file " + QString(shpFile));
            return -1008;
        }
        DBFHandle dbf = DBFCreate( qPrintable(dbfFile) );
        if(dbf == nullptr)
        {
            main_window->Log_Message("[catchment_shape] Error[-1009] dbfFile is NULL. With file " + QString(dbfFile));
            SHPClose(shp);
            return -1009;
        }

        int polyFld = DBFAddField(dbf, "catNum", FTInteger, 5, 0);
        if(polyFld < 0)
        {
            main_window->Log_Message("[catchment_shape] Error[-1010] Failed to add field catNum");
            SHPClose(shp);
            DBFClose(dbf);
            return -1010;
        }
        int wshedID = DBFAddField(dbf, "Watershed", FTInteger, 5, 0);
        if(wshedID < 0)
        {
            main_window->Log_Message("[catchment_shape] Error[-1011] Failed to add field Watershed");
            SHPClose(shp);
            DBFClose(dbf);
            return -1011;
        }

        SHPHandle tempshp = SHPCreate(qPrintable(TempString), SHPT_ARC);
        if(tempshp == nullptr)
        {
            main_window->Log_Message("[catchment_shape] Error[-1012] tempshp is NULL.");
            SHPClose(shp);
            DBFClose(dbf);
            return -1012;
        }

        TempString.replace(".shp",".dbf");
        DBFHandle tempdbf = DBFCreate(qPrintable(TempString));
        if(tempdbf == nullptr)
        {
            main_window->Log_Message("[catchment_shape] Error[-1013] tempdbf is NULL.");
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(tempshp);
            return -1013;
        }

        int tempFld = DBFAddField(tempdbf, "lineNum", FTInteger, 5, 0);
        if(tempFld < 0)
        {
            main_window->Log_Message("[catchment_shape] Error[-1014] Failed to add field lineNum.");
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(tempshp);
            DBFClose(tempdbf);
            return -1014;
        }

        double *ptx, *pty, *ptz;

        int result = gridread( catFile ,(void ***)&elev,RPFLTDTYPE,&nx,&ny,&dx,&dy,bndbox,&csize,&mval,&filetype);

        if ( result != 0)
        {
            main_window->Log_Message("[catchment_shape] Error[-1015] Failed to to Read Catchment Grid File.");
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(tempshp);
            DBFClose(tempdbf);
            return -1015;
        }
        if ( nx <= 0)
        {
            main_window->Log_Message("[catchment_shape] Error[-1016] Invalid nx value of " + QString::number(nx) );
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(tempshp);
            DBFClose(tempdbf);
            return -1016;
        }
        if ( nx > 250000) //250000 is a guess
        {
            main_window->Log_Message("[catchment_shape] Error[-1017] Invalid nx value (250000 is a guess) of " + QString::number(nx) );
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(tempshp);
            DBFClose(tempdbf);
            return -1017;
        }
        if ( ny <= 0)
        {
            main_window->Log_Message("[catchment_shape] Error[-1018] Invalid ny value of " + QString::number(ny) );
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(tempshp);
            DBFClose(tempdbf);
            return -1018;
        }
        if ( ny > 250000) //250000 is a guess
        {
            main_window->Log_Message("[catchment_shape] Error[-1019] Invalid ny value (250000 is a guess) of " + QString::number(ny) );
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(tempshp);
            DBFClose(tempdbf);
            return -1019;
        }

        ptx = (double *)malloc(sizeof(double) * nx * ny * 2);
        if ( ptx == nullptr)
        {
            main_window->Log_Message("[catchment_shape] Error[-1020] ptx is null" );
            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(tempshp);
            DBFClose(tempdbf);
            return -1020;
        }

        pty = (double *)malloc(sizeof(double) * nx * ny * 2);
        if ( pty == nullptr)
        {
            main_window->Log_Message("[catchment_shape] Error[-1021] pty is null" );
            free(ptx);

            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(tempshp);
            DBFClose(tempdbf);
            return -1021;
        }

        ptz = (double *)malloc(sizeof(double) * nx * ny * 2);
        if ( ptz == nullptr)
        {
            main_window->Log_Message("[catchment_shape] Error[-1022] ptz is null" );
            free(ptx);
            free(pty);

            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(tempshp);
            DBFClose(tempdbf);
            return -1022;
        }

        line = (LINE *)malloc(sizeof(LINE) * 4 * nx * ny);
        if ( line == nullptr)
        {
            main_window->Log_Message("[catchment_shape] Error[-1023] line is null" );
            free(ptx);
            free(pty);
            free(ptz);

            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(tempshp);
            DBFClose(tempdbf);
            return -1023;
        }

        if ( elev == nullptr)
        {
            main_window->Log_Message("[catchment_shape] Error[-1024] elev is null" );
            free(ptx);
            free(pty);
            free(ptz);
            free(line);

            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(tempshp);
            DBFClose(tempdbf);
            return -1024;
        }

        for(i = 0; i < nx; i++)
        {
            for(j = 0; j < ny; j++)
            {
                if(maxClass < elev[i][j])
                    maxClass = elev[i][j];
            }
        }

        if ( maxClass <= 0)
        {
            main_window->Log_Message("[catchment_shape] Error[78] Invalid maxClass " + QString::number(maxClass) );
            free(ptx);
            free(pty);
            free(ptz);
            free(line);

            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(tempshp);
            DBFClose(tempdbf);
            return 78;
        }

        linesInClass = (int *)malloc( (maxClass+1) * sizeof(int));
        if ( linesInClass == nullptr)
        {
            main_window->Log_Message("[catchment_shape] Error[-1025] linesInClass is null" );
            free(ptx);
            free(pty);
            free(ptz);
            free(line);

            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(tempshp);
            DBFClose(tempdbf);
            return -1025;
        }


        for(i = 1; i <= maxClass; i++)
        {
            linesInClass[i] = 0;
        }

        int numLine = 0;
        //store all the lines
        for(i = 1; i < nx-1; i++)
        {
            for(j = 1; j < ny-1; j++)
            {
                if(elev[i][j]>0)
                {
                    if(elev[i][j] != elev[i-1][j])
                    {
                        line[numLine].x1 = bndbox[0] + (i)*csize;
                        line[numLine].y1 = bndbox[3] - (j+1)*csize;
                        line[numLine].x2 = bndbox[0] + (i)*csize;
                        line[numLine].y2 = bndbox[3] - (j)*csize;
                        line[numLine].cl = elev[i][j];
                        linesInClass[line[numLine].cl]++;
                        numLine++;
                    }

                    if(elev[i][j] != elev[i][j-1])
                    {
                        line[numLine].x1 = bndbox[0] + (i)*csize;
                        line[numLine].y1 = bndbox[3] - (j)*csize;
                        line[numLine].x2 = bndbox[0] + (i+1)*csize;
                        line[numLine].y2 = bndbox[3] - (j)*csize;
                        line[numLine].cl = elev[i][j];
                        linesInClass[line[numLine].cl]++;
                        numLine++;
                    }

                    if(elev[i][j] != elev[i+1][j])
                    {
                        line[numLine].x1 = bndbox[0] + (i+1)*csize;
                        line[numLine].y1 = bndbox[3] - (j)*csize;
                        line[numLine].x2 = bndbox[0] + (i+1)*csize;
                        line[numLine].y2 = bndbox[3] - (j+1)*csize;
                        line[numLine].cl = elev[i][j];
                        linesInClass[line[numLine].cl]++;
                        numLine++;
                    }

                    if(elev[i][j] != elev[i][j+1])
                    {
                        line[numLine].x1 = bndbox[0] + (i+1)*csize;
                        line[numLine].y1 = bndbox[3] - (j+1)*csize;
                        line[numLine].x2 = bndbox[0] + (i)*csize;
                        line[numLine].y2 = bndbox[3] - (j+1)*csize;
                        line[numLine].cl = elev[i][j];
                        linesInClass[line[numLine].cl]++;
                        numLine++;
                    }
                }
            }
        }


        //sort the lines with class information
        int sort_result = sortLine(line, numLine);
        if( sort_result != 0)
        {
            main_window->Log_Message("[catchment_shape] Error[-1026] sortLine failed" );
            free(ptx);
            free(pty);
            free(ptz);
            free(linesInClass);
            free(line);

            SHPClose(shp);
            DBFClose(dbf);
            SHPClose(tempshp);
            DBFClose(tempdbf);
            return -1026;
        }

        int temprecordNum = 0;
        bool error_found = false;

        for(i = 0; i < numLine; i++)
        {
            ptx[0] = line[i].x1;
            ptx[1] = line[i].x2;
            pty[0] = line[i].y1;
            pty[1] = line[i].y2;
            ptz[0] = 0.0;
            ptz[1] = 0.0;

            tempobj = SHPCreateSimpleObject(SHPT_ARC, 2, ptx, pty, ptz);
            if(tempobj != nullptr)
            {
                ShpEntryNumber = SHPWriteObject(tempshp, -1, tempobj);
                if ( ShpEntryNumber < 0 )
                {
                    main_window->Log_Message("[catchment_shape] Error[-2000] SHPWriteObject Failed. Unable to Add Shape Entry to SHP/SHX file" );
                    error_found = true;
                }

                if ( ! DBFWriteIntegerAttribute(tempdbf, temprecordNum, tempFld, line[i].cl) )
                {
                    main_window->Log_Message("[catchment_shape] Error[-2001] SHPWriteObject Failed. Unable to Write Integer Attribute to DBF file" );
                    error_found = true;
                }

                SHPDestroyObject( tempobj );
            }
            else {
                error_found = true;
            }

            temprecordNum++;

        }

        SHPClose(tempshp);
        DBFClose(tempdbf);

        if( error_found )
        {
            main_window->Log_Message("[catchment_shape] Error[-1027] Errors found while creating " + TempString );
            free(ptx);
            free(pty);
            free(ptz);
            free(linesInClass);
            free(line);

            SHPClose(shp);
            DBFClose(dbf);
            return -1027;
        }

        ////////////////////////////////////////////////////////////////////////////////
        // start forming polygons now  NOTE: polygon:=class

        classNum = 1;
        startPivot = 0;
        endPivot  = startPivot + linesInClass[classNum];
        i = startPivot;
        numPt = 0;
        error_found = false;
        bool write_error_found = false;
        bool logic_error_found = false;

        while(classNum <= maxClass)
        {
            ptx[numPt] = line[i].x1;
            pty[numPt] = line[i].y1;
            ptz[numPt] = 0.0;
            numPt++;

            if( lineDirFlag == 0 && numPt > 1 )
            {
                --numPt;
                lineDirFlag = 1;
            }

            // search for connection
            count=0;
            for(j = startPivot; j < endPivot; j++)
            {
                if(dist(line[i].x2,line[j].x1) < 0.0001 && dist(line[i].y2,line[j].y1) < 0.0001 && line[j].cl != 0)
                {
                    point[count++] = j;
                }
            }

            if(count == 1)
            {
                line[i].cl = 0;
                lineDirFlag = direction(line[i], line[point[0]]);
                i = point[0]; // start search from found connecting line
            }
            else if(count == 0)
            {
                ptx[numPt] = line[i].x2;
                pty[numPt] = line[i].y2;
                ptz[numPt] = 0.0;
                numPt++;

                //write polygon here
                obj = SHPCreateSimpleObject(SHPT_POLYGON, numPt, ptx, pty, ptz);

                if(obj == nullptr)
                {
                    error_found = true;
                }
                else
                {
                    if ( SHPWriteObject(shp, -1, obj) < 0 )
                    {
                        error_found = true;
                    }

                    SHPDestroyObject( obj );

                    if ( ! DBFWriteIntegerAttribute(dbf, recordNum, polyFld, classNum))
                    {
                        write_error_found = true;
                    }

                    if ( ! DBFWriteIntegerAttribute(dbf, recordNum, wshedID, 1))
                    {
                        write_error_found = true;
                    }

                    recordNum++;
                    numPt = 0;

                    classNum++;
                    startPivot = endPivot;
                    endPivot   = startPivot + linesInClass[classNum];
                    i = startPivot;

                }
            }
            else if(count == 2)
            {
                line[i].cl = 0;

                if(abs(i-point[0]) > abs(i-point[1]))
                {
                    i = point[0];
                }
                else
                {
                    i = point[1];
                }
            }
            else
            {
                logic_error_found = true;
            }
        }

        SHPClose(shp);
        DBFClose(dbf);


        //Clean up
        free(ptx);
        free(pty);
        free(ptz);
        free(linesInClass);
        free(line);

        if(error_found)
        {
            main_window->Log_Message("[catchment_shape] Error[-3000] while writing to shapefile. It is recommended to use GIS tool to inspect results " );
            return -3000;
        }

        if(write_error_found)
        {
            main_window->Log_Message("[catchment_shape] Error[-3001] while writing shapefile. It is recommended to use GIS tool to inspect results " );
            return -3001;
        }

        if(logic_error_found)
        {
            main_window->Log_Message("[catchment_shape] Error[-3002] Logic issue found. Something went wrong. It is recommended to use GIS tool to inspect results " );
            return -3002;
        }

        return 0;

    }
    catch (...)
    {
        qDebug() << "Error: catchment_shape [TODO More error checking required]";
        return -5000;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Sorts Lines from above catchment
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int sortLine(LINE *lines, int numLine)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start sortLine";

    try {

        if(lines == nullptr)
        {
            return -9999;
        }

        int tempI, swapFlag=0;
        double tempD = 0.0;

        for(int i = 0; i < numLine-1; i++)
        {
            swapFlag = 0;

            for(int j = 0; j < numLine-1-i; j++)
            {
                if(lines[j+1].cl < lines[j].cl)
                {
                    swapFlag = 1;

                    tempD = lines[j].x1;
                    lines[j].x1   = lines[j+1].x1;
                    lines[j+1].x1 = tempD;

                    tempD = lines[j].y1;
                    lines[j].y1   = lines[j+1].y1;
                    lines[j+1].y1 = tempD;

                    tempD = lines[j].x2;
                    lines[j].x2   = lines[j+1].x2;
                    lines[j+1].x2 = tempD;

                    tempD = lines[j].y2;
                    lines[j].y2   = lines[j+1].y2;
                    lines[j+1].y2 = tempD;

                    tempI = lines[j].cl;
                    lines[j].cl   = lines[j+1].cl;
                    lines[j+1].cl = tempI;
                }

            } //End of for(int j = 0; j < numLine-1-i; j++)

            if(swapFlag == 0)
                break;

        } //End of for(int i = 0; i < numLine-1; i++)

    } catch (...) {
        qDebug() << "Error: sortLine is returning w/o checking";
    }

    return 0;
}
