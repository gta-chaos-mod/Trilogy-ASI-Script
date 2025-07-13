include(FetchContent)

FetchContent_Declare(json
	URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz)

message("Fetching nlohmann::json from GitHub...")
FetchContent_MakeAvailable(json)