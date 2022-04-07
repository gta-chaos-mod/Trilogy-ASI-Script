include(FetchContent)
FetchContent_Declare(LIB_ZLIB
  URL https://zlib.net/zlib1212.zip)

message("Fetching zlib from zlib.net...")
FetchContent_MakeAvailable (LIB_ZLIB)

FetchContent_GetProperties(LIB_ZLIB
  SOURCE_DIR LIB_ZLIB_SOURCE_DIR
  BINARY_DIR LIB_ZLIB_BINARY_DIR)