cmake_minimum_required(VERSION 3.21)
project(test)
message(DEBUG "[CMake Debug] Generating project ${PROJECT_NAME}...")

################################################################################
# Target
################################################################################
set(target_name "${PROJECT_NAME}")
add_executable(${target_name})

################################################################################
# Source
################################################################################
file(GLOB_RECURSE source_local CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/${target_name}/*.hpp"
    "${CMAKE_SOURCE_DIR}/${target_name}/*.cpp"
)
target_sources(${target_name} PRIVATE ${source_local})

################################################################################
# Include
################################################################################
target_include_directories(${target_name} PRIVATE
    "${CMAKE_SOURCE_DIR}/include"
    "${CMAKE_SOURCE_DIR}"
)

########################################
# Source Groups
########################################
# all in "src" folder
set(group "src")
source_group("${group}" FILES ${source_local})

################################################################################
# Link
################################################################################
target_link_libraries(${target_name} PRIVATE
    libcompiler
)

################################################################################
# Debugging (for Visual Studio project only)
################################################################################
if(MSVC)
    # asset directory
    set_target_properties(${target_name}
                          PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY
                          ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif()
