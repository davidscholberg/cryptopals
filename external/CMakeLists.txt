include(FetchContent)

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
