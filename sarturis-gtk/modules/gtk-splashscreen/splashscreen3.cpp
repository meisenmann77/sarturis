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


#include "version.h"
#include "splash_image.h"
#include "include/splashscreen3.h"
using namespace sarturis;
using namespace sarturis::gtk;


/******************************************************************************/
SplashScreen::SplashScreen():win(0),image(0),textbar(0)
/******************************************************************************/
{
  // Fenster
  win=gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_decorated(GTK_WINDOW(win),FALSE);
  gtk_window_set_title(GTK_WINDOW(win),"sarturis");
  gtk_window_set_position(GTK_WINDOW(win),GTK_WIN_POS_CENTER_ALWAYS);
  gtk_window_set_type_hint(GTK_WINDOW(win),GDK_WINDOW_TYPE_HINT_SPLASHSCREEN);

  // Image aus Code (SPLASH_IMAGE aus splash_image.h wegen Symbolname)
  image=Pixbuf(SPLASH_IMAGE,sizeof(SPLASH_IMAGE));

  // Abmessungen
  int width=gdk_pixbuf_get_width(image);
  int height=gdk_pixbuf_get_height(image);

  // Image mit Textbalken (Texthoehe merken)
  double mul[]=SPLASH_BAR_COLOR_MULTIPLIER;
  cairo_text_extents_t extents;
  textbar=cairo_image_surface_create(CAIRO_FORMAT_ARGB32,width,height);
  cairo_t* cr=cairo_create(textbar);
  cairo_select_font_face(cr,"Sans",CAIRO_FONT_SLANT_NORMAL,
                         CAIRO_FONT_WEIGHT_NORMAL);
  cairo_set_font_size(cr,(double)SPLASH_TEXT_SIZE);
  cairo_text_extents(cr,"ABC",&extents);
  cairo_set_source_rgba(cr,0.0,0.0,0.0,mul[0]);
  cairo_rectangle(cr,0.0,(double)(SPLASH_TEXT_POS_Y-4),
                  width,(double)(SPLASH_TEXT_POS_Y+4)+extents.height);
  cairo_fill(cr);
  cairo_destroy(cr);
  th=extents.height;

  // Bild
  splash_area=gtk_drawing_area_new();
  gtk_widget_set_size_request(splash_area,width,height);
  gtk_widget_show(splash_area);
  gtk_container_add(GTK_CONTAINER(win),splash_area);
  g_signal_connect(G_OBJECT(splash_area),"draw",G_CALLBACK(draw),this);
}
/******************************************************************************/


/******************************************************************************/
SplashScreen::~SplashScreen()
/******************************************************************************/
{
  // Aufraeumen
  g_object_unref(image);
  image=0;
  cairo_surface_destroy(textbar);
  textbar=0;

  // Fenster ausblenden
  gtk_widget_hide(win);
}
/******************************************************************************/


/******************************************************************************/
void SplashScreen::Message(const std::string& Msg)
/******************************************************************************/
{
  // Test setzen
  text=Msg;

  // Neuzeichnen
  gtk_widget_queue_resize(splash_area);

  // Event-Handling
  while (gtk_events_pending()) gtk_main_iteration();
}
/******************************************************************************/


/******************************************************************************/
void SplashScreen::Show()
/******************************************************************************/
{
  // Anzeigen
  gtk_widget_show(win);

  // Event-Handling
  while (gtk_events_pending()) gtk_main_iteration();
}
/******************************************************************************/


/******************************************************************************/
void SplashScreen::Hide()
/******************************************************************************/
{
  // Alles verstecken
  gtk_widget_hide(win);

  // Event-Handling
  while (gtk_events_pending()) gtk_main_iteration();
}
/******************************************************************************/


/******************************************************************************/
gboolean SplashScreen::draw(GtkWidget* widget, cairo_t* cr, SplashScreen* s)
/******************************************************************************/
{
  // Absichern
  if (!s->image) return FALSE;
  if (!s->textbar) return FALSE;
  
  // Zeichne Bild
  gdk_cairo_set_source_pixbuf(cr,s->image,0.0,0.0);
  cairo_paint(cr);

  // Zeichne Textbalken
  cairo_set_source_surface(cr,s->textbar,0.0,0.0);
  cairo_paint(cr);

  // Zeichne Text
  double col[]=SPLASH_TEXT_COLOR;
  cairo_set_source_rgba(cr,col[0],col[1],col[2],1.0);
  cairo_select_font_face(cr,"Sans",CAIRO_FONT_SLANT_NORMAL,
                         CAIRO_FONT_WEIGHT_NORMAL);
  cairo_set_font_size(cr,(double)SPLASH_TEXT_SIZE);
  cairo_move_to(cr,(double)SPLASH_TEXT_POS_X,
                (double)SPLASH_TEXT_POS_Y+s->th+4.0);
  cairo_show_text(cr,s->text.c_str());
  
  // return
  return TRUE;
}
/******************************************************************************/
