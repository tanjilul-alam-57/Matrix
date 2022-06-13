###############################################################################
# SET QT5 Variables
###############################################################################
# set Qt directory
set (CMAKE_QTDIR ${TSEP_SOURCE_DIR}/../ThirdParty/Qt5.12.8/5.12.8/msvc2017_64)

set (TSEP_QT_DIR ${CMAKE_QTDIR})
set (Qt5_DIR ${CMAKE_QTDIR})
# set global autorcc options
set (CMAKE_AUTORCC_OPTIONS "-no-compress")

set (QT_MKSPECS_DIR "${CMAKE_QTDIR}/mkspecs" CACHE STRING "")
set (QT_INCLUDE_DIR "${CMAKE_QTDIR}/include" CACHE STRING "")
set (QT_MOC_EXECUTABLE "${CMAKE_QTDIR}/bin/moc.exe" CACHE STRING "")
set (QT_RCC_EXECUTABLE "${CMAKE_QTDIR}/bin/rcc.exe" CACHE STRING "")
#uic.exe is not available but CMAKE needs this variable defined as it can not find uic.exe
set (QT_UIC_EXECUTABLE "${CMAKE_QTDIR}/bin/uic.exe" CACHE STRING "")
set (QT_QTCORE_LIBRARY_DEBUG "${CMAKE_QTDIR}/lib/Qt5Cored.lib" CACHE STRING "")
set (QT_QTCORE_LIBRARY_RELEASE "${CMAKE_QTDIR}/lib/Qt5Core.lib" CACHE STRING "")
set (Qt5Core_DIR "${CMAKE_QTDIR}/lib/cmake/Qt5Core/")
set (Qt5Xml_DIR "${CMAKE_QTDIR}/lib/cmake/Qt5Xml/")
set (Qt5Gui_DIR "${CMAKE_QTDIR}/lib/cmake/Qt5Gui/")
set (Qt5Widgets_DIR "${CMAKE_QTDIR}/lib/cmake/Qt5Widgets/")
set (Qt5Svg_DIR "${CMAKE_QTDIR}/lib/cmake/Qt5Svg/")
set (Qt5Designer_DIR "${CMAKE_QTDIR}/lib/cmake/Qt5Designer/")
set (Qt5Multimedia_DIR "${CMAKE_QTDIR}/lib/cmake/Qt5Multimedia/")
set (Qt5WebEngine_DIR "${CMAKE_QTDIR}/lib/cmake/Qt5WebEngine/")
set (Qt5AxContainer_DIR "${CMAKE_QTDIR}/lib/cmake/Qt5AxContainer/")
set (Qt5AxServer_DIR "${CMAKE_QTDIR}/lib/cmake/Qt5AxServer/")
set (Qt5Sql_DIR "${CMAKE_QTDIR}/lib/cmake/Qt5Sql/")

#Find the Qt5 Packages
find_package(Qt5Core)
find_package(Qt5Xml)
find_package(Qt5Svg)
find_package(Qt5Widgets)
find_package(Qt5Designer)
find_package(Qt5Multimedia)
find_package(Qt5Sql)
#find_package(Qt5WebEngine)
###############################################################################
# QT5 Macros
###############################################################################

