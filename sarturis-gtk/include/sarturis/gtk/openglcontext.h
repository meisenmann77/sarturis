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


#ifndef __SARTURIS_GTK_OPENGLCONTEXT__
#define __SARTURIS_GTK_OPENGLCONTEXT__

#include <gtk/gtk.h>

#include "sarturis/base/referenced.h"
#include "sarturis/gtk/export.h"
#include "sarturis/gtk/base.h"

/******************************************************************************/
namespace sarturis
{
  namespace gtk
  {
    class DLLIMPORT OpenGLContext : virtual public Referenced, public Base
    {
      public:
        // Je nach Implementierung abgeleitete Instanz erzeugen
        static sarturis::ref<OpenGLContext> Create(GtkWidget* Widget);

        // Fensterkoordinaten aktualisierten
        virtual void Update(GtkAllocation A)=0;

        // Aktivieren und Buffer swappen
        virtual bool MakeCurrent()=0;
        virtual void SwapBuffers()=0;

      protected:
        // Destruktor
        virtual ~OpenGLContext() { ; }
    };
  }
}
/******************************************************************************/

#endif
