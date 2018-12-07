#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QThread>

class PIHMThread : public QThread
{
        Q_OBJECT
public:
    explicit PIHMThread(QObject *parent = 0, bool b = false);
    void run();

    bool set_Output_Folder(QString output_folder);
    bool set_Project_Name(QString project_name);
    void Log_Message(QString message);


    //Log file is automatically generated for users to debug issues
    std::string get_LogFile_FileName();

    std::string get_Groundwater_Output_FileName();
    std::string get_infil_Output_FileName();
    std::string get_rbed_Output_FileName();
    std::string get_Rech_Output_FileName();
    std::string get_Unsat_Output_FileName();
    std::string get_Stage_Output_FileName();
    std::string get_rivFlx_Output_FileName(int value);
    std::string get_Snow_Output_FileName();
    std::string get_is_Output_FileName();
    std::string get_et2_Output_FileName();
    std::string get_et1_Output_FileName();
    std::string get_et0_Output_FileName();
    std::string get_Surf_Output_FileName();

    //Input FileNames //Error Checking
    //Should users be stuck with project name only?
    std::string get_mesh_Input_FileName();
    std::string get_att_Input_FileName();
    std::string get_forc_Input_FileName();
    std::string get_ibc_Input_FileName();
    std::string get_soil_Input_FileName();
    std::string get_geol_Input_FileName();
    std::string get_lc_Input_FileName();
    std::string get_para_Input_FileName();
    std::string get_riv_Input_FileName();
    std::string get_calib_Input_FileName();
    std::string get_init_Input_FileName();


    // if Stop = true, the thread will break
    // out of the loop, and will be disposed
    bool Stop;

signals:
    // To communicate with Gui Thread
    // we need to emit a signal
    void valueChanged(int);
    void onPIHM_StatusChanged(std::string);
    void onPIHM_Finished(bool);
    void onPIHM_Failed();

public slots:


private:

    bool Check_Output_Folder();
    bool Check_Project_Name();

    QString output_folder;
    QString project_name;
    QString model_version;
    QString logFileName;


};

#endif // MYTHREAD_H
