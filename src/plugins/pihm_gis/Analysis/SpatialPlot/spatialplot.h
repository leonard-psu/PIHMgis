#ifndef SPATIAL_PLOT
#define SPATIAL_PLOT

#include "ui_spatialplot.h"
//??#include <qgisapp.h>

class spatialPlotDlg : public QDialog, private Ui::spatialPlotDialog
{
	Q_OBJECT

public:
	spatialPlotDlg(QDialog *parent = 0);

//??	void setApplicationPointer(QgisApp *);
//??	QgisApp* applicationPointer;

public slots:
	void browseEleShapeFile();
	void browseRivShapeFile();
	void browseModelFile();
	void generate();
	void help();
};

#endif
