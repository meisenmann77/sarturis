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


#include "include/frame.h"
using namespace sarturis::gtk;


/******************************************************************************/
Frame::Frame(sarturis::ref<Widget> Child, sarturis::ref<Widget> Caption,
             unsigned int BorderWidth):
         borderwidth(BorderWidth),
         child(Child),
         caption(Caption)
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
Frame::~Frame()
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
GtkWidget* Frame::setup()
/******************************************************************************/
{
  // Frame
  GtkWidget* frame=gtk_frame_new(0);
  gtk_frame_set_label_widget(GTK_FRAME(frame),caption->GetWidget());

  // Randbreite
  gtk_container_set_border_width(GTK_CONTAINER(frame),borderwidth);

  // Anzeigen und Child draufpacken
  gtk_widget_show(frame);
  gtk_container_add(GTK_CONTAINER(frame),child->GetWidget());

  // Verbinde mit Style-Set-Callback
  g_signal_connect(G_OBJECT(child->GetWidget()),"style-set",
                   G_CALLBACK(styleset),frame);

  return frame;
}
/******************************************************************************/


/******************************************************************************/
void Frame::styleset(GtkWidget* widget, GtkStyle* previous_style,
                     GtkWidget* parent)
/******************************************************************************/
{
  gtk_widget_set_style(widget,gtk_widget_get_style(parent));
}
/******************************************************************************/
