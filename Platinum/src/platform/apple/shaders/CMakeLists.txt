file(GLOB_RECURSE MTLShaders *.metal)

add_custom_command(
        OUTPUT default.metallib
        DEPENDS ${MTLShaders}
        COMMAND xcrun -sdk macosx metal ${MTLShaders}
        WORKING_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
        COMMENT "Compiling Metal Shaders.."
        VERBATIM
)

add_custom_target(mtl_shaders ALL DEPENDS default.metallib)
add_dependencies(Platinum mtl_shaders)
