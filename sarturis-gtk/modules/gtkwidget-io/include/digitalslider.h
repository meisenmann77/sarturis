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


#ifndef __DIGITALSLIDER__
#define __DIGITALSLIDER__

#include "sarturis/interface/resettable.h"
#include "sarturis/interface/digitalinput.h"
#include "sarturis/gtk/activewidget.h"

/******************************************************************************/
namespace sarturis
{
  namespace gtk
  {
    class DigitalSlider : public ActiveWidget,
                          public DigitalInput,
                          public Resettable
    {
      public:
        // Konstruktor
        DigitalSlider(double Value, double Min, double Max,
                      const std::string& Orientation, bool ShowValue);

        // Wert
        int Get();

        // Update-Methode
        void Update();

        // Reset-Methode
        void Reset();

      protected:
        // Destruktor
        ~DigitalSlider();

      private:
        // Zwischengspeicherte config
        std::string orientation;
        double min;
        double max;

        // Impl. Widget::setup
        GtkWidget* setup();

        // Tabelle
        GtkWidget* scale;

        // Cache fuer Wert
        int value;

        // Anfangswert fuer Reset
        int value0;

        // Flag
        bool show_value;
    };
  }
}
/******************************************************************************/

#endif
