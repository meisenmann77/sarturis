cmake_minimum_required(VERSION 2.6)

# Projekt und pkg-config
PROJECT(sarturis-curses)
FIND_PACKAGE(PkgConfig)

# 64bit?
IF(CMAKE_SIZEOF_VOID_P MATCHES "8")
  SET(LIB_POSTFIX "64")
ENDIF(CMAKE_SIZEOF_VOID_P MATCHES "8")

# Include
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include)
SET(SARTURIS_CURSES_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Setze Sarturis-Pfade
INCLUDE_DIRECTORIES(${SARTURIS_PREFIX}/include)
LINK_DIRECTORIES(${SARTURIS_PREFIX}/lib${LIB_POSTFIX})
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${SARTURIS_PREFIX}/share/cmake/Modules)

# externe Dateien
INCLUDE(sarturis-common)
INCLUDE(sarturis-library-postfix)
INCLUDE(sarturis-prefix)

# Curses-Library
FIND_LIBRARY(CURSESLIB curses NAMES ncurses DOC "the curses library")

# Verzeichnisse
ADD_SUBDIRECTORY(libraries)
ADD_SUBDIRECTORY(modules)
