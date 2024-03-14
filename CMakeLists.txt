cmake_minimum_required(VERSION 3.18)
project(CLI)

file(GLOB CLI_SRC
    "src/*.hpp"
    "src/*.cpp"
)

file (GLOB CLI_BINARIES
    "bin/*.dll"
)

list(GET CMAKE_CONFIGURATION_TYPES 0 CMAKE_BUILD_TYPE)
# if cli binaries are not found, copy them from the build directory
if (CLI_BINARIES)
    add_custom_target(CopyBinaries ALL
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CLI_BINARIES} ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}
    )
    add_dependencies(CopyBinaries CLI)
endif()

add_executable(CLI ${CLI_SRC})
include_directories(CLI PUBLIC "include")
link_directories(CLI PUBLIC "lib")
set_property(TARGET CLI PROPERTY CXX_STANDARD 17)
