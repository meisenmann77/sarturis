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


#include "sarturis/gtk/activewidget.h"
using namespace sarturis::gtk;


/******************************************************************************/
ActiveWidget::ActiveWidget():widget(0)
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
ActiveWidget::~ActiveWidget()
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
GtkWidget* ActiveWidget::GetWidget()
/******************************************************************************/
{
  // widget erzeugen, wenn noch nicht da -> this merken
  if (!widget)
  {
    widget=Widget::GetWidget();
    g_object_set_data(G_OBJECT(widget),"sarturis::gtk::ActiveWidget",this);
  }

  // return
  return widget;
}
/******************************************************************************/


/******************************************************************************/
void ActiveWidget::Update()
/******************************************************************************/
{
  // Wenn widget ein Container ist, dann update fuer alle Kinder aufrufen
  if (GTK_IS_CONTAINER(widget))
  {
    gtk_container_foreach(GTK_CONTAINER(widget),update,0);
  }
}
/******************************************************************************/


/******************************************************************************/
void ActiveWidget::update(GtkWidget* w, gpointer data)
/******************************************************************************/
{
  // Hole ActiveWidget
  ActiveWidget* aw=
    (ActiveWidget*)g_object_get_data(G_OBJECT(w),"sarturis::gtk::ActiveWidget");

  // Wenn vorhanden dann Update
  if (aw) aw->Update();
}
/******************************************************************************/
