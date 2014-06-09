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


#ifndef __WINDOW__
#define __WINDOW__

#include "sarturis/apps/applicationcontext.h"
#include "sarturis/gtk/base.h"
#include "sarturis/gtk/window.h"
#include "gtkwidget-standard-configurations.h"


/******************************************************************************/
namespace sarturis
{
  namespace application
  {
    namespace gtk
    {
      class Window : public sarturis::gtk::Base, public application::Context
      {
        public:
          // Konstruktor
          Window(sarturis::ref<sarturis::gtk::Widget> Child,
                 window::_Icon_ Icon, const std::string& Title, int X, int Y,
                 unsigned int Width, unsigned int Height,
                 unsigned int BorderWidth, bool FullScreen, bool QuitOnClose,
                 bool AllowClose);

          // ApplicationContext
          void OnInit();
          bool OnLoop();
          void OnExit();
          void OnError();

        protected:
          // Destruktor
          ~Window();

        private:
          // Fenster
          sarturis::ref<sarturis::gtk::Window> window;
      };
    }
  }
}
/******************************************************************************/


#endif // __WINDOW__
