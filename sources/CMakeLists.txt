cmake_minimum_required(VERSION 3.5)

project(jsonparser LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(ROOT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../")

# 3rd party
if(UNIX AND NOT APPLE)
        find_package(Qt5 COMPONENTS Widgets Qml Quick REQUIRED)
endif()

include_directories(${Qt5Widgets_INCLUDE_DIRS} ${QtQml_INCLUDE_DIRS})
add_definitions(${Qt5Widgets_DEFINITIONS} ${QtQml_DEFINITIONS} ${${Qt5Quick_DEFINITIONS}})

# directory with Qt application source code
#add_subdirectory(app)

if(NOT DEFINED HEADERS)
        file(GLOB HEADERS ⁄json_parser.h)
endif()
source_group("Parser Headers" FILES ${HEADERS})

if(NOT DEFINED SOURCES)
        file(GLOB SOURCES json_parser.cpp)
endif()
source_group("Parser Sources" FILES ${SOURCES})

if(NOT DEFINED QMLFILES)
        file(GLOB QMLFILES components/messagebox.qml)
endif()
source_group("Parser QML Sources" FILES ${QMLFILES})

add_executable(jsonparser ${HEADERS} ${SOURCES})
target_link_libraries(jsonparser Qt5::Widgets Qt5::Qml Qt5::Quick)

# POST BUILD SECTION
# copy all qml components to build dir
foreach(PATH_QMLFILE ${QMLFILES})
        string(REPLACE "sources" "build" OUT_FILE ${PATH_QMLFILE})
        add_custom_command(TARGET jsonparser POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy ${PATH_QMLFILE} ${OUT_FILE}
            COMMENT "Copying ${OUT_FILE}"
        )
        #configure_file(${PATH_QMLFILE} ${OUT_FILE} COPYONLY)
endforeach(PATH_QMLFILE)

# copy example json file to build dir
add_custom_command(TARGET jsonparser POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${ROOT_PATH}/examples/db.json ${PROJECT_BINARY_DIR}/db.json
    COMMENT "Copying ${PROJECT_BINARY_DIR}/db.json"
)
#configure_file( db.json COPYONLY)
