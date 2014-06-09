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


#ifndef __PANED__
#define __PANED__

#include "sarturis/gtk/activewidget.h"

/******************************************************************************/
namespace sarturis
{
  namespace gtk
  {
    // Allgemeines Paned
    class Paned : public ActiveWidget
    {
      public:
        // typedef fuer Widget-Erstellung
        typedef GtkWidget*(*create_paned_method)();

      protected:
        // Konstruktor
        Paned(sarturis::ref<Widget> C1, sarturis::ref<Widget> C2,
              unsigned int Position, create_paned_method CreatePaned);

        // Destruktor
        ~Paned();

      private:
        // Zwischengespeicherte Konfiguration
        unsigned int position;
        create_paned_method create_paned;

        // Impl. Widget::setup
        GtkWidget* setup();

        // Widgets
        sarturis::ref<Widget> c1;
        sarturis::ref<Widget> c2;

        // Style-Set Signal aus GTK
        static void styleset(GtkWidget* widget, GtkStyle* previous_style,
                             GtkWidget* parent);
    };

    // HPaned
    class HPaned : public Paned
    {
      public:
        // Konstruktor
        HPaned(sarturis::ref<Widget> Left, sarturis::ref<Widget> Right,
               unsigned int Position);

      protected:
        // Destruktor
        ~HPaned();
    };

    // VPaned
    class VPaned : public Paned
    {
      public:
        // Konstruktor
        VPaned(sarturis::ref<Widget> Upper, sarturis::ref<Widget> Lower,
               unsigned int Position);

      protected:
        // Destruktor
        ~VPaned();
    };
  }
}
/******************************************************************************/

#endif
