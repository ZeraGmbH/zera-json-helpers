file(GLOB HEADER
    *.h
    )

file(GLOB SOURCE
    *.cpp
    )

add_library(zera-json-qml SHARED
    ${HEADER}
    ${SOURCE}
)

target_include_directories(zera-json-qml
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/zera-json-qml>
    )

target_link_libraries(zera-json-qml
    PUBLIC
    Qt5::Core
    Qt5::Qml
    # ask linker to help us finding unresolved symbols
    "-Wl,--no-undefined"
    )

set_target_properties(zera-json-qml PROPERTIES VERSION ${PROJECT_VERSION})

generate_export_header(zera-json-qml)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/zera-json-qml_export.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/zera-json-qml
    )

install(TARGETS zera-json-qml
    EXPORT zera-json-qmlExport
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

write_basic_package_version_file(
    zera-json-qmlConfigVersion.cmake
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY SameMajorVersion
    )

configure_file(zera-json-qmlConfig.cmake.in zera-json-qmlConfig.cmake @ONLY)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/zera-json-qmlConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/zera-json-qmlConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/zera-json-qml
    )

install(EXPORT zera-json-qmlExport
    FILE zera-json-qmlTargets.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/zera-json-qml
    )

install(
    FILES ${HEADER}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/zera-json-qml
    )

