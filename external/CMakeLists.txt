include(ExternalProject)

ExternalProject_Add(
    libgpg-error
    URL https://gnupg.org/ftp/gcrypt/libgpg-error/libgpg-error-1.47.tar.bz2
    URL_HASH SHA512=bbb4b15dae75856ee5b1253568674b56ad155524ae29a075cb5b0a7e74c4af685131775c3ea2226fff2f84ef80855e77aa661645d002b490a795c7ae57b66a30
    CONFIGURE_COMMAND <SOURCE_DIR>/configure --prefix=<INSTALL_DIR> --enable-static --enable-install-gpg-error-config --disable-doc
    # NOTE: there's currently a bug with this project's tests so we have to skip them for now.
    #TEST_COMMAND make check
    #TEST_BEFORE_INSTALL true
)

ExternalProject_Get_Property(libgpg-error INSTALL_DIR)

ExternalProject_Add(
    libgcrypt
    URL https://gnupg.org/ftp/gcrypt/libgcrypt/libgcrypt-1.10.2.tar.bz2
    URL_HASH SHA512=3a850baddfe8ffe8b3e96dc54af3fbb9e1dab204db1f06b9b90b8fbbfb7fb7276260cd1e61ba4dde5a662a2385385007478834e62e95f785d2e3d32652adb29e
    CONFIGURE_COMMAND <SOURCE_DIR>/configure --prefix=<INSTALL_DIR> --enable-static --with-libgpg-error-prefix=${INSTALL_DIR} --disable-doc
    TEST_COMMAND make check
    TEST_BEFORE_INSTALL true
)
add_dependencies(
    libgcrypt
    libgpg-error
)

add_dependencies(
    cryptopals
    libgcrypt
)
ExternalProject_Get_Property(libgcrypt INSTALL_DIR)
target_include_directories(
    cryptopals
    PRIVATE
    ${INSTALL_DIR}/include
)
target_link_libraries(
    cryptopals
    PRIVATE
    ${INSTALL_DIR}/lib/libgcrypt.a
)

# The following has to be specified down here because I don't know of a better way of having cmake
# get the link order correct for libgpg-error and libgcrypt.
add_dependencies(
    cryptopals
    libgpg-error
)
ExternalProject_Get_Property(libgpg-error INSTALL_DIR)
target_include_directories(
    cryptopals
    PRIVATE
    ${INSTALL_DIR}/include
)
target_link_libraries(
    cryptopals
    PRIVATE
    ${INSTALL_DIR}/lib/libgpg-error.a
)
