#include "meshspatial.h"
#include "ui_meshspatial.h"

#include "7VisualAnalytics/QCustomPlot/qcustomplot.h"
#include "7VisualAnalytics/QCustomPlotMainWindow/qcustomplotmainwindow.h"

#include "0LibsIO/IOProjectFile.h"
#include "0LibsShape/shapefil.h"
#include "globals.h"



MeshSpatial::MeshSpatial(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MeshSpatial)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshSpatial";

    try {
        ui->setupUi(this);

        // ** Start: Set Defaults
        QFile ProjectFile(user_pihmgis_root_folder+user_pihmgis_project_folder + "/OpenProject.txt");
        if ( ! ProjectFile.open(QIODevice::ReadOnly | QIODevice::Text) )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Open File: </span>")+user_pihmgis_root_folder+user_pihmgis_project_folder + "/OpenProject.txt"+tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
        }
        QTextStream ProjectFileTextStream(&ProjectFile);
        QString ProjectFolder   = ProjectFileTextStream.readLine();
        QString ProjectFileName = ProjectFileTextStream.readLine();
        ProjectFile.close();


        QStringList ModuleStringList;
        QString TempFileName;

        // **
        ModuleStringList = ReadModuleLine(ProjectFileName,tr("PIHMSimulation"));
        if ( ModuleStringList.length() > 0  )
        {
            TempFileName = ModuleStringList.at(4);
            ui->lineEditOutputDataFolder->setText(TempFileName);

            TempFileName = ModuleStringList.at(2);
            ui->lineEditDataKey->setText(TempFileName);

            if ( QFile(ui->lineEditOutputDataFolder->text()+"/"+ui->lineEditDataKey->text()+".para").exists() )
            {
                QFile TempFile(ui->lineEditOutputDataFolder->text()+"/"+ui->lineEditDataKey->text()+".para");
                TempFile.open(QIODevice::ReadOnly | QIODevice::Text);
                QTextStream TempFileTextStream(&TempFile);
                double TempDouble;
                int Start, Stop;
                for (int i=1; i<=45; i++)
                {
                    TempFileTextStream >> TempDouble;
                    //qDebug() << TempDouble << "\t";
                }
                TempFileTextStream >> Start; qDebug() << "Start = " << Start << "\t";
                TempFileTextStream >> Stop;  qDebug() << "Stop  = " << Stop  << "\t";
                if      ( Stop / (60*24*365) >= 1 ) { Start = Start / (60*24*365); Stop = Stop / (60*24*365); ui->comboBoxStartStop->setCurrentIndex(5); }
                else if ( Stop / (60*24*30)  >= 1 ) { Start = Start / (60*24*30);  Stop = Stop / (60*24*30);  ui->comboBoxStartStop->setCurrentIndex(4); }
                else if ( Stop / (60*24*7)   >= 1 ) { Start = Start / (60*24*7);   Stop = Stop / (60*24*7);   ui->comboBoxStartStop->setCurrentIndex(3); }
                else if ( Stop / (60*24*1)   >= 1 ) { Start = Start / (60*24*1);   Stop = Stop / (60*24*1);   ui->comboBoxStartStop->setCurrentIndex(2); }
                else if ( Stop / (60*1*1)    >= 1 ) { Start = Start / (60*1*1);    Stop = Stop / (60*1*1);    ui->comboBoxStartStop->setCurrentIndex(1); }
                else if ( Stop / (1*1*1)     >= 1 ) { Start = Start / (1*1*1);     Stop = Stop / (1*1*1);     ui->comboBoxStartStop->setCurrentIndex(0); }

                ui->spinBoxStartTime->setValue( Start );
                ui->spinBoxStopTime->setValue( Stop );
            }
        }

        ModuleStringList = ReadModuleLine(ProjectFileName,tr("TINShapeLayer"));
        if ( ModuleStringList.length() > 0 )
        {
            TempFileName = ModuleStringList.at(3);
            ui->lineEditMeshShapeFile->setText(TempFileName);
        }
        // ** End: Set Defaults


        // ** Start: Fill Form If Module Has Been Run Previously

        ModuleStringList = ReadModuleLine(ProjectFileName,tr("MeshSpatial"));

        if ( ModuleStringList.length() > 0 )
        {
            ui->lineEditOutputDataFolder->setText(ModuleStringList.at(1));
            ui->lineEditOutputDataFolder->setStyleSheet("color: rgb(0, 180, 0);");

            ui->lineEditDataKey->setText(ModuleStringList.at(2));
            ui->lineEditDataKey->setStyleSheet("color: rgb(0, 180, 0);");

            ui->lineEditMeshShapeFile->setText(ModuleStringList.at(8));
            ui->lineEditMeshShapeFile->setStyleSheet("color: rgb(0, 180, 0);");
        }

        verifyInputOutputFile();
        pushButtonSetFocus();

    } catch (...) {
        qDebug() << "Error: MeshSpatial is returning w/o checking";
    }
}

MeshSpatial::~MeshSpatial()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ~MeshSpatial";

    try {
        delete ui;
    } catch (...) {
        qDebug() << "Error: ~MeshSpatial is returning w/o checking";
    }
}

