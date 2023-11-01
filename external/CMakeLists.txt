include(FetchContent)

FetchContent_Declare(
    tiny-aes
    GIT_REPOSITORY https://github.com/kokke/tiny-AES-c.git
    GIT_TAG f06ac37fc31dfdaca2e0d9bec83f90d5663c319b
)
FetchContent_MakeAvailable(tiny-aes)
target_link_libraries(
    cryptopals
    PRIVATE
    tiny-aes
)
