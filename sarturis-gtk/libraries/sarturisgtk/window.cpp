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


#include "sarturis/base/logger.h"
#include "sarturis/common/str.h"
#include "sarturis/apps/application.h"
#include "sarturis/base/generalexception.h"
#include "sarturis/gtk/window.h"
using namespace sarturis;
using namespace sarturis::gtk;


/******************************************************************************/
Window::Window(sarturis::ref<Widget> Child, const std::string& Title,
                       int X, int Y, unsigned int Width, unsigned int Height,
                       unsigned int BorderWidth, bool FullScreen,
                       bool QuitOnClose, bool AllowClose):
          child(Child),
          quitonclose(QuitOnClose),
          allowclose(AllowClose),
          closed(false) 
/******************************************************************************/
{
  // GTK initialisieren -> ConfigReader
  if (!Base::Display(true)) throw Base::DisplayException();

  // Fenster mit Titel
  window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window),Title.c_str());

  // Position
  #ifdef SARTURIS_GTK2
    gtk_widget_set_uposition(window,X,Y);
  #endif

  // Groesse
  if (Width && Height) gtk_widget_set_size_request(window,Width,Height);
  if (FullScreen) gtk_window_fullscreen(GTK_WINDOW(window));

  // BorderWidth
  gtk_container_set_border_width(GTK_CONTAINER(window),BorderWidth);

  // Child
  gtk_container_add(GTK_CONTAINER(window),child->GetWidget());

  // Signal
  g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(delete_event),
                   this);
}
/******************************************************************************/


/******************************************************************************/
Window::~Window()
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
void Window::SetDisplay(const std::string& Display)
/******************************************************************************/
{
  #ifdef WIN32
    // Schade-Schade
    Logger::Warning("Setting the Display is not supported \
                                      by this OS!");
    return;
  #else
    // Display
    GdkDisplay* d=gdk_display_open(Display.c_str());
    if (!d) throw GeneralException("Could not open display "+Display);

    // GdkScreen
    GdkScreen* s=gdk_display_get_default_screen(d);

    // Setzen
    gtk_window_set_screen(GTK_WINDOW(window),s);
  #endif
}
/******************************************************************************/


/******************************************************************************/
void Window::SetScreen(int Screen)
/******************************************************************************/
{
  // aktueller GdkScreen
  GdkScreen* s=gtk_window_get_screen(GTK_WINDOW(window));

  // GdkDisplay
  GdkDisplay* d=gdk_screen_get_display(s);

  // neuer GdkScreen
  GdkScreen* sn=gdk_display_get_screen(d,Screen);

  // Pruefung
  if (!GDK_IS_SCREEN(sn))
    throw GeneralException("Could not find Screen "+str(Screen));

  // setzen
  gtk_window_set_screen(GTK_WINDOW(window),sn);
}
/******************************************************************************/


/******************************************************************************/
void Window::Show() const
/******************************************************************************/
{
  gtk_widget_show(window);
}
/******************************************************************************/


/******************************************************************************/
void Window::Hide() const
/******************************************************************************/
{
  gtk_widget_hide(window);
}
/******************************************************************************/


/******************************************************************************/
bool Window::Close()
/******************************************************************************/
{
  // Nicht erlaubt
  if (!allowclose) return false;

  // Flag setzen
  closed=true;

  // Evtl. beenden - Verzoegern, da evtl. auf Threads gewartet wird und sonst
  // der Windowmanager staendig anbietet die Anwendung zu killen weil keine
  // Reaktion
  if (quitonclose)
  {
    Logger::Info("Quit on Window-close");
    g_timeout_add_full(G_PRIORITY_HIGH,10,(GSourceFunc)do_quit,0,0);

    // Fenster offen lassen, falls Timer noch Aktualisierungen laufen haben
    // den Rest erledigt Window::do_quit
    return false;
  }

  // Fenster kann geschlossen werden
  return true;
}
/******************************************************************************/


/******************************************************************************/
bool Window::Closed() const
/******************************************************************************/
{
  return closed;
}
/******************************************************************************/


/******************************************************************************/
void Window::SetIcon(const guint8* data) const
/******************************************************************************/
{
  GdkPixbuf* pb=gdk_pixbuf_new_from_inline(-1,data,FALSE,NULL);
  gtk_window_set_icon(GTK_WINDOW(window),pb);
}
/******************************************************************************/


/******************************************************************************/
bool Window::SetIcon(const std::string& Filename) const
/******************************************************************************/
{
  if (Filename==".") return false;
  return gtk_window_set_icon_from_file(GTK_WINDOW(window),
                                       Filename.c_str(),0) ? true : false;
}
/******************************************************************************/


/******************************************************************************/
void Window::SetIcon(GdkPixbuf* pb) const
/******************************************************************************/
{
  gtk_window_set_icon(GTK_WINDOW(window),pb);
}
/******************************************************************************/


/******************************************************************************/
void Window::SetTitle(const std::string& Title)
/******************************************************************************/
{
  gtk_window_set_title(GTK_WINDOW(window),Title.c_str());
}
/******************************************************************************/


/******************************************************************************/
void Window::SetSize(unsigned int Width, unsigned int Height)
/******************************************************************************/
{
  if (Width && Height) gtk_widget_set_size_request(window,Width,Height);
}
/******************************************************************************/


/******************************************************************************/
gboolean Window::delete_event(GtkWidget* widget, GdkEvent* event, Window* w)
/******************************************************************************/
{
  return !(w->Close());
}
/******************************************************************************/


/******************************************************************************/
gboolean Window::do_quit(gpointer data)
/******************************************************************************/
{
  Application::Quit();
  return FALSE;
}
/******************************************************************************/
