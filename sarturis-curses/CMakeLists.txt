# Projekt, cmake und pkg-config
PROJECT(sarturis-curses)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
FIND_PACKAGE(PkgConfig)

# externe Dateien
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${SARTURIS_PREFIX}/share/cmake/Modules)
INCLUDE(sarturis-common)
INCLUDE(sarturis-platform)
INCLUDE(sarturis-library-postfix)
INCLUDE(sarturis-prefix)

# Include
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include)
SET(SARTURIS_CURSES_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

IF(SARTURIS_WIN32)
  MESSAGE(STATUS "sarturis-curses is not build on this platform")
ELSE()
  # NCURSES
  PKG_CHECK_MODULES(NCURSES REQUIRED ncurses)
  INCLUDE_DIRECTORIES(${NCURSES_INCLUDE_DIRS})
  LINK_DIRECTORIES(${NCURSES_LIBRARY_DIRS})

  # Verzeichnisse
  ADD_SUBDIRECTORY(libraries)
  ADD_SUBDIRECTORY(modules)
ENDIF()

