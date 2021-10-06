
cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)
project(clickup LANGUAGES CXX C)

include_directories("${PROJECT_BINARY_DIR}")

add_executable(clickupExample
            main.cpp)
include(FetchContent)

FetchContent_Declare(clickup
        GIT_REPOSITORY git@github.com:BranchTechnology/clickup-cpp-sdk.git
        GIT_TAG v0.0.2)

target_link_libraries(clickupExample
        clickup
        )
#FetchContent_GetProperties(json)
#if(NOT json_POPULATED)
#    FetchContent_Populate(json)
#    add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
#endif()

FetchContent_MakeAvailable(clickup)