#ifndef PIHMTHREAD_H
#define PIHMTHREAD_H

#include <QThread>
#include <QProgressBar>

//#include "../1PIHM_v2.2/pihm.h"


class PIHMThread : public QThread
{
public:
    PIHMThread(QObject* parent=0);
    //int i;
    //char **arguments;

    int* RunFlag;

    bool init();
    void run();
    void kill();
    void kill_from_PIHM();

    bool set_Output_Folder(QString output_folder);
    bool set_Project_Name(QString project_name);
    bool set_Model_Version(QString model_version);
    bool set_Progress_Bar(QProgressBar* progressBar);
    bool set_LogFile(QString logFileName);

    int get_Progress_Bar_Value();

    //TODO Error checking
    //Output FileNames
    char* get_Groundwater_Output_FileName();
    char* get_infil_Output_FileName();
    char* get_rbed_Output_FileName();
    char* get_Rech_Output_FileName();
    char* get_Unsat_Output_FileName();
    char* get_Stage_Output_FileName();
    char* get_rivFlx_Output_FileName(int value);
    char* get_Snow_Output_FileName();
    char* get_is_Output_FileName();
    char* get_et2_Output_FileName();
    char* get_et1_Output_FileName();
    char* get_et0_Output_FileName();
    char* get_Surf_Output_FileName();

    //Input FileNames //Error Checking
    //Should users be stuck with project name only?
    char* get_mesh_Input_FileName();
    char* get_att_Input_FileName();
    char* get_forc_Input_FileName();
    char* get_ibc_Input_FileName();
    char* get_soil_Input_FileName();
    char* get_geol_Input_FileName();
    char* get_lc_Input_FileName();
    char* get_para_Input_FileName();
    char* get_riv_Input_FileName();
    char* get_calib_Input_FileName();
    char* get_init_Input_FileName();

    bool has_user_requested_kill_thread();

signals:
    void updateProgressBar(int progress);


private:

    bool Check_Output_Folder();
    bool Check_Project_Name();
    bool Check_Model_Version();
    bool Check_Progress_Bar();
    bool Check_LogFile();


    QString output_folder;
    QString project_name;
    QString model_version;
    QProgressBar* progressBar;
    QString logFileName;
    bool kill_thread;


};

#endif
