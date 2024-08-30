# Déclaration de la version minimale de CMake requise
cmake_minimum_required(VERSION 3.10)

# Nom du projet
project(MonProjet VERSION 1.0)

# Définir les fichiers sources
set(SOURCES
  src/pacwall.cpp
  src/raymath.h
)

# Trouver raylib
find_package(raylib REQUIRED)

# Ajouter les include directories
include_directories(${RAYLIB_INCLUDE_DIRS})

# Ajouter l'exécutable
add_executable(MonExec ${SOURCES})

# Lier raylib et raymath à l'exécutable
target_link_libraries(MonExec raylib)
