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


#include "include/drawedwidget.h"
using namespace sarturis;
using namespace sarturis::gtk;


/******************************************************************************/
DrawedWidget::DrawedWidget()
/******************************************************************************/
{
  // Pixmap und Drawing-Area
  pixmap=0;
  drawing_area=gtk_drawing_area_new();

  // Signale verbinden
  g_signal_connect(G_OBJECT(drawing_area),"configure_event",
                   G_CALLBACK(_configure),this);
  g_signal_connect(G_OBJECT(drawing_area),"expose_event",
                   G_CALLBACK(_expose),this);
}
/******************************************************************************/


/******************************************************************************/
DrawedWidget::~DrawedWidget()
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
GtkWidget* DrawedWidget::setup()
/******************************************************************************/
{
  /* Alle Ableitungen von DrawedWidget werden von Diagramm::setup aufgerufen,
     also immmer vom Main-Thread -> GTK-Code kann in Konstruktoren bleiben
     Hier nur Rueckgabe der drawing_area */

  return drawing_area;
}
/******************************************************************************/


/******************************************************************************/
void DrawedWidget::configure()
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
gint DrawedWidget::_configure(GtkWidget *widget, GdkEventConfigure *event,
                              DrawedWidget* dw)
/******************************************************************************/
{
  // anfangen
  if (widget->window==NULL) return FALSE;

  // Bild freigeben, wenn vorhanden
  if (dw->pixmap) gdk_pixmap_unref(dw->pixmap);

  // Neues Bild, mit entsprechender Groesse anlegen 
  dw->pixmap=gdk_pixmap_new(widget->window,widget->allocation.width,
                            widget->allocation.height,-1);

  // Zeichnen und return
  dw->configure();
  dw->draw();
  return TRUE;
}
/******************************************************************************/


/******************************************************************************/
gint DrawedWidget::_expose(GtkWidget* widget, GdkEventExpose* event,
                           DrawedWidget* dw)
/******************************************************************************/
{
  // abfangen
  if (widget->window==NULL) return FALSE;

  // Bild in Rechteck aus Event zeichnen
  gdk_draw_pixmap(widget->window,widget->style->fg_gc[GTK_WIDGET_STATE(widget)],
                  dw->pixmap,event->area.x,event->area.y,event->area.x,
                  event->area.y,event->area.width,event->area.height);

  return TRUE;
}
/******************************************************************************/
