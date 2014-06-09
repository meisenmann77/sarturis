# Include
INCLUDE(sarturis-module)
INCLUDE(sarturis-gtk)
INCLUDE(sarturis-codeembed)

# Bilder einbetten
CODEEMBED(${CMAKE_CURRENT_SOURCE_DIR}/sarturis.png)
SET(EMBEDDED_HEADERS ${CMAKE_CURRENT_BINARY_DIR}/sarturis.h)

# Plattform-Sourcen
IF(WIN32)
  SET(PLATFORM_SOURCES notify_win32.cpp)
  SET(PLATFORM_LIBS )
ELSE(WIN32)
  INCLUDE_DIRECTORIES(${NOTIFY_INCLUDE_DIRS})
  LINK_DIRECTORIES(${NOTIFY_LIBRARY_DIRS})
  SET(PLATFORM_SOURCES notify_linux.cpp)
  SET(PLATFORM_LIBS ${NOTIFY_LIBRARIES})
ENDIF(WIN32)

# Modul
MODULE(tray-notifier traynotifier.cpp include/traynotifier.h include/notify.h ${EMBEDDED_HEADERS} ${PLATFORM_SOURCES})
TARGET_LINK_LIBRARIES(tray-notifier sarturisgtk ${PLATFORM_LIBS})

# Doku
MODULE_DOC(tray-notifier)
