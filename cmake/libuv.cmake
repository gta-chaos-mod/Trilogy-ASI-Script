include(FetchContent)
FetchContent_Declare(LIB_UV
  GIT_REPOSITORY https://github.com/libuv/libuv
  GIT_TAG v1.44.2)

message("Fetching libuv from GitHub...")
FetchContent_MakeAvailable(LIB_UV)