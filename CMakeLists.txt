cmake_minimum_required(VERSION 3.1)
project(zera-json-helpers LANGUAGES CXX)

include(GNUInstallDirs)
include(GenerateExportHeader)
include(CMakePackageConfigHelpers)

set(PROJECT_VERSION_MAJOR "1")
set(PROJECT_VERSION_MINOR "0")
set(PROJECT_VERSION_PATCH "1")

set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Core Qml Test CONFIG REQUIRED)
find_package(GTest REQUIRED)
# Note 1: In OE we do not (yet) have jsonlint-php so it must be optional
# Note 2: In case we make COMMAND in target below conditional on JSONLINT,
#         qt-creator does not display source-capabilities. That's what the
#         'echo' dance is for
find_program(JSONLINT NAMES jsonlint-php echo)
if(${JSONLINT} MATCHES ".*echo.*")
    message(WARNING "Program jsonlint-php not found. On Fedora install php-jsonlint")
endif()

enable_testing()

write_basic_package_version_file(
    zera-json-helpersConfigVersion.cmake
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY SameMajorVersion
    )

configure_file(zera-json-helpersConfig.cmake.in zera-json-helpersConfig.cmake @ONLY)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/zera-json-helpersConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/zera-json-helpersConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/zera-json-helpers
    )

install(EXPORT zera-json-helpersExport
    FILE zera-json-helpersTargets.cmake
    NAMESPACE Zera::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/zera-json-helpers
    )

add_subdirectory(zera-json-helpers-testlib)
add_subdirectory(zera-json-params)
add_subdirectory(zera-json-qml)
add_subdirectory(zera-json-settings)

