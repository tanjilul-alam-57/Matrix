cmake_minimum_required (VERSION 3.16)

project (Matrix)


#include necessary configuration files
include(CMake/Settings/CMakeSettings.cmake)
include(CMake/Macros/CMakeMacros.cmake)
include(CMake/Macros/GenerateExportHeader.cmake)
include(CMake/Macros/PrecompiledHeaders.cmake)

#import thirdparty libraries
#include(CMake/Import/ImportQt5.cmake)


#add projects
add_subdirectory (Application )


