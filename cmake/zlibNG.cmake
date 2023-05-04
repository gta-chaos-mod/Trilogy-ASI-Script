include(FetchContent)
# FetchContent_Declare(LIB_ZLIB_NG
#   URL https://zlib.net/zlib1213.zip)

FetchContent_Declare(LIB_ZLIB_NG
  GIT_REPOSITORY https://github.com/zlib-ng/zlib-ng/
  GIT_TAG 2.0.7)

set(ZLIB_COMPAT ON)

message("Fetching zlib-ng from GitHub...")
FetchContent_MakeAvailable (LIB_ZLIB_NG)

FetchContent_GetProperties(LIB_ZLIB_NG
  SOURCE_DIR LIB_ZLIB_SOURCE_DIR
  BINARY_DIR LIB_ZLIB_BINARY_DIR)