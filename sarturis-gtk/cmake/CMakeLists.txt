# Include
INCLUDE(sarturis-install-file)

# CMAKE-Files (ohne Pfad)
SET(CMAKE_FILES sarturis-gtk.cmake
                sarturis-pygtk.cmake)

# custom command fuer cmake-files und Listen mit Pfaden aufbauen
FOREACH(CMAKE_FILE ${CMAKE_FILES})
  # Source und Target
  SET(SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_FILE})
  SET(TARGET ${CMAKE_BINARY_DIR}/share/cmake/Modules/${CMAKE_FILE})

  # Listen
  SET(CMAKE_FILE_SOURCES ${CMAKE_FILE_SOURCES} ${SOURCE})
  SET(CMAKE_FILE_TARGETS ${CMAKE_FILE_TARGETS} ${TARGET})

  # Custom Command
  INSTALL_FILE(${TARGET} ${SOURCE})
ENDFOREACH(CMAKE_FILE)

# custom target fuer cmake-files
ADD_CUSTOM_TARGET(ALL_CMAKE_SARTURIS_GTK ALL DEPENDS ${CMAKE_FILE_TARGETS})

# CMAKE-Files installieren
INSTALL(FILES ${CMAKE_FILE_SOURCES}
        DESTINATION share/cmake/Modules
        COMPONENT CMake_Headers)
