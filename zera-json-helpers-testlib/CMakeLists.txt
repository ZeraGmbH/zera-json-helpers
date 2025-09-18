file(GLOB SOURCES
    *.cpp
    )

file(GLOB HEADER
    *.h
    )

add_library(zera-json-helpers-testlib STATIC
    ${SOURCES}
    ${HEADER}
    )

target_link_libraries(zera-json-helpers-testlib
    PUBLIC
    Qt5::Core
    )

target_include_directories(zera-json-helpers-testlib
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    )

set_target_properties(zera-json-helpers-testlib PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(zera-json-helpers-testlib PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})
