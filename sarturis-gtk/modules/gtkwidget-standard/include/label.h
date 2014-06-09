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


#ifndef __LABEL__
#define __LABEL__

#include <string>
#include "sarturis/gtk/widget.h"

/******************************************************************************/
namespace sarturis
{
  namespace gtk
  {
    class Label : public Widget
    {
      public:
        // Konstruktor
        Label(const std::string& Text, bool Markup, bool LineWrap,
              double XAlign, double YAlign);

      protected:
        // Destruktor
        ~Label();

      private:
        // Zwischengespeicherte Konfiguration
        std::string text;
        bool markup;
        bool linewrap;
        double xalign;
        double yalign;

        // Impl. Widget::setup
        GtkWidget* setup();
    };
  }
}
/******************************************************************************/

#endif
