# Projekt, cmake und pkg-config
PROJECT(sarturis-sound)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
FIND_PACKAGE(PkgConfig)

# externe Dateien
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${SARTURIS_PREFIX}/share/cmake/Modules)
INCLUDE(sarturis-common)
INCLUDE(sarturis-library-postfix)
INCLUDE(sarturis-prefix)
INCLUDE(sarturis-platform)

# openal
PKG_CHECK_MODULES(OPENAL REQUIRED openal)
INCLUDE_DIRECTORIES(${OPENAL_INCLUDE_DIRS})
LINK_DIRECTORIES(${OPENAL_LIBRARY_DIRS})

# sndfile
PKG_CHECK_MODULES(SNDFILE REQUIRED sndfile)
INCLUDE_DIRECTORIES(${SNDFILE_INCLUDE_DIRS})
LINK_DIRECTORIES(${SNDFILE_LIBRARY_DIRS})

# Verzeichnisse
ADD_SUBDIRECTORY(modules)
