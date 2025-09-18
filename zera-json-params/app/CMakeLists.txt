add_executable(zera-json-params-cli
    main.cpp
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

