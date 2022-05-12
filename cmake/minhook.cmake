include(FetchContent)
FetchContent_Declare(LIB_MINHOOK
  GIT_REPOSITORY https://github.com/TsudaKageyu/minhook
  GIT_TAG 4a455528f61b5a375b1f9d44e7d296d47f18bb18)

message("Fetching MinHook from GitHub...")
FetchContent_MakeAvailable(LIB_MINHOOK)
