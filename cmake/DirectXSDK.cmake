include(FetchContent)

FetchContent_Declare(
    dxsdk
    GIT_REPOSITORY https://github.com/hrydgard/minidx9.git
    GIT_TAG master
)

FetchContent_MakeAvailable(dxsdk)

# Wrap in an INTERFACE target for modern CMake target-based linking
if(NOT TARGET dxsdk)
    add_library(dxsdk INTERFACE)
    target_include_directories(dxsdk INTERFACE "${dxsdk_SOURCE_DIR}/Include")
    target_link_directories(dxsdk INTERFACE "${dxsdk_SOURCE_DIR}/Lib/x86")
endif()