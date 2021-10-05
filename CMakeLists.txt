cmake_minimum_required(VERSION 3.3)
set(CMAKE_CXX_STANDARD 17)
project(clickup LANGUAGES CXX)

set(CLICKUP_CONFIG_HEADER ${CMAKE_BINARY_DIR}/config_clickup.h)
message("Generating ${CLICKUP_CONFIG_HEADER}...")
configure_file( src/clickup/config.h.in ${CLICKUP_CONFIG_HEADER} )
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