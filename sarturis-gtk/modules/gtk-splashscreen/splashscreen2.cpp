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
#include "include/splashscreen2.h"
using namespace sarturis;
using namespace sarturis::gtk;


/******************************************************************************/
SplashScreen::SplashScreen():win(0),pixmap(0),logo(0),gc(0),layout(0)
/******************************************************************************/
{
  // Fenster
  win=gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_decorated(GTK_WINDOW(win),FALSE);
  gtk_window_set_title(GTK_WINDOW(win),"sarturis");
  gtk_window_set_position(GTK_WINDOW(win),GTK_WIN_POS_CENTER_ALWAYS);
  gtk_window_set_type_hint(GTK_WINDOW(win),GDK_WINDOW_TYPE_HINT_SPLASHSCREEN);

  // Image aus Code (SPLASH_IMAGE aus splash_image.h wegen Symbolname)
  GdkPixbuf* pb=Pixbuf(SPLASH_IMAGE,sizeof(SPLASH_IMAGE));

  // Abmessungen
  int width=gdk_pixbuf_get_width(pb);
  int height=gdk_pixbuf_get_height(pb);

  // Pixmap erstellen und Zeichnen
  logo=gdk_pixmap_new(NULL,width,height,24);
  gdk_draw_pixbuf(logo,NULL,pb,0,0,0,0,width,height,GDK_RGB_DITHER_MAX,0,0);

  // Bild
  splash_area=gtk_drawing_area_new();
  gtk_widget_set_size_request(splash_area,width,height);
  gtk_container_add(GTK_CONTAINER(win),splash_area);

  // Signale verbinden
  g_signal_connect(G_OBJECT(splash_area),"configure_event",
                   G_CALLBACK(_configure),this);
  g_signal_connect(G_OBJECT(splash_area),"expose_event",
                   G_CALLBACK(_expose),this);

}
/******************************************************************************/


/******************************************************************************/
SplashScreen::~SplashScreen()
/******************************************************************************/
{
  Hide();
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
  gtk_widget_show_all(win);

  // Event-Handling
  while (gtk_events_pending()) gtk_main_iteration();
}
/******************************************************************************/


/******************************************************************************/
void SplashScreen::Hide()
/******************************************************************************/
{
  // Alles verstecken
  gtk_widget_hide_all(win);

  // Event-Handling
  while (gtk_events_pending()) gtk_main_iteration();

  // Objekte freigeben
  if (layout) g_object_unref(layout);
  if (gc) g_object_unref(gc);  
  if (pixmap) g_object_unref(pixmap);

  // Pointer zuruecksetzen
  layout=0;
  gc=0;
  pixmap=0;
}
/******************************************************************************/


/******************************************************************************/
gint SplashScreen::_configure(GtkWidget* widget, GdkEventConfigure* event,
                              SplashScreen* s)
/******************************************************************************/
{
  // anfangen
  if (widget->window==NULL) return FALSE;

  // Mauszeiger
  gdk_window_set_cursor(widget->window,gdk_cursor_new(GDK_WATCH));

  // first-Flag initialisieren
  bool first=true;

  // Bild freigeben, wenn vorhanden, auch first-Flag setzen
  if (s->pixmap)
  {
    gdk_pixmap_unref(s->pixmap);
    first=false;
  }

  // Neues Bild, mit entsprechender Groesse anlegen 
  s->pixmap=gdk_pixmap_new(widget->window,widget->allocation.width,
                           widget->allocation.height,-1);

  // erster Durchlauf -> Objekte anlegen
  if (first)
  {
    // GC fuer Text
    s->gc=gdk_gc_new(s->pixmap);
    gdk_gc_copy(s->gc,widget->style->black_gc);

    // Farbe fuer Text
    GdkColor color;
    double tcol[]=SPLASH_TEXT_COLOR;
    color.red=(int)(65535.0*tcol[0]);
    color.green=(int)(65535.0*tcol[1]);
    color.blue=(int)(65535.0*tcol[2]);
    gdk_gc_set_rgb_fg_color(s->gc,&color);

    // Text-Layout
    s->layout=gtk_widget_create_pango_layout(widget,0);

    // Textbalken erzeugen und Version auf Logo schreiben
    s->create_textbar(widget);
    s->print_version(widget);
  }

  // Logo zeichnen (Logo ist genau so gross wie Widget)
  gdk_draw_pixmap(s->pixmap,widget->style->bg_gc[GTK_WIDGET_STATE(widget)],
                  s->logo,0,0,0,0,widget->allocation.width,
                  widget->allocation.height);

  // Text zeichnen
  pango_layout_set_text(s->layout,s->text.c_str(),-1);
  gdk_draw_layout(s->pixmap,s->gc,SPLASH_TEXT_POS_X,SPLASH_TEXT_POS_Y,
                  s->layout);

  // return
  return TRUE;
}
/******************************************************************************/


