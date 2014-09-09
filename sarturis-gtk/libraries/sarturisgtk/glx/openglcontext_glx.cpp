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


#include <gdk/gdk.h>
#include "sarturis/base/generalexception.h"
#include "sarturis/gtk/glx/openglcontext_glx.h"
using namespace sarturis;
using namespace sarturis::gtk;


/******************************************************************************/
OpenGLContext::OpenGLContext(GtkWidget* Widget):widget(Widget),context(0)
/******************************************************************************/
{
  // Double-Buffered einstellen
  gtk_widget_set_double_buffered(widget,FALSE);

  // Attribute
  int attributes[]={GLX_USE_GL, GLX_DOUBLEBUFFER, GLX_RGBA, None};

  // Display, Window und Screen
  display=GDK_WINDOW_XDISPLAY(gtk_widget_get_window(widget));
  glwindow=GDK_WINDOW_XID(gtk_widget_get_window(widget));
  GdkScreen* gscreen=gdk_window_get_screen(gtk_widget_get_window(widget));
  int screen=gdk_x11_screen_get_screen_number(gscreen);
   
  // screen und VisualInfo
  XVisualInfo* vinfo=glXChooseVisual(display,screen,attributes);

  // Fallback ohne DoubleBuffer und RGBA
  if (!vinfo)
  {
    int _attributes[]={None};
    vinfo=glXChooseVisual(display,screen,_attributes);
    if (!vinfo) throw GeneralException("Couldn't find GLX visual!");
  }

  // Kontext
  context=glXCreateContext(display,vinfo,NULL,True);
}
/******************************************************************************/


/******************************************************************************/
OpenGLContext::~OpenGLContext()
/******************************************************************************/
{
  glXDestroyContext(display,context);
}
/******************************************************************************/


/******************************************************************************/
bool OpenGLContext::MakeCurrent()
/******************************************************************************/
{
  // Context muss da sein
  if (!context) return false;

  // Context aktivieren
  return (glXMakeCurrent(display,glwindow,context)==True);
}
/******************************************************************************/


/******************************************************************************/
void OpenGLContext::SwapBuffers()
/******************************************************************************/
{
  glXSwapBuffers(display,glwindow);
}
/******************************************************************************/
