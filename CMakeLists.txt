cmake_minimum_required(VERSION 3.8)

set(CMAKE_OSX_DEPLOYMENT_TARGET 11.0)

project(SeeX VERSION 1.1.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    application.cpp
    application.h
    fileprovider.cpp
    fileprovider.h
    frameprovider.cpp
    frameprovider.h
    images.qrc
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    statuslabel.cpp
    statuslabel.h
    viewerwidget.cpp
    viewerwidget.hpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(SeeX
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    add_executable(SeeX
        ${PROJECT_SOURCES}
    )
endif()

target_link_libraries(SeeX PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

if (APPLE)
    target_sources(SeeX PRIVATE SeeX.icns)
    set_source_files_properties(SeeX.icns PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
endif()

set_target_properties(SeeX PROPERTIES
    MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_LIST_DIR}/SeeX.plist
    MACOSX_BUNDLE_BUNDLE_NAME ${PROJECT_NAME}
    MACOSX_BUNDLE_ICON_FILE SeeX.icns
    MACOSX_BUNDLE_GUI_IDENTIFIER io.github.kolcha.seex
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(SeeX)
endif()
