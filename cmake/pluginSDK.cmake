include(FetchContent)
FetchContent_Declare(plugin-sdk
  GIT_REPOSITORY https://github.com/gta-chaos-mod/plugin-sdk
  GIT_SHALLOW)

set(PSDK_BUILD_III ON)
set(PSDK_BUILD_VC ON)
set(PSDK_BUILD_SA ON)

message("Fetching plugin-sdk from GitHub...")
FetchContent_MakeAvailable(plugin-sdk)