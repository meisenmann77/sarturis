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


#include "include/legend.h"
using namespace sarturis;
using namespace sarturis::gtk;


/******************************************************************************/
Legend::Legend(const std::string& Name, unsigned long Red, unsigned long Green,
               unsigned long Blue, unsigned char Style,
               unsigned char Thickness):
          LineDrawer(Red,Green,Blue,Style,Thickness),
          name(Name)
/******************************************************************************/
{
  // Mindesgroesse
  gtk_widget_set_usize(drawing_area,-1,25);
}
/******************************************************************************/


/******************************************************************************/
Legend::~Legend()
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
void Legend::draw()
/******************************************************************************/
{
  // Kein Bild
  if (pixmap==NULL) return;

  // Hintergrundrechteck
  gdk_draw_rectangle(pixmap,
                     drawing_area->style->bg_gc[GTK_WIDGET_STATE(drawing_area)],
                     TRUE,
                     0,0,
                     drawing_area->allocation.width,
                     drawing_area->allocation.height);

  // Begrenzung nach unten
  gdk_draw_line(pixmap,drawing_area->style->dark_gc[0],0,
                drawing_area->allocation.height-1,
                drawing_area->allocation.width-1,
                drawing_area->allocation.height-1);

  // GC und Pango-Layout
  GdkGC* gc=gdk_gc_new(pixmap);
  PangoLayout* pl=gtk_widget_create_pango_layout(drawing_area,0);

  // Text zeichnen, vorher Hoehe bestimmen
  int th=0;
  std::string m="<b>"+name+"</b>";
  pango_layout_set_markup(pl,m.c_str(),-1);
  pango_layout_get_pixel_size(pl,0,&th);
  gdk_draw_layout(pixmap,gc,35,drawing_area->allocation.height/2-th/2,pl);
  
  // Farbe und Stil setzen, Linie zeichnen
  attach_to_gc(gc);
  gdk_draw_line(pixmap,gc,0,drawing_area->allocation.height/2,30,
                drawing_area->allocation.height/2);

  // GC und Pango-Layout zuruecksetzen
  g_object_unref(pl);
  g_object_unref(gc);
}
/******************************************************************************/
