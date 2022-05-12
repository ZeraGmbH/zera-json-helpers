cmake_minimum_required(VERSION 3.1)
# set project name and language
project(zera-json-params LANGUAGES CXX
VERSION ${REPO_VERSION}
)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# find required dependencies
find_package(Qt5 COMPONENTS Core CONFIG REQUIRED)
find_package(GTest)

file(GLOB HEADER
    ${PROJECT_SOURCE_DIR}/src/*.h
    )

file(GLOB SOURCE
    ${PROJECT_SOURCE_DIR}/src/*.cpp
    )

# zera-json-params
########################
add_library(zera-json-params SHARED
    ${HEADER}
    ${SOURCE}
)

# announce headers - target perspective
target_include_directories(zera-json-params
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/zera-json-params>
    )

target_link_libraries(zera-json-params
    PUBLIC
    Qt5::Core
    # ask linker to help us finding unresolved symbols
    "-Wl,--no-undefined"
    )


#set target Version
set_target_properties(zera-json-params PROPERTIES VERSION ${PROJECT_VERSION})

# generate export header
include(GenerateExportHeader)
generate_export_header(zera-json-params)


# install export header
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/zera-json-params_export.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/zera-json-params
    )

# install library
install(TARGETS zera-json-params
    EXPORT zera-json-paramsExport
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

# configure *ConfigVersion.cmake
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    zera-json-paramsConfigVersion.cmake
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY SameMajorVersion
    )

# configure *Config.cmake
configure_file(zera-json-paramsConfig.cmake.in zera-json-paramsConfig.cmake @ONLY)


# install *Config(Version).cmake
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/zera-json-paramsConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/zera-json-paramsConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/zera-json-params
    )

# install targets cmake-files
install(EXPORT zera-json-paramsExport
    FILE zera-json-paramsTargets.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/zera-json-params
    )

# install public headers
install(
    FILES ${HEADER}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/zera-json-params
    )


# zera-json-params-cli
####################
add_executable(zera-json-params-cli
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

target_include_directories(zera-json-params-cli
   PRIVATE
   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)

# link dependencies
target_link_libraries(zera-json-params-cli
    PRIVATE
    Qt5::Core
    zera-json-params
    # ask linker to help us finding unresolved symbols
    "-Wl,--no-undefined"
)

# install application
install(TARGETS zera-json-params-cli
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Unittest
####################
if(${GTest_FOUND})
message(STATUS "building with unittest")
file(GLOB UNITTEST_SOURCE
    ${PROJECT_SOURCE_DIR}/unittest/*.cpp
    )
add_executable(zera-json-params-unittest
    unittest/resources.qrc
    unittest/zerajsonhelper.h
    ${UNITTEST_SOURCE}
    )


file(GLOB TEST_RESOURCE_FILES
    unittest/json-test-files/*.json
    )

# Note 1: In OE we do not (yet) have jsonlint-php so it must be optional
# Note 2: In case we make COMMAND in target below conditional on JSONLINT,
#         qt-creator does not display source-capabilities. That's what the
#         'echo' dance is for
find_program (JSONLINT NAMES jsonlint-php echo)
if(${JSONLINT} MATCHES ".*echo.*")
    message(WARNING "Program jsonlint-php not found. On Fedora install php-jsonlint")
endif()

# display in qt-creator
add_custom_target(zera-json-params-unittest-dont-forget-qrc ALL
    SOURCES ${TEST_RESOURCE_FILES}
    COMMAND ${JSONLINT} ${TEST_RESOURCE_FILES}
    )

# check if all json test files made it into resources.qrc
foreach(jsonfile ${TEST_RESOURCE_FILES})
    get_filename_component(filename ${jsonfile} NAME)
    file(STRINGS unittest/resources.qrc lines REGEX "${filename}")
    if(NOT lines)
        message(FATAL_ERROR "${filename} was not added to resources.qrc - unittests will fail!!!")
    endif()
endforeach()


target_link_libraries(zera-json-params-unittest
    gtest
    gtest_main
    Qt5::Core
    zera-json-params
)

target_include_directories(zera-json-params-unittest
    PUBLIC
    $<INSTALL_INTERFACE:src>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

enable_testing()
add_test(NAME    zera-json-params-unittest
         COMMAND zera-json-params-unittest
)
endif()
