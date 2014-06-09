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


#ifndef __FRAME__
#define __FRAME__

#include <string>
#include <vector>
#include "sarturis/gtk/activewidget.h"

/******************************************************************************/
namespace sarturis
{
  namespace gtk
  {
    class Frame : public ActiveWidget
    {
      public:
        // Konstruktor
        Frame(sarturis::ref<Widget> Child, sarturis::ref<Widget> Caption,
              unsigned int BorderWidth);

      protected:
        // Destruktor
        ~Frame();

      private:
        // Zwischengespeicherte Konfiguration
        unsigned int borderwidth;

        // Impl. Widget::setup
        GtkWidget* setup();

        // Widgets
        sarturis::ref<Widget> child;
        sarturis::ref<Widget> caption;

        // Style-Set Signal aus GTK
        static void styleset(GtkWidget* widget, GtkStyle* previous_style,
                             GtkWidget* parent);
    };
  }
}
/******************************************************************************/

#endif
