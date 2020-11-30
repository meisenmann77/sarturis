# espeak-ng
PKG_CHECK_MODULES(ESPEAKNG REQUIRED espeak-ng)
INCLUDE_DIRECTORIES(${ESPEAKNG_INCLUDE_DIRS})
LINK_DIRECTORIES(${ESPEAKNG_LIBRARY_DIRS})

# Include
INCLUDE(sarturis-module)

# Quellen und Header
SET(misc-speech_sources speak.cpp)
SET(misc-speech_headers include/speak.h)

# Modul
MODULE(misc-speech ${misc-speech_sources} ${misc-speech_headers})
TARGET_LINK_LIBRARIES(misc-speech sarturisbase ${ESPEAKNG_LIBRARIES})

# demo app
INCLUDE(sarturis-application)
CONSOLE_APP(espeak-ng_demo espeak-ng_demo.cpp)
TARGET_LINK_LIBRARIES(espeak-ng_demo ${ESPEAKNG_LIBRARIES})
