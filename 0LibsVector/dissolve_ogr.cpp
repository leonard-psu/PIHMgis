//CREDIT: https://lists.osgeo.org/pipermail/discuss/2011-March/008642.html

#include<QDebug>

#include <assert.h>

#include "gdal.h"
#include "gdal_priv.h"

#include "ogrsf_frmts.h"
#include "ogr_p.h"

#include "cpl_conv.h"
#include "cpl_string.h"

#include "ogr_api.h"
#include "gdal_priv.h"

#include "globals.h"

// User interface to PIHMgis v3.5
extern PIHMgisDialog *main_window;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct s_attribute
{
    const char *value;
    struct s_attribute *next;	// list link
} t_attribute;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// attributeNew
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
t_attribute *attributeNew()
{
    if(print_debug_messages)
        qDebug() << "INFO: Start attributeNew";

    try {
        t_attribute *attribute;
        attribute = (t_attribute *) malloc(sizeof(t_attribute));
        if(attribute == nullptr)
        {
            main_window->Log_Message("[attributeNew] Malloc failed returning nullptr.");
            return nullptr;
        }

        attribute->value = nullptr;
        attribute->next = nullptr;

        return(attribute);

    } catch (...) {
        qDebug() << "Error: attributeNew is returning nullptr";
        return nullptr;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// attributeInsert
// Used in dissolve_ogr below
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int attributeInsert(t_attribute **head, const char* newValue )
{
    if(print_debug_messages)
        qDebug() << "INFO: Start attributeInsert";

    try {
        t_attribute *curr;
        t_attribute *prev=nullptr;
        t_attribute *item=nullptr;

        curr = *head;
        while(curr != nullptr)
        {
            if( strcmp( curr->value , newValue) >= 0 )
                break;
            prev = curr;
            curr = curr->next;
        }

        if ( !curr || strcmp(curr->value, newValue) != 0 )	//insert a new node in the list
        {
            item = attributeNew();
            if(item == nullptr)
            {
                main_window->Log_Message("[attributeInsert] Failed to create new item.");
                curr = nullptr;
                return -1001;
            }

            item->value = newValue;
            if(prev == nullptr)
            {
                item->next = *head;	// new top
                *head = item;		// link to old top
            }else
            {
                prev->next = item;
                item->next = curr;
            }
        }
        return 0 ;

    } catch (...) {
        qDebug() << "Error: attributeInsert is returning nullptr";
        return -5000;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// attributePrint
// Note used. Kept for debugging.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void attributePrint( t_attribute *head)
{
    t_attribute *curr;
    curr =head;
    while(curr != nullptr)
    {
        printf("%s\n",curr->value );
        curr = curr->next;
    }
    return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// attributeCount
// Used in dissolve_ogr below
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int attributeCount( t_attribute *head)
{
    int i=0;
    t_attribute *curr;
    curr =head;
    while(curr != nullptr)
    {
        i++;
        curr = curr->next;
    }
    return(i);

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// dissolve_ogr ogrDissolve v1.0
// Dissolves common boundaries between polygons with the same attribute value.
// "Usage: ogrDissolve [-a <attr name>] [-u] <input DS> <output DS>\n"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int dissolve_ogr( int argc, char *argv[] )
{
    if(print_debug_messages)
        qDebug() << "INFO: Start dissolve_ogr";

    try {

        const char *pszUnionAttrib = nullptr;
        const char *pszSrcFilename = nullptr;
        const char *pszDstFilename = nullptr;
        char *pzsDstFormat = nullptr;
        const char *pzsDstFormatDefault = "ESRI Shapefile";

        bool bUnpackMultiPolys = false;
        bool bVerbose = false;

        char pszQuery[250];

        // --------------------------------------------------------------------
        //      Parse arguments.
        // --------------------------------------------------------------------
        argc = GDALGeneralCmdLineProcessor( argc, &argv, 0 );
        if( argc <= 1 )
        {
            main_window->Log_Message("[dissolve_ogr] Error[-1000] Invalid arguments <= 1");
            return -1000;
        }


        for( int i = 1; i < argc; i++ )
        {
            if( EQUAL(argv[i],"-a") && i < argc-1 )
            {
                pszUnionAttrib = argv[++i];		// location (path) attribute name
            }
            else if( EQUAL(argv[i],"-u") )
            {
                bUnpackMultiPolys = true;
            }
            else if( EQUAL(argv[i],"-v") )
            {
                bVerbose = true;
            }
            else if( EQUAL(argv[i],"-of") && i < argc-1 )
            {
                pzsDstFormat = argv[++i];
            }
            else if( pszSrcFilename == nullptr )
            {
                pszSrcFilename = argv[i];
            }
            else if( pszDstFilename == nullptr )
            {
                pszDstFilename = argv[i];
            }
            else
            {
                main_window->Log_Message("[dissolve_ogr] Error[-1001] Failed to parse arguments ");
                return -1001;
            }
        }

        if( pszSrcFilename == nullptr )
        {
            CPLError( CE_Failure, CPLE_AppDefined, "An input DataSet is required." );
            main_window->Log_Message("[dissolve_ogr] Error[-1002] An input DataSet is required. ");
            return -1002;
        }

        if( pszDstFilename == nullptr )
        {
            CPLError( CE_Failure, CPLE_AppDefined, "An output DataSet is required." );
            main_window->Log_Message("[dissolve_ogr] Error[-1003] An output DataSet is required. ");
            return -1003;
        }

        if ( pzsDstFormat == nullptr )
        {
            pzsDstFormat = (char*)pzsDstFormatDefault;
        }


        // --------------------------------------------------------------------
        //  Do requested Operations:
        // --------------------------------------------------------------------
        OGRLayer		*poLayer;
        OGRFeature		*poFeature;
        OGRFeatureDefn  *poFDefn;
        OGRGeometry		*poGeometry;
        OGRwkbGeometryType poGeomType;
        OGRLayer		*poLayerOut;

        long nLayers = 0;
        long nFeatures = 0;
        long iField = 0;
        bool bFoundAttrib = FALSE;

        //-----------------------------------------------------------------------
        //  Open input, check for requirements:
        //-----------------------------------------------------------------------
        OGRRegisterAll();

        GDALDataset *poDS = (GDALDataset*) GDALOpenEx(pszSrcFilename, GDAL_OF_READONLY, nullptr, nullptr, nullptr);
        if( poDS == nullptr )
        {
            main_window->Log_Message("[dissolve_ogr] Error[-1004] can't open dataset. ");
            return -1004;
        }

        nLayers = poDS->GetLayerCount();
        if (nLayers == 0)
        {
            main_window->Log_Message("[dissolve_ogr] Error[-1005] no layers in dataset. ");
            GDALClose(poDS);
            return -1005;
        }

        poLayer = poDS->GetLayer( 0 );
        poLayer->ResetReading();

        nFeatures = poLayer->GetFeatureCount();

        bool error_found = false;
        if ( (poFeature = poLayer->GetNextFeature()) != nullptr )
        {
            // Check Geometry type
            poGeometry = poFeature->GetGeometryRef();
            if( poGeometry != nullptr )
            {
                poGeomType = poGeometry->getGeometryType();	// TBD: check if polygon
                if ( poGeomType != wkbMultiPolygon && poGeomType != wkbPolygon )
                {
                    //Data must be polygon.
                    error_found = true;
                }
            }
            else
            {
                //no geometry in feature
                error_found = true;
            }

            //--- Get Field of Union Attribute: ---//
            OGRFeatureDefn *poFDefn = poLayer->GetLayerDefn();
            for( iField = 0; iField < poFDefn->GetFieldCount(); iField++ )
            {
                OGRFieldDefn *poFieldDefn = poFDefn->GetFieldDefn( iField );
                if ( EQUAL(poFieldDefn->GetNameRef(),pszUnionAttrib) )
                {
                    bFoundAttrib =  true;
                    break;
                }
            }

            if (!bFoundAttrib)
            {
                main_window->Log_Message("[dissolve_ogr] Error Data must have a disolve field. ");
                error_found = true;
            }

        }
        else
        {
            main_window->Log_Message("[dissolve_ogr] Error No features in dataset. ");
            GDALClose(poDS);
            error_found = true;
        }

        if (error_found)
        {
            main_window->Log_Message("[dissolve_ogr] Error(s) [-1006] found parsing features. ");
            GDALClose(poDS);
            return -1006;
        }

        //-----------------------------------------------------------------------
        //  Create Attribute List:
        //-----------------------------------------------------------------------
        poLayer->ResetReading();
        int i = 0;
        const char *pszAttrValue;
        t_attribute *attrList=nullptr;

        error_found = false;
        while( (poFeature = poLayer->GetNextFeature()) != nullptr )
        {
            pszAttrValue = poFeature->GetFieldAsString(iField);
            int err = attributeInsert( &attrList, pszAttrValue );
            if(err != 0)
            {
                error_found = true;
            }
        }
        if (error_found)
        {
            main_window->Log_Message("[dissolve_ogr] Error(s) [-1007] found parsing features. ");
            GDALClose(poDS);
            return -1007;
        }

        //-----------------------------------------------------------------------
        //  Create output:
        //-----------------------------------------------------------------------
        GDALDriver *poDriver = GetGDALDriverManager()->GetDriverByName(pzsDstFormat);

        if( poDriver == nullptr )
        {
            main_window->Log_Message("[dissolve_ogr] Error(s) [-1008]  driver not available. Are OGL dlls/so/a missing in PIHMgis installation directory?");
            GDALClose(poDS);
            return -1008;
        }

        GDALDataset *poDSout = poDriver->Create(pszDstFilename,0,0,0,GDT_Unknown,nullptr);
        if( poDSout == nullptr )
        {
            main_window->Log_Message("[dissolve_ogr] Error(s) [-1009] Creation of output file failed. ");
            GDALClose(poDS);
            return -1009;
        }

        poLayerOut = poDSout->CreateLayer( "new_layer", NULL, poGeomType, nullptr );
        if( poLayerOut == nullptr )
        {
            main_window->Log_Message("[dissolve_ogr] Error(s) [-1010] Layer creation failed. ");
            GDALClose(poDS);
            GDALClose(poDSout);
            return -1010;
        }

        error_found = false;
        poFDefn = poLayer->GetLayerDefn();
        for(int iField2 = 0; iField2 < poFDefn->GetFieldCount(); iField2++ )
        {
            OGRFieldDefn *poFieldDefn = poFDefn->GetFieldDefn( iField2 );

            if( poLayerOut->CreateField( poFieldDefn ) != OGRERR_NONE )
            {
                error_found = true;
            }
        }

        if(error_found )
        {
            main_window->Log_Message("[dissolve_ogr] Error(s) [-1011] Creation of field failed. ");
            GDALClose(poDS);
            GDALClose(poDSout);
            return -1011;
        }

        //-----------------------------------------------------------------------
        //  Process Features:
        //-----------------------------------------------------------------------
        poLayer->ResetReading();

        i = 0;
        t_attribute *curr = attrList;
        int nAttrs = attributeCount(attrList);

        OGRGeometryCollection *poCollection = new OGRGeometryCollection();
        if( poCollection == nullptr )
        {
            main_window->Log_Message("[dissolve_ogr] Error [-1012] poCollection is nullptr. ");
            GDALClose(poDS);
            GDALClose(poDSout);
            return -1012;
        }

        bool feature_error_found = false;
        bool geometry_error_found = false;
        while ( curr )
        {
            i++;
            if (!bVerbose )
            {
                GDALTermProgress( ((double)i)/nAttrs, "", nullptr);
            }
            else
            {
                main_window->Log_Message("[dissolve_ogr] Progress " + QString::number(i) + "/" + QString::number(nAttrs) + " " + QString(curr->value));
            }

            sprintf( pszQuery, "%s='%s'",pszUnionAttrib, curr->value );
            poLayer->SetAttributeFilter( pszQuery );
            poLayer->ResetReading();

            int nFeatures = poLayer->GetFeatureCount();
            if(nFeatures <= 0)
            {
                feature_error_found = true;
            }
            else
            {
                OGRGeometry *poGeometryOut = nullptr;

                int k=0;
                while ( (poFeature = poLayer->GetNextFeature()) )
                {
                    k++;

                    if (bVerbose )
                    {
                        GDALTermProgress( ((double)k)/nFeatures, "", nullptr);
                    }

                    OGRGeometry *poGeometryTemp = nullptr;
                    poGeometryTemp = poFeature->GetGeometryRef();

                    if (poGeometryTemp)
                    {
                        if (poGeometryOut)
                        {
                            poGeometryOut = poGeometryOut->Union( poGeometryTemp);
                        }
                        else
                        {
                            poGeometryOut = poGeometryTemp->clone();
                        }
                    }
                }

                if (bVerbose )
                {
                    GDALTermProgress( ((double)nFeatures)/nFeatures, "", nullptr);
                }

                if (poGeometryOut)
                {
                    char * pszTemp = nullptr;

                    if ( poGeometryOut->getGeometryType() == wkbMultiPolygon )	//it's a collection
                    {
                        int nPolys = ((OGRGeometryCollection *)poGeometryOut)->getNumGeometries();

                        OGRGeometry *poGeometryTemp = nullptr;

                        if(nPolys <= 0)
                        {
                            geometry_error_found = true; //Does this error matter? User has decide
                        }
                        else if(nPolys > 500000) //500000 is a guess too large
                        {
                            geometry_error_found = true;
                        }
                        else
                        {
                            for (int j = 0; j < nPolys; j++ )
                            {
                                poGeometryTemp = ((OGRGeometryCollection *)poGeometryOut)->getGeometryRef(j);

                                OGRFeature *poFeatureOut = new OGRFeature( poLayer->GetLayerDefn() );

                                if(poFeatureOut == nullptr)
                                {
                                    geometry_error_found = false;
                                }
                                else
                                {
                                    poFeatureOut->SetField( iField, curr->value );
                                    poFeatureOut->SetGeometryDirectly(poGeometryTemp);
                                    poLayerOut->CreateFeature(poFeatureOut);
                                }
                            }
                        }
                    }
                    else
                    {
                        OGRFeature *poFeatureOut = new OGRFeature( poLayer->GetLayerDefn() );
                        if(poFeatureOut == nullptr)
                        {
                            geometry_error_found = false;
                        }
                        else
                        {
                            poFeatureOut->SetField( iField, curr->value );
                            poFeatureOut->SetGeometryDirectly(poGeometryOut);
                            poLayerOut->CreateFeature(poFeatureOut);
                        }
                    }
                }

            }
            curr = curr->next;
        }

        GDALTermProgress( ((double)nAttrs)/nAttrs, "", nullptr);

        //Clean up
        GDALClose(poDS);
        GDALClose(poDSout);

        if( feature_error_found )
        {
            main_window->Log_Message("[dissolve_ogr] WARNING [-5000]] Feature error found. User needs to check. ");
            return -5000;
        }
        if( geometry_error_found )
        {
            main_window->Log_Message("[dissolve_ogr] WARNING [-5001]] Geometry error found. User needs to check. ");
            return -5001;
        }

        return(0);

    }
    catch (...)
    {
        qDebug() << "Error: dissolve_ogr is returning w/o checking";
        return -5000;
    }
}
