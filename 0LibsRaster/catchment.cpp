#include <QDebug>

#include <stdio.h>
#include "lsm.h"
#include "globals.h"


void findIJCat(short **fdr, int i, int j, int *mIJ);
int trace(float **seg, short int **fdr, float **cat, int i, int j);


int catchment(char *segFile, char *fdrFile, char *catFile){

    if(print_debug_messages)
        qDebug() << "INFO: Start catchment";

    try {

        int i, j;
        int mIJ[2];
        int err, err1, err2, err3, err4;

        err1=gridread(fdrFile,(void ***)&dir,RPSHRDTYPE,&nx,&ny,&dx,&dy,bndbox,&csize,&mval,&filetype);
        err2=gridread(segFile,(void ***)&elev,RPFLTDTYPE,&nx,&ny,&dx,&dy,bndbox,&csize,&mval,&filetype);
        err3=gridread(segFile,(void ***)&slope,RPFLTDTYPE,&nx,&ny,&dx,&dy,bndbox,&csize,&mval,&filetype);

        // THIS LOOP CAN BE ELIMINATED BY CHANGING (SLOPE[I][J] < 0) FROM == IN THE NEXT FOR LOOP
        for(i=0; i<nx; i++){
            for(j=0; j<ny; j++){
                if(slope[i][j]<0)
                    slope[i][j]=0;
            }
        }

        for(i=0; i<nx; i++){
            for(j=0; j<ny; j++){
                //printf("->%d\t%d\t%d\n", i, j, dir[i][j]); //getchar(); getchar();
                if(slope[i][j] == 0 && dir[i][j] != -1){
                    //printf("-->%d\t%d\t%d\n", i, j, dir[i][j]);// getchar(); getchar();
                    findIJCat(dir, i, j, mIJ);
                    slope[i][j]=trace(elev, dir, slope, mIJ[0], mIJ[1]);
                }
            }
        }

        err4 = gridwrite(catFile,(void **)slope,RPFLTDTYPE,nx,ny,dx,dy,bndbox,csize,mval,filetype);
        err = err1 + err2 + err3 + err4;
        return err;

    } catch (...) {
        qDebug() << "Error: catchment ";
        return 50;
    }


}

int trace(float **seg, short int **fdr, float **cat, int i, int j){

    //if(print_debug_messages)
    //    qDebug() << "INFO: Start trace";

    try {

        int mIJ[2];
        //printf("in trace\n");

        if(seg[i][j]>0){
            //printf("in trace 1\n"); // getchar(); getchar();
            return seg[i][j];
        }
        else if(cat[i][j] != 0){
            //printf("in trace 2\n"); // getchar(); getchar();
            return cat[i][j];
        }
        else if(fdr[i][j] == -1){
            return fdr[i][j];
        }
        else{
            //printf("in trace 3\n");
            //printf("%d\t%d\t%d\n", i, j, fdr[i][j]); // getchar(); getchar();
            findIJCat(fdr, i, j, mIJ);
            cat[i][j]=trace(seg, fdr, cat, mIJ[0], mIJ[1]);
        }
        return cat[i][j];

    } catch (...) {
        qDebug() << "Error: trace is returning w/o checking [VERY BAD ERROR HERE] not returning anything";
    }

}

void findIJCat(short **fdr, int i, int j, int *mIJ){

    //if(print_debug_messages)
    //    qDebug() << "INFO: Start findIJCat";

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
        qDebug() << "Error: findIJCat is returning w/o checking";
    }

    return;
}
