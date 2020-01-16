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

# ImGui
set(IMGUI_VERSION "1.74")
FetchContent_Declare(
        imgui
        GIT_REPOSITORY "https://github.com/ocornut/imgui.git"
        GIT_TAG        "v${IMGUI_VERSION}"
)
FetchContent_GetProperties(imgui)
if(NOT imgui_POPULATED)
    FetchContent_Populate(imgui)
    #add_subdirectory("${imgui_SOURCE_DIR}" "${imgui_BINARY_DIR}")
endif()

# ImGui-SFML
set(IMGUI_SFML_VERSION "2.1")
FetchContent_Declare(
        imgui_sfml
        GIT_REPOSITORY "https://github.com/eliasdaler/imgui-sfml.git"
        GIT_TAG        "v${IMGUI_SFML_VERSION}"
)

set(IMGUI_DIR ${imgui_SOURCE_DIR})
set(IMGUI_SFML_FIND_SFML CACHE BOOL FALSE)

FetchContent_GetProperties(imgui_sfml)
if(NOT imgui_sfml_POPULATED)
    FetchContent_Populate(imgui_sfml)
    add_subdirectory("${imgui_sfml_SOURCE_DIR}" "${imgui_sfml_BINARY_DIR}")
endif()

set(SOURCE
    "src/main.cpp"
)

add_executable(2DComputerGraphicsAndAnimationApp
    "${SOURCE}"
)

target_link_libraries(2DComputerGraphicsAndAnimationApp
    PRIVATE
        "sfml-graphics"
        "sfml-system"
        "sfml-window"
        ImGui-SFML::ImGui-SFML
)

if(MSVC)
	configure_file(
		${imgui_sfml_BINARY_DIR}/ImGui-SFML.dll
		ImGui-SFML.dll
		COPYONLY
	)
	configure_file(
		${sfml_BINARY_DIR}/lib/sfml-graphics-d-2.dll
		sfml-graphics-d-2.dll
		COPYONLY
	)
	configure_file(
		${sfml_BINARY_DIR}/lib/sfml-window-d-2.dll
		sfml-window-d-2.dll
		COPYONLY
	)
	configure_file(
		${sfml_BINARY_DIR}/lib/sfml-system-d-2.dll
		sfml-system-d-2.dll
		COPYONLY
	)
endif()