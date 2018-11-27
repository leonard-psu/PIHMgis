#-------------------------------------------------
#
# Project created by QtCreator 2013-10-11T17:40:21
#
#-------------------------------------------------

QT       += core gui
#QT += widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += core
greaterThan(QT_MAJOR_VERSION, 4): QT += gui
greaterThan(QT_MAJOR_VERSION, 4): QT += concurrent

TARGET = PIHMgis
TEMPLATE = app

QMAKE_CFLAGS += -std=c99

SOURCES += main.cpp\
        pihmgisdialog.cpp \
    1ProjectManagement/1NewProject/newproject.cpp \
    1ProjectManagement/2OpenProject/openproject.cpp \
    1ProjectManagement/3ImportProject/importproject.cpp \
    1ProjectManagement/4CloseProject/closeproject.cpp \
    2RasterProcessing/1FillPits/fillpits.cpp \
    0LibsIO/IOProjectFile.cpp \
    0LibsRaster/ADFFiletoASCFile.cpp \
    0LibsRaster/flood.cpp \
    0LibsRaster/gridio.cpp \
    0LibsRaster/gridio_null.cpp \
    0LibsRaster/lsmcom.cpp \
    0LibsRaster/callocate.cpp \
    0LibsRaster/avcalls_null.cpp \
    2RasterProcessing/2FlowGrids/flowgrids.cpp \
    0LibsRaster/setdir.cpp \
    0LibsRaster/aread8.cpp \
    2RasterProcessing/3StreamGrids/streamgrids.cpp \
    0LibsRaster/stream_definition.cpp \
    2RasterProcessing/4LinkGrids/linkgrids.cpp \
    0LibsRaster/stream_links.cpp \
    2RasterProcessing/5CatchmentGrids/catchmentgrids.cpp \
    0LibsRaster/catchment.cpp \
    2RasterProcessing/6StreamPolyline/streampolyline.cpp \
    0LibsShape/shpopen.c \
    0LibsShape/dbfopen.c \
    0LibsRaster/stream_shape.cpp \
    2RasterProcessing/7CatchmentPolygon/catchmentpolygon.cpp \
    0LibsRaster/catchment_shape.cpp \
    3VectorProcessing/1DissolvePolygons/dissolvepolygons.cpp \
    0LibsVector/dissolve.cpp \
    3VectorProcessing/2PolygonToPolylines/polygontopolylines.cpp \
    0LibsVector/polygon_polylines.cpp \
    3VectorProcessing/3SimplifyPolylines/simplifypolylines.cpp \
    0LibsVector/simplify_shape.cpp \
    0LibsVector/simplify_polyline.cpp \
    3VectorProcessing/4PolylineToLines/polylinetolines.cpp \
    0LibsVector/polyline_splitline.cpp \
    0LibsVector/dissolve_ogr.cpp \
    3VectorProcessing/5MergeVectorLayers/mergevectorlayers.cpp \
    0LibsVector/merge_lines.cpp \
    4DomainDecomposition/1ReadTopology/readtopology.cpp \
    0LibsOther/shape_pslg.cpp \
    4DomainDecomposition/2DelaunayTriangulation/delaunaytriangulation.cpp \
    4DomainDecomposition/3TINShapeLayer/tinshapelayer.cpp \
    0LibsOther/triangle_shewchuk.cpp \
    0LibsVector/tin_shape.cpp \
    5DataModelLoader/1MeshDataFile/meshdatafile.cpp \
    0LibsOther/mesh_data_file.cpp \
    0LibsOther/raster_grid_value.cpp \
    0LibsOther/interpolate_river_nodes_elev.cpp \
    5DataModelLoader/2AttDataFile/attdatafile.cpp \
    0LibsOther/att_data_file.cpp \
    5DataModelLoader/3RivDataFile/rivdatafile.cpp \
    0LibsOther/riv_data_file.cpp \
    5DataModelLoader/4SoilDataFile/soildatafile.cpp \
    5DataModelLoader/5GeolDataFile/geoldatafile.cpp \
    0LibsOther/pedo_transfer_functions.cpp \
    5DataModelLoader/6LcDataFile/lcdatafile.cpp \
    5DataModelLoader/7InitDataFile/initdatafile.cpp \
    5DataModelLoader/8IbcDataFile/ibcdatafile.cpp \
    5DataModelLoader/9ParaDataFile/paradatafile.cpp \
    5DataModelLoader/10CalibDataFile/calibdatafile.cpp \
    6PIHMSimulation/1PIHM_v2.2/pihmsimulation.cpp \
    6PIHMSimulation/PIHMSrc/PIHM_v2.2/update.cpp \
    6PIHMSimulation/PIHMSrc/PIHM_v2.2/read_alloc.cpp \
    6PIHMSimulation/PIHMSrc/PIHM_v2.2/print.cpp \
    6PIHMSimulation/PIHMSrc/PIHM_v2.2/pihm.cpp \
    6PIHMSimulation/PIHMSrc/PIHM_v2.2/is_sm_et.cpp \
    6PIHMSimulation/PIHMSrc/PIHM_v2.2/initialize.cpp \
    6PIHMSimulation/PIHMSrc/PIHM_v2.2/f.cpp \
    7VisualAnalytics/4RiverTemporal/rivertemporal.cpp \
    7VisualAnalytics/QCustomPlot/qcustomplot.cpp \
    7VisualAnalytics/QCustomPlotMainWindow/qcustomplotmainwindow.cpp \
    7VisualAnalytics/2MeshTemporal/meshtemporal.cpp \
    7VisualAnalytics/1MeshSpatial/meshspatial.cpp \
    7VisualAnalytics/3RiverSpatial/riverspatial.cpp \
    0LibsIO/IOProjectFile.cpp \
    0LibsOther/att_data_file.cpp \
    0LibsOther/interpolate_river_nodes_elev.cpp \
    0LibsOther/mesh_data_file.cpp \
    0LibsOther/pedo_transfer_functions.cpp \
    0LibsOther/raster_grid_value.cpp \
    0LibsOther/riv_data_file.cpp \
    0LibsOther/shape_pslg.cpp \
    0LibsOther/triangle_shewchuk.cpp \
    0LibsRaster/ADFFiletoASCFile.cpp \
    0LibsRaster/aread8.cpp \
    0LibsRaster/avcalls_null.cpp \
    0LibsRaster/callocate.cpp \
    0LibsRaster/catchment.cpp \
    0LibsRaster/catchment_shape.cpp \
    0LibsRaster/flood.cpp \
    0LibsRaster/gridio.cpp \
    0LibsRaster/gridio_null.cpp \
    0LibsRaster/lsmcom.cpp \
    0LibsRaster/setdir.cpp \
    0LibsRaster/stream_definition.cpp \
    0LibsRaster/stream_links.cpp \
    0LibsRaster/stream_shape.cpp \
    0LibsVector/dissolve.cpp \
    0LibsVector/dissolve_ogr.cpp \
    0LibsVector/merge_lines.cpp \
    0LibsVector/polygon_polylines.cpp \
    0LibsVector/polyline_splitline.cpp \
    0LibsVector/simplify_polyline.cpp \
    0LibsVector/simplify_shape.cpp \
    0LibsVector/tin_shape.cpp \
    1ProjectManagement/1NewProject/newproject.cpp \
    1ProjectManagement/2OpenProject/openproject.cpp \
    1ProjectManagement/3ImportProject/importproject.cpp \
    1ProjectManagement/4CloseProject/closeproject.cpp \
    #1ProjectManagement/Project/CloseProject/closeproject.cpp \
    #1ProjectManagement/Project/CloseProject/main.cpp \
    #1ProjectManagement/Project/DefineProject/defineproject.cpp \
    #1ProjectManagement/Project/DefineProject/main.cpp \
    #1ProjectManagement/Project/ImportProject/importproject.cpp \
    #1ProjectManagement/Project/ImportProject/main.cpp \
    #1ProjectManagement/Project/OpenProject/main.cpp \
    #1ProjectManagement/Project/OpenProject/openproject.cpp \
    2RasterProcessing/1FillPits/fillpits.cpp \
    2RasterProcessing/2FlowGrids/flowgrids.cpp \
    2RasterProcessing/3StreamGrids/streamgrids.cpp \
    2RasterProcessing/4LinkGrids/linkgrids.cpp \
    2RasterProcessing/5CatchmentGrids/catchmentgrids.cpp \
    2RasterProcessing/6StreamPolyline/streampolyline.cpp \
    2RasterProcessing/7CatchmentPolygon/catchmentpolygon.cpp \
    3VectorProcessing/1DissolvePolygons/dissolvepolygons.cpp \
    #3VectorProcessing/1DissolvePolygons copy/dissolvepolygons.cpp \
    3VectorProcessing/2PolygonToPolylines/polygontopolylines.cpp \
    3VectorProcessing/3SimplifyPolylines/simplifypolylines.cpp \
    3VectorProcessing/4PolylineToLines/polylinetolines.cpp \
    3VectorProcessing/5MergeVectorLayers/mergevectorlayers.cpp \
    4DomainDecomposition/1ReadTopology/readtopology.cpp \
    4DomainDecomposition/2DelaunayTriangulation/delaunaytriangulation.cpp \
    4DomainDecomposition/3TINShapeLayer/tinshapelayer.cpp \
    5DataModelLoader/10CalibDataFile/calibdatafile.cpp \
    5DataModelLoader/1MeshDataFile/meshdatafile.cpp \
    5DataModelLoader/2AttDataFile/attdatafile.cpp \
    5DataModelLoader/3RivDataFile/rivdatafile.cpp \
    5DataModelLoader/4SoilDataFile/soildatafile.cpp \
    #5DataModelLoader/4SoilDataFile copy/soildatafile.cpp \
    5DataModelLoader/5GeolDataFile/geoldatafile.cpp \
    5DataModelLoader/6LcDataFile/lcdatafile.cpp \
    5DataModelLoader/7InitDataFile/initdatafile.cpp \
    5DataModelLoader/8IbcDataFile/ibcdatafile.cpp \
    5DataModelLoader/9ParaDataFile/paradatafile.cpp \
    6PIHMSimulation/1PIHM_v2.2/pihmsimulation.cpp \
   # 6PIHMSimulation/1PIHM_v2.2 copy/pihm_v22.cpp \
   # 6PIHMSimulation/1PIHM_v2.2 copy/pihm_v22.cpp \
    6PIHMSimulation/PIHMSrc/PIHM_v2.2/f.cpp \
    6PIHMSimulation/PIHMSrc/PIHM_v2.2/initialize.cpp \
    6PIHMSimulation/PIHMSrc/PIHM_v2.2/is_sm_et.cpp \
    6PIHMSimulation/PIHMSrc/PIHM_v2.2/pihm.cpp \
    6PIHMSimulation/PIHMSrc/PIHM_v2.2/print.cpp \
    6PIHMSimulation/PIHMSrc/PIHM_v2.2/read_alloc.cpp \
    6PIHMSimulation/PIHMSrc/PIHM_v2.2/update.cpp \
    #6PIHMSimulation/PIHMThread copy/PIHMThread.cpp \
    7VisualAnalytics/1MeshSpatial/meshspatial.cpp \
    7VisualAnalytics/2MeshTemporal/meshtemporal.cpp \
    7VisualAnalytics/3RiverSpatial/riverspatial.cpp \
    7VisualAnalytics/4RiverTemporal/rivertemporal.cpp \
    7VisualAnalytics/QCustomPlot/qcustomplot.cpp \
    7VisualAnalytics/QCustomPlotMainWindow/qcustomplotmainwindow.cpp \
    main.cpp \
    moc_attdatafile.cpp \
    moc_calibdatafile.cpp \
    moc_catchmentgrids.cpp \
    moc_catchmentpolygon.cpp \
    moc_closeproject.cpp \
    moc_delaunaytriangulation.cpp \
    moc_dissolvepolygons.cpp \
    moc_fillpits.cpp \
    moc_flowgrids.cpp \
    moc_geoldatafile.cpp \
    moc_ibcdatafile.cpp \
    moc_importproject.cpp \
    moc_initdatafile.cpp \
    moc_lcdatafile.cpp \
    moc_linkgrids.cpp \
    moc_mergevectorlayers.cpp \
    moc_meshdatafile.cpp \
    moc_meshspatial.cpp \
    moc_meshtemporal.cpp \
    moc_newproject.cpp \
    moc_openproject.cpp \
    moc_paradatafile.cpp \
    #moc_pihm_v22.cpp \
    moc_pihmgisdialog.cpp \
    moc_pihmsimulation.cpp \
    moc_polygontopolylines.cpp \
    moc_polylinetolines.cpp \
    moc_qcustomplot.cpp \
    moc_qcustomplotmainwindow.cpp \
    moc_readtopology.cpp \
    moc_rivdatafile.cpp \
    moc_riverspatial.cpp \
    moc_rivertemporal.cpp \
    moc_simplifypolylines.cpp \
    moc_soildatafile.cpp \
    moc_streamgrids.cpp \
    moc_streampolyline.cpp \
    moc_tinshapelayer.cpp \
    #pihmgis_plugin_import.cpp \
    pihmgisdialog.cpp \
    qrc_Icons.cpp \
    6PIHMSimulation/PIHMThread/MyThread.cpp

