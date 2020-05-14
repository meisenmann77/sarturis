# Include
INCLUDE(sarturis-install-file)

# sarturis-python Includes
INCLUDE_DIRECTORIES(${SARTURIS_PYTHON_SRC}/include)

# SUB-Directories
ADD_SUBDIRECTORY(pyembed_gtk)

# GTK-Python Files
INSTALL_FILE(${CMAKE_BINARY_DIR}/python/sarturis/gtk/__init__.py   ${CMAKE_CURRENT_SOURCE_DIR}/__init__.py)
INSTALL_FILE(${CMAKE_BINARY_DIR}/python/sarturis/gtk/gtkwrapper.py ${CMAKE_CURRENT_SOURCE_DIR}/gtkwrapper.py)
INSTALL_FILE(${CMAKE_BINARY_DIR}/python/sarturis/gtk/guibase.py    ${CMAKE_CURRENT_SOURCE_DIR}/guibase.py)
INSTALL_FILE(${CMAKE_BINARY_DIR}/python/sarturis/gtk/gladegui.py   ${CMAKE_CURRENT_SOURCE_DIR}/gladegui.py)

# Target
ADD_CUSTOM_TARGET(SARTURIS_GTK_PYTHON ALL DEPENDS ${CMAKE_BINARY_DIR}/python/sarturis/gtk/__init__.py
                                                  ${CMAKE_BINARY_DIR}/python/sarturis/gtk/gtkwrapper.py
                                                  ${CMAKE_BINARY_DIR}/python/sarturis/gtk/guibase.py
                                                  ${CMAKE_BINARY_DIR}/python/sarturis/gtk/gladegui.py)

# Install
INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/__init__.py   DESTINATION share/sarturis/python/sarturis/gtk)
INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/gtkwrapper.py DESTINATION share/sarturis/python/sarturis/gtk)
INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/guibase.py    DESTINATION share/sarturis/python/sarturis/gtk)
INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/gladegui.py   DESTINATION share/sarturis/python/sarturis/gtk)
