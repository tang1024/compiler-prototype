################################################################################
# Windows MSVC
################################################################################
function(compiler_setup_win32_msvc)
    add_compile_definitions(
        WIN32_LEAN_AND_MEAN
        NOMINMAX
    )

    # Add compiler options
    # https://cmake.org/cmake/help/latest/command/add_compile_options.html
    # warning level 4 and all warnings as errors
    # Multi-processor Compilation (/MP) for parallel source code compilation
    add_compile_options(/W4 /WX /MP)
endfunction()

################################################################################
# Export
################################################################################
function(compiler_setup)
if (MSVC)
    compiler_setup_win32_msvc()
endif()
endfunction()
