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


#include "include/textedit.h"
using namespace sarturis;
using namespace sarturis::gtk;


/******************************************************************************/
TextEdit::TextEdit(const std::string& Text):edit(0),value(Text)
/******************************************************************************/
{
  if (value=="__EMPTY__") value="";
}
/******************************************************************************/


/******************************************************************************/
TextEdit::~TextEdit()
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
std::string TextEdit::Get()
/******************************************************************************/
{
  return value;
}
/******************************************************************************/


/******************************************************************************/
void TextEdit::Update()
/******************************************************************************/
{
  if (edit) value=gtk_entry_get_text(GTK_ENTRY(edit));
}
/******************************************************************************/


/******************************************************************************/
GtkWidget* TextEdit::setup()
/******************************************************************************/
{
  // Textfeld erzeugen, Text setzen und anzeigen
  edit=gtk_entry_new();
  gtk_entry_set_text(GTK_ENTRY(edit),value.c_str());
  gtk_widget_show(edit);

  return edit;
}
/******************************************************************************/