void MeshSpatial::on_pushButtonOutputDataFolder_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshSpatial::on_pushButtonOutputDataFolder_clicked()";

    try {
        LogsString = tr("");
        LogsString.append(tr("Processing ... <br>"));
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();
        LogsString = tr("");

        QString ProjectFolder, ProjectFileName;
        QFile ProjectFile(user_pihmgis_root_folder+user_pihmgis_project_folder + "/OpenProject.txt");
        if ( ! ProjectFile.open(QIODevice::ReadOnly | QIODevice::Text) )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Open File: </span>")+user_pihmgis_root_folder+user_pihmgis_project_folder + "/OpenProject.txt"+tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
            return;
        }
        QTextStream ProjectFileTextStream(&ProjectFile);
        ProjectFolder   = ProjectFileTextStream.readLine();
        ProjectFileName = ProjectFileTextStream.readLine();
        ProjectFile.close();
        qDebug() << ProjectFolder;

        QString OutputDataFolder = QFileDialog::getExistingDirectory(this, "PIHM Input Data Folder", ProjectFolder+"/5PIHMSimulation", 0);

        if( OutputDataFolder != nullptr )
        {
            ui->lineEditOutputDataFolder->setStyleSheet("color: black;");
            ui->lineEditOutputDataFolder->setText(OutputDataFolder);

            QStringList ModuleStringList;
            QString TempFileName;

            if( ui->lineEditDataKey->text() == nullptr )
            {
                // ** Data Model INPUT File Name
                ModuleStringList = ReadModuleLine(ProjectFileName,tr("TINShapeLayer"));
                if ( ModuleStringList.length() > 0  )
                {
                    TempFileName = ModuleStringList.at(3);
                    TempFileName = TempFileName.right(TempFileName.length()-TempFileName.lastIndexOf("/")-1);

                    TempFileName.replace( QString(".shp"), QString("") );
                    if ( QFile(ui->lineEditOutputDataFolder->text()+"/"+TempFileName+".para").exists() )
                    {
                        ui->lineEditDataKey->setText(TempFileName);
                    }

                }

                ModuleStringList = ReadModuleLine(ProjectFileName,tr("MeshDataFile"));
                if ( ModuleStringList.length() > 0  )
                {
                    TempFileName = ModuleStringList.at(9);
                    if ( QFile(ui->lineEditOutputDataFolder->text()+"/"+TempFileName+".para").exists() )
                    {
                        ui->lineEditDataKey->setText(TempFileName);
                    }
                }
            }
        }

        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

        pushButtonSetFocus();

    } catch (...) {
        qDebug() << "Error: MeshSpatial::on_pushButtonOutputDataFolder_clicked() is returning w/o checking";
    }
}
/*
void MeshSpatial::on_comboBoxModelSegments_currentIndexChanged(int index)
{
    if ( index == 2 || index == 4 )
        ui->lineEditModelSegments->hide();
    else
        ui->lineEditModelSegments->show();
    pushButtonSetFocus();
}*/

void MeshSpatial::on_lineEditOutputDataFolder_textChanged(const QString &arg1)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshSpatial::on_lineEditOutputDataFolder_textChanged()";

    try {
        ui->lineEditOutputDataFolder->setStyleSheet("color: rgb(0, 0, 0);");
        verifyInputOutputFile();
    } catch (...) {
        qDebug() << "Error: MeshSpatial::on_lineEditOutputDataFolder_textChanged() is returning w/o checking";
    }
}

void MeshSpatial::on_lineEditDataKey_textChanged(const QString &arg1)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshSpatial::on_lineEditDataKey_textChanged()";

    try {
        ui->lineEditDataKey->setStyleSheet("color: rgb(0, 0, 0);");
        verifyInputOutputFile();
    } catch (...) {
        qDebug() << "Error: MeshSpatial::on_lineEditDataKey_textChanged() is returning w/o checking";
    }
}

void MeshSpatial::on_lineEditMeshShapeFile_textChanged(const QString &arg1)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshSpatial::on_lineEditMeshShapeFile_textChanged()";

    try {
        ui->lineEditMeshShapeFile->setStyleSheet("color: rgb(0, 0, 0);");
    } catch (...) {
        qDebug() << "Error: MeshSpatial::on_lineEditMeshShapeFile_textChanged() is returning w/o checking";
    }
}

void MeshSpatial::on_comboBoxPlotVariable_currentIndexChanged(int index)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshSpatial::on_comboBoxPlotVariable_currentIndexChanged()";

    try {
        verifyInputOutputFile();
    } catch (...) {
        qDebug() << "Error: MeshSpatial::on_comboBoxPlotVariable_currentIndexChanged() is returning w/o checking";
    }
}

