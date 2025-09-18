add_executable(zera-json-qml-unittest
    unittest-cpp.cpp
    resources.qrc
)

file(GLOB TEST_RESOURCE_FILES
    json-test-files/*.json
    )

# display in qt-creator
add_custom_target(zera-json-qml-unittest-dont-forget-qrc ALL
    SOURCES ${TEST_RESOURCE_FILES}
    COMMAND ${JSONLINT} ${TEST_RESOURCE_FILES}
    )

# check if all json test files made it into resources.qrc
foreach(jsonfile ${TEST_RESOURCE_FILES})
    get_filename_component(filename ${jsonfile} NAME)
    file(STRINGS resources.qrc lines REGEX "${filename}")
    if(NOT lines)
        message(FATAL_ERROR "${filename} was not added to resources.qrc - unittests will fail!!!")
    endif()
endforeach()

target_link_libraries(zera-json-qml-unittest
    gtest
    gtest_main
    zera-json-qml
    zera-json-helpers-testlib
)
add_test(NAME    zera-json-qml-unittest
         COMMAND zera-json-qml-unittest)
