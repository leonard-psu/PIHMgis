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
void            initialize(PIHMThread *thread, Model_Data, Control_Data *, N_Vector);
//void            is_sm_et(realtype, realtype, Model_Data, N_Vector);
/* Function to calculate right hand side of ODE systems */
int             f(realtype, N_Vector, N_Vector, void *);
void            read_alloc(PIHMThread *thread, Model_Data, Control_Data *);	/* Variable definition */
//void            update(realtype, Model_Data);
void            PrintData(FILE **, Control_Data *, Model_Data, N_Vector, realtype);
void            FreeData(Model_Data, Control_Data *);

/* Main Function */
int
//PIHM_v2_2(int argc, char *argv[], QProgressBar* progressBar, QString logFileName, int* RunFlag, PIHMThread *thread)
PIHM_v2_2(PIHMThread *thread)
{
    //-------------------------------------------------------------------------------------//
    printf("\n [00] PIHM 2.2 is starting ... \n");
    //-------------------------------------------------------------------------------------//

    Model_Data      mData;              /* Model Data                */
    N_Vector        CV_Y;               /* State Variables Vector    */
    Control_Data    cData;              /* Solver Control Data       */
    void           *cvode_mem;          /* Model Data Pointer        */
    FILE           *Ofile[25];          /* Output files              */
    realtype        t = 0;              /* simulation time           */
    realtype        NextPtr, StepSize;	/* stress period & step size */
    int             N = 0;              /* Problem size              */
    int             i = 0;              /* loop index                */
    int             flag = 0;           /* flag to test return value */

    //-------------------------------------------------------------------------------------//
    /* START Open Output Files */
    printf("\n [01] Creating output file locations");
    //-------------------------------------------------------------------------------------//

    char *tmp_filename = thread->get_Groundwater_Output_FileName();
    Ofile[0] = fopen(tmp_filename, "w"); //".gw.dat"
    tmp_filename = thread->get_Surf_Output_FileName();
    Ofile[1] = fopen(tmp_filename, "w"); //".surf.dat"
    tmp_filename = thread->get_et0_Output_FileName();
    Ofile[2] = fopen(tmp_filename, "w"); //".et0.dat"
    tmp_filename = thread->get_et1_Output_FileName();
    Ofile[3] = fopen(tmp_filename, "w"); //".et1.dat"
    tmp_filename = thread->get_et2_Output_FileName();
    Ofile[4] = fopen(tmp_filename, "w"); //".et2.dat"
    tmp_filename = thread->get_is_Output_FileName();
    Ofile[5] = fopen(tmp_filename, "w"); //".is.dat"
    tmp_filename = thread->get_Snow_Output_FileName();
    Ofile[6] = fopen(tmp_filename, "w"); //".snow.dat"
    for (i = 0; i < 11; i++) {
        tmp_filename = thread->get_rivFlx_Output_FileName(i);
        Ofile[7 + i] = fopen(tmp_filename, "w");
    }
    tmp_filename = thread->get_Stage_Output_FileName();
    Ofile[18] = fopen(tmp_filename, "w"); //".stage.dat"
    tmp_filename = thread->get_Unsat_Output_FileName();
    Ofile[19] = fopen(tmp_filename, "w"); //".unsat.dat"
    tmp_filename = thread->get_Rech_Output_FileName();
    Ofile[20] = fopen(tmp_filename, "w"); //".rech.dat"
    tmp_filename = thread->get_rbed_Output_FileName();
    Ofile[21] = fopen(tmp_filename, "w"); //".rbed.dat"
    tmp_filename = thread->get_infil_Output_FileName();
    Ofile[22] = fopen(tmp_filename, "w"); //".infil.dat"
    tmp_filename = nullptr;

    /* END Open Output Files */

    //-------------------------------------------------------------------------------------//
    /* allocate memory for model data structure */
    printf("\n [02] Creating model data structure");
    //-------------------------------------------------------------------------------------//
    mData = (Model_Data) malloc(sizeof *mData);

    //-------------------------------------------------------------------------------------//
    /* read in 9 input files with "filename" as prefix */
    printf("\n [03] Reading Data Files");
    //-------------------------------------------------------------------------------------//

    read_alloc(thread, mData, &cData);

    //-------------------------------------------------------------------------------------//
    printf("\n [04] Defining Problem Size");
    //-------------------------------------------------------------------------------------//
    /*
     * if(mData->UnsatMode ==1) {    }
     */
    if (mData->UnsatMode == 2) {
        /* problem size */
        N = 3 * mData->NumEle + 2 * mData->NumRiv;
        mData->DummyY = (realtype *) malloc((3 * mData->NumEle + 2 * mData->NumRiv) * sizeof(realtype));
    }
    else
    {
        printf("\n [04] Error: Defining Problem Size as ubdefined mode requested");
        return (1000);
    }


    printf("\nODE Size = %d\n",N);
    /* initial state variable depending on machine */
    CV_Y = N_VNew_Serial(N);

    //-------------------------------------------------------------------------------------//
    /* initialize mode data structure */
    printf("\n [05] Initialize Data Structures");
    //-------------------------------------------------------------------------------------//
    initialize(thread, mData, &cData, CV_Y);

    //-------------------------------------------------------------------------------------//
    /* allocate memory for solver */
    printf("\n [06] Initialize CVODE");
    //-------------------------------------------------------------------------------------//
    cvode_mem = CVodeCreate(CV_BDF, CV_NEWTON);
    if (cvode_mem == nullptr) {
        printf("CVodeMalloc failed. \n");
        return (1001);
    }

    //flag = CVodeSetFdata(cvode_mem, mData);
    flag = CVodeSetInitStep(cvode_mem, cData.InitStep);
    flag = CVodeSetStabLimDet(cvode_mem, TRUE);
    flag = CVodeSetMaxStep(cvode_mem, cData.MaxStep);
    //flag = CVodeMalloc(cvode_mem, f, cData.StartTime, CV_Y, CV_SS, cData.reltol, &cData.abstol);
    flag = CVodeInit(cvode_mem, f, cData.StartTime, CV_Y);

    flag = CVSpgmr(cvode_mem, PREC_NONE, 0);
    //flag = CVSpgmrSetGSType(cvode_mem, MODIFIED_GS);

    /* set start time */
    t = cData.StartTime;
    //start = clock();

    //-------------------------------------------------------------------------------------//
    /* start solver in loops */
    printf("\n [07] Solving ODE system");
    //-------------------------------------------------------------------------------------//

    int progress;
    for (i = 0; i < cData.NumSteps; i++) {

        while (t < cData.Tout[i + 1]) {
            if (t + cData.ETStep >= cData.Tout[i + 1]) {
                NextPtr = cData.Tout[i + 1];
            } else {
                NextPtr = t + cData.ETStep;
            }
            StepSize = NextPtr - t;

            if(thread->has_user_requested_kill_thread())
            {
                printf("\n Trying to stop PIHM nicely.");
                i = cData.NumSteps;
            }

            //-------------------------------------------------------------------------------------//
            /* calculate Interception Storage */
            //-------------------------------------------------------------------------------------//
            is_sm_et(t, StepSize, mData, CV_Y);

            printf("\n Tsteps = %f of %f ", t+1, cData.EndTime);

            progress = (int) (100*(t+1)/cData.EndTime);
            if( progress > thread->get_Progress_Bar_Value() )
            {
                printf("Progress %d ",progress);
                emit thread->updateProgressBar(progress);
            }

            flag = CVode(cvode_mem, NextPtr, CV_Y, &t, CV_NORMAL);
            update(t, mData);
        }
        PrintData(Ofile, &cData, mData, CV_Y, t);

        progress = (int) (100*(t+1)/cData.EndTime);
        if( progress > thread->get_Progress_Bar_Value() )
        {
            printf(" Progress %d %d", thread->get_Progress_Bar_Value(), progress);
            emit thread->updateProgressBar(progress);
        }

        if(thread->has_user_requested_kill_thread())
        {
            printf("\n Trying to stop PIHM nicely.");
            i = cData.NumSteps;
        }

    }
    /* Free memory */
    N_VDestroy_Serial(CV_Y);

    /* Free integrator memory */
    CVodeFree(&cvode_mem);
    FreeData(mData, &cData);
    for(i=0;i<23;i++)
        fclose(Ofile[i]);

    free(mData);
    return 0;
}
