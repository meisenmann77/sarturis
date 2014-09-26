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


#ifndef __VIEWER__
#define __VIEWER__

#include <vlc/libvlc.h>
#include <vlc/libvlc_media.h>
#include <vlc/libvlc_media_player.h>
#include "sarturis/gtk/widget.h"
#include "mediasource.h"

/******************************************************************************/
namespace sarturis
{
  namespace vlc
  {
    namespace gtk
    {
      class Viewer : public sarturis::gtk::Widget, public Base
      {
        public:
          // Konstruktor
          Viewer(sarturis::ref<MediaSource> Source);

        protected:
          // Destruktor
          ~Viewer();

        private:
          sarturis::ref<MediaSource> source;
          libvlc_media_player_t* player;

          GtkWidget* setup();
          void set_widget(GtkWidget* w);
          static void realize(GtkWidget* w, Viewer* v);
      };
    }
  }
}
/******************************************************************************/

#endif
