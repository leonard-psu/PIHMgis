#include "qcustomplotmainwindow.h"
#include "ui_qcustomplotmainwindow.h"
#include "globals.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QCustomPlotMainWindow Constructor
// Parent is Main Window, filename is the open project text file used to store project details
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
QCustomPlotMainWindow::QCustomPlotMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QCustomPlotMainWindow)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start QCustomPlotMainWindow";

    try {
        this->setWindowTitle("PIHM GIS");
        ui->setupUi(this);

        QAction *PrintAction = new QAction(tr("&Save..."),this);
        PrintAction->setShortcut(tr("Ctrl+S"));
        connect(PrintAction,SIGNAL(triggered()),this,SLOT(SaveAsPDF()));

        ui->QCustomPlotWidget->setStyleSheet("border: 1px solid black");
    } catch (...) {
        qDebug() << "Error: QCustomPlotMainWindow is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QCustomPlotMainWindow Deconstructor
// Todo: Check for memory leaks
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
QCustomPlotMainWindow::~QCustomPlotMainWindow()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ~QCustomPlotMainWindow";

    try {
        //QMainWindow::menuBar()->clear();
        //ui->menuSave->menuAction()->setVisible(false);
        delete ui;

    } catch (...) {
        qDebug() << "Error: ~QCustomPlotMainWindow is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SaveAsPDF
// Todo: Check for memory leaks
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void QCustomPlotMainWindow::SaveAsPDF()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start SaveAsPDF";

    try {
        QString OutputFileName = QFileDialog::getSaveFileName(this, "Save As PDF File", tr("."), tr(".pdf"));
    } catch (...) {
        qDebug() << "Error: SaveAsPDF is returning w/o checking";
    }
}
