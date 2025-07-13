include(FetchContent)
FetchContent_Declare(LIB_MINHOOK
	GIT_REPOSITORY https://github.com/TsudaKageyu/minhook
	GIT_TAG v1.3.4)

message("Fetching MinHook from GitHub...")
FetchContent_MakeAvailable(LIB_MINHOOK)
