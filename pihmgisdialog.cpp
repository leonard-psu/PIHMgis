#include <QDir>
#include <QDebug>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include <QThread>
#include <QFileDialog>

#include <QException>
#include <iostream>

#include "pihmgisdialog.h"
#include "ui_pihmgisdialog.h"

#include "1ProjectManagement/1NewProject/newproject.h"
#include "1ProjectManagement/2OpenProject/openproject.h"
#include "1ProjectManagement/3ImportProject/importproject.h"
#include "1ProjectManagement/4CloseProject/closeproject.h"

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

//#include "6PIHMSimulation/1PIHM_v2.2/PIHMSimulation.h"
#include "6PIHMSimulation/1PIHM_v2.2/pihmsimulation.h"

#include "7VisualAnalytics/1MeshSpatial/meshspatial.h"
#include "7VisualAnalytics/2MeshTemporal/meshtemporal.h"
#include "7VisualAnalytics/3RiverSpatial/riverspatial.h"
#include "7VisualAnalytics/4RiverTemporal/rivertemporal.h"

#include "globals.h"

QString user_pihmgis_root_folder = QDir::homePath(); //Default for now, need to customize based on OS
QString user_pihmgis_project_folder = "/.PIHMgis";   //Default for now, need to customize


PIHMgisDialog::PIHMgisDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PIHMgisDialog)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog";

    try {

        this->setWindowIcon(QIcon("Icons/PIHMgis000.icns"));
        ui->setupUi(this);

        //QObject::connect(ui->pushButton_PickWorkspace,SIGNAL(clicked()),this,SLOT(on_pushButton_PickWorkspace_clicked()));

        qDebug() << "PIHMgisDialog started";

        update_current_label();


        //        connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(this->on_pushButton_clicked()));

        //    QDir dir;
        //    success = dir.mkpath(QDir::homePath()+"/.PIHMgis/");
        //    if(success == true)
        //    {
        //        qDebug() << "Successfully Created Folder: " << QDir::homePath()+"/.PIHMgis/";
        //    }
        //    else
        //    {
        //        qDebug() << "Unable to Create Director: " << QDir::homePath()+"/.PIHMgis/";
        //        qDebug() << "Please Check File/Folder Permissions";
        //        QMessageBox::critical(this,tr("Critical Error"),tr("Unable to Create Folder in the Home Directory.\nPlease Close & Open PIHMgis After Fixing Permissions!"),QMessageBox::Ok);
        //    }

        //ui->PIHMgisToolBox->setCurrentIndex(8-1);
        //ui->pushButtonWorkFlow1->setDefault(1);
        //ui->pushButtonWorkFlow1->setFocus();
    } catch (...) {
        qDebug() << "Error: PIHMgisDialog is returning w/o checking";
    }

}

void PIHMgisDialog::update_current_label()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start update_current_label";

    try {
        ui->label_home_workspace->setText("Current workspace: " + user_pihmgis_root_folder);
    } catch (...) {
        qDebug() << "Error: update_current_label is returning w/o checking";
    }
}

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


