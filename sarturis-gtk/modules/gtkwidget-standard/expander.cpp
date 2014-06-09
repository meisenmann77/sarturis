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


#include "include/expander.h"
using namespace sarturis::gtk;


/******************************************************************************/
Expander::Expander(sarturis::ref<Widget> Child, const std::string& Caption,
                   bool Expanded):
            caption(Caption),
            expanded(Expanded),
            child(Child)
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
Expander::~Expander()
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
GtkWidget* Expander::setup()
/******************************************************************************/
{
  // Erstellen
  GtkWidget* expander=gtk_expander_new(caption.c_str());

  // Kind zuweisen und evtl. aufklappen
  gtk_container_add(GTK_CONTAINER(expander),child->GetWidget());
  if (expanded) gtk_expander_set_expanded(GTK_EXPANDER(expander),TRUE);

  // Anzeigen und return
  gtk_widget_show(expander);
  return expander;
}
/******************************************************************************/
