# Include
INCLUDE(sarturis-module)
INCLUDE(sarturis-gtk)
INCLUDE(sarturis-codeembed)
INCLUDE(sarturis-platform)

# Sourcen und Header
SET(tray-notifier_sources traynotifier.cpp notify.cpp)
SET(tray-notifier_headers include/traynotifier.h include/notify.h)

# Bilder einbetten
CODEEMBED(${CMAKE_CURRENT_SOURCE_DIR}/sarturis.png)
SET(embedded_headers ${CMAKE_CURRENT_BINARY_DIR}/sarturis.h)

# Plattform-Sourcen
IF(SARTURIS_CYGWIN)
  SET(platform_sources cygwin/notify_cygwin.cpp cygwin/logo_cygwin.rc)  
  SET(platform_headers cygwin/notify_cygwin.h)
  SET(platform_libs )
ENDIF(SARTURIS_CYGWIN)
IF(SARTURIS_LINUX)
  FIND_PACKAGE(PkgConfig)
  PKG_CHECK_MODULES(NOTIFY libnotify)
  INCLUDE_DIRECTORIES(${NOTIFY_INCLUDE_DIRS})
  LINK_DIRECTORIES(${NOTIFY_LIBRARY_DIRS})
  SET(platform_sources linux/notify_linux.cpp)  
  SET(platform_headers linux/notify_linux.h)
  SET(platform_libs ${NOTIFY_LIBRARIES})
ENDIF(SARTURIS_LINUX)
IF(SARTURIS_APPLE)
  SET(platform_sources osx/notify_osx.cpp)  
  SET(platform_headers osx/notify_osx.h)
  SET(platform_libs)
ENDIF(SARTURIS_APPLE)
IF(SARTURIS_WIN32)
  SET(platform_sources win32/notify_win32.cpp)  
  SET(platform_headers win32/notify_win32.h)
  SET(platform_libs)
ENDIF(SARTURIS_WIN32)

# Modul
MODULE(tray-notifier ${tray-notifier_sources} ${tray-notifier_headers} ${embedded_headers} ${platform_sources} ${platform_headers})
TARGET_LINK_LIBRARIES(tray-notifier sarturisgtk ${platform_libs})

# Doku
MODULE_DOC(tray-notifier)
