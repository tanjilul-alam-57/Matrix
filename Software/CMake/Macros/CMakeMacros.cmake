####################################
#target_link_external_libraries
#  Description:
#    Add desired system library dependencies.
#
#  Syntax:
#    target_link_external_libraries(project_name [system_library [system_libary2]...])
#    system_library may be one of
#      Visa
####################################
macro (target_link_external_libraries PROJECT_NAME)
#System dependent libraries

IF (WIN32)
# set libraries for windows
foreach(LIB ${ARGN})
  if ("${LIB}" STREQUAL "Visa")
    include_directories(${TSEP_VISA_DIR}/include)
    target_link_libraries(${PROJECT_NAME} 
      ${TSEP_VISA_DIR}/lib/msc/RsVisa32.lib 
      ${TSEP_VISA_DIR}/lib/msc/RsVisaLoader.lib
    )
    
  endif ()
endforeach()
ELSE()
########Search for R&S VISA ########
if(NOT TARGET rsvisa::rsvisa)
  find_package(RsVisa REQUIRED)
endif()

# set libraries for linux systems
foreach(LIB ${ARGN})
  if ("${LIB}" STREQUAL "Visa")
    include_directories(${TSEP_VISA_DIR})    
    target_link_libraries(${PROJECT_NAME} 
                      rsvisa::rsvisa)
    
  endif ()
endforeach()
ENDIF()
# set libraries for linux systems

endmacro (target_link_external_libraries)

####################################
#target_link_system_libraries
#  Description:
#    Add desired system library dependencies.
#
#  Syntax:
#    target_link_system_libraries(project_name [system_library [system_libary2]...])
#    system_library may be one of
#      Sockets
#      Network
#      dnssd
####################################
macro (target_link_system_libraries PROJECT_NAME)

#System dependent libraries
IF (WIN32)
# set libraries for windows
    foreach(LIB ${ARGN})
      if ("${LIB}" STREQUAL "Sockets")
        target_link_libraries(${PROJECT_NAME}
          Ws2_32.lib
        )
      endif ()

      if ("${LIB}" STREQUAL "Network")
        target_link_libraries(${PROJECT_NAME}
          IPHLPAPI.lib
        )
      endif ()

     if ("${LIB}" STREQUAL "SetupAPI")
        target_link_libraries(${PROJECT_NAME}
          SetupAPI.lib
        )
      endif ()
    endforeach()
ELSE()
# set libraries for linux systems
    foreach(LIB ${ARGN})
      if ("${LIB}" STREQUAL "Sockets")
        target_link_libraries(${PROJECT_NAME}
          dl
          pthread
          rt
        )
      endif ("${LIB}" STREQUAL "Sockets")

      if ("${LIB}" STREQUAL "Thread")
        target_link_libraries(${PROJECT_NAME}
          dl
          pthread
          rt
        )
      endif ("${LIB}" STREQUAL "Thread")
    endforeach()
ENDIF()
endmacro (target_link_system_libraries)

####################################
#set_output_dir
#  Description:
#    Change the output directory of the project to given folder
#       for all configurations
#
#  Syntax:
#    set_output_dir(foldername)
####################################
macro (set_output_dir DIR)
  foreach (CONFIG ${CMAKE_CONFIGURATION_TYPES})
    # make configuration variable upper case for CMAKE macros
    string(TOUPPER ${CONFIG} CONFIGUPPERCASE)

    # set directories
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CONFIGUPPERCASE} ${DIR})
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${CONFIGUPPERCASE} ${DIR})
    set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${CONFIGUPPERCASE} ${DIR})
    set( CMAKE_PDB_OUTPUT_DIRECTORY_${CONFIGUPPERCASE} ${DIR})
  endforeach (CONFIG ${CMAKE_CONFIGURATION_TYPES})
endmacro (set_output_dir)

####################################
#no_compile
#  Description:
#    Do not compile files in the list
#
#  Syntax:
#    no_compile(file1 file2)
####################################
macro(no_compile FILE_LIST)
   set_source_files_properties(${${FILE_LIST}} PROPERTIES HEADER_FILE_ONLY TRUE)
endmacro()


####################################
#set_warning_level_for_automoc_file
#  Description:
#    Set warning level to 1 for the  automoc file of the given project
#
#  Syntax:
#    set_warning_level_for_automoc_file(project_name)
####################################
function (set_warning_level_for_automoc_file PROJECT_NAME)
  string (CONCAT MOC_FILENAME ${PROJECT_NAME} "_automoc.cpp" )
  set_source_files_properties( ${MOC_FILENAME} PROPERTIES GENERATED true)
  set_source_files_properties( ${MOC_FILENAME} PROPERTIES COMPILE_FLAGS -W1 )
endfunction(set_warning_level_for_automoc_file)