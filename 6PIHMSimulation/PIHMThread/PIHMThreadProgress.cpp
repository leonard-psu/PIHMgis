#include "PIHMThreadProgress.h"
#include "globals.h"

void PIHMThreadProgress(QProgressBar *MyProgressBar, int MyProgress)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMThreadProgress";

    try {
        MyProgressBar->setValue( MyProgress );
        QApplication::processEvents();

    } catch (...) {
        qDebug() << "Error: PIHMThreadProgress is returning w/o checking";
    }
    return;
}
