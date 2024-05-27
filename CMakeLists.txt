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
    src/application/application.cpp
    src/application/application_kernel.cpp

    src/kernel/code_editor/code_editor_model.cpp
    src/kernel/code_editor/code_editor_model_controller.cpp
    src/kernel/graph_editor/graph_editor_model.cpp
    src/kernel/graph_editor/graph_editor_model_controller.cpp
    src/kernel/graph_editor/graph_editor_view_controller.cpp
    src/kernel/data_model/graph.cpp
    src/kernel/data_model/data_model.cpp

    src/misc/QPorts.cpp
    src/misc/QRunTime.cpp

    src/ui/static/resources.qrc
    src/ui/static/static.cpp
    src/ui/views/code_editor/widget/code_editor_base.cpp
    src/ui/views/code_editor/widget/line_number_area.cpp
    src/ui/views/code_editor/code_editor.cpp
    src/ui/views/graph_editor/edge.cpp
    src/ui/views/graph_editor/graph_editor.cpp
    src/ui/views/graph_editor/node.cpp
    src/ui/widgets/activitybar.cpp
    src/ui/mainwindow.cpp

    src/main.cpp
)

qt_add_executable(${PROJECT_NAME} ${PROJECT_SOURCES}
    src/kernel/code_editor/code_editor_controller.h src/kernel/code_editor/code_editor_controller.cpp
    src/kernel/code_editor/serialized_graph.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)
set_target_properties(${PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)
