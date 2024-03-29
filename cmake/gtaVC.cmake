# #####################################################################
# ########################### GTA Vice City ###########################
set(CHAOS_VC ${PROJECT_NAME}.VC)

file(GLOB_RECURSE VC_SOURCES CONFIGURE_DEPENDS src/TrilogyChaosMod.cpp src/shared/*.cpp src/gtavc/*.cpp)

add_library(${CHAOS_VC} SHARED ${VC_SOURCES})

set_target_properties(${CHAOS_VC} PROPERTIES SUFFIX ".asi")

target_include_directories(${CHAOS_VC} PUBLIC "src/shared/" "src/gtavc" "${dxsdk_SOURCE_DIR}/Include")

target_link_directories(${CHAOS_VC} PUBLIC
    lib/
    "${dxsdk_SOURCE_DIR}/Lib/x86"
)
target_link_libraries(${CHAOS_VC} PUBLIC plugin_vc nlohmann_json uWebSockets minhook efsw bass)

target_compile_definitions(${CHAOS_VC} PUBLIC NOMINMAX)

# Include global definitions like colors
target_precompile_headers(
    ${CHAOS_VC}
    PUBLIC
    src/shared/_include/Definitions.h
    src/shared/_include/cpptoml.h
    lib/bass.h
)

# Include specific libraries for easier use
target_precompile_headers(
    ${CHAOS_VC}
    PRIVATE
    <plugin.h>
    <nlohmann/json.hpp>
    <App.h>
)

# #####################################################################