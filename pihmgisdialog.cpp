#include <QDir>
#include <QDebug>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include <QThread>
#include <QFileDialog>
#include <QPainter>
#include <QMenu>
#include <QMenuBar>

#include <QException>
#include <iostream>

#include "pihmgisdialog.h"
#include "ui_pihmgisdialog.h"

#include "1ProjectManagement/1NewProject/newproject.h"
#include "1ProjectManagement/2OpenProject/openproject.h"
#include "1ProjectManagement/3ImportProject/importproject.h"
#include "1ProjectManagement/4CloseProject/closeproject.h"
#include "1ProjectManagement/CheckProject/checkproject.h"
#include "1ProjectManagement/InspectProject/inspectproject.h"

#include "2RasterProcessing/1FillPits/fillpits.h"
#include "2RasterProcessing/2FlowGrids/flowgrids.h"
#include "2RasterProcessing/3StreamGrids/streamgrids.h"
#include "2RasterProcessing/4LinkGrids/linkgrids.h"
#include "2RasterProcessing/5CatchmentGrids/catchmentgrids.h"
#include "2RasterProcessing/6StreamPolyline/streampolyline.h"
#include "2RasterProcessing/7CatchmentPolygon/catchmentpolygon.h"

#include "3VectorProcessing/1DissolvePolygons/dissolvepolygons.h"
#include "3VectorProcessing/2PolygonToPolylines/polygontopolylines.h"
#include "3VectorProcessing/3SimplifyPolylines/simplifypolylines.h"
#include "3VectorProcessing/4PolylineToLines/polylinetolines.h"
#include "3VectorProcessing/5MergeVectorLayers/mergevectorlayers.h"

#include "4DomainDecomposition/1ReadTopology/readtopology.h"
#include "4DomainDecomposition/2DelaunayTriangulation/delaunaytriangulation.h"
#include "4DomainDecomposition/3TINShapeLayer/tinshapelayer.h"

#include "5DataModelLoader/1MeshDataFile/meshdatafile.h"
#include "5DataModelLoader/2AttDataFile/attdatafile.h"
#include "5DataModelLoader/3RivDataFile/rivdatafile.h"
#include "5DataModelLoader/4SoilDataFile/soildatafile.h"
#include "5DataModelLoader/5GeolDataFile/geoldatafile.h"
#include "5DataModelLoader/6LcDataFile/lcdatafile.h"
#include "5DataModelLoader/7InitDataFile/initdatafile.h"
#include "5DataModelLoader/8IbcDataFile/ibcdatafile.h"
#include "5DataModelLoader/9ParaDataFile/paradatafile.h"
#include "5DataModelLoader/10CalibDataFile/calibdatafile.h"

#include "6PIHMSimulation/1PIHM_v2.2/pihmsimulation.h"

#include "7VisualAnalytics/1MeshSpatial/meshspatial.h"
#include "7VisualAnalytics/2MeshTemporal/meshtemporal.h"
#include "7VisualAnalytics/3RiverSpatial/riverspatial.h"
#include "7VisualAnalytics/4RiverTemporal/rivertemporal.h"

#include "globals.h"

