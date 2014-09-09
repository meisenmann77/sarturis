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
                        application.cpp)
SET(sarturisgtk_headers ${SARTURIS_GTK_INCLUDE_DIR}/sarturis/gtk/export.h
                        ${SARTURIS_GTK_INCLUDE_DIR}/sarturis/gtk/base.h
                        ${SARTURIS_GTK_INCLUDE_DIR}/sarturis/gtk/compat.h
                        ${SARTURIS_GTK_INCLUDE_DIR}/sarturis/gtk/timer.h
                        ${SARTURIS_GTK_INCLUDE_DIR}/sarturis/gtk/widget.h
                        ${SARTURIS_GTK_INCLUDE_DIR}/sarturis/gtk/activewidget.h
                        ${SARTURIS_GTK_INCLUDE_DIR}/sarturis/gtk/window.h
                        ${SARTURIS_GTK_INCLUDE_DIR}/sarturis/gtk/emptycursor.h
                        ${SARTURIS_GTK_INCLUDE_DIR}/sarturis/gtk/application.h)

# OpenGL
IF(SARTURIS_CYGWIN)
  SET(platform_sources glx/openglcontext_glx.cpp)  
  SET(platform_libs GL)
  ADD_DEFINITIONS('-DOPENGL_CONTEXT_GLX')
ENDIF(SARTURIS_CYGWIN)
IF(SARTURIS_LINUX)
  SET(platform_sources glx/openglcontext_glx.cpp)  
  SET(platform_libs GL)
  ADD_DEFINITIONS('-DOPENGL_CONTEXT_GLX')
ENDIF(SARTURIS_LINUX)
IF(SARTURIS_APPLE)
  SET(platform_sources cgl/openglcontext_cgl.cpp)  
  SET(platfrom_libs GL)
  ADD_DEFINITIONS('-DOPENGL_CONTEXT_CGL')
ENDIF(SARTURIS_APPLE)
IF(SARTURIS_WIN32)
  SET(platform_sources wgl/openglcontext_wgl.cpp)  
  SET(platform_libs OpenGL32)
  ADD_DEFINITIONS('-DOPENGL_CONTEXT_WGL')
ENDIF(SARTURIS_WIN32)

# Kompatibilitaets-Wrapper
IF(GTK_VERSION_GTK3)
  SET(compat_sources compat_gtk3.c)
ENDIF(GTK_VERSION_GTK3)
IF(GTK_VERSION_GTK2)
  SET(compat_sources compat_gtk2.c)
ENDIF(GTK_VERSION_GTK2)

# Bibliothek
SHARED_LIBRARY(sarturisgtk ${sarturisgtk_sources} ${sarturisgtk_headers} ${compat_sources} ${platform_sources})
TARGET_LINK_LIBRARIES(sarturisgtk sarturisapps sarturisconfig sarturisbase ${GTK_LIBRARIES} ${platform_libs})

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
