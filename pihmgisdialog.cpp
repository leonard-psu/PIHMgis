#include <QDir>
#include <QDebug>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include <QThread>

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

PIHMgisDialog::PIHMgisDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PIHMgisDialog)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog";

    try {

        this->setWindowIcon(QIcon("Icons/PIHMgis000.icns"));
        ui->setupUi(this);


        qDebug() << "PIHMgisDialog started";

        ui->label_home_workspace->setText("Current workspace: " + user_pihmgis_root_folder);


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
            //        if (DEFAULT_PARAM.at(i) == "WORKFLOW1") { boolWORKFLOW1 = true; ui->pushButtonWorkFlow1->setFocus(); continue; }
            //        if (DEFAULT_PARAM.at(i) == "WORKFLOW2") { boolWORKFLOW2 = true; ui->pushButtonWorkFlow2->setFocus(); continue; }
            //        if (DEFAULT_PARAM.at(i) == "WORKFLOW3") { boolWORKFLOW3 = true; ui->pushButtonWorkFlow3->setFocus(); continue; }
            //        if (DEFAULT_PARAM.at(i) == "WORKFLOW4") { boolWORKFLOW4 = true; ui->pushButtonWorkFlow4->setFocus(); continue; }
            //        if (DEFAULT_PARAM.at(i) == "WORKFLOW5") { boolWORKFLOW5 = true; ui->pushButtonWorkFlow5->setFocus(); continue; }
            //        if (DEFAULT_PARAM.at(i) == "WORKFLOW6") { boolWORKFLOW6 = true; ui->pushButtonWorkFlow6->setFocus(); continue; }
            //        if (DEFAULT_PARAM.at(i) == "WORKFLOW7") { boolWORKFLOW7 = true; ui->pushButtonWorkFlow7->setFocus(); continue; }

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
        //    ui->pushButtonWorkFlow1->setDefault(boolWORKFLOW1);
        //    ui->pushButtonWorkFlow2->setDefault(boolWORKFLOW2);
        //    ui->pushButtonWorkFlow3->setDefault(boolWORKFLOW3);
        //    ui->pushButtonWorkFlow4->setDefault(boolWORKFLOW4);
        //    ui->pushButtonWorkFlow5->setDefault(boolWORKFLOW5);
        //    ui->pushButtonWorkFlow6->setDefault(boolWORKFLOW6);
        //    ui->pushButtonWorkFlow7->setDefault(boolWORKFLOW7);

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

void PIHMgisDialog::on_pushButtonWorkFlow0_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonWorkFlow0_clicked";

    try {
        bool success = QDesktopServices::openUrl(QUrl("http://www.pihm.psu.edu"));
        QStringList default_params; default_params << "WORKFLOW1"; set_defaults(default_params);
    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonWorkFlow0_clicked is returning w/o checking";
    }
}

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
        ImportProjectDialog->show();
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
        FillPits *FillPitsDialog = new FillPits(this);
        FillPitsDialog->show();
    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonRasterProcessingFillPits_clicked is returning w/o checking";
    }
}

void PIHMgisDialog::on_pushButtonRasterProcessingFlowGrids_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonRasterProcessingFlowGrids_clicked";

    try {
        FlowGrids *FlowGridsDialog = new FlowGrids(this);
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
        StreamGrids *StreamGridsDialog = new StreamGrids(this);
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
        LinkGrids *LinkGridsDialog = new LinkGrids(this);
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
        CatchmentGrids *CatchmentGridsDialog = new CatchmentGrids(this);
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
        StreamPolyline *StreamPolylineDialog = new StreamPolyline(this);
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
        CatchmentPolygon *CatchmentPolygonDialog = new CatchmentPolygon(this);
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
        DissolvePolygons *DissolvePolygonsDialog = new DissolvePolygons(this);
        DissolvePolygonsDialog->show();
    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButtonVectorProcessingDissolvePolygons_clicked is returning w/o checking";
    }
}

void PIHMgisDialog::on_pushButtonVectorProcessingPolygonToPolylines_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButtonVectorProcessingPolygonToPolylines_clicked";

    try {
        PolygonToPolylines *PolygonToPolylinesDialog = new PolygonToPolylines(this);
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
        SimplifyPolylines *SimplifyPolylinesDialog = new SimplifyPolylines(this);
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
        PolylineToLines *PolylineToLinesDialog = new PolylineToLines(this);
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
        MergeVectorLayers *MergeVectorLayersDialog = new MergeVectorLayers(this);
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
        ReadTopology *ReadTopologyDialog = new ReadTopology(this);
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
        DelaunayTriangulation *DelaunayTriangulationDialog = new DelaunayTriangulation(this);
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
        TINShapeLayer *TINShapeLayerDialog = new TINShapeLayer(this);
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
        MeshDataFile *MeshDataFileDialog = new MeshDataFile(this);
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
        AttDataFile *AttDataFileDialog = new AttDataFile(this);
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
        RivDataFile *RivDataFileDialog = new RivDataFile(this);
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
        SoilDataFile *SoilDataFileDialog = new SoilDataFile(this);
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
        GeolDataFile *GeolDataFileDialog = new GeolDataFile(this);
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
        LcDataFile *LcDataFileDialog = new LcDataFile(this);
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
        InitDataFile *InitDataFileDialog = new InitDataFile(this);
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
        IbcDataFile *IbcDataFileDialog = new IbcDataFile(this);
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
        ParaDataFile *ParaDataFileDialog = new ParaDataFile(this);
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
        CalibDataFile *CalibDataFileDialog = new CalibDataFile(this);
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
        QStringList default_params; default_params << "WORKFLOW6" << "WORKFLOW8"; set_defaults(default_params);
        bool success = QDesktopServices::openUrl(QUrl("http://cataract.cee.psu.edu/PIHM/index.php/PIHMgis_3.0#forc_Data_File"));

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
        PIHMSimulation *PIHMSimulationDialog = new PIHMSimulation(this);
        PIHMSimulationDialog->ModelVersion = ui->comboBoxPIHMVersion->currentText();
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
        MeshSpatial *MeshSpatialDialog = new MeshSpatial(this);
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
        MeshTemporal *MeshTemporalDialog = new MeshTemporal(this);
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
        RiverSpatial *RiverSpatialDialog = new RiverSpatial(this);
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

void PIHMgisDialog::on_pushButton_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButton_clicked";

    try {
        qDebug() << "on_pushButtonPIHMgisProjectNew_clicked";

        NewProject *NewProjectDialog = new NewProject(this);
        NewProjectDialog->show();
    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButton_clicked is returning w/o checking";
    }
}


void PIHMgisDialog::on_pushButton_clicked(bool checked)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButton_clicked";

    try {
        qDebug() << "on_pushButtonPIHMgisProjectNew_clicked";
    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButton_clicked is returning w/o checking";
    }
}

void PIHMgisDialog::on_pushButton_2_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start PIHMgisDialog::on_pushButton_2_clicked";

    try {
        qDebug() << "on_pushButton_2_clicked";
    } catch (...) {
        qDebug() << "Error: PIHMgisDialog::on_pushButton_2_clicked is returning w/o checking";
    }

}
