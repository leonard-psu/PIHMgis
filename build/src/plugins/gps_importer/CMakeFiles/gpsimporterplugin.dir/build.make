# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.4

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
.SUFFIXES:

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/build

# Include any dependencies generated for this target.
include src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/depend.make

# Include the progress variables for this target.
include src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/progress.make

# Include the compile flags for this target's objects.
include src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/flags.make

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/depend.make.mark: src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/flags.make
src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/depend.make.mark: ../src/plugins/gps_importer/qgsgpsplugin.cpp

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsplugin.o: src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/flags.make
src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsplugin.o: ../src/plugins/gps_importer/qgsgpsplugin.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsplugin.o"
	/usr/bin/c++   $(CXX_FLAGS) -o src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsplugin.o -c /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/src/plugins/gps_importer/qgsgpsplugin.cpp

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsplugin.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsplugin.i"
	/usr/bin/c++  $(CXX_FLAGS) -E /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/src/plugins/gps_importer/qgsgpsplugin.cpp > src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsplugin.i

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsplugin.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsplugin.s"
	/usr/bin/c++  $(CXX_FLAGS) -S /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/src/plugins/gps_importer/qgsgpsplugin.cpp -o src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsplugin.s

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsplugin.o.requires:

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsplugin.o.provides: src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsplugin.o.requires
	$(MAKE) -f src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/build.make src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsplugin.o.provides.build

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsplugin.o.provides.build: src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsplugin.o

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/depend.make.mark: src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/flags.make
src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/depend.make.mark: ../src/plugins/gps_importer/qgsbabelformat.cpp

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsbabelformat.o: src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/flags.make
src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsbabelformat.o: ../src/plugins/gps_importer/qgsbabelformat.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsbabelformat.o"
	/usr/bin/c++   $(CXX_FLAGS) -o src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsbabelformat.o -c /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/src/plugins/gps_importer/qgsbabelformat.cpp

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsbabelformat.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsbabelformat.i"
	/usr/bin/c++  $(CXX_FLAGS) -E /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/src/plugins/gps_importer/qgsbabelformat.cpp > src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsbabelformat.i

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsbabelformat.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsbabelformat.s"
	/usr/bin/c++  $(CXX_FLAGS) -S /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/src/plugins/gps_importer/qgsbabelformat.cpp -o src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsbabelformat.s

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsbabelformat.o.requires:

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsbabelformat.o.provides: src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsbabelformat.o.requires
	$(MAKE) -f src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/build.make src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsbabelformat.o.provides.build

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsbabelformat.o.provides.build: src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsbabelformat.o

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/depend.make.mark: src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/flags.make
src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/depend.make.mark: ../src/plugins/gps_importer/qgsgpsdevice.cpp

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsdevice.o: src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/flags.make
src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsdevice.o: ../src/plugins/gps_importer/qgsgpsdevice.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsdevice.o"
	/usr/bin/c++   $(CXX_FLAGS) -o src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsdevice.o -c /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/src/plugins/gps_importer/qgsgpsdevice.cpp

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsdevice.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsdevice.i"
	/usr/bin/c++  $(CXX_FLAGS) -E /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/src/plugins/gps_importer/qgsgpsdevice.cpp > src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsdevice.i

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsdevice.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsdevice.s"
	/usr/bin/c++  $(CXX_FLAGS) -S /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/src/plugins/gps_importer/qgsgpsdevice.cpp -o src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsdevice.s

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsdevice.o.requires:

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsdevice.o.provides: src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsdevice.o.requires
	$(MAKE) -f src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/build.make src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsdevice.o.provides.build

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsdevice.o.provides.build: src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsdevice.o

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/depend.make.mark: src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/flags.make
src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/depend.make.mark: ../src/plugins/gps_importer/qgsgpsplugingui.cpp

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsplugingui.o: src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/flags.make
src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsplugingui.o: ../src/plugins/gps_importer/qgsgpsplugingui.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsplugingui.o"
	/usr/bin/c++   $(CXX_FLAGS) -o src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsplugingui.o -c /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/src/plugins/gps_importer/qgsgpsplugingui.cpp

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsplugingui.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsplugingui.i"
	/usr/bin/c++  $(CXX_FLAGS) -E /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/src/plugins/gps_importer/qgsgpsplugingui.cpp > src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsplugingui.i

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsplugingui.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsplugingui.s"
	/usr/bin/c++  $(CXX_FLAGS) -S /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/src/plugins/gps_importer/qgsgpsplugingui.cpp -o src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsplugingui.s

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsplugingui.o.requires:

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsplugingui.o.provides: src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsplugingui.o.requires
	$(MAKE) -f src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/build.make src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsplugingui.o.provides.build

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsplugingui.o.provides.build: src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsplugingui.o

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/depend.make.mark: src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/flags.make
src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/depend.make.mark: ../src/plugins/gps_importer/qgsgpsdevicedialog.cpp

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsdevicedialog.o: src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/flags.make
src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsdevicedialog.o: ../src/plugins/gps_importer/qgsgpsdevicedialog.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsdevicedialog.o"
	/usr/bin/c++   $(CXX_FLAGS) -o src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsdevicedialog.o -c /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/src/plugins/gps_importer/qgsgpsdevicedialog.cpp

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsdevicedialog.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsdevicedialog.i"
	/usr/bin/c++  $(CXX_FLAGS) -E /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/src/plugins/gps_importer/qgsgpsdevicedialog.cpp > src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsdevicedialog.i

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsdevicedialog.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsdevicedialog.s"
	/usr/bin/c++  $(CXX_FLAGS) -S /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/src/plugins/gps_importer/qgsgpsdevicedialog.cpp -o src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsdevicedialog.s

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsdevicedialog.o.requires:

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsdevicedialog.o.provides: src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsdevicedialog.o.requires
	$(MAKE) -f src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/build.make src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsdevicedialog.o.provides.build

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsdevicedialog.o.provides.build: src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsdevicedialog.o

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/depend.make.mark: src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/flags.make
src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/depend.make.mark: src/plugins/gps_importer/moc_qgsgpsplugin.cxx

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/moc_qgsgpsplugin.o: src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/flags.make
src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/moc_qgsgpsplugin.o: src/plugins/gps_importer/moc_qgsgpsplugin.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/build/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/moc_qgsgpsplugin.o"
	/usr/bin/c++   $(CXX_FLAGS) -o src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/moc_qgsgpsplugin.o -c /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/build/src/plugins/gps_importer/moc_qgsgpsplugin.cxx

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/moc_qgsgpsplugin.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/moc_qgsgpsplugin.i"
	/usr/bin/c++  $(CXX_FLAGS) -E /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/build/src/plugins/gps_importer/moc_qgsgpsplugin.cxx > src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/moc_qgsgpsplugin.i

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/moc_qgsgpsplugin.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/moc_qgsgpsplugin.s"
	/usr/bin/c++  $(CXX_FLAGS) -S /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/build/src/plugins/gps_importer/moc_qgsgpsplugin.cxx -o src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/moc_qgsgpsplugin.s

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/moc_qgsgpsplugin.o.requires:

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/moc_qgsgpsplugin.o.provides: src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/moc_qgsgpsplugin.o.requires
	$(MAKE) -f src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/build.make src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/moc_qgsgpsplugin.o.provides.build

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/moc_qgsgpsplugin.o.provides.build: src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/moc_qgsgpsplugin.o

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/depend.make.mark: src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/flags.make
src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/depend.make.mark: src/plugins/gps_importer/moc_qgsgpsplugingui.cxx

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/moc_qgsgpsplugingui.o: src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/flags.make
src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/moc_qgsgpsplugingui.o: src/plugins/gps_importer/moc_qgsgpsplugingui.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/build/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/moc_qgsgpsplugingui.o"
	/usr/bin/c++   $(CXX_FLAGS) -o src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/moc_qgsgpsplugingui.o -c /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/build/src/plugins/gps_importer/moc_qgsgpsplugingui.cxx

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/moc_qgsgpsplugingui.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/moc_qgsgpsplugingui.i"
	/usr/bin/c++  $(CXX_FLAGS) -E /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/build/src/plugins/gps_importer/moc_qgsgpsplugingui.cxx > src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/moc_qgsgpsplugingui.i

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/moc_qgsgpsplugingui.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/moc_qgsgpsplugingui.s"
	/usr/bin/c++  $(CXX_FLAGS) -S /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/build/src/plugins/gps_importer/moc_qgsgpsplugingui.cxx -o src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/moc_qgsgpsplugingui.s

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/moc_qgsgpsplugingui.o.requires:

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/moc_qgsgpsplugingui.o.provides: src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/moc_qgsgpsplugingui.o.requires
	$(MAKE) -f src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/build.make src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/moc_qgsgpsplugingui.o.provides.build

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/moc_qgsgpsplugingui.o.provides.build: src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/moc_qgsgpsplugingui.o

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/depend.make.mark: src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/flags.make
src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/depend.make.mark: src/plugins/gps_importer/moc_qgsgpsdevicedialog.cxx

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/moc_qgsgpsdevicedialog.o: src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/flags.make
src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/moc_qgsgpsdevicedialog.o: src/plugins/gps_importer/moc_qgsgpsdevicedialog.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/build/CMakeFiles $(CMAKE_PROGRESS_8)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/moc_qgsgpsdevicedialog.o"
	/usr/bin/c++   $(CXX_FLAGS) -o src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/moc_qgsgpsdevicedialog.o -c /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/build/src/plugins/gps_importer/moc_qgsgpsdevicedialog.cxx

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/moc_qgsgpsdevicedialog.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/moc_qgsgpsdevicedialog.i"
	/usr/bin/c++  $(CXX_FLAGS) -E /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/build/src/plugins/gps_importer/moc_qgsgpsdevicedialog.cxx > src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/moc_qgsgpsdevicedialog.i

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/moc_qgsgpsdevicedialog.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/moc_qgsgpsdevicedialog.s"
	/usr/bin/c++  $(CXX_FLAGS) -S /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/build/src/plugins/gps_importer/moc_qgsgpsdevicedialog.cxx -o src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/moc_qgsgpsdevicedialog.s

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/moc_qgsgpsdevicedialog.o.requires:

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/moc_qgsgpsdevicedialog.o.provides: src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/moc_qgsgpsdevicedialog.o.requires
	$(MAKE) -f src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/build.make src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/moc_qgsgpsdevicedialog.o.provides.build

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/moc_qgsgpsdevicedialog.o.provides.build: src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/moc_qgsgpsdevicedialog.o

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/depend.make.mark: src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/flags.make
src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/depend.make.mark: src/plugins/gps_importer/qrc_qgsgps_plugin.cxx

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qrc_qgsgps_plugin.o: src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/flags.make
src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qrc_qgsgps_plugin.o: src/plugins/gps_importer/qrc_qgsgps_plugin.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/build/CMakeFiles $(CMAKE_PROGRESS_9)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qrc_qgsgps_plugin.o"
	/usr/bin/c++   $(CXX_FLAGS) -o src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qrc_qgsgps_plugin.o -c /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/build/src/plugins/gps_importer/qrc_qgsgps_plugin.cxx

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qrc_qgsgps_plugin.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qrc_qgsgps_plugin.i"
	/usr/bin/c++  $(CXX_FLAGS) -E /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/build/src/plugins/gps_importer/qrc_qgsgps_plugin.cxx > src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qrc_qgsgps_plugin.i

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qrc_qgsgps_plugin.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qrc_qgsgps_plugin.s"
	/usr/bin/c++  $(CXX_FLAGS) -S /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/build/src/plugins/gps_importer/qrc_qgsgps_plugin.cxx -o src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qrc_qgsgps_plugin.s

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qrc_qgsgps_plugin.o.requires:

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qrc_qgsgps_plugin.o.provides: src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qrc_qgsgps_plugin.o.requires
	$(MAKE) -f src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/build.make src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qrc_qgsgps_plugin.o.provides.build

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qrc_qgsgps_plugin.o.provides.build: src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qrc_qgsgps_plugin.o

