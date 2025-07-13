include(FetchContent)
FetchContent_Declare(EFSW
	GIT_REPOSITORY https://github.com/SpartanJ/efsw
	GIT_TAG 1.4.1)

message("Fetching efsw from GitHub...")
FetchContent_MakeAvailable(EFSW)