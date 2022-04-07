include(FetchContent)

FetchContent_Declare(json
  GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
  GIT_TAG v3.10.5)

message("Fetching nlohmann::json from GitHub...")
FetchContent_MakeAvailable(json)