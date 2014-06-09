# Include
INCLUDE(sarturis-module)
INCLUDE(sarturis-gtk)

# Quellen und Header
SET(logger-gtkwidget_sources loggerwidget.cpp)
SET(logger-gtkwidget_headers include/loggerwidget.h)

# Modul
MODULE(logger-gtkwidget ${logger-gtkwidget_sources} ${logger-gtkwidget_headers})
TARGET_LINK_LIBRARIES(logger-gtkwidget sarturisbase sarturisgtk ${GTK_LIBRARIES})

# Doku
MODULE_DOC(logger-gtkwidget)
