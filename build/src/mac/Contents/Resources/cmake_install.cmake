# Install script for directory: /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/src/mac/Contents/Resources

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/Users/bhattgopal/apps/qgis0.9.0.app/Contents/MacOS")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "Release")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

FILE(INSTALL DESTINATION "/Users/bhattgopal/apps/qgis0.9.0.app/Contents/MacOS/../Resources" TYPE FILE COMPONENTS "Unspecified" FILES "/Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/src/mac/Contents/Resources/asc.icns")
FILE(INSTALL DESTINATION "/Users/bhattgopal/apps/qgis0.9.0.app/Contents/MacOS/../Resources" TYPE FILE COMPONENTS "Unspecified" FILES "/Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/src/mac/Contents/Resources/ddf.icns")
FILE(INSTALL DESTINATION "/Users/bhattgopal/apps/qgis0.9.0.app/Contents/MacOS/../Resources" TYPE FILE COMPONENTS "Unspecified" FILES "/Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/src/mac/Contents/Resources/dem.icns")
FILE(INSTALL DESTINATION "/Users/bhattgopal/apps/qgis0.9.0.app/Contents/MacOS/../Resources" TYPE FILE COMPONENTS "Unspecified" FILES "/Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/src/mac/Contents/Resources/dt0.icns")
FILE(INSTALL DESTINATION "/Users/bhattgopal/apps/qgis0.9.0.app/Contents/MacOS/../Resources" TYPE FILE COMPONENTS "Unspecified" FILES "/Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/src/mac/Contents/Resources/gml.icns")
FILE(INSTALL DESTINATION "/Users/bhattgopal/apps/qgis0.9.0.app/Contents/MacOS/../Resources" TYPE FILE COMPONENTS "Unspecified" FILES "/Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/src/mac/Contents/Resources/img.icns")
FILE(INSTALL DESTINATION "/Users/bhattgopal/apps/qgis0.9.0.app/Contents/MacOS/../Resources" TYPE FILE COMPONENTS "Unspecified" FILES "/Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/src/mac/Contents/Resources/jp2.icns")
FILE(INSTALL DESTINATION "/Users/bhattgopal/apps/qgis0.9.0.app/Contents/MacOS/../Resources" TYPE FILE COMPONENTS "Unspecified" FILES "/Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/src/mac/Contents/Resources/mif.icns")
FILE(INSTALL DESTINATION "/Users/bhattgopal/apps/qgis0.9.0.app/Contents/MacOS/../Resources" TYPE FILE COMPONENTS "Unspecified" FILES "/Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/src/mac/Contents/Resources/qgis.icns")
FILE(INSTALL DESTINATION "/Users/bhattgopal/apps/qgis0.9.0.app/Contents/MacOS/../Resources" TYPE FILE COMPONENTS "Unspecified" FILES "/Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/src/mac/Contents/Resources/qgs.icns")
FILE(INSTALL DESTINATION "/Users/bhattgopal/apps/qgis0.9.0.app/Contents/MacOS/../Resources" TYPE FILE COMPONENTS "Unspecified" FILES "/Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/src/mac/Contents/Resources/shp.icns")
FILE(INSTALL DESTINATION "/Users/bhattgopal/apps/qgis0.9.0.app/Contents/MacOS/../Resources" TYPE FILE COMPONENTS "Unspecified" FILES "/Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/src/mac/Contents/Resources/tiff.icns")