/*void PIHMgisDialog::set_defaults(QStringList DEFAULT_PARAM)
{
    bool boolWORKFLOW0, boolWORKFLOW1, boolWORKFLOW2, boolWORKFLOW3, boolWORKFLOW4, boolWORKFLOW5, boolWORKFLOW6, boolWORKFLOW7;
    bool boolNEWPRJ, boolOPENPRJ, boolIMPORTPRJ, boolCLOSEPRJ;
    bool boolFILLPITS, boolFLOWGRIDS, boolSTRGRIDS, boolLINKGRIDS, boolCATGRIDS, boolSTRPOLY, boolCATPOLY;
    bool boolDISSOLVE, boolPOLYGON, boolSIMPLIFY, boolPOLYLINE, boolMERGE;
    bool boolREADSHP, boolTRIANGLE, boolTINSHP;
    bool boolMESH, boolATTX, boolSOIL, boolRIVX, boolGEOL, boolLCXX, boolPARA, boolINIT, boolIBCX, boolCALI, boolFORC;
    bool boolPIHM;
    bool boolSPATIALW, boolSPATIALR, boolTIMEW, boolTIMER;

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
        if (DEFAULT_PARAM.at(i) == "WORKFLOW0") { boolWORKFLOW0 = true; ui->pushButtonWorkFlow0->setFocus(); continue; }
        if (DEFAULT_PARAM.at(i) == "WORKFLOW1") { boolWORKFLOW1 = true; ui->pushButtonWorkFlow1->setFocus(); continue; }
        if (DEFAULT_PARAM.at(i) == "WORKFLOW2") { boolWORKFLOW2 = true; ui->pushButtonWorkFlow2->setFocus(); continue; }
        if (DEFAULT_PARAM.at(i) == "WORKFLOW3") { boolWORKFLOW3 = true; ui->pushButtonWorkFlow3->setFocus(); continue; }
        if (DEFAULT_PARAM.at(i) == "WORKFLOW4") { boolWORKFLOW4 = true; ui->pushButtonWorkFlow4->setFocus(); continue; }
        if (DEFAULT_PARAM.at(i) == "WORKFLOW5") { boolWORKFLOW5 = true; ui->pushButtonWorkFlow5->setFocus(); continue; }
        if (DEFAULT_PARAM.at(i) == "WORKFLOW6") { boolWORKFLOW6 = true; ui->pushButtonWorkFlow6->setFocus(); continue; }
        if (DEFAULT_PARAM.at(i) == "WORKFLOW7") { boolWORKFLOW7 = true; ui->pushButtonWorkFlow7->setFocus(); continue; }

        if (DEFAULT_PARAM.at(i) == "NEWPRJ")    { boolNEWPRJ    = true; ui->pushButtonPIHMgisProjectNew->setFocus();    continue; }
        if (DEFAULT_PARAM.at(i) == "OPENPRJ")   { boolOPENPRJ   = true; ui->pushButtonPIHMgisProjectOpen->setFocus();   continue; }
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

    ui->pushButtonWorkFlow0->setDefault(boolWORKFLOW0);
    ui->pushButtonWorkFlow1->setDefault(boolWORKFLOW1);
    ui->pushButtonWorkFlow2->setDefault(boolWORKFLOW2);
    ui->pushButtonWorkFlow3->setDefault(boolWORKFLOW3);
    ui->pushButtonWorkFlow4->setDefault(boolWORKFLOW4);
    ui->pushButtonWorkFlow5->setDefault(boolWORKFLOW5);
    ui->pushButtonWorkFlow6->setDefault(boolWORKFLOW6);
    ui->pushButtonWorkFlow7->setDefault(boolWORKFLOW7);

    ui->pushButtonPIHMgisProjectNew->setDefault(boolNEWPRJ);
    ui->pushButtonPIHMgisProjectOpen->setDefault(boolOPENPRJ);
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
}*/

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
            if (DEFAULT_PARAM.at(i) == "OPENPRJ")   { boolOPENPRJ   = true; ui->pushButtonPIHMgisProjectOpen->setFocus();   continue; }
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
        ui->pushButtonPIHMgisProjectOpen->setDefault(boolOPENPRJ);
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

// ************************************************************************** //

// **** START :: PIHMgis Help & Resources Slots **** //

//void PIHMgisDialog::on_pushButtonWorkFlow0_clicked()
//{
//    if(print_debug_messages)
//        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonWorkFlow0_clicked";

//    try {
//        bool success = QDesktopServices::openUrl(QUrl("http://www.pihm.psu.edu"));
//        QStringList default_params; default_params << "WORKFLOW1"; set_defaults(default_params);
//    } catch (...) {
//        qDebug() << "Error: PIHMgisDialog::on_pushButtonWorkFlow0_clicked is returning w/o checking";
//    }
//}

// **** START :: PIHMgis Project Management **** //

void PIHMgisDialog::on_pushButtonPIHMgisProjectNew_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonPIHMgisProjectNew_clicked";

    try {
        qDebug() << "on_pushButtonPIHMgisProjectNew_clicked";

        NewProject *NewProjectDialog = new NewProject(this);
        NewProjectDialog->show();
    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonPIHMgisProjectNew_clicked is returning w/o checking";
    }
}

