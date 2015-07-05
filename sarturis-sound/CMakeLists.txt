# cmake
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

# Projekt und pkg-config
PROJECT(sarturis-sound)
FIND_PACKAGE(PkgConfig)

# 64bit?
IF(CMAKE_SIZEOF_VOID_P MATCHES "8")
  SET(LIB_POSTFIX "64")
ENDIF(CMAKE_SIZEOF_VOID_P MATCHES "8")

# Setze Sarturis-Pfade
INCLUDE_DIRECTORIES(${SARTURIS_PREFIX}/include)
LINK_DIRECTORIES(${SARTURIS_PREFIX}/lib${LIB_POSTFIX})
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${SARTURIS_PREFIX}/share/cmake/Modules)

# externe Dateien
INCLUDE(sarturis-common)
INCLUDE(sarturis-library-postfix)
INCLUDE(sarturis-prefix)

# Verzeichnisse
ADD_SUBDIRECTORY(modules)
