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


#ifndef __BOX__
#define __BOX__

#include <vector>
#include "sarturis/gtk/activewidget.h"
#include "gtkwidget-standard-configurations.h"

/******************************************************************************/
namespace sarturis
{
  namespace gtk
  {
    // Allgemeine Box
    class Box : public ActiveWidget
    {
      protected:
        // typedef fuer Widget-Erstellung
        typedef GtkWidget*(*create_box_method)(gboolean,gint);

        // Konstruktor
        Box(bool Homogeneous, unsigned int Spacing, unsigned int BorderWidth,
            create_box_method CreateBox);

        // Destruktor
        ~Box();

        // Widget hinzufuegen
        void PackStart(sarturis::ref<Widget> Child, bool Expand, bool Fill,
                       unsigned int Padding);
        void PackEnd(sarturis::ref<Widget> Child, bool Expand, bool Fill,
                     unsigned int Padding);

      private:
        // typedef fuer Konfigurationen
        typedef struct _cfg
        {
          _cfg(sarturis::ref<Widget> Child, bool Expand, bool Fill,
               unsigned int Padding);

          sarturis::ref<Widget> child;
          bool expand;
          bool fill;
          unsigned int padding;
        } cfg;

        // Zwischengespeicherte Konfiguration
        std::vector<cfg> pack_start;
        std::vector<cfg> pack_end;
        bool homogeneous;
        unsigned int spacing;
        unsigned int borderwidth;
        create_box_method create_box;

        // Impl. Widget::setup
        GtkWidget* setup();

        // vector auf gehaltene Widgets
        std::vector<sarturis::ref<Widget> > childs;

        // Style-Set Signal aus GTK
        static void styleset(GtkWidget* widget, GtkStyle* previous_style,
                             GtkWidget* parent);
    };

    // HBox
    class HBox : public Box
    {
      public:
        // Konstruktor
        HBox(hbox::_PackStart_Vec_ S, hbox::_PackEnd_Vec_ E,
             bool Homogeneous, unsigned int Spacing, unsigned int BorderWidth);

      protected:
        // Destruktor
        ~HBox();
    };

    // VBox
    class VBox : public Box
    {
      public:
        // Konstruktor
        VBox(vbox::_PackStart_Vec_ S, vbox::_PackEnd_Vec_ E,
             bool Homogeneous, unsigned int Spacing, unsigned int BorderWidth);

      protected:
        // Destruktor
        ~VBox();
    };
  }
}
/******************************************************************************/

#endif
