#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>

#include <gdal.h>
#include <gdal_priv.h>

#include "./0LibsShape/shapefil.h"
#include "./0LibsOther/raster_grid_value.h"
#include "globals.h"


#define _GDAL_PRECIPITATION     if ( ! PrecipitationFlag )
#define _GDAL_TEMPERATURE       if ( ! TemperatureFlag )
#define _GDAL_RELATIVEHUMIDITY  if ( ! RelativeHumidityFlag )
#define _GDAL_WINDVELOCITY      if ( ! WindVelocityFlag )
#define _GDAL_SOLARRADIATION    if ( ! SolarRadiationFlag )
#define _GDAL_VAPORPRESSURE     if ( ! VaporPressureFlag )

#define _GDAL_SOILCLASSES       if ( ! SoilClassesFlag )
#define _GDAL_GEOLOGYCLASSES    if ( ! GeologyClassesFlag )
#define _GDAL_MACROPORES        if ( ! MacroporesFlag )
#define _GDAL_LANDCOVERCLASSES  if ( ! LandCoverClassesFlag )
#define _GDAL_MELTREGIONS       if ( ! MeltRegionsFlag )
#define _GDAL_SOURCESSINKS      if ( ! SourcesSinksFlag )

#define _GDAL_INTERCEPTION      if ( ! InterceptionFlag )
#define _GDAL_SNOWCOVER         if ( ! SnowCoverFileFlag )
#define _GDAL_SURFACESTORAGE    if ( ! SurfaceStorageFlag )
#define _GDAL_SOILMOISTURE      if ( ! SoilMoistureFlag )
#define _GDAL_GROUNDWATER       if ( ! GroundwaterFlag )
#define _GDAL_BOUNDARYCONDITION if ( ! BoundaryConditionFlag )

// _GDAL_PRECIPITATION _GDAL_TEMPERATURE _GDAL_RELATIVEHUMIDITY _GDAL_WINDVELOCITY _GDAL_SOLARRADIATION _GDAL_VAPORPRESSURE
// _GDAL_SOILCLASSES _GDAL_GEOLOGYCLASSES _GDAL_MACROPORES _GDAL_LANDCOVERCLASSES _GDAL_MELTREGIONS _GDAL_SOURCESSINKS
// _GDAL_INTERCEPTION _GDAL_SNOWCOVER _GDAL_SURFACESTORAGE _GDAL_SOILMOISTURE _GDAL_GROUNDWATER _GDAL_BOUNDARYCONDITION

