#ifndef PIHMGISDIALOG_H
#define PIHMGISDIALOG_H

#include <QWidget>
#include <QString>

namespace Ui {
class PIHMgisDialog;
}

class PIHMgisDialog : public QWidget
{
    Q_OBJECT

public:
    explicit PIHMgisDialog(QWidget *parent = 0);
    ~PIHMgisDialog();

public slots:
    void set_defaults(QStringList DEFAULT_PARAM);

private slots:

    void on_pushButtonPIHMgisProjectNew_clicked();

    void on_pushButtonPIHMgisProjectOpen_clicked();

    void on_pushButtonPIHMgisProjectImport_clicked();

    void on_pushButtonPIHMgisProjectClose_clicked();

    // **** :: Raster Processing Slots **** //

    void on_pushButtonRasterProcessingFillPits_clicked();

    void on_pushButtonRasterProcessingFlowGrids_clicked();

    void on_pushButtonRasterProcessingStreamGrids_clicked();

    void on_pushButtonRasterProcessingLinkGrids_clicked();

    void on_pushButtonRasterProcessingCatchmentGrids_clicked();

    void on_pushButtonRasterProcessingStreamPolyline_clicked();

    void on_pushButtonRasterProcessingCatchmentPolygon_clicked();

    // **** :: Vector Processing Slots **** //

    void on_pushButtonVectorProcessingDissolvePolygons_clicked();

    void on_pushButtonVectorProcessingPolygonToPolylines_clicked();

    void on_pushButtonVectorProcessingSimplifyPolylines_clicked();

    void on_pushButtonVectorProcessingPolylineToLines_clicked();

    void on_pushButtonVectorProcessingMergeVectorLayers_clicked();

    // **** :: Domain Decomposition Slots v //

    void on_pushButtonDomainDecompositionReadTopology_clicked();

    void on_pushButtonDomainDecompositionTriangulation_clicked();

    void on_pushButtonDomainDecompositionTINShapeLayer_clicked();

    // **** :: Data Model Loader Slots **** //

    void on_pushButtonDataModelLoaderMeshDataFile_clicked();

    void on_pushButtonDataModelLoaderAttDataFile_clicked();

    void on_pushButtonDataModelLoaderRivDataFile_clicked();

    void on_pushButtonDataModelLoaderSoilDataFile_clicked();

    void on_pushButtonDataModelLoaderGeolDataFile_clicked();

    void on_pushButtonDataModelLoaderLcDataFile_clicked();

    void on_pushButtonDataModelLoaderInitDataFile_clicked();

    void on_pushButtonDataModelLoaderIbcDataFile_clicked();

    void on_pushButtonDataModelLoaderParamDataFile_clicked();

    void on_pushButtonDataModelLoaderCalibDataFile_clicked();

    void on_pushButtonDataModelLoaderForcDataFile_clicked();

    // **** :: PIHM Simulation Slots **** //

    void on_pushButtonPIHMSimulation_clicked();

    // **** :: Visual Analytics Slots **** //

    void on_pushButtonVisualAnalyticsSpatialWatershed_clicked();

    void on_pushButtonVisualAnalyticsTemporalWatershed_clicked();

    void on_pushButtonVisualAnalyticsSpatialRiverNetwork_clicked();

    void on_pushButtonVisualAnalyticsTemporalRiverNetwork_clicked();


    //void on_PIHMgisToolBox_Help_windowIconChanged(const QIcon &icon);

    //void on_pushButtonWorkFlow6_clicked();

    //void on_pushButton_clicked();

    //void on_pushButton_clicked(bool checked);

    //void on_pushButton_2_clicked();

    void on_pushButton_PickWorkspace_clicked();


    void on_pushButton_PickWorkspace_clicked(bool checked);

private:


    void update_project_file_label();
    void update_current_workspace_label();
    bool create_default_project_workspace();
    bool set_project_button_settings(bool enabled);

    Ui::PIHMgisDialog *ui;
};

#endif // PIHMGISDIALOG_H
