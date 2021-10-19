cmake_minimum_required(VERSION 3.17)
# set project name and language
project(zera-json-params-top LANGUAGES CXX
)

include(GNUInstallDirs)

set(PROJECT_VERSION_MAJOR "1")
set(PROJECT_VERSION_MINOR "0")
set(PROJECT_VERSION_PATCH "1")

set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")
set(REPO_VERSION ${PROJECT_VERSION})

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/zera-json-params)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/zera-json-qml)
