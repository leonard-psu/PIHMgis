#############################################################################
# Makefile for building: PIHMgis
# Generated by qmake (3.1) (Qt 5.11.1)
# Project:  PIHMgis.pro
# Template: app
# Command: G:\Qt\5.11.1\msvc2017_64\bin\qmake.exe -o Makefile PIHMgis.pro -spec win32-msvc "CONFIG+=debug" "CONFIG+=qml_debug"
#############################################################################

MAKEFILE      = Makefile

first: debug
install: debug-install
uninstall: debug-uninstall
QMAKE         = G:\Qt\5.11.1\msvc2017_64\bin\qmake.exe
DEL_FILE      = del
CHK_DIR_EXISTS= if not exist
MKDIR         = mkdir
COPY          = copy /y
COPY_FILE     = copy /y
COPY_DIR      = xcopy /s /q /y /i
INSTALL_FILE  = copy /y
INSTALL_PROGRAM = copy /y
INSTALL_DIR   = xcopy /s /q /y /i
QINSTALL      = G:\Qt\5.11.1\msvc2017_64\bin\qmake.exe -install qinstall
QINSTALL_PROGRAM = G:\Qt\5.11.1\msvc2017_64\bin\qmake.exe -install qinstall -exe
DEL_FILE      = del
SYMLINK       = $(QMAKE) -install ln -f -s
DEL_DIR       = rmdir
MOVE          = move
SUBTARGETS    =  \
		debug \
		release


debug: FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Debug
debug-make_first: FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Debug 
debug-all: FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Debug all
debug-clean: FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Debug clean
debug-distclean: FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Debug distclean
debug-install: FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Debug install
debug-uninstall: FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Debug uninstall
release: FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Release
release-make_first: FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Release 
release-all: FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Release all
release-clean: FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Release clean
release-distclean: FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Release distclean
release-install: FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Release install
release-uninstall: FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Release uninstall

Makefile: PIHMgis.pro G:\Qt\5.11.1\msvc2017_64\mkspecs\win32-msvc\qmake.conf G:\Qt\5.11.1\msvc2017_64\mkspecs\features\spec_pre.prf \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\common\angle.conf \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\common\windows-vulkan.conf \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\common\msvc-desktop.conf \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\qconfig.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_3danimation.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_3danimation_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_3dcore.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_3dcore_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_3dextras.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_3dextras_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_3dinput.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_3dinput_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_3dlogic.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_3dlogic_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_3dquick.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_3dquick_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_3dquickanimation.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_3dquickanimation_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_3dquickextras.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_3dquickextras_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_3dquickinput.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_3dquickinput_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_3dquickrender.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_3dquickrender_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_3dquickscene2d.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_3dquickscene2d_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_3drender.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_3drender_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_accessibility_support_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_axbase.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_axbase_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_axcontainer.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_axcontainer_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_axserver.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_axserver_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_bluetooth.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_bluetooth_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_bootstrap_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_charts.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_charts_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_concurrent.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_concurrent_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_core.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_core_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_datavisualization.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_datavisualization_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_dbus.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_dbus_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_designer.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_designer_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_designercomponents_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_devicediscovery_support_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_edid_support_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_egl_support_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_eventdispatcher_support_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_fb_support_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_fontdatabase_support_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_gamepad.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_gamepad_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_gui.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_gui_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_help.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_help_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_location.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_location_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_multimedia.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_multimedia_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_multimediawidgets.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_multimediawidgets_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_network.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_network_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_nfc.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_nfc_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_opengl.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_opengl_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_openglextensions.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_openglextensions_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_packetprotocol_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_platformcompositor_support_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_positioning.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_positioning_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_positioningquick.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_positioningquick_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_printsupport.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_printsupport_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_qml.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_qml_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_qmldebug_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_qmldevtools_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_qmltest.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_qmltest_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_qtmultimediaquicktools_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_quick.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_quick_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_quickcontrols2.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_quickcontrols2_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_quickparticles_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_quicktemplates2_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_quickwidgets.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_quickwidgets_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_scxml.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_scxml_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_sensors.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_sensors_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_serialbus.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_serialbus_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_serialport.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_serialport_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_sql.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_sql_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_svg.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_svg_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_testlib.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_testlib_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_texttospeech.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_texttospeech_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_theme_support_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_uiplugin.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_uitools.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_uitools_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_vulkan_support_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_webchannel.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_webchannel_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_websockets.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_websockets_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_webview.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_webview_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_widgets.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_widgets_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_windowsuiautomation_support_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_winextras.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_winextras_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_xml.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_xml_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_xmlpatterns.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_xmlpatterns_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_zlib_private.pri \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\features\qt_functions.prf \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\features\qt_config.prf \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\win32-msvc\qmake.conf \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\features\spec_post.prf \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\features\exclusive_builds.prf \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\common\msvc-version.conf \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\features\toolchain.prf \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\features\default_pre.prf \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\features\win32\default_pre.prf \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\features\resolve_config.prf \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\features\exclusive_builds_post.prf \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\features\default_post.prf \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\features\qml_debug.prf \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\features\precompile_header.prf \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\features\warn_on.prf \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\features\qt.prf \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\features\resources.prf \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\features\moc.prf \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\features\win32\opengl.prf \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\features\uic.prf \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\features\qmake_use.prf \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\features\file_copies.prf \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\features\win32\windows.prf \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\features\testcase_targets.prf \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\features\exceptions.prf \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\features\yacc.prf \
		G:\Qt\5.11.1\msvc2017_64\mkspecs\features\lex.prf \
		PIHMgis.pro \
		G:\Qt\5.11.1\msvc2017_64\lib\qtmaind.prl \
		G:\Qt\5.11.1\msvc2017_64\lib\Qt5PrintSupport.prl \
		G:\Qt\5.11.1\msvc2017_64\lib\Qt5Widgets.prl \
		G:\Qt\5.11.1\msvc2017_64\lib\Qt5Gui.prl \
		G:\Qt\5.11.1\msvc2017_64\lib\Qt5Core.prl
	$(QMAKE) -o Makefile PIHMgis.pro -spec win32-msvc "CONFIG+=debug" "CONFIG+=qml_debug"
