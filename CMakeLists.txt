# Définir la version minimale de CMake
cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

# Nom du projet et version
project(Pac-Wall VERSION 0.2.7)

# Chercher tous les fichiers .cpp et .h dans le répertoire src/
file(GLOB SOURCES
    src/*.cpp
    src/*.h
)

# Trouver raylib
find_package(raylib REQUIRED)

# Ajouter les include directories (inclut src pour les headers locaux)
include_directories(${RAYLIB_INCLUDE_DIRS} src)

# Ajouter l'exécutable
add_executable(Pac-Wall ${SOURCES})

# Lier raylib à l'exécutable
target_link_libraries(Pac-Wall raylib)

add_compile_options(-mwindows)

install(TARGETS Pac-Wall DESTINATION .)

# Si vous utilisez des fonctionnalités OpenGL ou autres
if (WIN32)
    target_link_libraries(Pac-Wall opengl32 gdi32 winmm)
elseif (APPLE)
    target_link_libraries(Pac-Wall "-framework OpenGL" "-framework Cocoa" "-framework IOKit" "-framework CoreVideo")
elseif (UNIX)
    target_link_libraries(Pac-Wall GL m pthread dl X11)
endif()
