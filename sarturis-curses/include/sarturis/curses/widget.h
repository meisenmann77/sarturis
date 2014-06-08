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


#ifndef __SARTURIS_CURSES_WIDGET__
#define __SARTURIS_CURSES_WIDGET__

#include <ncurses.h>
#include <string>
#include "sarturis/base/referenced.h"
#include "export.h"
#include "base.h"

/******************************************************************************/
namespace sarturis
{
  namespace curses
  {
    class DLLIMPORT Widget : virtual public Referenced, public Base
    {
      public:
        // Focus-Handling
        virtual bool CanHaveFocus()=0;
        virtual void SetFocus(bool Focus);

        // Key-Handling
        virtual void HandleKey(int Key)=0;

        // Zeichnen
        virtual void Draw();

        // Farben
        virtual void SetBgColor(int Color);
        virtual void SetFgColor(int Color);
        virtual void SetColors(const std::string& Bg, const std::string& Fg);

      protected:
        // Konstruktor fuer neues Window
        Widget(unsigned int X, unsigned int Y,
               unsigned int Width, unsigned int Height);

        // Destruktor
        virtual ~Widget();

        // Zeichne Inhalt
        virtual void draw_content()=0;

        // Bewegen
        virtual void move_by(int x, int y);
        virtual void move_to(int x, int y);

        // NCURSES-Window
        WINDOW* win;

        // Geometrie
        unsigned int x;
        unsigned int y;
        unsigned int width;
        unsigned int height;

        // Farben
        int bg_col;
        int fg_col;
        int color;

        // Focus
        bool focus;
    };

    // Typ fuer vector mit Widgets
    typedef std::vector<sarturis::ref<Widget> > widget_vec;
  }
}
/******************************************************************************/

#endif
