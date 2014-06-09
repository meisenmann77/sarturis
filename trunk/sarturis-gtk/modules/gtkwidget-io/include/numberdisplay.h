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


#ifndef __NUMBERDISPLAY__
#define __NUMBERDISPLAY__

#include <string>
#include "sarturis/interface/digitaloutput.h"
#include "sarturis/interface/analogoutput.h"
#include "sarturis/gtk/activewidget.h"

/******************************************************************************/
namespace sarturis
{
  namespace gtk
  {
    class NumberDisplay : public ActiveWidget,
                          public AnalogOutput,
                          public DigitalOutput
    {
      public:
        // Konstruktor
        NumberDisplay();

        // Setze Daten
        void Set(double V);
        void Set(int V);

        // Update-Methode
        void Update();

      protected:
        // Destruktor
        ~NumberDisplay();

      private:
        // Impl. Widget::setup
        GtkWidget* setup();

        // Zwischengespeicherter Wert
        std::string sval;

        // Widget
        GtkWidget* value;
    };
  }
}
/******************************************************************************/

#endif
