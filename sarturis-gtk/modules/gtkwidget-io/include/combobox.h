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


#ifndef __COMBO_BOX__
#define __COMBO_BOX__

#include <string>
#include "sarturis/interface/textinput.h"
#include "sarturis/gtk/activewidget.h"
#include "gtkwidget-io-configurations.h"

/******************************************************************************/
namespace sarturis
{
  namespace gtk
  {
    class ComboBox : public ActiveWidget,
                     public TextInput
    {
      public:

        // Konstruktor
        ComboBox(const combobox::_Item_Vec_& items);

        // Impl. TextInput::Get
        std::string Get();

        // Update-Methode
        void Update();

      protected:
        // Destruktor
        ~ComboBox();

      private:
        // Impl. Widget::setup
        GtkWidget* setup();

        // Widget
        GtkWidget* _comboBox;

        // zwischengespeicherter Wert
        combobox::_Item_Vec_ _items;
				
				// aktueller Text
				std::string _value;
    };
  }
}
/******************************************************************************/

#endif
