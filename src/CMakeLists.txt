target_sources(
    cryptopals
    PRIVATE
    main.c
)

target_include_directories(
    cryptopals
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_subdirectory(analysis)
add_subdirectory(ciphers)
add_subdirectory(codecs)
add_subdirectory(external)
add_subdirectory(oracles)
add_subdirectory(resources)
add_subdirectory(solutions)
add_subdirectory(uncrypt)
add_subdirectory(utility)
