cmake_minimum_required(VERSION 3.15)
project(CLI)

file(GLOB CLI_SRC
    "src/*.hpp"
    "src/*.cpp"
)

add_executable(CLI ${CLI_SRC})
target_include_directories(CLI PUBLIC "include")
target_link_directories(CLI PUBLIC "lib")