HEADERS  += pihmgisdialog.h \
    1ProjectManagement/1NewProject/newproject.h \
    1ProjectManagement/2OpenProject/openproject.h \
    1ProjectManagement/3ImportProject/importproject.h \
    1ProjectManagement/4CloseProject/closeproject.h \
    2RasterProcessing/1FillPits/fillpits.h \
    0LibsIO/IOProjectFile.h \
    0LibsRaster/ADFFiletoASCFile.h \
    0LibsRaster/flood.h \
    0LibsRaster/lsm.h \
    0LibsRaster/gridio.h \
    0LibsRaster/gioapi.h \
    0LibsRaster/avexec32.h \
    2RasterProcessing/2FlowGrids/flowgrids.h \
    0LibsRaster/setdir.h \
    0LibsRaster/aread8.h \
    2RasterProcessing/3StreamGrids/streamgrids.h \
    0LibsRaster/stream_definition.h \
    2RasterProcessing/4LinkGrids/linkgrids.h \
    0LibsRaster/stream_links.h \
    2RasterProcessing/5CatchmentGrids/catchmentgrids.h \
    0LibsRaster/catchment.h \
    2RasterProcessing/6StreamPolyline/streampolyline.h \
    0LibsShape/shapefil.h \
    0LibsRaster/stream_shape.h \
    2RasterProcessing/7CatchmentPolygon/catchmentpolygon.h \
    0LibsRaster/catchment_shape.h \
    3VectorProcessing/1DissolvePolygons/dissolvepolygons.h \
    0LibsVector/dissolve.h \
    3VectorProcessing/2PolygonToPolylines/polygontopolylines.h \
    0LibsVector/polygon_polylines.h \
    3VectorProcessing/3SimplifyPolylines/simplifypolylines.h \
    0LibsVector/simplify_shape.h \
    0LibsVector/simplify_polyline.h \
    3VectorProcessing/4PolylineToLines/polylinetolines.h \
    0LibsVector/polyline_splitline.h \
    0LibsVector/dissolve_ogr.h \
    3VectorProcessing/5MergeVectorLayers/mergevectorlayers.h \
    0LibsVector/merge_lines.h \
    4DomainDecomposition/1ReadTopology/readtopology.h \
    0LibsOther/shape_pslg.h \
    4DomainDecomposition/2DelaunayTriangulation/delaunaytriangulation.h \
    4DomainDecomposition/3TINShapeLayer/tinshapelayer.h \
    0LibsOther/triangle_shewchuk.h \
    0LibsVector/tin_shape.h \
    5DataModelLoader/1MeshDataFile/meshdatafile.h \
    0LibsOther/mesh_data_file.h \
    0LibsOther/raster_grid_value.h \
    0LibsOther/interpolate_river_nodes_elev.h \
    5DataModelLoader/2AttDataFile/attdatafile.h \
    0LibsOther/att_data_file.h \
    5DataModelLoader/3RivDataFile/rivdatafile.h \
    0LibsOther/riv_data_file.h \
    5DataModelLoader/4SoilDataFile/soildatafile.h \
    5DataModelLoader/5GeolDataFile/geoldatafile.h \
    0LibsOther/pedo_transfer_functions.h \
    5DataModelLoader/6LcDataFile/lcdatafile.h \
    5DataModelLoader/7InitDataFile/initdatafile.h \
    5DataModelLoader/8IbcDataFile/ibcdatafile.h \
    5DataModelLoader/9ParaDataFile/paradatafile.h \
    5DataModelLoader/10CalibDataFile/calibdatafile.h \
    6PIHMSimulation/1PIHM_v2.2/pihmsimulation.h \
    6PIHMSimulation/PIHMSrc/PIHM_v2.2/pihm.h \
    6PIHMSimulation/PIHMSrc/PIHM_v2.2/update.h \
    6PIHMSimulation/PIHMSrc/PIHM_v2.2/initialize.h \
    7VisualAnalytics/4RiverTemporal/rivertemporal.h \
    7VisualAnalytics/QCustomPlotMainWindow/qcustomplotmainwindow.h \
    7VisualAnalytics/QCustomPlot/qcustomplot.h \
    7VisualAnalytics/2MeshTemporal/meshtemporal.h \
    7VisualAnalytics/1MeshSpatial/meshspatial.h \
    7VisualAnalytics/3RiverSpatial/riverspatial.h \
    0LibsIO/IOProjectFile.h \
    0LibsOther/att_data_file.h \
    0LibsOther/interpolate_river_nodes_elev.h \
    0LibsOther/mesh_data_file.h \
    0LibsOther/pedo_transfer_functions.h \
    0LibsOther/raster_grid_value.h \
    0LibsOther/riv_data_file.h \
    0LibsOther/shape_pslg.h \
    0LibsOther/triangle_shewchuk.h \
    0LibsRaster/ADFFiletoASCFile.h \
    0LibsRaster/aread8.h \
    0LibsRaster/avexec32.h \
    0LibsRaster/catchment.h \
    0LibsRaster/catchment_shape.h \
    0LibsRaster/flood.h \
    0LibsRaster/gioapi.h \
    0LibsRaster/gridio.h \
    0LibsRaster/lsm.h \
    0LibsRaster/setdir.h \
    0LibsRaster/stream_definition.h \
    0LibsRaster/stream_links.h \
    0LibsRaster/stream_shape.h \
    0LibsShape/shapefil.h \
    0LibsVector/dissolve.h \
    0LibsVector/dissolve_ogr.h \
    0LibsVector/merge_lines.h \
    0LibsVector/polygon_polylines.h \
    0LibsVector/polyline_splitline.h \
    0LibsVector/simplify_polyline.h \
    0LibsVector/simplify_shape.h \
    0LibsVector/tin_shape.h \
    1ProjectManagement/1NewProject/newproject.h \
    1ProjectManagement/2OpenProject/openproject.h \
    1ProjectManagement/3ImportProject/importproject.h \
    1ProjectManagement/4CloseProject/closeproject.h \