void PIHMgisDialog::on_pushButtonPIHMgisProjectOpen_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonPIHMgisProjectOpen_clicked";

    try {
        OpenProject *OpenProjectDialog = new OpenProject(this);
        OpenProjectDialog->show();
    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonPIHMgisProjectOpen_clicked is returning w/o checking";
    }
}

void PIHMgisDialog::on_pushButtonPIHMgisProjectImport_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonPIHMgisProjectImport_clicked";

    try {
        ImportProject *ImportProjectDialog = new ImportProject(this);
        ImportProjectDialog->setModal(true);
        ImportProjectDialog->exec();


    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonPIHMgisProjectImport_clicked is returning w/o checking";
    }
}

void PIHMgisDialog::on_pushButtonPIHMgisProjectClose_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonPIHMgisProjectClose_clicked";

    try {
        CloseProject *CloseProjectDialog = new CloseProject(this);
        CloseProjectDialog->show();
    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonPIHMgisProjectClose_clicked is returning w/o checking";
    }
}

// **** END   :: PIHMgis Project Management Slots **** //


// ************************************************************************** //


// **** START :: Raster Processing Slots **** //

void PIHMgisDialog::on_pushButtonRasterProcessingFillPits_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonRasterProcessingFillPits_clicked";

    try {

        QString filename_open_project = user_pihmgis_root_folder+user_pihmgis_project_folder + "/OpenProject.txt";


        FillPits *FillPitsDialog = new FillPits(this, filename_open_project);
        FillPitsDialog->setModal(true);
        FillPitsDialog->exec();

    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonRasterProcessingFillPits_clicked is returning w/o checking";
    }
}

void PIHMgisDialog::on_pushButtonRasterProcessingFlowGrids_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonRasterProcessingFlowGrids_clicked";

    try {

        QString filename_open_project = user_pihmgis_root_folder+user_pihmgis_project_folder + "/OpenProject.txt";

        FlowGrids *FlowGridsDialog = new FlowGrids(this, filename_open_project);
        FlowGridsDialog->setModal(true);
        FlowGridsDialog->show();
    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonRasterProcessingFlowGrids_clicked is returning w/o checking";
    }
}

void PIHMgisDialog::on_pushButtonRasterProcessingStreamGrids_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonRasterProcessingStreamGrids_clicked";

    try {
        QString filename_open_project = user_pihmgis_root_folder+user_pihmgis_project_folder + "/OpenProject.txt";

        StreamGrids *StreamGridsDialog = new StreamGrids(this, filename_open_project);
        StreamGridsDialog->setModal(true);
        StreamGridsDialog->show();

    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonRasterProcessingStreamGrids_clicked is returning w/o checking";
    }
}

void PIHMgisDialog::on_pushButtonRasterProcessingLinkGrids_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonRasterProcessingLinkGrids_clicked";

    try {
        QString filename_open_project = user_pihmgis_root_folder+user_pihmgis_project_folder + "/OpenProject.txt";

        LinkGrids *LinkGridsDialog = new LinkGrids(this, filename_open_project);
        LinkGridsDialog->setModal(true);
        LinkGridsDialog->show();

    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonRasterProcessingLinkGrids_clicked is returning w/o checking";
    }
}

void PIHMgisDialog::on_pushButtonRasterProcessingCatchmentGrids_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonRasterProcessingCatchmentGrids_clicked";

    try {
        QString filename_open_project = user_pihmgis_root_folder+user_pihmgis_project_folder + "/OpenProject.txt";

        CatchmentGrids *CatchmentGridsDialog = new CatchmentGrids(this, filename_open_project);
        CatchmentGridsDialog->setModal(true);
        CatchmentGridsDialog->show();

    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonRasterProcessingCatchmentGrids_clicked is returning w/o checking";
    }
}

