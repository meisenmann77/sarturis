# Include
INCLUDE(sarturis-module)
INCLUDE(sarturis-gtk)

# Quellen und Header
SET(misc-vlc_sources camera.cpp
                     genericsource.cpp
                     httpstream.cpp
                     mediafile.cpp
                     mediasource.cpp
                     udpstream.cpp
                     viewer.cpp
                     vlcbase.cpp)
SET(misc-vlc_headers include/camera.h
                     include/genericsource.h
                     include/httpstream.h
                     include/mediafile.h
                     include/mediasource.h
                     include/udpstream.h
                     include/viewer.h
                     include/vlcbase.h)

# Modul
MODULE(misc-vlc ${misc-vlc_sources} ${misc-vlc_headers})
TARGET_LINK_LIBRARIES(misc-vlc sarturisbase sarturisgtk ${VLC_LIBRARIES})

# Doku
MODULE_DOC(misc-vlc)
