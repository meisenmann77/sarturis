# Include
INCLUDE(sarturis-module)
INCLUDE(sarturis-gtk)

# Quellen und Header
SET(gtk-objectmanipulator_sources instancetree.cpp
                                  mainwidget.cpp
                                  objectmanipulator.cpp
                                  textentry.cpp
                                  typetree.cpp)
SET(gtk-objectmanipulator_headers include/instancetree.h
                                  include/mainwidget.h
                                  include/objectmanipulator.h
                                  include/selectionhandler.h
                                  include/textentry.h
                                  include/typetree.h)

# Modul
MODULE(gtk-objectmanipulator ${gtk-objectmanipulator_sources} ${gtk-objectmanipulator_headers})
TARGET_LINK_LIBRARIES(gtk-objectmanipulator sarturisbase sarturisreflection sarturisdata sarturisnet sarturisgtk)

# Doku
MODULE_DOC(gtk-objectmanipulator)
