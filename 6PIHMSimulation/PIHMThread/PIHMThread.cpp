#include <QDebug>

#include "sundials/sundials_types.h"
#include "nvector/nvector_serial.h"

#include "PIHMThread.h"
#include "6PIHMSimulation/PIHMSrc/PIHM_v2.2/pihm.h"
#include "globals.h"


PIHMThread::PIHMThread(QObject * parent)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMThread";

    try {
        setParent(parent);
        setTerminationEnabled(1);
    } catch (...) {
        qDebug() << "Error: PIHMThread is returning w/o checking";
    }
}

void PIHMThread::init(int _i, char **_arguments, QProgressBar* _progressBar, QString _logFileName, QString _ModelVersion, int _RunFlag)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMThread::init";

    try {
        i            = _i;
        arguments    = _arguments;
        progressBar  = _progressBar;
        logFileName  = _logFileName;
        ModelVersion = _ModelVersion;

        RunFlag  = new int[1];
        *RunFlag = _RunFlag;
    } catch (...) {
        qDebug() << "Error: PIHMThread::init is returning w/o checking";
    }
}

void PIHMThread::run()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMThread::run";

    try {
        qDebug() << "\nNew Thread Started from PIHMThread::run\n";
        //this->RunFlag = new int[1];

        //*RunFlag = 1;
        qDebug() << "Run Flag = " << *RunFlag << "\n";
        qDebug() << "Calling PIHM now ... \n";

        if (ModelVersion == "PIHM v2.2")
        {
            PIHM_v2_2(i, arguments, this->progressBar, logFileName, this->RunFlag, this);
        }
        //exec();

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
        *RunFlag = 0; // Forces PIHM Simulation to Stop
        qDebug() << "RunFlag set to "<< *RunFlag << "\n";
        qDebug() << "Waiting for PIHM to clear...\n";
        //wait(20);
        wait();
        //terminate();
    } catch (...) {
        qDebug() << "Error: PIHMThread::kill is returning w/o checking";
    }
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
