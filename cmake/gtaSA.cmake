######################################################################
########################### GTA San Andreas ##########################
set(CHAOS_SA ${PROJECT_NAME}.SA)

file(GLOB_RECURSE SA_SOURCES CONFIGURE_DEPENDS src/TrilogyChaosMod.cpp src/shared/*.cpp src/gtasa/*.cpp)

add_library(${CHAOS_SA} SHARED ${SA_SOURCES})

set_target_properties(${CHAOS_SA} PROPERTIES SUFFIX ".asi")

target_include_directories(${CHAOS_SA} PUBLIC "src/shared/" "src/gtasa")

target_link_libraries(${CHAOS_SA} PUBLIC plugin_sa)

target_compile_definitions(${CHAOS_SA} PUBLIC NOMINMAX)
######################################################################