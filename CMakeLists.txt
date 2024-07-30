cmake_minimum_required(VERSION 3.24)

project(
    cryptopals
    VERSION 0.1.0
    LANGUAGES C
)

add_executable(
    cryptopals
    main.c
)

# NOTE: target_compile_features sometimes doesn't set the standard properly, but the below works fine.
set_target_properties(
    cryptopals
    PROPERTIES
    C_STANDARD 23
    C_STANDARD_REQUIRED ON
    # TODO: turn this off as soon as we fix file io (or get rid of file io entirely).
    C_EXTENSIONS ON
    EXPORT_COMPILE_COMMANDS ON
)

target_include_directories(
    cryptopals
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_options(
    cryptopals
    PUBLIC
    -Wall
    -Wextra
    -Werror
    -Wpedantic
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
