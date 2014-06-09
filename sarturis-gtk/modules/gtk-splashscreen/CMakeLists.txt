# Include
INCLUDE(sarturis-library-postfix)
INCLUDE(sarturis-version)
INCLUDE(sarturis-gtk)
INCLUDE(splashscreen.cmake)

# Eine Version.h und Resource File generieren 
VERSION(gtk-splashscreen)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Modul
ADD_DEFINITIONS(-DCREATE_MODULE)  
ADD_LIBRARY(gtk-splashscreen MODULE module.cpp module-meta.cpp include/splashscreen-meta.h ${splash_files} ${splashscreen_resfile})
SET_TARGET_PROPERTIES(gtk-splashscreen PROPERTIES PREFIX "")
SET_TARGET_PROPERTIES(gtk-splashscreen PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib${SARTURIS_LIBRARY_POSTFIX}/sarturis)
TARGET_LINK_LIBRARIES(gtk-splashscreen sarturisbase sarturisgtk)

# CYGWIN
IF(CYGWIN)
  SET_TARGET_PROPERTIES(gtk-splashscreen PROPERTIES PREFIX "cygwin_")
ENDIF(CYGWIN)

# Install
INSTALL(TARGETS gtk-splashscreen
        LIBRARY DESTINATION lib${SARTURIS_LIBRARY_POSTFIX}/sarturis
        COMPONENT sarturis)
