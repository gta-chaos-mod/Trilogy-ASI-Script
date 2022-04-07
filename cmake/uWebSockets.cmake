include(cmake/zlib.cmake)
include(cmake/libuv.cmake)
include(FetchContent)

FetchContent_Declare(LIB_uWebSockets
  GIT_REPOSITORY https://github.com/uNetworking/uWebSockets/
  GIT_TAG v20.12.0)

message("Fetching uWebSockets from GitHub...")
FetchContent_MakeAvailable (LIB_uWebSockets)
FetchContent_GetProperties(LIB_uWebSockets
  SOURCE_DIR LIB_uWebSockets_SOURCE_DIR)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
  ${LIB_uWebSockets_SOURCE_DIR}/uSockets/src/*.c
  ${LIB_uWebSockets_SOURCE_DIR}/uSockets/src/eventing/*.c
  ${LIB_uWebSockets_SOURCE_DIR}/uSockets/src/crypto/*.c
  )

add_library (uWebSockets STATIC ${SOURCES})
target_include_directories(uWebSockets PUBLIC
  ${LIB_uWebSockets_SOURCE_DIR}/src
  ${LIB_uWebSockets_SOURCE_DIR}/uSockets/src
  ${LIB_ZLIB_SOURCE_DIR}
  ${LIB_ZLIB_BINARY_DIR})
target_compile_definitions(uWebSockets PUBLIC -DLIBUS_NO_SSL)
target_link_libraries(uWebSockets PUBLIC uv_a zlibstatic)