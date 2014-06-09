# Include
INCLUDE(sarturis-module)
INCLUDE(sarturis-codeembed)
INCLUDE(sarturis-gtk)

# Quellen und Header
SET(gtkwidget-standard_sources box.cpp
                               button.cpp
                               expander.cpp
                               frame.cpp
                               image.cpp
                               label.cpp
                               notebook.cpp
                               paned.cpp
                               scrolledwindow.cpp
                               sizegroup.cpp
                               stockimage.cpp
                               backgroundimage.cpp
                               table.cpp
                               togglebutton.cpp
                               usize.cpp
                               window.cpp)
SET(gtkwidget-standard_headers include/box.h
                               include/button.h
                               include/expander.h
                               include/frame.h
                               include/image.h
                               include/label.h
                               include/notebook.h
                               include/paned.h
                               include/scrolledwindow.h
                               include/sizegroup.h
                               include/stockimage.h
                               include/backgroundimage.h
                               include/table.h
                               include/togglebutton.h
                               include/usize.h
                               include/window.h)

# Bild
CODEEMBED(${CMAKE_CURRENT_SOURCE_DIR}/sarturis.png)
SET(EMBEDDED_HEADERS ${CMAKE_CURRENT_BINARY_DIR}/sarturis.h)

# Modul
MODULE(gtkwidget-standard ${gtkwidget-standard_sources} ${gtkwidget-standard_headers} ${EMBEDDED_HEADERS})
TARGET_LINK_LIBRARIES(gtkwidget-standard sarturisbase sarturisgtk ${GTK_LIBRARIES})

# Doku
MODULE_DOC(gtkwidget-standard)
