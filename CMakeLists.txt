
cmake_minimum_required(VERSION 3.22)
# include(CTest)

project(GeeBEmu LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# L'eseguibile sarà generato nella cartella di build.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# Non compilare gli esempi della libreria.
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Compila raylib direttamente dal repository.
add_subdirectory(external/raylib)

# Sorgenti di GeeBEmu.
file(GLOB GEEMEMU_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)

add_executable(geebemu
    geebemu.c
    ${GEEMEMU_SOURCES}
)

target_include_directories(geebemu PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

# Collega raylib e le sue dipendenze.
target_link_libraries(geebemu PRIVATE raylib)

# Avvisi del compilatore per GCC e Clang.
if(MSVC)
    target_compile_options(geebemu PRIVATE /W4)
else()
    target_compile_options(geebemu PRIVATE
        -Wall -Wextra -Wpedantic
    )
endif()

add_executable(cputest 
    "tests/cputests.c"
    ${GEEMEMU_SOURCES}
)

target_include_directories(cputest PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

add_executable(bustest 
    "tests/bustests.c"
    ${GEEMEMU_SOURCES}
)

target_include_directories(bustest PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

# # Collega raylib e le sue dipendenze.
# target_link_libraries(geebemu PRIVATE raylib)