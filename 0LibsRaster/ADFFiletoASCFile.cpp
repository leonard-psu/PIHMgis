#include <QObject>
#include <QString>
#include <QDebug>
#include <QFile>

#include <gdal.h>
#include <gdal_priv.h>

#include "ADFFiletoASCFile.h"
#include "globals.h"


// User interface to PIHMgis v3.5
extern PIHMgisDialog *main_window;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper function readValueB2A
// Used in ADFFiletoASCFile function below
// NOTE: double value type is returned regardless of original type. Potential issues here.
// NOTE: -99999.0 is returned with bad index. Not Zero. As zero is more likely appropriate value than -99999
// NOTE:  -9999.0 is returned when unable to read value.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double readValueB2A ( void *data, GDALDataType type, int index )
{
    if(print_debug_messages)
        qDebug() << "INFO: Start readValueB2A";

    if(data == nullptr)
    {
        main_window->Log_Message("[readValueB2A] Error[0] data is NULL, returning -99999.");
        return -99999.0;
    }
    if(index < 0 )
    {
        main_window->Log_Message("[readValueB2A] Error[1] invalid index < 0, returning -99999.");
        return -99999.0;
    }
    if(index > 500000 ) //500000 is a guess
    {
        main_window->Log_Message("[readValueB2A] Error[1] invalid index > 500000 ( a guess), returning -99999.");
        return -99999.0;
    }

    try {
        switch ( type )
        {
        case GDT_Byte:
        {
            return (double) ((GByte *)data)[index];
            break;
        }
        case GDT_UInt16:
        {
            return (double) ((GUInt16 *)data)[index];
            break;
        }
        case GDT_Int16:
        {
            return (double) ((GInt16 *)data)[index];
            break;
        }
        case GDT_UInt32:
        {
            return (double) ((GUInt32 *)data)[index];
            break;
        }
        case GDT_Int32:
        {
            return (double) ((GInt32 *)data)[index];
            break;
        }
        case GDT_Float32:
        {
            return (double) ((float *)data)[index];
            break;
        }
        case GDT_Float64:
        {
            double val = ((double *)data)[index];
            return (double) ((double *)data)[index];
            break;
        }
        default:
        {
            main_window->Log_Message("[readValueB2A] Error[2] Raster Data Type is not supported ");
            break;
        }
        }

    } catch (...) {
        qDebug() << "Error: readValueB2A is returning w/o checking";
    }

    return -9999.0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper function ADFFiletoASCFile
// Used in fillpits, flowgrids
// Zero returned if no errors/issues found
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ADFFiletoASCFile(QString ADFFileName, QString ASCFileName)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start ADFFiletoASCFile";

    try {

        if(ADFFileName == nullptr)
        {
            main_window->Log_Message("[ADFFiletoASCFile] Error[100] Invalid ADFFileName ");
            return 100;
        }
        if(ADFFileName.length() < 1)
        {
            main_window->Log_Message("[ADFFiletoASCFile] Error[101] Invalid ADFFileName ");
            return 101;
        }
        if(ASCFileName == nullptr)
        {
            main_window->Log_Message("[ADFFiletoASCFile] Error[102] Invalid ASCFileName ");
            return 102;
        }
        if(ASCFileName.length() < 1)
        {
            main_window->Log_Message("[ADFFiletoASCFile] Error[103] Invalid ASCFileName ");
            return 103;
        }

        GDALAllRegister();
        GDALDataset *layer = (GDALDataset *)GDALOpen(qPrintable(ADFFileName), GA_ReadOnly);
        if(layer == nullptr)
        {
            main_window->Log_Message("[ADFFiletoASCFile] Error[104] layer is NULL ");
            return 104;
        }

        int bandNumber = 1;
        GDALRasterBand *band = layer->GetRasterBand(bandNumber);
        if(band == nullptr)
        {
            main_window->Log_Message("[ADFFiletoASCFile] Error[105] band is NULL ");
            GDALClose(layer);
            return 105;
        }

        GDALDataType type = band->GetRasterDataType();
        if(type == GDT_Unknown)
        {
            main_window->Log_Message("[ADFFiletoASCFile] Error[106] Unknown Raster Type ");
            GDALClose(layer);
            return 106;
        }

        double ranges[6];
        layer->GetGeoTransform(ranges);

        QFile ASCFile(ASCFileName);
        bool opened = ASCFile.open(QIODevice::WriteOnly | QIODevice::Text);
        if(!opened)
        {
            main_window->Log_Message("[ADFFiletoASCFile] Error[107] Unable to open " + ASCFileName);
            GDALClose(layer);
            return 107;
        }

        QTextStream ASCFileTextStream(&ASCFile);

        ASCFileTextStream << "ncols "        << layer->GetRasterXSize() << "\n";
        ASCFileTextStream << "nrows "        << layer->GetRasterYSize() << "\n";
        ASCFileTextStream << "xllcorner "    << ranges[0] << "\n";
        ASCFileTextStream << "yllcorner "    << (ranges[3] + layer->GetRasterXSize() * ranges[4] + layer->GetRasterYSize() * ranges[5]) << "\n";
        ASCFileTextStream << "cellsize "     << ranges[1] << "\n";
        ASCFileTextStream << "nodata_value " << "-9999" << "\n";

        int cols = layer->GetRasterXSize();
        int rows = layer->GetRasterYSize();
        if(cols < 1)
        {
            main_window->Log_Message("[ADFFiletoASCFile] Error[108] Invalid cols < 0 ");
            GDALClose(layer);
            ASCFile.close();
            return 108;
        }
        if(cols > 100000) //100000 is a guess
        {
            main_window->Log_Message("[ADFFiletoASCFile] Error[109] Invalid cols > 100000 ");
            GDALClose(layer);
            ASCFile.close();
            return 109;
        }
        if(rows < 1)
        {
            main_window->Log_Message("[ADFFiletoASCFile] Error[110] Invalid rows < 0 ");
            GDALClose(layer);
            ASCFile.close();
            return 110;
        }
        if(rows > 100000) //100000 is a guess
        {
            main_window->Log_Message("[ADFFiletoASCFile] Error[111] Invalid rows > 100000 ");
            GDALClose(layer);
            ASCFile.close();
            return 111;
        }

        double NODATA_VAL = band->GetNoDataValue();

        if(print_many_messages)
        {
            main_window->Log_Message("[ADFFiletoASCFile] NODATA value =  " + QString::number(NODATA_VAL) + " for file: " + ASCFileName);
        }

        int size = GDALGetDataTypeSize(type) / 8;
        if(size < 1)
        {
            main_window->Log_Message("[ADFFiletoASCFile] Error[112] Invalid Size < 1 ");
            GDALClose(layer);
            ASCFile.close();
            return 112;
        }
        if(size > 50000000) //50000000 is a guess
        {
            main_window->Log_Message("[ADFFiletoASCFile] Error[113] Invalid Size > 50000000 ( a guess) ");
            GDALClose(layer);
            ASCFile.close();
            return 113;
        }

        void *data = VSIMalloc(size);
        if(data == nullptr)
        {
            main_window->Log_Message("[ADFFiletoASCFile] Error[114] Data is NULL ");
            GDALClose(layer);
            ASCFile.close();
            return 114;
        }

        bool raster_error_found = false;
        bool value_error_found = false;
        for(int row=0; row < rows; row++)
        {
            for(int col=0; col < cols; col++)
            {
                CPLErr err = band->RasterIO(GF_Read, col, row, 1, 1, data, 1, 1, type, 0, 0);
                if(err == 0 )
                {
                    //Note any errors from readValueB2A returns -99999
                    double tempVal = readValueB2A(data, type, 0);
                    if(tempVal <= -99999.0)
                    {
                        //Error value will be written regardless, but need to let user know!
                        if(print_many_messages)
                        {
                            main_window->Log_Message("[ADFFiletoASCFile] readValueB2A Error code =  " + QString::number(tempVal));
                            value_error_found = true;
                        }
                    }

                    ASCFileTextStream<<( tempVal != NODATA_VAL ? tempVal : -9999) << " ";

                }
                else {
                    raster_error_found = true;
                    if(print_many_messages)
                    {
                        switch(err)
                        {
                        case CE_Debug:
                            main_window->Log_Message("[ADFFiletoASCFile] CE_Debug RasterIO Error code =  " + QString::number(err));
                            break;
                        case CE_Warning:
                            main_window->Log_Message("[ADFFiletoASCFile] CE_Warning RasterIO Error code =  " + QString::number(err));
                            break;
                        case CE_Failure:
                            main_window->Log_Message("[ADFFiletoASCFile] CE_Failure RasterIO Error code =  " + QString::number(err));
                            break;
                        case CE_Fatal:
                            main_window->Log_Message("[ADFFiletoASCFile] CE_Fatal RasterIO Error code =  " + QString::number(err));
                            break;
                        default:
                            main_window->Log_Message("[ADFFiletoASCFile] RasterIO Error code =  " + QString::number(err));
                            break;
                        }
                    }
                }
            }
            ASCFileTextStream << "\n";
        }

        ASCFile.close();
        VSIFree(data);
        GDALClose(layer);

        if(raster_error_found) //Potentially Serious error  (user has to decide)
        {
            main_window->Log_Message("[ADFFiletoASCFile] [ERRORs] Issues found reading raster dataset. See Logs.");
            return -1000;
        }

        if(value_error_found) //Potentially Bad errors (user has to decide)
        {
            main_window->Log_Message("[ADFFiletoASCFile] [ERRORs] Issues found parsing values. Recommend checking with GIS tool.");
            return -1001;
        }

        if(print_debug_messages)
            main_window->Log_Message("[ADFFiletoASCFile] Processing ... Done!");

        return 0;

    } catch (...) {
        qDebug() << "Error: ADFFiletoASCFile is returning w/o checking";
    }

    return -9999;
}
