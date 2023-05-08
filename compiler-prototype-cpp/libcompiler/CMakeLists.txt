cmake_minimum_required(VERSION 3.21)
project(libcompiler)
message(DEBUG "[CMake Debug] Generating project ${PROJECT_NAME}...")

########################################
# Target
########################################
set(target_name "${PROJECT_NAME}")
add_library(${target_name} STATIC)

########################################
# Source
########################################
# RELATIVE doesn't work with a parent folder
# file(GLOB_RECURSE source_local CONFIGURE_DEPENDS
#     RELATIVE "${CMAKE_SOURCE_DIR}"
#     "include/${target_name}/*.hpp"
#     "${target_name}/*.hpp"
#     "${target_name}/*.cpp"
# )

# ${CMAKE_SOURCE_DIR} == ../${CMAKE_CURRENT_SOURCE_DIR}
file(GLOB_RECURSE source_local CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/include/${target_name}/*.hpp"
    "${CMAKE_SOURCE_DIR}/${target_name}/*.hpp"
    "${CMAKE_SOURCE_DIR}/${target_name}/*.cpp"
)
target_sources(${target_name} PRIVATE ${source_local})

########################################
# Include
########################################
target_include_directories(${target_name} PRIVATE
    "${CMAKE_SOURCE_DIR}/include"
    "${CMAKE_SOURCE_DIR}"
)

########################################
# Source Groups
########################################
# source code
set(source_groups
)
foreach(group ${source_groups})
    file(GLOB_RECURSE group_src CONFIGURE_DEPENDS
        "${CMAKE_SOURCE_DIR}/${target_name}/${group}/*.hpp"
        "${CMAKE_SOURCE_DIR}/${target_name}/${group}/*.cpp"
    )
    source_group("${group}" FILES ${group_src})
endforeach()

# export header
set(group "export")
file(GLOB group_src CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/include/${target_name}/*.hpp"
)
source_group("${group}" FILES ${group_src})