void MeshSpatial::verifyInputOutputFile()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshSpatial::verifyInputOutputFile()";

    try {
        LogsString = tr("");
        if ( ! QDir(ui->lineEditOutputDataFolder->text()).exists() )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Folder Does Not Exist ... </span>")+ui->lineEditOutputDataFolder->text()+tr("<br>"));
        }
        else
        {
            LogsString.append(tr("Output Folder Exists ... ")+ui->lineEditOutputDataFolder->text()+tr("<br>"));

        }


        QString FileName, Extension;

        FileName = ui->lineEditOutputDataFolder->text() + "/" + ui->lineEditDataKey->text();
        Extension = tr(".para");

        if ( ! QFile(FileName + Extension).exists() )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Para File Does Not Exist ... </span>")+ FileName + Extension +tr("<br>"));
        }
        else
        {
            LogsString.append(tr("Para File Exists ... ")+ FileName + Extension +tr("<br>"));

        }

        QStringList Extensions;
        if (ui->comboBoxPlotVariable->currentIndex() ==  0) Extensions << ".surf.dat";  //surface storage
        if (ui->comboBoxPlotVariable->currentIndex() ==  1) Extensions << ".unsat.dat"; //soil moisture storage
        if (ui->comboBoxPlotVariable->currentIndex() ==  2) Extensions << ".gw.dat";    //groundwater storage
        if (ui->comboBoxPlotVariable->currentIndex() ==  3) Extensions << ".is.dat";    //interception strorage
        if (ui->comboBoxPlotVariable->currentIndex() ==  4) Extensions << ".snow.dat";  //snowpack storage
        if (ui->comboBoxPlotVariable->currentIndex() ==  5) Extensions << ".et0.dat";   //evapotranspiration
        if (ui->comboBoxPlotVariable->currentIndex() ==  5) Extensions << ".et1.dat";   //evapotranspiration
        if (ui->comboBoxPlotVariable->currentIndex() ==  5) Extensions << ".et2.dat";   //evapotranspiration
        if (ui->comboBoxPlotVariable->currentIndex() ==  6) Extensions << ".et0.dat";   //interception loss
        if (ui->comboBoxPlotVariable->currentIndex() ==  7) Extensions << ".et1.dat";   //transpiration
        if (ui->comboBoxPlotVariable->currentIndex() ==  8) Extensions << ".et2.dat";   //evaporation
        if (ui->comboBoxPlotVariable->currentIndex() ==  9) Extensions << ".infil.dat"; //infiltration
        if (ui->comboBoxPlotVariable->currentIndex() == 10) Extensions << ".rech.dat";  //recharge

        for( int i=0; i < Extensions.length(); i++)
        {
            if ( ! QFile(FileName + Extensions.at(i)).exists() )
            {
                LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Output File Does Not Exist ... </span>")+ FileName + Extensions.at(i) +tr("<br>"));
            }
            else
            {
                LogsString.append(tr("Output File Exists ... ")+ FileName + Extensions.at(i) +tr("<br>"));
            }
        }

        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();
        //pushButtonSetFocus();
    } catch (...) {
        qDebug() << "Error: MeshSpatial::verifyInputOutputFile() is returning w/o checking";
    }
}

void MeshSpatial::pushButtonSetFocus()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshSpatial::pushButtonSetFocus()";

    try {
        ui->pushButtonOutputDataFolder->setDefault(false);

        if (ui->lineEditOutputDataFolder->text() == nullptr)
        {
            ui->pushButtonOutputDataFolder->setDefault(true);
            ui->pushButtonOutputDataFolder->setFocus();
            return;
        }

        if (ui->lineEditDataKey->text() == nullptr)
        {
            ui->lineEditDataKey->setFocus();
            return;
        }

        ui->pushButtonMeshShapeFile->setDefault(false);
        if (ui->lineEditMeshShapeFile->text() == nullptr)
        {
            ui->pushButtonMeshShapeFile->setDefault(true);
            ui->pushButtonMeshShapeFile->setFocus();
            return;
        }

        ui->pushButtonRun->setDefault(true);
        ui->pushButtonRun->setFocus();

    } catch (...) {
        qDebug() << "Error: MeshSpatial::pushButtonSetFocus() is returning w/o checking";
    }
}

