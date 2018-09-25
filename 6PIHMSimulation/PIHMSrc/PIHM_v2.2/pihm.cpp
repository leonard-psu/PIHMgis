/*******************************************************************************
 * File        : pihm.c                                                        *
 * Version     : Nov, 2007 (2.0)                                               *
 * Developer of PIHM2.0:        Mukesh Kumar (muk139@psu.edu)                  *
 * Developer of PIHM1.0:        Yizhong Qu   (quyizhong@gmail.com)             *
 *-----------------------------------------------------------------------------*
 *                                                                             *
 *..............MODIFICATIONS/ADDITIONS in PIHM 2.0............................*
 * a) All modifications in physical process representations  in this version   *
 *    are listed as header in f.c and is_sm_et.c.     			       *
 * b) All addition/modifications in variable and structure definition/declarat-*
 *    -ion are listed as header in read_alloc.c and initialize.c	       *
 * c) 3 new input files have been added for geology, landcover and calibration *
 *    data								       *
 * d) Ported to Sundials 2.1.0                                                 *
 *-----------------------------------------------------------------------------*
 *                                                                             *
 * PIHM is an integrated finite volume based hydrologic model. It simulates    *
 * channel routing, overland flow, groundwater flow, macropore based infiltra- *
 * tion and stormflow, throughfall, evaporation from overlandflow-subsurface-  *
 * canopy, transpiration and  snowmelt by full coupling of processes.          *
 * It uses semi-discrete finite volume approach to discretize PDEs into ODEs,  *
 * and henceforth solving the global system of ODEs using CVODE. Global ODEs   *
 * are created in f.c. Any modifications in the process equations has to be    *
 * performed in f.c
 *                                                                             *
 *-----------------------------------------------------------------------------*
 * For questions or comments, please contact                                   *
 *      --> Mukesh Kumar (muk139@psu.edu)                                      *
 *      --> Prof. Chris Duffy (cxd11@psu.edu)                                  *
 * This code is free for research purpose only.                                *
 * Please provide relevant references if you use this code in your research work*
 *-----------------------------------------------------------------------------*
 *									       *
 * DEVELOPMENT RELATED REFERENCES:					       *
 * PIHM2.0:								       *
 *	a) Kumar, M., 2008, "Development and Implementation of a Multiscale,   *
 *	Multiprocess Hydrologic Model". PhD Thesis, Penn State University      *
 *	b) Kumar, M, G.Bhatt & C.Duffy, "Coupling of Data and Processes in     *
 *	Mesoscale Watershed", Advances in Water Resources (submitted)          *
 * PIHM1.0:								       *
 *	a) Qu, Y., 2005, "An Integrated hydrologic model for multiproces       *
 *	simulation using semi-discrete finite volume approach".PhD Thesis, PSU *
 *	b) Qu, Y. & C. Duffy, 2007, "A semidiscrete finite volume formulation  *
 *	for multiprocess watershed simulation". Water Resources Research       *
 *-----------------------------------------------------------------------------*
 * LICENSE:
 *******************************************************************************/



#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

/* SUNDIAL Header Files */

#include "sundials/sundials_types.h"
#include "nvector/nvector_serial.h"


#include "cvode/cvode.h"		/* CVODE header file                             */
#include "cvode/cvode_spgmr.h"	/* CVSPGMR linear header file                    */
//#include "sundials_smalldense.h"/* use generic DENSE linear solver for
//				 * "small"   */
#include "sundials/sundials_math.h"	/* contains UnitRoundoff, RSqrt, SQR
				 * functions   */
#include "cvode/cvode_dense.h"	/* CVDENSE header file                           */
#include "sundials/sundials_dense.h"	/* generic dense solver header file              */


#include "pihm.h"		/* Data Model and Variable Declarations     */

#include "update.h"
#include "initialize.h"
#include "is_sm_et.h"

#include "6PIHMSimulation/PIHMThread/PIHMThreadProgress.h"

#define UNIT_C 1440		/* Unit Conversions */

/* Function Declarations */
void            initialize(char *, Model_Data, Control_Data *, N_Vector);
//void            is_sm_et(realtype, realtype, Model_Data, N_Vector);
/* Function to calculate right hand side of ODE systems */
int             f(realtype, N_Vector, N_Vector, void *);
void            read_alloc(char *, Model_Data, Control_Data *);	/* Variable definition */
//void            update(realtype, Model_Data);
void            PrintData(FILE **, Control_Data *, Model_Data, N_Vector, realtype);
void            FreeData(Model_Data, Control_Data *);

