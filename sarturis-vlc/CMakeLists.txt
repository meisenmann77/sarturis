# Projekt, cmake und pkg-config
PROJECT(sarturis-vlc)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
FIND_PACKAGE(PkgConfig)

# externe Dateien
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${SARTURIS_PREFIX}/share/cmake/Modules)
INCLUDE(sarturis-common)
INCLUDE(sarturis-library-postfix)
INCLUDE(sarturis-prefix)
INCLUDE(sarturis-platform)

IF(CMAKE_CROSSCOMPILING)
  MESSAGE(STATUS "sarturis-vlc is not build with cross compiling (vlc is not building with mingw on fc32)")
ELSE()
  # vlc
  PKG_CHECK_MODULES(VLC REQUIRED libvlc)
  INCLUDE_DIRECTORIES(${VLC_INCLUDE_DIRS})
  LINK_DIRECTORIES(${VLC_LIBRARY_DIRS})

  # Verzeichnisse
  ADD_SUBDIRECTORY(modules)
ENDIF()
