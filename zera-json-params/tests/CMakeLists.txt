file(GLOB UNITTEST_SOURCE
    *.cpp
    )
add_executable(zera-json-params-unittest
    resources.qrc
    zerajsonhelper.h
    ${UNITTEST_SOURCE}
    )


file(GLOB TEST_RESOURCE_FILES
    json-test-files/*.json
    )

file(GLOB TEST_RESOURCE_FILES_INVALID
    json-test-invalid-files/*.json
    )


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
    file(STRINGS resources.qrc lines REGEX "${filename}")
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

add_test(NAME    zera-json-params-unittest
         COMMAND zera-json-params-unittest
)