####################################
#target_qt_libraries
#  Description:
#    Add desired Qt library dependencies and the required Qt include directives to the project.
#    If no library is given, the standard qt include directories will be added.
#
#  Syntax:
#    target_qt_libraries(project_name [qt_library [qt_libary2]...])
#    qt_library may be one of
#      QtCore
#      QtGui
#      QtXml
#      QtSvg
#      QAxContainer
#      QAxServer
#      QAxWidget
#      QtMain
#      QtNetwork
#      QtDesigner
#      QtMultimedia
#      QtWebKit
####################################
macro (target_qt_libraries PROJECT_NAME)
    include_directories(
      ${CMAKE_QTDIR}/include
    )

    foreach(LIB ${ARGN})
      if ("${LIB}" STREQUAL "QtMain")
        #include_directories(${CMAKE_QTDIR}/qtbase/include/QtMain)
        target_link_libraries(${PROJECT_NAME} debug "${CMAKE_QTDIR}/lib/qtmaind.lib" optimized "${CMAKE_QTDIR}/lib/qtmain.lib")
      endif ("${LIB}" STREQUAL "QtMain")

      if ("${LIB}" STREQUAL "QtCore")
        include_directories(${CMAKE_QTDIR}/include/QtCore)
        target_link_libraries(${PROJECT_NAME} debug "${CMAKE_QTDIR}/lib/Qt5Cored.lib" optimized "${CMAKE_QTDIR}/lib/Qt5Core.lib")
      endif ("${LIB}" STREQUAL "QtCore")

      if ("${LIB}" STREQUAL "QtGui")
        include_directories(${CMAKE_QTDIR}/include/QtGui)
        target_link_libraries(${PROJECT_NAME} debug "${CMAKE_QTDIR}/lib/Qt5Guid.lib" optimized "${CMAKE_QTDIR}/lib/Qt5Gui.lib")
      endif ("${LIB}" STREQUAL "QtGui")

      if ("${LIB}" STREQUAL "QtXml")
        include_directories(${CMAKE_QTDIR}/include/QtXml)
        target_link_libraries(${PROJECT_NAME} debug "${CMAKE_QTDIR}/lib/Qt5Xmld.lib" optimized "${CMAKE_QTDIR}/lib/Qt5Xml.lib")
      endif ("${LIB}" STREQUAL "QtXml")

      if ("${LIB}" STREQUAL "QtSvg")
        include_directories(
          ${CMAKE_QTDIR}/include/QtSvg
          )
        target_link_libraries(${PROJECT_NAME} debug "${CMAKE_QTDIR}/lib/Qt5Svgd.lib" optimized "${CMAKE_QTDIR}/lib/Qt5Svg.lib")
      endif ("${LIB}" STREQUAL "QtSvg")

      if ("${LIB}" STREQUAL "QtWidgets")
        include_directories(${CMAKE_QTDIR}/include/QtWidgets)
        target_link_libraries(${PROJECT_NAME} debug "${CMAKE_QTDIR}/lib/Qt5Widgetsd.lib" optimized "${CMAKE_QTDIR}/lib/Qt5Widgets.lib")
      endif ("${LIB}" STREQUAL "QtWidgets")

      if ("${LIB}" STREQUAL "QtNetwork")
        include_directories(${CMAKE_QTDIR}/include/QtNetwork)
        target_link_libraries(${PROJECT_NAME} debug "${CMAKE_QTDIR}/lib/Qt5Networkd.lib" optimized "${CMAKE_QTDIR}/lib/Qt5Network.lib")
      endif ("${LIB}" STREQUAL "QtNetwork")

      if ("${LIB}" STREQUAL "QtDesigner")
        include_directories(
          ${CMAKE_QTDIR}/include/QtDesigner
          )
        target_link_libraries(${PROJECT_NAME} debug "${CMAKE_QTDIR}/lib/Qt5Designerd.lib" optimized "${CMAKE_QTDIR}/lib/Qt5Designer.lib")
      endif ("${LIB}" STREQUAL "QtDesigner")

      if ("${LIB}" STREQUAL "QtMultimedia")
        include_directories(${CMAKE_QTDIR}/include/QtMultimedia)
        target_link_libraries(${PROJECT_NAME} debug "${CMAKE_QTDIR}/lib/Qt5Multimediad.lib" optimized "${CMAKE_QTDIR}/lib/Qt5Multimedia.lib")
      endif ("${LIB}" STREQUAL "QtMultimedia")

      if ("${LIB}" STREQUAL "QtWebKit")
        include_directories(
          ${CMAKE_QTDIR}/include/QtWebKit
          ${CMAKE_QTDIR}/include/QtWebKitWidgets
          )
        target_link_libraries(${PROJECT_NAME}
          debug "${CMAKE_QTDIR}/lib/Qt5WebKitd.lib" optimized "${CMAKE_QTDIR}/lib/Qt5WebKit.lib"
          debug "${CMAKE_QTDIR}/lib/Qt5WebKitWidgetsd.lib" optimized "${CMAKE_QTDIR}/lib/Qt5WebKitWidgets.lib"
          )
      endif ("${LIB}" STREQUAL "QtWebKit")
	  
	   if ("${LIB}" STREQUAL "QtSql")
        include_directories(${CMAKE_QTDIR}/include/QtSql)
        target_link_libraries(${PROJECT_NAME} debug "${CMAKE_QTDIR}/lib/Qt5Sqld.lib" optimized "${CMAKE_QTDIR}/lib/Qt5Sql.lib")
      endif ("${LIB}" STREQUAL "QtSql")
      
      	   if ("${LIB}" STREQUAL "QtConCurrent")
        include_directories(${CMAKE_QTDIR}/include/QtConCurrent)
        target_link_libraries(${PROJECT_NAME} debug "${CMAKE_QTDIR}/lib/QtConCurrentd.lib" optimized "${CMAKE_QTDIR}/lib/QtConCurrent.lib")
      endif ("${LIB}" STREQUAL "QtConCurrent")

      if ("${LIB}" STREQUAL "QtPrintSupport")
        include_directories(${CMAKE_QTDIR}/include/QtPrintSupport)
        target_link_libraries(${PROJECT_NAME} debug "${CMAKE_QTDIR}/lib/Qt5PrintSupportd.lib" optimized "${CMAKE_QTDIR}/lib/Qt5PrintSupport.lib")
      endif ("${LIB}" STREQUAL "QtPrintSupport")

      if ("${LIB}" STREQUAL "QtWinExtras")
        include_directories(
          ${CMAKE_QTDIR}/include/QtWinExtras
          )

        target_link_libraries(${PROJECT_NAME} debug "${CMAKE_QTDIR}/lib/Qt5WinExtrasd.lib" optimized "${CMAKE_QTDIR}/lib/Qt5WinExtras.lib")
      endif ("${LIB}" STREQUAL "QtWinExtras")

      if ("${LIB}" STREQUAL "ActiveQt")
        include_directories(
          ${CMAKE_QTDIR}/include/ActiveQt
          )

        target_link_libraries(${PROJECT_NAME}
          debug "${CMAKE_QTDIR}/lib/Qt5AxBased.lib" optimized "${CMAKE_QTDIR}/lib/Qt5AxBase.lib"
          debug "${CMAKE_QTDIR}/lib/Qt5AxServerd.lib" optimized "${CMAKE_QTDIR}/lib/Qt5AxServer.lib"
          debug "${CMAKE_QTDIR}/lib/Qt5AxContainerd.lib" optimized "${CMAKE_QTDIR}/lib/Qt5AxContainer.lib"
          )
      endif ("${LIB}" STREQUAL "ActiveQt")

      if ("${LIB}" STREQUAL "QtANGLE")
        include_directories(
          ${CMAKE_QTDIR}/include/QtANGLE
          ${CMAKE_QTDIR}/include/QtANGLE/EGL
          ${CMAKE_QTDIR}/include/QtANGLE/GLES2
          )
        target_link_libraries(${PROJECT_NAME}
          debug "${CMAKE_QTDIR}/lib/libEGLd.lib" optimized "${CMAKE_QTDIR}/lib/libEGL.lib"
          debug "${CMAKE_QTDIR}/lib/libGLESv2d.lib" optimized "${CMAKE_QTDIR}/lib/libGLESv2.lib"
          )
      endif ("${LIB}" STREQUAL "QtANGLE")
    endforeach()
