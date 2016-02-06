/***************************************************************************
    qgsrasterdataprovider.h - DataProvider Interface for raster layers
     --------------------------------------
    Date                 : Mar 11, 2005
    Copyright            : (C) 2005 by Brendan Morley
    email                : morb at ozemail dot com dot au
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
/* $Id: qgsrasterdataprovider.h 7169 2007-08-29 05:39:44Z timlinux $ */

/* Thank you to Marco Hugentobler for the original vector DataProvider */

#ifndef QGSRASTERDATAPROVIDER_H
#define QGSRASTERDATAPROVIDER_H


#include "qgsdataprovider.h"

class QImage;
class QgsPoint;

/** Base class for raster data providers
 *
 *  \note  This class has been copied and pasted from
 *         QgsVectorDataProvider, and does not yet make
 *         sense for Raster layers.
 */
 
class CORE_EXPORT QgsRasterDataProvider : public QgsDataProvider
{
 
  Q_OBJECT

public:

    //! If you add to this, please also add to capabilitiesString()
    enum Capability
    {
      NoCapabilities =              0,
      Identify =                    1
//      Capability2 =           1 <<  1,    , etc
    };


    QgsRasterDataProvider();

    QgsRasterDataProvider( QString const & uri );

    virtual ~QgsRasterDataProvider() {};


    /**
     * Gets the HTTP proxy host used for this connection
     */
    virtual QString proxyHost() const = 0;

    /**
     * Gets the HTTP proxy port used for this connection
     */
    virtual int proxyPort() const = 0;

    /**
     * Gets the HTTP proxy user name used for this connection
     */
    virtual QString proxyUser() const = 0;

    /**
     * Gets the HTTP proxy user password used for this connection
     */
    virtual QString proxyPass() const = 0;


    /**
     *
     * Sets a proxy for the URL given in the constructor
     *
     *
     * \retval TRUE if proxy setting is successful (if indeed it is supported)
     */
    virtual bool setProxy(QString const & host,
                                      int port,
                          QString const & user,
                          QString const & pass)
    {
      //this is mainly to prevent compiler warnings
      if (host.isEmpty() || port < 1 || user.isEmpty() || pass.isEmpty())
      {
        return FALSE;
      }

      return FALSE;
    }

    /**
     * Add the list of WMS layer names to be rendered by this server
     */
    virtual void addLayers(QStringList const & layers,
                           QStringList  const & styles = QStringList()) = 0;

    //! get raster image encodings supported by (e.g.) the WMS Server, expressed as MIME types
    virtual QStringList supportedImageEncodings() = 0;

    /**
     * Get the image encoding (as a MIME type) used in the transfer from (e.g.) the WMS server
     */
    virtual QString imageEncoding() const = 0;

    /**
     * Set the image encoding (as a MIME type) used in the transfer from (e.g.) the WMS server
     */
    virtual void setImageEncoding(QString  const & mimeType) = 0;

    /**
     * Set the image projection (in WMS CRS format) used in the transfer from (e.g.) the WMS server
     */
    virtual void setImageCrs(QString const & crs) = 0;


    // TODO: Document this better.
    /** \brief   Renders the layer as an image
     */
    virtual QImage* draw(QgsRect  const & viewExtent, int pixelWidth, int pixelHeight) = 0;

    /** Returns a bitmask containing the supported capabilities
        Note, some capabilities may change depending on whether
        a spatial filter is active on this provider, so it may
        be prudent to check this value per intended operation.
      */
    virtual int capabilities() const 
    {
      return QgsRasterDataProvider::NoCapabilities;
    }

    /**
     *  Returns the above in friendly format.
     */
    QString capabilitiesString() const;


    // TODO: Get the supported formats by this provider
    
    // TODO: Get the file masks supported by this provider, suitable for feeding into the file open dialog box
    

    /**
     * Get metadata in a format suitable for feeding directly
     * into a subset of the GUI raster properties "Metadata" tab.
     */
    virtual QString getMetadata() = 0;

    /**
     * \brief Identify details from a server (e.g. WMS) from the last screen update
     *
     * \param point[in]  The pixel coordinate (as it was displayed locally on screen)
     *
     * \return  A text document containing the return from the WMS server
     *
     * \note WMS Servers prefer to receive coordinates in image space, therefore
     *       this function expects coordinates in that format.
     *
     * \note  The arbitraryness of the returned document is enforced by WMS standards
     *        up to at least v1.3.0
     */
    virtual QString identifyAsText(const QgsPoint& point) = 0;

    /**
     * \brief   Returns the caption error text for the last error in this provider
     *
     * If an operation returns 0 (e.g. draw()), this function
     * returns the text of the error associated with the failure.
     * Interactive users of this provider can then, for example,
     * call a QMessageBox to display the contents.
     *
     */
    virtual QString errorCaptionString() = 0;

    /**
     * \brief   Returns the verbose error text for the last error in this provider
     *
     * If an operation returns 0 (e.g. draw()), this function
     * returns the text of the error associated with the failure.
     * Interactive users of this provider can then, for example,
     * call a QMessageBox to display the contents.
     *
     */
    virtual QString errorString() = 0;


protected:

};

#endif
