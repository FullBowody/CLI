cmake_minimum_required(VERSION 3.15)
project(CLI)

file(GLOB CLI_SRC
    "src/*.hpp"
    "src/*.cpp"
)

file (GLOB CLI_BINARIES
    "bin/*.dll"
)

list(GET CMAKE_CONFIGURATION_TYPES 0 CMAKE_BUILD_TYPE)
add_custom_target(CopyBinaries ALL
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CLI_BINARIES} ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}
)

add_executable(CLI ${CLI_SRC})
add_dependencies(CLI CopyBinaries)
target_include_directories(CLI PUBLIC "include")
target_link_directories(CLI PUBLIC "lib")
