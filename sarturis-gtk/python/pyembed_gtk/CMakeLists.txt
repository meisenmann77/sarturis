# Includes
INCLUDE(sarturis-pygtk)
INCLUDE(sarturis-pyembed)

# Target pyembed_gtk, pyembed gibt es schon
PYTHON_EMBED(pyembed_gtk embed_gtk.cpp include/sarturis_gtk.h)
TARGET_LINK_LIBRARIES(pyembed_gtk sarturisgtk ${PYGTK_LIBS})

# Auf pyembed -> sarturis.gtk.pyembed umstellen
SET_TARGET_PROPERTIES(pyembed_gtk PROPERTIES OUTPUT_NAME pyembed)
SET_TARGET_PROPERTIES(pyembed_gtk PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/python/sarturis/gtk)

# Install
INSTALL(TARGETS pyembed_gtk
        RUNTIME DESTINATION ${PYTHON_SITEDIR3}/sarturis/gtk COMPONENT sarturis_gtk
        LIBRARY DESTINATION ${PYTHON_SITEDIR3}/sarturis/gtk COMPONENT sarturis_gtk
        ARCHIVE DESTINATION ${PYTHON_SITEDIR3}/sarturis/gtk COMPONENT sarturis_gtk)
