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


#include "sarturis/gtk/compat.h"
#include "include/table.h"
using namespace sarturis::gtk;


/******************************************************************************/
Table::Table(table::_Cell_Vec_ C, bool Homogeneous):config(C),
                                                    homogeneous(Homogeneous)
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
Table::~Table()
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
GtkWidget* Table::setup()
/******************************************************************************/
{
  // Tabelle (0 Zeilen und 0 Spalten - waechst automatisch)
  GtkWidget* table=_gtk_table_new(0,0,homogeneous);
  gtk_widget_show(table);

  // Konfiguriere "Kinder"
  for (unsigned int i=0;i<config.size();++i)
  {
    // AttachOptions;
    int attach_ops=0;
    if (config[i].Expand) attach_ops |= GTK_EXPAND;
    if (config[i].Shrink) attach_ops |= GTK_SHRINK;
    if (config[i].Fill) attach_ops |= GTK_FILL;

    // Hinzufuegen
    _gtk_table_attach(GTK_TABLE(table),config[i].Instance->GetWidget(),
                      config[i].Left,config[i].Right,
                      config[i].Top,config[i].Bottom,
                      (GtkAttachOptions)attach_ops,(GtkAttachOptions)attach_ops,
                      config[i].Padding,config[i].Padding);

    // Verbinde mit Style-Set-Callback
    g_signal_connect(G_OBJECT(config[i].Instance->GetWidget()),"style-set",
                     G_CALLBACK(styleset),table);
  }

  return table;
}
/******************************************************************************/


/******************************************************************************/
void Table::styleset(GtkWidget* widget, GtkStyle* previous_style,
                     GtkWidget* parent)
/******************************************************************************/
{
  gtk_widget_set_style(widget,gtk_widget_get_style(parent));
}
/******************************************************************************/
