### config for s3

add_library(clickup STATIC
        clickup.cpp
        )

add_library(clickup::clickup ALIAS clickup)

target_include_directories(clickup SYSTEM PRIVATE
        src/clickup
        $<INSTALL_INTERFACE:src/clickup>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

target_sources(clickup PRIVATE
        clickup.h
        params.h
        )

target_link_libraries(clickup
        nlohmann_json::nlohmann_json
        cpr::cpr
        )

#target_include_directories(clickup PUBLIC src/clickup)
#
#target_include_directories(clickup PRIVATE "${CMAKE_BINARY_DIR}" "${PROJECT_BINARY_DIR}")
