#include <QDebug>
#include "raster_grid_value.h"
#include "cpl_error.h"
#include "globals.h"

using namespace std;

static double Xmax = 0;
static double Xmin = 0;
static double Ymax = 0;
static double Ymin = 0;
static double Xres = 0;
static double Yres = 0;

// User interface to PIHMgis v3.5
extern PIHMgisDialog *main_window;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to read value from GDAL dataset
// WARNING: Every value is converted to a double.
// Used for elevation values. PIHM uses doubles.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double readValue( void *data, GDALDataType type, int index )
{
    if(print_many_messages)
        qDebug() << "INFO: Start readValue";

    try {
        double val = 0.0;

        if(data == nullptr)
        {
            qDebug() << "readValue Error: data is null. Returning zero.";
            return 0.0;
        }

        switch ( type )
        {
        case GDT_Byte:
            return (double) ((GByte *)data)[index];
            break;
        case GDT_UInt16:
            return (double) ((GUInt16 *)data)[index];
            break;
        case GDT_Int16:
            return (double) ((GInt16 *)data)[index];
            break;
        case GDT_UInt32:
            return (double) ((GUInt32 *)data)[index];
            break;
        case GDT_Int32:
            return (double) ((GInt32 *)data)[index];
            break;
        case GDT_Float32:
            return (double) ((float *)data)[index];
            break;
        case GDT_Float64:
            val = ((double *)data)[index];
            return (double) ((double *)data)[index];
            break;
        default:
            qDebug() <<"Data type "<< type <<" is not supported";
        }

    } catch (...) {

        qDebug() << "readValue Error: readValue is returning zero";

    }

    return 0.0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get Extent from GDAL dataset
// Used for elevation values and PIHM attribute file.
// WARNING: No values assigned to extent with error. This will cause issues to the user!
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void getExtent(GDALDataset *temp, double *ranges){

    if(print_many_messages)
        qDebug() << "INFO: Start getExtent";

    try {
        if(temp == nullptr)
        {
            main_window->Log_Message("[getExtent] Error finding extent");
            qDebug() << "getExtent Error: data is null. Returning WITHOUT ASSIGN EXTENT.";
            return;
        }

        double adfGeoTransform[6];
        temp->GetGeoTransform(adfGeoTransform);
        double myXMaxDouble = adfGeoTransform[0] + temp->GetRasterXSize() * adfGeoTransform[1] + temp->GetRasterYSize() * adfGeoTransform[2];
        double myYMinDouble = adfGeoTransform[3] + temp->GetRasterXSize() * adfGeoTransform[4] + temp->GetRasterYSize() * adfGeoTransform[5];

        Xmax = myXMaxDouble;
        // The affine transform reduces to these values at the
        // top-left corner of the raster
        Xmin = adfGeoTransform[0];
        Ymax = adfGeoTransform[3];
        Ymin = myYMinDouble;

        int rasterXDimInt = temp->GetRasterXSize();
        int rasterYDimInt = temp->GetRasterYSize();

        if(rasterXDimInt < 1)
        {
            main_window->Log_Message("[getExtent] Error with rasterXDimInt");
            qDebug() << "getExtent Error: rasterXDimInt. Returning WITHOUT ASSIGN EXTENT.";
            return;
        }
        if(rasterYDimInt < 1)
        {
            main_window->Log_Message("[getExtent] Error with rasterYDimInt");
            qDebug() << "getExtent Error: rasterYDimInt. Returning WITHOUT ASSIGN EXTENT.";
            return;
        }

        Xres = (Xmax - Xmin) / rasterXDimInt;
        Yres = (Ymax - Ymin) / rasterYDimInt;

        if(print_many_messages)
        {
            qDebug() << "Xres= "<< Xres <<"\n";
            qDebug() << "Yres= "<< Yres <<"\n";
        }

        ranges[0]=Xmin;
        ranges[1]=Xmax;
        ranges[2]=Ymin;
        ranges[3]=Ymax;
        ranges[4]=Xres;
        ranges[5]=Yres;

        return;

    } catch (...) {

        qDebug() << "Error: getExtent is returning w/o error checking";
    }

    return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper Function to get GDAL dataset value at X Y Location
// Used for elevation values and PIHM attribute file.
// WARNING: Every value is converted to a double, regardless of type.
// WARNING: No values assigned to extent with error. This will cause issues to the user!
// WARNING: return -9999 on error not zero
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double raster_grid_value(GDALDataset* layer, int bandNumber, double x, double y, double *ranges){

    if(print_many_messages)
        qDebug() << "INFO: Start raster_grid_value";

    try {

        if(layer == nullptr)
        {
            main_window->Log_Message("[raster_grid_value] Error layer is NULL. Returning -9999.");
            return -9999;
        }

        if(print_many_messages)
        {
            qDebug() << "Xres= " << Xres << "\n";
            qDebug() << "Yres= " << Yres << "\n";
        }
        if(Xres == 0)
        {
            main_window->Log_Message("[raster_grid_value] Error Xres is zero. Returning -9999.");
            return -9999;
        }
        if(Yres == 0)
        {
            main_window->Log_Message("[raster_grid_value] Error Yres is zero. Returning -9999.");
            return -9999;
        }
        if(bandNumber < 0)
        {
            main_window->Log_Message("[raster_grid_value] Error bandNumber < 0. Returning -9999.");
            return -9999;
        }

        GDALRasterBand *band = layer->GetRasterBand(bandNumber); //starts with 1
        if(band == nullptr)
        {
            main_window->Log_Message("[raster_grid_value] band is null. Returning -9999.");
            return -9999;
        }

        GDALDataType type = band->GetRasterDataType();
        int size = GDALGetDataTypeSize(type) / 8;
        if(size < 1)
        {
            main_window->Log_Message("[raster_grid_value] size < 1. Returning -9999.");
            return -9999;
        }

        void *data = CPLMalloc(size);
        if(data == nullptr)
        {
            main_window->Log_Message("[raster_grid_value] data is null. Returning -9999.");
            return -9999;
        }

        int col = (int) floor( (x-ranges[0])/ranges[4] );
        int row = (int) floor( (ranges[3]-y)/ranges[5] );

        if(print_many_messages)
        {
            qDebug() << "col = " << col << "\n";
            qDebug() << "row = " << row << "\n";
        }
        if(col < 1)
        {
            main_window->Log_Message("[raster_grid_value] col < 1. Returning -9999.");
            return -9999;
        }
        if(row < 1)
        {
            main_window->Log_Message("[raster_grid_value] row < 1. Returning -9999.");
            return -9999;
        }

        //band->ReadBlock(col, row, data);
        //https://www.gdal.org/cpl__error_8h.html
        CPLErr err = band->RasterIO(GF_Read, col, row, 1, 1, data, 1, 1, type, 0, 0);
        if( err == CPLE_None)
        {
            return readValue(data, type, 0);
        }
        else
        {
            main_window->Log_Message("[raster_grid_value] Error while reading Raster. Return -9999.");
            return -9999;
        }

    } catch (...) {
        qDebug() << "Error: raster_grid_value is returning w/o error checking. Return -9999.";
        return -9999;
    }

} 