src/plugins/gps_importer/moc_qgsgpsplugin.cxx: ../src/plugins/gps_importer/qgsgpsplugin.h
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/build/CMakeFiles $(CMAKE_PROGRESS_10)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating moc_qgsgpsplugin.cxx"
	cd /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/build/src/plugins/gps_importer && /Developer/Tools/Qt/moc -I /usr/include -I /Library/Frameworks/Qt3Support.framework/Headers -I /Library/Frameworks/QtSvg.framework/Headers -I /Library/Frameworks/QtGui.framework/Headers -I /Library/Frameworks/QtXml.framework/Headers -I /Library/Frameworks/QtSql.framework/Headers -I /Library/Frameworks/QtNetwork.framework/Headers -I /Library/Frameworks/QtCore.framework/Headers -I /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/build -o /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/build/src/plugins/gps_importer/moc_qgsgpsplugin.cxx /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/src/plugins/gps_importer/qgsgpsplugin.h

src/plugins/gps_importer/moc_qgsgpsplugingui.cxx: ../src/plugins/gps_importer/qgsgpsplugingui.h
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/build/CMakeFiles $(CMAKE_PROGRESS_11)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating moc_qgsgpsplugingui.cxx"
	cd /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/build/src/plugins/gps_importer && /Developer/Tools/Qt/moc -I /usr/include -I /Library/Frameworks/Qt3Support.framework/Headers -I /Library/Frameworks/QtSvg.framework/Headers -I /Library/Frameworks/QtGui.framework/Headers -I /Library/Frameworks/QtXml.framework/Headers -I /Library/Frameworks/QtSql.framework/Headers -I /Library/Frameworks/QtNetwork.framework/Headers -I /Library/Frameworks/QtCore.framework/Headers -I /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/build -o /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/build/src/plugins/gps_importer/moc_qgsgpsplugingui.cxx /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/src/plugins/gps_importer/qgsgpsplugingui.h

