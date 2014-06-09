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


#ifndef __INSTANCETREE__
#define __INSTANCETREE__

#include <map>
#include <set>
#include "sarturis/base/mutex.h"
#include "sarturis/gtk/widget.h"
#include "sarturis/reflection/type.h"

/******************************************************************************/
namespace sarturis
{
  namespace gtk
  {
    class InstanceTree : public Widget
    {
      public:
        // Konstruktor
        InstanceTree();
        
        // Instanz hinzufuegen
        void Add(sarturis::ref<reflection::Type> T,sarturis::ref<Referenced> R);

        // Filter
        void SetFilter(const std::set<std::string>& Types,
                       const std::string& NameFilter);

        // Veraenderungen
        std::string GetChange(unsigned int Id);

      protected:
        // Destruktor
        ~InstanceTree();

      private:
        // Impl. Widget::setup
        GtkWidget* setup();

        // Widget und Datenmodell;
        GtkWidget* tree;
        GtkTreeStore* treestore;
        GtkTreeModel* filtered;

        // Zuordnung Instanz-Knoten
        typedef std::map<std::string,GtkTreeIter> instance_map;
        instance_map instances;

        // Filter
        std::set<std::string> types;
        std::string namefilter;

        // Liste der Aenderungen zum Verteilen
        sarturis::ref<Mutex> lock;
        std::vector<std::string> changes;

        // Helfer
        void attribute_tree(GtkTreeIter r, Referenced* R,
                            sarturis::ref<reflection::ConfigurationParent> c);

        // GTK-Callbacks
        static void edited(GtkCellRendererText* cell, gchar* path_string,
                           gchar* new_text, InstanceTree* t);
        static gboolean filter(GtkTreeModel* model, GtkTreeIter* iter,
                               InstanceTree* t);
    };
  }
}
/******************************************************************************/

#endif // __INSTANCETREE__