#    1ProjectManagement/Project/CloseProject/closeproject.h \
#    1ProjectManagement/Project/DefineProject/defineproject.h \
#    1ProjectManagement/Project/DefineProject/ui_defineproject.h \  #ADDED
#    1ProjectManagement/Project/ImportProject/importproject.h \
#    1ProjectManagement/Project/OpenProject/openproject.h \
    2RasterProcessing/1FillPits/fillpits.h \
    2RasterProcessing/2FlowGrids/flowgrids.h \
    2RasterProcessing/3StreamGrids/streamgrids.h \
    2RasterProcessing/4LinkGrids/linkgrids.h \
    2RasterProcessing/5CatchmentGrids/catchmentgrids.h \
    2RasterProcessing/6StreamPolyline/streampolyline.h \
    2RasterProcessing/7CatchmentPolygon/catchmentpolygon.h \
    3VectorProcessing/1DissolvePolygons/dissolvepolygons.h \
    #3VectorProcessing/1DissolvePolygons copy/dissolvepolygons.h \
    3VectorProcessing/2PolygonToPolylines/polygontopolylines.h \
    3VectorProcessing/3SimplifyPolylines/simplifypolylines.h \
    3VectorProcessing/4PolylineToLines/polylinetolines.h \
    3VectorProcessing/5MergeVectorLayers/mergevectorlayers.h \
    4DomainDecomposition/1ReadTopology/readtopology.h \
    4DomainDecomposition/2DelaunayTriangulation/delaunaytriangulation.h \
    4DomainDecomposition/3TINShapeLayer/tinshapelayer.h \
    5DataModelLoader/10CalibDataFile/calibdatafile.h \
    5DataModelLoader/1MeshDataFile/meshdatafile.h \
    5DataModelLoader/2AttDataFile/attdatafile.h \
    5DataModelLoader/3RivDataFile/rivdatafile.h \
    5DataModelLoader/4SoilDataFile/soildatafile.h \
    #5DataModelLoader/4SoilDataFile copy/soildatafile.h \
    5DataModelLoader/5GeolDataFile/geoldatafile.h \
    5DataModelLoader/6LcDataFile/lcdatafile.h \
    5DataModelLoader/7InitDataFile/initdatafile.h \
    5DataModelLoader/8IbcDataFile/ibcdatafile.h \
    5DataModelLoader/9ParaDataFile/paradatafile.h \
    6PIHMSimulation/1PIHM_v2.2/pihmsimulation.h \
    #6PIHMSimulation/1PIHM_v2.2 copy/pihm_v22.h \
    6PIHMSimulation/PIHMSrc/PIHM_v2.2/initialize.h \
    6PIHMSimulation/PIHMSrc/PIHM_v2.2/is_sm_et.h \
    6PIHMSimulation/PIHMSrc/PIHM_v2.2/pihm.h \
    6PIHMSimulation/PIHMSrc/PIHM_v2.2/update.h \
    #6PIHMSimulation/PIHMThread copy/PIHMThread.h \
    7VisualAnalytics/1MeshSpatial/meshspatial.h \
    7VisualAnalytics/2MeshTemporal/meshtemporal.h \
    7VisualAnalytics/3RiverSpatial/riverspatial.h \
    7VisualAnalytics/4RiverTemporal/rivertemporal.h \
    7VisualAnalytics/QCustomPlot/qcustomplot.h \
    7VisualAnalytics/QCustomPlotMainWindow/qcustomplotmainwindow.h \
    pihmgisdialog.h \
