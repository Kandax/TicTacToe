cmake_minimum_required(VERSION 3.16)

project(TicTacToe LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_AUDIO OFF CACHE BOOL "" FORCE)
#set(SFML_BUILD_DOC OFF CACHE BOOL "" FORCE)
#set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Ścieżka do SFML jako submodule
set(SFML_DIR "${CMAKE_SOURCE_DIR}/external/SFML")

# Dodanie SFML do builda
add_subdirectory(${SFML_DIR})

set(SFML_BUILD_NETWORK OFF)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

# Główny plik wykonywalny
add_executable(${PROJECT_NAME} ${SOURCES})

# Linkowanie SFML
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        sfml-graphics
        sfml-window
        sfml-system
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# (opcjonalnie) kopiowanie DLL na Windows
#if (WIN32)
#    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_if_different
#        $<TARGET_FILE:sfml-graphics>
#        $<TARGET_FILE:sfml-window>
#        $<TARGET_FILE:sfml-system>
#        $<TARGET_FILE_DIR:MyProject>
#    )
#endif()