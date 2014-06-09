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


/*
 * DO NOT EDIT THIS FILE - it is generated by Glade.
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#ifndef WIN32
  #include <unistd.h>
#endif
#include <string.h>
#include <stdio.h>

#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>

#include "include/glade.h"
#include "sarturis/gtk/compat.h"

#define GLADE_HOOKUP_OBJECT(component,widget,name) \
  g_object_set_data_full (G_OBJECT (component), name, \
    gtk_widget_ref (widget), (GDestroyNotify) gtk_widget_unref)

#define GLADE_HOOKUP_OBJECT_NO_REF(component,widget,name) \
  g_object_set_data (G_OBJECT (component), name, widget)

GtkWidget*
create_errordialog (void)
{
  GtkWidget *errordialog;
  GtkWidget *dialog_vbox1;
  GtkWidget *hbox2;
  GtkWidget *image1;
  GtkWidget *vbox2;
  GtkWidget *label4;
  GtkWidget *la_main;
  GtkWidget *ex_source;
  GtkWidget *scrolledwindow2;
  GtkWidget *tv_source;
  GtkWidget *label11;
  GtkWidget *ex_logging;
  GtkWidget *vbox1;
  GtkWidget *scrolledwindow1;
  GtkWidget *tv_logging;
  GtkWidget *hbox1;
  GtkWidget *hbox3;
  GtkWidget *cb_info;
  GtkWidget *cb_warning;
  GtkWidget *cb_error;
  GtkWidget *btn_save;
  GtkWidget *alignment1;
  GtkWidget *hbox4;
  GtkWidget *image2;
  GtkWidget *label3;
  GtkWidget *label6;
  GtkWidget *dialog_action_area1;
  GtkWidget *btn_ok;

  errordialog = gtk_dialog_new ();
  gtk_window_set_title (GTK_WINDOW (errordialog), "dialog1");
  gtk_window_set_type_hint (GTK_WINDOW (errordialog), GDK_WINDOW_TYPE_HINT_DIALOG);

  dialog_vbox1 = gtk_dialog_get_content_area( GTK_DIALOG (errordialog));
  gtk_widget_show (dialog_vbox1);

  hbox2 = _gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox2);
  gtk_box_pack_start (GTK_BOX (dialog_vbox1), hbox2, TRUE, TRUE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (hbox2), 5);

  image1 = gtk_image_new_from_icon_name ("gtk-dialog-error", GTK_ICON_SIZE_DIALOG);
  gtk_widget_show (image1);
  gtk_box_pack_start (GTK_BOX (hbox2), image1, FALSE, TRUE, 5);

  vbox2 = _gtk_vbox_new (FALSE, 5);
  gtk_widget_show (vbox2);
  gtk_box_pack_start (GTK_BOX (hbox2), vbox2, TRUE, TRUE, 5);

  label4 = gtk_label_new ("<b>Fehlermeldung</b>");
  gtk_widget_show (label4);
  gtk_box_pack_start (GTK_BOX (vbox2), label4, FALSE, FALSE, 5);
  gtk_label_set_use_markup (GTK_LABEL (label4), TRUE);
  gtk_misc_set_alignment (GTK_MISC (label4), 0, 0.5);

  la_main = gtk_label_new ("label5");
  gtk_widget_show (la_main);
  gtk_box_pack_start (GTK_BOX (vbox2), la_main, FALSE, FALSE, 5);
  gtk_misc_set_alignment (GTK_MISC (la_main), 0, 0.5);

  ex_source = gtk_expander_new (NULL);
  gtk_widget_show (ex_source);
  gtk_box_pack_start (GTK_BOX (vbox2), ex_source, TRUE, TRUE, 0);

  scrolledwindow2 = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_show (scrolledwindow2);
  gtk_container_add (GTK_CONTAINER (ex_source), scrolledwindow2);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolledwindow2), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
  gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (scrolledwindow2), GTK_SHADOW_IN);

  tv_source = gtk_tree_view_new ();
  gtk_widget_show (tv_source);
  gtk_container_add (GTK_CONTAINER (scrolledwindow2), tv_source);
  gtk_tree_view_set_headers_visible (GTK_TREE_VIEW (tv_source), FALSE);

  label11 = gtk_label_new ("<b>Fehlerquelle</b>");
  gtk_widget_show (label11);
  gtk_expander_set_label_widget (GTK_EXPANDER (ex_source), label11);
  gtk_label_set_use_markup (GTK_LABEL (label11), TRUE);

  ex_logging = gtk_expander_new (NULL);
  gtk_widget_show (ex_logging);
  gtk_box_pack_start (GTK_BOX (vbox2), ex_logging, TRUE, TRUE, 0);

  vbox1 = _gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox1);
  gtk_container_add (GTK_CONTAINER (ex_logging), vbox1);
  gtk_container_set_border_width (GTK_CONTAINER (vbox1), 5);

  scrolledwindow1 = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_show (scrolledwindow1);
  gtk_box_pack_start (GTK_BOX (vbox1), scrolledwindow1, TRUE, TRUE, 0);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolledwindow1), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
  gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (scrolledwindow1), GTK_SHADOW_IN);

  tv_logging = gtk_tree_view_new ();
  gtk_widget_show (tv_logging);
  gtk_container_add (GTK_CONTAINER (scrolledwindow1), tv_logging);
  gtk_tree_view_set_headers_visible (GTK_TREE_VIEW (tv_logging), FALSE);

  hbox1 = _gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox1);
  gtk_box_pack_start (GTK_BOX (vbox1), hbox1, FALSE, TRUE, 0);

  hbox3 = _gtk_hbox_new (TRUE, 0);
  gtk_widget_show (hbox3);
  gtk_box_pack_start (GTK_BOX (hbox1), hbox3, FALSE, FALSE, 0);

  cb_info = gtk_check_button_new_with_mnemonic ("Info");
  gtk_widget_show (cb_info);
  gtk_box_pack_start (GTK_BOX (hbox3), cb_info, FALSE, FALSE, 0);
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (cb_info), TRUE);

  cb_warning = gtk_check_button_new_with_mnemonic ("Warnung");
  gtk_widget_show (cb_warning);
  gtk_box_pack_start (GTK_BOX (hbox3), cb_warning, FALSE, FALSE, 0);
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (cb_warning), TRUE);

  cb_error = gtk_check_button_new_with_mnemonic ("Fehler");
  gtk_widget_show (cb_error);
  gtk_box_pack_start (GTK_BOX (hbox3), cb_error, FALSE, FALSE, 0);
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (cb_error), TRUE);

  btn_save = gtk_button_new ();
  gtk_widget_show (btn_save);
  gtk_box_pack_end (GTK_BOX (hbox1), btn_save, FALSE, FALSE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (btn_save), 5);

  alignment1 = gtk_alignment_new (0.5, 0.5, 0, 0);
  gtk_widget_show (alignment1);
  gtk_container_add (GTK_CONTAINER (btn_save), alignment1);

  hbox4 = _gtk_hbox_new (FALSE, 2);
  gtk_widget_show (hbox4);
  gtk_container_add (GTK_CONTAINER (alignment1), hbox4);

  image2 = gtk_image_new_from_stock ("gtk-floppy", GTK_ICON_SIZE_BUTTON);
  gtk_widget_show (image2);
  gtk_box_pack_start (GTK_BOX (hbox4), image2, FALSE, FALSE, 0);

  label3 = gtk_label_new_with_mnemonic ("Speichern");
  gtk_widget_show (label3);
  gtk_box_pack_start (GTK_BOX (hbox4), label3, FALSE, FALSE, 0);

  label6 = gtk_label_new ("<b>Logging</b>");
  gtk_widget_show (label6);
  gtk_expander_set_label_widget (GTK_EXPANDER (ex_logging), label6);
  gtk_label_set_use_markup (GTK_LABEL (label6), TRUE);

  dialog_action_area1 =gtk_dialog_get_action_area (GTK_DIALOG (errordialog));
  gtk_widget_show (dialog_action_area1);
  gtk_button_box_set_layout (GTK_BUTTON_BOX (dialog_action_area1), GTK_BUTTONBOX_END);

  btn_ok = gtk_button_new_from_stock ("gtk-ok");
  gtk_widget_show (btn_ok);
  gtk_dialog_add_action_widget (GTK_DIALOG (errordialog), btn_ok, GTK_RESPONSE_OK);
//  GTK_WIDGET_SET_FLAGS (btn_ok, GTK_CAN_DEFAULT);

  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (errordialog, errordialog, "errordialog");
  GLADE_HOOKUP_OBJECT_NO_REF (errordialog, dialog_vbox1, "dialog_vbox1");
  GLADE_HOOKUP_OBJECT_NO_REF (errordialog, hbox2, "hbox2");
  GLADE_HOOKUP_OBJECT_NO_REF (errordialog, image1, "image1");
  GLADE_HOOKUP_OBJECT_NO_REF (errordialog, vbox2, "vbox2");
  GLADE_HOOKUP_OBJECT_NO_REF (errordialog, label4, "label4");
  GLADE_HOOKUP_OBJECT_NO_REF (errordialog, la_main, "la_main");
  GLADE_HOOKUP_OBJECT_NO_REF (errordialog, ex_source, "ex_source");
  GLADE_HOOKUP_OBJECT_NO_REF (errordialog, scrolledwindow2, "scrolledwindow2");
  GLADE_HOOKUP_OBJECT_NO_REF (errordialog, tv_source, "tv_source");
  GLADE_HOOKUP_OBJECT_NO_REF (errordialog, label11, "label11");
  GLADE_HOOKUP_OBJECT_NO_REF (errordialog, ex_logging, "ex_logging");
  GLADE_HOOKUP_OBJECT_NO_REF (errordialog, vbox1, "vbox1");
  GLADE_HOOKUP_OBJECT_NO_REF (errordialog, scrolledwindow1, "scrolledwindow1");
  GLADE_HOOKUP_OBJECT_NO_REF (errordialog, tv_logging, "tv_logging");
  GLADE_HOOKUP_OBJECT_NO_REF (errordialog, hbox1, "hbox1");
  GLADE_HOOKUP_OBJECT_NO_REF (errordialog, hbox3, "hbox3");
  GLADE_HOOKUP_OBJECT_NO_REF (errordialog, cb_info, "cb_info");
  GLADE_HOOKUP_OBJECT_NO_REF (errordialog, cb_warning, "cb_warning");
  GLADE_HOOKUP_OBJECT_NO_REF (errordialog, cb_error, "cb_error");
  GLADE_HOOKUP_OBJECT_NO_REF (errordialog, btn_save, "btn_save");
  GLADE_HOOKUP_OBJECT_NO_REF (errordialog, alignment1, "alignment1");
  GLADE_HOOKUP_OBJECT_NO_REF (errordialog, hbox4, "hbox4");
  GLADE_HOOKUP_OBJECT_NO_REF (errordialog, image2, "image2");
  GLADE_HOOKUP_OBJECT_NO_REF (errordialog, label3, "label3");
  GLADE_HOOKUP_OBJECT_NO_REF (errordialog, label6, "label6");
  GLADE_HOOKUP_OBJECT_NO_REF (errordialog, dialog_action_area1, "dialog_action_area1");
  GLADE_HOOKUP_OBJECT_NO_REF (errordialog, btn_ok, "btn_ok");

  return errordialog;
}