endmacro (target_qt_libraries)

####################################
#link_qt_libraries
#  Description:
#    Add desired Qt library dependencies.
#
#  Syntax:
#    link_qt_libraries(project_name [qt_library [qt_libary2]...])
#    qt_library may be one of
#      QtCore
#      QtGui
#      QtXml
#      QtSvg
#      QAxContainer
#      QAxServer
#      QAxWidget
#      QtMain
#      QtNetwork
#      QtDesigner
#      QtMultimedia
#      QtWebKit
####################################
macro (link_qt_libraries PROJECT_NAME)
    foreach(LIB ${ARGN})
      if ("${LIB}" STREQUAL "QtCore")
        target_link_libraries(${PROJECT_NAME} debug "${CMAKE_QTDIR}/lib/Qt5Cored.lib" optimized "${CMAKE_QTDIR}/lib/Qt5Core.lib")
      endif ("${LIB}" STREQUAL "QtCore")

      if ("${LIB}" STREQUAL "QtGui")
        target_link_libraries(${PROJECT_NAME} debug "${CMAKE_QTDIR}/lib/Qt5Guid.lib" optimized "${CMAKE_QTDIR}/lib/Qt5Gui.lib")
      endif ("${LIB}" STREQUAL "QtGui")

      if ("${LIB}" STREQUAL "QtXml")
        target_link_libraries(${PROJECT_NAME} debug "${CMAKE_QTDIR}/lib/Qt5Xmld.lib" optimized "${CMAKE_QTDIR}/lib/Qt5Xml.lib")
      endif ("${LIB}" STREQUAL "QtXml")

      if ("${LIB}" STREQUAL "QtSvg")
        target_link_libraries(${PROJECT_NAME} debug "${CMAKE_QTDIR}/lib/Qt5Svgd.lib" optimized "${CMAKE_QTDIR}/lib/Qt5Svg.lib")
      endif ("${LIB}" STREQUAL "QtSvg")

      if ("${LIB}" STREQUAL "QtWidgets")
        include_directories(${CMAKE_QTDIR}/include/QtWidgets)
        target_link_libraries(${PROJECT_NAME} debug "${CMAKE_QTDIR}/lib/Qt5Widgetsd.lib" optimized "${CMAKE_QTDIR}/lib/Qt5Widgets.lib")
      endif ("${LIB}" STREQUAL "QtWidgets")

      if ("${LIB}" STREQUAL "QtNetwork")
        target_link_libraries(${PROJECT_NAME} debug "${CMAKE_QTDIR}/lib/Qt5Networkd.lib" optimized "${CMAKE_QTDIR}/lib/Qt5Network.lib")
      endif ("${LIB}" STREQUAL "QtNetwork")

      if ("${LIB}" STREQUAL "QtDesigner")
        target_link_libraries(${PROJECT_NAME} debug "${CMAKE_QTDIR}/lib/Qt5Designerd.lib" optimized "${CMAKE_QTDIR}/lib/Qt5Designer.lib")
      endif ("${LIB}" STREQUAL "QtDesigner")

      if ("${LIB}" STREQUAL "QtMultimedia")
        target_link_libraries(${PROJECT_NAME} debug "${CMAKE_QTDIR}/lib/Qt5Multimediad.lib" optimized "${CMAKE_QTDIR}/lib/Qt5Multimedia.lib")
      endif ("${LIB}" STREQUAL "QtMultimedia")
	  
	   if ("${LIB}" STREQUAL "QtSql")
        target_link_libraries(${PROJECT_NAME} debug "${CMAKE_QTDIR}/lib/Qt5Sqld.lib" optimized "${CMAKE_QTDIR}/lib/Qt5Sql.lib")
      endif ("${LIB}" STREQUAL "QtSql")

      if ("${LIB}" STREQUAL "QtWebKit")
        target_link_libraries(${PROJECT_NAME}
          debug "${CMAKE_QTDIR}/lib/Qt5WebKitd.lib" optimized "${CMAKE_QTDIR}/lib/Qt5WebKit.lib"
          debug "${CMAKE_QTDIR}/lib/Qt5WebKitWidgetsd.lib" optimized "${CMAKE_QTDIR}/lib/Qt5WebKitWidgets.lib"
          )
      endif ("${LIB}" STREQUAL "QtWebKit")

      if ("${LIB}" STREQUAL "QtPrintSupport")
        target_link_libraries(${PROJECT_NAME} debug "${CMAKE_QTDIR}/lib/Qt5PrintSupportd.lib" optimized "${CMAKE_QTDIR}/lib/Qt5PrintSupport.lib")
      endif ("${LIB}" STREQUAL "QtPrintSupport")

      if ("${LIB}" STREQUAL "QtWinExtras")
        target_link_libraries(${PROJECT_NAME} debug "${CMAKE_QTDIR}/lib/Qt5WinExtrasd.lib" optimized "${CMAKE_QTDIR}/lib/Qt5WinExtras.lib")
      endif ("${LIB}" STREQUAL "QtWinExtras")

      if ("${LIB}" STREQUAL "ActiveQt")
        target_link_libraries(${PROJECT_NAME}
          debug "${CMAKE_QTDIR}/lib/Qt5AxBased.lib" optimized "${CMAKE_QTDIR}/lib/Qt5AxBase.lib"
          debug "${CMAKE_QTDIR}/lib/Qt5AxServerd.lib" optimized "${CMAKE_QTDIR}/lib/Qt5AxServer.lib"
          debug "${CMAKE_QTDIR}/lib/Qt5AxContainerd.lib" optimized "${CMAKE_QTDIR}/lib/Qt5AxContainer.lib"
          )
      endif ("${LIB}" STREQUAL "ActiveQt")

      if ("${LIB}" STREQUAL "QtANGLE")
        target_link_libraries(${PROJECT_NAME}
          debug "${CMAKE_QTDIR}/lib/libEGLd.lib" optimized "${CMAKE_QTDIR}/lib/libEGL.lib"
          debug "${CMAKE_QTDIR}/lib/libGLESv2d.lib" optimized "${CMAKE_QTDIR}/lib/libGLESv2.lib"
          )
      endif ("${LIB}" STREQUAL "QtANGLE")
    endforeach()