// User interface to PIHMgis v3.5
extern PIHMgisDialog *main_window;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Important function to Assign Attributes to PIHM TIN Triangles
// This function has not been tested rigously.
// Known issues include the following:
// (1) GDAL versions behaviour slightly differently.
// (2) No extent checking (For example, do they all overlap?)
// (3) No checking of values. Are they reasonable?
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int att_data_file(
        QString PrecipitationFileName, bool PrecipitationFlag, QString TemperatureFileName,    bool TemperatureFlag,    QString RelativeHumidityFileName, bool RelativeHumidityFlag, QString WindVelocityFileName,     bool WindVelocityFlag,     QString SolarRadiationFileName, bool SolarRadiationFlag, QString VaporPressureFileName,     bool VaporPressureFlag,
        QString SoilClassesFileName,   bool SoilClassesFlag,   QString GeologyClassesFileName, bool GeologyClassesFlag, QString MacroporesFileName,       bool MacroporesFlag,       QString LandCoverClassesFileName, bool LandCoverClassesFlag, QString MeltRegionsFileName,    bool MeltRegionsFlag,    QString SourcesSinksFileName,      bool SourcesSinksFlag,
        QString InterceptionFileName,  bool InterceptionFlag,  QString SnowCoverFileFileName,  bool SnowCoverFileFlag,  QString SurfaceStorageFileName,   bool SurfaceStorageFlag,   QString SoilMoistureFileName,     bool SoilMoistureFlag,     QString GroundwaterFileName,    bool GroundwaterFlag,    QString BoundaryConditionFileName, bool BoundaryConditionFlag,
        QString TINShapeLayerFileName, QString AttDataFileName
        )
{

    if(print_debug_messages)
        qDebug() << "INFO: Start att_data_file";

    try {

        QString TINShpFileName, TINDbfFileName;

        TINShpFileName = TINShapeLayerFileName;
        TINDbfFileName = TINShapeLayerFileName;
        TINDbfFileName = TINDbfFileName.replace( QString(".shp"), QString(".dbf") );

        SHPHandle _ShpHandle = SHPOpen(qPrintable(TINShpFileName), "rb");
        if(_ShpHandle == nullptr)
        {
            main_window->Log_Message("[att_data_file] Error[-1000] TINShpFileName is NULL. ");
            return -1000;
        }

        DBFHandle _DbfHandle = DBFOpen(qPrintable(TINDbfFileName), "rb");
        if(_DbfHandle == nullptr)
        {
            main_window->Log_Message("[att_data_file] Error[-1001] TINDbfFileName is NULL. ");
            return -1001;
        }

        int recordCount = DBFGetRecordCount( _DbfHandle );

        if ( recordCount < 1 )
        {
            main_window->Log_Message("[att_data_file] Error[-1002] recordCount < 1 ");
            return -1002;
        }

        if ( recordCount > 500000 ) //500000 is a guess
        {
            main_window->Log_Message("[att_data_file] Error[-1003] recordCount > 500000 ");
            return -1003;
        }

        QFile AttDataFile(AttDataFileName);
        if ( ! AttDataFile.open(QIODevice::WriteOnly | QIODevice::Text) )
        {
            main_window->Log_Message("[att_data_file] Error[-1004] failed to open AttDataFile ");
            return -1004;
        }

        QTextStream AttDataFileTextStream(&AttDataFile);

        GDALDataset *GDALPrecipitation, *GDALTemperature,    *GDALRelativeHumidity, *GDALWindVelocity,     *GDALSolarRadiation, *GDALVaporPressure;
        GDALDataset *GDALSoilClasses,   *GDALGeologyClasses, *GDALMacropores,       *GDALLandCoverClasses, *GDALMeltRegions,    *GDALSourcesSinks;
        GDALDataset *GDALInterception,  *GDALSnowCover,      *GDALSurfaceStorage,   *GDALSoilMoisture,     *GDALGroundwater,    *GDALBoundaryCondition;

        double PrecipitationRanges[6], TemperatureRanges[6],    RelativeHumidityRanges[6], WindVelocityRanges[6],     SolarRadiationRanges[6], VaporPressureRanges[6];
        double SoilClassesRanges[6],   GeologyClassesRanges[6], MacroporesRanges[6],       LandCoverClassesRanges[6], MeltRegionsRanges[6],    SourcesSinksRanges[6];
        double InterceptionRanges[6],  SnowCoverRanges[6],      SurfaceStorageRanges[6],   SoilMoistureRanges[6],     GroundwaterRanges[6],    BoundaryConditionRanges[6];


        GDALAllRegister();

        _GDAL_PRECIPITATION     GDALPrecipitation     = (GDALDataset *)GDALOpen(qPrintable(PrecipitationFileName), GA_ReadOnly);
        _GDAL_TEMPERATURE       GDALTemperature       = (GDALDataset *)GDALOpen(qPrintable(TemperatureFileName), GA_ReadOnly);
        _GDAL_RELATIVEHUMIDITY  GDALRelativeHumidity  = (GDALDataset *)GDALOpen(qPrintable(RelativeHumidityFileName), GA_ReadOnly);
        _GDAL_WINDVELOCITY      GDALWindVelocity      = (GDALDataset *)GDALOpen(qPrintable(WindVelocityFileName), GA_ReadOnly);
        _GDAL_SOLARRADIATION    GDALSolarRadiation    = (GDALDataset *)GDALOpen(qPrintable(SolarRadiationFileName), GA_ReadOnly);
        _GDAL_VAPORPRESSURE     GDALVaporPressure     = (GDALDataset *)GDALOpen(qPrintable(VaporPressureFileName), GA_ReadOnly);

        _GDAL_SOILCLASSES       GDALSoilClasses       = (GDALDataset *)GDALOpen(qPrintable(SoilClassesFileName), GA_ReadOnly);
        _GDAL_GEOLOGYCLASSES    GDALGeologyClasses    = (GDALDataset *)GDALOpen(qPrintable(GeologyClassesFileName), GA_ReadOnly);
        _GDAL_MACROPORES        GDALMacropores        = (GDALDataset *)GDALOpen(qPrintable(MacroporesFileName), GA_ReadOnly);
        _GDAL_LANDCOVERCLASSES  GDALLandCoverClasses  = (GDALDataset *)GDALOpen(qPrintable(LandCoverClassesFileName), GA_ReadOnly);
        _GDAL_MELTREGIONS       GDALMeltRegions       = (GDALDataset *)GDALOpen(qPrintable(MeltRegionsFileName), GA_ReadOnly);
        _GDAL_SOURCESSINKS      GDALSourcesSinks      = (GDALDataset *)GDALOpen(qPrintable(SourcesSinksFileName), GA_ReadOnly);

        _GDAL_INTERCEPTION      GDALInterception      = (GDALDataset *)GDALOpen(qPrintable(InterceptionFileName), GA_ReadOnly);
        _GDAL_SNOWCOVER         GDALSnowCover         = (GDALDataset *)GDALOpen(qPrintable(SnowCoverFileFileName), GA_ReadOnly);
        _GDAL_SURFACESTORAGE    GDALSurfaceStorage    = (GDALDataset *)GDALOpen(qPrintable(SurfaceStorageFileName), GA_ReadOnly);
        _GDAL_SOILMOISTURE      GDALSoilMoisture      = (GDALDataset *)GDALOpen(qPrintable(SoilMoistureFileName), GA_ReadOnly);
        _GDAL_GROUNDWATER       GDALGroundwater       = (GDALDataset *)GDALOpen(qPrintable(GroundwaterFileName), GA_ReadOnly);
        _GDAL_BOUNDARYCONDITION GDALBoundaryCondition = (GDALDataset *)GDALOpen(qPrintable(BoundaryConditionFileName), GA_ReadOnly);

        _GDAL_PRECIPITATION         if ( GDALPrecipitation     == nullptr ) return 75;
        _GDAL_TEMPERATURE           if ( GDALTemperature       == nullptr ) return 76;
        _GDAL_RELATIVEHUMIDITY      if ( GDALRelativeHumidity  == nullptr ) return 77;
        _GDAL_WINDVELOCITY          if ( GDALWindVelocity      == nullptr ) return 78;
        _GDAL_SOLARRADIATION        if ( GDALSolarRadiation    == nullptr ) return 79;
        _GDAL_VAPORPRESSURE         if ( GDALVaporPressure     == nullptr ) return 80;

        _GDAL_SOILCLASSES           if ( GDALSoilClasses       == nullptr ) return 82;
        _GDAL_GEOLOGYCLASSES        if ( GDALGeologyClasses    == nullptr ) return 83;
        _GDAL_MACROPORES            if ( GDALMacropores        == nullptr ) return 84;
        _GDAL_LANDCOVERCLASSES      if ( GDALLandCoverClasses  == nullptr ) return 85;
        _GDAL_MELTREGIONS           if ( GDALMeltRegions       == nullptr ) return 86;
        _GDAL_SOURCESSINKS          if ( GDALSourcesSinks      == nullptr ) return 87;

        _GDAL_INTERCEPTION          if ( GDALInterception      == nullptr ) return 89;
        _GDAL_SNOWCOVER             if ( GDALSnowCover         == nullptr ) return 90;
        _GDAL_SURFACESTORAGE        if ( GDALSurfaceStorage    == nullptr ) return 91;
        _GDAL_SOILMOISTURE          if ( GDALSoilMoisture      == nullptr ) return 92;
        _GDAL_GROUNDWATER           if ( GDALGroundwater       == nullptr ) return 93;
        _GDAL_BOUNDARYCONDITION     if ( GDALBoundaryCondition == nullptr ) return 94;


        _GDAL_PRECIPITATION         if( getExtent(GDALPrecipitation, PrecipitationRanges) == false) return -3001;
        _GDAL_TEMPERATURE           if( getExtent(GDALTemperature, TemperatureRanges) == false) return -3002;
        _GDAL_RELATIVEHUMIDITY      if( getExtent(GDALRelativeHumidity, RelativeHumidityRanges) == false) return -3003;
        _GDAL_WINDVELOCITY          if( getExtent(GDALWindVelocity, WindVelocityRanges) == false) return -3004;
        _GDAL_SOLARRADIATION        if( getExtent(GDALSolarRadiation, SolarRadiationRanges) == false) return -3005;
        _GDAL_VAPORPRESSURE         if( getExtent(GDALVaporPressure, VaporPressureRanges) == false) return -3006;

        _GDAL_SOILCLASSES           if( getExtent(GDALSoilClasses, SoilClassesRanges) == false) return -3007;
        _GDAL_GEOLOGYCLASSES        if( getExtent(GDALGeologyClasses, GeologyClassesRanges) == false) return -3008;
        _GDAL_MACROPORES            if( getExtent(GDALMacropores, MacroporesRanges) == false) return -3009;
        _GDAL_LANDCOVERCLASSES      if( getExtent(GDALLandCoverClasses, LandCoverClassesRanges) == false) return -3010;
        _GDAL_MELTREGIONS           if( getExtent(GDALMeltRegions, MeltRegionsRanges) == false) return -3011;
        _GDAL_SOURCESSINKS          if( getExtent(GDALSourcesSinks, SourcesSinksRanges) == false) return -3012;

        _GDAL_INTERCEPTION          if( getExtent(GDALInterception, InterceptionRanges) == false) return -3013;
        _GDAL_SNOWCOVER             if( getExtent(GDALSnowCover, SnowCoverRanges) == false) return -3014;
        _GDAL_SURFACESTORAGE        if( getExtent(GDALSurfaceStorage, SurfaceStorageRanges) == false) return -3015;
        _GDAL_SOILMOISTURE          if( getExtent(GDALSoilMoisture, SoilMoistureRanges) == false) return -3016;
        _GDAL_GROUNDWATER           if( getExtent(GDALGroundwater, GroundwaterRanges) == false) return -3017;
        _GDAL_BOUNDARYCONDITION     if( getExtent(GDALBoundaryCondition, BoundaryConditionRanges) == false) return -3018;

        double X, Y;
        int    GridValueInteger;
        double GridValueDouble;

        bool error_found = false;
        for(int i = 0; i < recordCount; i++)
        {
            SHPObject *_ShpObject = SHPReadObject(_ShpHandle, i);

            if(_ShpObject == nullptr)
            {
                main_window->Log_Message("[att_data_file] Warning/Error[-2000] ShapeObject null at index " + QString::number(i) );
            }
            else
            {
                // Centroid of the Triangle ( TIN )
                X = ( _ShpObject->padfX[0] + _ShpObject->padfX[1] + _ShpObject->padfX[2] ) / 3;
                Y = ( _ShpObject->padfY[0] + _ShpObject->padfY[1] + _ShpObject->padfY[2] ) / 3;

                AttDataFileTextStream << i+1 << "\t";

                _GDAL_SOILCLASSES
                {
                    GridValueInteger = (int) raster_grid_value(GDALSoilClasses, 1, X, Y, SoilClassesRanges);
                    if(GridValueInteger == -9999)
                        error_found = true;
                }
                else
                {
                    GridValueInteger = SoilClassesFileName.toInt();
                }

                AttDataFileTextStream << GridValueInteger << "\t";

                _GDAL_GEOLOGYCLASSES
                {
                    GridValueInteger = (int) raster_grid_value(GDALGeologyClasses, 1, X, Y, GeologyClassesRanges);
                    if(GridValueInteger == -9999)
                        error_found = true;
                }
                else
                {
                    GridValueInteger = GeologyClassesFileName.toInt();
                }

                AttDataFileTextStream << GridValueInteger << "\t";

                _GDAL_LANDCOVERCLASSES
                {
                    GridValueInteger = (int) raster_grid_value(GDALLandCoverClasses, 1, X, Y, LandCoverClassesRanges);
                    if(GridValueInteger == -9999)
                        error_found = true;
                }
                else
                {
                    GridValueInteger = LandCoverClassesFileName.toInt();
                }

                AttDataFileTextStream << GridValueInteger << "\t";

                _GDAL_INTERCEPTION
                {
                    GridValueDouble = raster_grid_value(GDALInterception, 1, X, Y, InterceptionRanges);
                    if( (int)GridValueDouble == -9999)
                        error_found = true;
                }
                else
                {
                    GridValueDouble = InterceptionFileName.toDouble();
                }

                AttDataFileTextStream << GridValueDouble << "\t";

                _GDAL_SNOWCOVER
                {
                    GridValueDouble = raster_grid_value(GDALSnowCover, 1, X, Y, SnowCoverRanges);
                    if( (int)GridValueDouble == -9999)
                        error_found = true;
                }
                else
                {
                    GridValueDouble = SnowCoverFileFileName.toDouble();
                }
                AttDataFileTextStream << GridValueDouble << "\t";

                _GDAL_SURFACESTORAGE
                {
                    GridValueDouble = raster_grid_value(GDALSurfaceStorage, 1, X, Y, SurfaceStorageRanges);
                    if( (int)GridValueDouble == -9999)
                        error_found = true;
                }
                else
                {
                    GridValueDouble = SurfaceStorageFileName.toDouble();
                }

                AttDataFileTextStream << GridValueDouble << "\t";

                _GDAL_SOILMOISTURE
                {
                    GridValueDouble = raster_grid_value(GDALSoilMoisture, 1, X, Y, SoilMoistureRanges);
                    if( (int)GridValueDouble == -9999)
                        error_found = true;
                }
                else
                {
                    GridValueDouble = SoilMoistureFileName.toDouble();
                }

                AttDataFileTextStream << GridValueDouble << "\t";

                _GDAL_GROUNDWATER
                {
                    GridValueDouble = raster_grid_value(GDALGroundwater,1, X, Y, GroundwaterRanges);
                    if( (int)GridValueDouble == -9999)
                        error_found = true;
                }
                else
                {
                    GridValueDouble = GroundwaterFileName.toDouble();
                }

                AttDataFileTextStream << GridValueDouble << "\t";

                _GDAL_PRECIPITATION
                {
                    GridValueInteger = (int) raster_grid_value(GDALPrecipitation, 1, X, Y, PrecipitationRanges);
                    if( GridValueInteger == -9999)
                        error_found = true;
                }
                else
                {
                    GridValueInteger = PrecipitationFileName.toInt();
                }

                AttDataFileTextStream << GridValueInteger << "\t";

                _GDAL_TEMPERATURE
                {
                    GridValueInteger = (int) raster_grid_value(GDALTemperature, 1, X, Y, TemperatureRanges);
                    if( GridValueInteger == -9999)
                        error_found = true;
                }
                else
                {
                    GridValueInteger = TemperatureFileName.toInt();
                }

                AttDataFileTextStream << GridValueInteger << "\t";

                _GDAL_RELATIVEHUMIDITY
                {
                    GridValueInteger = (int) raster_grid_value(GDALRelativeHumidity, 1, X, Y, RelativeHumidityRanges);
                    if( GridValueInteger == -9999)
                        error_found = true;
                }
                else
                {
                    GridValueInteger = RelativeHumidityFileName.toInt();
                }

                AttDataFileTextStream << GridValueInteger << "\t";

                _GDAL_WINDVELOCITY
                {
                    GridValueInteger = (int) raster_grid_value(GDALWindVelocity, 1, X, Y, WindVelocityRanges);
                    if( GridValueInteger == -9999)
                        error_found = true;
                }
                else
                {
                    GridValueInteger = WindVelocityFileName.toInt();
                }

                AttDataFileTextStream << GridValueInteger << "\t";

                _GDAL_SOLARRADIATION
                {
                    GridValueInteger = (int) raster_grid_value(GDALSolarRadiation, 1, X, Y, SolarRadiationRanges);
                    if( GridValueInteger == -9999)
                        error_found = true;
                }
                else
                {
                    GridValueInteger = SolarRadiationFileName.toInt();
                }

                AttDataFileTextStream << GridValueInteger << "\t";

                //TODO
                GridValueInteger = 0;
                AttDataFileTextStream << GridValueInteger << "\t";

                _GDAL_VAPORPRESSURE
                {
                    GridValueInteger = (int) raster_grid_value(GDALVaporPressure, 1, X, Y, VaporPressureRanges);
                    if( GridValueInteger == -9999)
                        error_found = true;
                }
                else
                {
                    GridValueInteger = VaporPressureFileName.toInt();
                }

                AttDataFileTextStream << GridValueInteger << "\t";

                //TODO: DEAL TWO CASES: SHARED WITH TRIANGLES & INSIDE A TRIANGLE
                //TODO: USE SHAPE FILE FOR SOURCE/SINK INFORMATION - DETERMINE IN WHICH TRIANGLE THAT SOURCE/SINK POINT LIES
                _GDAL_SOURCESSINKS
                {
                    GridValueInteger = (int) raster_grid_value(GDALSourcesSinks, 1, X, Y, SourcesSinksRanges);
                    if( GridValueInteger == -9999)
                        error_found = true;
                }
                else
                {
                    GridValueInteger = SourcesSinksFileName.toInt();
                }

                AttDataFileTextStream << GridValueInteger << "\t";

                _GDAL_MELTREGIONS
                {
                    GridValueInteger = (int) raster_grid_value(GDALMeltRegions, 1, X, Y, MeltRegionsRanges);
                    if( GridValueInteger == -9999)
                        error_found = true;
                }
                else
                {
                    GridValueInteger = MeltRegionsFileName.toInt();
                }

                AttDataFileTextStream << GridValueInteger << "\t";

                _GDAL_BOUNDARYCONDITION
                {
                    GridValueInteger = (int) raster_grid_value(GDALBoundaryCondition, 1, X, Y, BoundaryConditionRanges);
                    if( GridValueInteger == -9999)
                        error_found = true;
                }
                else
                {
                    GridValueInteger = BoundaryConditionFileName.toInt();
                }

                //TODO : FIGURE OUT WAY TO TRANSFER INFORMATION ABOUT BOUNDARY CONDITION ACROSS THE EDGE
                AttDataFileTextStream << GridValueInteger << "\t"; //BC1
                AttDataFileTextStream << GridValueInteger << "\t"; //BC2
                AttDataFileTextStream << GridValueInteger << "\t"; //BC3

                _GDAL_MACROPORES
                {
                    GridValueInteger = (int) raster_grid_value(GDALMacropores, 1, X, Y, MacroporesRanges);
                    if( GridValueInteger == -9999)
                        error_found = true;
                }
                else
                {
                    GridValueInteger = MacroporesFileName.toInt();
                }
                AttDataFileTextStream << GridValueInteger << "\n";

            }
        }

        AttDataFile.close();

        if(error_found)
        {
            main_window->Log_Message("[att_data_file] Warning(s)/Error(s)[-4000] -9999 returned by raster_grid_value. See log messages for details ");
            return -4000;
        }

    }
    catch (...) {

        qDebug() << "Error: att_data_file";
        return -9000;
    }

    return 0;
}
