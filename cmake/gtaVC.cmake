######################################################################
############################ GTA Vice City ###########################
set(CHAOS_VC ${PROJECT_NAME}.VC)

file(GLOB_RECURSE VC_SOURCES CONFIGURE_DEPENDS src/TrilogyChaosMod.cpp src/shared/*.cpp src/gtavc/*.cpp)

add_library(${CHAOS_VC} SHARED ${VC_SOURCES})

set_target_properties(${CHAOS_VC} PROPERTIES SUFFIX ".asi")

target_include_directories(${CHAOS_VC} PUBLIC "src/shared/" "src/gtavc")

target_link_libraries(${CHAOS_VC} PUBLIC plugin_vc)

target_compile_definitions(${CHAOS_VC} PUBLIC NOMINMAX)
######################################################################