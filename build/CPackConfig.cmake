# This file will be configured to contain variables for CPack. These variables
# should be set in the CMake list file of the project before CPack module is
# included. Example variables are:
#   CPACK_GENERATOR                     - Generator used to create package
#   CPACK_INSTALL_CMAKE_PROJECTS        - For each project (path, name, component)
#   CPACK_CMAKE_GENERATOR               - CMake Generator used for the projects
#   CPACK_INSTALL_COMMANDS              - Extra commands to install components
#   CPACK_INSTALL_DIRECTORIES           - Extra directories to install
#   CPACK_PACKAGE_DESCRIPTION_FILE      - Description file for the package
#   CPACK_PACKAGE_DESCRIPTION_SUMMARY   - Summary of the package
#   CPACK_PACKAGE_EXECUTABLES           - List of pairs of executables and labels
#   CPACK_PACKAGE_FILE_NAME             - Name of the package generated
#   CPACK_PACKAGE_ICON                  - Icon used for the package
#   CPACK_PACKAGE_INSTALL_DIRECTORY     - Name of directory for the installer
#   CPACK_PACKAGE_NAME                  - Package project name
#   CPACK_PACKAGE_VENDOR                - Package project vendor
#   CPACK_PACKAGE_VERSION               - Package project version
#   CPACK_PACKAGE_VERSION_MAJOR         - Package project version (major)
#   CPACK_PACKAGE_VERSION_MINOR         - Package project version (minor)
#   CPACK_PACKAGE_VERSION_PATCH         - Package project version (patch)

# There are certain generator specific ones

# NSIS Generator:
#   CPACK_PACKAGE_INSTALL_REGISTRY_KEY  - Name of the registry key for the installer
#   CPACK_NSIS_EXTRA_UNINSTALL_COMMANDS - Extra commands used during uninstall
#   CPACK_NSIS_EXTRA_INSTALL_COMMANDS   - Extra commands used during install


SET(CPACK_CMAKE_GENERATOR "Unix Makefiles")
SET(CPACK_GENERATOR "PackageMaker;STGZ;TGZ")
SET(CPACK_INSTALL_CMAKE_PROJECTS "/Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/build;qgis0.9.0;ALL;/")
SET(CPACK_MODULE_PATH "/Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/cmake")
SET(CPACK_NSIS_DISPLAY_NAME "CMake .")
SET(CPACK_OUTPUT_CONFIG_FILE "/Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/build/CPackConfig.cmake")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "/Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/README")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Quantum GIS")
SET(CPACK_PACKAGE_EXECUTABLES "qgis;QGIS")
SET(CPACK_PACKAGE_FILE_NAME "qgis0.9.0-0.9.0-Darwin")
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "CMake .")
SET(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "qgis0.9.0 0.9.0")
SET(CPACK_PACKAGE_NAME "qgis0.9.0")
SET(CPACK_PACKAGE_RELOCATABLE "false")
SET(CPACK_PACKAGE_VENDOR "Tim Sutton")
SET(CPACK_PACKAGE_VERSION "0.9.0")
SET(CPACK_PACKAGE_VERSION_MAJOR "0")
SET(CPACK_PACKAGE_VERSION_MINOR "9")
SET(CPACK_PACKAGE_VERSION_PATCH "0")
SET(CPACK_RESOURCE_FILE_LICENSE "/Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/COPYING")
SET(CPACK_RESOURCE_FILE_README "/usr/share/cmake-2.4/Templates/CPack.GenericDescription.txt")
SET(CPACK_RESOURCE_FILE_WELCOME "/usr/share/cmake-2.4/Templates/CPack.GenericWelcome.txt")
SET(CPACK_SOURCE_GENERATOR "TGZ;TZ")
SET(CPACK_SOURCE_OUTPUT_CONFIG_FILE "/Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/build/CPackSourceConfig.cmake")
SET(CPACK_SYSTEM_NAME "Darwin")
SET(CPACK_TOPLEVEL_TAG "Darwin")
