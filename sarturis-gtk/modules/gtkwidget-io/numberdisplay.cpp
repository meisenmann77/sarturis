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


#include "sarturis/common/str.h"
#include "include/numberdisplay.h"
using namespace sarturis;
using namespace sarturis::gtk;

/******************************************************************************/
NumberDisplay::NumberDisplay():value(0)
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
NumberDisplay::~NumberDisplay()
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
void NumberDisplay::Set(double V)
/******************************************************************************/
{
  sval=str(V);
}
/******************************************************************************/


/******************************************************************************/
void NumberDisplay::Set(int V)
/******************************************************************************/
{
  sval=str(V);
}
/******************************************************************************/


/******************************************************************************/
void NumberDisplay::Update()
/******************************************************************************/
{
  if (value) gtk_label_set_text(GTK_LABEL(value),sval.c_str());
}
/******************************************************************************/


/******************************************************************************/
GtkWidget* NumberDisplay::setup()
/******************************************************************************/
{
  // Label fuer Wert
  value=gtk_label_new("");
  gtk_widget_show(value);

  return value;
}
/******************************************************************************/
