# Include
INCLUDE(sarturis-module)
INCLUDE(sarturis-gtk)

# Quellen und Header
SET(gtkwidget-analogdisplay_sources cairowidget.cpp
                                    fillleveldisplay.cpp 
                                    circulardisplay.cpp)

SET(gtkwidget-analogdisplay_headers include/cairowidget.h
                                    include/fillleveldisplay.h
                                    include/circulardisplay.h)

#Modul
MODULE(gtkwidget-analogdisplay ${gtkwidget-analogdisplay_sources} ${gtkwidget-analogdisplay_headers})
TARGET_LINK_LIBRARIES(gtkwidget-analogdisplay sarturisbase sarturisgtk ${GTK_LIBRARIES})

# Beispiele
INSTALL(FILES config/circular.xml DESTINATION share/sarturis/examples/gtk)
INSTALL(FILES config/filllevel.xml DESTINATION share/sarturis/examples/gtk)

# Doku
MODULE_DOC(gtkwidget-analogdisplay)

