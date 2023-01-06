include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)

message("Fetching nlohmann::json from GitHub...")
FetchContent_MakeAvailable(json)