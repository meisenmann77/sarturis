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


#ifndef __SARTURIS_GTK_COMPAT__
#define __SARTURIS_GTK_COMPAT__

#include <gtk/gtk.h>
#include "export.h"

#ifdef __cplusplus
extern "C" {
#endif

DLLIMPORT GtkWidget* _gtk_hbox_new(gboolean homogeneous,gint spacing);
DLLIMPORT GtkWidget* _gtk_vbox_new(gboolean homogeneous,gint spacing);
DLLIMPORT GtkWidget* _gtk_hpaned_new();
DLLIMPORT GtkWidget* _gtk_vpaned_new();
DLLIMPORT GtkWidget* _gtk_hscale_new(GtkAdjustment *adjustment);
DLLIMPORT GtkWidget* _gtk_vscale_new(GtkAdjustment *adjustment);
DLLIMPORT GtkWidget* _gtk_hseparator_new();
DLLIMPORT GtkWidget* _gtk_vseparator_new();
DLLIMPORT GtkWidget* _gtk_table_new(guint rows,guint columns,
                                    gboolean homogeneous);
DLLIMPORT void       _gtk_table_attach(GtkTable *table,GtkWidget *child,
                                       guint left_attach,guint right_attach,
                                       guint top_attach,guint bottom_attach,
                                       GtkAttachOptions xoptions,
                                       GtkAttachOptions yoptions,
                                       guint xpadding,guint ypadding);
DLLIMPORT void       _gtk_table_set_row_spacings(GtkTable *table,guint spacing);
DLLIMPORT void       _gtk_table_set_col_spacings(GtkTable *table,guint spacing);
#ifdef __cplusplus
}
#endif

#endif
