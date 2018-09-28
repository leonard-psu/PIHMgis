#ifndef IMPORTPROJECT_H
#define IMPORTPROJECT_H

#include <QDialog>

namespace Ui
{
    class ImportProject;
}

class ImportProject : public QDialog
{
    Q_OBJECT

public:
    ImportProject(QWidget *parent = 0);
    ~ImportProject();
    QString LogsString;

//    QString string_FillPits;
//    QString string_FlowGrids;
//    QString string_StreamGrids;
//    QString string_LinkGrids;
//    QString string_CatchmentGrids;
//    QString string_StreamPolyline;
//    QString string_StreamRasterVector;
//    QString string_CatchmentPolygon;
//    QString string_CatchmentRasterVector;
//    QString string_DissolvePolygons;
//    QString string_PolygonToPolylines;
//    QString string_SimplifyPolylines;
//    QString string_PolylineToLines;
//    QString string_MergeVectorLayers;
//    QString string_MergeVectorDomainDecomposition;
//    QString string_ReadTopology;
//    QString string_DelaunayTriangulation;
//    QString string_TINShapeLayer;


private:
    Ui::ImportProject *ui;

private slots:
    void on_pushButtonHelp_clicked();
    void on_pushButtonImport_clicked();
    void on_pushButtonClose_clicked();
    void on_pushButtonProject_clicked();
};

#endif // IMPORTPROJECT_H
