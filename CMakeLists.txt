cmake_minimum_required(VERSION 3.16)
project(TrilogyChaosMod)

# C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POLICY_VERSION_MINIMUM 3.11)

if(CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
	cmake_policy(SET CMP0135 NEW)
endif()

if(MSVC_VERSION GREATER_EQUAL "1900")
  set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
  add_compile_options(/Zc:preprocessor /Zm500)
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")

find_package(PluginSDK REQUIRED COMPONENTS gtasa OPTIONAL_COMPONENTS gta3 gtavc)

# Include cmakes
if (PluginSDK_gta3_FOUND)
  include(cmake/gta3.cmake)
endif()

if (PluginSDK_gtavc_FOUND)
  include(cmake/gtaVC.cmake)
endif()

if (PluginSDK_gtasa_FOUND)
  include(cmake/gtaSA.cmake)
endif()

include(cmake/DirectXSDK.cmake)

include(cmake/nlohmannJSON.cmake)
include(cmake/IXWebSocket.cmake)
include(cmake/minhook.cmake)
include(cmake/efsw.cmake)

if(DEFINED ENV{VERSION_SUFFIX})
	string(SUBSTRING "$ENV{VERSION_SUFFIX}" 0 7 VERSION_SUFFIX)
	message(STATUS "Version Suffix: ${VERSION_SUFFIX}")
endif()

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/src/shared/util/Version.h.in"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/shared/util/Version.h")
