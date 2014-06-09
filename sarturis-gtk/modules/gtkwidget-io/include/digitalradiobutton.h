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


#ifndef __DIGITALRADIOBUTTON__
#define __DIGITALRADIOBUTTON__

#include "sarturis/interface/digitalinput.h"
//#include "sarturis/interface/resettable.h"
#include "sarturis/gtk/activewidget.h"

/******************************************************************************/
namespace sarturis
{
  namespace gtk
  {
    class DigitalRadioButton : public ActiveWidget,
                               public DigitalInput
															 //public Resettable
    {
      public:
        // Konstruktor
        DigitalRadioButton(sarturis::ref<Widget> Label,
                           sarturis::ref<DigitalRadioButton> GroupMember);

        // Impl. DigitalInput::GetValue
        int Get();

        // Update-Methode
        void Update();

				// Impl. Resetable::Reset()
				//void Reset();
				
				// Gibt Gruppe zurueck
				GSList* GetGroup();

      protected:
        // Destruktor
        ~DigitalRadioButton();

      private:
        // Impl. Widget::setup
        GtkWidget* setup();

        // Widget
        GtkWidget* radiobutton;

        // Referenz auf Label
        sarturis::ref<Widget> label;
        
        // RadioButton, zu dessen Gruppe der Button gehoeren soll
        sarturis::ref<DigitalRadioButton> groupMember;

        // zwischengespeicherter Wert
        int value;
    };
  }
}
/******************************************************************************/

#endif
