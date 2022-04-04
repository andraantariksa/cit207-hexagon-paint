cmake_minimum_required(VERSION 3.10)
include(FetchContent)

project(HexagonPaint
        LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(FETCHCONTENT_QUIET OFF)

set(BUILD_SHARED_LIBS FALSE)

# SFML
set(SFML_VERSION "2.5.1")
FetchContent_Declare(
        sfml
        GIT_REPOSITORY "https://github.com/SFML/SFML.git"
        GIT_TAG "${SFML_VERSION}"
)
FetchContent_GetProperties(sfml)
if (NOT sfml_POPULATED)
    FetchContent_Populate(sfml)
    add_subdirectory("${sfml_SOURCE_DIR}" "${sfml_BINARY_DIR}")
endif ()

# ImGui
set(IMGUI_VERSION "1.74")
FetchContent_Declare(
        imgui
        GIT_REPOSITORY "https://github.com/ocornut/imgui.git"
        GIT_TAG "v${IMGUI_VERSION}"
)
FetchContent_GetProperties(imgui)
if (NOT imgui_POPULATED)
    FetchContent_Populate(imgui)
    #add_subdirectory("${imgui_SOURCE_DIR}" "${imgui_BINARY_DIR}")
endif ()

# ImGui-SFML
set(IMGUI_SFML_VERSION "2.1")
FetchContent_Declare(
        imgui_sfml
        GIT_REPOSITORY "https://github.com/eliasdaler/imgui-sfml.git"
        GIT_TAG "v${IMGUI_SFML_VERSION}"
)

set(IMGUI_DIR ${imgui_SOURCE_DIR})
set(IMGUI_SFML_FIND_SFML CACHE BOOL FALSE)

FetchContent_GetProperties(imgui_sfml)
if (NOT imgui_sfml_POPULATED)
    FetchContent_Populate(imgui_sfml)
    add_subdirectory("${imgui_sfml_SOURCE_DIR}" "${imgui_sfml_BINARY_DIR}")
endif ()

add_executable(HexagonPaint

        "lib/tinyfiledialogs/tinyfiledialogs.c"
        "lib/lodepng/lodepng.cpp"
        "lib/lodepng/lodepng_fuzzer.cpp"
        "lib/lodepng/lodepng_util.cpp"

        "src/main.cpp"
        "src/helpers.cpp"
        "src/helpers.hpp"
        "src/canvas.cpp"
        "src/canvas.hpp"
        "src/color.hpp"
        "src/shape/line.cpp"
        "src/shape/line.hpp"
        "src/fps.cpp"
        "src/fps.hpp"
        "src/application.cpp"
        "src/application.hpp")

target_include_directories(HexagonPaint
        PRIVATE "lib/tinyfiledialogs"
        PRIVATE "lib/stb"
        PRIVATE "lib/lodepng")

target_link_libraries(HexagonPaint
        PUBLIC
        #        "sfml-graphics"
        #        "sfml-system"
        #        "sfml-window"
        ImGui-SFML::ImGui-SFML
        )