cmake_minimum_required(VERSION 3.1)
# set project name and language
project(zera-json-qml LANGUAGES CXX
VERSION ${REPO_VERSION}
)


set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# find required depemdencies
find_package(Qt5 COMPONENTS Core Qml CONFIG REQUIRED)

file(GLOB HEADER
    ${PROJECT_SOURCE_DIR}/src/*.h
    )

file(GLOB SOURCE
    ${PROJECT_SOURCE_DIR}/src/*.cpp
    )

# zera-json-qml
########################
add_library(zera-json-qml SHARED
    ${HEADER}
    ${SOURCE}
)

# announce headers - target perspective
target_include_directories(zera-json-qml
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:include/zera-json-qml>
    )

target_link_libraries(zera-json-qml
    PUBLIC
    Qt5::Core
    Qt5::Qml
    # ask linker to help us finding unresolved symbols
    "-Wl,--no-undefined"
    )

#set target Version
set_target_properties(zera-json-qml PROPERTIES VERSION ${PROJECT_VERSION})

# generate export header
include(GenerateExportHeader)
generate_export_header(zera-json-qml)


# install export header
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/zera-json-qml_export.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/zera-json-qml
    )

# install library
install(TARGETS zera-json-qml
    EXPORT zera-json-qmlExport
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

# configure *ConfigVersion.cmake
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    zera-json-qmlConfigVersion.cmake
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY SameMinorVersion
    )

# configure *Config.cmake
configure_file(zera-json-qmlConfig.cmake.in zera-json-qmlConfig.cmake @ONLY)


# install *Config(Version).cmake
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/zera-json-qmlConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/zera-json-qmlConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/zera-json-qml
    )

# install targets cmake-files
install(EXPORT zera-json-qmlExport
    FILE zera-json-qmlTargets.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/zera-json-qml
    )

# install public headers
install(
    FILES ${HEADER}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/zera-json-qml
    )


