#include <QDebug>

#include "sundials/sundials_types.h"
#include "nvector/nvector_serial.h"

#include "PIHMThread.h"
#include "6PIHMSimulation/PIHMSrc/PIHM_v2.2/pihm.h"
#include "globals.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PIHMThread Constructor
// Parent is Simulation Window
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PIHMThread::PIHMThread(QObject * parent)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMThread";

    try {
        kill_thread = false;
        setParent(parent);
        setTerminationEnabled(1);
    } catch (...) {
        qDebug() << "Error: PIHMThread is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check everything is ready
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PIHMThread::init()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMThread::init";

    try {

        bool of_check = Check_Output_Folder();
        if(!of_check)
            return false;
        bool pn_check = Check_Project_Name();
        if(!pn_check)
            return false;
        bool mv_check = Check_Model_Version();
        if(!mv_check)
            return false;
        bool pb_check = Check_Progress_Bar();
        if(!pb_check)
            return false;
        bool lf_check = Check_LogFile();
        if(!lf_check)
            return false;

        //        RunFlag  = new int[1];
        //        *RunFlag = _RunFlag;

    } catch (...) {
        qDebug() << "Error: PIHMThread::init is returning w/o checking";
        return false;
    }
    return true;
}


void PIHMThread::run()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMThread::run";

    try {
        qDebug() << "\nNew Thread Started from PIHMThread::run\n";
        //this->RunFlag = new int[1];

        //*RunFlag = 1;
        //qDebug() << "Run Flag = " << *RunFlag << "\n";
        qDebug() << "Calling PIHM now ... \n";

        //if (ModelVersion == "PIHM v2.2")
        //{
        //    PIHM_v2_2(i, arguments, this->progressBar, logFileName, this->RunFlag, this);
        //}
        PIHM_v2_2(this);

    } catch (...) {
        qDebug() << "Error: PIHMThread::run is returning w/o checking";
    }
    return;
}

void PIHMThread::kill()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMThread::kill";

    try {
        qDebug() << "PIHM Thread KILL invoked...\n";
        //*RunFlag = 0; // Forces PIHM Simulation to Stop
        kill_thread = true;
        qDebug() << "RunFlag set to "<< *RunFlag << "\n";
        qDebug() << "Waiting for PIHM to clear...\n";
        //wait(20);
        wait();
        //terminate();
    } catch (...) {
        qDebug() << "Error: PIHMThread::kill is returning w/o checking";
    }
}

void PIHMThread::kill_from_PIHM()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMThread::kill_from_PIHM";

    try {
        qDebug() << "Info: Call from PIHM to Kill this Thread\n";
        kill();
    } catch (...) {
        qDebug() << "Error: PIHMThread::kill_from_PIHM is returning w/o checking";
    }
}


bool PIHMThread::has_user_requested_kill_thread()
{
    return kill_thread;
}


