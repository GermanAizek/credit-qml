cmake_minimum_required(VERSION 3.5)

project(jsonparser LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(ROOT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/..")
set(BINARY_PATH "")
if(UNIX AND NOT APPLE)
	set(BINARY_PATH "${PROJECT_BINARY_DIR}")
elseif(WIN32)
	set(BINARY_PATH "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
	set(BINARY_NAME "$<TARGET_FILE_NAME:${PROJECT_NAME}>")
endif()

# 3rd party
find_package(Qt5 COMPONENTS Widgets Qml Quick REQUIRED)

include_directories(${Qt5Widgets_INCLUDE_DIRS} ${QtQml_INCLUDE_DIRS})
add_definitions(${Qt5Widgets_DEFINITIONS} ${QtQml_DEFINITIONS} ${${Qt5Quick_DEFINITIONS}})

# directory with Qt application source code
#add_subdirectory(app)

if(NOT DEFINED HEADERS)
	file(GLOB HEADERS json_parser.h)
endif()
source_group("Header Files" FILES ${HEADERS})

if(NOT DEFINED SOURCES)
	file(GLOB SOURCES json_parser.cpp)
endif()
source_group("Source Files" FILES ${SOURCES})

if(NOT DEFINED QMLFILES)
	file(GLOB QMLFILES components/messagebox.qml)
endif()
source_group("QML Files" FILES ${QMLFILES})

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Qml Qt5::Quick)

# POST BUILD SECTION

# copy all qml components to build dir
foreach(PATH_QMLFILE ${QMLFILES})
	if(UNIX AND NOT APPLE)
		string(REPLACE "sources" "build" OUT_FILE ${PATH_QMLFILE})
		add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy "${PATH_QMLFILE}" "${OUT_FILE}"
			COMMENT "Copying ${PATH_QMLFILE} to ${OUT_FILE}"
		)
	elseif(WIN32)
		add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy "${PATH_QMLFILE}" "${BINARY_PATH}/components/messagebox.qml" # здесь необходимо перечисление компонентов для множественной подгрузки /components/messagebox.qml
			COMMENT "Copying ${PATH_QMLFILE} to ${BINARY_PATH}/components/"
		)
	endif()
endforeach(PATH_QMLFILE)

# Collecting DLL components for Windows
if(WIN32)
	set(QT_PATH_BIN "${Qt5_DIR}/../../../bin")
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${QT_PATH_BIN}/windeployqt.exe --qmldir ${BINARY_PATH}/components/ ${BINARY_PATH}/${BINARY_NAME}
		COMMENT "Collecting DLL using windeployqt..."
	)
endif()

# copy example json file to build dir
if(UNIX AND NOT APPLE)
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy "${ROOT_PATH}/examples/db.json" "${BINARY_PATH}/db.json"
		COMMENT "Copying ${ROOT_PATH}/examples/db.json to ${BINARY_PATH}"
	)
elseif(WIN32)
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy "${ROOT_PATH}/examples/db.json" "${BINARY_PATH}/db.json"
		COMMENT "Copying ${ROOT_PATH}/examples/db.json to ${BINARY_PATH}"
	)
endif()