src/plugins/gps_importer/moc_qgsgpsdevicedialog.cxx: ../src/plugins/gps_importer/qgsgpsdevicedialog.h
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/build/CMakeFiles $(CMAKE_PROGRESS_12)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating moc_qgsgpsdevicedialog.cxx"
	cd /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/build/src/plugins/gps_importer && /Developer/Tools/Qt/moc -I /usr/include -I /Library/Frameworks/Qt3Support.framework/Headers -I /Library/Frameworks/QtSvg.framework/Headers -I /Library/Frameworks/QtGui.framework/Headers -I /Library/Frameworks/QtXml.framework/Headers -I /Library/Frameworks/QtSql.framework/Headers -I /Library/Frameworks/QtNetwork.framework/Headers -I /Library/Frameworks/QtCore.framework/Headers -I /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/build -o /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/build/src/plugins/gps_importer/moc_qgsgpsdevicedialog.cxx /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/src/plugins/gps_importer/qgsgpsdevicedialog.h

src/plugins/gps_importer/qrc_qgsgps_plugin.cxx: ../src/plugins/gps_importer/gps.xpm
src/plugins/gps_importer/qrc_qgsgps_plugin.cxx: ../src/plugins/gps_importer/qgsgps_plugin.qrc
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/build/CMakeFiles $(CMAKE_PROGRESS_13)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating qrc_qgsgps_plugin.cxx"
	cd /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/build/src/plugins/gps_importer && /Developer/Tools/Qt/rcc -name qgsgps_plugin -o /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/build/src/plugins/gps_importer/qrc_qgsgps_plugin.cxx /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/src/plugins/gps_importer/qgsgps_plugin.qrc

