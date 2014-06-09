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


/******************************************************************************/
GtkWidget* _gtk_hbox_new(gboolean homogeneous,gint spacing)
/******************************************************************************/
{
  GtkWidget* box=gtk_box_new(GTK_ORIENTATION_HORIZONTAL,spacing);
  gtk_box_set_homogeneous(GTK_BOX(box),homogeneous);
  return box;
}
/******************************************************************************/


/******************************************************************************/
GtkWidget* _gtk_vbox_new(gboolean homogeneous,gint spacing)
/******************************************************************************/
{
  GtkWidget* box=gtk_box_new(GTK_ORIENTATION_VERTICAL,spacing);
  gtk_box_set_homogeneous(GTK_BOX(box),homogeneous);
  return box;
}
/******************************************************************************/


/******************************************************************************/
GtkWidget* _gtk_hpaned_new()
/******************************************************************************/
{
  return gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
}
/******************************************************************************/


/******************************************************************************/
GtkWidget* _gtk_vpaned_new()
/******************************************************************************/
{
  return gtk_paned_new(GTK_ORIENTATION_VERTICAL);
}
/******************************************************************************/


/******************************************************************************/
GtkWidget* _gtk_hscale_new(GtkAdjustment *adjustment)
/******************************************************************************/
{
  return gtk_scale_new(GTK_ORIENTATION_HORIZONTAL,adjustment);
}
/******************************************************************************/


/******************************************************************************/
GtkWidget* _gtk_vscale_new(GtkAdjustment *adjustment)
/******************************************************************************/
{
  return gtk_scale_new(GTK_ORIENTATION_VERTICAL,adjustment);
}
/******************************************************************************/


/******************************************************************************/
GtkWidget* _gtk_hseparator_new()
/******************************************************************************/
{
  return gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
}
/******************************************************************************/


/******************************************************************************/
GtkWidget* _gtk_vseparator_new()
/******************************************************************************/
{
  return gtk_separator_new(GTK_ORIENTATION_VERTICAL);
}
/******************************************************************************/


/******************************************************************************/
GtkWidget* _gtk_table_new(guint rows,guint columns,gboolean homogeneous)
/******************************************************************************/
{
  return gtk_table_new(rows,columns,homogeneous);
}
/******************************************************************************/


/******************************************************************************/
void _gtk_table_attach(GtkTable *table,GtkWidget *child,
                       guint left_attach,guint right_attach,
                       guint top_attach,guint bottom_attach,
                       GtkAttachOptions xoptions,GtkAttachOptions yoptions,
                       guint xpadding,guint ypadding)
/******************************************************************************/
{
  gtk_table_attach(table,child,left_attach,right_attach,top_attach,
                   bottom_attach,xoptions,yoptions,xpadding,ypadding);
}
/******************************************************************************/


/******************************************************************************/
void _gtk_table_set_row_spacings(GtkTable *table,guint spacing)
/******************************************************************************/
{
  gtk_table_set_row_spacings(table,spacing);
}
/******************************************************************************/


/******************************************************************************/
void _gtk_table_set_col_spacings(GtkTable *table,guint spacing)
/******************************************************************************/
{
  gtk_table_set_col_spacings(table,spacing);
}
/******************************************************************************/

