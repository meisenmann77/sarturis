# Include
INCLUDE(sarturis-module)
INCLUDE(sarturis-gtk)

# Modul
MODULE(terrain-heightmap mapterrain.cpp include/mapterrain.h)
TARGET_LINK_LIBRARIES(terrain-heightmap sarturisbase sarturislinalg  sarturisgtk ${GTK_LIBRARIES})

# Doku
MODULE_DOC(terrain-heightmap)
