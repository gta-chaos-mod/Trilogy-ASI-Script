include(FetchContent)

# Disable unnecessary tests and examples
set(LSM_BUILD_TEST OFF CACHE BOOL "" FORCE)
set(LSM_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_Declare(libsharedmemory
    GIT_REPOSITORY https://github.com/kyr0/libsharedmemory
    GIT_TAG v2.0.0
)

message("Fetching libsharedmemory from GitHub...")
FetchContent_MakeAvailable(libsharedmemory)

# Remove hardcoded /std:c++20 so it doesn't override C++23 on dependent targets
if(TARGET lsm)
    get_target_property(LSM_COMPILE_OPTIONS lsm INTERFACE_COMPILE_OPTIONS)
    if(LSM_COMPILE_OPTIONS)
        list(REMOVE_ITEM LSM_COMPILE_OPTIONS "/std:c++20" "-std=c++20")
        set_target_properties(lsm PROPERTIES INTERFACE_COMPILE_OPTIONS "${LSM_COMPILE_OPTIONS}")
    endif()
endif()