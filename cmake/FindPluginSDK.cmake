#[=======================================================================[.rst:
FindPluginSDK
-------------

FindModule for Plugin-SDK library (https://github.com/DK22Pac/plugin-sdk).
Created by THE-FYP - https://gist.github.com/THE-FYP/104855c5fdd7311a336a5178a0b33118
Slightly modified to support RenderWare includes

COMPONENTS
^^^^^^^^^^

This module respects several components: ``gta3``, ``gtavc``, and ``gtasa``.
There are corresponding import targets for each of these flags.
No targets will be defined if no components are specified.

IMPORTED Targets
^^^^^^^^^^^^^^^^

This module defines the :prop_tgt:`IMPORTED` targets:

``PluginSDK::gta3``
 Defined to the libraries for GTA: III when component ``gta3`` is specified.
``PluginSDK::gtavc``
 Defined to the libraries for GTA: Vice City when component ``gtavc`` is specified.
``PluginSDK::gtasa``
 Defined to the libraries for GTA: San Andreas if component ``gtasa`` is specified.

Result Variables
^^^^^^^^^^^^^^^^

This module sets the following variables:

``PluginSDK_FOUND``
 True, if the system has Plugin-SDK and all specified components are found.
``PluginSDK_shared_INCLUDE_DIRS``
 Paths to the directories containing shared headers.
``PluginSDK_gta3_FOUND``
 True, if all parts of the ``gta3`` component are found.
``PluginSDK_gta3_INCLUDE_DIRS``
 Paths to the include directories of the ``gta3`` component.
``PluginSDK_gta3_LIBRARIES``
 Paths to libraries of the ``gta3`` component.
``PluginSDK_gtavc_FOUND``
 True, if all parts of the ``gtavc`` component are found.
``PluginSDK_gtavc_INCLUDE_DIRS``
 Paths to the include directories of the ``gtavc`` component.
``PluginSDK_gtavc_LIBRARIES``
 Paths to libraries of the ``gtavc`` component.
``PluginSDK_gtasa_FOUND``
 True, if all parts of the ``gtasa`` component are found.
``PluginSDK_gtasa_INCLUDE_DIRS``
 Paths to the include directories of the ``gtasa`` component.
``PluginSDK_gtasa_LIBRARIES``
 Paths to libraries of the ``gtasa`` component.

Cache variables
^^^^^^^^^^^^^^^

The following cache variables may also be set:

``PluginSDK_ROOT_DIR``
 Path to the Plugin-SDK root directory.
``PluginSDK_shared_INCLUDE_DIR``
 Path to the Plugin-SDK shared headers root directory.
``PluginSDK_gta3_LIBRARY``
 Path to the library of the ``gta3`` component selected for the given build configuration.
``PluginSDK_gta3_LIBRARY_RELEASE``
 Path to the optimized library of the ``gta3`` component.
``PluginSDK_gta3_LIBRARY_DEBUG``
 Path to the debug library of the ``gta3`` component.
``PluginSDK_gtavc_LIBRARY``
 Path to the library of the ``gtavc`` component selected for the given build configuration.
``PluginSDK_gtavc_LIBRARY_RELEASE``
 Path to the optimized library of the ``gtavc`` component.
``PluginSDK_gtavc_LIBRARY_DEBUG``
 Path to the debug library of the ``gtavc`` component.
``PluginSDK_gtasa_LIBRARY``
 Path to the library of the ``gtasa`` component selected for the given build configuration.
``PluginSDK_gtasa_LIBRARY_RELEASE``
 Path to the optimized library of the ``gtasa`` component.
``PluginSDK_gtasa_LIBRARY_DEBUG``
 Path to the debug library of the ``gtasa`` component.
#]=======================================================================]

include(FindPackageHandleStandardArgs)
include(SelectLibraryConfigurations)

find_path(PluginSDK_ROOT_DIR
  NAMES "shared/PluginBase.h"
  HINTS
    "${PluginSDK_ROOT}"
    ENV PLUGIN_SDK_DIR
  NO_DEFAULT_PATH
)

# Shared
find_path(PluginSDK_shared_INCLUDE_DIR
  NAMES "PluginBase.h"
  HINTS "${PluginSDK_ROOT_DIR}/shared"
  NO_DEFAULT_PATH
)
if(PluginSDK_shared_INCLUDE_DIR)
  set(PluginSDK_shared_INCLUDE_DIRS
    "${PluginSDK_shared_INCLUDE_DIR}"
    "${PluginSDK_shared_INCLUDE_DIR}/game"
  )
endif()

# GTA III
set(PluginSDK_gta3_REL_LIB_NAMES "plugin_iii")
set(PluginSDK_gta3_DBG_LIB_NAMES "plugin_iii_d")
set(PluginSDK_gta3_INC_NAMES "plugin_III.h")
set(PluginSDK_gta3_INCDIR_NAME "plugin_III")
set(PluginSDK_gta3_GAME_INCDIR_NAME "game_III")
set(PluginSDK_gta3_DEFINES
  PLUGIN_SGV_10EN
  GTA3
  GTAGAME_NAME="3"
  GTAGAME_ABBR="3"
  GTAGAME_ABBRLOW="3"
  GTAGAME_PROTAGONISTNAME="Claude"
  GTAGAME_CITYNAME="Liberty City"
  RW
)

# GTA: VC
set(PluginSDK_gtavc_REL_LIB_NAMES "plugin_vc")
set(PluginSDK_gtavc_DBG_LIB_NAMES "plugin_vc_d")
set(PluginSDK_gtavc_INC_NAMES "plugin_vc.h")
set(PluginSDK_gtavc_INCDIR_NAME "plugin_vc")
set(PluginSDK_gtavc_GAME_INCDIR_NAME "game_vc")
set(PluginSDK_gtavc_DEFINES
  PLUGIN_SGV_10EN
  GTAVC
  GTAGAME_NAME="Vice City"
  GTAGAME_ABBR="VC"
  GTAGAME_ABBRLOW="vc"
  GTAGAME_PROTAGONISTNAME="Tommy"
  GTAGAME_CITYNAME="Vice City"
  RW
)

# GTA: SA
set(PluginSDK_gtasa_REL_LIB_NAMES "plugin" "plugin_sa")
set(PluginSDK_gtasa_DBG_LIB_NAMES "plugin_d" "plugin_sa_d")
set(PluginSDK_gtasa_INC_NAMES "plugin_sa.h")
set(PluginSDK_gtasa_INCDIR_NAME "plugin_sa")
set(PluginSDK_gtasa_GAME_INCDIR_NAME "game_sa")
set(PluginSDK_gtasa_DEFINES
  PLUGIN_SGV_10US
  GTASA
  GTAGAME_NAME="San Andreas"
  GTAGAME_ABBR="SA"
  GTAGAME_ABBRLOW="sa"
  GTAGAME_PROTAGONISTNAME="CJ"
  GTAGAME_CITYNAME="San Andreas"
  RW
)

foreach(comp_name ${PluginSDK_FIND_COMPONENTS})
  set(component PluginSDK_${comp_name})
  if(${component}_INC_NAMES)
    find_path(${component}_INCLUDE_DIR
      NAMES ${${component}_INC_NAMES}
      HINTS "${PluginSDK_ROOT_DIR}/${${component}_INCDIR_NAME}"
      NO_DEFAULT_PATH
    )
    if(${component}_INCLUDE_DIR)
      set(${component}_INCLUDE_DIRS
        "${${component}_INCLUDE_DIR}"
        "${${component}_INCLUDE_DIR}/${${component}_GAME_INCDIR_NAME}"
        "${${component}_INCLUDE_DIR}/${${component}_GAME_INCDIR_NAME}/enums"
        "${${component}_INCLUDE_DIR}/${${component}_GAME_INCDIR_NAME}/rw"
      )
    endif()

    find_library(${component}_LIBRARY_RELEASE
      NAMES ${${component}_REL_LIB_NAMES}
      HINTS "${PluginSDK_ROOT_DIR}/output"
      PATH_SUFFIXES "lib"
      NO_DEFAULT_PATH
    )
    find_library(${component}_LIBRARY_DEBUG
      NAMES ${${component}_DBG_LIB_NAMES}
      HINTS "${PluginSDK_ROOT_DIR}/output"
      PATH_SUFFIXES "lib"
      NO_DEFAULT_PATH
    )

    select_library_configurations("${component}")
    mark_as_advanced(${component}_INCLUDE_DIR)

    set(target PluginSDK::${comp_name})
    if(${component}_FOUND AND NOT TARGET ${target})
      add_library(${target} STATIC IMPORTED)
      target_include_directories(${target}
        INTERFACE
          "${${component}_INCLUDE_DIRS}"
          "${PluginSDK_shared_INCLUDE_DIRS}"
      )
      target_compile_definitions(${target}
        INTERFACE
          "_CRT_SECURE_NO_WARNINGS"
          "_CRT_NON_CONFORMING_SWPRINTFS"
          ${${component}_DEFINES}
      )
      set_target_properties(${target}
        PROPERTIES
          IMPORTED_LOCATION "${${component}_LIBRARY_RELEASE}"
          IMPORTED_LOCATION_DEBUG "${${component}_LIBRARY_DEBUG}"
      )
    endif()
  else()
    message(FATAL_ERROR "Wrong component name: ${component}")
  endif()
endforeach()

find_package_handle_standard_args("PluginSDK" REQUIRED_VARS PluginSDK_ROOT_DIR HANDLE_COMPONENTS)
mark_as_advanced(PluginSDK_ROOT_DIR PluginSDK_shared_INCLUDE_DIR)
