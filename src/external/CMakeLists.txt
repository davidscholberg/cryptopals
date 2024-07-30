include(FetchContent)

FetchContent_Declare(
    cesources
    GIT_REPOSITORY https://github.com/davidscholberg/cesources.git
    GIT_TAG 3b6bb46f172c411a61c95890b8b2acc91a0f7bfb
)
FetchContent_MakeAvailable(cesources)
add_dependencies(
    cryptopals
    cesources
)
target_include_directories(
    cryptopals
    PRIVATE
    ${cesources_SOURCE_DIR}/src/include
)

FetchContent_Declare(
    tiny-aes
    GIT_REPOSITORY https://github.com/davidscholberg/tiny-AES-c.git
    GIT_TAG f1121188301423e4c54d60629e0695eb7638c59d
)
FetchContent_MakeAvailable(tiny-aes)
target_link_libraries(
    cryptopals
    PRIVATE
    tiny-aes
)
