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

    src/kernel/code_editor_model/code_editor_model.cpp
    src/kernel/graph_editor_model/graph_editor_model.cpp
    src/kernel/model/model.cpp

    src/ui/static/resources.qrc
    src/ui/static/static.cpp
    src/ui/views/code_editor/codeeditor.cpp
    src/ui/views/graph_editor/edge.cpp
    src/ui/views/graph_editor/grapheditor.cpp
    src/ui/views/graph_editor/node.cpp
    src/ui/widgets/activitybar.cpp
    src/ui/mainwindow.cpp
)

qt_add_executable(${PROJECT_NAME} ${PROJECT_SOURCES}
    src/misc/Observer.h)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)
set_target_properties(${PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)
