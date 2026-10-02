# Copyright (c) 2023 Nordic Semiconductor
#
# SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
#

if(NOT NRFXLIB_MPSL_FEM_PATH)
  message(FATAL_ERROR "should not hit")
  set(NRFXLIB_MPSL_FEM_PATH "${CMAKE_CURRENT_SOURCE_DIR}")
endif()

function(mpsl_fem_append_lib fem_lib_name)
    set(LIB_DIR "${NRFXLIB_MPSL_PATH}/${NRFXLIB_COMPILER_VARIANT_PATH}/fem/${fem_lib_name}/lib/${CONFIG_MPSL_LIB_DIR}/${CONFIG_MPSL_LIB_FLOAT_ABI_DIR}")

    if(LIB_DIR)
      zephyr_include_directories(${NRFXLIB_MPSL_FEM_PATH}/${fem_lib_name}/include)
      zephyr_link_libraries(${LIB_DIR}/libmpsl_fem_${fem_lib_name}.a)
    endif()
endfunction()

FILE(GLOB subdirlist RELATIVE ${NRFXLIB_MPSL_FEM_PATH} ${NRFXLIB_MPSL_FEM_PATH}/*)

# call mpsl_fem_append_lib for each subdirectory
FOREACH(subdir ${subdirlist})
  IF((IS_DIRECTORY ${NRFXLIB_MPSL_FEM_PATH}/${subdir}) AND NOT (${subdir} STREQUAL "include"))
    mpsl_fem_append_lib(${subdir})
  ENDIF()
ENDFOREACH()

zephyr_include_directories(${NRFXLIB_MPSL_FEM_PATH}/include)
zephyr_include_directories(${NRFXLIB_MPSL_FEM_PATH}/include/protocol)
