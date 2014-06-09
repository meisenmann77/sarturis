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


#include "include/button.h"
using namespace sarturis;
using namespace sarturis::gtk;


/******************************************************************************/
Button::Button(sarturis::ref<Widget> Label,
               sarturis::ref<Executable> Click):
          label(Label),
          click(Click)
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
Button::~Button()
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
GtkWidget* Button::setup()
/******************************************************************************/
{
  // Button mit Child-Widget erzeugen und anzeigen
  GtkWidget* button=gtk_button_new();
  gtk_container_add(GTK_CONTAINER(button),label->GetWidget());
  gtk_widget_show(button);

  // Callback
  g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(clicked),this);

  return button;
}
/******************************************************************************/


/******************************************************************************/
void Button::clicked(GtkWidget* button, Button* b)
/******************************************************************************/
{
  if (b->click.valid()) b->click->Exec();
}
/******************************************************************************/
