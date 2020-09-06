IF(CMAKE_CROSSCOMPILING)
  MESSAGE(STATUS "python-gtkwidget is not build with cross compiling (pygobject not available)")
ELSEIF(MSVC)
  MESSAGE(STATUS "python-gtkwidget is not build with msvc compilers (pygobject not available)")
ELSE()
  # Include
  INCLUDE(sarturis-module)
  INCLUDE(sarturis-pygtk)

  # Header und Source-Files
  SET(python-gtkwidget_headers include/gtkwidget.h)
  SET(python-gtkwidget_sources gtkwidget.cpp)

  # Modul
  MODULE(python-gtkwidget ${python-gtkwidget_sources} ${python-gtkwidget_headers})
  TARGET_LINK_LIBRARIES(python-gtkwidget sarturisbase sarturis-python sarturisgtk ${PYGTK_LIBS})

  # Doku
  MODULE_DOC(python-gtkwidget)
ENDIF()
