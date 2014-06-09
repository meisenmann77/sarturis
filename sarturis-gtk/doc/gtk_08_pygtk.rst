Sarturis and PyGTK
------------------

Explain windows issue with different gtk runtimes for sarturis
and pygtk.


  .. figure:: gtk_08_pygtk_error.png

EXCEPTION: <type 'exceptions.ImportError'>: could not import gtk
           Traceback (most recent call last):
           File "C:\Daten\build\sarturis\src-devel\sarturis-gtk\examples\pygtk-glade-demo\main.py", line 1, in <module>
           from config import GuiConfig
           File "C:\Daten\build\sarturis\src-devel\sarturis-gtk\examples\pygtk-glade-demo\config.py", line 1, in <module>
           from gui import GUI
           File "C:\Daten\build\sarturis\src-devel\sarturis-gtk\examples\pygtk-glade-demo\gui.py", line 1, in <module>
           from sarturis.gtk import gtk, gobject, GUIBase
           File "C:\Daten\Software\sarturis\python\sarturis\gtk\__init__.py", line 1, in <module>
           from gtkwrapper import gtk
           File "C:\Daten\Software\sarturis\python\sarturis\gtk\gtkwrapper.py", line 5, in <module>
           from sarturis.gtk.pyembed import GtkVersion
