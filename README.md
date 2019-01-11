### Windows Users
Download latest executable PIHMGis v3.5 in the zip file called Windows_PIHM_GIS.zip

### Ubuntu 18.04 Users
Download latest executable PIHMGis v3.5 in the zip file called Ubuntu_PIHMgis.zip

### Other Linux Users
Will need to compile code. See How to Compile Linux PIHMgis below. These steps were used to build with Ubuntu, and should apply to other Linux environments.

### PIHMgis v3.5 developed using windows Qt Creator 
1. [Latest] Qt 5.12.0 (MSVC 2015, 32 bit) Based on Qt 5.12.0 (MSVC 2015, 32 bit) Built on Dec 3 2018 13:08:01 From revision d51ddbb8f0 Copyright 2008-2018 The Qt Company Ltd. All rights reserved.
2. [Worked with] Qt 5.11.2 (i386-little_endian-ilp32 shared (dynamic) release build; by MSVC 2015) on "windows" 

### These libraries are required
1. gdal-2.3.1 or higher
2. sundials 2.7.0 solver. This code will need modification to use higher versions of sundials.
3. triangle by Jonathan Richard Shewchuk, see note below.

### Note this code has been developed and tested on windows environment only.

### General Steps to compile code using Qt Creator 
1. Open Qt Project file/folder with this github code repository
2. Clean All. Make sure no moc files etc automatically created by Qt exist in folders.
3. Run qmake. Fix any error issues found.
4. Build. Fix any error issues found.
5. Run.

### Problems you will encounter, as they are dependent on your compute environment
You will need to modify the (1) include paths (2) depenency paths (3) LIBs locations for this project. These are in the PIHMgis.pro project file. It is recommended to update these via the Qt Creator interface.
Sometimes Qt Creator will find code errors when building. Especially for code/functions that exist and are fine. When this happens, clean all, run qmake, and rebuild all.

### Code changes to PIHMgis reflect research discussed here:

• Leonard, L., Duffy, C., 2016. Visualization Workflows for Level-12 HUC Scales: Towards an Expert System for Watershed Analysis in a Distributed Computing Environment”, Environmental Modelling & Software, Vol 78, pp 163-178. http://dx.doi.org/10.1016/j.envsoft.2016.01.001

• Leonard, L., Duffy, C., 2014. Automating data-model workflows at a level 12 HUC scale: Watershed modeling in a distributed computing environment. Vol 61, pp 174-190. https://doi.org/10.1016/j.envsoft.2014.07.015

• Leonard, L., Duffy, C., 2013. Essential Terrestrial Variable Data Workflows for Distributed Water Resources Modeling. Vol 50, pp 85-96. http://dx.doi.org/10.1016/j.envsoft.2013.09.003


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#### PIHMgis Version 3.0
Software Author:
Gopal Bhatt
Penn State University

• Bhatt, G., Kumar, M., Duffy, C., 2014. A Tightly Coupled GIS and Distributed Hydrologic Modeling Framework, Environmental Modelling & Software, Vol. 62, pp. 70–84. https://doi.org/10.1016/j.envsoft.2014.08.003


#### Highlights
• A coupled GIS and distributed hydrologic modeling framework, PIHMgis was developed.
• PIHMgis uses national geospatial dataset to setup, execute, and analyze simulations.
• Procedural framework improves model-data integration using shared geodata model.


PIHMgis is an open-source, platform independent, tightly coupled GIS and distributed hydrologic modeling framework (www.pihm.psu.edu). PIHMgis improves model-data integration, and provides functionalities for watershed delineation, domain decomposition, parameter assignment, simulation, visualization and analyses.

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
### Other Software 

Triangle is required to create PIHM meshes.
The version supplied with PIHMgis v3.0 has been removed from this PIHMgis version (3.5).
Users are required to copy/compile Shewchuk's triangle software into the Software directory.
The Software directory is created in their PIHMgis workspace.
A Two-Dimensional Quality Mesh Generator and Delaunay Triangulator. (triangle.c)
Copyright 1993, 1995, 1997, 1998, 2002, 2005
Jonathan Richard Shewchuk

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
### How to Compile Linux PIHMgis.

Build and install QT5.12 or higher. You will need to use QTCreator.
Build and install GDAL from https://github.com/OSGeo/gdal
Build and install Sundials-2.7.0 from https://computation.llnl.gov/projects/sundials/download/sundials-2.7.0.tar.gz
Build and install Triangle from https://www.cs.cmu.edu/~quake/triangle.html
Download PIHMgis from github.
Open/Import PIHMgis.pro using QTCreator.
Clean all.
Add Library and Include Linux paths for gdal (libgdal_i.a), sundials (libsundials_nvecserial.a, libsundials_cvodes.a), to the PIHMgis.pro using QTCreator "Add Library".

### Issues found when compile Linux PIHMgis
QT Creator may complain about multiple definitions. Comment out the duplicate .cpp and .h files in PIHMgis.pro.
