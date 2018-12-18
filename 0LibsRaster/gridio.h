#ifndef GRID_H
#define GRID_H

/***********************************************************/
/*                                                         */
/* gridio.h                                                */
/*                                                         */
/* Grid Data manipulation functions -- header file       */
/*                                                         */
/*                                                         */
/* David Tarboton                                           */
/* Utah Water Research Laboratory                          */
/* Utah State University                                   */
/* Logan, UT 84322-8200                                    */
/*                                                         */
/***********************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>

#include <QString>


/*  ESRI Application Programmers Interface include file  */

#define NA (10.0*FLT_MIN)
#ifndef PI
#define PI 3.14159265359
#endif
#define LINELEN 40
#ifndef MAXLN
#define MAXLN 4096
#endif

/* data types */
#define RPSHRDTYPE  1
#define RPINTDTYPE  2
#define RPFLTDTYPE  3

/* byte sizes corresponding to data types above */
#define RPSHRSIZE (sizeof(short))
#define RPINTSIZE (sizeof(int))
#define RPFLTSIZE (sizeof(float))


void fgridread(char *file,void *dem, int *datatype, int *nx, int *ny,
			   float *dx, float *dy, double bndbox[4],double *csize,
			   float *ndv,int *filetype, int *igy);
void fgridwrite(char *file,void *dem, int *datatype, int *nx, int *ny,
			   float *dx, float *dy, double bndbox[4],double *csize,
			   float *ndv,int *filetype, int *igy);    
int gridwrite(QString file, void **data, int datatype, int nx, int ny, float dx,
 float dy, double bndbox[4], double csize, float ndv, int filetype);

int gridread(QString file, void ***data, int datatype, int *nx, int *ny,
 float *dx, float *dy, double bndbox[4], double *csize, float *ndv, int *filetype);


int readline(FILE *fp,char *fline);

void **matalloc(int nx,int ny,int datatype);


#endif