src/plugins/gps_importer/ui_qgsgpspluginguibase.h: ../src/plugins/gps_importer/qgsgpspluginguibase.ui
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/build/CMakeFiles $(CMAKE_PROGRESS_14)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating ui_qgsgpspluginguibase.h"
	cd /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/build/src/plugins/gps_importer && /Developer/Tools/Qt/uic -o /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/build/src/plugins/gps_importer/ui_qgsgpspluginguibase.h /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/src/plugins/gps_importer/qgsgpspluginguibase.ui

src/plugins/gps_importer/ui_qgsgpsdevicedialogbase.h: ../src/plugins/gps_importer/qgsgpsdevicedialogbase.ui
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/build/CMakeFiles $(CMAKE_PROGRESS_15)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating ui_qgsgpsdevicedialogbase.h"
	cd /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/build/src/plugins/gps_importer && /Developer/Tools/Qt/uic -o /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/build/src/plugins/gps_importer/ui_qgsgpsdevicedialogbase.h /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/src/plugins/gps_importer/qgsgpsdevicedialogbase.ui

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/depend: src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/depend.make.mark

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/depend.make.mark: src/plugins/gps_importer/moc_qgsgpsplugin.cxx
src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/depend.make.mark: src/plugins/gps_importer/moc_qgsgpsplugingui.cxx
src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/depend.make.mark: src/plugins/gps_importer/moc_qgsgpsdevicedialog.cxx
src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/depend.make.mark: src/plugins/gps_importer/qrc_qgsgps_plugin.cxx
src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/depend.make.mark: src/plugins/gps_importer/ui_qgsgpspluginguibase.h
src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/depend.make.mark: src/plugins/gps_importer/ui_qgsgpsdevicedialogbase.h
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --magenta --bold "Scanning dependencies of target gpsimporterplugin"
	cd /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0 /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/src/plugins/gps_importer /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/build /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/build/src/plugins/gps_importer /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/build/src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/DependInfo.cmake

