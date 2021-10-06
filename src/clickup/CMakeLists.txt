### config for s3

add_library(clickup STATIC
        clickup.cpp
        clickup.h
        )

add_library(clickup::clickup ALIAS clickup)

target_link_libraries(clickup
        nlohmann_json::nlohmann_json
        cpr::cpr
        )

#target_include_directories(clickup PUBLIC src/clickup)
#
#target_include_directories(clickup PRIVATE "${CMAKE_BINARY_DIR}" "${PROJECT_BINARY_DIR}")
