ADD_SUBDIRECTORY(logger-gtkwidget)
ADD_SUBDIRECTORY(gtk-splashscreen)
ADD_SUBDIRECTORY(gtk-error-dialog)
ADD_SUBDIRECTORY(gtk-objectmanipulator)

ADD_SUBDIRECTORY(gtkwidget-io)
ADD_SUBDIRECTORY(gtkwidget-standard)
ADD_SUBDIRECTORY(gtkwidget-playercontrol)
ADD_SUBDIRECTORY(terrain-heightmap)
ADD_SUBDIRECTORY(gtkwidget-analogdisplay)

ADD_SUBDIRECTORY(tray-notifier)

IF(SARTURIS_PYTHON)
  ADD_SUBDIRECTORY(python-gtkwidget)
ENDIF(SARTURIS_PYTHON)
