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


#ifndef __MISCCURSES_WINDOW__
#define __MISCCURSES_WINDOW__

#include <sarturis/curses/widget.h>

/******************************************************************************/
namespace sarturis
{
  namespace curses
  {
    class Window : public Widget
    {
      public:
        // Konstruktor
        Window(unsigned int X, unsigned int Y, unsigned Width,
               unsigned int Height, const std::string& Caption,
               const std::string& BgColor, const std::string& FgColor);

        // Focus
        bool CanHaveFocus();

        // Tasten-Event
        void HandleKey(int Key);

      protected:
        // Destruktor
        ~Window();

      private:
        // Impl. Widget::draw_content
        void draw_content();

        // Ueberschrift
        std::string caption;
    };
  }
}
/******************************************************************************/

#endif