#    ui_attdatafile.h \
#    ui_calibdatafile.h \
#    ui_catchmentgrids.h \
#    ui_catchmentpolygon.h \
#    ui_closeproject.h \
#    ui_delaunaytriangulation.h \
#    ui_dissolvepolygons.h \
#    ui_fillpits.h \
#    ui_flowgrids.h \
#    ui_geoldatafile.h \
#    ui_ibcdatafile.h \
#    ui_importproject.h \
#    ui_initdatafile.h \
#    ui_lcdatafile.h \
#    ui_linkgrids.h \
#    ui_mergevectorlayers.h \
#    ui_meshdatafile.h \
#    ui_meshspatial.h \
#    ui_meshtemporal.h \
#    ui_newproject.h \
#    ui_openproject.h \
#    ui_paradatafile.h \
#    #ui_pihm_v22.h \
#    ui_pihmgisdialog.h \
#    ui_pihmsimulation.h \
#    ui_polygontopolylines.h \
#    ui_polylinetolines.h \
#    ui_qcustomplotmainwindow.h \
#    ui_readtopology.h \
#    ui_rivdatafile.h \
#    ui_riverspatial.h \
#    ui_rivertemporal.h \
#    ui_simplifypolylines.h \
#    ui_soildatafile.h \
#    ui_streamgrids.h \
#    ui_streampolyline.h \
#    ui_tinshapelayer.h \
    main.h \
    globals.h \
    6PIHMSimulation/PIHMThread/MyThread.h