void PIHMgisDialog::on_pushButtonRasterProcessingStreamPolyline_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonRasterProcessingStreamPolyline_clicked";

    try {
        QString filename_open_project = user_pihmgis_root_folder+user_pihmgis_project_folder + "/OpenProject.txt";

        StreamPolyline *StreamPolylineDialog = new StreamPolyline(this, filename_open_project);
        StreamPolylineDialog->setModal(true);
        StreamPolylineDialog->show();
    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonRasterProcessingStreamPolyline_clicked is returning w/o checking";
    }
}

void PIHMgisDialog::on_pushButtonRasterProcessingCatchmentPolygon_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonRasterProcessingCatchmentPolygon_clicked";

    try {
        QString filename_open_project = user_pihmgis_root_folder+user_pihmgis_project_folder + "/OpenProject.txt";

        CatchmentPolygon *CatchmentPolygonDialog = new CatchmentPolygon(this, filename_open_project);
        CatchmentPolygonDialog->setModal(true);
        CatchmentPolygonDialog->show();
    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonRasterProcessingCatchmentPolygon_clicked is returning w/o checking";
    }
}

// **** END   :: Raster Processing Slots **** //


// ************************************************************************** //


// **** START :: Vector Processing Slots **** //

void PIHMgisDialog::on_pushButtonVectorProcessingDissolvePolygons_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonVectorProcessingDissolvePolygons_clicked";

    try {

        QString filename_open_project = user_pihmgis_root_folder+user_pihmgis_project_folder + "/OpenProject.txt";

        DissolvePolygons *DissolvePolygonsDialog = new DissolvePolygons(this, filename_open_project);
        DissolvePolygonsDialog->setModal(true);
        DissolvePolygonsDialog->show();


        //delete DissolvePolygonsDialog;

    } catch (QException ex) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonVectorProcessingDissolvePolygons_clicked is returning w/o checking";
    }
}

void PIHMgisDialog::on_pushButtonVectorProcessingPolygonToPolylines_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonVectorProcessingPolygonToPolylines_clicked";

    try {
        QString filename_open_project = user_pihmgis_root_folder+user_pihmgis_project_folder + "/OpenProject.txt";

        PolygonToPolylines *PolygonToPolylinesDialog = new PolygonToPolylines(this, filename_open_project);
        PolygonToPolylinesDialog->setModal(true);
        PolygonToPolylinesDialog->show();

    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonVectorProcessingPolygonToPolylines_clicked is returning w/o checking";
    }
}

void PIHMgisDialog::on_pushButtonVectorProcessingSimplifyPolylines_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonVectorProcessingSimplifyPolylines_clicked";

    try {
        QString filename_open_project = user_pihmgis_root_folder+user_pihmgis_project_folder + "/OpenProject.txt";

        SimplifyPolylines *SimplifyPolylinesDialog = new SimplifyPolylines(this, filename_open_project);
        SimplifyPolylinesDialog->setModal(true);
        SimplifyPolylinesDialog->show();
    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonVectorProcessingSimplifyPolylines_clicked is returning w/o checking";
    }
}

void PIHMgisDialog::on_pushButtonVectorProcessingPolylineToLines_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonVectorProcessingPolylineToLines_clicked";

    try {
        QString filename_open_project = user_pihmgis_root_folder+user_pihmgis_project_folder + "/OpenProject.txt";

        PolylineToLines *PolylineToLinesDialog = new PolylineToLines(this, filename_open_project);
        PolylineToLinesDialog->setModal(true);
        PolylineToLinesDialog->show();
    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonVectorProcessingPolylineToLines_clicked is returning w/o checking";
    }
}

void PIHMgisDialog::on_pushButtonVectorProcessingMergeVectorLayers_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonVectorProcessingMergeVectorLayers_clicked";

    try {
        QString filename_open_project = user_pihmgis_root_folder+user_pihmgis_project_folder + "/OpenProject.txt";

        MergeVectorLayers *MergeVectorLayersDialog = new MergeVectorLayers(this, filename_open_project);
        MergeVectorLayersDialog->setModal(true);
        MergeVectorLayersDialog->show();

    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonVectorProcessingMergeVectorLayers_clicked is returning w/o checking";
    }
}

// **** END   :: Vector Processing Slots **** //


// ************************************************************************** //


// **** START :: Domain Decomposition Slots **** //

