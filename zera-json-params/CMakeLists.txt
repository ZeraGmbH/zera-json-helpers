cmake_minimum_required(VERSION 3.17)
# set project name and language
project(zera-json-params LANGUAGES CXX
VERSION ${REPO_VERSION}
)

# find required depemdencies
find_package(Qt5 COMPONENTS Core CONFIG REQUIRED)
find_package(GTest)

file(GLOB HEADER
    ${PROJECT_SOURCE_DIR}/src/*.h
    )

file(GLOB SOURCE
    ${PROJECT_SOURCE_DIR}/src/*.cpp
    )

file(GLOB TEST_FILES
    ${PROJECT_SOURCE_DIR}/test/json-param-test-files/*.json
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
    $<INSTALL_INTERFACE:include/zera-json-params>
    )

target_link_libraries(zera-json-params
    PRIVATE
    Qt5::Core
    # ask linker to help us finding unresolved symbols
    "-Wl,--no-undefined"
    )

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
    COMPATIBILITY SameMinorVersion
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
add_executable(zera-json-params-unittest
    unittest/type-unittest.cpp
    unittest/template-unittest.cpp
    unittest/zerajsonhelper.cpp
    unittest/zerajsonhelper.h
    ${TEST_FILES}
    )

target_link_libraries(zera-json-params-unittest
    gtest
    gtest_main
    Qt5::Core
    # lin to test
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
