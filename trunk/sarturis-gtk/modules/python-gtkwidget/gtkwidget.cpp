/*******************************************************************************
 *
 * Sarturis is (C) Copyright 2006-2011 by Dresden University of Technology
 *
 * This software is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this software; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 * 
 ******************************************************************************/


#include <pygobject.h>
#define PYMODULE "gi.overrides.Gtk"
#include "sarturis/apps/datamanager.h"
#include "include/gtkwidget.h"
using namespace sarturis;
using namespace sarturis::python::gtk;


/******************************************************************************/
Widget::Widget(widget::_Parent_Vec_ P, widget::_Children_Vec_ C,
               const std::string& N):
          Object(pyref(0)),
          parents(P),
          children(C)
/******************************************************************************/
{
  // Python-Objekt uebernehmen
  set(DataManager::Get(N).as<Object>());

  // GTK-Widget extrahieren  
  if (IsSubClass(PYMODULE,"Widget"))
  {
    // Objekt in Widget umwandeln
    PyGObject* py_widget=0;
    if (!PyArg_Parse(get(),"O",&py_widget)) PyErr_Print();
      else widget=GTK_WIDGET(py_widget->obj);
  }
}
/******************************************************************************/


/******************************************************************************/
Widget::~Widget()
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
GtkWidget* Widget::setup()
/******************************************************************************/
{
  // Kinder "andocken"
  for (unsigned int i=0;i<children.size();++i)
  {
    // Parent-Widget holen
    sarturis::ref<gtk::Widget> parent=
      DataManager::Get(children[i].Parent).as<gtk::Widget>();

    // Parent-Widget muss Container sein - Kind drauftun
    if (parent.valid()) gtk_container_add(GTK_CONTAINER(parent->GetWidget()),
                                          children[i].Instance->GetWidget());
  }

  // Widget anzeigen und return
  gtk_widget_show(widget);
  return widget;
}
/******************************************************************************/
