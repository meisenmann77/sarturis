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


#include <gtk/gtk.h>

#include "sarturis/apps/application.h"
#include "sarturis/gtk/base.h"
using namespace sarturis;
using namespace sarturis::gtk;


/******************************************************************************/
bool Base::init=false;
bool Base::display=false;
/******************************************************************************/


/******************************************************************************/
Base::Base()
/******************************************************************************/
{
  Init();
}
/******************************************************************************/


/******************************************************************************/
void Base::Init()
/******************************************************************************/
{
  // GTK initialisieren
  if (!init)
  {
    // GTK initialisieren
    display=gtk_init_check(0,0) ? true : false;

    // Merken
    init=true;
  }
}
/******************************************************************************/


/******************************************************************************/
bool Base::Display(bool InitIfNot)
/******************************************************************************/
{
  // Evtl. initialisieren
  if (InitIfNot && !init) Init();

  // return
  return display;
}
/******************************************************************************/


/******************************************************************************/
int Base::GtkVersion()
/******************************************************************************/
{
  return 3;
}
/******************************************************************************/


/******************************************************************************/
void Base::InfoDialog(const std::string& Caption, const std::string& Text)
/******************************************************************************/
{
  GtkWidget* dialog=gtk_message_dialog_new(0,GTK_DIALOG_MODAL,
                                           GTK_MESSAGE_INFO,GTK_BUTTONS_OK,
                                           "%s",Text.c_str());
  gtk_window_set_title(GTK_WINDOW(dialog),Caption.c_str());
  gtk_window_set_position(GTK_WINDOW(dialog),GTK_WIN_POS_CENTER);
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);
}
/******************************************************************************/


/******************************************************************************/
void Base::ErrorDialog(const std::string& Caption,
                          const std::string& Message)
/******************************************************************************/
{
  GtkWidget* dialog=gtk_message_dialog_new(0,GTK_DIALOG_MODAL,
                                           GTK_MESSAGE_ERROR,GTK_BUTTONS_OK,
                                           "%s",Message.c_str());
  gtk_window_set_title(GTK_WINDOW(dialog),Caption.c_str());
  gtk_window_set_position(GTK_WINDOW(dialog),GTK_WIN_POS_CENTER);
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);
}
/******************************************************************************/


/******************************************************************************/
std::string Base::LoadDialog(const std::string& Caption,
                                const std::string& Filename)
/******************************************************************************/
{
  // Datei-Dialog anlegen
  GtkWidget* d=gtk_file_chooser_dialog_new(Caption.c_str(),NULL,
                                           GTK_FILE_CHOOSER_ACTION_OPEN,
                                           "_Cancel",
                                           GTK_RESPONSE_CANCEL,
                                           "_Open",
                                           GTK_RESPONSE_ACCEPT,
                                           NULL);
  gtk_window_set_position(GTK_WINDOW(d),GTK_WIN_POS_CENTER);

  // Dialog anzeigen
  if (gtk_dialog_run(GTK_DIALOG(d))==GTK_RESPONSE_ACCEPT)
  {
    gchar* gc = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(d));
    std::string res = "";
    if (gc != NULL) res = gc;
    gtk_widget_destroy(d);
    return res;
  }
  else
  {
    gtk_widget_destroy(d);
    return "";
  }
}
/******************************************************************************/


/******************************************************************************/
std::string Base::SaveDialog(const std::string& Caption,
                                const std::string& Filename)
/******************************************************************************/
{
  // Dialog aufbauen
  GtkWidget* d=gtk_file_chooser_dialog_new(Caption.c_str(),NULL,
                                           GTK_FILE_CHOOSER_ACTION_SAVE,
                                           "_Cancel",
                                           GTK_RESPONSE_CANCEL,
                                           "_Save",
                                           GTK_RESPONSE_ACCEPT,
                                           NULL);
  gtk_file_chooser_set_do_overwrite_confirmation(GTK_FILE_CHOOSER(d),TRUE);
  gtk_window_set_position(GTK_WINDOW(d),GTK_WIN_POS_CENTER);

  // Dialog anzeigen
  if (gtk_dialog_run(GTK_DIALOG(d))==GTK_RESPONSE_ACCEPT)
  {
    gchar* gc = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(d));
    std::string res = "";
    if (gc != NULL) res = gc;
    gtk_widget_destroy(d);
    return res;
  }
  else
  {
    gtk_widget_destroy(d);
    return "";
  }
}
/******************************************************************************/


/******************************************************************************/
GdkPixbuf* Base::Pixbuf(unsigned char* Data, unsigned int Size)
/******************************************************************************/
{
  // Memory-Stream
  GInputStream* str=g_memory_input_stream_new_from_data(Data,Size,NULL);

  // Pixbuf
  return gdk_pixbuf_new_from_stream(str,NULL,NULL);
}
/******************************************************************************/


/******************************************************************************/
std::string Base::DisplayException::ToString()
/******************************************************************************/
{
  return "Kein Display!";
}
/******************************************************************************/


/******************************************************************************/
std::string Base::DisplayException::GetName()
/******************************************************************************/
{
  return "Base::DisplayException";
}
/******************************************************************************/
