file(GLOB HEADER
    *.h
    )
file(GLOB SOURCES
    *.cpp
    )

add_library(zera-json-settings SHARED
    ${HEADER}
    ${SOURCES}
    )

target_link_libraries(zera-json-settings
    PUBLIC
    Qt5::Core
    )

target_include_directories(zera-json-settings
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/zera-json-settings>
    )

set_target_properties(zera-json-settings PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(zera-json-settings PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

install(TARGETS zera-json-settings
    EXPORT zera-json-helpersExport
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

generate_export_header(zera-json-settings)
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/zera-json-settings_export.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/zera-json-settings
    )

install(
    FILES ${HEADER}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/zera-json-settings
    )
