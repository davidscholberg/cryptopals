cmake_minimum_required(VERSION 3.24)
project(cryptopals VERSION 0.1.0 LANGUAGES C)

add_executable(
    cryptopals
    main.c
)
target_include_directories(
    cryptopals
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)
target_compile_features(cryptopals PUBLIC c_std_17)
target_compile_options(cryptopals PUBLIC -Wall -Wextra -Werror -Wpedantic)

add_subdirectory(analysis)
add_subdirectory(ciphers)
add_subdirectory(codecs)
add_subdirectory(external)
add_subdirectory(resources)
add_subdirectory(solutions)
add_subdirectory(uncrypt)
add_subdirectory(utility)
