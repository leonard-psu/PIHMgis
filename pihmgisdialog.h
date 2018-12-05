#ifndef PIHMGISDIALOG_H
#define PIHMGISDIALOG_H

#include <QMainWindow>
#include <QWidget>
#include <QString>
#include <QDir>

namespace Ui {
class PIHMgisDialog;
}

class PIHMgisDialog : public QMainWindow
{
    Q_OBJECT

public:
    explicit PIHMgisDialog(QWidget *parent = 0);
    ~PIHMgisDialog();

    void Log_Message(QString message); //Display on main window log messages

public slots:
    void set_defaults(QStringList DEFAULT_PARAM);

private slots:

    void on_pushButtonPIHMgisProjectNew_clicked();

   // void on_pushButtonPIHMgisProjectOpen_clicked();

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

    void on_pushButton_PickWorkspace_clicked();

    void on_pushButtonPIHMgisProjectInspect_clicked();

    void on_pushButtonClearLog_clicked();

private:
    void Setup_Menu();
    void Clear_Log();
    void Log_Error_Message(QString message);

    void update_project_file_label();
    void update_current_workspace_label();

    bool create_default_project_workspace();
    bool enable_project_settings(bool enabled);
    bool check_directory_IsEmpty(const QDir& _dir);
    bool check_if_pihmgis_project_exists();

    int check_pihmgis_project_exists(QString folder);


    Ui::PIHMgisDialog *ui;
    QString LogsString;

    //File menu
    QAction *mnu_quit;
    void menu_quit();

    //Log menu
    void menu_debug_messages();
    void menu_log_messages();
    void menu_log_many();

    QAction *mnu_debug;     //static bool print_debug_messages = false;  //Print to console window
    QAction *mnu_log_debug; //static bool print_log_messages = true;     //Print to widget log window (Only important messages)
    QAction *mnu_log_many;  //static bool print_many_messages = false;

    //Help menu
    QAction *mnu_help;
    void menu_help();

};

#endif // PIHMGISDIALOG_H
