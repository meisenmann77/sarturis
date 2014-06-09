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


#ifndef __OBJECTMANIPULATOR__
#define __OBJECTMANIPULATOR__

#include <set>
#include "sarturis/base/mutex.h"
#include "sarturis/gtk/window.h"
#include "sarturis/gtk/widget.h"
#include "sarturis/data/objectreader.h"
#include "sarturis/data/objectwriter.h"
#include "mainwidget.h"


/******************************************************************************/
namespace sarturis
{
  namespace gtk
  {
    class ObjectManipulator : public Widget,
                              public sarturis::data::ObjectReader,
                              public sarturis::data::ObjectWriter
    {
      public:
        // Konstruktor
        ObjectManipulator();

        // Impl. ObjectReader und ObjectWriter
        void Read(sarturis::data::Data& d);
        void Write(sarturis::data::Data& d) const;

      protected:
        // Destruktor
        ~ObjectManipulator();

      private:
        // MainWidget und InstanceTree
        sarturis::ref<MainWidget> mainwidget;
        sarturis::ref<InstanceTree> instancetree;

        // Mutex
        sarturis::ref<Mutex> lock;

        // Impl. Widget::setup
        GtkWidget* setup();

        // Anfragen
        mutable std::set<unsigned int> requests;
    };
  }
}
/******************************************************************************/

#endif
