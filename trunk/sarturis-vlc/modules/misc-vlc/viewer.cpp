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


#ifdef WIN32
  #include <gdk/gdkwin32.h>
#else
  #include <gdk/gdkx.h>
#endif
#include "include/viewer.h"
using namespace sarturis::vlc;
using namespace sarturis::vlc::gtk;


/******************************************************************************/
Viewer::Viewer(sarturis::ref<MediaSource> Source):source(Source),player(0)
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
Viewer::~Viewer()
/******************************************************************************/
{
  if (player) libvlc_media_player_release(player);
}
/******************************************************************************/


/******************************************************************************/
GtkWidget* Viewer::setup()
/******************************************************************************/
{
  // Drawing-Area
  GtkWidget* area=gtk_drawing_area_new();
  gtk_widget_show(area);
  g_signal_connect(area,"realize",(GCallback)realize,this);
  return area;
}
/******************************************************************************/


/******************************************************************************/
void Viewer::realize(GtkWidget* w, Viewer* v)
/******************************************************************************/
{
  // Player erzeugen
  v->player=libvlc_media_player_new_from_media(v->source->GetMedia());

  // Drawable setzen
  #ifdef WIN32
    // Window-Handle
    libvlc_media_player_set_hwnd(v->player,(HWND)GDK_WINDOW_HWND(w->window));
  #else
    // X11-Id
    #ifdef SARTURIS_GTK2
      uint32_t xid=gdk_x11_drawable_get_xid(w->window);
    #else
      uint32_t xid=GDK_WINDOW_XID(gtk_widget_get_window(w));
    #endif
    libvlc_media_player_set_xwindow(v->player,xid);
  #endif

  // Abspielen
  libvlc_media_player_play(v->player);
}
/******************************************************************************/
