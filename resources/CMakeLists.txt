set(
    resources
    s04_hex_string_array.txt
    s06_base64_string.txt
    s07_base64_string.txt
    s08_hex_string_array.txt
    s10_base64_string.txt
    s19_base64_string_array.txt
    s20_base64_string_array.txt
    s25_base64_string.txt
)
foreach(resource IN LISTS resources)
    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${resource}
        COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_SOURCE_DIR}/${resource}
            ${CMAKE_CURRENT_BINARY_DIR}/${resource}
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${resource}
    )
endforeach()
list(TRANSFORM resources PREPEND ${CMAKE_CURRENT_BINARY_DIR}/)
add_custom_target(copy_resources ALL DEPENDS ${resources})
add_dependencies(cryptopals copy_resources)
