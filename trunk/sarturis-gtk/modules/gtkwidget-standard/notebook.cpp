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


#include "include/notebook.h"
using namespace sarturis::gtk;


/******************************************************************************/
Notebook::Notebook(notebook::_Page_Vec_ C, unsigned int Active):
            config(C),
            active(Active)
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
Notebook::~Notebook()
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
GtkWidget* Notebook::setup()
/******************************************************************************/
{
  // Notebook
  GtkWidget* notebook=gtk_notebook_new();
  gtk_widget_show(notebook);

  // Konfiguriere "Kinder"
  for (unsigned int i=0;i<config.size();++i)
  {
    // Ueberschift
    GtkWidget* cap=gtk_label_new(config[i].Caption.c_str());
    gtk_widget_show(cap);

    // Seite
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook),
                             config[i].Instance->GetWidget(),cap);

    // Verbinde mit Style-Set-Callback
    g_signal_connect(G_OBJECT(config[i].Instance->GetWidget()),"style-set",
                     G_CALLBACK(styleset),notebook);
  }

  // Aktive Seite setzen und return
  gtk_notebook_set_current_page(GTK_NOTEBOOK(notebook),active);
  return notebook;
}
/******************************************************************************/


/******************************************************************************/
void Notebook::styleset(GtkWidget* widget, GtkStyle* previous_style,
                        GtkWidget* parent)
/******************************************************************************/
{
  gtk_widget_set_style(widget,gtk_widget_get_style(parent));
}
/******************************************************************************/
