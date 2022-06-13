
set(CMAKE_CONFIGURATION_TYPES Debug Release)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

###############################################################################
# Determine architecture
#
# You can set the architecture via enironment variable.
# Just "set ARCHITECTURE=x86" on Windows or "export ARCHITECTURE=x86" on
# Linux before calling CMake
# (Enironment variable will be stored in the current environment)
# This is mainly important for the correct Program Files / Qt folder on Windows
# and the correct folders on Linux for x86 / arm.
###############################################################################

# default values
set (ARCHITECTURE_STR "x64")
set (ARCHITECTURE_QT "64")
set (ARCHITECTURE_X86 FALSE)
set (ARCHITECTURE_X64 TRUE)

if (DEFINED ENV{ARCHITECTURE})
  if ("$ENV{ARCHITECTURE}" STREQUAL "x86")
    set (ARCHITECTURE_X86 TRUE)
    set (ARCHITECTURE_X64 FALSE)
    set (ARCHITECTURE_STR "x86")
  endif ("$ENV{ARCHITECTURE}" STREQUAL "x86")

  IF (!WIN32)
    if ("$ENV{ARCHITECTURE}" STREQUAL "arm")
      set (ARCHITECTURE_ARM TRUE)
      set (ARCHITECTURE_X64 FALSE)
      set (LINUX_ARM_PROCESSOR TRUE)
      set (ARCHITECTURE_STR "arm")
    endif ("$ENV{ARCHITECTURE}" STREQUAL "arm")
  endif (!WIN32)
else()
  string (FIND ${CMAKE_GENERATOR} "Visual Studio" FLAG_VISUALSTUDIO)
  string (FIND ${CMAKE_GENERATOR} "Win64" FLAG_64BIT)
  IF (FLAG_VISUALSTUDIO GREATER -1)
    IF (FLAG_64BIT GREATER -1)
    ELSE()
      set (ARCHITECTURE_X86 TRUE)
      set (ARCHITECTURE_X64 FALSE)
      set (ARCHITECTURE_STR "x86")
    ENDIF()
  ENDIF()
ENDIF()

###############################################################################

set (TSEP_PROJECT_NAME ${PROJECT_NAME})
set (TSEP_SOURCE_DIR ${PROJECT_SOURCE_DIR})
set (TSEP_BINARY_DIR ${PROJECT_BINARY_DIR})

set (VXI_EXTERN_INCLUDE ${PROJECT_SOURCE_DIR}/../External)
set (COMMON_EXTERN_INCLUDE ${PROJECT_SOURCE_DIR}/../../Common)

###############################################################################
# PROJECT SPECIFIC VARIABLES
###############################################################################

if (WIN32)
  # set directory where to find Qt
  #set (TSEP_QT_DIR  D:/NugetCache/artifacts/Qt/x64-vs15/5.12.3.0)
  #set (TSEP_QT_DIR  D:/Qt/Qt5.9.6/5.9.6/msvc2017_64)
                 
  # set target directory for build process
  set (TSEP_TARGET_DIR ${CMAKE_BINARY_DIR}/$(Configuration))
  
else ()
  # set target directory for build process
  set (TSEP_TARGET_DIR ${CMAKE_BINARY_DIR})  
  
endif ()

IF (WIN32)

  ###############################################################################
  # COMPILER SETTINGS
  ###############################################################################
  # Standard CMake options set
  # /D_DEBUG for Debug; /DNDEBUG for Release
  # /D_WINDOWS
  # /MDd for Debug; /MD for Release
  # /Od for Debug; /O2 for Release

  # Compiler Warning level 4
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W4")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4" CACHE STRING "")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W4" CACHE STRING "")

  add_definitions(
		/DUNICODE
		/D_UNICODE
		/DWIN32_LEAN_AND_MEAN
		# set Minimum system required to (0x06010000) = W7 
		/D_WIN32_WINNT=0x06010000
		/DNOMINMAX
    		  )

###############################################################################

  # set stuff for windows

  set ( CMAKE_QTDIR ${TSEP_QT_DIR})

ELSE()

  # Compiler Warning level 4
  # "visibility=hidden": hide all symbols in object files per default
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -fvisibility=hidden")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic -fvisibility=hidden")

  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")
  set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -D_DEBUG")

  # preprocessor definitions
  add_definitions(
    /Dlinux_i386
    /D_${CFG_FLAG}
  )

  # this setting is necessary at least for static libraries. Set it general.
  # set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)  is not enough for Qt
  #add_compile_options(-fPIC)
ENDIF()


###############################################################################
# SET OUTPUT DIRECTORIES for exe, dll, lib and pdb files
###############################################################################

IF (WIN32)
  # set stuff for windows
  set ( RUN_OUT_DIR ${TSEP_TARGET_DIR}/bin)
  set ( LIB_OUT_DIR ${RUN_OUT_DIR})
  set ( ARCH_OUT_DIR ${RUN_OUT_DIR})
  set ( PDB_OUT_DIR ${RUN_OUT_DIR})
ELSE()
  # set stuff for linux systems
  set ( RUN_OUT_DIR ${TSEP_TARGET_DIR}/bin)
  set ( LIB_OUT_DIR ${RUN_OUT_DIR})
  set ( ARCH_OUT_DIR ${RUN_OUT_DIR})
  set ( PDB_OUT_DIR ${RUN_OUT_DIR})
ENDIF()

# must set directories for each configuration,
# otherwise CMake adds /Configuration at the end of directory.
foreach (CONFIG ${CMAKE_CONFIGURATION_TYPES})
  # make configuration variable upper case for CMAKE macros
  string(TOUPPER ${CONFIG} CONFIGUPPERCASE)

  # set directories
  set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CONFIGUPPERCASE} ${RUN_OUT_DIR})
  set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${CONFIGUPPERCASE} ${LIB_OUT_DIR})
  set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${CONFIGUPPERCASE} ${ARCH_OUT_DIR})
  set( CMAKE_PDB_OUTPUT_DIRECTORY_${CONFIGUPPERCASE} ${PDB_OUT_DIR})

endforeach (CONFIG ${CMAKE_CONFIGURATION_TYPES})
###############################################################################


###############################################################################
# Setup directories files
###############################################################################

if (NOT WIN32)
  file(MAKE_DIRECTORY ${TSEP_TARGET_DIR}/bin/)
endif ()
