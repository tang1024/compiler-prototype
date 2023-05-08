cmake_minimum_required(VERSION 3.21)
project(
    compiler-prototype-cpp
    VERSION "0.1"
)

#################################################################################
# Include cmake scripts of functions and macros.
#################################################################################
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/setup_compiler.cmake")

#################################################################################
# Compilers and Platforms
#################################################################################
compiler_setup()

#################################################################################
# Programming Language Standards
#################################################################################
set(CMAKE_CXX_STANDARD 20)

#################################################################################
# Debug or Release Build
################################################################################
set(CMAKE_BUILD_TYPE "Debug")

################################################################################
# Output Directories
################################################################################
set(target_dir "${CMAKE_CURRENT_SOURCE_DIR}/target")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${target_dir}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${target_dir}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${target_dir}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${target_dir}/bin")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG}")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE}")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}")
endif()

################################################################################
# Targets
################################################################################
set(sub_dirs
    "libcompiler"
    "test"
)

foreach(sub_dir IN LISTS sub_dirs)
    add_subdirectory("${sub_dir}")
endforeach()

#################################################################################
# Startup Excutable Target (for Visual Studio solution only)
#################################################################################
if(MSVC)
    set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT "test")
endif()
