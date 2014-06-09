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


#include "include/usize.h"
using namespace sarturis::gtk;


/******************************************************************************/
USize::USize(sarturis::ref<Widget> C, int W, int H):w(W),h(H),c(C)
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
USize::~USize()
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
void USize::Update()
/******************************************************************************/
{
  // Test, ob Child ein ActiveWidget ist
  sarturis::ref<ActiveWidget> a=c.as<ActiveWidget>();
  if (a.valid()) a->Update();
}
/******************************************************************************/


/******************************************************************************/
GtkWidget* USize::setup()
/******************************************************************************/
{
  // Child
  GtkWidget* widget=c->GetWidget();

  // Groesse setzen und return
  gtk_widget_set_size_request(widget,w,h);
  return widget;
}
/******************************************************************************/
