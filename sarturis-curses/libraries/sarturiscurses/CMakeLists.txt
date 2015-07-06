# Includes
INCLUDE(sarturis-library)
INCLUDE(sarturis-interfacedefinition)

# Quellen und Header
SET(sarturiscurses_sources curses.cpp
                           base.cpp
                           color.cpp 
                           widget.cpp)
SET(sarturiscurses_headers ${SARTURIS_CURSES_INCLUDE_DIR}/sarturis/curses/export.h
                           ${SARTURIS_CURSES_INCLUDE_DIR}/sarturis/curses/curses.h
                           ${SARTURIS_CURSES_INCLUDE_DIR}/sarturis/curses/base.h
                           ${SARTURIS_CURSES_INCLUDE_DIR}/sarturis/curses/color.h
                           ${SARTURIS_CURSES_INCLUDE_DIR}/sarturis/curses/widget.h)

# Bibliothek
SHARED_LIBRARY(sarturiscurses ${sarturiscurses_sources} ${sarturiscurses_headers})
TARGET_LINK_LIBRARIES(sarturiscurses sarturisbase ${NCURSES_LIBRARIES})

# Install
INSTALL(FILES ${sarturiscurses_headers}
        DESTINATION include/sarturis/curses)
INSTALL(TARGETS sarturiscurses
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib${SARTURIS_LIBRARY_POSTFIX}
        ARCHIVE DESTINATION lib${SARTURIS_LIBRARY_POSTFIX})

# Typdefinition
INTERFACEDEF(curses)
