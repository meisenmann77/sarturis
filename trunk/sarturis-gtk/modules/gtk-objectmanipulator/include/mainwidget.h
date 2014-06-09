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


#ifndef __MAINWIDGET__
#define __MAINWIDGET__

#include <set>
#include "sarturis/gtk/widget.h"
#include "typetree.h"
#include "instancetree.h"
#include "textentry.h"


/******************************************************************************/
namespace sarturis
{
  namespace gtk
  {
    class MainWidget : public Widget, public SelectionHandler
    {
      public:
        // Konstruktor
        MainWidget();

        // Instanz hinzufuegen
        void AddInstance(sarturis::ref<Referenced> R);

        // Impl. SelectionHandler
        void Change();

        // Getter fuer InstanceTree
        sarturis::ref<InstanceTree> GetInstanceTree() const;

      protected:
        // Destruktor
        ~MainWidget();

      private:
        // Impl. Widget::setup
        GtkWidget* setup();

        // Baumansichten und Eingabefelder
        sarturis::ref<TypeTree> typetree;
        sarturis::ref<InstanceTree> instancetree;
        sarturis::ref<TextEntry> instancefilter;

        // Liste mit Typen
        typedef std::set<std::string> type_set;
        type_set types;
    };
  }
}
/******************************************************************************/

#endif