void MeshSpatial::on_comboBoxStartStop_currentIndexChanged(int index)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshSpatial::on_comboBoxStartStop_currentIndexChanged()";

    try {
        QString ProjectFolder, ProjectFileName;
        QFile ProjectFile(user_pihmgis_root_folder+user_pihmgis_project_folder + "/OpenProject.txt");
        if ( ! ProjectFile.open(QIODevice::ReadOnly | QIODevice::Text) )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Open File: </span>")+user_pihmgis_root_folder+user_pihmgis_project_folder + "/OpenProject.txt"+tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
            return;
        }
        QTextStream ProjectFileTextStream(&ProjectFile);
        ProjectFolder   = ProjectFileTextStream.readLine();
        ProjectFileName = ProjectFileTextStream.readLine();
        ProjectFile.close();

        QStringList ModuleStringList;

        ModuleStringList = ReadModuleLine(ProjectFileName,tr("PIHMSimulation"));
        if ( ModuleStringList.length() > 0  )
        {
            if ( QFile(ui->lineEditOutputDataFolder->text()+"/"+ui->lineEditDataKey->text()+".para").exists() )
            {
                QFile TempFile(ui->lineEditOutputDataFolder->text()+"/"+ui->lineEditDataKey->text()+".para");
                TempFile.open(QIODevice::ReadOnly | QIODevice::Text);
                QTextStream TempFileTextStream(&TempFile);
                double TempDouble;
                int Start, Stop;
                for (int i=1; i<=45; i++)
                {
                    TempFileTextStream >> TempDouble;
                    //qDebug() << TempDouble << "\t";
                }
                TempFileTextStream >> Start; qDebug() << "Start = " << Start << "\t";
                TempFileTextStream >> Stop;  qDebug() << "Stop  = " << Stop  << "\t";
                if ( index == 5 ) { Start = Start / (60*24*365); Stop = Stop / (60*24*365); }
                if ( index == 4 ) { Start = Start / (60*24*30);  Stop = Stop / (60*24*30);  }
                if ( index == 3 ) { Start = Start / (60*24*7);   Stop = Stop / (60*24*7);   }
                if ( index == 2 ) { Start = Start / (60*24*1);   Stop = Stop / (60*24*1);   }
                if ( index == 1 ) { Start = Start / (60*1*1);    Stop = Stop / (60*1*1);    }
                if ( index == 0 ) { Start = Start / (1*1*1);     Stop = Stop / (1*1*1);     }

                ui->spinBoxStartTime->setValue( Start );
                ui->spinBoxStopTime->setValue( Stop );
            }
        }
    } catch (...) {
        qDebug() << "Error: MeshSpatial::on_comboBoxStartStop_currentIndexChanged() is returning w/o checking";
    }
}

void MeshSpatial::on_pushButtonMeshShapeFile_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshSpatial::on_pushButtonMeshShapeFile_clicked()";

    try {

        LogsString = tr("");
        LogsString.append(tr("Processing ... <br>"));
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();
        LogsString = tr("");

        QString ProjectFolder, ProjectFileName;
        QFile ProjectFile(user_pihmgis_root_folder+user_pihmgis_project_folder + "/OpenProject.txt");
        if ( ! ProjectFile.open(QIODevice::ReadOnly | QIODevice::Text) )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Open File: </span>")+user_pihmgis_root_folder+user_pihmgis_project_folder + "/OpenProject.txt"+tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
            return;
        }

        QTextStream ProjectFileTextStream(&ProjectFile);
        ProjectFolder   = ProjectFileTextStream.readLine();
        ProjectFileName = ProjectFileTextStream.readLine();
        ProjectFile.close();
        qDebug() << ProjectFolder;

        QString MeshShapeFile = QFileDialog::getOpenFileName(this, "Mesh Shape File", ProjectFolder+"/3DomainDecomposition", "Mesh Shape File(*.shp)");

        if( MeshShapeFile != nullptr )
        {
            ui->lineEditMeshShapeFile->setStyleSheet("color: black;");
            ui->lineEditMeshShapeFile->setText(MeshShapeFile);
        }

        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

        pushButtonSetFocus();

    } catch (...) {
        qDebug() << "Error: MeshSpatial::on_pushButtonMeshShapeFile_clicked() is returning w/o checking";
    }
}

