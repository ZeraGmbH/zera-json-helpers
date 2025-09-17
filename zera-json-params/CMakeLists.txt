
add_subdirectory(lib)

# zera-json-params-cli
####################
add_executable(zera-json-params-cli
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

target_link_libraries(zera-json-params-cli
    PRIVATE
    Qt5::Core
    zera-json-params
    # ask linker to help us finding unresolved symbols
    "-Wl,--no-undefined"
)

install(TARGETS zera-json-params-cli
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Unittest
####################
file(GLOB UNITTEST_SOURCE
    unittest/*.cpp
    )
add_executable(zera-json-params-unittest
    unittest/resources.qrc
    unittest/zerajsonhelper.h
    ${UNITTEST_SOURCE}
    )


file(GLOB TEST_RESOURCE_FILES
    unittest/json-test-files/*.json
    )

file(GLOB TEST_RESOURCE_FILES_INVALID
    unittest/json-test-invalid-files/*.json
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
add_custom_target(zera-json-params-unittest-dont-forget-qrc-invalid ALL
    SOURCES ${TEST_RESOURCE_FILES_INVALID}
    COMMAND echo ${TEST_RESOURCE_FILES_INVALID}
    )

# check if all json test files made it into resources.qrc
foreach(jsonfile ${TEST_RESOURCE_FILES} ${TEST_RESOURCE_FILES_INVALID})
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

add_test(NAME    zera-json-params-unittest
         COMMAND zera-json-params-unittest
)