endmacro (link_qt_libraries)

####################################
#include_qt_libraries
#  Description:
#    Add desired Qt library includes.
#    If no library is given, the standard qt include directories will be added.
#
#  Syntax:
#    include_qt_libraries(project_name [qt_library [qt_libary2]...])
#    qt_library may be one of
#      QtCore
#      QtGui
#      QtXml
#      QtSvg
#      QAxContainer
#      QAxServer
#      QAxWidget
#      QtMain
#      QtNetwork
#      QtDesigner
#      QtMultimedia
#      QtWebKit
####################################
macro (include_qt_libraries)
    include_directories(
      ${CMAKE_QTDIR}/src
      ${CMAKE_QTDIR}/include
    )

    foreach(LIB ${ARGN})
      if ("${LIB}" STREQUAL "QtCore")
        include_directories(${CMAKE_QTDIR}/include/QtCore)
      endif ("${LIB}" STREQUAL "QtCore")

      if ("${LIB}" STREQUAL "QtGui")
        include_directories(${CMAKE_QTDIR}/include/QtGui)
      endif ("${LIB}" STREQUAL "QtGui")

      if ("${LIB}" STREQUAL "QtXml")
        include_directories(${CMAKE_QTDIR}/include/QtXml)
      endif ("${LIB}" STREQUAL "QtXml")

      if ("${LIB}" STREQUAL "QtSvg")
        include_directories(
          ${CMAKE_QTDIR}/include/QtSvg
        )
      endif ("${LIB}" STREQUAL "QtSvg")

      if ("${LIB}" STREQUAL "QtWidgets")
        include_directories(${CMAKE_QTDIR}/include/QtWidgets)
      endif ("${LIB}" STREQUAL "QtWidgets")

      if ("${LIB}" STREQUAL "QtNetwork")
        include_directories(${CMAKE_QTDIR}/include/QtNetwork)
      endif ("${LIB}" STREQUAL "QtNetwork")

      if ("${LIB}" STREQUAL "QtDesigner")
        include_directories(
          ${CMAKE_QTDIR}/include/QtDesigner
          )
      endif ("${LIB}" STREQUAL "QtDesigner")

      if ("${LIB}" STREQUAL "QtMultimedia")
        include_directories(${CMAKE_QTDIR}/include/QtMultimedia)
      endif ("${LIB}" STREQUAL "QtMultimedia")	  
	  
      if ("${LIB}" STREQUAL "QtSql")
        include_directories(${CMAKE_QTDIR}/include/QtSql)
      endif ("${LIB}" STREQUAL "QtSql")

      if ("${LIB}" STREQUAL "QtWebKit")
        include_directories(
          ${CMAKE_QTDIR}/include/QtWebKit
          ${CMAKE_QTDIR}/include/QtWebKitWidgets
          )
      endif ("${LIB}" STREQUAL "QtWebKit")

      if ("${LIB}" STREQUAL "QtPrintSupport")
        include_directories(${CMAKE_QTDIR}/include/QtPrintSupport)
      endif ("${LIB}" STREQUAL "QtPrintSupport")

      if ("${LIB}" STREQUAL "QtWinExtras")
        include_directories(
          ${CMAKE_QTDIR}/include/QtWinExtras
          )
      endif ("${LIB}" STREQUAL "QtWinExtras")

      if ("${LIB}" STREQUAL "ActiveQt")
        include_directories(
          ${CMAKE_QTDIR}/include/ActiveQt
        )
      endif ("${LIB}" STREQUAL "ActiveQt")

      if ("${LIB}" STREQUAL "QtANGLE")
        include_directories(
          ${CMAKE_QTDIR}/include/QtANGLE
          ${CMAKE_QTDIR}/include/QtANGLE/EGL
          ${CMAKE_QTDIR}/include/QtANGLE/GLES2
          )
      endif ("${LIB}" STREQUAL "QtANGLE")
    endforeach()
endmacro (include_qt_libraries)