void MeshSpatial::on_pushButtonRun_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshSpatial::on_pushButtonRun_clicked()";

    try {
        LogsString = tr("");
        LogsString.append(tr("Mesh Spatial Analysis Processing Started ... <br>"));
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

        QString ProjectFolder, ProjectFileName;
        QFile ProjectFile(user_pihmgis_root_folder+user_pihmgis_project_folder + "/OpenProject.txt");
        ProjectFile.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream ProjectFileTextStream(&ProjectFile);
        ProjectFolder   = ProjectFileTextStream.readLine();
        ProjectFileName = ProjectFileTextStream.readLine();
        ProjectFile.close();


        LogsString.append(tr("Verifying Data Files ... <br>"));
        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

        int runFlag = 1;

        QStringList Extensions;
        if (ui->comboBoxPlotVariable->currentIndex() ==  0) Extensions << ".surf.dat";  //surface storage
        if (ui->comboBoxPlotVariable->currentIndex() ==  1) Extensions << ".unsat.dat"; //soil moisture storage
        if (ui->comboBoxPlotVariable->currentIndex() ==  2) Extensions << ".gw.dat";    //groundwater storage
        if (ui->comboBoxPlotVariable->currentIndex() ==  3) Extensions << ".is.dat";    //interception strorage
        if (ui->comboBoxPlotVariable->currentIndex() ==  4) Extensions << ".snow.dat";  //snowpack storage
        if (ui->comboBoxPlotVariable->currentIndex() ==  5) Extensions << ".et0.dat";   //evapotranspiration
        if (ui->comboBoxPlotVariable->currentIndex() ==  5) Extensions << ".et1.dat";   //evapotranspiration
        if (ui->comboBoxPlotVariable->currentIndex() ==  5) Extensions << ".et2.dat";   //evapotranspiration
        if (ui->comboBoxPlotVariable->currentIndex() ==  6) Extensions << ".et0.dat";   //interception loss
        if (ui->comboBoxPlotVariable->currentIndex() ==  7) Extensions << ".et1.dat";   //transpiration
        if (ui->comboBoxPlotVariable->currentIndex() ==  8) Extensions << ".et2.dat";   //evaporation
        if (ui->comboBoxPlotVariable->currentIndex() ==  9) Extensions << ".infil.dat"; //infiltration
        if (ui->comboBoxPlotVariable->currentIndex() == 10) Extensions << ".rech.dat";  //recharge

        QString PlotParameter;
        if (ui->comboBoxPlotVariable->currentIndex() ==  0) PlotParameter = "surf";
        if (ui->comboBoxPlotVariable->currentIndex() ==  1) PlotParameter = "unsat";
        if (ui->comboBoxPlotVariable->currentIndex() ==  2) PlotParameter = "gw";
        if (ui->comboBoxPlotVariable->currentIndex() ==  3) PlotParameter = "is";
        if (ui->comboBoxPlotVariable->currentIndex() ==  4) PlotParameter = "snow";
        if (ui->comboBoxPlotVariable->currentIndex() ==  5) PlotParameter = "etx";
        if (ui->comboBoxPlotVariable->currentIndex() ==  6) PlotParameter = "et0";
        if (ui->comboBoxPlotVariable->currentIndex() ==  7) PlotParameter = "et1";
        if (ui->comboBoxPlotVariable->currentIndex() ==  8) PlotParameter = "et2";
        if (ui->comboBoxPlotVariable->currentIndex() ==  9) PlotParameter = "infil";
        if (ui->comboBoxPlotVariable->currentIndex() == 10) PlotParameter = "rech";
        /*if (ui->comboBoxPlotVariable->currentIndex() ==  0) PlotParameter = "Surface Storage"; //outflow
    if (ui->comboBoxPlotVariable->currentIndex() ==  1) PlotParameter = "Soil Moisture Storage"; //inflow
    if (ui->comboBoxPlotVariable->currentIndex() ==  2) PlotParameter = "Groundwater Storage";    //storage
    if (ui->comboBoxPlotVariable->currentIndex() ==  3) PlotParameter = "Interception Storage"; //surfaceflow
    if (ui->comboBoxPlotVariable->currentIndex() ==  4) PlotParameter = "Snowpack Storage"; //baseflow
    if (ui->comboBoxPlotVariable->currentIndex() ==  5) PlotParameter = "Evapotranspiration"; //surfaceflow left
    if (ui->comboBoxPlotVariable->currentIndex() ==  6) PlotParameter = "Interception Loss"; //surfaceflow right
    if (ui->comboBoxPlotVariable->currentIndex() ==  7) PlotParameter = "Transpiration"; //baseflow left
    if (ui->comboBoxPlotVariable->currentIndex() ==  8) PlotParameter = "Evaporation from Ground"; //baseflow right
    if (ui->comboBoxPlotVariable->currentIndex() ==  9) PlotParameter = "Infiltration"; //seepage bed
    if (ui->comboBoxPlotVariable->currentIndex() == 10) PlotParameter = "Recharge"; //bed outflow*/


        QString OutputFileName;
        int NUMELEMENTS, NUMRIVERS;
        int STARTTIME, STOPTIME;
        int SKIPTIMESTEPS;
        int TIMESTEP;
        int NTIMESTEPS;
        int NBREAKS, BREAKSTEPS;


        NTIMESTEPS = 999999999;
        if( ui->lineEditOutputDataFolder->text() == nullptr || ui->lineEditDataKey->text() == nullptr )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Input Folder and/or Data Key Input(s) Missing </span>")+tr("<br>"));
            runFlag = 0;
        }
        else if( ui->spinBoxStopTime->value() - ui->spinBoxStartTime->value() <= 0 )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Inconsitent Start - Stop Time </span>")+tr("<br>"));
            runFlag = 0;
        }
        else
        {
            OutputFileName = ui->lineEditOutputDataFolder->text() + "/" + ui->lineEditDataKey->text();

            if ( ! CheckFileAccess(OutputFileName+".mesh", "ReadOnly") )
            {
                LogsString.append(tr("<span style=\"color:#FF0000\">Error: No Read Access to ... </span>")+OutputFileName+".mesh"+tr("<br>"));
                runFlag = 0;
            }
            LogsString.append(OutputFileName+".mesh" + " ... <br>");

            if ( ! CheckFileAccess(OutputFileName+".riv", "ReadOnly") )
            {
                LogsString.append(tr("<span style=\"color:#FF0000\">Error: No Read Access to ... </span>")+OutputFileName+".riv"+tr("<br>"));
                runFlag = 0;
            }
            LogsString.append(OutputFileName+".riv" + " ... <br>");

            for (int i=0; i<Extensions.length(); i++)
            {
                if ( ! CheckFileAccess(OutputFileName+Extensions.at(i), "ReadOnly") )
                {
                    LogsString.append(tr("<span style=\"color:#FF0000\">Error: No Read Access to ... </span>")+OutputFileName+Extensions.at(i)+tr("<br>"));
                    runFlag = 0;
                }
                LogsString.append(OutputFileName+Extensions.at(i) + " ... <br>");
            }

            if ( ! CheckFileAccess(ui->lineEditMeshShapeFile->text(), "ReadOnly") )
            {
                LogsString.append(tr("<span style=\"color:#FF0000\">Error: No Read Access to ... </span>")+ui->lineEditMeshShapeFile->text()+tr("<br>"));
                runFlag = 0;
            }
            LogsString.append(ui->lineEditMeshShapeFile->text() + " ... <br>");

            QFile TempFile;
            QTextStream TempFileTextStream;

            TempFile.setFileName(OutputFileName+".mesh");
            TempFile.open(QIODevice::ReadOnly | QIODevice::Text);
            TempFileTextStream.setDevice(&TempFile);
            TempFileTextStream >> NUMELEMENTS;
            TempFile.close();
            LogsString.append(tr("Number of Elements = ")+QString::number(NUMELEMENTS)+tr("<br>"));
            if ( NUMELEMENTS < 1 )
            {
                LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Number of Elements Less Than One... </span>")+QString::number(NUMELEMENTS)+tr("<br>"));
                runFlag = 0;
            }

            TempFile.setFileName(OutputFileName+".riv");
            TempFile.open(QIODevice::ReadOnly | QIODevice::Text);
            TempFileTextStream.setDevice(&TempFile);
            TempFileTextStream >> NUMRIVERS;
            TempFile.close();
            LogsString.append(tr("Number of River Segments = ")+QString::number(NUMRIVERS)+tr("<br>"));
            if ( NUMRIVERS < 1 )
            {
                LogsString.append(tr("<span style=\"color:#FF0000\">WARNING: Number of River Segments Less Than One... </span>")+QString::number(NUMRIVERS)+tr("<br>"));
                //runFlag = 0;
            }

            int TIMESTEP1, TIMESTEP2;
            double TempDouble;
            QString TempQString;
            TempFile.setFileName(OutputFileName+Extensions.at(0));
            TempFile.open(QIODevice::ReadOnly | QIODevice::Text);
            TempFileTextStream.setDevice(&TempFile);

            TempFileTextStream >> TIMESTEP1;
            qDebug() << "Time Step1 = " << TIMESTEP1 << "\n";
            for (int i=0; i<NUMELEMENTS+1; i++)
            {
                TempFileTextStream >> TempDouble;
                qDebug() << TempDouble << ", ";
            }
            TempFileTextStream >> TIMESTEP2;
            qDebug() << "\nTime Step2 = " << TIMESTEP2 << "\n";
            TempFile.close();

            TIMESTEP = TIMESTEP2 - TIMESTEP1;
            qDebug() << "Time Step = " << TIMESTEP << "\n";

            int timeunitfactor;
            if ( ui->comboBoxStartStop->currentIndex() == 0 ) timeunitfactor = 1;
            if ( ui->comboBoxStartStop->currentIndex() == 1 ) timeunitfactor = 60;
            if ( ui->comboBoxStartStop->currentIndex() == 2 ) timeunitfactor = 60*24;
            if ( ui->comboBoxStartStop->currentIndex() == 3 ) timeunitfactor = 60*24*7;
            if ( ui->comboBoxStartStop->currentIndex() == 4 ) timeunitfactor = 60*24*30;
            if ( ui->comboBoxStartStop->currentIndex() == 5 ) timeunitfactor = 60*24*365;

            STARTTIME = ui->spinBoxStartTime->value() * timeunitfactor;
            STOPTIME  = ui->spinBoxStopTime->value()  * timeunitfactor;

            qDebug() << "Start Time = " << STARTTIME << "\n";
            qDebug() << "Stop Time  = " << STOPTIME  << "\n";

            SKIPTIMESTEPS = ( STARTTIME + TIMESTEP - TIMESTEP1 ) / TIMESTEP;
            NTIMESTEPS    = ( STOPTIME  - STARTTIME ) / TIMESTEP;
            NBREAKS       = ui->spinBoxNumBreaks->value();
            BREAKSTEPS    = NTIMESTEPS / NBREAKS;

            qDebug() << "SKIP TIME STEPS = " << SKIPTIMESTEPS << "\n";
            qDebug() << "N TIME STEPS    = " << NTIMESTEPS << "\n";
            qDebug() << "BREAKSTEPS      = " << BREAKSTEPS << "\n";

            if ( BREAKSTEPS < 1 )
            {
                LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: SKIP TIME STEPS = ")+QString::number(SKIPTIMESTEPS)+tr(" N TIME STEPS = ")+QString::number(NTIMESTEPS)+tr(" NBREAKS = ")+QString::number(BREAKSTEPS)+tr("</span>")+tr("<br>"));
                runFlag = 0;
            }
        }

        if ( QFile(ProjectFolder+"/6VisualAnalytics/Spatial_"+PlotParameter+".shp").exists() )
            if ( ! QFile::remove(ProjectFolder+"/6VisualAnalytics/Spatial_"+PlotParameter+".shp") )
            {
                LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to delete file... </span>")+ProjectFolder+"/6VisualAnalytics/Spatial_"+PlotParameter+".shp"+tr("<br>"));
                runFlag = 0;
            }
        if ( QFile(ProjectFolder+"/6VisualAnalytics/Spatial_"+PlotParameter+".shx").exists() )
            if ( ! QFile::remove(ProjectFolder+"/6VisualAnalytics/Spatial_"+PlotParameter+".shx") )
            {
                LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to delete file... </span>")+ProjectFolder+"/6VisualAnalytics/Spatial_"+PlotParameter+".shx"+tr("<br>"));
                runFlag = 0;
            }
        if ( QFile(ProjectFolder+"/6VisualAnalytics/Spatial_"+PlotParameter+".dbf").exists() )
            if ( ! QFile::remove(ProjectFolder+"/6VisualAnalytics/Spatial_"+PlotParameter+".dbf") )
            {
                LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to delete file... </span>")+ProjectFolder+"/6VisualAnalytics/Spatial_"+PlotParameter+".dbf"+tr("<br>"));
                runFlag = 0;
            }

        ui->textBrowserLogs->setHtml(LogsString);
        ui->textBrowserLogs->repaint();

        if (runFlag == 1)
        {
            ui->pushButtonRun->setText("Running");

            QVector<QString> Legends(NBREAKS);
            QVector<QVector<double>> datax(NBREAKS), datay(NBREAKS);
            for (int j=0; j<NBREAKS; j++)
            {
                datax[j].resize(NUMELEMENTS);
                datay[j].resize(NUMELEMENTS);
            }

            QString TempString;
            if(NBREAKS > 1)
                for (int i=0; i<NBREAKS; i++)
                    Legends[i] = PlotParameter + TempString.sprintf("_%03d",i+1);
            else
                Legends[0] = PlotParameter;


            //** READ DATA
            QFile DataFile;
            QTextStream DataFileTextStream;
            QString DataString;
            QStringList Data;
            for (int i=0; i<Extensions.length(); i++)
            {
                DataFile.setFileName(OutputFileName+Extensions.at(i));
                DataFile.open(QIODevice::ReadOnly | QIODevice::Text);
                DataFileTextStream.setDevice(&DataFile);
                int nline  = 1;
                int nbreak = 1;
                while ( nline <= SKIPTIMESTEPS )
                {
                    if( DataFileTextStream.atEnd() )
                    {
                        LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Reached End of File... </span>")+OutputFileName+Extensions.at(i)+tr("<br>"));
                        ui->textBrowserLogs->setHtml(LogsString);
                        ui->textBrowserLogs->repaint();
                        ui->pushButtonRun->setText("Run");
                        return;
                    }
                    DataString = DataFileTextStream.readLine();
                    qDebug() << "A Line Number = " << nline << "\n";
                    nline ++;
                }
                while ( nline <= SKIPTIMESTEPS+NTIMESTEPS )
                {
                    if( DataFileTextStream.atEnd() )
                    {
                        LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Reached End of File... </span>")+OutputFileName+Extensions.at(i)+tr("<br>"));
                        ui->textBrowserLogs->setHtml(LogsString);
                        ui->textBrowserLogs->repaint();
                        ui->pushButtonRun->setText("Run");
                        return;
                    }
                    DataString = DataFileTextStream.readLine();
                    if ( nline > SKIPTIMESTEPS + nbreak*BREAKSTEPS ) nbreak++;
                    qDebug() << "B Line Number = " << nline << "\n";
                    nline++;

                    Data = DataString.split(QRegExp("\\s+"),QString::SkipEmptyParts);
                    for (int j=0; j<NUMELEMENTS; j++)
                    {
                        datax[nbreak-1][j] = Data.at(0).toDouble();
                        datay[nbreak-1][j] = datay[nbreak-1][j] + Data.at(j+1).toDouble()/BREAKSTEPS;
                        qDebug() << i << "," << j << "," << nbreak << "," << datax[nbreak-1][j] << "," << datay[nbreak-1][j] << "\n";
                    }
                }
                DataFile.close();
            }

            /*for (int i=0; i<NUMELEMENTS; i++)
        {
            for (int j=0; j<NBREAKS; j++)
            {
                qDebug() << datay[j][i] << "\t";
            }
            qDebug() << "\n";
        }*/



            TempString = ui->lineEditMeshShapeFile->text();
            TempString.replace(".shp",".shp");
            QFile::copy(TempString,ProjectFolder+"/6VisualAnalytics/spatial_"+PlotParameter+".shp");
            TempString.replace(".shp",".shx");
            QFile::copy(TempString,ProjectFolder+"/6VisualAnalytics/spatial_"+PlotParameter+".shx");
            //TempString.replace(".shx",".dbf");
            //QFile::copy(TempString,ProjectFolder+"/6VisualAnalytics/spatial_"+PlotParameter+".dbf");

            QString dbfFileName = ProjectFolder+"/6VisualAnalytics/spatial_"+PlotParameter+".dbf";
            DBFHandle DBF;
            DBF = DBFCreate((char *)qPrintable(dbfFileName));
            //DBF = DBFOpen((char *)qPrintable(dbfFileName), "rb+");
            if ( DBF == nullptr )
            {
                LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable To Open DBF File... </span>")+dbfFileName+tr("<br>"));
                ui->textBrowserLogs->setHtml(LogsString);
                ui->textBrowserLogs->repaint();
                ui->pushButtonRun->setText("Run");
                return;
            }

            int tempInt;
            char fieldName[11];
            QVector<int> fields(NBREAKS+1);
            fields[0] = DBFAddField(DBF, "Ele", FTInteger, 9, 0);
            if ( fields[0] == -1 )
            {
                LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable To Add New Attribute Ele To DBF File... </span>")+dbfFileName+tr("<br>"));
                ui->textBrowserLogs->setHtml(LogsString);
                ui->textBrowserLogs->repaint();
                ui->pushButtonRun->setText("Run");
                return;
            }
            for (int i=0; i<NBREAKS; i++)
            {
                //qDebug() << Legends[i];
                sprintf(fieldName,"%s",qPrintable(Legends[i]));
                qDebug() << Legends[i] << fieldName;
                //fields[i+1] = DBFAddField(DBF, "Ele", FTInteger, 9, 0);
                fields[i+1] = DBFAddField(DBF, fieldName, FTDouble, 16, 8);
                if ( fields[i+1] == -1 )
                {
                    LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable To Add New Attribute To DBF File... </span>")+dbfFileName+tr("<br>"));
                    ui->textBrowserLogs->setHtml(LogsString);
                    ui->textBrowserLogs->repaint();
                    ui->pushButtonRun->setText("Run");
                    return;
                }
                else
                {
                    LogsString.append(tr("Added New Attribute #")+QString::number(fields[i+1])+ tr(" ")+Legends[i]+tr(" To DBF File... </span>")+dbfFileName+tr("<br>"));
                    ui->textBrowserLogs->setHtml(LogsString);
                    ui->textBrowserLogs->repaint();
                }
            }

            for(int j=0; j<NUMELEMENTS; j++)
            {
                tempInt = DBFWriteIntegerAttribute(DBF, j, fields[0], j+1);
                if ( tempInt == 0 )
                {
                    LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable To Write Attribute To DBF File... </span>")+dbfFileName+tr("<br>"));
                    ui->textBrowserLogs->setHtml(LogsString);
                    ui->textBrowserLogs->repaint();
                    return;
                }
            }

            for (int i=0; i<NBREAKS; i++)
            {
                //out<<"Field Ele_ID with Field number: "<<temp<<" added to .dbf file\n";
                for(int j=0; j<NUMELEMENTS; j++)
                {
                    tempInt = DBFWriteDoubleAttribute(DBF, j, fields[i+1], datay[i][j]);
                    if ( tempInt == 0 )
                    {
                        LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable To Write Attribute To DBF File... </span>")+dbfFileName+tr("<br>"));
                        ui->textBrowserLogs->setHtml(LogsString);
                        ui->textBrowserLogs->repaint();
                        return;
                    }
                }
            }
            DBFClose(DBF);


            dbfFileName.replace(".dbf",".shp");
            if ( ! QDesktopServices::openUrl(QUrl("file://"+dbfFileName)) )
                LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Load SHP File in GIS ... </span>")+dbfFileName+tr("<br>"));

            ProjectIOStringList << "MeshSpatial" << ui->lineEditOutputDataFolder->text() << ui->lineEditDataKey->text();
            ProjectIOStringList << QString::number(ui->comboBoxPlotVariable->currentIndex());
            ProjectIOStringList << QString::number(ui->spinBoxStartTime->value()) << QString::number(ui->spinBoxStopTime->value()) << QString::number(ui->comboBoxStartStop->currentIndex()) << QString::number(ui->spinBoxNumBreaks->value());
            ProjectIOStringList << ui->lineEditMeshShapeFile->text();
            ProjectIOStringList << dbfFileName;
            WriteModuleLine(ProjectFileName, ProjectIOStringList);
            ProjectIOStringList.clear();

            LogsString.append(tr("<br><b>Mesh Spatial Analysis Processing Completed.</b>")+tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();

            ui->pushButtonRun->setText("Run");

            //pushButtonSetFocus();
            ui->pushButtonRun->setDefault(false);
            ui->pushButtonClose->setDefault(true);
            ui->pushButtonClose->setFocus();
        }

    } catch (...) {
        qDebug() << "Error: MeshSpatial::on_pushButtonMeshShapeFile_clicked() is returning w/o checking";
    }
}

void MeshSpatial::on_pushButtonClose_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshSpatial::on_pushButtonClose_clicked()";

    try {
        close();
    } catch (...) {
        qDebug() << "Error: MeshSpatial::on_pushButtonClose_clicked() is returning w/o checking";
    }
}

void MeshSpatial::on_pushButtonHelp_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start MeshSpatial::on_pushButtonHelp_clicked()";

    try {
//        LogsString = tr("");
//        if ( ! QDesktopServices::openUrl(QUrl("http://cataract.cee.psu.edu/PIHM/index.php/PIHMgis_3.0#Spatial_Analysis:_Mesh_Elements")) )
//            LogsString.append(tr("<span style=\"color:#FF0000\">ERROR: Unable to Load HTTP Link ... </span>")+tr("<br>"));
//        ui->textBrowserLogs->setHtml(LogsString);
//        ui->textBrowserLogs->repaint();
    } catch (...) {
        qDebug() << "Error: MeshSpatial::on_pushButtonHelp_clicked() is returning w/o checking";
    }
}
