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


#include "include/digitalradiobutton.h"

using namespace sarturis;
using namespace sarturis::gtk;

/******************************************************************************/
DigitalRadioButton::DigitalRadioButton(sarturis::ref<Widget> Label,
                                       sarturis::ref<DigitalRadioButton> GroupMember):
                                       radiobutton(0),
                                       label(Label),
                                       groupMember(GroupMember),
                                       value(0)
/******************************************************************************/
{;}
/******************************************************************************/


/******************************************************************************/
DigitalRadioButton::~DigitalRadioButton()
/******************************************************************************/
{;}
/******************************************************************************/


/******************************************************************************/
int DigitalRadioButton::Get()
/******************************************************************************/
{
  return value;
}
/******************************************************************************/


/******************************************************************************/
void DigitalRadioButton::Update()
/******************************************************************************/
{
  if (radiobutton)
  {
    value=(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobutton)) ==
           (gboolean)TRUE);
  }
}
/******************************************************************************/


/******************************************************************************/
GtkWidget* DigitalRadioButton::setup()
/******************************************************************************/
{
  // Toggle-Button erzeugen und anzeigen
  if(groupMember.valid())
    radiobutton=  gtk_radio_button_new(groupMember->GetGroup());
  else
    radiobutton=  gtk_radio_button_new(NULL);
  gtk_container_add(GTK_CONTAINER(radiobutton),label->GetWidget());
  gtk_widget_show(radiobutton);

  return radiobutton;
}
/******************************************************************************/


/******************************************************************************/
//void DigitalRadioButton::Reset()
/******************************************************************************/
/*{
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(togglebutton),defaultValue);
}*/
/******************************************************************************/

/******************************************************************************/
GSList* DigitalRadioButton::GetGroup()
/******************************************************************************/
{
  return gtk_radio_button_get_group(GTK_RADIO_BUTTON (radiobutton));
}
/******************************************************************************/
