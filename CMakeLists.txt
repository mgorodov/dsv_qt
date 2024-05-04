cmake_minimum_required(VERSION 3.5)

project(dsv VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

include_directories(src)
set(PROJECT_SOURCES
    src/application.cpp
    src/main.cpp
    src/controller/controller.cpp
    src/model/model.cpp
    src/static/resources.qrc
    src/static/static.cpp
    src/ui/graph/edge.cpp
    src/ui/graph/grapheditor.cpp
    src/ui/graph/node.cpp
    src/ui/widgets/activitybar.cpp
    src/ui/widgets/codeeditor.cpp
    src/ui/mainwindow.cpp
)

qt_add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)
set_target_properties(${PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)
