#
# CMakeLists Configuration File
#
# copyright (c) 2015+ Rohde & Schwarz & Co. KG, Munich
# originally written by Luis Roalter <luis.roalter@rohde-schwarz.com>
#
# This is a CMake Configuration File and used for generating solution files.
#

#
# Macro to add the precompiled headers to the project.
#
macro(enable_precompiled_headers SourcesVar)
   enable_precompiled_headers_per_file(${SourcesVar})
endmacro(enable_precompiled_headers)

macro(enable_precompiled_headers_per_project SourcesVar)
    if (MSVC)
        add_flag(/YuStdAfx.h)
        add_flag(/FIStdAfx.h)
        set_source_files_properties(StdAfx.cpp
            PROPERTIES
            COMPILE_FLAGS "/YcStdAfx.h"
            )
        list(APPEND ${${SourcesVar}} StdAfx.cpp)
    endif()
endmacro(enable_precompiled_headers_per_project)

macro(enable_precompiled_headers_per_file SourcesVar)
    if (MSVC)
        #add_flag(/YuStdAfx.h)
        #add_flag(/FIStdAfx.h)
        foreach(f ${${SourcesVar}})
           #message(AUTHOR_WARNING "Adding /Yu and /FI to ${f}")
           get_filename_component(_temp_name ${f} NAME_WE)
           string(TOUPPER ${_temp_name} __temp_name)
           if (__temp_name STREQUAL STDAFX)
                set_source_files_properties(StdAfx.cpp
                    PROPERTIES
                    COMPILE_FLAGS "/YcStdAfx.h /MP1"
                    )
           else()
               set_source_files_properties(${f}
               PROPERTIES
               COMPILE_FLAGS "/YuStdAfx.h /FIStdAfx.h"
               )
           endif()
        endforeach()
        #list(APPEND ${${SourcesVar}} StdAfx.cpp)
    endif()
endmacro(enable_precompiled_headers_per_file)


macro(no_precompiled_headers SourcesVar)
    if (MSVC)
        foreach(f ${${SourcesVar}})
           get_source_file_property(FLAGS ${f} COMPILE_FLAGS)
           if (FLAGS MATCHES "NOTFOUND")
              set(FLAGS "")
           endif()
           set_source_files_properties(${f}
           PROPERTIES
           COMPILE_FLAGS "${FLAGS} /Y- /FI"
           )
        endforeach()
   endif()
endmacro(no_precompiled_headers)
