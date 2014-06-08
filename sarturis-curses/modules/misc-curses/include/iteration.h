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


#ifndef __MISCCURSES_ITERATION__
#define __MISCCURSES_ITERATION__

#include <vector>
#include <sarturis/interface/executable.h>
#include <sarturis/curses/widget.h>

/******************************************************************************/
namespace sarturis
{
  namespace curses
  {
    class Iteration : public Executable, public Base
    {
      public:
		// Fehler im GCC? Typedef ist nicht da!
		typedef std::vector<sarturis::ref<Widget> > widget_vec;	
        // Konstruktor
        Iteration(const widget_vec& V);

        // Impl. ExecutionBlock::Exec
        void Exec();

      protected:
        // Destruktor
        ~Iteration();

      private:
        // Verwaltete Widgets
        widget_vec widgets;

        // Verwaltete Widgets mit Focus
        widget_vec focus_widgets;
        sarturis::ref<Widget> focus;

        // Focus-Methoden
        sarturis::ref<Widget> focus_next();
        sarturis::ref<Widget> focus_prev();
    };
  }
}
/******************************************************************************/

#endif
