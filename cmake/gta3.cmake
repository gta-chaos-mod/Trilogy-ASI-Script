# #####################################################################
# ############################### GTA 3 ###############################
set(CHAOS_3 ${PROJECT_NAME}.III)

file(GLOB_RECURSE III_SOURCES CONFIGURE_DEPENDS
	src/TrilogyChaosMod.cpp
	src/shared/*.cpp
	src/shared/*.h
	src/shared/*.hpp
	src/gta3/*.cpp
	src/gta3/*.h
	src/gta3/*.hpp
)

add_library(${CHAOS_3} SHARED ${III_SOURCES})

set_target_properties(${CHAOS_3} PROPERTIES SUFFIX ".asi")

target_include_directories(${CHAOS_3} PUBLIC
	"src/"
	"src/shared"
	"src/gta3"
)

target_link_directories(${CHAOS_3} PUBLIC
	lib/
)

target_link_libraries(${CHAOS_3} PUBLIC
	PluginSDK::gta3
	dxsdk
	nlohmann_json
	ixwebsocket
	minhook
	efsw
	lsm
	bass
)

target_compile_definitions(${CHAOS_3} PUBLIC NOMINMAX)

# Include global definitions like colors
target_precompile_headers(
	${CHAOS_3}
	PUBLIC
	src/shared/_include/Definitions.h
	src/shared/_include/cpptoml.h
	lib/bass.h
)

# Include specific libraries for easier use
target_precompile_headers(
	${CHAOS_3}
	PRIVATE
	<plugin.h>
	<nlohmann/json.hpp>
)

# #####################################################################
