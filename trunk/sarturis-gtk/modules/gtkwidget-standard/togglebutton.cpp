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


#include "include/togglebutton.h"
using namespace sarturis;
using namespace sarturis::gtk;


/******************************************************************************/
ToggleButton::ToggleButton(sarturis::ref<Widget> Label,
                           sarturis::ref<Executable> ToggleOn,
                           sarturis::ref<Executable> ToggleOff):
          label(Label),
          toogleon(ToggleOn),
          toogleoff(ToggleOff)
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
ToggleButton::~ToggleButton()
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
GtkWidget* ToggleButton::setup()
/******************************************************************************/
{
  // Button mit Child-Widget erzeugen und anzeigen
  GtkWidget* button=gtk_toggle_button_new();
  gtk_container_add(GTK_CONTAINER(button),label->GetWidget());
  gtk_widget_show(button);

  // Callback verbinden und return
  g_signal_connect(G_OBJECT(button),"toggled",G_CALLBACK(toggled),this);
  return button;
}
/******************************************************************************/


/******************************************************************************/
void ToggleButton::toggled(GtkWidget* button, ToggleButton* tb)
/******************************************************************************/
{
  if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button)))
  {
    if (tb->toogleon.valid()) tb->toogleon->Exec();
  }
  else
  {
    if (tb->toogleoff.valid()) tb->toogleoff->Exec();
  }
}
/******************************************************************************/

