# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.6.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.6.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/alexjohnson/Documents/CPSC385/Final Project"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/alexjohnson/Documents/CPSC385/Final Project"

# Include any dependencies generated for this target.
include CMakeFiles/EncryptImage.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/EncryptImage.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/EncryptImage.dir/flags.make

CMakeFiles/EncryptImage.dir/EncryptImage.cpp.o: CMakeFiles/EncryptImage.dir/flags.make
CMakeFiles/EncryptImage.dir/EncryptImage.cpp.o: EncryptImage.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/alexjohnson/Documents/CPSC385/Final Project/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/EncryptImage.dir/EncryptImage.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/EncryptImage.dir/EncryptImage.cpp.o -c "/Users/alexjohnson/Documents/CPSC385/Final Project/EncryptImage.cpp"

CMakeFiles/EncryptImage.dir/EncryptImage.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/EncryptImage.dir/EncryptImage.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/alexjohnson/Documents/CPSC385/Final Project/EncryptImage.cpp" > CMakeFiles/EncryptImage.dir/EncryptImage.cpp.i

CMakeFiles/EncryptImage.dir/EncryptImage.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/EncryptImage.dir/EncryptImage.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/alexjohnson/Documents/CPSC385/Final Project/EncryptImage.cpp" -o CMakeFiles/EncryptImage.dir/EncryptImage.cpp.s

CMakeFiles/EncryptImage.dir/EncryptImage.cpp.o.requires:

.PHONY : CMakeFiles/EncryptImage.dir/EncryptImage.cpp.o.requires

CMakeFiles/EncryptImage.dir/EncryptImage.cpp.o.provides: CMakeFiles/EncryptImage.dir/EncryptImage.cpp.o.requires
	$(MAKE) -f CMakeFiles/EncryptImage.dir/build.make CMakeFiles/EncryptImage.dir/EncryptImage.cpp.o.provides.build
.PHONY : CMakeFiles/EncryptImage.dir/EncryptImage.cpp.o.provides

CMakeFiles/EncryptImage.dir/EncryptImage.cpp.o.provides.build: CMakeFiles/EncryptImage.dir/EncryptImage.cpp.o


# Object files for target EncryptImage
EncryptImage_OBJECTS = \
"CMakeFiles/EncryptImage.dir/EncryptImage.cpp.o"

# External object files for target EncryptImage
EncryptImage_EXTERNAL_OBJECTS =

EncryptImage: CMakeFiles/EncryptImage.dir/EncryptImage.cpp.o
EncryptImage: CMakeFiles/EncryptImage.dir/build.make
EncryptImage: /usr/local/lib/libopencv_core.a
EncryptImage: /usr/local/lib/libopencv_flann.a
EncryptImage: /usr/local/lib/libopencv_imgproc.a
EncryptImage: /usr/local/lib/libopencv_highgui.a
EncryptImage: /usr/local/lib/libopencv_features2d.a
EncryptImage: /usr/local/lib/libopencv_calib3d.a
EncryptImage: /usr/local/lib/libopencv_ml.a
EncryptImage: /usr/local/lib/libopencv_video.a
EncryptImage: /usr/local/lib/libopencv_legacy.a
EncryptImage: /usr/local/lib/libopencv_objdetect.a
EncryptImage: /usr/local/lib/libopencv_photo.a
EncryptImage: /usr/local/lib/libopencv_gpu.a
EncryptImage: /usr/local/lib/libopencv_videostab.a
EncryptImage: /usr/local/lib/libopencv_ts.a
EncryptImage: /usr/local/lib/libopencv_ocl.a
EncryptImage: /usr/local/lib/libopencv_superres.a
EncryptImage: /usr/local/lib/libopencv_nonfree.a
EncryptImage: /usr/local/lib/libopencv_stitching.a
EncryptImage: /usr/local/lib/libopencv_contrib.a
EncryptImage: /usr/local/lib/libopencv_nonfree.a
EncryptImage: /usr/local/lib/libopencv_gpu.a
EncryptImage: /usr/local/lib/libopencv_legacy.a
EncryptImage: /usr/local/lib/libopencv_photo.a
EncryptImage: /usr/local/lib/libopencv_ocl.a
EncryptImage: /usr/local/lib/libopencv_calib3d.a
EncryptImage: /usr/local/lib/libopencv_features2d.a
EncryptImage: /usr/local/lib/libopencv_flann.a
EncryptImage: /usr/local/lib/libopencv_ml.a
EncryptImage: /usr/local/lib/libopencv_video.a
EncryptImage: /usr/local/lib/libopencv_objdetect.a
EncryptImage: /usr/local/lib/libopencv_highgui.a
EncryptImage: /usr/local/lib/libopencv_imgproc.a
EncryptImage: /usr/local/lib/libopencv_core.a
EncryptImage: /usr/local/share/OpenCV/3rdparty/lib/liblibjpeg.a
EncryptImage: /usr/local/share/OpenCV/3rdparty/lib/liblibpng.a
EncryptImage: /usr/local/share/OpenCV/3rdparty/lib/liblibtiff.a
EncryptImage: /usr/local/share/OpenCV/3rdparty/lib/liblibjasper.a
EncryptImage: /usr/local/share/OpenCV/3rdparty/lib/libIlmImf.a
EncryptImage: /usr/local/share/OpenCV/3rdparty/lib/libzlib.a
EncryptImage: CMakeFiles/EncryptImage.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/alexjohnson/Documents/CPSC385/Final Project/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable EncryptImage"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/EncryptImage.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/EncryptImage.dir/build: EncryptImage

.PHONY : CMakeFiles/EncryptImage.dir/build

CMakeFiles/EncryptImage.dir/requires: CMakeFiles/EncryptImage.dir/EncryptImage.cpp.o.requires

.PHONY : CMakeFiles/EncryptImage.dir/requires

CMakeFiles/EncryptImage.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/EncryptImage.dir/cmake_clean.cmake
.PHONY : CMakeFiles/EncryptImage.dir/clean

CMakeFiles/EncryptImage.dir/depend:
	cd "/Users/alexjohnson/Documents/CPSC385/Final Project" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/alexjohnson/Documents/CPSC385/Final Project" "/Users/alexjohnson/Documents/CPSC385/Final Project" "/Users/alexjohnson/Documents/CPSC385/Final Project" "/Users/alexjohnson/Documents/CPSC385/Final Project" "/Users/alexjohnson/Documents/CPSC385/Final Project/CMakeFiles/EncryptImage.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/EncryptImage.dir/depend

