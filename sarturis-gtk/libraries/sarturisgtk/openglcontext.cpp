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
#include "sarturis/gtk/openglcontext.h"
using namespace sarturis;
using namespace sarturis::gtk;


/******************************************************************************/
OpenGLContext::OpenGLContext(GtkWidget* Widget):widget(Widget),context(0)
/******************************************************************************/
{
  // Double-Buffered einstellen
  gtk_widget_set_double_buffered(widget,FALSE);

  #ifdef WIN32
	  // get the device context (DC)
	  dc=GetDC((HWND)GDK_WINDOW_HWND(widget->window));

    // Pixel-Format
  	PIXELFORMATDESCRIPTOR pfd;
	  ZeroMemory(&pfd,sizeof(pfd));
	  pfd.nSize=sizeof(pfd);
	  pfd.nVersion=1;
	  pfd.dwFlags=PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	  pfd.iPixelType=PFD_TYPE_RGBA;
	  pfd.cColorBits=24;
	  pfd.cDepthBits=16;
	  pfd.iLayerType=PFD_MAIN_PLANE;

	  // set the pixel format for the DC
	  int format=ChoosePixelFormat(dc,&pfd);
	  SetPixelFormat(dc,format,&pfd);
	
	  // create and enable the render context (RC)
	  context=wglCreateContext(dc);
  #else
    // Attribute
    int attributes[]={GLX_USE_GL, GLX_DOUBLEBUFFER, GLX_RGBA, None};

    // Display, Window und Screen
    #ifdef SARTURIS_GTK2
      display=GDK_DRAWABLE_XDISPLAY(widget->window);
      glwindow=gdk_x11_drawable_get_xid(widget->window);
  	  GdkScreen* gscreen=gdk_drawable_get_screen(widget->window);
  	  int screen=gdk_x11_screen_get_screen_number(gscreen);
    #else
      display=GDK_WINDOW_XDISPLAY(gtk_widget_get_window(widget));
      glwindow=GDK_WINDOW_XID(gtk_widget_get_window(widget));
  	  GdkScreen* gscreen=gdk_window_get_screen(gtk_widget_get_window(widget));
  	  int screen=gdk_x11_screen_get_screen_number(gscreen);
    #endif
    
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
  #endif
}
/******************************************************************************/


/******************************************************************************/
OpenGLContext::~OpenGLContext()
/******************************************************************************/
{
  #ifdef WIN32
    wglDeleteContext(context);
  #else
    glXDestroyContext(display,context);
  #endif
}
/******************************************************************************/


/******************************************************************************/
bool OpenGLContext::MakeCurrent()
/******************************************************************************/
{
  // Context muss da sein
  if (!context) return false;

  // Context aktivieren
  #ifdef WIN32
    return (wglMakeCurrent(dc,context)==(BOOL)TRUE);
  #else
    return (glXMakeCurrent(display,glwindow,context)==True);
  #endif
}
/******************************************************************************/


/******************************************************************************/
void OpenGLContext::SwapBuffers()
/******************************************************************************/
{
  #ifdef WIN32
    ::SwapBuffers(dc);
  #else
    glXSwapBuffers(display,glwindow);
  #endif
}
/******************************************************************************/
