# Sarturis
INCLUDE(sarturis-module)

# Quellen und Header
SET(misc-curses_sources bardrawer.cpp
                        progressbar.cpp
                        label.cpp
                        analogslider.cpp
                        window.cpp
                        iteration.cpp)
SET(misc-curses_headers include/bardrawer.h
                        include/progressbar.h
                        include/label.h
                        include/analogslider.h
                        include/window.h
                        include/iteration.h)

# Modul
MODULE(misc-curses ${misc-curses_sources} ${misc-curses_headers})
TARGET_LINK_LIBRARIES(misc-curses sarturiscurses ${CURSESLIB})

# Install Demo
INSTALL(FILES test.xml DESTINATION share/sarturis/examples/curses)
