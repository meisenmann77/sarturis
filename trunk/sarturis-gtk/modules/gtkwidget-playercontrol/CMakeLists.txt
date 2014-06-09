# Sarturis
INCLUDE(sarturis-module)
INCLUDE(sarturis-gtk)

# Quellen und Header
SET(gtkwidget-playercontrol_sources playercontrol.cpp)
SET(gtkwidget-playercontrol_headers include/playercontrol.h)

# Modul
MODULE(gtkwidget-playercontrol ${gtkwidget-playercontrol_sources} ${gtkwidget-playercontrol_headers})
TARGET_LINK_LIBRARIES(gtkwidget-playercontrol  sarturisbase sarturisgtk ${GTK_LIBRARIES})

# Doku
MODULE_DOC(gtkwidget-playercontrol)
