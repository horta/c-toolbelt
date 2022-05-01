cmake_minimum_required(VERSION 3.16.3 FATAL_ERROR)

project(
  c_toolbelt
  VERSION 0.2.0
  LANGUAGES C)

# Generate compile_commands.json file
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(cmake/compiler-options.cmake)
include(cmake/sanitizers.cmake)

add_library(${PROJECT_NAME} src/c_toolbelt.c)
add_library(C_TOOLBELT::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

set(EXPORT_FILE ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/export.h)
include(GenerateExportHeader)
generate_export_header(
  ${PROJECT_NAME}
  BASE_NAME
  CTB
  INCLUDE_GUARD_NAME
  C_TOOLBELT_EXPORT_H
  EXPORT_MACRO_NAME
  CTB_API
  EXPORT_FILE_NAME
  ${EXPORT_FILE})

if(CMAKE_BUILD_TYPE STREQUAL "Release")
  include(CheckIPOSupported)
  check_ipo_supported()
  set_target_properties(${PROJECT_NAME} PROPERTIES INTERPROCEDURAL_OPTIMIZATION
                                                   TRUE)
endif()

target_compile_features(${PROJECT_NAME} PRIVATE c_std_11)
target_compile_options(${PROJECT_NAME} PRIVATE ${WARNING_FLAGS})

target_include_directories(
  ${PROJECT_NAME}
  PUBLIC $<INSTALL_INTERFACE:include>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
  PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>)

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}-targets)

install(DIRECTORY include/${PROJECT_NAME}/ DESTINATION include/${PROJECT_NAME})

install(
  EXPORT ${PROJECT_NAME}-targets
  FILE ${PROJECT_NAME}-targets.cmake
  NAMESPACE C_TOOLBELT::
  DESTINATION lib/cmake/${PROJECT_NAME})

include(CMakePackageConfigHelpers)

set(CMAKE_CONFIG_FILE ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake)
configure_package_config_file(
  ${PROJECT_NAME}-config.cmake.in ${CMAKE_CONFIG_FILE}
  INSTALL_DESTINATION lib/cmake/${PROJECT_NAME})

set(CMAKE_VERSION_FILE
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake)
write_basic_package_version_file(${CMAKE_VERSION_FILE}
                                 COMPATIBILITY SameMajorVersion)

install(FILES ${CMAKE_VERSION_FILE} ${CMAKE_CONFIG_FILE}
        DESTINATION lib/cmake/${PROJECT_NAME})
install(FILES ${EXPORT_FILE} DESTINATION include/${PROJECT_NAME})

set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VENDOR "Danilo Horta")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY
    "Additional functions to the standard C library")
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