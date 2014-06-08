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


#ifndef __MISCCURSES_ANALOGSLIDER__
#define __MISCCURSES_ANALOGSLIDER__

#include <sarturis/interface/analoginput.h>
#include "bardrawer.h"

/******************************************************************************/
namespace sarturis
{
  namespace curses
  {
    class AnalogSlider : public BarDrawer,
                         public AnalogInput
    {
      public:
        // Konstruktor
        AnalogSlider(unsigned int X, unsigned int Y, unsigned int Width,
                     double Min, double Max, double Value, bool ShowValue,
                     const std::string& BgColor, const std::string& FgColor);

        // Wert
        double Get();

        // Focus
        bool CanHaveFocus();

        // Key-Handler
        void HandleKey(int Key);

      protected:
        // Destruktor
        ~AnalogSlider();

      private:
        // Zeichne
        void draw_content();
    };
  }
}
/******************************************************************************/

#endif