FORMS    += pihmgisdialog.ui \
    1ProjectManagement/1NewProject/newproject.ui \
    1ProjectManagement/2OpenProject/openproject.ui \
    1ProjectManagement/3ImportProject/importproject.ui \
    1ProjectManagement/4CloseProject/closeproject.ui \
    2RasterProcessing/1FillPits/fillpits.ui \
    2RasterProcessing/2FlowGrids/flowgrids.ui \
    2RasterProcessing/3StreamGrids/streamgrids.ui \
    2RasterProcessing/4LinkGrids/linkgrids.ui \
    2RasterProcessing/5CatchmentGrids/catchmentgrids.ui \
    2RasterProcessing/6StreamPolyline/streampolyline.ui \
    2RasterProcessing/7CatchmentPolygon/catchmentpolygon.ui \
    3VectorProcessing/1DissolvePolygons/dissolvepolygons.ui \
    3VectorProcessing/2PolygonToPolylines/polygontopolylines.ui \
    3VectorProcessing/3SimplifyPolylines/simplifypolylines.ui \
    3VectorProcessing/4PolylineToLines/polylinetolines.ui \
    3VectorProcessing/5MergeVectorLayers/mergevectorlayers.ui \
    4DomainDecomposition/1ReadTopology/readtopology.ui \
    4DomainDecomposition/2DelaunayTriangulation/delaunaytriangulation.ui \
    4DomainDecomposition/3TINShapeLayer/tinshapelayer.ui \
    5DataModelLoader/1MeshDataFile/meshdatafile.ui \
    5DataModelLoader/2AttDataFile/attdatafile.ui \
    5DataModelLoader/3RivDataFile/rivdatafile.ui \
    5DataModelLoader/4SoilDataFile/soildatafile.ui \
    5DataModelLoader/5GeolDataFile/geoldatafile.ui \
    5DataModelLoader/6LcDataFile/lcdatafile.ui \
    5DataModelLoader/7InitDataFile/initdatafile.ui \
    5DataModelLoader/8IbcDataFile/ibcdatafile.ui \
    5DataModelLoader/9ParaDataFile/paradatafile.ui \
    5DataModelLoader/10CalibDataFile/calibdatafile.ui \
    6PIHMSimulation/1PIHM_v2.2/pihmsimulation.ui \
    7VisualAnalytics/4RiverTemporal/rivertemporal.ui \
    7VisualAnalytics/QCustomPlotMainWindow/qcustomplotmainwindow.ui \
    7VisualAnalytics/2MeshTemporal/meshtemporal.ui \
    7VisualAnalytics/1MeshSpatial/meshspatial.ui \
    7VisualAnalytics/3RiverSpatial/riverspatial.ui

