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


#ifndef __SPLASHSCREEN__
#define __SPLASHSCREEN__

#include <string>
#include <gtk/gtk.h>
#include "sarturis//base/referenced.h"
#include "sarturis/gtk/base.h"

/******************************************************************************/
namespace sarturis
{
  namespace gtk
  {
    class SplashScreen : public Base, public Referenced
    {
      public:
        // Konstruktor
        SplashScreen();

        // Anzeigen und verstecken
        void Show();
        void Hide();

        // Text setzen
        void Message(const std::string& Msg);

      protected:
        // Destruktor
        ~SplashScreen();

      private:
        // Text
        std::string text;

        // Fenster-Widget und Zeichenbereich
        GtkWidget* win;
        GtkWidget* splash_area;

        // Bild und Bild mit Text-Hintergrund-Streifen
        GdkPixbuf* image;
        cairo_surface_t* textbar;

        // Text hoehe
        double th;

        // Zeichnen
        static gboolean draw(GtkWidget* widget, cairo_t* cr, SplashScreen* s);
    };
  }
}
/******************************************************************************/

#endif
