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

  // Drawable (des Widgets) setzen
  v->set_widget(w);

  // Abspielen
  libvlc_media_player_play(v->player);
}
/******************************************************************************/
