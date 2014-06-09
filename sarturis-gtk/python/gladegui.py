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

from sarturis.pyembed import Embed
from sarturis.config.sarturis.python.gtk import Widget as PyGtkWidget

class GladeGUI(PyGtkWidget):
  def __init__(self, guiClass, children = {}):
    # assertion
    assert(isinstance(children,dict))

    # init PyGtkWidget with embedded frame1
    gui=guiClass()
    PyGtkWidget.__init__(self, Embed(gui.getMainWidget()))

    # configure children and store children names in gui object
    for _c in children.keys():
      w = PyGtkWidget(Embed(gui.getWidget(_c)))
      self.connect(w)
      self.connect(children[_c], Parent=w.name)
      gui.children[_c] = children[_c].name