G:\Qt\5.11.1\msvc2017_64\mkspecs\features\spec_pre.prf:
G:\Qt\5.11.1\msvc2017_64\mkspecs\common\angle.conf:
G:\Qt\5.11.1\msvc2017_64\mkspecs\common\windows-vulkan.conf:
G:\Qt\5.11.1\msvc2017_64\mkspecs\common\msvc-desktop.conf:
G:\Qt\5.11.1\msvc2017_64\mkspecs\qconfig.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_3danimation.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_3danimation_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_3dcore.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_3dcore_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_3dextras.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_3dextras_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_3dinput.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_3dinput_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_3dlogic.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_3dlogic_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_3dquick.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_3dquick_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_3dquickanimation.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_3dquickanimation_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_3dquickextras.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_3dquickextras_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_3dquickinput.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_3dquickinput_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_3dquickrender.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_3dquickrender_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_3dquickscene2d.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_3dquickscene2d_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_3drender.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_3drender_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_accessibility_support_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_axbase.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_axbase_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_axcontainer.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_axcontainer_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_axserver.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_axserver_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_bluetooth.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_bluetooth_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_bootstrap_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_charts.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_charts_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_concurrent.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_concurrent_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_core.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_core_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_datavisualization.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_datavisualization_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_dbus.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_dbus_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_designer.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_designer_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_designercomponents_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_devicediscovery_support_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_edid_support_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_egl_support_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_eventdispatcher_support_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_fb_support_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_fontdatabase_support_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_gamepad.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_gamepad_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_gui.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_gui_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_help.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_help_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_location.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_location_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_multimedia.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_multimedia_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_multimediawidgets.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_multimediawidgets_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_network.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_network_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_nfc.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_nfc_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_opengl.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_opengl_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_openglextensions.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_openglextensions_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_packetprotocol_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_platformcompositor_support_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_positioning.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_positioning_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_positioningquick.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_positioningquick_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_printsupport.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_printsupport_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_qml.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_qml_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_qmldebug_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_qmldevtools_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_qmltest.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_qmltest_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_qtmultimediaquicktools_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_quick.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_quick_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_quickcontrols2.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_quickcontrols2_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_quickparticles_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_quicktemplates2_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_quickwidgets.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_quickwidgets_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_scxml.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_scxml_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_sensors.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_sensors_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_serialbus.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_serialbus_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_serialport.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_serialport_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_sql.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_sql_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_svg.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_svg_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_testlib.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_testlib_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_texttospeech.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_texttospeech_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_theme_support_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_uiplugin.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_uitools.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_uitools_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_vulkan_support_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_webchannel.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_webchannel_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_websockets.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_websockets_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_webview.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_webview_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_widgets.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_widgets_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_windowsuiautomation_support_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_winextras.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_winextras_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_xml.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_xml_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_xmlpatterns.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_xmlpatterns_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\modules\qt_lib_zlib_private.pri:
G:\Qt\5.11.1\msvc2017_64\mkspecs\features\qt_functions.prf:
G:\Qt\5.11.1\msvc2017_64\mkspecs\features\qt_config.prf:
G:\Qt\5.11.1\msvc2017_64\mkspecs\win32-msvc\qmake.conf:
G:\Qt\5.11.1\msvc2017_64\mkspecs\features\spec_post.prf:
G:\Qt\5.11.1\msvc2017_64\mkspecs\features\exclusive_builds.prf:
G:\Qt\5.11.1\msvc2017_64\mkspecs\common\msvc-version.conf:
G:\Qt\5.11.1\msvc2017_64\mkspecs\features\toolchain.prf:
G:\Qt\5.11.1\msvc2017_64\mkspecs\features\default_pre.prf:
G:\Qt\5.11.1\msvc2017_64\mkspecs\features\win32\default_pre.prf:
G:\Qt\5.11.1\msvc2017_64\mkspecs\features\resolve_config.prf:
G:\Qt\5.11.1\msvc2017_64\mkspecs\features\exclusive_builds_post.prf:
G:\Qt\5.11.1\msvc2017_64\mkspecs\features\default_post.prf:
G:\Qt\5.11.1\msvc2017_64\mkspecs\features\qml_debug.prf:
G:\Qt\5.11.1\msvc2017_64\mkspecs\features\precompile_header.prf:
G:\Qt\5.11.1\msvc2017_64\mkspecs\features\warn_on.prf:
G:\Qt\5.11.1\msvc2017_64\mkspecs\features\qt.prf:
G:\Qt\5.11.1\msvc2017_64\mkspecs\features\resources.prf:
G:\Qt\5.11.1\msvc2017_64\mkspecs\features\moc.prf:
G:\Qt\5.11.1\msvc2017_64\mkspecs\features\win32\opengl.prf:
G:\Qt\5.11.1\msvc2017_64\mkspecs\features\uic.prf:
G:\Qt\5.11.1\msvc2017_64\mkspecs\features\qmake_use.prf:
G:\Qt\5.11.1\msvc2017_64\mkspecs\features\file_copies.prf:
G:\Qt\5.11.1\msvc2017_64\mkspecs\features\win32\windows.prf:
G:\Qt\5.11.1\msvc2017_64\mkspecs\features\testcase_targets.prf:
G:\Qt\5.11.1\msvc2017_64\mkspecs\features\exceptions.prf:
G:\Qt\5.11.1\msvc2017_64\mkspecs\features\yacc.prf:
G:\Qt\5.11.1\msvc2017_64\mkspecs\features\lex.prf:
PIHMgis.pro:
G:\Qt\5.11.1\msvc2017_64\lib\qtmaind.prl:
G:\Qt\5.11.1\msvc2017_64\lib\Qt5PrintSupport.prl:
G:\Qt\5.11.1\msvc2017_64\lib\Qt5Widgets.prl:
G:\Qt\5.11.1\msvc2017_64\lib\Qt5Gui.prl:
G:\Qt\5.11.1\msvc2017_64\lib\Qt5Core.prl:
qmake: FORCE
	@$(QMAKE) -o Makefile PIHMgis.pro -spec win32-msvc "CONFIG+=debug" "CONFIG+=qml_debug"

qmake_all: FORCE

make_first: debug-make_first release-make_first  FORCE
all: debug-all release-all  FORCE
clean: debug-clean release-clean  FORCE
	-$(DEL_FILE) PIHMgis.exp
	-$(DEL_FILE) PIHMgis.vc.pdb
	-$(DEL_FILE) PIHMgis.ilk
	-$(DEL_FILE) PIHMgis.idb
distclean: debug-distclean release-distclean  FORCE
	-$(DEL_FILE) Makefile
	-$(DEL_FILE) .qmake.stash PIHMgis.lib PIHMgis.pdb

debug-mocclean:
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Debug mocclean
release-mocclean:
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Release mocclean
mocclean: debug-mocclean release-mocclean

debug-mocables:
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Debug mocables
release-mocables:
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Release mocables
mocables: debug-mocables release-mocables

check: first

benchmark: first
FORCE:

$(MAKEFILE).Debug: Makefile
$(MAKEFILE).Release: Makefile