void PIHMgisDialog::on_pushButtonDomainDecompositionReadTopology_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonDomainDecompositionReadTopology_clicked";

    try {
        QString filename_open_project = user_pihmgis_root_folder+user_pihmgis_project_folder + "/OpenProject.txt";

        ReadTopology *ReadTopologyDialog = new ReadTopology(this, filename_open_project);
        ReadTopologyDialog->setModal(true);
        ReadTopologyDialog->show();

    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonDomainDecompositionReadTopology_clicked is returning w/o checking";
    }
}

void PIHMgisDialog::on_pushButtonDomainDecompositionTriangulation_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonDomainDecompositionTriangulation_clicked";

    try {
        QString filename_open_project = user_pihmgis_root_folder+user_pihmgis_project_folder + "/OpenProject.txt";

        DelaunayTriangulation *DelaunayTriangulationDialog = new DelaunayTriangulation(this, filename_open_project);
        DelaunayTriangulationDialog->setModal(true);
        DelaunayTriangulationDialog->show();
    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonDomainDecompositionTriangulation_clicked is returning w/o checking";
    }
}

void PIHMgisDialog::on_pushButtonDomainDecompositionTINShapeLayer_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonDomainDecompositionTINShapeLayer_clicked";

    try {
        QString filename_open_project = user_pihmgis_root_folder+user_pihmgis_project_folder + "/OpenProject.txt";

        TINShapeLayer *TINShapeLayerDialog = new TINShapeLayer(this, filename_open_project);
        TINShapeLayerDialog->setModal(true);
        TINShapeLayerDialog->show();

    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonDomainDecompositionTINShapeLayer_clicked is returning w/o checking";
    }
}

// **** END   :: Domain Decomposition Slots **** //


// ************************************************************************** //


// **** START :: Data Model Loader Slots **** //

void PIHMgisDialog::on_pushButtonDataModelLoaderMeshDataFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonDataModelLoaderMeshDataFile_clicked";

    try {

        QString filename_open_project = user_pihmgis_root_folder+user_pihmgis_project_folder + "/OpenProject.txt";


        MeshDataFile *MeshDataFileDialog = new MeshDataFile(this, filename_open_project);
        MeshDataFileDialog->setModal(true);
        MeshDataFileDialog->show();
    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonDataModelLoaderMeshDataFile_clicked0 is returning w/o checking";
    }
}

void PIHMgisDialog::on_pushButtonDataModelLoaderAttDataFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonDataModelLoaderAttDataFile_clicked";

    try {
        QString filename_open_project = user_pihmgis_root_folder+user_pihmgis_project_folder + "/OpenProject.txt";

        AttDataFile *AttDataFileDialog = new AttDataFile(this, filename_open_project);
        AttDataFileDialog->setModal(true);

        AttDataFileDialog->show();
    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonDataModelLoaderAttDataFile_clicked is returning w/o checking";
    }
}

void PIHMgisDialog::on_pushButtonDataModelLoaderRivDataFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonDataModelLoaderRivDataFile_clicked";

    try {
        QString filename_open_project = user_pihmgis_root_folder+user_pihmgis_project_folder + "/OpenProject.txt";

        RivDataFile *RivDataFileDialog = new RivDataFile(this, filename_open_project);
        RivDataFileDialog->setModal(true);

        RivDataFileDialog->show();
    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonDataModelLoaderRivDataFile_clicked is returning w/o checking";
    }
}

void PIHMgisDialog::on_pushButtonDataModelLoaderSoilDataFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonDataModelLoaderSoilDataFile_clicked";

    try {
        QString filename_open_project = user_pihmgis_root_folder+user_pihmgis_project_folder + "/OpenProject.txt";

        SoilDataFile *SoilDataFileDialog = new SoilDataFile(this, filename_open_project);
        SoilDataFileDialog->setModal(true);

        SoilDataFileDialog->show();
    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonDataModelLoaderSoilDataFile_clicked is returning w/o checking";
    }
}

