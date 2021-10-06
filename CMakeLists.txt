cmake_minimum_required(VERSION 3.3)
set(CMAKE_CXX_STANDARD 17)
project(clickup LANGUAGES CXX)

include_directories("${PROJECT_BINARY_DIR}")
add_subdirectory(thirdparty)

# library
add_subdirectory(src/clickup)
target_include_directories(clickup PUBLIC src)

# tests
if($ENV{TEST_CLICKUP})
    message("Generating tests")
    add_subdirectory(test)
elseif(${TEST_CLICKUP})
    message("Generating tests")
    add_subdirectory(test)
else()
    message("Building without tests")
endif()