/******************************************************************************/
gint SplashScreen::_expose(GtkWidget* widget, GdkEventExpose* event,
                           SplashScreen* s)
/******************************************************************************/
{
  // abfangen
  if (widget->window==NULL) return FALSE;

  // Bild in Rechteck aus Event zeichnen
  gdk_draw_pixmap(widget->window,widget->style->fg_gc[GTK_WIDGET_STATE(widget)],
                  s->pixmap,event->area.x,event->area.y,event->area.x,
                  event->area.y,event->area.width,event->area.height);

  return TRUE;
}
/******************************************************************************/


/******************************************************************************/
void SplashScreen::create_textbar(GtkWidget* widget)
/******************************************************************************/
{
  // Faktor
  double mul[]=SPLASH_BAR_COLOR_MULTIPLIER;

  // Dummy-Text zum bestimmen der Hoehe
  PangoLayout* pl=gtk_widget_create_pango_layout(widget,0);
  pango_layout_set_text(pl,"ABC",-1);

  // Hoehe
  int textsize;
  pango_layout_get_pixel_size(pl,0,&textsize);

  // Bereich
  int x0=0;
  int x1=widget->allocation.width;
  int y0=SPLASH_TEXT_POS_Y-4;
  int y1=SPLASH_TEXT_POS_Y+textsize+4;

  // y-Bereich evtl. korrigieren (0..Hoehe-1)
  if (y0<0) y0=0;
  if (y1>widget->allocation.height) y1=widget->allocation.height;

  // Hole Rechteck in GdkImage, bestimme Colormap
  GdkImage* img=gdk_drawable_get_image(logo,x0,y0,x1-x0,y1-y0);
  GdkColormap* cmap=gdk_image_get_colormap(img);

  // Dunkle Bild ab
  for (int i=0;i<img->width;++i)
  {
    for (int j=0;j<img->height;++j)
    {
      // Aktuelle Farbe
      GdkColor col;
      gdk_colormap_query_color(cmap,gdk_image_get_pixel(img,i,j),&col);

      // Farbe abdunkeln
      col.pixel=0;
      col.red=textbar_color(col.red,mul[0]);
      col.green=textbar_color(col.green,mul[1]);
      col.blue=textbar_color(col.blue,mul[2]);

      // In Colormap eintragen und dann Pixel setzen
      gdk_colormap_alloc_color(cmap,&col,FALSE,TRUE);
      gdk_image_put_pixel(img,i,j,col.pixel);
    }
  }

  // Zeichne abgedunkeltes Bild
  gdk_draw_image(logo,widget->style->black_gc,img,0,0,x0,y0,x1-x0,y1-y0);

  // Objekte freigeben
  g_object_unref(pl);
  g_object_unref(img);
  g_object_unref(cmap);
}
/******************************************************************************/


/******************************************************************************/
int SplashScreen::textbar_color(int col, double mul)
/******************************************************************************/
{
  int x=(int)((double)col*mul);
  if (x>65535) x=65535;
  return x;
}
/******************************************************************************/


/******************************************************************************/
void SplashScreen::print_version(GtkWidget* widget)
/******************************************************************************/
{
  // Versions-Text
  const std::string v="Sarturis "+VersiontoString(VERSION);
  pango_layout_set_text(layout,v.c_str(),-1);
  gdk_draw_layout(logo,gc,VERSION_TEXT_POS_X,VERSION_TEXT_POS_Y,layout);
}
/******************************************************************************/
