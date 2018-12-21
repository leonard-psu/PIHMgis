#include "PIHMThread.h"
#include <QDebug>
#include <QMutex>
#include "globals.h"
#include <fstream>
#include <string>
#include<iostream>
#include <QDateTime>

#include "6PIHMSimulation/PIHMSrc/PIHM_v2.2/pihm.h"

Q_DECLARE_METATYPE(std::string)

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PIHMThread Constructor
// Parent is Main Window, filename is the open project text file used to store project details
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PIHMThread::PIHMThread(QObject *parent, bool b) :
    QThread(parent), Stop(b)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMThread";

    try {
        //Do nothing for now
    } catch (...) {
        qDebug() << "Error: PIHMThread is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// run() will be called when a thread starts
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMThread::run()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start run";

    try {

        int error = PIHM_v2_2(this);
        Log_Message("PIHM_v2_2 return status: " + QString::number(error));

        if(print_debug_messages)
            qDebug() << "PIHM_v2_2 return status:" << error << " \n";

    } catch (...) {
        qDebug() << "Error: run is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check Log Message USING PARENT WINDOW
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMThread::Log_Message(QString message)
{
    try {

        if(redirect_debug_messages_to_log)
        {
            ((PIHMgisDialog*)this->parent())->Log_Message( message );
        }

    } catch (...) {
        qDebug() << "Error: Log_Message is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to set Output Folder variable (OUTPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PIHMThread::set_Output_Folder(QString folder)
{
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
bool PIHMThread::set_Project_Name(QString name)
{
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
// Helper Function to get LogFile set by user (OUTPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string PIHMThread::get_LogFile_FileName()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMThread::get_LogFile_FileName";

    try {

        QDateTime now = QDateTime::currentDateTime();
        QString now_str = now.toString();
        now_str = now_str.replace(":", "_");

        logFileName = output_folder + "/" + project_name + "_" + now_str + ".log";
        logFileName = logFileName.replace(" ", "_");
        return logFileName.toUtf8().toStdString();

    } catch (...) {
        qDebug() << "Error: PIHMThread::get_LogFile_FileName is returning w/o checking";
    }
    return std::string("");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get Groundwater fileName (OUTPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string PIHMThread::get_Groundwater_Output_FileName()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMThread::get_Groundwater_Output_FileName";

    try {

        QString output(output_folder + "/" + project_name + ".gw.dat");
        return output.toUtf8().toStdString();

    } catch (...) {
        qDebug() << "Error: PIHMThread::get_Groundwater_Output_FileName is returning w/o checking";
    }
    return std::string("");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get Surface fileName (OUTPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string PIHMThread::get_Surf_Output_FileName()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMThread::get_Surf_Output_FileName";

    try {

        QString output(output_folder + "/" + project_name + ".surf.dat");
        return output.toUtf8().toStdString();

    } catch (...) {
        qDebug() << "Error: PIHMThread::get_Surf_Output_FileName is returning w/o checking";
    }
    return std::string("");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get et0 fileName (OUTPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string PIHMThread::get_et0_Output_FileName()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMThread::get_et0_Output_FileName";

    try {

        QString output(output_folder + "/" + project_name + ".et0.dat");
        return output.toUtf8().toStdString();

    } catch (...) {
        qDebug() << "Error: PIHMThread::get_et0_Output_FileName is returning w/o checking";
    }
    return std::string("");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get et1 fileName (OUTPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string PIHMThread::get_et1_Output_FileName()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMThread::get_et1_Output_FileName";

    try {

        QString output(output_folder + "/" + project_name + ".et1.dat");
        return output.toUtf8().toStdString();

    } catch (...) {
        qDebug() << "Error: PIHMThread::get_et1_Output_FileName is returning w/o checking";
    }
    return std::string("");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get et2 fileName (OUTPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string PIHMThread::get_et2_Output_FileName()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMThread::get_et2_Output_FileName";

    try {

        QString output(output_folder + "/" + project_name + ".et2.dat");
        return output.toUtf8().toStdString();

    } catch (...) {
        qDebug() << "Error: PIHMThread::get_et2_Output_FileName is returning w/o checking";
    }
    return std::string("");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get is fileName (OUTPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string PIHMThread::get_is_Output_FileName()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMThread::get_is_Output_FileName";

    try {

        QString output(output_folder + "/" + project_name + ".is.dat");
        return output.toUtf8().toStdString();

    } catch (...) {
        qDebug() << "Error: PIHMThread::get_is_Output_FileName is returning w/o checking";
    }
    return std::string("");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get snow fileName (OUTPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string PIHMThread::get_Snow_Output_FileName()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMThread::get_Snow_Output_FileName";

    try {

        QString output(output_folder + "/" + project_name + ".snow.dat");
        return output.toUtf8().toStdString();

    } catch (...) {
        qDebug() << "Error: PIHMThread::get_Snow_Output_FileName is returning w/o checking";
    }
    return std::string("");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get rivFlx fileName (OUTPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string PIHMThread::get_rivFlx_Output_FileName(int value)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMThread::get_rivFlx_Output_FileName";

    try {

        QString num_str;
        num_str = QString::number(value).rightJustified(2, '0');

        QString output(output_folder + "/" + project_name + ".rivFlx" + num_str + ".dat");
        return output.toUtf8().toStdString();

    } catch (...) {
        qDebug() << "Error: PIHMThread::get_rivFlx_Output_FileName is returning w/o checking";
    }
    return std::string("");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get stage fileName (OUTPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string PIHMThread::get_Stage_Output_FileName()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMThread::get_Stage_Output_FileName";

    try {

        QString output(output_folder + "/" + project_name + ".stage.dat");
        return output.toUtf8().toStdString();

    } catch (...) {
        qDebug() << "Error: PIHMThread::get_Stage_Output_FileName is returning w/o checking";
    }
    return std::string("");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get unsat fileName (OUTPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string PIHMThread::get_Unsat_Output_FileName()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMThread::get_Unsat_Output_FileName";

    try {

        QString output(output_folder + "/" + project_name + ".unsat.dat");
        return output.toUtf8().toStdString();

    } catch (...) {
        qDebug() << "Error: PIHMThread::get_Unsat_Output_FileName is returning w/o checking";
    }
    return std::string("");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get rech fileName (OUTPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string PIHMThread::get_Rech_Output_FileName()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMThread::get_Rech_Output_FileName";

    try {

        QString output(output_folder + "/" + project_name + ".rech.dat");
        return output.toUtf8().toStdString();

    } catch (...) {
        qDebug() << "Error: PIHMThread::get_Rech_Output_FileName is returning w/o checking";
    }
    return std::string("");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get rbed fileName (OUTPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string PIHMThread::get_rbed_Output_FileName()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMThread::get_rbed_Output_FileName";

    try {

        QString output(output_folder + "/" + project_name + ".rbed.dat");
        return output.toUtf8().toStdString();

    } catch (...) {
        qDebug() << "Error: PIHMThread::get_rbed_Output_FileName is returning w/o checking";
    }
    return std::string("");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get infil fileName (OUTPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string PIHMThread::get_infil_Output_FileName()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMThread::get_infil_Output_FileName";

    try {

        QString output(output_folder + "/" + project_name + ".infil.dat");
        return output.toUtf8().toStdString();

    } catch (...) {
        qDebug() << "Error: PIHMThread::get_infil_Output_FileName is returning w/o checking";
    }
    return std::string("");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get mesh fileName (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string PIHMThread::get_mesh_Input_FileName()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMThread::get_mesh_Input_FileName";

    try {

        QString output(output_folder + "/" + project_name + ".mesh");
        return output.toUtf8().toStdString();

    } catch (...) {
        qDebug() << "Error: PIHMThread::get_mesh_Input_FileName is returning w/o checking";
    }
    return std::string("");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get att fileName (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string PIHMThread::get_att_Input_FileName()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMThread::get_att_Input_FileName";

    try {

        QString output(output_folder + "/" + project_name + ".att");
        return output.toUtf8().toStdString();

    } catch (...) {
        qDebug() << "Error: PIHMThread::get_att_Input_FileName is returning w/o checking";
    }
    return std::string("");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get forc fileName (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string PIHMThread:: get_forc_Input_FileName()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMThread::get_forc_Input_FileName";

    try {

        QString output(output_folder + "/" + project_name + ".forc");
        return output.toUtf8().toStdString();

    } catch (...) {
        qDebug() << "Error: PIHMThread::get_forc_Input_FileName is returning w/o checking";
    }
    return std::string("");
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get ibc fileName (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string PIHMThread::get_ibc_Input_FileName()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMThread::get_ibc_Input_FileName";

    try {

        QString output(output_folder + "/" + project_name + ".ibc");
        return output.toUtf8().toStdString();

    } catch (...) {
        qDebug() << "Error: PIHMThread::get_ibc_Input_FileName is returning w/o checking";
    }
    return std::string("");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get soil fileName (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string PIHMThread::get_soil_Input_FileName()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMThread::get_soil_Input_FileName";

    try {

        QString output(output_folder + "/" + project_name + ".soil");
        return output.toUtf8().toStdString();

    } catch (...) {
        qDebug() << "Error: PIHMThread::get_soil_Input_FileName is returning w/o checking";
    }
    return std::string("");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get geol fileName (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string PIHMThread::get_geol_Input_FileName()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMThread::get_geol_Input_FileName";

    try {

        QString output(output_folder + "/" + project_name + ".geol");
        return output.toUtf8().toStdString();

    } catch (...) {
        qDebug() << "Error: PIHMThread::get_geol_Input_FileName is returning w/o checking";
    }
    return std::string("");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get lc fileName (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string PIHMThread::get_lc_Input_FileName()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMThread::get_lc_Input_FileName";

    try {

        QString output(output_folder + "/" + project_name + ".lc");
        return output.toUtf8().toStdString();

    } catch (...) {
        qDebug() << "Error: PIHMThread::get_lc_Input_FileName is returning w/o checking";
    }
    return std::string("");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get para fileName (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string PIHMThread::get_para_Input_FileName()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMThread::get_para_Input_FileName";

    try {

        QString output(output_folder + "/" + project_name + ".para");
        return output.toUtf8().toStdString();

    } catch (...) {
        qDebug() << "Error: PIHMThread::get_para_Input_FileName is returning w/o checking";
    }
    return std::string("");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get riv fileName (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string PIHMThread::get_riv_Input_FileName()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMThread::get_riv_Input_FileName";

    try {

        QString output(output_folder + "/" + project_name + ".riv");
        return output.toUtf8().toStdString();

    } catch (...) {
        qDebug() << "Error: PIHMThread::get_riv_Input_FileName is returning w/o checking";
    }
    return std::string("");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get calib fileName (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string PIHMThread::get_calib_Input_FileName()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMThread::get_calib_Input_FileName";

    try {

        QString output(output_folder + "/" + project_name + ".calib");
        return output.toUtf8().toStdString();

    } catch (...) {
        qDebug() << "Error: PIHMThread::get_calib_Input_FileName is returning w/o checking";
    }
    return std::string("");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get init fileName (INPUT)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string PIHMThread::get_init_Input_FileName()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMThread::get_init_Input_FileName";

    try {

        QString output(output_folder + "/" + project_name + ".init");
        return output.toUtf8().toStdString();

    } catch (...) {
        qDebug() << "Error: PIHMThread::get_init_Input_FileName is returning w/o checking";
    }
    return std::string("");
}




