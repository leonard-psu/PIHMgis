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

#include <fstream>
#include <string>
#include <iostream>
#include <cstring>

#include <QMutex>

#include "sundials/sundials_types.h"
#include "nvector/nvector_serial.h"
#include "cvode/cvode.h"		/* CVODE header file                             */
#include "cvode/cvode_spgmr.h"	/* CVSPGMR linear header file                    */
#include "sundials/sundials_math.h"	/* contains UnitRoundoff, RSqrt, SQR*/
#include "sundials/sundials_dense.h"	/* generic dense solver header file              */

#include "pihm.h"		/* Data Model and Variable Declarations     */
#include "update.h"
#include "initialize.h"
#include "is_sm_et.h"

#include "6PIHMSimulation/PIHMThread/PIHMThread.h"

#define UNIT_C 1440		/* Unit Conversions */
#define Ith(v,i)    NV_Ith_S(v,i-1)       /* Ith numbers components 1..NEQ */

void  initialize(std::string, Model_Data, Control_Data *, N_Vector);
int   f(realtype, N_Vector, N_Vector, void *);
bool  read_alloc(PIHMThread *thread, Model_Data, Control_Data *);	/* Variable definition */
void  PrintData(FILE **, Control_Data *, Model_Data, N_Vector, realtype);
void  FreeData(Model_Data, Control_Data *);

QMutex stop_mutex; //Used to check thread stop status

