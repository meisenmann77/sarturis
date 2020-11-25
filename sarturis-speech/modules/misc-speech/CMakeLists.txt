# espeak-ng
PKG_CHECK_MODULES(ESPEAKNG REQUIRED espeak-ng)
INCLUDE_DIRECTORIES(${ESPEAKNG_INCLUDE_DIRS})
LINK_DIRECTORIES(${ESPEAKNG_LIBRARY_DIRS})

# Modul
INCLUDE(sarturis-module)


# demo app
INCLUDE(sarturis-application)
CONSOLE_APP(espeak-ng_demo espeak-ng_demo.cpp)
TARGET_LINK_LIBRARIES(espeak-ng_demo ${ESPEAKNG_LIBRARIES})
