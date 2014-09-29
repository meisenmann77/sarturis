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


#include "include/scrolledwindow.h"
using namespace sarturis::gtk;


/******************************************************************************/
ScrolledWindow::ScrolledWindow(sarturis::ref<Widget> Child, bool ScrollX,
                               bool ScrollY):
                  scrollx(ScrollX),
                  scrolly(ScrollY),
                  child(Child)
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
ScrolledWindow::~ScrolledWindow()
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
GtkWidget* ScrolledWindow::setup()
/******************************************************************************/
{
  // Policies
  const int px=scrollx ? GTK_POLICY_AUTOMATIC : GTK_POLICY_NEVER;
  const int py=scrolly ? GTK_POLICY_AUTOMATIC : GTK_POLICY_NEVER;

  // Erzeuge Scrolled-Window
  GtkWidget* wnd=gtk_scrolled_window_new(0,0);
  gtk_widget_show(wnd);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(wnd),
                                 (GtkPolicyType)px,(GtkPolicyType)py);

  // Fuege Child hinzu
  gtk_container_add(GTK_CONTAINER(wnd),child->GetWidget());

  // Verbinde mit Style-Set-Callback
  g_signal_connect(G_OBJECT(child->GetWidget()),"style-set",
                   G_CALLBACK(styleset),wnd);

  return wnd;
}
/******************************************************************************/


/******************************************************************************/
void ScrolledWindow::styleset(GtkWidget* widget, GtkStyle* previous_style,
                              GtkWidget* parent)
/******************************************************************************/
{
  gtk_widget_set_style(widget,gtk_widget_get_style(parent));
}
/******************************************************************************/
