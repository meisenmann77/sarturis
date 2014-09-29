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


#include "include/combobox.h"
using namespace sarturis;
using namespace sarturis::gtk;


/******************************************************************************/
ComboBox::ComboBox(const combobox::_Item_Vec_& c_items):_comboBox(0),
                                                        _items(c_items),
                                                        _value("")
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
ComboBox::~ComboBox()
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
std::string ComboBox::Get()
/******************************************************************************/
{
  return _value;
}
/******************************************************************************/


/******************************************************************************/
void ComboBox::Update()
/******************************************************************************/
{
  if (_comboBox)
  {
    _value = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(_comboBox));
  }
}
/******************************************************************************/


/******************************************************************************/
GtkWidget* ComboBox::setup()
/******************************************************************************/
{
  // ComboBox erzeugen
  _comboBox = gtk_combo_box_text_new_with_entry ();

	// items setzen
	for(unsigned int i=0; i < _items.size(); i++)
	{
	  gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (_comboBox),
	                                  _items[i].Text.c_str());
	}

	// ComboBox anzeigen
  gtk_widget_show(_comboBox);

  return _comboBox;
}
/******************************************************************************/
