cmake_minimum_required(VERSION 3.16.3 FATAL_ERROR)

project(
  c_toolbelt
  VERSION 0.6.1
  LANGUAGES C
)

# Generate compile_commands.json file
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(cmake/compiler-options.cmake)
include(cmake/sanitizers.cmake)

add_library(ctb src/endian.c src/strlcpy.c src/realloc.c src/bzero.c src/strtok_s.c)
add_library(C_TOOLBELT::ctb ALIAS ctb)

set(EXPORT_FILE ${CMAKE_CURRENT_BINARY_DIR}/ctb/export.h)
include(GenerateExportHeader)
generate_export_header(
  ctb
  BASE_NAME
  CTB
  INCLUDE_GUARD_NAME
  C_TOOLBELT_EXPORT_H
  EXPORT_MACRO_NAME
  CTB_API
  EXPORT_FILE_NAME
  ${EXPORT_FILE}
)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
  include(CheckIPOSupported)
  check_ipo_supported()
  set_target_properties(ctb PROPERTIES INTERPROCEDURAL_OPTIMIZATION ON)
endif()

target_compile_features(ctb PRIVATE c_std_11)
target_compile_options(ctb PRIVATE ${WARNING_FLAGS})
set_target_properties(ctb PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_include_directories(
  ctb
  PUBLIC $<INSTALL_INTERFACE:include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
  PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)

install(TARGETS ctb EXPORT ctb-targets)

install(DIRECTORY include/ctb/ DESTINATION include/ctb)

install(
  EXPORT ctb-targets
  FILE ctb-targets.cmake
  NAMESPACE C_TOOLBELT::
  DESTINATION lib/cmake/ctb
)

include(CMakePackageConfigHelpers)

set(CMAKE_CONFIG_FILE ${CMAKE_CURRENT_BINARY_DIR}/ctb-config.cmake)
configure_package_config_file(
  ctb-config.cmake.in ${CMAKE_CONFIG_FILE}
  INSTALL_DESTINATION lib/cmake/ctb
)

set(
  CMAKE_VERSION_FILE
  ${CMAKE_CURRENT_BINARY_DIR}/ctb-config-version.cmake
)
write_basic_package_version_file(
  ${CMAKE_VERSION_FILE}
  COMPATIBILITY SameMajorVersion
)

install(
  FILES ${CMAKE_VERSION_FILE} ${CMAKE_CONFIG_FILE}
  DESTINATION lib/cmake/ctb
)
install(FILES ${EXPORT_FILE} DESTINATION include/ctb)

set(CPACK_PACKAGE_NAME c_toolbelt)
set(CPACK_PACKAGE_VENDOR "Danilo Horta")
set(
  CPACK_PACKAGE_DESCRIPTION_SUMMARY
  "Additional functions to the standard C library"
)
set(CPACK_PACKAGE_CONTACT "Danilo Horta")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE)
set(CPACK_RESOURCE_FILE_README ${CMAKE_CURRENT_SOURCE_DIR}/README.md)
set(CPACK_OUTPUT_FILE_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/package)
set(CPACK_VERBATIM_VARIABLES YES)
set(CPACK_PACKAGE_RELOCATABLE YES)
set(CPACK_MONOLITHIC_INSTALL YES)
include(CPack)
