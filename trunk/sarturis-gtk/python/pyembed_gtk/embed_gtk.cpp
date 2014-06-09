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


#include "sarturis/pyembed/decode.h"
#include "include/sarturis_gtk.h"

// Letzter Include !
#include "sarturis/pyembed/export.h"


/******************************************************************************/
static PyMethodDef EMBED_API[]={
  {"GetWidget",get_widget,METH_VARARGS,"Get the GTK widget of an object"},
  {"GtkVersion",get_version,METH_VARARGS,"Get the GTK major version of this sarturis-gtk build"},
  {NULL,NULL,0,NULL}};
/******************************************************************************/


/******************************************************************************/
extern "C" DLLIMPORT void initpyembed()
/******************************************************************************/
{
  Py_InitModule("pyembed",EMBED_API);

  #ifdef SARTURIS_GTK2
    pygobject_init(-1,-1,-1);
    init_pygtk();
#else
    PyImport_ImportModule("gi");
    PyImport_ImportModule("gi.repository");
    PyImport_ImportModule("gi.repository.GObject");
    PyImport_ImportModule("gi.repository.Gtk");
    pygobject_init(-1,-1,-1);
  #endif
}
/******************************************************************************/
