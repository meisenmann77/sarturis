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


#ifndef __TYPETREE__
#define __TYPETREE__

#include <string>
#include <map>
#include "sarturis/gtk/widget.h"
#include "selectionhandler.h"

/******************************************************************************/
namespace sarturis
{
  namespace gtk
  {
    class TypeTree : public Widget
    {
      public:
        // Konstruktor
        TypeTree(SelectionHandler& H);

        // Typ hinzufuegen
        void Add(const std::string& T);

        // Abfrage
        bool Active(const std::string& T);

      protected:
        // Destruktor
        ~TypeTree();

      private:
        // Impl. Widget::setup
        GtkWidget* setup();

        // Widget und Datenmodell;
        GtkWidget* tree;
        GtkTreeStore* treestore;

        // Zuordnung Typ-Knoten
        typedef std::map<std::string,GtkTreeIter> type_map;
        type_map types;

        // Helfer
        void set_active(GtkTreeIter iter, gboolean value);

        // GTK-Callback
        static void toggle(GtkCellRendererToggle* cell_renderer, gchar* path,
                           TypeTree* t);

        // Handler
        SelectionHandler& handler;
    };
  }
}
/******************************************************************************/

#endif // __TYPETREE__
