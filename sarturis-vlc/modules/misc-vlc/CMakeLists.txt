# Include
INCLUDE(sarturis-module)
INCLUDE(sarturis-gtk)
INCLUDE(sarturis-platform)

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

# Platform
IF(SARTURIS_CYGWIN)
  SET(platform_sources viewer_cygwin.cpp)  
ENDIF(SARTURIS_CYGWIN)
IF(SARTURIS_LINUX)
  SET(platform_sources viewer_linux.cpp)  
ENDIF(SARTURIS_LINUX)
IF(SARTURIS_APPLE)
  SET(platform_sources viewer_osx.mm)  
ENDIF(SARTURIS_APPLE)
IF(SARTURIS_WIN32)
  SET(platform_sources viewer_win32.cpp)  
ENDIF(SARTURIS_WIN32)

# Modul
MODULE(misc-vlc ${misc-vlc_sources} ${misc-vlc_headers} ${platform_sources})
TARGET_LINK_LIBRARIES(misc-vlc sarturisbase sarturisgtk ${VLC_LIBRARIES})

# Doku
MODULE_DOC(misc-vlc)
