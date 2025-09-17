file(GLOB HEADER
    *.h
    )

file(GLOB SOURCE
    *.cpp
    )

add_library(zera-json-params SHARED
    ${HEADER}
    ${SOURCE}
)

target_include_directories(zera-json-params
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/zera-json-params>
    )

target_link_libraries(zera-json-params
    PUBLIC
    Qt5::Core
    # ask linker to help us finding unresolved symbols
    "-Wl,--no-undefined"
    )

set_target_properties(zera-json-params PROPERTIES VERSION ${PROJECT_VERSION})

generate_export_header(zera-json-params)
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/zera-json-params_export.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/zera-json-params
    )

install(TARGETS zera-json-params
    EXPORT zera-json-paramsExport
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

write_basic_package_version_file(
    zera-json-paramsConfigVersion.cmake
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY SameMajorVersion
    )

configure_file(zera-json-paramsConfig.cmake.in zera-json-paramsConfig.cmake @ONLY)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/zera-json-paramsConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/zera-json-paramsConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/zera-json-params
    )

install(EXPORT zera-json-paramsExport
    FILE zera-json-paramsTargets.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/zera-json-params
    )

install(
    FILES ${HEADER}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/zera-json-params
    )

