include(FetchContent)

FetchContent_Declare(json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.7.3)

#FetchContent_GetProperties(json)
#if(NOT json_POPULATED)
#    FetchContent_Populate(json)
#    add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
#endif()

FetchContent_MakeAvailable(json)

set(CPR_BUILD_TESTS OFF)
set(CPR_BUILD_TESTS_SSL OFF)
include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY
        https://github.com/libcpr/cpr.git
        GIT_TAG 1.6.2) # the commit hash for 1.6.2
FetchContent_MakeAvailable(cpr)
