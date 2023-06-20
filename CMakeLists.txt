cmake_minimum_required(VERSION 3.20.0)

project(PhotoClassifiersApp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
set(CMAKE_OBJECT_PATH_MAX 777)

find_package(Qt6 6.2 COMPONENTS Gui Widgets Core Quick REQUIRED)

add_executable(PhotoClassifiersApp
    "${CMAKE_CURRENT_SOURCE_DIR}/Backend/includes/RenamingEngine.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Backend/srcs/RenamingEngine.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Backend/srcs/ApplicationController.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Backend/srcs/LoggingController.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Backend/includes/ApplicationController.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Backend/includes/LoggingController.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Backend/includes/Settings.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Backend/srcs/Settings.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Backend/includes/AppListModel.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Backend/srcs/AppListModel.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Backend/srcs/FileNamesContainer.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Backend/includes/PhotoFactory.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Backend/srcs/PhotoFactory.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Backend/srcs/PhotoObject.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Backend/srcs/AlbumPresenter.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Backend/includes/AlbumPresenter.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Backend/includes/PhotoObject.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/Backend/includes/FileNamesContainer.h"
)

option(ENABLED_UI "enable UI" OFF)

if(ENABLED_UI)
    qt6_add_qml_module(PhotoClassifiersApp
        URI PhotoClassifiersApp
        VERSION 1.0
        QML_FILES main.qml MainWindow.qml
    )
endif()

target_include_directories(${PROJECT_NAME}
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/Backend/includes/"
        )

if(ENABLED_UI)
   target_compile_definitions(PhotoClassifiersApp
       PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>
       PUBLIC $<$<CONFIG:Debug>:ENABLED_UI>
    )
endif()

set_target_properties(PhotoClassifiersApp PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(PhotoClassifiersApp
    PRIVATE Qt6::Quick Qt6::Widgets Qt6::Core Qt6::Gui)


install(TARGETS PhotoClassifiersApp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
