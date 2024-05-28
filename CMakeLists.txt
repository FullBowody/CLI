cmake_minimum_required(VERSION 3.18)
project(CLI)

file(GLOB_RECURSE CLI_SRC "src/*.cpp")

include_directories(include)
include_directories(dependencies/Engine/include/public)

add_executable(CLI ${CLI_SRC})
set_property(TARGET CLI PROPERTY CXX_STANDARD 17)
