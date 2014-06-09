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


#ifndef __SARTURIS_GTK_WINDOW__
#define __SARTURIS_GTK_WINDOW__

#include <gtk/gtk.h>
#include <string>
#include "export.h"
#include "base.h"
#include "widget.h"

/******************************************************************************/
namespace sarturis
{
  namespace gtk
  {
    class DLLIMPORT Window : public Base, virtual public Referenced
    {
      public:
        // Konstruktor
        Window(sarturis::ref<Widget> Child, const std::string& Title,
               int X, int Y, unsigned int Width, unsigned int Height,
               unsigned int BorderWidth, bool FullScreen, bool QuitOnClose,
               bool AllowClose);

        // Display und Screen setzen
        virtual void SetDisplay(const std::string& Display);
        virtual void SetScreen(int Screen);

        // Beenden
        virtual bool Close();
        virtual bool Closed() const;

        // Anzeigen und Verstecken
        virtual void Show() const;
        virtual void Hide() const;

        // Groesse, Titel und Icon setzen
        virtual void SetSize(unsigned int Width, unsigned int Height);
        virtual void SetTitle(const std::string& Title);
        virtual void SetIcon(const guint8* data) const;
        virtual bool SetIcon(const std::string& Filename) const;
        virtual void SetIcon(GdkPixbuf* pb) const;

      protected:
        // Destruktor
        virtual ~Window();

      private:
        // Widget
        sarturis::ref<Widget> child;

        // Window
        GtkWidget* window;

        // Attribute
        bool quitonclose;
        bool allowclose;
        bool closed;

        // Callback fuer Fenster schliessen
        static gboolean delete_event(GtkWidget* widget, GdkEvent* event,
                                     Window* w);

        // Callback fuer Quit
        static gboolean do_quit(gpointer data);
    };
  }
}
/******************************************************************************/

#endif
