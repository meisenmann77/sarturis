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


#include "include/digitalled.h"
using namespace sarturis;
using namespace sarturis::gtk;


/******************************************************************************/
DigitalLED::DigitalLED(double Red, double Green, double Blue):
              red(Red),
              green(Green),
              blue(Blue),
              value(0),
              old_value(0),
              area(0)
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
DigitalLED::~DigitalLED()
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
void DigitalLED::Set(int V)
/******************************************************************************/
{
  value=V;
}
/******************************************************************************/


/******************************************************************************/
void DigitalLED::Update()
/******************************************************************************/
{
  if ((old_value!=value) && area)
  {
    old_value=value;
    gtk_widget_queue_draw(area);
  }
}
/******************************************************************************/


/******************************************************************************/
GtkWidget* DigitalLED::setup()
/******************************************************************************/
{
  // Drawing-Area
  area=gtk_drawing_area_new();
  gtk_widget_show(area);

  // 12x12 Pixel
  gtk_widget_set_size_request(area,12,12);

  // Callback
  g_signal_connect(G_OBJECT(area),"draw",G_CALLBACK(draw),this);

  // return
  return area;
}
/******************************************************************************/


/******************************************************************************/
gboolean DigitalLED::draw(GtkWidget* widget, cairo_t* cr, DigitalLED* d)
/******************************************************************************/
{
  // Breite und Hoehe
  GtkAllocation alloc;
  gtk_widget_get_allocation(widget,&alloc);
  const unsigned int width=alloc.width;
  const unsigned int height=alloc.height;

  // Kleinste Abmessung ist Durchmesser
  const unsigned int dia=width < height ? width : height;

  // Kreis zeichnen
  if (d->value) cairo_set_source_rgb(cr,d->red,d->green,d->blue);
  else cairo_set_source_rgb(cr,0,0,0);
  cairo_arc(cr,(double)width/2.0,(double)height/2.0,(double)dia/2.0,0.0,-0.1);
  cairo_fill(cr);

  // return
  return TRUE;
}
/******************************************************************************/
