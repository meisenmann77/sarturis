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


#include "include/label.h"
using namespace sarturis::gtk;


/******************************************************************************/
Label::Label(const std::string& Text, bool Markup, bool LineWrap, double XAlign,
             double YAlign):
         text(Text),
         markup(Markup),
         linewrap(LineWrap),
         xalign(XAlign),
         yalign(YAlign)
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
Label::~Label()
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
GtkWidget* Label::setup()
/******************************************************************************/
{
  // Label
  GtkWidget* label=gtk_label_new(text.c_str());

  // Markup und LineWrap
  gtk_label_set_use_markup(GTK_LABEL(label),markup);
  gtk_label_set_line_wrap(GTK_LABEL(label),linewrap);

  // Alignment
  gtk_misc_set_alignment(GTK_MISC(label),(gfloat)xalign,(gfloat)yalign);

  // Anzeigen und return
  gtk_widget_show(label);
  return label;
}
/******************************************************************************/
