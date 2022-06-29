include(FetchContent)
FetchContent_Declare(dxsdk
    GIT_REPOSITORY https://github.com/hrydgard/minidx9.git
    GIT_TAG master
)

message("Fetching DirectX SDK from GitHub...")

FetchContent_MakeAvailable(dxsdk)
message("DirectX SDK path: ${dxsdk_SOURCE_DIR}")