/* Main Function */
int
PIHM_v2_2(int argc, char *argv[], QProgressBar* progressBar, QString logFileName, int* RunFlag, PIHMThread *thread)
{
    char            tmpLName[20], tmpFName[425];	/* rivFlux File names */
	Model_Data      mData;	/* Model Data                */
	Control_Data    cData;	/* Solver Control Data       */
	N_Vector        CV_Y;	/* State Variables Vector    */
	void           *cvode_mem;	/* Model Data Pointer        */
	int             flag;	/* flag to test return value */
	FILE           *Ofile[25];	/* Output file     */
	char           *ofn[25];
	FILE           *iproj;	/* Project File */
	int             N;	/* Problem size              */
	int             i, j, k;/* loop index                */
	realtype        t;	/* simulation time           */
	realtype        NextPtr, StepSize;	/* stress period & step size */
	clock_t         start, end_r, end_s;	/* system clock at points    */
	realtype        cputime_r, cputime_s;	/* for duration in realtype  */
	char           *filename;

    printf("\nPIHM %d %s %d\n",argc,argv[1],*RunFlag);
	/* Project Input Name */
	if (argc != 2) {
		iproj = fopen("projectName.txt", "r");
        if (iproj == nullptr) {
			printf("\t\nUsage ./pihm project_name");
			printf("\t\n         OR              ");
			printf("\t\nUsage ./pihm, and have a file in the current directory named projectName.txt with the project name in it");
			exit(0);
		} else {
            filename = (char *) malloc(405 * sizeof(char));
			fscanf(iproj, "%s", filename);
			fclose(iproj);
		}
	} else {
		/* get user specified file name in command line */
		filename = (char *) malloc(strlen(argv[1]) * sizeof(char));
		strcpy(filename, argv[1]);
	}
	/* Open Output Files */
    ofn[0] = (char *) malloc((strlen(filename) + 8) * sizeof(char));
	strcpy(ofn[0], filename);
    Ofile[0] = fopen(strcat(ofn[0], ".gw.dat"), "w");
    ofn[1] = (char *) malloc((strlen(filename) + 10) * sizeof(char));
	strcpy(ofn[1], filename);
    Ofile[1] = fopen(strcat(ofn[1], ".surf.dat"), "w");
    ofn[2] = (char *) malloc((strlen(filename) + 9) * sizeof(char));
	strcpy(ofn[2], filename);
    Ofile[2] = fopen(strcat(ofn[2], ".et0.dat"), "w");
    ofn[3] = (char *) malloc((strlen(filename) + 9) * sizeof(char));
	strcpy(ofn[3], filename);
    Ofile[3] = fopen(strcat(ofn[3], ".et1.dat"), "w");
    ofn[4] = (char *) malloc((strlen(filename) + 9) * sizeof(char));
	strcpy(ofn[4], filename);
    Ofile[4] = fopen(strcat(ofn[4], ".et2.dat"), "w");
    ofn[5] = (char *) malloc((strlen(filename) + 8) * sizeof(char));
	strcpy(ofn[5], filename);
    Ofile[5] = fopen(strcat(ofn[5], ".is.dat"), "w");
    ofn[6] = (char *) malloc((strlen(filename) + 10) * sizeof(char));
	strcpy(ofn[6], filename);
    Ofile[6] = fopen(strcat(ofn[6], ".snow.dat"), "w");
	for (i = 0; i < 11; i++) {
        sprintf(tmpLName, ".rivFlx%02d.dat", i);
		strcpy(tmpFName, filename);
		strcat(tmpFName, tmpLName);
		Ofile[7 + i] = fopen(tmpFName, "w");
	}
    ofn[18] = (char *) malloc((strlen(filename) + 11) * sizeof(char));
	strcpy(ofn[18], filename);
    Ofile[18] = fopen(strcat(ofn[18], ".stage.dat"), "w");
    ofn[19] = (char *) malloc((strlen(filename) + 11) * sizeof(char));
	strcpy(ofn[19], filename);
    Ofile[19] = fopen(strcat(ofn[19], ".unsat.dat"), "w");
    ofn[20] = (char *) malloc((strlen(filename) + 10) * sizeof(char));
	strcpy(ofn[20], filename);
    Ofile[20] = fopen(strcat(ofn[20], ".rech.dat"), "w");
    ofn[21] = (char *) malloc((strlen(filename) + 10) * sizeof(char));
		strcpy(ofn[21], filename);
    Ofile[21] = fopen(strcat(ofn[21], ".rbed.dat"), "w");
    ofn[22] = (char *) malloc((strlen(filename) + 11) * sizeof(char));
		strcpy(ofn[22], filename);
    Ofile[22] = fopen(strcat(ofn[22], ".infil.dat"), "w");

	/* allocate memory for model data structure */
	mData = (Model_Data) malloc(sizeof *mData);

	printf("\n ...  PIHM 2.2 is starting ... \n");

	/* read in 9 input files with "filename" as prefix */
    printf("Reading Data Files ... ");
	read_alloc(filename, mData, &cData);
    printf("Done.\n");
	/*
	 * if(mData->UnsatMode ==1) {    }
	 */
	if (mData->UnsatMode == 2) {
		/* problem size */
		N = 3 * mData->NumEle + 2 * mData->NumRiv;
		mData->DummyY = (realtype *) malloc((3 * mData->NumEle + 2 * mData->NumRiv) * sizeof(realtype));
	}
    printf("\nODE Size = %d\n",N);
	/* initial state variable depending on machine */
	CV_Y = N_VNew_Serial(N);

	/* initialize mode data structure */
    printf("Calling Initialize Data Structures ... ");
	initialize(filename, mData, &cData, CV_Y);
    printf("Done.\n");

    printf("\nInitializing CVODE ... ");
	/* allocate memory for solver */
	cvode_mem = CVodeCreate(CV_BDF, CV_NEWTON);
    if (cvode_mem == nullptr) {
		printf("CVodeMalloc failed. \n");
		return (1);
	}
    //flag = CVodeSetFdata(cvode_mem, mData);
	flag = CVodeSetInitStep(cvode_mem, cData.InitStep);
	flag = CVodeSetStabLimDet(cvode_mem, TRUE);
	flag = CVodeSetMaxStep(cvode_mem, cData.MaxStep);
    //flag = CVodeMalloc(cvode_mem, f, cData.StartTime, CV_Y, CV_SS, cData.reltol, &cData.abstol);
    flag = CVodeInit(cvode_mem, f, cData.StartTime, CV_Y);

    flag = CVSpgmr(cvode_mem, PREC_NONE, 0);
	//flag = CVSpgmrSetGSType(cvode_mem, MODIFIED_GS);
    printf("Done.\n");

	/* set start time */
	t = cData.StartTime;
    //start = clock();

	/* start solver in loops */
    printf("\nSolving ODE system ... \n");

    printf("RunFlag = %d %d of %d\n",*RunFlag,i,cData.NumSteps); fflush(stdout);
    int progress;
	for (i = 0; i < cData.NumSteps; i++) {
//        if(*RunFlag == 0)
//            return 0;
		/*
		 * if (cData.Verbose != 1) { printf("  Running: %-4.1f%% ...
		 * ", (100*(i+1)/((realtype) cData.NumSteps)));
		 * fflush(stdout); }
		 */
		/*
		 * inner loops to next output points with ET step size
		 * control
		 */
		while (t < cData.Tout[i + 1]) {
			if (t + cData.ETStep >= cData.Tout[i + 1]) {
				NextPtr = cData.Tout[i + 1];
			} else {
				NextPtr = t + cData.ETStep;
			}
			StepSize = NextPtr - t;

			/* calculate Interception Storage */
			is_sm_et(t, StepSize, mData, CV_Y);
            printf("\n Tsteps = %f of %f %d", t+1, cData.EndTime, *RunFlag);
            /*progress = (int) (100*(t+1)/cData.EndTime);
            if( progress > thread->progressBar->value() )
            {
                printf("Progress %d \%",progress);
                //thread->progressBar->setValue(progress);
                //QApplication::processEvents();
                emit thread->updateProgressBar(progress);
                //QMetaObject::invokeMethod(thread,"updateProgressBar",Qt::DirectConnection,Q_ARG(int,progress));
                //QMetaObject::invokeMethod(obj,"updateProgressBarValue",Qt::QueuedConnection,Q_ARG(int,progress)));
                //PIHMThreadProgress(progressBar, progress);
                //progressBar->setValue(progress);
            }*/
			flag = CVode(cvode_mem, NextPtr, CV_Y, &t, CV_NORMAL);
			update(t, mData);
		}
		PrintData(Ofile, &cData, mData, CV_Y, t);

        progress = (int) (100*(t+1)/cData.EndTime);
        if( progress > thread->progressBar->value() )
        {
            printf(" Progress %d %d %",thread->progressBar->value(), progress);
            emit thread->updateProgressBar(progress);
        }
        if(*RunFlag == 0)
            i = cData.NumSteps;
	}
	/* Free memory */
	N_VDestroy_Serial(CV_Y);
	/* Free integrator memory */
	CVodeFree(&cvode_mem);
	FreeData(mData, &cData);
        for(i=0;i<23;i++)fclose(Ofile[i]);
        for(i=0;i<7;i++)free(ofn[i]);
        for(i=18;i<23;i++)free(ofn[i]);
        free(filename);

        free(mData);
        return 0;
}
