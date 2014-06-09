# Include
INCLUDE(sarturis-documentation)

# Doku
MISC_DOC(packages_02_sarturis-gtk.rst gtk_01_introduction.rst)

# PyGTK-Doku
IF(SARTURIS_PYTHON)
  MISC_DOC(gtk_08_pygtk.rst gtk_08_pygtk_error.png)
ENDIF(SARTURIS_PYTHON)

