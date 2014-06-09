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


#include "sarturis/gtk/compat.h"
#include "include/box.h"
using namespace sarturis::gtk;


/******************************************************************************/
Box::Box(bool Homogeneous, unsigned int Spacing, unsigned int BorderWidth,
         create_box_method CreateBox):homogeneous(Homogeneous),
                                      spacing(Spacing),
                                      borderwidth(BorderWidth),
                                      create_box(CreateBox)
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
Box::~Box()
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
void Box::PackStart(sarturis::ref<Widget> Child, bool Expand, bool Fill,
                    unsigned int Padding)
/******************************************************************************/
{
  pack_start.push_back(cfg(Child,Expand,Fill,Padding));
}
/******************************************************************************/


/******************************************************************************/
void Box::PackEnd(sarturis::ref<Widget> Child, bool Expand, bool Fill,
                  unsigned int Padding)
/******************************************************************************/
{
  pack_end.push_back(cfg(Child,Expand,Fill,Padding));
}
/******************************************************************************/


/******************************************************************************/
GtkWidget* Box::setup()
/******************************************************************************/
{
  // Box
  GtkWidget* box=create_box(homogeneous,spacing);
  gtk_widget_show(box);

  // Randbreite
  gtk_container_set_border_width(GTK_CONTAINER(box),borderwidth);

  // Konfiguriere PackStart
  for (unsigned int i=0;i<pack_start.size();++i)
  {
    // Packe
    gtk_box_pack_start(GTK_BOX(box),pack_start[i].child->GetWidget(),
                       pack_start[i].expand,pack_start[i].fill,
                       pack_start[i].padding);

    // Verbinde mit Style-Set-Callback
    g_signal_connect(G_OBJECT(pack_start[i].child->GetWidget()),"style-set",
                     G_CALLBACK(styleset),box);
  }

  // Konfiguriere PackEnd
  for (unsigned int i=0;i<pack_end.size();++i)
  {
    // Packe
    gtk_box_pack_end(GTK_BOX(box),pack_end[i].child->GetWidget(),
                     pack_end[i].expand,pack_end[i].fill,pack_end[i].padding);

    // Verbinde mit Style-Set-Callback
    g_signal_connect(G_OBJECT(pack_end[i].child->GetWidget()),"style-set",
                     G_CALLBACK(styleset),box);
  }

  return box;
}
/******************************************************************************/


/******************************************************************************/
void Box::styleset(GtkWidget* widget, GtkStyle* previous_style,
                   GtkWidget* parent)
/******************************************************************************/
{
  gtk_widget_set_style(widget,gtk_widget_get_style(parent));
}
/******************************************************************************/


/******************************************************************************/
Box::_cfg::_cfg(sarturis::ref<Widget> Child, bool Expand, bool Fill,
                unsigned int Padding):
             child(Child),
             expand(Expand),
             fill(Fill),
             padding(Padding)
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
HBox::HBox(hbox::_PackStart_Vec_ S, hbox::_PackEnd_Vec_ E, bool Homogeneous,
           unsigned int Spacing, unsigned int BorderWidth):
        Box(Homogeneous,Spacing,BorderWidth,_gtk_hbox_new)
/******************************************************************************/
{
  for (unsigned int i=0;i<S.size();++i)
  {
    PackStart(S[i].Instance,S[i].Expand,S[i].Fill,S[i].Padding);
  }
  for (unsigned int i=0;i<E.size();++i)
  {
    PackEnd(E[i].Instance,E[i].Expand,E[i].Fill,E[i].Padding);
  }
}
/******************************************************************************/


/******************************************************************************/
HBox::~HBox()
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
VBox::VBox(vbox::_PackStart_Vec_ S, vbox::_PackEnd_Vec_ E, bool Homogeneous,
           unsigned int Spacing, unsigned int BorderWidth):
        Box(Homogeneous,Spacing,BorderWidth,_gtk_vbox_new)
/******************************************************************************/
{
  for (unsigned int i=0;i<S.size();++i)
  {
    PackStart(S[i].Instance,S[i].Expand,S[i].Fill,S[i].Padding);
  }
  for (unsigned int i=0;i<E.size();++i)
  {
    PackEnd(E[i].Instance,E[i].Expand,E[i].Fill,E[i].Padding);
  }
}
/******************************************************************************/


/******************************************************************************/
VBox::~VBox()
/******************************************************************************/
{
}
/******************************************************************************/
