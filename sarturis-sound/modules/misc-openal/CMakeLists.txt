# Include
INCLUDE(sarturis-module)

# Quellen und Header
SET(misc-openal_sources openalbase.cpp
                        sample.cpp
                        sound.cpp
                        listener.cpp)
SET(misc-openal_headers include/openalbase.h
                        include/sample.h
                        include/sound.h
                        include/listener.h)

# Open-AL
IF(SARTURIS_WIN32)
  SET(openal_platform_libs OpenAL32)
ELSE(SARTURIS_WIN32)
  SET(openal_platform_libs ${OPENAL_LIBRARIES} )
ENDIF(SARTURIS_WIN32)

# Modul
MODULE(misc-openal ${misc-openal_sources} ${misc-openal_headers})
TARGET_LINK_LIBRARIES(misc-openal sarturisbase sarturislinalg ${openal_platform_libs} ${SNDFILE_LIBRARIES})

# Doku
MODULE_DOC(misc-openal)
