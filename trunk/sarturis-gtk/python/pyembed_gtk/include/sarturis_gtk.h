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


#ifdef SARTURIS_GTK2
  #include <pygtk/pygtk.h>
#else
  #include <pygobject.h>
#endif
#include "sarturis/gtk/widget.h"
#include "sarturis/python/generic.h"
using namespace sarturis;
using namespace sarturis::gtk;
using namespace sarturis::python;


/******************************************************************************/
#ifdef SARTURIS_GTK2
  struct _PyGObject_Functions* _PyGObject_API;
#endif
/******************************************************************************/


/******************************************************************************/
static PyObject* get_widget(PyObject* self, PyObject* args)
/******************************************************************************/
{
  // Widget holen, wenn vorhanden zurueckgeben
  sarturis::ref<Widget> w=decode(args).as<Widget>();
  if (w.valid()) return pygobject_new(G_OBJECT(w->GetWidget()));

  // Kein Widget, refcount von Py_None erhoehen und return
  Py_INCREF(Py_None);
  return Py_None;
}
/******************************************************************************/


/******************************************************************************/
static PyObject* get_version(PyObject* self, PyObject* args)
/******************************************************************************/
{
  return PyInt_FromLong(sarturis::gtk::Base::GtkVersion());
}
/******************************************************************************/
