# Include
INCLUDE(sarturis-codeembed)
INCLUDE(sarturis-version)
INCLUDE(sarturis-library-postfix)
INCLUDE(sarturis-gtk)

# Bilder einbetten
CODEEMBED(${CMAKE_CURRENT_SOURCE_DIR}/joe.png)
SET(EMBEDDED_HEADERS ${CMAKE_CURRENT_BINARY_DIR}/joe.h)

# Eine Version.h und Resource File generieren 
VERSION(gtk-error-dialog)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Modul
ADD_DEFINITIONS(-DCREATE_MODULE)  
ADD_LIBRARY(gtk-error-dialog MODULE module.cpp glade.cpp errordialog.cpp gtk-error-dialog-meta.cpp include/glade.h include/errordialog.h include/gtk-error-dialog-meta.h ${EMBEDDED_HEADERS} ${gtk-error-dialog_resfile})
SET_TARGET_PROPERTIES(gtk-error-dialog PROPERTIES PREFIX "")
SET_TARGET_PROPERTIES(gtk-error-dialog PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib${SARTURIS_LIBRARY_POSTFIX}/sarturis)
TARGET_LINK_LIBRARIES(gtk-error-dialog sarturisbase sarturisgtk)

# CYGWIN
IF(CYGWIN)
  SET_TARGET_PROPERTIES(gtk-error-dialog PROPERTIES PREFIX "cygwin_")
ENDIF(CYGWIN)

# Install
INSTALL(TARGETS gtk-error-dialog 
        LIBRARY DESTINATION lib${SARTURIS_LIBRARY_POSTFIX}/sarturis
        COMPONENT sarturis)