void PIHMThread::updateProgressBar(int progress)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMThread::updateProgressBar";

    try {
        qDebug() << "From SIGNAL PIHMThread::updateProgressBar " << progress;
        QMetaObject::invokeMethod(parent(),"updateProgressBarValue",Q_ARG(int,progress));
        //this->progressBar->setValue(progress);
    } catch (...) {
        qDebug() << "Error: PIHMThread::updateProgressBar is returning w/o checking";
    }

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to set Output Folder variable (OUTPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PIHMThread::set_Output_Folder(QString folder){
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMThread::set_Output_Folder";

    try {

        output_folder = folder;
        return Check_Output_Folder();

    } catch (...) {
        qDebug() << "Error: PIHMThread::set_Output_Folder is returning w/o checking";
        return false;
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to set Project variable (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PIHMThread::set_Project_Name(QString name){
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMThread::set_Project_Name";

    try {
        project_name =name;
        return Check_Project_Name();
    } catch (...) {
        qDebug() << "Error: PIHMThread::set_Project_Name is returning w/o checking";
        return false;
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to set Model Version variable (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PIHMThread::set_Model_Version(QString version){
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMThread::set_Model_Version";

    try {
        model_version = version;
        return Check_Model_Version();

    } catch (...) {
        qDebug() << "Error: PIHMThread::set_Model_Version is returning w/o checking";
        return false;
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to set Progress_Bar variable (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PIHMThread::set_Progress_Bar(QProgressBar* value){
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMThread::set_Progress_Bar";

    try {
        progressBar = value;
        return Check_Progress_Bar();

    } catch (...) {
        qDebug() << "Error: PIHMThread::set_Progress_Bar is returning w/o checking";
        return false;
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get Progress Bar variable (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PIHMThread::get_Progress_Bar_Value()
{
    try {
        if(progressBar == nullptr)
        {
            //Do nothing
            return 0;
        }
        else
        {
            return progressBar->value();
        }
    } catch (...) {
        qDebug() << "Error: PIHMThread::get_Progress_Bar_Value is returning w/o checking";
        return 0;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to set Log File variable (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PIHMThread::set_LogFile(QString value){
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMThread::set_LogFile";

    try {
        logFileName = value;
        return Check_LogFile();

    } catch (...) {
        qDebug() << "Error: PIHMThread::set_LogFile is returning w/o checking";
        return false;
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Check Output Folder exists (OUTPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PIHMThread::Check_Output_Folder()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMThread::Check_Output_Folder";

    try {

        if(output_folder.isNull() || output_folder.isEmpty())
        {
            return false;
        }

        if (QDir(output_folder).exists() )
        {
            return true;
        }
        else
        {
            return false;
        }

    } catch (...) {
        qDebug() << "Error: PIHMThread::Check_Output_Folder is returning w/o checking";
        return false;
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Check Project Name has been set (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PIHMThread::Check_Project_Name()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMThread::Check_Project_Name";

    try {

        if(project_name.isNull() || project_name.isEmpty())
        {
            return false;
        }
        else
        {
            return true;
        }

    } catch (...) {
        qDebug() << "Error: PIHMThread::Check_Output_Folder is returning w/o checking";
        return false;
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Check Model Version has been set (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PIHMThread::Check_Model_Version()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMThread::Check_Model_Version";

    try {

        if(model_version.isNull() || model_version.isEmpty())
        {
            return false;
        }
        else
        {
            return true;
        }

    } catch (...) {
        qDebug() << "Error: PIHMThread::Check_Model_Version is returning w/o checking";
        return false;
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Check Progress Bar has been set (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PIHMThread::Check_Progress_Bar()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMThread::Check_Progress_Bar";

    try {

        if(progressBar == nullptr)
        {
            return false;
        }
        else
        {
            return true;
        }

    } catch (...) {
        qDebug() << "Error: PIHMThread::Check_Output_Folder is returning w/o checking";
        return false;
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to Check Log File has been set (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PIHMThread::Check_LogFile()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMThread::Check_LogFile";

    try {

        if(logFileName.isNull() || logFileName.isEmpty())
        {
            return false;
        }
        else
        {
            return true;
        }

    } catch (...) {
        qDebug() << "Error: PIHMThread::Check_LogFile is returning w/o checking";
        return false;
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get Groundwater fileName (OUTPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char* PIHMThread::get_Groundwater_Output_FileName()
{
    QString output(output_folder + "/" + project_name + ".gw.dat");
    QByteArray string = output.toLatin1();
    return string.data();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get Surface fileName (OUTPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char* PIHMThread::get_Surf_Output_FileName()
{
    QString output(output_folder + "/" + project_name + ".surf.dat");
    QByteArray string = output.toLatin1();
    return string.data();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get et0 fileName (OUTPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char* PIHMThread::get_et0_Output_FileName()
{
    QString output(output_folder + "/" + project_name + ".et0.dat");
    QByteArray string = output.toLatin1();
    return string.data();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get et1 fileName (OUTPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char* PIHMThread::get_et1_Output_FileName()
{
    QString output(output_folder + "/" + project_name + ".et1.dat");
    QByteArray string = output.toLatin1();
    return string.data();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get et2 fileName (OUTPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char* PIHMThread::get_et2_Output_FileName()
{
    QString output(output_folder + "/" + project_name + ".et2.dat");
    QByteArray string = output.toLatin1();
    return string.data();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get is fileName (OUTPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char* PIHMThread::get_is_Output_FileName()
{
    QString output(output_folder + "/" + project_name + ".is.dat");
    QByteArray string = output.toLatin1();
    return string.data();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get snow fileName (OUTPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char* PIHMThread::get_Snow_Output_FileName()
{
    QString output(output_folder + "/" + project_name + ".snow.dat");
    QByteArray string = output.toLatin1();
    return string.data();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get rivFlx fileName (OUTPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char* PIHMThread::get_rivFlx_Output_FileName(int value)
{
    QString num_str;
    num_str = QString::number(value).rightJustified(2, '0');

    QString output(output_folder + "/" + project_name + ".rivFlx" + num_str + ".dat");
    QByteArray string = output.toLatin1();
    return string.data();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get stage fileName (OUTPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char* PIHMThread::get_Stage_Output_FileName()
{
    QString output(output_folder + "/" + project_name + ".stage.dat");
    QByteArray string = output.toLatin1();
    return string.data();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get unsat fileName (OUTPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char* PIHMThread::get_Unsat_Output_FileName()
{
    QString output(output_folder + "/" + project_name + ".unsat.dat");
    QByteArray string = output.toLatin1();
    return string.data();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get rech fileName (OUTPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char* PIHMThread::get_Rech_Output_FileName()
{
    QString output(output_folder + "/" + project_name + ".rech.dat");
    QByteArray string = output.toLatin1();
    return string.data();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get rbed fileName (OUTPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char* PIHMThread::get_rbed_Output_FileName()
{
    QString output(output_folder + "/" + project_name + ".rbed.dat");
    QByteArray string = output.toLatin1();
    return string.data();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get infil fileName (OUTPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char* PIHMThread::get_infil_Output_FileName()
{
    QString output(output_folder + "/" + project_name + ".infil.dat");
    QByteArray string = output.toLatin1();
    return string.data();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get mesh fileName (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char* PIHMThread::get_mesh_Input_FileName()
{
    QString output(output_folder + "/" + project_name + ".mesh");
    QByteArray string = output.toLatin1();
    return string.data();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get att fileName (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char* PIHMThread::get_att_Input_FileName()
{
    QString output(output_folder + "/" + project_name + ".att");
    QByteArray string = output.toLatin1();
    return string.data();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get forc fileName (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char* PIHMThread:: get_forc_Input_FileName()
{
    QString output(output_folder + "/" + project_name + ".forc");
    QByteArray string = output.toLatin1();
    return string.data();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get ibc fileName (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char* PIHMThread::get_ibc_Input_FileName()
{
    QString output(output_folder + "/" + project_name + ".ibc");
    QByteArray string = output.toLatin1();
    return string.data();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get soil fileName (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char* PIHMThread::get_soil_Input_FileName()
{
    QString output(output_folder + "/" + project_name + ".soil");
    QByteArray string = output.toLatin1();
    return string.data();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get geol fileName (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char* PIHMThread::get_geol_Input_FileName()
{
    QString output(output_folder + "/" + project_name + ".geol");
    QByteArray string = output.toLatin1();
    return string.data();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get lc fileName (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char* PIHMThread::get_lc_Input_FileName()
{
    QString output(output_folder + "/" + project_name + ".lc");
    QByteArray string = output.toLatin1();
    return string.data();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get para fileName (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char* PIHMThread::get_para_Input_FileName()
{
    QString output(output_folder + "/" + project_name + ".para");
    QByteArray string = output.toLatin1();
    return string.data();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get riv fileName (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char* PIHMThread::get_riv_Input_FileName()
{
    QString output(output_folder + "/" + project_name + ".riv");
    QByteArray string = output.toLatin1();
    return string.data();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get calib fileName (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char* PIHMThread::get_calib_Input_FileName()
{
    QString output(output_folder + "/" + project_name + ".calib");
    QByteArray string = output.toLatin1();
    return string.data();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get init fileName (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char* PIHMThread::get_init_Input_FileName()
{
    QString output(output_folder + "/" + project_name + ".init");
    QByteArray string = output.toLatin1();
    return string.data();
}


