cmake_minimum_required(VERSION 3.16)
project(Test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SFML 3 COMPONENTS Graphics Window System Audio QUIET)

if(NOT SFML_FOUND)
    include(FetchContent)
    set(BUILD_SHARED_LIBS OFF)
    FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.2
        GIT_SHALLOW ON)
    FetchContent_MakeAvailable(SFML)
endif()

add_executable(game
                main.cpp 
                tank.cpp 
                tile.cpp
                bullet.cpp)
target_link_libraries(game PRIVATE SFML::Graphics SFML::Window SFML::System SFML::Audio)

add_custom_command(TARGET game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:game>/assets)