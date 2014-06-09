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
#include "include/paned.h"
using namespace sarturis::gtk;


/******************************************************************************/
Paned::Paned(sarturis::ref<Widget> C1, sarturis::ref<Widget> C2,
             unsigned int Position, create_paned_method CreatePaned):
          position(Position),
          create_paned(CreatePaned),
          c1(C1),
          c2(C2)
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
Paned::~Paned()
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
GtkWidget* Paned::setup()
/******************************************************************************/
{
  // Paned und Widgets
  GtkWidget* paned=create_paned();
  gtk_widget_show(paned);
  gtk_paned_add1(GTK_PANED(paned),c1->GetWidget());
  gtk_paned_add2(GTK_PANED(paned),c2->GetWidget());

  // Anzeigen
  gtk_widget_show(paned);

  // Position
  if (position) gtk_paned_set_position(GTK_PANED(paned),position);

  // Verbinde mit Style-Set-Callback
  g_signal_connect(G_OBJECT(c1->GetWidget()),"style-set",
                   G_CALLBACK(styleset),paned);
  g_signal_connect(G_OBJECT(c2->GetWidget()),"style-set",
                   G_CALLBACK(styleset),paned);

  return paned;
}
/******************************************************************************/


/******************************************************************************/
void Paned::styleset(GtkWidget* widget, GtkStyle* previous_style,
                     GtkWidget* parent)
/******************************************************************************/
{
  gtk_widget_set_style(widget,gtk_widget_get_style(parent));
}
/******************************************************************************/


/******************************************************************************/
HPaned::HPaned(sarturis::ref<Widget> Left, sarturis::ref<Widget> Right,
               unsigned int Position):
          Paned(Left,Right,Position,_gtk_hpaned_new)
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
HPaned::~HPaned()
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
VPaned::VPaned(sarturis::ref<Widget> Upper, sarturis::ref<Widget> Lower,
               unsigned int Position):
          Paned(Upper,Lower,Position,_gtk_vpaned_new)
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
VPaned::~VPaned()
/******************************************************************************/
{
}
/******************************************************************************/
