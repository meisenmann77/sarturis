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


#ifndef __DIGITALLED__
#define __DIGITALLED__

#include "sarturis/interface/digitaloutput.h"
#include "sarturis/gtk/activewidget.h"

/******************************************************************************/
namespace sarturis
{
  namespace gtk
  {
    class DigitalLED : public ActiveWidget,
                       public DigitalOutput
    {
      public:
        // Konstruktor
        DigitalLED(double Red, double Green, double Blue);

        // Setze Daten
        void Set(int V);

        // Update-Methode
        void Update();

      protected:
        // Destruktor
        ~DigitalLED();

      private:
        // Zwischengespeicherte Werte
        double red;
        double green;
        double blue;

        // Impl. Widget::setup
        GtkWidget* setup();

        // Callback
        static gboolean draw(GtkWidget* widget, cairo_t* cr, DigitalLED* d);

        // Zwischengespeicherte Werte
        int value;
        int old_value;

        // Widget
        GtkWidget* area;

        // Farbe
        GdkColor color_on;
        GdkColor color_off;
    };
  }
}
/******************************************************************************/

#endif