# Object files for target gpsimporterplugin
gpsimporterplugin_OBJECTS = \
"CMakeFiles/gpsimporterplugin.dir/qgsgpsplugin.o" \
"CMakeFiles/gpsimporterplugin.dir/qgsbabelformat.o" \
"CMakeFiles/gpsimporterplugin.dir/qgsgpsdevice.o" \
"CMakeFiles/gpsimporterplugin.dir/qgsgpsplugingui.o" \
"CMakeFiles/gpsimporterplugin.dir/qgsgpsdevicedialog.o" \
"CMakeFiles/gpsimporterplugin.dir/moc_qgsgpsplugin.o" \
"CMakeFiles/gpsimporterplugin.dir/moc_qgsgpsplugingui.o" \
"CMakeFiles/gpsimporterplugin.dir/moc_qgsgpsdevicedialog.o" \
"CMakeFiles/gpsimporterplugin.dir/qrc_qgsgps_plugin.o"

# External object files for target gpsimporterplugin
gpsimporterplugin_EXTERNAL_OBJECTS =

src/plugins/gps_importer/libgpsimporterplugin.so: src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsplugin.o
src/plugins/gps_importer/libgpsimporterplugin.so: src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsbabelformat.o
src/plugins/gps_importer/libgpsimporterplugin.so: src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsdevice.o
src/plugins/gps_importer/libgpsimporterplugin.so: src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsplugingui.o
src/plugins/gps_importer/libgpsimporterplugin.so: src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsdevicedialog.o
src/plugins/gps_importer/libgpsimporterplugin.so: src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/moc_qgsgpsplugin.o
src/plugins/gps_importer/libgpsimporterplugin.so: src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/moc_qgsgpsplugingui.o
src/plugins/gps_importer/libgpsimporterplugin.so: src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/moc_qgsgpsdevicedialog.o
src/plugins/gps_importer/libgpsimporterplugin.so: src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qrc_qgsgps_plugin.o
src/plugins/gps_importer/libgpsimporterplugin.so: /Library/Frameworks/Qt3Support.framework
src/plugins/gps_importer/libgpsimporterplugin.so: /Library/Frameworks/QtSvg.framework
src/plugins/gps_importer/libgpsimporterplugin.so: /Library/Frameworks/QtGui.framework
src/plugins/gps_importer/libgpsimporterplugin.so: /Library/Frameworks/QtXml.framework
src/plugins/gps_importer/libgpsimporterplugin.so: /Library/Frameworks/QtSql.framework
src/plugins/gps_importer/libgpsimporterplugin.so: /Library/Frameworks/QtNetwork.framework
src/plugins/gps_importer/libgpsimporterplugin.so: /Library/Frameworks/QtCore.framework
src/plugins/gps_importer/libgpsimporterplugin.so: /usr/lib/libz.dylib
src/plugins/gps_importer/libgpsimporterplugin.so: src/core/libqgis_core.dylib
src/plugins/gps_importer/libgpsimporterplugin.so: src/gui/libqgis_gui.dylib
src/plugins/gps_importer/libgpsimporterplugin.so: /Library/Frameworks/proj.framework
src/plugins/gps_importer/libgpsimporterplugin.so: /Library/Frameworks/sqlite3.framework
src/plugins/gps_importer/libgpsimporterplugin.so: /Library/Frameworks/geos.framework
src/plugins/gps_importer/libgpsimporterplugin.so: /Library/Frameworks/GDAL.framework/Versions/1.5/unix/lib/libgdal.dylib
src/plugins/gps_importer/libgpsimporterplugin.so: src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/build.make
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared module libgpsimporterplugin.so"
	cd /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/build/src/plugins/gps_importer && $(CMAKE_COMMAND) -P CMakeFiles/gpsimporterplugin.dir/cmake_clean_target.cmake
	cd /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/build/src/plugins/gps_importer && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gpsimporterplugin.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/build: src/plugins/gps_importer/libgpsimporterplugin.so

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/requires: src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsplugin.o.requires
src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/requires: src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsbabelformat.o.requires
src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/requires: src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsdevice.o.requires
src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/requires: src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsplugingui.o.requires
src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/requires: src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qgsgpsdevicedialog.o.requires
src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/requires: src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/moc_qgsgpsplugin.o.requires
src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/requires: src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/moc_qgsgpsplugingui.o.requires
src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/requires: src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/moc_qgsgpsdevicedialog.o.requires
src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/requires: src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/qrc_qgsgps_plugin.o.requires

src/plugins/gps_importer/CMakeFiles/gpsimporterplugin.dir/clean:
	cd /Users/bhattgopal/dev/cpp/qgis0.9_pihm2.0/build/src/plugins/gps_importer && $(CMAKE_COMMAND) -P CMakeFiles/gpsimporterplugin.dir/cmake_clean.cmake