OTHER_FILES +=

RESOURCES += \
    Icons.qrc

#ORG macx: LIBS += $$PWD/../../../GDAL/gdal-1.10.0-geos/lib/libgdal.1.dylib

#ORG INCLUDEPATH += $$PWD/../../../GDAL/gdal-1.10.0-geos/include
#ORG DEPENDPATH += $$PWD/../../../GDAL/gdal-1.10.0-geos/include
INCLUDEPATH += $$PWD/../gdal-2.3.1/gcore
DEPENDPATH += $$PWD/../gdal-2.3.1/gcore
INCLUDEPATH += $$PWD/../gdal-2.3.1/port
DEPENDPATH += $$PWD/../gdal-2.3.1/port
INCLUDEPATH += $$PWD/../gdal-2.3.1/ogr
DEPENDPATH += $$PWD/../gdal-2.3.1/ogr
INCLUDEPATH += $$PWD/../gdal-2.3.1/ogr/ogrsf_frmts
DEPENDPATH += $$PWD/../gdal-2.3.1/ogr/ogrsf_frmts

#ORG macx: PRE_TARGETDEPS += $$PWD/../../../GDAL/gdal-1.10.0-geos/lib/libgdal.a

#ORG INCLUDEPATH += $$PWD/../../../SUNDIALS/sundials-2.2.0/include $$PWD/../../../SUNDIALS/sundials-2.2.0/include/sundials $$PWD/../../../SUNDIALS/sundials-2.2.0/include/cvode
#ORG macx: LIBS += $$PWD/../../../SUNDIALS/sundials-2.2.0/lib/libsundials_nvecserial.a
#ORG macx: LIBS += $$PWD/../../../SUNDIALS/sundials-2.2.0/lib/libsundials_cvode.a