void PIHMgisDialog::on_pushButtonDataModelLoaderGeolDataFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonDataModelLoaderGeolDataFile_clicked";

    try {
        QString filename_open_project = user_pihmgis_root_folder+user_pihmgis_project_folder + "/OpenProject.txt";

        GeolDataFile *GeolDataFileDialog = new GeolDataFile(this, filename_open_project);
        GeolDataFileDialog->setModal(true);
        GeolDataFileDialog->show();
    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonDataModelLoaderGeolDataFile_clicked is returning w/o checking";
    }
}

void PIHMgisDialog::on_pushButtonDataModelLoaderLcDataFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonDataModelLoaderLcDataFile_clicked";

    try {
        QString filename_open_project = user_pihmgis_root_folder+user_pihmgis_project_folder + "/OpenProject.txt";

        LcDataFile *LcDataFileDialog = new LcDataFile(this, filename_open_project);
        LcDataFileDialog->setModal(true);
        LcDataFileDialog->show();
    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonDataModelLoaderLcDataFile_clicked is returning w/o checking";
    }
}

void PIHMgisDialog::on_pushButtonDataModelLoaderInitDataFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonDataModelLoaderInitDataFile_clicked";

    try {
        QString filename_open_project = user_pihmgis_root_folder+user_pihmgis_project_folder + "/OpenProject.txt";

        InitDataFile *InitDataFileDialog = new InitDataFile(this, filename_open_project);
        InitDataFileDialog->setModal(true);
        InitDataFileDialog->show();
    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonDataModelLoaderInitDataFile_clicked is returning w/o checking";
    }
}

void PIHMgisDialog::on_pushButtonDataModelLoaderIbcDataFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonDataModelLoaderIbcDataFile_clicked";

    try {
        QString filename_open_project = user_pihmgis_root_folder+user_pihmgis_project_folder + "/OpenProject.txt";

        IbcDataFile *IbcDataFileDialog = new IbcDataFile(this, filename_open_project);
        IbcDataFileDialog->setModal(true);
        IbcDataFileDialog->show();
    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonDataModelLoaderIbcDataFile_clicked is returning w/o checking";
    }
}

void PIHMgisDialog::on_pushButtonDataModelLoaderParamDataFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonDataModelLoaderParamDataFile_clicked";

    try {
        QString filename_open_project = user_pihmgis_root_folder+user_pihmgis_project_folder + "/OpenProject.txt";

        ParaDataFile *ParaDataFileDialog = new ParaDataFile(this, filename_open_project);
        ParaDataFileDialog->setModal(true);
        ParaDataFileDialog->show();

    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonDataModelLoaderParamDataFile_clicked is returning w/o checking";
    }
}

void PIHMgisDialog::on_pushButtonDataModelLoaderCalibDataFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonDataModelLoaderCalibDataFile_clicked";

    try {
        QString filename_open_project = user_pihmgis_root_folder+user_pihmgis_project_folder + "/OpenProject.txt";


        CalibDataFile *CalibDataFileDialog = new CalibDataFile(this, filename_open_project);
        CalibDataFileDialog->setModal(true);
        CalibDataFileDialog->show();

    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonDataModelLoaderCalibDataFile_clicked is returning w/o checking";
    }
}

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

// **** END   :: Data Model Loader Slots **** //


// ************************************************************************** //


// **** START :: PIHM Simulation Slots **** //

void PIHMgisDialog::on_pushButtonPIHMSimulation_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonPIHMSimulation_clicked";

    try {
        QString filename_open_project = user_pihmgis_root_folder+user_pihmgis_project_folder + "/OpenProject.txt";

        PIHMSimulation *PIHMSimulationDialog = new PIHMSimulation(this, filename_open_project);
        PIHMSimulationDialog->setModal(true);
        //PIHMSimulationDialog->ModelVersion = ui->comboBoxPIHMVersion->currentText();
        PIHMSimulationDialog->show();

    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonPIHMSimulation_clicked is returning w/o checking";
    }
}

// **** END   :: PIHM Simulation Slots **** //


// ************************************************************************** //


// **** START :: Visual Analytics Slots **** //

