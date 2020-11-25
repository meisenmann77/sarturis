# externe Dateien
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${SARTURIS_PREFIX}/share/cmake/Modules)
INCLUDE(sarturis-common)
INCLUDE(sarturis-library-postfix)
INCLUDE(sarturis-prefix)
INCLUDE(sarturis-platform)

# pkg-config und espeak-ng
FIND_PACKAGE(PkgConfig)
PKG_CHECK_MODULES(ESPEAKNG_X espeak-ng)
IF(ESPEAKNG_X_FOUND)
  ADD_SUBDIRECTORY(misc-speech)
ELSE()
  MESSAGE(STATUS "misc-speech is not build (espeak-ng is missing")
ENDIF()
