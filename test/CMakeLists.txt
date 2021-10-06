#
# Create a target for executing the Catch unit tests.
#

set(CPR_BUILD_TESTS OFF)
set(CPR_BUILD_TESTS_SSL OFF)

add_executable(clickup_test
        main.cpp
        clickup_test.cpp
        )

target_include_directories(clickup_test
        PUBLIC
        test/
        "${PROJECT_BINARY_DIR}"
        "${CMAKE_BINARY_DIR}"
        )

target_link_libraries(clickup_test
        Catch2::Catch2
        clickup
#        nlohmann_json::nlohmann_json
        cpr::cpr
        )

cmake_policy(SET CMP0110 NEW)
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/Modules")
Include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v2.13.1)

FetchContent_MakeAvailable(Catch2)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/contrib)
include(CTest)
include(Catch)
#target_compile_options(test
#        PRIVATE
#        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
#        -Wall -Weffc++ -Wextra -Wsign-conversion -Werror -pedantic-errors>
#        $<$<CXX_COMPILER_ID:MSVC>:
#        /W4>
#        )

# Load and use the .cmake file provided by Catch so all the test cases
# are made available to CTest.
include(ParseAndAddCatchTests)
ParseAndAddCatchTests(clickup_test)