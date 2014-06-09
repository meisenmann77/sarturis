# Include
INCLUDE(sarturis-module)
INCLUDE(sarturis-gtk)

# Modul
MODULE(terrain-heightmap mapterrain.cpp include/mapterrain.h)
TARGET_LINK_LIBRARIES(terrain-heightmap sarturisbase sarturislinalg  sarturisgtk ${GTK_LIBRARIES})

# Install Demo
INSTALL(FILES config/map1.xml config/map1_highres.xml config/map2.xml config/map3.xml config/map4.xml config/bodenwelle.xml
        DESTINATION share/sarturis/examples/terrain-heightmap
		COMPONENT sarturis_Examples)
INSTALL(FILES maps/map1.png maps/map2.png maps/map3.png maps/map4.png maps/bodenwelle.png
        DESTINATION share/sarturis/examples/terrain-heightmap/maps
		COMPONENT sarturis_Examples)

# Doku
MODULE_DOC(terrain-heightmap)
