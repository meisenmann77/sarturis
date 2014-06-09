'''

   Sarturis is (C) Copyright 2006-2011 by Dresden University of Technology

   This software is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This software is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with this software; if not, write to the
   Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.

'''

# Man kann nicht verhindern, dass der User pygtk importiert
# aber dass hier kann dennoch eine Vereinfachung sein

# GTK je nach GTK-Version
from sarturis.gtk.pyembed import GtkVersion
x=GtkVersion()
if x==3:
  # GTK3 Imports
  from gi.repository import GObject as gobject
  from gi.repository import Gtk as gtk
elif x==2:
  import pygtk
  import gobject
  import gtk
else:
  print "No supported GTK Version"
