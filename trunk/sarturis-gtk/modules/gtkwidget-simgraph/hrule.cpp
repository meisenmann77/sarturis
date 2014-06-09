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


#ifdef WIN32
  #define _CRT_SECURE_NO_DEPRECATE
#endif
#include "include/hrule.h"
using namespace sarturis;
using namespace sarturis::gtk;


/******************************************************************************/
HRule::HRule(unsigned int GridX, const std::string& Unit):Ruler(GridX,Unit)
/******************************************************************************/
{
  // Initialisieren
  usized=false;
  scroll=(upper-lower)/(double)(GridX+1);
}
/******************************************************************************/


/******************************************************************************/
HRule::~HRule()
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
void HRule::draw()
/******************************************************************************/
{
  // Pixmap schon da
  if (!pixmap) return;

  // Hintergrundrechteck
  gdk_draw_rectangle(pixmap,
                     drawing_area->style->bg_gc[GTK_WIDGET_STATE(drawing_area)],
                     TRUE,
                     0,0,
                     drawing_area->allocation.width,
                     drawing_area->allocation.height);

  // Hoehe setzen
  if (!usized)
  {
    // Texthoehe ermitteln
    int th;
    PangoLayout* pl=gtk_widget_create_pango_layout(drawing_area,0);
    pango_layout_set_text(pl,unit.c_str(),-1);
    pango_layout_get_pixel_size(pl,0,&th);
    g_object_unref(pl);

    // Groesse setzen
    gtk_widget_set_usize(drawing_area,-1,th+10);
    usized=true;
  }

  // Begrenzung nach oben
  gdk_draw_line(pixmap,drawing_area->style->dark_gc[0],0,0,
                drawing_area->allocation.width-1,0);

  // Grid-Weite
  const unsigned int gw=(drawing_area->allocation.width-20)/(grid+1);

  // Pango-Layout
  PangoLayout* pl=gtk_widget_create_pango_layout(drawing_area,0);

  // Initialisieren
  char buf[100];
  int tp=0;
  int tw=0;

  // Skala zeichnen
  for (unsigned int i=0;i<grid+2;++i)
  {
    // Linie
    const int p=10+i*gw;
    gdk_draw_line(pixmap,drawing_area->style->fg_gc[0],p,0,p,3);

    // Text setzen
    sprintf(buf,"%-1.1f",lower+(double)i*(upper-lower)/(double)(grid+1));
    pango_layout_set_text(pl,buf,-1);
    pango_layout_get_pixel_size(pl,&tw,0);

    // Position vom Text
    tp=p-tw/2;

    // Texpos. gegebenenfalls korrigieren
    if (tp<0) tp=2;
    if (tp+tw>drawing_area->allocation.width-3)
    {
      tp=drawing_area->allocation.width-tw-3;
    }

    // Text rendern
    gdk_draw_layout(pixmap,drawing_area->style->fg_gc[0],tp,8,pl);
  }

  // Masseinheit - Text setzen
  std::string m="<i>["+unit+"]</i>";
  pango_layout_set_markup(pl,m.c_str(),-1);

  // Masseinheit - Text rendern
  pango_layout_get_pixel_size(pl,&tw,0);
  gdk_draw_layout(pixmap,drawing_area->style->fg_gc[0],
                  10+grid*gw+(gw-tw)/2,8,pl);

  // Pango-Layout freigeben
  g_object_unref(pl);
}
/******************************************************************************/


/******************************************************************************/
bool HRule::fit_to_value(double Value)
/******************************************************************************/
{
  // Nach rechts scrollen
  if (Value>upper)
  {
    // Wieviel muss gescrollt werden
    unsigned int scroll_cnt=(unsigned int)((Value-upper)/scroll);

    // Grenzen setzen und return
    SetBounds(lower+scroll*(double)(scroll_cnt+1),
              upper+scroll*(double)(scroll_cnt+1));

    // return
    return true;
  }

  // Keine Veraenderung
  return false;
}
/******************************************************************************/
