#include "main.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PIHMgisDialog w;
    w.show();

    return a.exec();
}
