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


#include "include/digitaltogglebutton.h"
#include <iostream>
using namespace sarturis;
using namespace sarturis::gtk;

/******************************************************************************/
DigitalToggleButton::DigitalToggleButton(sarturis::ref<Widget> Label,
                                         bool Toggled):
                       togglebutton(0),
                       label(Label),
                       value(Toggled ? 1 : 0),
											 defaultValue(value)
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
DigitalToggleButton::~DigitalToggleButton()
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
int DigitalToggleButton::Get()
/******************************************************************************/
{
  return value;
}
/******************************************************************************/


/******************************************************************************/
void DigitalToggleButton::Update()
/******************************************************************************/
{
  if (togglebutton)
  {
    value=(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton)) ==
           (gboolean)TRUE);
  }
}
/******************************************************************************/


/******************************************************************************/
GtkWidget* DigitalToggleButton::setup()
/******************************************************************************/
{
  // Toggle-Button erzeugen und anzeigen
  togglebutton=gtk_toggle_button_new();
  gtk_container_add(GTK_CONTAINER(togglebutton),label->GetWidget());
  gtk_widget_show(togglebutton);

  // Status einstellen
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(togglebutton),value);

  return togglebutton;
}
/******************************************************************************/


/******************************************************************************/
void DigitalToggleButton::Reset()
/******************************************************************************/
{
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(togglebutton),defaultValue);
}
/******************************************************************************/