int PIHM_v2_2(PIHMThread *thread)
{
    if(thread == NULL)
        return 100;

    emit thread->onPIHM_StatusChanged( std::string("Starting PIHM 2.2"));

    //-------------------------------------------------------------------------------------//
    std::cout << "[00] PIHM 2.2 is starting ... " << std::endl; std::cout << std::flush;
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
    int progress_value = 0; //Used to track progress

    //-------------------------------------------------------------------------------------//
    /* START Open Output Files */
    std::cout << "[01] Creating output file locations" << std::endl; std::cout << std::flush;
    //-------------------------------------------------------------------------------------//

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Step One: Setup log file
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::string log_filename(thread->get_LogFile_FileName());
    std::cout << "Logfile: " <<  log_filename << std::endl; std::cout << std::flush;
    if(log_filename.length() < 1)
    {
        emit thread->onPIHM_Finished(true);
        return 101;
    }

    std::ofstream log_file;
    log_file.open(log_filename, std::ios::out);
    if( !log_file.is_open())
    {
        std::cerr << "open lof file failure: " << std::strerror(errno) << '\n';
        emit thread->onPIHM_Finished(true);
        return 102;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Step Two: Create Output Files
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    log_file << "\n[01] Creating PIHM Output file names from Thread";
    std::string tmp_filename = thread->get_Groundwater_Output_FileName();
    log_file << "\ngw = " << tmp_filename;
    Ofile[0] = fopen(tmp_filename.c_str(), "w"); //".gw.dat"

    tmp_filename = thread->get_Surf_Output_FileName();
    log_file << "\nsurf = " << tmp_filename;
    Ofile[1] = fopen(tmp_filename.c_str(), "w"); //".surf.dat"

    tmp_filename = thread->get_et0_Output_FileName();
    log_file << "\net0 = " << tmp_filename;
    Ofile[2] = fopen(tmp_filename.c_str(), "w"); //".et0.dat"

    tmp_filename = thread->get_et1_Output_FileName();
    log_file << "\net1 = " << tmp_filename;
    Ofile[3] = fopen(tmp_filename.c_str(), "w"); //".et1.dat"

    tmp_filename = thread->get_et2_Output_FileName();
    log_file << "\net2 = " << tmp_filename;
    Ofile[4] = fopen(tmp_filename.c_str(), "w"); //".et2.dat"

    tmp_filename = thread->get_is_Output_FileName();
    log_file << "\nis = " << tmp_filename;
    Ofile[5] = fopen(tmp_filename.c_str(), "w"); //".is.dat"

    tmp_filename = thread->get_Snow_Output_FileName();
    log_file << "\nsnow = " << tmp_filename;
    Ofile[6] = fopen(tmp_filename.c_str(), "w"); //".snow.dat"

    for (i = 0; i < 11; i++) {
        tmp_filename = thread->get_rivFlx_Output_FileName(i);
        log_file << "\nriv " << i << " = " << tmp_filename;
        Ofile[7 + i] = fopen(tmp_filename.c_str(), "w");
    }

    tmp_filename = thread->get_Stage_Output_FileName();
    log_file << "\nstage = " << tmp_filename;
    Ofile[18] = fopen(tmp_filename.c_str(), "w"); //".stage.dat"

    tmp_filename = thread->get_Unsat_Output_FileName();
    log_file << "\nunsat = " << tmp_filename;
    Ofile[19] = fopen(tmp_filename.c_str(), "w"); //".unsat.dat"

    tmp_filename = thread->get_Rech_Output_FileName();
    log_file << "\nrech = " << tmp_filename;
    Ofile[20] = fopen(tmp_filename.c_str(), "w"); //".rech.dat"

    tmp_filename = thread->get_rbed_Output_FileName();
    log_file << "\nrbed = " << tmp_filename;
    Ofile[21] = fopen(tmp_filename.c_str(), "w"); //".rbed.dat"

    tmp_filename = thread->get_infil_Output_FileName();
    log_file << "\ninfil = " << tmp_filename;
    Ofile[22] = fopen(tmp_filename.c_str(), "w"); //".infil.dat"

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Check if user requested to stop
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    progress_value = 15;
    emit thread->valueChanged(progress_value);
    emit thread->onPIHM_StatusChanged( std::string("Created PIHM output files"));

    stop_mutex.lock();    // prevent other threads from changing the "Stop" value
    if(thread->Stop)
    {
        log_file.close();
        emit thread->onPIHM_Finished(true);
        emit thread->onPIHM_StatusChanged( std::string("Job cancelled by user"));

        return 103;
    }
    stop_mutex.unlock();

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Step Two: Allocate memory for model data structure
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "[02] Creating model data structure" << std::endl; std::cout << std::flush;
    log_file << "\n[02] Creating model data structure";
    emit thread->onPIHM_StatusChanged( std::string("Creating model data structure"));

    mData = (Model_Data) malloc(sizeof *mData);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Check if user requested to stop
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    progress_value = 30;
    emit thread->valueChanged(progress_value);

    stop_mutex.lock();    // prevent other threads from changing the "Stop" value
    if(thread->Stop)
    {
        log_file.close();
        emit thread->onPIHM_StatusChanged( std::string("Job cancelled by user"));

        emit thread->onPIHM_Finished(true);
        return 104;
    }
    stop_mutex.unlock();

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Step Three: Read input filenames
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "[03] Reading Data Files" << std::endl; std::cout << std::flush;
    log_file << "\n[03] Start Reading Data Files";
    log_file.close(); //Close here so we can open in read_alloc
    emit thread->onPIHM_StatusChanged( std::string("Start Reading Data Files"));

    bool success = read_alloc(thread, mData, &cData);
    if(!success)
    {
        log_file.close();
        emit thread->onPIHM_StatusChanged( std::string("Issue(s) with reading data."));
        emit thread->onPIHM_Finished(true);
        return 105;
    }

    //Re-open log file
    log_file.open(log_filename, std::ios::out| std::ios::app);
    if( !log_file.is_open())
    {
        std::cerr << "open failure: " << std::strerror(errno) << '\n';
        //Must create a log file
        emit thread->onPIHM_Finished(true);
        return 106;
    }
    log_file << "\n[03] Finished Reading Data Files";
    log_file.flush();
    emit thread->onPIHM_StatusChanged( std::string("Finished Reading Data Files"));

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Check if user requested to stop
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    progress_value = 60;
    emit thread->valueChanged(progress_value);

    stop_mutex.lock();    // prevent other threads from changing the "Stop" value
    if(thread->Stop)
    {
        log_file.close();
        emit thread->onPIHM_StatusChanged( std::string("Job cancelled by user"));
        emit thread->onPIHM_Finished(true);
        return 106;
    }
    stop_mutex.unlock();

    if( mData->NumEle <= 0 || mData->NumEle > 100000) //100,000 is a guess for now
    {
        log_file << "\n[03] Invalid Number of Elements: " << mData->NumEle;
        log_file.close();
        emit thread->onPIHM_StatusChanged( std::string("Invalid number of elements"));
        emit thread->onPIHM_Finished(true);
        return 107;
    }

    if( mData->NumRiv <= 0 || mData->NumRiv > 100000) //100,000 is a guess for now
    {
        log_file << "\n[03] Invalid Number of River segments: " << mData->NumRiv;
        log_file.close();
        emit thread->onPIHM_StatusChanged( std::string("Invalid number of river segments"));
        emit thread->onPIHM_Finished(true);
        return 108;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Step Four: Defining Problem Size
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "[04] Defining Problem Size" << std::endl; std::cout << std::flush;
    log_file << "\n[04] Defining Problem Size";
    log_file.flush();
    emit thread->onPIHM_StatusChanged( std::string("Defining Problem Size"));

    if (mData->UnsatMode == 2)
    {
        N = 3 * mData->NumEle + 2 * mData->NumRiv;
        mData->DummyY = (realtype *) malloc((3 * mData->NumEle + 2 * mData->NumRiv) * sizeof(realtype));
    }
    else
    {
        std::cout << "[04] Error: Defining Problem Size or undefined mode requested" << std::endl; std::cout << std::flush;
        log_file << "\n[04] Error: Defining Problem Size or undefined mode requested";
        log_file.close();
        emit thread->onPIHM_StatusChanged( std::string("Error: Defining Problem Size or undefined mode requested."));
        emit thread->onPIHM_Finished(true);
        return 107;
    }

    std::cout << "ODE Size = " << N << std::endl; std::cout << std::flush;
    CV_Y = N_VNew_Serial(N);

    progress_value = 70;
    emit thread->valueChanged(progress_value);

    stop_mutex.lock();    // prevent other threads from changing the "Stop" value
    if(thread->Stop)
    {
        log_file.close();
        emit thread->onPIHM_StatusChanged( std::string("Job cancelled by user"));
        emit thread->onPIHM_Finished(true);
        return 108;
    }
    stop_mutex.unlock();

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Step Five: initialize mode data structure
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "[05] Initialize Data Structures" << std::endl; std::cout << std::flush;
    log_file << "\n[05] Initialize Data Structures";
    log_file.flush();
    emit thread->onPIHM_StatusChanged( std::string("Initialize Data Structures"));

    std::string init_filename = thread->get_init_Input_FileName();
    initialize(init_filename, mData, &cData, CV_Y);

    progress_value = 80;
    emit thread->valueChanged(progress_value);

    stop_mutex.lock();    // prevent other threads from changing the "Stop" value
    if(thread->Stop)
    {
        log_file.close();
        emit thread->onPIHM_StatusChanged( std::string("Job cancelled by user"));
        emit thread->onPIHM_Finished(true);
        return 109;
    }
    stop_mutex.unlock();

    //-------------------------------------------------------------------------------------//
    /* allocate memory for solver */
    std::cout << "[06] Initialize CVODE" << std::endl; std::cout << std::flush;
    //-------------------------------------------------------------------------------------//
    cvode_mem = CVodeCreate(CV_BDF, CV_NEWTON);

    if (cvode_mem == nullptr) {
        printf("CVodeMalloc failed. \n");

        log_file << "\n[06] Initialize CVODE failed";
        log_file.close();
        emit thread->onPIHM_StatusChanged( std::string(" Initialize CVODE failed."));
        emit thread->onPIHM_Finished(true);
        return 110;
    }

    progress_value = 90;
    emit thread->valueChanged(progress_value);

    stop_mutex.lock();    // prevent other threads from changing the "Stop" value
    if(thread->Stop)
    {
        log_file.close();
        emit thread->onPIHM_StatusChanged( std::string("Job cancelled by user"));
        emit thread->onPIHM_Finished(true);
        return 109;
    }
    stop_mutex.unlock();

    flag = CVodeInit(cvode_mem, f, cData.StartTime, CV_Y);
    if (flag != CV_SUCCESS)
        std::cout << "FAILED -> CVodeInit " << std::endl;

    N_Vector abstol = N_VNew_Serial((long int)1);
    Ith(abstol, 1) = cData.abstol;

    flag = CVodeSetUserData(cvode_mem, mData);

    flag = CVodeSStolerances(cvode_mem, cData.reltol, cData.abstol);
    if (flag != CV_SUCCESS)
        std::cout << "FAILED -> CVodeSStolerances " << std::endl;

    flag = CVSpgmr(cvode_mem, PREC_NONE, 0);
    if (flag != CV_SUCCESS)
        std::cout << "FAILED -> CVSpgmr " << std::endl;

    flag = CVodeSetInitStep(cvode_mem, cData.InitStep);
    if (flag != CV_SUCCESS)
        std::cout << "FAILED -> CVodeSetInitStep " << std::endl;

    flag = CVodeSetStabLimDet(cvode_mem, TRUE);
    if (flag != CV_SUCCESS)
        std::cout << "FAILED -> CVodeSetStabLimDet " << std::endl;

    flag = CVodeSetMaxStep(cvode_mem, cData.MaxStep);
    if (flag != CV_SUCCESS)
        std::cout << "FAILED -> CVodeSetMaxStep " << std::endl;

    /* set start time */
    t = cData.StartTime;

    //-------------------------------------------------------------------------------------//
    /* start solver in loops */
    std::cout << "[07] Solving ODE system" << std::endl; std::cout << std::flush;
    //-------------------------------------------------------------------------------------//
    progress_value = 0;
    emit thread->valueChanged(progress_value);

    log_file << "\n[07] Solving ODE system";
    log_file.flush();
    emit thread->onPIHM_StatusChanged( std::string("Solving ODE system. Progress reset to zero."));

    stop_mutex.lock();    // prevent other threads from changing the "Stop" value
    if(thread->Stop)
    {
        log_file.close();
        emit thread->onPIHM_StatusChanged( std::string("Job cancelled by user"));
        emit thread->onPIHM_Finished(true);
        return 110;
    }
    stop_mutex.unlock();

    int progress = 0;
    for (i = 0; i < cData.NumSteps; i++)
    {
        while (t < cData.Tout[i + 1])
        {
            if (t + cData.ETStep >= cData.Tout[i + 1])
            {
                NextPtr = cData.Tout[i + 1];
            }
            else
            {
                NextPtr = t + cData.ETStep;
            }
            StepSize = NextPtr - t;

            stop_mutex.lock();    // prevent other threads from changing the "Stop" value
            if(thread->Stop)
            {
                log_file.close();
                emit thread->onPIHM_StatusChanged( std::string("Job cancelled by user"));
                emit thread->onPIHM_Finished(true);
                return 110;
            }
            stop_mutex.unlock();

            int is_err = is_sm_et(t, StepSize, mData, CV_Y);
if(is_err < 0)
{
    //Warning errors unlikely to be caught.
                    std::cout << "FAILED -> is_sm_et " << std::endl;
                    log_file.close();
                    emit thread->onPIHM_StatusChanged( std::string("Job cancelled by PIHM [is_sm_et error]"));
                    emit thread->onPIHM_Finished(true);
                    return 110;
}

            flag = CVode(cvode_mem, NextPtr, CV_Y, &t, CV_NORMAL);
            if (flag != CV_SUCCESS)
            {
                std::cout << "FAILED -> CVode " << std::endl;
                log_file.close();
                emit thread->onPIHM_StatusChanged( std::string("Job cancelled by PIHM [CVode Error]"));
                emit thread->onPIHM_Finished(true);
                return 110;
            }

            update(t, mData);
        }

        PrintData(Ofile, &cData, mData, CV_Y, t);

        progress = (int) (100*(t+1)/cData.EndTime);

        progress_value = progress;
        emit thread->valueChanged(progress_value);

        stop_mutex.lock();    // prevent other threads from changing the "Stop" value
        if(thread->Stop)
        {
            log_file.close();
            emit thread->onPIHM_StatusChanged( std::string("Job cancelled by user"));
            emit thread->onPIHM_Finished(true);
            emit thread->onPIHM_Failed();
            return 110;
        }
        stop_mutex.unlock();

    }

    log_file.close();

    /* Free memory */
    N_VDestroy_Serial(CV_Y);

    /* Free integrator memory */
    CVodeFree(&cvode_mem);
    FreeData(mData, &cData);
    for(i=0;i<23;i++)
        fclose(Ofile[i]);

    free(mData);

    emit thread->onPIHM_Finished(true);

    return 0;
}
