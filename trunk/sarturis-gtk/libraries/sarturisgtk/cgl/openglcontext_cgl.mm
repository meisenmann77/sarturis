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
OpenGLContextCGL::OpenGLContextCGL(GtkWidget* Widget):widget(Widget),context(0)
/******************************************************************************/
{
  // Double-Buffered einstellen
  gtk_widget_set_double_buffered(widget,FALSE);

  /* TODO: Implement me */

    CGLPixelFormatObj pix; 
    GLint             npix; 
    CGLPixelFormatAttribute attribs[] = { 
        (CGLPixelFormatAttribute) 0
    }; 

    CGLChoosePixelFormat( attribs, &pix, &npix ); 
    CGLCreateContext( pix, NULL, &context ); 
    CGLSetCurrentContext( context ); 

    printf("Vendor:   %s\n", glGetString(GL_VENDOR)                  ); 
    printf("Renderer: %s\n", glGetString(GL_RENDERER)                ); 
    printf("Version:  %s\n", glGetString(GL_VERSION)                 ); 
    printf("GLSL:     %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
}
/******************************************************************************/


/******************************************************************************/
OpenGLContextCGL::~OpenGLContextCGL()
/******************************************************************************/
{
  /* TODO: Implement me */
}
/******************************************************************************/


/******************************************************************************/
bool OpenGLContextCGL::MakeCurrent()
/******************************************************************************/
{
  // Context muss da sein
  if (!context) return false;

  /* TODO: Implement me */
  CGLSetCurrentContext( context );
  return true;
}
/******************************************************************************/


/******************************************************************************/
void OpenGLContextCGL::SwapBuffers()
/******************************************************************************/
{
  /* TODO: Implement me */
  CGLFlushDrawable(context);
}
/******************************************************************************/
