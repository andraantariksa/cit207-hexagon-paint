cmake_minimum_required(VERSION 3.10)
include(FetchContent)

project(2DComputerGraphicsAndAnimation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(FETCHCONTENT_QUIET OFF)

# SFML
set(SFML_VERSION "2.5.1")
FetchContent_Declare(
    sfml
    GIT_REPOSITORY "https://github.com/SFML/SFML.git"
	GIT_TAG        "${SFML_VERSION}"
)
FetchContent_GetProperties(sfml)
if(NOT sfml_POPULATED)
    FetchContent_Populate(sfml)
    add_subdirectory("${sfml_SOURCE_DIR}" "${sfml_BINARY_DIR}")
endif()

set(SOURCE
    "src/main.cpp"
)

add_executable(2DComputerGraphicsAndAnimationApp
    "${SOURCE}"
)

target_link_libraries(2DComputerGraphicsAndAnimationApp
    PRIVATE
        "sfml-audio"
        "sfml-graphics"
        "sfml-system"
        "sfml-window"
)
