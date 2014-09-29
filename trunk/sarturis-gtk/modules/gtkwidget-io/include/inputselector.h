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


#ifndef __INPUT_SELECTOR__
#define __INPUT_SELECTOR__

#include <map>
#include <string>
#include <vector>
#include "sarturis/apps/datamanager.h"
#include "sarturis/gtk/activewidget.h"
#include "sarturis/interface/analoginput.h"
#include "sarturis/interface/digitalinput.h"
#include "gtkwidget-io-configurations.h"


/******************************************************************************/
namespace sarturis
{
  namespace gtk
  {
    template <class T1, class T2> class InputSelector : public ActiveWidget,
                                                        public T1
    {
      public:
        // Konstruktor
        InputSelector(T2 Items):vitems(Items)
        {
          // Items in map speichern
          for (unsigned int i=0;i<Items.size();++i)
          {
            items[Items[i].Caption]=Items[i].Instance;
          }

          // Wenn leer, dann alle vom Typ aus DataManager
          if (!items.size())
          {
            DataManager::data_map m=DataManager::GetAll<T1>();
            for (DataManager::data_map::const_iterator iter=m.begin();
                   iter!=m.end();++iter)
            {
              // Typ-Ueberpruefung
              sarturis::ref<T1> r=iter->second.as<T1>();
              if (r.valid()) items[iter->first]=r;
            }
          }
        }

        // Update-Methode
        void Update()
        {
          // Abfangen
          if (!cb) return;

          // atkives Element bestimmen
          std::string t=gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(cb));

          active=items[t];
        }

      protected:
        // Destruktor
        ~InputSelector() { ; }

				// aktuelles Element
				sarturis::ref<T1> active;

        // Elemente
        std::map<std::string, sarturis::ref<T1> > items;
        T2 vitems;

      private:
        // Impl. Widget::setup
        GtkWidget* setup()
        {
          // ComboBox erzeugen
          cb=gtk_combo_box_text_new_with_entry();

          // items setzen
          for(unsigned int i=0;i<vitems.size();++i)
          {
            gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(cb),vitems[i].Caption.c_str());
          }

	        // ComboBox anzeigen und return
          gtk_widget_show(cb);
          return cb;
        }

        // Widget
        GtkWidget* cb;
    };

    // Abgeleitete Klassen
    class AnalogSelector : public InputSelector<sarturis::AnalogInput, analogselector::_Item_Vec_>
    {
      public:
        AnalogSelector(analogselector::_Item_Vec_ V);
        double Get();

      protected:
        ~AnalogSelector();
    };

    class DigitalSelector : public InputSelector<sarturis::DigitalInput, digitalselector::_Item_Vec_>
    {
      public:
        DigitalSelector(digitalselector::_Item_Vec_ V);
        int Get();

      protected:
        ~DigitalSelector();
    };
  }
}
/******************************************************************************/

#endif
