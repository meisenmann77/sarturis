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

# Modul
MODULE(misc-openal ${misc-openal_sources} ${misc-openal_headers})
TARGET_LINK_LIBRARIES(misc-openal sarturisbase sarturislinalg ${OPENAL_LIBRARIES} ${SNDFILE_LIBRARIES})

# Doku
MODULE_DOC(misc-openal)
