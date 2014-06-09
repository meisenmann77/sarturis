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

from sarturis.gtk import gtk

class GUIBase(object):
  def __init__(self, filename, mainwidget, widgets = []):
    # create GUI
    self.builder = gtk.Builder()
    self.builder.add_from_file(filename)
    self.mainwidget = self.builder.get_object(mainwidget)

    # remove mainwidget from its parent to get an orphan widget
    parent = self.mainwidget.get_parent()
    parent.remove(self.mainwidget)

    # store widgets
    self.storeWidgets(widgets)

  def getMainWidget(self):
    return self.mainwidget;

  def getWidget(self, name):
    return self.builder.get_object(name)

  def storeWidgets(self, widgets):
    assert(isinstance(widgets, list))
    for _w in widgets:
      self.__dict__[_w] = self.builder.get_object(_w)

