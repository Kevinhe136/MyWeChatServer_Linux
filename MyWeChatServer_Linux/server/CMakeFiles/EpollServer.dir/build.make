# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/kevin/MyProgram/MyWeChatServer_Linux/server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kevin/MyProgram/MyWeChatServer_Linux/server

# Include any dependencies generated for this target.
include CMakeFiles/EpollServer.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/EpollServer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/EpollServer.dir/flags.make

CMakeFiles/EpollServer.dir/MyEpollPort.cpp.o: CMakeFiles/EpollServer.dir/flags.make
CMakeFiles/EpollServer.dir/MyEpollPort.cpp.o: MyEpollPort.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kevin/MyProgram/MyWeChatServer_Linux/server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/EpollServer.dir/MyEpollPort.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/EpollServer.dir/MyEpollPort.cpp.o -c /home/kevin/MyProgram/MyWeChatServer_Linux/server/MyEpollPort.cpp

CMakeFiles/EpollServer.dir/MyEpollPort.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/EpollServer.dir/MyEpollPort.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kevin/MyProgram/MyWeChatServer_Linux/server/MyEpollPort.cpp > CMakeFiles/EpollServer.dir/MyEpollPort.cpp.i

CMakeFiles/EpollServer.dir/MyEpollPort.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/EpollServer.dir/MyEpollPort.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kevin/MyProgram/MyWeChatServer_Linux/server/MyEpollPort.cpp -o CMakeFiles/EpollServer.dir/MyEpollPort.cpp.s

CMakeFiles/EpollServer.dir/MyEpollPort.cpp.o.requires:

.PHONY : CMakeFiles/EpollServer.dir/MyEpollPort.cpp.o.requires

CMakeFiles/EpollServer.dir/MyEpollPort.cpp.o.provides: CMakeFiles/EpollServer.dir/MyEpollPort.cpp.o.requires
	$(MAKE) -f CMakeFiles/EpollServer.dir/build.make CMakeFiles/EpollServer.dir/MyEpollPort.cpp.o.provides.build
.PHONY : CMakeFiles/EpollServer.dir/MyEpollPort.cpp.o.provides

CMakeFiles/EpollServer.dir/MyEpollPort.cpp.o.provides.build: CMakeFiles/EpollServer.dir/MyEpollPort.cpp.o


CMakeFiles/EpollServer.dir/main.cpp.o: CMakeFiles/EpollServer.dir/flags.make
CMakeFiles/EpollServer.dir/main.cpp.o: main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kevin/MyProgram/MyWeChatServer_Linux/server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/EpollServer.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/EpollServer.dir/main.cpp.o -c /home/kevin/MyProgram/MyWeChatServer_Linux/server/main.cpp

CMakeFiles/EpollServer.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/EpollServer.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kevin/MyProgram/MyWeChatServer_Linux/server/main.cpp > CMakeFiles/EpollServer.dir/main.cpp.i

CMakeFiles/EpollServer.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/EpollServer.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kevin/MyProgram/MyWeChatServer_Linux/server/main.cpp -o CMakeFiles/EpollServer.dir/main.cpp.s

CMakeFiles/EpollServer.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/EpollServer.dir/main.cpp.o.requires

CMakeFiles/EpollServer.dir/main.cpp.o.provides: CMakeFiles/EpollServer.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/EpollServer.dir/build.make CMakeFiles/EpollServer.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/EpollServer.dir/main.cpp.o.provides

CMakeFiles/EpollServer.dir/main.cpp.o.provides.build: CMakeFiles/EpollServer.dir/main.cpp.o


# Object files for target EpollServer
EpollServer_OBJECTS = \
"CMakeFiles/EpollServer.dir/MyEpollPort.cpp.o" \
"CMakeFiles/EpollServer.dir/main.cpp.o"

# External object files for target EpollServer
EpollServer_EXTERNAL_OBJECTS =

EpollServer: CMakeFiles/EpollServer.dir/MyEpollPort.cpp.o
EpollServer: CMakeFiles/EpollServer.dir/main.cpp.o
EpollServer: CMakeFiles/EpollServer.dir/build.make
EpollServer: CMakeFiles/EpollServer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kevin/MyProgram/MyWeChatServer_Linux/server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable EpollServer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/EpollServer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/EpollServer.dir/build: EpollServer

.PHONY : CMakeFiles/EpollServer.dir/build

CMakeFiles/EpollServer.dir/requires: CMakeFiles/EpollServer.dir/MyEpollPort.cpp.o.requires
CMakeFiles/EpollServer.dir/requires: CMakeFiles/EpollServer.dir/main.cpp.o.requires

.PHONY : CMakeFiles/EpollServer.dir/requires

CMakeFiles/EpollServer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/EpollServer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/EpollServer.dir/clean

CMakeFiles/EpollServer.dir/depend:
	cd /home/kevin/MyProgram/MyWeChatServer_Linux/server && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kevin/MyProgram/MyWeChatServer_Linux/server /home/kevin/MyProgram/MyWeChatServer_Linux/server /home/kevin/MyProgram/MyWeChatServer_Linux/server /home/kevin/MyProgram/MyWeChatServer_Linux/server /home/kevin/MyProgram/MyWeChatServer_Linux/server/CMakeFiles/EpollServer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/EpollServer.dir/depend

