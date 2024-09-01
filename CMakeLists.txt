# Définir la version minimale de CMake
cmake_minimum_required(VERSION 3.10)

# Nom du projet et version
project(MonProjet VERSION 1.0)

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
add_executable(MonExecutable ${SOURCES})

# Lier raylib à l'exécutable
target_link_libraries(MonExecutable raylib)

# Si vous utilisez des fonctionnalités OpenGL ou autres
if (WIN32)
    target_link_libraries(MonExecutable opengl32 gdi32 winmm)
elseif (APPLE)
    target_link_libraries(MonExecutable "-framework OpenGL" "-framework Cocoa" "-framework IOKit" "-framework CoreVideo")
elseif (UNIX)
    target_link_libraries(MonExecutable GL m pthread dl X11)
endif()
