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
#include "sarturis/gtk/wgl/openglcontext_wgl.h"
using namespace sarturis;
using namespace sarturis::gtk;


/******************************************************************************/
OpenGLContext::OpenGLContext(GtkWidget* Widget):widget(Widget),context(0)
/******************************************************************************/
{
  // Double-Buffered einstellen
  gtk_widget_set_double_buffered(widget,FALSE);

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
}
/******************************************************************************/


/******************************************************************************/
OpenGLContext::~OpenGLContext()
/******************************************************************************/
{
  wglDeleteContext(context);
}
/******************************************************************************/


/******************************************************************************/
bool OpenGLContext::MakeCurrent()
/******************************************************************************/
{
  // Context muss da sein
  if (!context) return false;

  // Context aktivieren
  return (wglMakeCurrent(dc,context)==(BOOL)TRUE);
}
/******************************************************************************/


/******************************************************************************/
void OpenGLContext::SwapBuffers()
/******************************************************************************/
{
  ::SwapBuffers(dc);
}
/******************************************************************************/
