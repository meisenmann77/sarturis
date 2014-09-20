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


#ifndef __SARTURIS_GTK_OPENGLCONTEXTCGL__
#define __SARTURIS_GTK_OPENGLCONTEXTCGL__

#include <gtk/gtk.h>
#include <OpenGL/OpenGL.h>

#include "sarturis/gtk/export.h"
#include "sarturis/gtk/openglcontext.h"

/******************************************************************************/
namespace sarturis
{
  namespace gtk
  {
    class DLLIMPORT OpenGLContextCGL : public OpenGLContext
    {
      public:
        // Konstruktor
        OpenGLContextCGL(GtkWidget* Widget);

        // Fensterkoordinaten aktualisierten
        void Update(GtkAllocation A);

        // Aktivieren und Buffer swappen
        bool MakeCurrent();
        void SwapBuffers();

      protected:
        // Destruktor
        ~OpenGLContextCGL();

      private:
        // Kontext und View
        NSOpenGLContext* ctxt;
        NSView* view;
    };
  }
}
/******************************************************************************/

#endif
