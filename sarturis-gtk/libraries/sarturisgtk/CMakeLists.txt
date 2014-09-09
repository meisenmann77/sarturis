# Includes
INCLUDE(sarturis-platform)
INCLUDE(sarturis-library)
INCLUDE(sarturis-interfacedefinition)
INCLUDE(sarturis-application)
INCLUDE(sarturis-install-file)
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
  SET(platform_include glx/openglcontext_glx.h)
  SET(platform_headers ${SARTURIS_GTK_INCLUDE_DIR}/sarturis/gtk/${platform_include})
  SET(platform_libs GL)
ENDIF(SARTURIS_CYGWIN)
IF(SARTURIS_LINUX)
  SET(platform_sources glx/openglcontext_glx.cpp)  
  SET(platform_include glx/openglcontext_glx.h)
  SET(platform_headers ${SARTURIS_GTK_INCLUDE_DIR}/sarturis/gtk/${platform_include})
  SET(platform_libs GL)
ENDIF(SARTURIS_LINUX)
IF(SARTURIS_APPLE)
  SET(platform_sources cgl/openglcontext_cgl.cpp)  
  SET(platform_include cgl/openglcontext_cgl.h)
  SET(platform_headers ${SARTURIS_GTK_INCLUDE_DIR}/sarturis/gtk/${platform_include})
  SET(platform_libs GL)
ENDIF(SARTURIS_APPLE)
IF(SARTURIS_WIN32)
  SET(platform_sources wgl/openglcontext_wgl.cpp)  
  SET(platform_include wgl/openglcontext_wgl.h)
  SET(platform_headers ${SARTURIS_GTK_INCLUDE_DIR}/sarturis/gtk/${platform_include})
  SET(platform_libs OpenGL32)
ENDIF(SARTURIS_WIN32)

# openglcontext.h erzeugen
CONFIGURE_FILE(${SARTURIS_GTK_INCLUDE_DIR}/sarturis/gtk/openglcontext.h.in ${CMAKE_CURRENT_BINARY_DIR}/openglcontext.h)

# Kompatibilitaets-Wrapper
IF(GTK_VERSION_GTK3)
  SET(compat_sources compat_gtk3.c)
ENDIF(GTK_VERSION_GTK3)
IF(GTK_VERSION_GTK2)
  SET(compat_sources compat_gtk2.c)
ENDIF(GTK_VERSION_GTK2)

# Bibliothek
SHARED_LIBRARY(sarturisgtk ${sarturisgtk_sources} ${sarturisgtk_headers} ${compat_sources} ${platform_sources} ${platform_headers})
TARGET_LINK_LIBRARIES(sarturisgtk sarturisapps sarturisconfig sarturisbase ${GTK_LIBRARIES} ${platform_libs})

# Zusaetzlich beim build
ADD_CUSTOM_TARGET(SARTURIS_GTK_OGL_BUILD DEPENDS ${CMAKE_BINARY_DIR}/include/sarturis/gtk/openglcontext.h
                                                 ${CMAKE_BINARY_DIR}/include/sarturis/gtk/${platform_include})
ADD_DEPENDENCIES(sarturisgtk SARTURIS_GTK_OGL_BUILD)

# Testanwendung (linkt nicht unter cygwin)
IF(NOT SARTURIS_CYGWIN)
  TEST_APP(sarturisgtk-test test.cpp)
  TARGET_LINK_LIBRARIES(sarturisgtk-test sarturisgtk sarturismain)
ENDIF(NOT SARTURIS_CYGWIN)

# Header-Install
HEADER_INSTALL(gtk ${sarturisgtk_headers})
INSTALL_FILE(${CMAKE_BINARY_DIR}/include/sarturis/gtk/openglcontext.h ${CMAKE_CURRENT_BINARY_DIR}/openglcontext.h)
ADD_CUSTOM_TARGET(SARTURIS_GTK_OGLCTXT DEPENDS ${CMAKE_BINARY_DIR}/include/sarturis/gtk/openglcontext.h)
INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/openglcontext.h DESTINATION include/sarturis/gtk)
IF(SARTURIS_CYGWIN)
  HEADER_INSTALL(gtk/glx ${platform_headers})
ENDIF(SARTURIS_CYGWIN)
IF(SARTURIS_LINUX)
  HEADER_INSTALL(gtk/glx ${platform_headers})
ENDIF(SARTURIS_LINUX)
IF(SARTURIS_APPLE)
  HEADER_INSTALL(gtk/cgl ${platform_headers})
ENDIF(SARTURIS_APPLE)
IF(SARTURIS_WIN32)
  HEADER_INSTALL(gtk/wgl ${platform_headers})
ENDIF(SARTURIS_WIN32)

# Typdefinition
INTERFACEDEF(gtk)

# Doku
MODULE_DOC(gtk)
