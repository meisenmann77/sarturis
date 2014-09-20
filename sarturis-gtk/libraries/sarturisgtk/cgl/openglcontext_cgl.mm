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


#include <OpenGL/gl.h>
#include <gdk/gdk.h>
#include <gdk/gdkquartz.h>

#include "sarturis/base/generalexception.h"
#include "openglcontext_cgl.h"
using namespace sarturis;
using namespace sarturis::gtk;


/******************************************************************************/
sarturis::ref<OpenGLContext> OpenGLContext::Create(GtkWidget* Widget)
/******************************************************************************/
{
  return new OpenGLContextCGL(Widget);
}
/******************************************************************************/


/******************************************************************************/
OpenGLContextCGL::OpenGLContextCGL(GtkWidget* Widget):ctxt(0),view(0)
/******************************************************************************/
{
  // Pixelformat
  NSOpenGLPixelFormatAttribute attr[]={NSOpenGLPFAColorSize, 24,
                                       NSOpenGLPFAAlphaSize,  8,
                                       NSOpenGLPFADepthSize,  1,
                                       NSOpenGLPFADoubleBuffer,
                                       0};
  NSOpenGLPixelFormat* pf=[[NSOpenGLPixelFormat alloc] initWithAttributes:attr];

  // Kontext
  ctxt=[[NSOpenGLContext alloc] initWithFormat:pf shareContext:nil];

  // View holen
  GdkWindow* win=gtk_widget_get_window(Widget);
  view=gdk_quartz_window_get_nsview(win);

  // View und Kontext verbinden
  [ctxt setView:view];
}
/******************************************************************************/


/******************************************************************************/
OpenGLContextCGL::~OpenGLContextCGL()
/******************************************************************************/
{
  [ctxt release];
}
/******************************************************************************/


/******************************************************************************/
void OpenGLContextCGL::Update(GtkAllocation A)
/******************************************************************************/
{
  // Abmessungen setzen
  NSRect rect=NSMakeRect(A.x,A.y,A.width,A.height);
  [view setFrame:rect];

  // Kontext aktualisieren und raus
  [ctxt update]; 
}
/******************************************************************************/


/******************************************************************************/
bool OpenGLContextCGL::MakeCurrent()
/******************************************************************************/
{
  [ctxt makeCurrentContext];
  return true;
}
/******************************************************************************/


/******************************************************************************/
void OpenGLContextCGL::SwapBuffers()
/******************************************************************************/
{
  [ctxt flushBuffer];
}
/******************************************************************************/
