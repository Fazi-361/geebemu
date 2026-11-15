cmake_minimum_required(VERSION 3.22)

project(GeeBEmu LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Gli eseguibili vengono generati in <build>/bin.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# ---------------------------------------------------------------------------
# Opzioni
# ---------------------------------------------------------------------------
option(GEEBEMU_BUILD_TESTS "Compila e registra i test (usa ctest)" ON)
option(GEEBEMU_SANITIZE    "Abilita AddressSanitizer e UBSan (se il compilatore li supporta)" ON)

# Molti toolchain (es. w64devkit/MinGW su Windows) non includono le librerie
# runtime di ASan/UBSan: in quel caso li disattiviamo invece di far fallire il link.
if(GEEBEMU_SANITIZE AND NOT MSVC)
    include(CheckCSourceCompiles)
    set(CMAKE_REQUIRED_FLAGS        "-fsanitize=address,undefined")
    set(CMAKE_REQUIRED_LINK_OPTIONS "-fsanitize=address,undefined")
    check_c_source_compiles("int main(void) { return 0; }" GEEBEMU_HAS_SANITIZERS)
    unset(CMAKE_REQUIRED_FLAGS)
    unset(CMAKE_REQUIRED_LINK_OPTIONS)

    if(NOT GEEBEMU_HAS_SANITIZERS)
        message(WARNING "Sanitizer non supportati da questo compilatore: disattivati.")
        set(GEEBEMU_SANITIZE OFF)
    endif()
endif()

# ---------------------------------------------------------------------------
# raylib
# ---------------------------------------------------------------------------
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(external/raylib)

# ---------------------------------------------------------------------------
# Compilation settings
# ---------------------------------------------------------------------------
function(geebemu_set_options target)
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4)
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic)
        if(GEEBEMU_SANITIZE)
            target_compile_options(${target} PRIVATE -fsanitize=address,undefined -fno-omit-frame-pointer)
            target_link_options(${target} PRIVATE -fsanitize=address,undefined)
        endif()
    endif()
endfunction()

# ---------------------------------------------------------------------------
# Core: CPU, bus, utils, load, arithmetic...
# ---------------------------------------------------------------------------
file(GLOB_RECURSE GEEBEMU_CORE_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)
# Se un domani sposti il main in src/main.c, non finisce nella libreria.
list(FILTER GEEBEMU_CORE_SOURCES EXCLUDE REGEX "/main\\.c$")

add_library(geebemu_core STATIC ${GEEBEMU_CORE_SOURCES})
target_include_directories(geebemu_core PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
geebemu_set_options(geebemu_core)

# ---------------------------------------------------------------------------
# Main executable (core + raylib)
# ---------------------------------------------------------------------------
add_executable(geebemu geebemu.c)
target_link_libraries(geebemu PRIVATE geebemu_core raylib)
geebemu_set_options(geebemu)

# ---------------------------------------------------------------------------
# Test
# ---------------------------------------------------------------------------
if(GEEBEMU_BUILD_TESTS)
    enable_testing()

    # add_geebemu_test(<nome> <file sorgente>)
    # Crea l'eseguibile <nome> e lo registra in CTest con lo stesso nome.
    # Un test passa se main() ritorna 0.
    function(add_geebemu_test name source)
        add_executable(${name} "${source}")
        target_link_libraries(${name} PRIVATE geebemu_core)
        target_include_directories(${name} PRIVATE
            "${CMAKE_CURRENT_SOURCE_DIR}/tests"   # per testutil.h
        )
        geebemu_set_options(${name})
        add_test(NAME ${name} COMMAND ${name})
    endfunction()

    add_geebemu_test(cputest "tests/cputests.c")
    add_geebemu_test(bustest "tests/bustests.c")

    # Altri test: una riga ciascuno, ad esempio
    # add_geebemu_test(utilstest "tests/utilstests.c")
endif()