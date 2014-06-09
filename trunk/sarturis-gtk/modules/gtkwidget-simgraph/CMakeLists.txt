# Include
INCLUDE(sarturis-module)
INCLUDE(sarturis-gtk)

# Quellen und Header
SET(gtkwidget-simgraph_sources drawedwidget.cpp
                               linedrawer.cpp
                               ruler.cpp
                               hrule.cpp
                               vrule.cpp
                               valuewindow.cpp
                               graph.cpp
                               legend.cpp
                               diagramm.cpp)
SET(gtkwidget-simgraph_headers include/drawedwidget.h
                               include/linedrawer.h
                               include/ruler.h
                               include/hrule.h
                               include/vrule.h
                               include/valuewindow.h
                               include/graph.h
                               include/legend.h
                               include/diagramm.h)

# Modul
MODULE(gtkwidget-simgraph ${gtkwidget-simgraph_sources} ${gtkwidget-simgraph_headers})
TARGET_LINK_LIBRARIES(gtkwidget-simgraph sarturisbase sarturisgtk ${GTK_LIBRARIES})

# Install Demo
INSTALL(FILES config/diagramm.xml 
        DESTINATION share/sarturis/examples/gtkwidget-simgraph
		COMPONENT sarturis_Examples)
		
# Tests
TEST(Test_sarturis_gtkwidget-simgraph config/diagramm.xml)		

# Doku
MODULE_DOC(gtkwidget-simgraph)
