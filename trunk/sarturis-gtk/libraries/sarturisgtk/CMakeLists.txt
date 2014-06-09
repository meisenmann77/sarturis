# Includes
INCLUDE(sarturis-platform)
INCLUDE(sarturis-library)
INCLUDE(sarturis-interfacedefinition)
INCLUDE(sarturis-application)
INCLUDE(sarturis-gtk)

# Quellen und Header
SET(sarturisgtk_sources base.cpp
                        timer.cpp
                        widget.cpp
                        activewidget.cpp
                        window.cpp
                        emptycursor.cpp
                        application.cpp
                        openglcontext.cpp)
SET(sarturisgtk_headers ${SARTURIS_GTK_INCLUDE_DIR}/sarturis/gtk/export.h
                        ${SARTURIS_GTK_INCLUDE_DIR}/sarturis/gtk/base.h
                        ${SARTURIS_GTK_INCLUDE_DIR}/sarturis/gtk/compat.h
                        ${SARTURIS_GTK_INCLUDE_DIR}/sarturis/gtk/timer.h
                        ${SARTURIS_GTK_INCLUDE_DIR}/sarturis/gtk/widget.h
                        ${SARTURIS_GTK_INCLUDE_DIR}/sarturis/gtk/activewidget.h
                        ${SARTURIS_GTK_INCLUDE_DIR}/sarturis/gtk/window.h
                        ${SARTURIS_GTK_INCLUDE_DIR}/sarturis/gtk/emptycursor.h
                        ${SARTURIS_GTK_INCLUDE_DIR}/sarturis/gtk/application.h
                        ${SARTURIS_GTK_INCLUDE_DIR}/sarturis/gtk/openglcontext.h)

# OpenGL
IF(WIN32)
  SET(ogl_lib OpenGL32)
ELSE(WIN32)
  SET(ogl_lib GL)
ENDIF(WIN32)

# Kompatibilitaets-Wrapper
IF(GTK_VERSION_GTK3)
  SET(compat_sources compat_gtk3.c)
ENDIF(GTK_VERSION_GTK3)
IF(GTK_VERSION_GTK2)
  SET(compat_sources compat_gtk2.c)
ENDIF(GTK_VERSION_GTK2)

# Bibliothek
SHARED_LIBRARY(sarturisgtk ${sarturisgtk_sources} ${sarturisgtk_headers} ${compat_sources})
TARGET_LINK_LIBRARIES(sarturisgtk sarturisapps sarturisconfig sarturisbase ${GTK_LIBRARIES} ${ogl_lib})

# Testanwendung (linkt nicht unter cygwin)
IF(NOT SARTURIS_CYGWIN)
  TEST_APP(sarturisgtk-test test.cpp)
  TARGET_LINK_LIBRARIES(sarturisgtk-test sarturisgtk sarturismain)
ENDIF(NOT SARTURIS_CYGWIN)

# Header-Install
HEADER_INSTALL(gtk ${sarturisgtk_headers})

# Typdefinition
INTERFACEDEF(gtk)

# Doku
MODULE_DOC(gtk)