void PIHMgisDialog::on_pushButtonVisualAnalyticsSpatialWatershed_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonVisualAnalyticsSpatialWatershed_clicked";

    try {
        QString filename_open_project = user_pihmgis_root_folder+user_pihmgis_project_folder + "/OpenProject.txt";

        MeshSpatial *MeshSpatialDialog = new MeshSpatial(this, filename_open_project);
        MeshSpatialDialog->setModal(true);
        MeshSpatialDialog->show();

    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonVisualAnalyticsSpatialWatershed_clicked is returning w/o checking";
    }
}

void PIHMgisDialog::on_pushButtonVisualAnalyticsTemporalWatershed_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonVisualAnalyticsTemporalWatershed_clicked";

    try {
        QString filename_open_project = user_pihmgis_root_folder+user_pihmgis_project_folder + "/OpenProject.txt";

        MeshTemporal *MeshTemporalDialog = new MeshTemporal(this, filename_open_project);
        MeshTemporalDialog->setModal(true);
        MeshTemporalDialog->show();

    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonVisualAnalyticsTemporalWatershed_clicked is returning w/o checking";
    }
}

void PIHMgisDialog::on_pushButtonVisualAnalyticsSpatialRiverNetwork_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonVisualAnalyticsSpatialRiverNetwork_clicked";

    try {
        QString filename_open_project = user_pihmgis_root_folder+user_pihmgis_project_folder + "/OpenProject.txt";

        RiverSpatial *RiverSpatialDialog = new RiverSpatial(this, filename_open_project);
        RiverSpatialDialog->show();
    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonVisualAnalyticsSpatialRiverNetwork_clicked is returning w/o checking";
    }
}

void PIHMgisDialog::on_pushButtonVisualAnalyticsTemporalRiverNetwork_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonVisualAnalyticsTemporalRiverNetwork_clicked";

    try {
        RiverTemporal *RiverTemporalDialog = new RiverTemporal(this);
        RiverTemporalDialog->show();
    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonVisualAnalyticsTemporalRiverNetwork_clicked is returning w/o checking";
    }
}

// **** END   :: Visual Analytics Slots **** //


// ************************************************************************** //

//void PIHMgisDialog::on_pushButton_clicked()
//{
//    //if(print_debug_messages)
//    qDebug() << "INFO: Start PIHMgisDialog::on_pushButton_clicked";

//    try {
//        qDebug() << "on_pushButtonPIHMgisProjectNew_clicked";

//        NewProject *NewProjectDialog = new NewProject(this);
//        NewProjectDialog->show();
//    } catch (...) {
//        qDebug() << "Error: PIHMgisDialog::on_pushButton_clicked is returning w/o checking";
//    }
//}



void PIHMgisDialog::on_pushButton_PickWorkspace_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButton_PickWorkspace_clicked";

    try {

        QString ProjectHome = QFileDialog::getExistingDirectory(this, "Specify Home Folder", user_pihmgis_root_folder, 0);
        qDebug() << "ProjectHome = " << ProjectHome;

        if(ProjectHome.length() > 0 )
        {
            user_pihmgis_root_folder = ProjectHome;

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

        }

        update_current_label();

    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButton_PickWorkspace_clicked is returning w/o checking";
    }

}

bool fileExists(QString path) {

    // QString tmp = path.replace("/","\\");
    QFileInfo check_file(path);

    // check if file exists and if yes: Is it really a file and no directory?
    if (check_file.exists() && check_file.isFile()) {
        return true;
    } else {
        return false;
    }
}

qint64 file_Size(QString path){

    QFileInfo check_file(path);

    // check if file exists and if yes: Is it really a file and no directory?
    if (check_file.exists() && check_file.isFile())
    {
        return check_file.size();
    } else {
        return -1;
    }
}



//void PIHMgisDialog::on_pushButtonWorkFlow7_clicked()
//{
//    qDebug() << "Error: PIHMgisDialog::on_pushButtonWorkFlow7_clicked is returning w/o checking";

//}


void PIHMgisDialog::on_pushButton_PickWorkspace_clicked(bool checked)
{
    qDebug() << "Error: PIHMgisDialog::on_pushButton_PickWorkspace_clicked is returning w/o checking";

}
