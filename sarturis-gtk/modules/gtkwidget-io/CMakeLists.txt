# Include
INCLUDE(sarturis-module)
INCLUDE(sarturis-gtk)

# Quellen und Header
SET(gtkwidget-io_sources vectordisplay.cpp
                         analogslider.cpp
                         digitalslider.cpp
                         analogprogressbar.cpp
                         digitalled.cpp
                         numberdisplay.cpp
                         digitalbutton.cpp
                         digitaltogglebutton.cpp
                         digitalradiobutton.cpp
                         textedit.cpp
                         textdisplay.cpp
                         combobox.cpp
                         inputselector.cpp)
SET(gtkwidget-io_headers include/vectordisplay.h
                         include/analogslider.h
                         include/digitalslider.h
                         include/analogprogressbar.h
                         include/digitalled.h
                         include/numberdisplay.h
                         include/digitalbutton.h
                         include/digitaltogglebutton.h
                         include/digitalradiobutton.h
                         include/textedit.h
                         include/textdisplay.h
                         include/combobox.h
                         include/inputselector.h)

# Modul
MODULE(gtkwidget-io ${gtkwidget-io_sources} ${gtkwidget-io_headers})
TARGET_LINK_LIBRARIES(gtkwidget-io sarturisbase sarturislinalg sarturisgtk ${GTK_LIBRARIES})

# Doku
MODULE_DOC(gtkwidget-io)