QString user_pihmgis_root_folder = "Please pick a workspace folder.";   //QDir::homePath(); //Default for now, need to customize based on OS
QString user_pihmgis_project_folder = "/.PIHMgis";                      //Default for now, need to customize
QString user_pihmgis_project_name = "/OpenProject.txt";                 //Note use of forward characters


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Main Dialog Constructor
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PIHMgisDialog::PIHMgisDialog(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PIHMgisDialog)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog";

    try {

        QApplication::setAttribute(Qt::AA_DisableWindowContextHelpButton);

        ui->setupUi(this);
        ui->label_project_found->setVisible(false);

        update_current_workspace_label();

        if(print_log_messages)
            Print_Message_To_Main_Dialog("Welcome to PIHMgis v3.5....");

        Setup_Menu();

    } catch (...) {
        qDebug() << "Error: PIHMgisDialog is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Main Dialog de-Constructor
// TODO memory checking
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PIHMgisDialog::~PIHMgisDialog()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ~PIHMgisDialog";

    try {

        delete ui;

    } catch (...) {
        qDebug() << "Error: ~PIHMgisDialog is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper function to setup menu bar
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::Setup_Menu()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start Setup_Menu";

    try {

        statusBar();

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// File Menu
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        mnu_pick = new QAction("&Pick", this);
        mnu_pick->setStatusTip(tr("Pick PIHMgis Workspace/Folder"));
        mnu_pick->setToolTip(tr("Pick PIHMgis Workspace/Folder"));
        mnu_pick->setShortcut(tr("CTRL+P"));
        connect(mnu_pick, &QAction::triggered, this, &PIHMgisDialog::menu_pick_workspace);

        mnu_new = new QAction("&New", this);
        mnu_new->setStatusTip(tr("New"));
        mnu_new->setShortcut(tr("CTRL+N"));
        mnu_new->setEnabled(false);
        connect(mnu_new, &QAction::triggered, this, &PIHMgisDialog::menu_new);

        mnu_import = new QAction("&Import", this);
        mnu_import->setStatusTip(tr("Import"));
        mnu_import->setShortcut(tr("CTRL+I"));
        mnu_import->setEnabled(false);
        connect(mnu_import, &QAction::triggered, this, &PIHMgisDialog::menu_import);

        mnu_close = new QAction("&Close", this);
        mnu_close->setStatusTip(tr("Close"));
        mnu_close->setShortcut(tr("CTRL+C"));
        mnu_close->setEnabled(false);
        connect(mnu_close, &QAction::triggered, this, &PIHMgisDialog::menu_close);

        mnu_quit = new QAction("&Quit", this);
        mnu_quit->setStatusTip(tr("Quit PIHMgis Application"));
        mnu_quit->setShortcut(tr("CTRL+Q"));
        connect(mnu_quit, &QAction::triggered, this, &PIHMgisDialog::menu_quit);

        QMenu *file;
        file = menuBar()->addMenu("&File");
        file->addAction(mnu_pick);
        file->addSeparator();
        file->addAction(mnu_new);
        file->addAction(mnu_import);
        file->addAction(mnu_close);
        file->addSeparator();
        file->addAction(mnu_quit);

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Log Menu
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        mnu_debug = new QAction("&Debug Console", this);
        mnu_debug->setShortcut(tr("CTRL+D"));
        mnu_debug->setStatusTip(tr("Messages displayed to console window"));
        mnu_debug->setCheckable(true);
        mnu_debug->setChecked(false);
        connect(mnu_debug, &QAction::triggered, this, &PIHMgisDialog::menu_debug_messages);

        mnu_log_debug = new QAction("&Important Only Log", this);
        mnu_log_debug->setStatusTip(tr("Important Messages displayed to application window"));
        mnu_log_debug->setCheckable(true);
        mnu_log_debug->setChecked(true);
        connect(mnu_log_debug, &QAction::triggered, this, &PIHMgisDialog::menu_log_messages);

        mnu_log_many = new QAction("&Many", this);
        mnu_log_many->setCheckable(true);
        mnu_log_many->setChecked(false);
        connect(mnu_log_many, &QAction::triggered, this, &PIHMgisDialog::menu_log_many);

        mnu_log_redirect = new QAction("Redirect Debug to Important Log", this);
        mnu_log_redirect->setCheckable(true);
        mnu_log_redirect->setChecked(true);
        mnu_log_redirect->setStatusTip(tr("Use this to save all debug console messages"));
        connect(mnu_log_redirect, &QAction::triggered, this, &PIHMgisDialog::menu_redirect_messages);

        mnu_clear_log = new QAction("&Clear Important Log", this);
        mnu_clear_log->setStatusTip(tr("Clear Important Messages displayed in application window"));
        connect(mnu_clear_log, &QAction::triggered, this, &PIHMgisDialog::menu_clear_messages);

        mnu_save_log = new QAction("&Save Important Log", this);
        mnu_save_log->setStatusTip(tr("Save Important Log to text file"));
        connect(mnu_save_log, &QAction::triggered, this, &PIHMgisDialog::menu_save_log);

        QMenu *log;
        log = menuBar()->addMenu("&Log");
        log->addAction(mnu_debug);
        log->addAction(mnu_log_debug);
        log->addAction(mnu_log_many);
        log->addSeparator();
        log->addAction(mnu_log_redirect);
        log->addAction(mnu_clear_log);
        log->addSeparator();
        log->addAction(mnu_save_log);

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Help Menu
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        mnu_help= new QAction("&Contact", this);
        connect(mnu_help, &QAction::triggered, this, &PIHMgisDialog::menu_help);

        QMenu *mainhelp;
        mainhelp = menuBar()->addMenu("&Help");
        mainhelp->addAction(mnu_help);

    }
    catch (...)
    {
        qDebug() << "Error: Setup_Menu is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Pick Workspace Menu Item Action
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::menu_pick_workspace()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start menu_pick_workspace";

    try
    {
        if(mnu_quit != nullptr)
        {
            PickWorkspace();
        }

    } catch (...) {
        qDebug() << "Error: menu_pick_workspace is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Pick Workspace Menu Item Action
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::menu_new()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start menu_new_project";

    try
    {
        if(mnu_new != nullptr)
        {
            New_Project();
        }

    } catch (...) {
        qDebug() << "Error: menu_new_project is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Import Menu Item Action
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::menu_import()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start menu_import";

    try
    {
        if(mnu_new != nullptr)
        {
            Import_Project();
        }

    } catch (...) {
        qDebug() << "Error: menu_import is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Close Menu Item Action
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::menu_close()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start menu_close";

    try
    {
        if(mnu_close != nullptr)
        {
            Close_Project();
        }

    } catch (...) {
        qDebug() << "Error: menu_close is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quit Menu Item Action
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::menu_quit()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start menu_quit";

    try
    {
        if(mnu_quit != nullptr)
        {
            Print_Message_To_Main_Dialog("Bye from PIHMgis v3.5....");
            close();
        }

    } catch (...) {
        qDebug() << "Error: menu_quit is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Display console messages  Menu Item Action
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::menu_debug_messages()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start menu_debug_messages";

    try
    {
        if(mnu_debug != nullptr)
        {
            if (mnu_debug->isChecked())
            {
                print_debug_messages = true;
            }
            else
            {
                print_debug_messages = false;
            }
        }

    } catch (...) {
        qDebug() << "Error: menu_debug_messages is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Display Important messages Menu Item Action
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::menu_log_messages()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start menu_log_messages";

    try
    {
        if(mnu_log_debug != nullptr)
        {
            if (mnu_log_debug->isChecked())
            {
                print_log_messages = true;
            }
            else
            {
                print_log_messages = false;
            }
        }

    } catch (...) {
        qDebug() << "Error: menu_log_messages is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Log Many Messages (from for loops etc) Menu Item Action
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::menu_log_many()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start menu_log_many";

    try
    {
        if(mnu_log_many != nullptr)
        {
            if (mnu_log_many->isChecked())
            {
                print_many_messages = true;
            }
            else
            {
                print_many_messages = false;
            }
        }

    } catch (...) {
        qDebug() << "Error: menu_log_many is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Redict log Menu Item Action
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::menu_redirect_messages()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start menu_redirect_messages";

    try
    {
        if(mnu_log_redirect != nullptr)
        {
            if (mnu_log_redirect->isChecked())
            {
                redirect_debug_messages_to_log = true;
            }
            else
            {
                redirect_debug_messages_to_log = false;
            }
        }

    } catch (...) {
        qDebug() << "Error: menu_redirect_messages is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Clear log Menu Item Action
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::menu_clear_messages()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start menu_clear_messages";

    try
    {
        if(mnu_clear_log != nullptr)
        {
            Clear_Log();
        }

    } catch (...) {
        qDebug() << "Error: menu_clear_messages is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Save log Menu Item Action
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::menu_save_log()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start menu_save_log";

    try
    {
        if(mnu_save_log != nullptr)
        {
            QString fileName = QFileDialog::getSaveFileName(this,tr("Save Log File"), "", tr("Log (*.txt);;All Files (*)"));
            if (fileName.isEmpty())
            {
                //Do nothing
                return;
            }
            else {
                QFile file(fileName);
                if (!file.open(QIODevice::WriteOnly))
                {
                    QMessageBox::information(this, tr("Unable to open file"),file.errorString());
                    return;
                }
                QTextStream out(&file);
                out << ui->textBrowserLogs->document()->toPlainText();
                file.close();

                Log_Message("Saved log message to :" + fileName);
            }
        }

    } catch (...) {
        qDebug() << "Error: menu_save_log is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Menu Item Action
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::menu_help()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start menu_help";

    try
    {
        if(mnu_help != nullptr)
        {
            QDesktopServices::openUrl(QUrl("http://www.pihm.psu.edu/team.html"));
        }

    } catch (...) {
        qDebug() << "Error: menu_help is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper function to display current PIHMgis workspace.
// This should eliminate issues of using not remembering which workspace/folder they are using.
// Mixing of folders is a common problem by users creating issues in data files.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::update_current_workspace_label()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start update_current_workspace_label";

    try
    {
        ui->label_home_workspace->setText("Current workspace: " + user_pihmgis_root_folder);

    } catch (...) {
        qDebug() << "Error: update_current_workspace_label is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper function to aid users in next step. I found this misleading, as closing a dialog will move to the next,
// regardless if a user finished a step correctly.
// NOTE: I plan to remove this function. It causes too many compiling issues.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::set_defaults(QStringList DEFAULT_PARAM)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::set_defaults";

    try {
        bool boolWORKFLOW0, boolWORKFLOW1, boolWORKFLOW2, boolWORKFLOW3, boolWORKFLOW4, boolWORKFLOW5, boolWORKFLOW6, boolWORKFLOW7;
        bool boolNEWPRJ, boolOPENPRJ, boolIMPORTPRJ, boolCLOSEPRJ;
        bool boolFILLPITS, boolFLOWGRIDS, boolSTRGRIDS, boolLINKGRIDS, boolCATGRIDS, boolSTRPOLY, boolCATPOLY;
        bool boolDISSOLVE, boolPOLYGON, boolSIMPLIFY, boolPOLYLINE, boolMERGE;
        bool boolREADSHP, boolTRIANGLE, boolTINSHP;
        bool boolMESH, boolATTX, boolSOIL, boolRIVX, boolGEOL, boolLCXX, boolPARA, boolINIT, boolIBCX, boolCALI, boolFORC;
        bool boolPIHM;
        bool boolSPATIALW, boolSPATIALR, boolTIMEW, boolTIMER;
        bool bool_PICK_location = false;

        boolWORKFLOW0 = boolWORKFLOW1 = boolWORKFLOW2 = boolWORKFLOW3 = boolWORKFLOW4 = boolWORKFLOW5 = boolWORKFLOW6 = boolWORKFLOW7 = false;
        boolNEWPRJ = boolOPENPRJ = boolIMPORTPRJ = boolCLOSEPRJ = false;
        boolFILLPITS = boolFLOWGRIDS = boolSTRGRIDS = boolLINKGRIDS = boolCATGRIDS = boolSTRPOLY = boolCATPOLY = false;
        boolDISSOLVE = boolPOLYGON = boolSIMPLIFY = boolPOLYLINE = boolMERGE = false;
        boolREADSHP = boolTRIANGLE = boolTINSHP = false;
        boolMESH = boolATTX = boolSOIL = boolRIVX = boolGEOL = boolLCXX = boolPARA = boolINIT = boolIBCX = boolCALI = boolFORC = false;
        boolPIHM = false;
        boolSPATIALW = boolSPATIALR = boolTIMEW = boolTIMER = false;

        qDebug() << "Function set_defaults: " << DEFAULT_PARAM;
        for(int i=0; i<DEFAULT_PARAM.size(); i++)
        {
            //if (DEFAULT_PARAM.at(i) == "WORKFLOW0") { boolWORKFLOW0 = true; ui->pushButtonWorkFlow0->setFocus(); continue; }
            //        if (DEFAULT_PARAM.at(i) == "WORKFLOW1") { boolWORKFLOW1 = true; ui->pushButtonWorkFlow1->setFocus(); continue; }
            //        if (DEFAULT_PARAM.at(i) == "WORKFLOW2") { boolWORKFLOW2 = true; ui->pushButtonWorkFlow2->setFocus(); continue; }
            //        if (DEFAULT_PARAM.at(i) == "WORKFLOW3") { boolWORKFLOW3 = true; ui->pushButtonWorkFlow3->setFocus(); continue; }
            //        if (DEFAULT_PARAM.at(i) == "WORKFLOW4") { boolWORKFLOW4 = true; ui->pushButtonWorkFlow4->setFocus(); continue; }
            //        if (DEFAULT_PARAM.at(i) == "WORKFLOW5") { boolWORKFLOW5 = true; ui->pushButtonWorkFlow5->setFocus(); continue; }
            //        if (DEFAULT_PARAM.at(i) == "WORKFLOW6") { boolWORKFLOW6 = true; ui->pushButtonWorkFlow6->setFocus(); continue; }
            //        if (DEFAULT_PARAM.at(i) == "WORKFLOW7") { boolWORKFLOW7 = true; ui->pushButtonWorkFlow7->setFocus(); continue; }

            if (DEFAULT_PARAM.at(i) == "PICKPRJ")    { bool_PICK_location    = true; ui->pushButton_PickWorkspace->setFocus();    continue; }
            //if (DEFAULT_PARAM.at(i) == "WORKFLOW7")    { boolWORKFLOW7    = true; ui->pushButton_PickWorkspace->setFocus();    continue; }

            if (DEFAULT_PARAM.at(i) == "NEWPRJ")    {  qDebug() << "Function NEWPRJ"; boolNEWPRJ    = true; ui->pushButtonPIHMgisProjectNew->setFocus();    continue; }
            if (DEFAULT_PARAM.at(i) == "OPENPRJ")   { boolOPENPRJ   = true; ui->pushButtonPIHMgisProjectInspect->setFocus();   continue; }
            if (DEFAULT_PARAM.at(i) == "IMPORTPRJ") { boolIMPORTPRJ = true; ui->pushButtonPIHMgisProjectImport->setFocus(); continue; }
            if (DEFAULT_PARAM.at(i) == "CLOSEPRJ")  { boolCLOSEPRJ  = true; ui->pushButtonPIHMgisProjectClose->setFocus();  continue; }

            if (DEFAULT_PARAM.at(i) == "FILLPITS")  { boolFILLPITS  = true; ui->pushButtonRasterProcessingFillPits->setFocus();         continue; }
            if (DEFAULT_PARAM.at(i) == "FLOWGRIDS") { boolFLOWGRIDS = true; ui->pushButtonRasterProcessingFlowGrids->setFocus();        continue; }
            if (DEFAULT_PARAM.at(i) == "STRGRIDS")  { boolSTRGRIDS  = true; ui->pushButtonRasterProcessingStreamGrids->setFocus();      continue; }
            if (DEFAULT_PARAM.at(i) == "LINKGRIDS") { boolLINKGRIDS = true; ui->pushButtonRasterProcessingLinkGrids->setFocus();        continue; }
            if (DEFAULT_PARAM.at(i) == "CATGRIDS")  { boolCATGRIDS  = true; ui->pushButtonRasterProcessingCatchmentGrids->setFocus();   continue; }
            if (DEFAULT_PARAM.at(i) == "STRPOLY")   { boolSTRPOLY   = true; ui->pushButtonRasterProcessingStreamPolyline->setFocus();   continue; }
            if (DEFAULT_PARAM.at(i) == "CATPOLY")   { boolCATPOLY   = true; ui->pushButtonRasterProcessingCatchmentPolygon->setFocus(); continue; }

            if (DEFAULT_PARAM.at(i) == "DISSOLVE")  { boolDISSOLVE = true; ui->pushButtonVectorProcessingDissolvePolygons->setFocus();      continue; }
            if (DEFAULT_PARAM.at(i) == "POLYGON")   { boolPOLYGON  = true; ui->pushButtonVectorProcessingPolygonToPolylines->setFocus();    continue; }
            if (DEFAULT_PARAM.at(i) == "SIMPLIFY")  { boolSIMPLIFY = true; ui->pushButtonVectorProcessingSimplifyPolylines->setFocus();     continue; }
            if (DEFAULT_PARAM.at(i) == "POLYLINE")  { boolPOLYLINE = true; ui->pushButtonVectorProcessingPolylineToLines->setFocus();       continue; }
            if (DEFAULT_PARAM.at(i) == "MERGE")     { boolMERGE    = true; ui->pushButtonVectorProcessingMergeVectorLayers->setFocus();     continue; }

            if (DEFAULT_PARAM.at(i) == "READSHP")   { boolREADSHP  = true; ui->pushButtonDomainDecompositionReadTopology->setFocus();   continue; }
            if (DEFAULT_PARAM.at(i) == "TRIANGLE")  { boolTRIANGLE = true; ui->pushButtonDomainDecompositionTriangulation->setFocus();  continue; }
            if (DEFAULT_PARAM.at(i) == "TINSHP")    { boolTINSHP   = true; ui->pushButtonDomainDecompositionTINShapeLayer->setFocus();  continue; }

            if (DEFAULT_PARAM.at(i) == "MESH")  { boolMESH = true; ui->pushButtonDataModelLoaderMeshDataFile->setFocus();   continue; }
            if (DEFAULT_PARAM.at(i) == "ATTX")  { boolATTX = true; ui->pushButtonDataModelLoaderAttDataFile->setFocus();    continue; }
            if (DEFAULT_PARAM.at(i) == "RIVX")  { boolRIVX = true; ui->pushButtonDataModelLoaderRivDataFile->setFocus();    continue; }
            if (DEFAULT_PARAM.at(i) == "SOIL")  { boolSOIL = true; ui->pushButtonDataModelLoaderSoilDataFile->setFocus();   continue; }
            if (DEFAULT_PARAM.at(i) == "GEOL")  { boolGEOL = true; ui->pushButtonDataModelLoaderGeolDataFile->setFocus();   continue; }
            if (DEFAULT_PARAM.at(i) == "LCXX")  { boolLCXX = true; ui->pushButtonDataModelLoaderLcDataFile->setFocus();     continue; }
            if (DEFAULT_PARAM.at(i) == "INIT")  { boolINIT = true; ui->pushButtonDataModelLoaderInitDataFile->setFocus();   continue; }
            if (DEFAULT_PARAM.at(i) == "IBCX")  { boolIBCX = true; ui->pushButtonDataModelLoaderIbcDataFile->setFocus();    continue; }
            if (DEFAULT_PARAM.at(i) == "PARA")  { boolPARA = true; ui->pushButtonDataModelLoaderParamDataFile->setFocus();  continue; }
            if (DEFAULT_PARAM.at(i) == "CALI")  { boolCALI = true; ui->pushButtonDataModelLoaderCalibDataFile->setFocus();  continue; }
            if (DEFAULT_PARAM.at(i) == "FORC")  { boolFORC = true; ui->pushButtonDataModelLoaderForcDataFile->setFocus();   continue; }

            if (DEFAULT_PARAM.at(i) == "PIHM")  { boolPIHM = true; ui->pushButtonPIHMSimulation->setFocus();    continue; }

            if (DEFAULT_PARAM.at(i) == "SPATIALW")  { boolSPATIALW = true; ui->pushButtonVisualAnalyticsSpatialWatershed->setFocus();       continue; }
            if (DEFAULT_PARAM.at(i) == "SPATIALR")  { boolSPATIALR = true; ui->pushButtonVisualAnalyticsSpatialRiverNetwork->setFocus();    continue; }
            if (DEFAULT_PARAM.at(i) == "TIMEW")     { boolTIMEW    = true; ui->pushButtonVisualAnalyticsTemporalWatershed->setFocus();      continue; }
            if (DEFAULT_PARAM.at(i) == "TIMER")     { boolTIMER    = true; ui->pushButtonVisualAnalyticsTemporalRiverNetwork->setFocus();   continue; }
        }

        //ui->pushButton_PickWorkspace->setDefault(boolWORKFLOW7); //bool_PICK_location);
        //    ui->pushButtonWorkFlow1->setDefault(boolWORKFLOW1);
        //    ui->pushButtonWorkFlow2->setDefault(boolWORKFLOW2);
        //    ui->pushButtonWorkFlow3->setDefault(boolWORKFLOW3);
        //    ui->pushButtonWorkFlow4->setDefault(boolWORKFLOW4);
        //    ui->pushButtonWorkFlow5->setDefault(boolWORKFLOW5);
        //    ui->pushButtonWorkFlow6->setDefault(boolWORKFLOW6);
        //    ui->pushButtonWorkFlow7->setDefault(boolWORKFLOW7);

        ui->pushButton_PickWorkspace->setDefault(bool_PICK_location);

        ui->pushButtonPIHMgisProjectNew->setDefault(boolNEWPRJ);
        ui->pushButtonPIHMgisProjectInspect->setDefault(boolOPENPRJ);
        ui->pushButtonPIHMgisProjectImport->setDefault(boolIMPORTPRJ);
        ui->pushButtonPIHMgisProjectClose->setDefault(boolCLOSEPRJ);

        ui->pushButtonRasterProcessingFillPits->setDefault(boolFILLPITS);
        ui->pushButtonRasterProcessingFlowGrids->setDefault(boolFLOWGRIDS);
        ui->pushButtonRasterProcessingStreamGrids->setDefault(boolSTRGRIDS);
        ui->pushButtonRasterProcessingLinkGrids->setDefault(boolLINKGRIDS);
        ui->pushButtonRasterProcessingCatchmentGrids->setDefault(boolCATGRIDS);
        ui->pushButtonRasterProcessingStreamPolyline->setDefault(boolSTRPOLY);
        ui->pushButtonRasterProcessingCatchmentPolygon->setDefault(boolCATPOLY);

        ui->pushButtonVectorProcessingDissolvePolygons->setDefault(boolDISSOLVE);
        ui->pushButtonVectorProcessingPolygonToPolylines->setDefault(boolPOLYGON);
        ui->pushButtonVectorProcessingSimplifyPolylines->setDefault(boolSIMPLIFY);
        ui->pushButtonVectorProcessingPolylineToLines->setDefault(boolPOLYLINE);
        ui->pushButtonVectorProcessingMergeVectorLayers->setDefault(boolMERGE);

        ui->pushButtonDomainDecompositionReadTopology->setDefault(boolREADSHP);
        ui->pushButtonDomainDecompositionTriangulation->setDefault(boolTRIANGLE);
        ui->pushButtonDomainDecompositionTINShapeLayer->setDefault(boolTINSHP);

        ui->pushButtonDataModelLoaderMeshDataFile->setDefault(boolMESH);
        ui->pushButtonDataModelLoaderAttDataFile->setDefault(boolATTX);
        ui->pushButtonDataModelLoaderRivDataFile->setDefault(boolRIVX);
        ui->pushButtonDataModelLoaderSoilDataFile->setDefault(boolSOIL);
        ui->pushButtonDataModelLoaderGeolDataFile->setDefault(boolGEOL);
        ui->pushButtonDataModelLoaderLcDataFile->setDefault(boolLCXX);
        ui->pushButtonDataModelLoaderInitDataFile->setDefault(boolINIT);
        ui->pushButtonDataModelLoaderIbcDataFile->setDefault(boolIBCX);
        ui->pushButtonDataModelLoaderParamDataFile->setDefault(boolPARA);
        ui->pushButtonDataModelLoaderCalibDataFile->setDefault(boolCALI);
        ui->pushButtonDataModelLoaderForcDataFile->setDefault(boolFORC);

        ui->pushButtonPIHMSimulation->setDefault(boolPIHM);

        ui->pushButtonVisualAnalyticsSpatialWatershed->setDefault(boolSPATIALW);
        ui->pushButtonVisualAnalyticsSpatialRiverNetwork->setDefault(boolSPATIALR);
        ui->pushButtonVisualAnalyticsTemporalWatershed->setDefault(boolTIMEW);
        ui->pushButtonVisualAnalyticsTemporalRiverNetwork->setDefault(boolTIMER);

        int toolset;
        for (int i=0; i<DEFAULT_PARAM.length(); i++)
        {
            if( DEFAULT_PARAM.at(i).contains("WORKFLOW") )
            {
                toolset = DEFAULT_PARAM.at(i).right(1).toInt();
            }
        }
        qDebug() << "Toolset ID = " << toolset << "\n";
        ui->PIHMgisToolBox->setCurrentIndex(toolset-1);

    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::set_defaults is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper function to Set status of New Project Events (Button and Menu)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::set_New_Project_Status(bool status)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::set_New_Project_Status";

    try {
        ui->pushButtonPIHMgisProjectNew->setEnabled(status);
        mnu_new->setEnabled(status);
    } catch (...)
    {
        qDebug() << "Error: PIHMgisDialog::set_New_Project_Status is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper function to Set status of Close Project Events (Button and Menu)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::set_Close_Status(bool status)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::set_Close_Status";

    try {
        ui->pushButtonPIHMgisProjectClose->setEnabled(status);
        mnu_close->setEnabled(status);
    } catch (...)
    {
        qDebug() << "Error: PIHMgisDialog::set_Close_Status is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper function to Set status of Inspect Events (Button and Menu)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::set_Inspect_Status(bool status)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::set_Inspect_Status";

    try {
        ui->pushButtonPIHMgisProjectInspect->setEnabled(status);
    } catch (...)
    {
        qDebug() << "Error: PIHMgisDialog::set_Inspect_Status is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper function to Set status of Import Events (Button and Menu)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::set_Import_Status(bool status)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::set_Import_Status";

    try {
        ui->pushButtonPIHMgisProjectImport->setEnabled(status);
        mnu_import->setEnabled(status);
    } catch (...)
    {
        qDebug() << "Error: PIHMgisDialog::set_Import_Status is returning w/o checking";
    }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// New Project
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::New_Project()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::new_project";

    try {
        QString project_location = user_pihmgis_root_folder; // + user_pihmgis_project_folder;
        QString project_folder = ".PIHMgis";        //Default
        QString project_name = "OpenProject.txt";   //Default

        NewProject *NewProjectDialog = new NewProject(this, project_location, project_folder, project_name);
        NewProjectDialog->setModal(true);
        NewProjectDialog->exec(); //Note difference

        QString newWfolder   = NewProjectDialog->get_Workspace_Folder();
        QString newPrjFolder = NewProjectDialog->get_Project_Folder();
        QString newPrjName   = NewProjectDialog->get_Project_Name();
        bool created         = NewProjectDialog->get_User_Created_New_Project();

        if(created)
        {
            //Check variables created by user
            if(newWfolder.length() < 1)
            {
                set_New_Project_Status(false);
                set_Close_Status(false);
                set_Inspect_Status(false);
                set_Import_Status(false);
                enable_project_settings(false); //User needs to setup project

                Log_Error_Message("Invalid workspace");
                return;
            }
            if(newPrjFolder.length() < 1)
            {
                set_New_Project_Status(false);
                set_Close_Status(false);

                set_Inspect_Status(false);
                set_Import_Status(false);
                enable_project_settings(false); //User needs to setup project

                Log_Error_Message("Invalid project folder");
                return;
            }
            if(newPrjName.length() < 1)
            {
                set_New_Project_Status(false);
                set_Close_Status(false);

                set_Inspect_Status(false);
                set_Import_Status(false);
                enable_project_settings(false); //User needs to setup project

                Log_Error_Message("Invalid project name");
                return;
            }

            //Prevent user for using same settings
            set_New_Project_Status(false);
            set_Close_Status(true);
            set_Inspect_Status(false);
            set_Import_Status(false);
            enable_project_settings(true); //User needs to setup project

            //Update global variables. I suggest coming back here and add more checking
            user_pihmgis_root_folder = newWfolder;
            user_pihmgis_project_folder = "/" + newPrjFolder;        //Default for now, need to customize
            user_pihmgis_project_name = "/" + newPrjName;   //Note use of forward characters

        }
        else
        {
            //Assume nothing was created and do nothing for now
        }

    } catch (...)
    {
        qDebug() << "Error: PIHMgisDialog::new_project is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// New Project Button Click Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::on_pushButtonPIHMgisProjectNew_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonPIHMgisProjectNew_clicked";

    try {
        New_Project();
    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonPIHMgisProjectNew_clicked is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Inspect Project Button Click Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::on_pushButtonPIHMgisProjectInspect_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonPIHMgisProjectInspect_clicked";

    try {
        QString filename_open_project = user_pihmgis_root_folder + user_pihmgis_project_folder + user_pihmgis_project_name;

        InspectProject *iprj = new InspectProject(this, filename_open_project);
        iprj->setModal(true);
        iprj->exec();


    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonPIHMgisProjectInspect_clicked is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Open Project Button Click Event
// Keep until feed back from users
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//void PIHMgisDialog::on_pushButtonPIHMgisProjectOpen_clicked()
//{
//    if(print_debug_messages)
//        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonPIHMgisProjectOpen_clicked";

//    try {
//        QString filename_open_project = user_pihmgis_root_folder + user_pihmgis_project_folder + user_pihmgis_project_name;

//        OpenProject *OpenProjectDialog = new OpenProject(this);
//        OpenProjectDialog->show();

//    } catch (...) {
//        qDebug() << "Error: PIHMgisDialog::on_pushButtonPIHMgisProjectOpen_clicked is returning w/o checking";
//    }
//}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Import
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::Import_Project()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::Import";

    try {
        ImportProject *ImportProjectDialog = new ImportProject(this);
        ImportProjectDialog->setModal(true);
        ImportProjectDialog->exec();


    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::Import is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Import Project Button Click Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::on_pushButtonPIHMgisProjectImport_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonPIHMgisProjectImport_clicked";

    try {

        Import_Project();

    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonPIHMgisProjectImport_clicked is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Close Project (Different from closing main window) Button Click Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::Close_Project()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::Close_Project";

    try {
        QString filename_open_project = user_pihmgis_root_folder + user_pihmgis_project_folder + user_pihmgis_project_name;
        CloseProject *CloseProjectDialog = new CloseProject(this, filename_open_project);
        CloseProjectDialog->setModal(true);
        CloseProjectDialog->exec();

        bool user_closed = CloseProjectDialog->user_closed_project();
        if(user_closed)
        {
            //Reset global variables
            user_pihmgis_root_folder = "";
            user_pihmgis_project_folder = "";
            user_pihmgis_project_name = "";

            //Reset user interface
            update_current_workspace_label();

            set_New_Project_Status(false);
            set_Close_Status(false);

            set_Inspect_Status(false);
            set_Import_Status(false);

            enable_project_settings(false); //User needs to setup project
            Log_Message("Closed Project");

        }
    }
    catch (...) {
        qDebug() << "Error: PIHMgisDialog::Close_Project is returning w/o checking";
    }

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Close Project (Different from closing main window) Button Click Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::on_pushButtonPIHMgisProjectClose_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonPIHMgisProjectClose_clicked";

    try {

        Close_Project();

    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonPIHMgisProjectClose_clicked is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Fill Pits (RasterProcessing Group) Button Click Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::on_pushButtonRasterProcessingFillPits_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonRasterProcessingFillPits_clicked";

    try {

        QString filename_open_project = user_pihmgis_root_folder + user_pihmgis_project_folder + user_pihmgis_project_name;


        FillPits *FillPitsDialog = new FillPits(this, filename_open_project);
        FillPitsDialog->setModal(true);
        FillPitsDialog->exec();

    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonRasterProcessingFillPits_clicked is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Flow Grids (RasterProcessing Group) Button Click Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::on_pushButtonRasterProcessingFlowGrids_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonRasterProcessingFlowGrids_clicked";

    try {

        QString filename_open_project = user_pihmgis_root_folder+user_pihmgis_project_folder + user_pihmgis_project_name;

        FlowGrids *FlowGridsDialog = new FlowGrids(this, filename_open_project);
        FlowGridsDialog->setModal(true);
        FlowGridsDialog->show();

    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonRasterProcessingFlowGrids_clicked is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Stream Grids (RasterProcessing Group) Button Click Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::on_pushButtonRasterProcessingStreamGrids_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonRasterProcessingStreamGrids_clicked";

    try {
        QString filename_open_project = user_pihmgis_root_folder+user_pihmgis_project_folder + user_pihmgis_project_name;

        StreamGrids *StreamGridsDialog = new StreamGrids(this, filename_open_project);
        StreamGridsDialog->setModal(true);
        StreamGridsDialog->show();

    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonRasterProcessingStreamGrids_clicked is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Link Grids (RasterProcessing Group) Button Click Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::on_pushButtonRasterProcessingLinkGrids_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonRasterProcessingLinkGrids_clicked";

    try {
        QString filename_open_project = user_pihmgis_root_folder+user_pihmgis_project_folder + user_pihmgis_project_name;

        LinkGrids *LinkGridsDialog = new LinkGrids(this, filename_open_project);
        LinkGridsDialog->setModal(true);
        LinkGridsDialog->show();

    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonRasterProcessingLinkGrids_clicked is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Catchment Grids (RasterProcessing Group) Button Click Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::on_pushButtonRasterProcessingCatchmentGrids_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonRasterProcessingCatchmentGrids_clicked";

    try {
        QString filename_open_project = user_pihmgis_root_folder+user_pihmgis_project_folder + user_pihmgis_project_name;

        CatchmentGrids *CatchmentGridsDialog = new CatchmentGrids(this, filename_open_project);
        CatchmentGridsDialog->setModal(true);
        CatchmentGridsDialog->show();

    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonRasterProcessingCatchmentGrids_clicked is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// StreamPolyline Grids (RasterProcessing Group) Button Click Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::on_pushButtonRasterProcessingStreamPolyline_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonRasterProcessingStreamPolyline_clicked";

    try {
        QString filename_open_project = user_pihmgis_root_folder+user_pihmgis_project_folder + user_pihmgis_project_name;

        StreamPolyline *StreamPolylineDialog = new StreamPolyline(this, filename_open_project);
        StreamPolylineDialog->setModal(true);
        StreamPolylineDialog->show();
    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonRasterProcessingStreamPolyline_clicked is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CatchmentPolygon Grids (RasterProcessing Group) Button Click Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::on_pushButtonRasterProcessingCatchmentPolygon_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonRasterProcessingCatchmentPolygon_clicked";

    try {
        QString filename_open_project = user_pihmgis_root_folder+user_pihmgis_project_folder + user_pihmgis_project_name;

        CatchmentPolygon *CatchmentPolygonDialog = new CatchmentPolygon(this, filename_open_project);
        CatchmentPolygonDialog->setModal(true);
        CatchmentPolygonDialog->show();
    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonRasterProcessingCatchmentPolygon_clicked is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DissolvePolygons (VectorProcessing Group) Button Click Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::on_pushButtonVectorProcessingDissolvePolygons_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonVectorProcessingDissolvePolygons_clicked";

    try {

        QString filename_open_project = user_pihmgis_root_folder+user_pihmgis_project_folder + user_pihmgis_project_name;

        DissolvePolygons *DissolvePolygonsDialog = new DissolvePolygons(this, filename_open_project);
        DissolvePolygonsDialog->setModal(true);
        DissolvePolygonsDialog->show();


        //delete DissolvePolygonsDialog;

    } catch (QException ex) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonVectorProcessingDissolvePolygons_clicked is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PolygonToPolylines (VectorProcessing Group) Button Click Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::on_pushButtonVectorProcessingPolygonToPolylines_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonVectorProcessingPolygonToPolylines_clicked";

    try {
        QString filename_open_project = user_pihmgis_root_folder+user_pihmgis_project_folder + user_pihmgis_project_name;

        PolygonToPolylines *PolygonToPolylinesDialog = new PolygonToPolylines(this, filename_open_project);
        PolygonToPolylinesDialog->setModal(true);
        PolygonToPolylinesDialog->show();

    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonVectorProcessingPolygonToPolylines_clicked is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SimplifyPolylines (VectorProcessing Group) Button Click Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::on_pushButtonVectorProcessingSimplifyPolylines_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonVectorProcessingSimplifyPolylines_clicked";

    try {
        QString filename_open_project = user_pihmgis_root_folder+user_pihmgis_project_folder + user_pihmgis_project_name;

        SimplifyPolylines *SimplifyPolylinesDialog = new SimplifyPolylines(this, filename_open_project);
        SimplifyPolylinesDialog->setModal(true);
        SimplifyPolylinesDialog->show();
    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonVectorProcessingSimplifyPolylines_clicked is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PolylineToLines (VectorProcessing Group) Button Click Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::on_pushButtonVectorProcessingPolylineToLines_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonVectorProcessingPolylineToLines_clicked";

    try {
        QString filename_open_project = user_pihmgis_root_folder+user_pihmgis_project_folder + user_pihmgis_project_name;

        PolylineToLines *PolylineToLinesDialog = new PolylineToLines(this, filename_open_project);
        PolylineToLinesDialog->setModal(true);
        PolylineToLinesDialog->show();
    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonVectorProcessingPolylineToLines_clicked is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VectorLayers (VectorProcessing Group) Button Click Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::on_pushButtonVectorProcessingMergeVectorLayers_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonVectorProcessingMergeVectorLayers_clicked";

    try {
        QString filename_open_project = user_pihmgis_root_folder+user_pihmgis_project_folder + user_pihmgis_project_name;

        MergeVectorLayers *MergeVectorLayersDialog = new MergeVectorLayers(this, filename_open_project);
        MergeVectorLayersDialog->setModal(true);
        MergeVectorLayersDialog->show();

    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonVectorProcessingMergeVectorLayers_clicked is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ReadTopology (DomainDecomposition Group) Button Click Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::on_pushButtonDomainDecompositionReadTopology_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonDomainDecompositionReadTopology_clicked";

    try {
        QString filename_open_project = user_pihmgis_root_folder+user_pihmgis_project_folder + user_pihmgis_project_name;

        ReadTopology *ReadTopologyDialog = new ReadTopology(this, filename_open_project);
        ReadTopologyDialog->setModal(true);
        ReadTopologyDialog->show();

    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonDomainDecompositionReadTopology_clicked is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Triangulation (DomainDecomposition Group) Button Click Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::on_pushButtonDomainDecompositionTriangulation_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonDomainDecompositionTriangulation_clicked";

    try {
        QString filename_open_project = user_pihmgis_root_folder+user_pihmgis_project_folder + user_pihmgis_project_name;

        DelaunayTriangulation *DelaunayTriangulationDialog = new DelaunayTriangulation(this, filename_open_project);
        DelaunayTriangulationDialog->setModal(true);
        DelaunayTriangulationDialog->show();
    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonDomainDecompositionTriangulation_clicked is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TINShapeLayer (DomainDecomposition Group) Button Click Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::on_pushButtonDomainDecompositionTINShapeLayer_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonDomainDecompositionTINShapeLayer_clicked";

    try {
        QString filename_open_project = user_pihmgis_root_folder+user_pihmgis_project_folder + user_pihmgis_project_name;

        TINShapeLayer *TINShapeLayerDialog = new TINShapeLayer(this, filename_open_project);
        TINShapeLayerDialog->setModal(true);
        TINShapeLayerDialog->show();

    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonDomainDecompositionTINShapeLayer_clicked is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MeshData (DataModel Group) Button Click Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::on_pushButtonDataModelLoaderMeshDataFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonDataModelLoaderMeshDataFile_clicked";

    try {

        QString filename_open_project = user_pihmgis_root_folder+user_pihmgis_project_folder + user_pihmgis_project_name;

        MeshDataFile *MeshDataFileDialog = new MeshDataFile(this, filename_open_project);
        MeshDataFileDialog->setModal(true);
        MeshDataFileDialog->show();
    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonDataModelLoaderMeshDataFile_clicked0 is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// AttData (DataModel Group) Button Click Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::on_pushButtonDataModelLoaderAttDataFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonDataModelLoaderAttDataFile_clicked";

    try {
        QString filename_open_project = user_pihmgis_root_folder+user_pihmgis_project_folder + user_pihmgis_project_name;

        AttDataFile *AttDataFileDialog = new AttDataFile(this, filename_open_project);
        AttDataFileDialog->setModal(true);

        AttDataFileDialog->show();
    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonDataModelLoaderAttDataFile_clicked is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RivData (DataModel Group) Button Click Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::on_pushButtonDataModelLoaderRivDataFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonDataModelLoaderRivDataFile_clicked";

    try {
        QString filename_open_project = user_pihmgis_root_folder+user_pihmgis_project_folder + user_pihmgis_project_name;

        RivDataFile *RivDataFileDialog = new RivDataFile(this, filename_open_project);
        RivDataFileDialog->setModal(true);

        RivDataFileDialog->show();
    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonDataModelLoaderRivDataFile_clicked is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SoilData (DataModel Group) Button Click Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::on_pushButtonDataModelLoaderSoilDataFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonDataModelLoaderSoilDataFile_clicked";

    try {
        QString filename_open_project = user_pihmgis_root_folder+user_pihmgis_project_folder + user_pihmgis_project_name;

        SoilDataFile *SoilDataFileDialog = new SoilDataFile(this, filename_open_project);
        SoilDataFileDialog->setModal(true);

        SoilDataFileDialog->show();
    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonDataModelLoaderSoilDataFile_clicked is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GeolData (DataModel Group) Button Click Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::on_pushButtonDataModelLoaderGeolDataFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonDataModelLoaderGeolDataFile_clicked";

    try {
        QString filename_open_project = user_pihmgis_root_folder+user_pihmgis_project_folder + user_pihmgis_project_name;

        GeolDataFile *GeolDataFileDialog = new GeolDataFile(this, filename_open_project);
        GeolDataFileDialog->setModal(true);
        GeolDataFileDialog->show();
    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonDataModelLoaderGeolDataFile_clicked is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// LcData (DataModel Group) Button Click Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::on_pushButtonDataModelLoaderLcDataFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonDataModelLoaderLcDataFile_clicked";

    try {
        QString filename_open_project = user_pihmgis_root_folder+user_pihmgis_project_folder + user_pihmgis_project_name;

        LcDataFile *LcDataFileDialog = new LcDataFile(this, filename_open_project);
        LcDataFileDialog->setModal(true);
        LcDataFileDialog->show();
    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonDataModelLoaderLcDataFile_clicked is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// InitData (DataModel Group) Button Click Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::on_pushButtonDataModelLoaderInitDataFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonDataModelLoaderInitDataFile_clicked";

    try {
        QString filename_open_project = user_pihmgis_root_folder+user_pihmgis_project_folder + user_pihmgis_project_name;

        InitDataFile *InitDataFileDialog = new InitDataFile(this, filename_open_project);
        InitDataFileDialog->setModal(true);
        InitDataFileDialog->show();
    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonDataModelLoaderInitDataFile_clicked is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// IbcData (DataModel Group) Button Click Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::on_pushButtonDataModelLoaderIbcDataFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonDataModelLoaderIbcDataFile_clicked";

    try {
        QString filename_open_project = user_pihmgis_root_folder+user_pihmgis_project_folder + user_pihmgis_project_name;

        IbcDataFile *IbcDataFileDialog = new IbcDataFile(this, filename_open_project);
        IbcDataFileDialog->setModal(true);
        IbcDataFileDialog->show();
    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonDataModelLoaderIbcDataFile_clicked is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ParamData (DataModel Group) Button Click Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::on_pushButtonDataModelLoaderParamDataFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonDataModelLoaderParamDataFile_clicked";

    try {
        QString filename_open_project = user_pihmgis_root_folder+user_pihmgis_project_folder + user_pihmgis_project_name;

        ParaDataFile *ParaDataFileDialog = new ParaDataFile(this, filename_open_project);
        ParaDataFileDialog->setModal(true);
        ParaDataFileDialog->show();

    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonDataModelLoaderParamDataFile_clicked is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CalibData (DataModel Group) Button Click Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::on_pushButtonDataModelLoaderCalibDataFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonDataModelLoaderCalibDataFile_clicked";

    try {
        QString filename_open_project = user_pihmgis_root_folder+user_pihmgis_project_folder + user_pihmgis_project_name;


        CalibDataFile *CalibDataFileDialog = new CalibDataFile(this, filename_open_project);
        CalibDataFileDialog->setModal(true);
        CalibDataFileDialog->show();

    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonDataModelLoaderCalibDataFile_clicked is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ForcData (DataModel Group) Button Click Event
// TODO cataract.cee.psu.edu is offline
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::on_pushButtonDataModelLoaderForcDataFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonDataModelLoaderForcDataFile_clicked";

    try {
        //QStringList default_params; default_params << "WORKFLOW6" << "WORKFLOW8"; set_defaults(default_params);
        //bool success = QDesktopServices::openUrl(QUrl("http://cataract.cee.psu.edu/PIHM/index.php/PIHMgis_3.0#forc_Data_File"));

    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonDataModelLoaderForcDataFile_clicked is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Run PIHMSimulation Button Click Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::on_pushButtonPIHMSimulation_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonPIHMSimulation_clicked";

    try {
        QString filename_open_project = user_pihmgis_root_folder+user_pihmgis_project_folder + user_pihmgis_project_name;

        PIHMSimulation *PIHMSimulationDialog = new PIHMSimulation(this, filename_open_project);
        PIHMSimulationDialog->setModal(true);
        PIHMSimulationDialog->show();

    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonPIHMSimulation_clicked is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SpatialWatershed (VisualAnalytics Group) Button Click Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::on_pushButtonVisualAnalyticsSpatialWatershed_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonVisualAnalyticsSpatialWatershed_clicked";

    try {
        QString filename_open_project = user_pihmgis_root_folder+user_pihmgis_project_folder + user_pihmgis_project_name;

        MeshSpatial *MeshSpatialDialog = new MeshSpatial(this, filename_open_project);
        MeshSpatialDialog->setModal(true);
        MeshSpatialDialog->show();

    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonVisualAnalyticsSpatialWatershed_clicked is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TemporalWatershed (VisualAnalytics Group) Button Click Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::on_pushButtonVisualAnalyticsTemporalWatershed_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonVisualAnalyticsTemporalWatershed_clicked";

    try {
        QString filename_open_project = user_pihmgis_root_folder+user_pihmgis_project_folder + user_pihmgis_project_name;

        MeshTemporal *MeshTemporalDialog = new MeshTemporal(this, filename_open_project);
        MeshTemporalDialog->setModal(true);
        MeshTemporalDialog->show();

    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonVisualAnalyticsTemporalWatershed_clicked is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RiverNetwork (VisualAnalytics Group) Button Click Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::on_pushButtonVisualAnalyticsSpatialRiverNetwork_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonVisualAnalyticsSpatialRiverNetwork_clicked";

    try {
        QString filename_open_project = user_pihmgis_root_folder+user_pihmgis_project_folder + user_pihmgis_project_name;

        RiverSpatial *RiverSpatialDialog = new RiverSpatial(this, filename_open_project);
        RiverSpatialDialog->setModal(true);

        RiverSpatialDialog->show();
    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonVisualAnalyticsSpatialRiverNetwork_clicked is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TemporalRiverNetwork (VisualAnalytics Group) Button Click Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::on_pushButtonVisualAnalyticsTemporalRiverNetwork_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonVisualAnalyticsTemporalRiverNetwork_clicked";

    try {
        QString filename_open_project = user_pihmgis_root_folder+user_pihmgis_project_folder + user_pihmgis_project_name;

        RiverTemporal *RiverTemporalDialog = new RiverTemporal(this, filename_open_project);
        RiverTemporalDialog->setModal(true);
        RiverTemporalDialog->show();
    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonVisualAnalyticsTemporalRiverNetwork_clicked is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PIHMgis relies on folder structure per group action/types
// This function creates the necessary folder structure.
// You will need to keep this function and the same ones in NewProject and Check functions in sync.
// Note: Remove this version latter. After running checks. It is not used here, but kept for reference.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PIHMgisDialog::create_default_project_workspace()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::create_default_project_workspace";

    try
    {
        QString make_folder = user_pihmgis_root_folder + user_pihmgis_project_folder;
        QDir dir(make_folder);

        if (!dir.exists()) {
            dir.mkpath(make_folder);
            qDebug() << "Creating folder = " << make_folder;
        }
        else
        {
            qDebug() << "Project Folder already exists = " << make_folder;
        }


        //Need to create default folders for pihmgis
        make_folder = user_pihmgis_root_folder +  + "/1RasterProcessing";
        QDir dir_1RasterProcessing(make_folder);

        if (!dir_1RasterProcessing.exists()) {
            dir_1RasterProcessing.mkpath(make_folder);
            qDebug() << "Creating 1RasterProcessing folder = " << make_folder;
        }
        else
        {
            qDebug() << "1RasterProcessing Folder already exists = " << make_folder;
        }

        make_folder = user_pihmgis_root_folder + "/2VectorProcessing";
        QDir dir_2VectorProcessing(make_folder);

        if (!dir_2VectorProcessing.exists()) {
            dir_2VectorProcessing.mkpath(make_folder);
            qDebug() << "Creating 2VectorProcessing folder = " << make_folder;
        }
        else
        {
            qDebug() << "2VectorProcessing Folder already exists = " << make_folder;
        }


        make_folder = user_pihmgis_root_folder + "/3DomainDecomposition";
        QDir dir_3DomainDecomposition(make_folder);

        if (!dir_3DomainDecomposition.exists()) {
            dir_3DomainDecomposition.mkpath(make_folder);
            qDebug() << "Creating 3DomainDecomposition folder = " << make_folder;
        }
        else
        {
            qDebug() << "3DomainDecomposition Folder already exists = " << make_folder;
        }

        make_folder = user_pihmgis_root_folder + "/4DataModelLoader";
        QDir dir_4DataModelLoader(make_folder);

        if (!dir_4DataModelLoader.exists()) {
            dir_4DataModelLoader.mkpath(make_folder);
            qDebug() << "Creating 4DataModelLoader folder = " << make_folder;
        }
        else
        {
            qDebug() << "4DataModelLoader Folder already exists = " << make_folder;
        }

        make_folder = user_pihmgis_root_folder + "/5PIHMSimulation";
        QDir dir_5PIHMSimulation(make_folder);

        if (!dir_5PIHMSimulation.exists()) {
            dir_5PIHMSimulation.mkpath(make_folder);
            qDebug() << "Creating 5PIHMSimulation folder = " << make_folder;
        }
        else
        {
            qDebug() << "5PIHMSimulation Folder already exists = " << make_folder;
        }

        make_folder = user_pihmgis_root_folder + "/6VisualAnalytics";
        QDir dir_6VisualAnalytics(make_folder);

        if (!dir_6VisualAnalytics.exists()) {
            dir_6VisualAnalytics.mkpath(make_folder);
            qDebug() << "Creating 6VisualAnalytics folder = " << make_folder;
        }
        else
        {
            qDebug() << "6VisualAnalytics Folder already exists = " << make_folder;
        }


        make_folder = user_pihmgis_root_folder + "/Software";
        QDir dir_Software(make_folder);

        if (!dir_Software.exists()) {
            dir_Software.mkpath(make_folder);
            qDebug() << "Creating Software folder = " << make_folder;
        }
        else
        {
            qDebug() << "Software Folder already exists = " << make_folder;
        }



        return true;


    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButton_PickWorkspace_clicked is returning w/o checking";
        return false;

    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper function to upload project label.
// To help users remember which folder and data they are using.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::update_project_file_label()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::update_project_file_label";

    try {

        QString filename_open_project = user_pihmgis_root_folder+user_pihmgis_project_folder + user_pihmgis_project_name;

        bool exists = QFileInfo(filename_open_project).exists();
        ui->label_project_found->setVisible(exists);

    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::update_project_file_label is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper function to check if PIHMgis folders (required by group steps) exist.
// Return value indicates the number of folders (total of 7) required for PIHMgis
// Warning not checking if files exist in folder. As users should be able to stop/start project components
// Need to keep in sync with new project and check project dialogs
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PIHMgisDialog::check_pihmgis_project_exists(QString folder)
{
    int result = 0;

    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::check_pihmgis_project_exists";

    try {
        QString project_folder = folder + user_pihmgis_project_folder;
        QDir dir(project_folder);
        if (!dir.exists())
        {
            result = 0;
            return result; //No point checking any further
        }
        else
        {
            result++;
        }

        QString gisfolder = folder + "/1RasterProcessing";
        QDir dir1(gisfolder);
        if (dir1.exists())
        {
            result++;
        }

        gisfolder = folder + "/2VectorProcessing";
        QDir dir2(gisfolder);
        if (dir2.exists())
        {
            result++;
        }

        gisfolder = folder + "/3DomainDecomposition";
        QDir dir3(gisfolder);
        if (dir3.exists())
        {
            result++;
        }

        gisfolder = folder + "/4DataModelLoader";
        QDir dir4(gisfolder);
        if (dir4.exists())
        {
            result++;
        }

        gisfolder = folder + "/5PIHMSimulation";
        QDir dir5(gisfolder);
        if (dir5.exists())
        {
            result++;
        }

        gisfolder = folder + "/6VisualAnalytics";
        QDir dir6(gisfolder);
        if (dir6.exists())
        {
            result++;
        }

    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::check_pihmgis_project_exists is returning w/o checking";
    }
    return result;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper function to enable groups of steps/buttons
// Need to keep in sync with new project and check project dialogs
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PIHMgisDialog::enable_project_settings(bool enabled)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::update_project_file_label";

    try {
        ui->PIHMgisToolBox_RasterProcessing->setEnabled(enabled);
        ui->PIHMgisToolBox_VectorProcessing->setEnabled(enabled);
        ui->PIHMgisToolBox_DomainDecomposition->setEnabled(enabled);
        ui->PIHMgisToolBox_DataModelLoader->setEnabled(enabled);
        ui->PIHMgisToolBox_PIHMSimulation->setEnabled(enabled);
        ui->PIHMgisToolBox_VisualAnalytics->setEnabled(enabled);

        update_project_file_label();

        return true;
    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::update_project_file_label is returning w/o checking";
        return false;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper function to check if folder is empty or not.
// Used to decide if PIHMgis project has started or not.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PIHMgisDialog::check_directory_IsEmpty(const QDir& _dir)
{
    QFileInfoList infoList = _dir.entryInfoList(QDir::AllEntries | QDir::System | QDir::NoDotAndDotDot | QDir::Hidden );
    return infoList.isEmpty();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper function to check if folder is empty or not.
// Used to decide if PIHMgis project has started or not.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PIHMgisDialog::check_if_pihmgis_project_exists()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::check_if_pihmgis_project_exists";

    try {

        QString project_folder = user_pihmgis_root_folder + user_pihmgis_project_folder;
        QString filename_open_project = user_pihmgis_root_folder + user_pihmgis_project_folder + user_pihmgis_project_name;

        if(check_directory_IsEmpty(project_folder))
        {
            Log_Message("Did not find PIHMgis project file. " + project_folder);
        }

        bool exists = QFile::exists(filename_open_project);
        if(exists)
            Log_Message("Found PIHMgis project file. " + filename_open_project);
        else
            Log_Message("Did not find PIHMgis project file. " + filename_open_project);

        return exists;

    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::check_if_pihmgis_project_exists is returning w/o checking";
    }

    return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PICK Workspace Button
// This function looks for a project file in provided workspace. Then sets up GUI based on whether the project has started or not.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::PickWorkspace()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::PickWorkspace";

    try {
        Clear_Log();

        QString ProjectHome = QFileDialog::getExistingDirectory(this, "Specify Workspace/Home Folder", user_pihmgis_root_folder, 0);

        if(ProjectHome.length() > 0 )
        {
            int folder_count = check_pihmgis_project_exists(ProjectHome);

            if(print_debug_messages)
                qDebug() << "folder_count = " << folder_count;

            if(folder_count == 0)
            {
                //Need to create workspace
                user_pihmgis_root_folder = ProjectHome;
                //KEEP create_default_project_workspace();
                update_current_workspace_label();

                set_New_Project_Status(true);
                set_Close_Status(false);

                set_Inspect_Status(true);
                set_Import_Status(true);

                enable_project_settings(false); //User needs to setup project
            }
            else if (folder_count == 7) //Everything exists
            {
                user_pihmgis_root_folder = ProjectHome;
                update_current_workspace_label();

                bool prj = check_if_pihmgis_project_exists();
                if(prj)
                {
                    //Dont want users overriding data
                    set_New_Project_Status(false);
                    set_Import_Status(false);
                }
                else
                {
                    //Assume user only has folders
                    set_New_Project_Status(true);
                    set_Import_Status(true);
                }

                set_Close_Status(true);
                set_Inspect_Status(true);

                enable_project_settings(true);
                Log_Message("Found PIHMgis workspace. All folders exist. ");

            }
            else
            {
                //This likely means an older workspace, but user needs to decide how to proceed
                CheckProject *checkDialog = new CheckProject(this, ProjectHome);
                checkDialog->setModal(true);
                checkDialog->exec(); //Note difference here

                //Recheck once
                int folder_count_recheck = check_pihmgis_project_exists(ProjectHome);

                Clear_Log();

                //Assuming permissions changed or user deleted folders
                if( folder_count_recheck == 0)
                {
                    user_pihmgis_root_folder = ProjectHome;
                    update_current_workspace_label();

                    set_New_Project_Status(true);
                    set_Close_Status(false);

                    set_Inspect_Status(true);
                    set_Import_Status(true);

                    enable_project_settings(false); //User needs to setup project
                    Log_Message("Invalid PIHMgis workspace. Check your file permissions or create new one.");

                }
                else if( folder_count_recheck == 7)
                {
                    user_pihmgis_root_folder = ProjectHome;
                    update_current_workspace_label();

                    bool prj = check_if_pihmgis_project_exists();
                    if(prj)
                    {
                        //Dont want users overriding data
                        set_New_Project_Status(false);
                        set_Import_Status(false);
                    }
                    else
                    {
                        //Assume user only has folders
                        set_New_Project_Status(true);
                        set_Import_Status(true);
                    }

                    set_Close_Status(true);
                    set_Inspect_Status(true);

                    enable_project_settings(true);
                    Log_Message("Found PIHMgis workspace. All folders exist. ");

                }
                else
                {
                    enable_project_settings(false); //User needs to setup project
                    Log_Message("Invalid PIHMgis workspace. Either fix your workspace or pick another one.");
                    qDebug() << "Recheck found " << folder_count_recheck << " items. ";
                }
            }
        }

    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::PickWorkspace is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PICK Workspace Button Click Event
// This function looks for a project file in provided workspace. Then sets up GUI based on whether the project has started or not.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::on_pushButton_PickWorkspace_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButton_PickWorkspace_clicked";

    try {

        PickWorkspace();
    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButton_PickWorkspace_clicked is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to clear message log
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::Clear_Log()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::Clear_Log()";

    try {

        LogsString = tr("");
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

    } catch (...) {
        qDebug() << "Error: CheckProject::PIHMgisDialog() is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check Log_Error_Message
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::Log_Error_Message(QString message)
{
    try {
        LogsString.append(tr("<span style=\"color:#FF0000\">Error: ") + message + " </span>" +tr("<br>"));
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();
    } catch (...) {
        qDebug() << "Error: Log_Error_Message is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to check Log_Error_Message
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::Log_Message(QString message)
{
    try {
        LogsString.append(tr("<span style=\"color:#000000\"> ") + message + " </span>"+tr("<br>"));
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();
    } catch (...) {
        qDebug() << "Error: Log_Message is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Clear Log Button Click Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PIHMgisDialog::on_pushButtonClearLog_clicked()
{
    Clear_Log();
}
