set(
    resource_filenames
    s04_hex_string_array.txt
    s06_base64_string.txt
    s07_base64_string.txt
    s08_hex_string_array.txt
    s10_base64_string.txt
    s19_base64_string_array.txt
    s20_base64_string_array.txt
    s25_base64_string.txt
)

add_custom_command(
    OUTPUT resources.c
    COMMAND cesources --input-dir ${CMAKE_CURRENT_SOURCE_DIR}/ ${resource_filenames}
    DEPENDS cesources ${resource_filenames}
)

add_library(
    cryptopals_resources
    OBJECT
    resources.c
)

set_target_properties(
    cryptopals_resources
    PROPERTIES
    C_STANDARD 99
    C_STANDARD_REQUIRED ON
    C_EXTENSIONS OFF
)

target_compile_options(
    cryptopals_resources
    PRIVATE
    -Wall
    -Wextra
    -Werror
    -Wpedantic
)

target_sources(
    cryptopals
    PRIVATE
    resources.h
    $<TARGET_OBJECTS:cryptopals_resources>
)

# old way of handling resource files
foreach(resource IN LISTS resource_filenames)
    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${resource}
        COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_SOURCE_DIR}/${resource}
            ${CMAKE_CURRENT_BINARY_DIR}/${resource}
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${resource}
    )
endforeach()
list(TRANSFORM resource_filenames PREPEND ${CMAKE_CURRENT_BINARY_DIR}/)
add_custom_target(copy_resources ALL DEPENDS ${resource_filenames})
add_dependencies(cryptopals copy_resources)