ICON = Icons/PIHMgis000.icns

#INCLUDEPATH += $$PWD/../../../QCUSTOMPLOT
#macx: LIBS += $$PWD/../../../QCUSTOMPLOT/qcustomplot-sharedlib/sharedlib-compilation/libqcustomplot.1.dylib

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../gdal231/gdal-2.3.1/ -lgdal_i
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../gdal231/gdal-2.3.1/ -lgdal_id
#else:unix: LIBS += -L$$PWD/../../../../gdal231/gdal-2.3.1/ -lgdal_i

#INCLUDEPATH += $$PWD/../../../../gdal231/gdal-2.3.1
#DEPENDPATH += $$PWD/../../../../gdal231/gdal-2.3.1



win32: LIBS += -L$$PWD/../gdal-2.3.1/ -lgdal_i

INCLUDEPATH += $$PWD/../gdal-2.3.1
DEPENDPATH += $$PWD/../gdal-2.3.1

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../gdal-2.3.1/gdal_i.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/../gdal-2.3.1/libgdal_i.a

win32: LIBS += -L$$PWD/../sundials_windows_install/lib/ -lsundials_cvode

INCLUDEPATH += $$PWD/../sundials_windows_install/include
DEPENDPATH += $$PWD/../sundials_windows_install/include

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../sundials_windows_install/lib/sundials_cvode.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/../sundials_windows_install/lib/libsundials_cvode.a

win32: LIBS += -L$$PWD/../sundials_windows_install/lib/ -lsundials_nvecserial

INCLUDEPATH += $$PWD/../sundials_windows_install/include
DEPENDPATH += $$PWD/../sundials_windows_install/include

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../sundials_windows_install/lib/sundials_nvecserial.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/../sundials_windows_install/lib/libsundials_nvecserial.a
