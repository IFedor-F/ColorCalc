cmake_minimum_required(VERSION 3.30)
project(ColorCalc)


set(CMAKE_PREFIX_PATH "C:\\Qt\\6.8.2\\mingw_64\\")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)


include_directories(${CMAKE_CURRENT_SOURCE_DIR})
# ColorUtils
add_subdirectory(ColorUtils)

add_executable(ColorCalc main.cpp
        ${RESOURCE_SRCS}
        ColorWidget/ColorWidget.cpp
        ColorWidget/ColorWidget.h
        ColorWidget/ColorWidget.ui
        mainwindow/MainWindow.cpp
        mainwindow/MainWindow.h
        mainwindow/MainWindow.ui
)

target_link_libraries(ColorCalc
        Qt::Core
        Qt::Gui
        Qt::Widgets
        ColorUtils
)

# To include without MainWindow/MainWindow and same with ColorWidget and ColorUtils
target_include_directories(ColorCalc PRIVATE MainWindow PRIVATE ColorWidget PRIVATE ColorUtils)

# Sets Resources files (for icon)
set(RESOURCE_FILE resources/resources.qrc)
qt_add_resources(RESOURCE_SRCS ${RESOURCE_FILE})

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
