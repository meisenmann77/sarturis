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


#ifndef __GTKWIDGET__
#define __GTKWIDGET__

#include <string>
#include <vector>
#include "sarturis/gtk/widget.h"
#include "sarturis/python/object.h"

namespace sarturis
{
  namespace python
  {
    namespace gtk
    {
      class Widget;
    }
  }
}

#include "python-gtkwidget-configurations.h"

/******************************************************************************/
namespace sarturis
{
  namespace python
  {
    namespace gtk
    {
      class Widget : public sarturis::gtk::Widget, public Object
      {
        public:
          // Konstruktor
          Widget(widget::_Parent_Vec_ P, widget::_Children_Vec_ C,
                 const std::string& N);

        protected:
          // Destruktor
          ~Widget();

        private:
          // Impl. Widget
          GtkWidget* setup();

          // Widget
          GtkWidget* widget;

          // Kinder und Parent-Widgets
          widget::_Parent_Vec_ parents;
          widget::_Children_Vec_ children;
      };
    }
  }
}
/******************************************************************************/

#endif // __GTKWIDGET__
