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
#include <math.h>
#include "include/vrule.h"
using namespace sarturis;
using namespace sarturis::gtk;


/******************************************************************************/
VRule::VRule(unsigned int GridY, const std::string& Unit):Ruler(GridY,Unit)
/******************************************************************************/
{
  // Initialisieren
  got_values=false;
  usized=false;
}
/******************************************************************************/


/******************************************************************************/
VRule::~VRule()
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
void VRule::Reset()
/******************************************************************************/
{
  got_values=false;
  Ruler::Reset();
}
/******************************************************************************/


/******************************************************************************/
void VRule::draw()
/******************************************************************************/
{
  // Pixmap schon da
  if (pixmap==NULL) return;

  // Hintergrundrechteck
  gdk_draw_rectangle(pixmap,
                     drawing_area->style->bg_gc[GTK_WIDGET_STATE(drawing_area)],
                     TRUE,
                     0,0,
                     drawing_area->allocation.width,
                     drawing_area->allocation.height);

  // Breite setzen
  if (!usized)
  {
    gtk_widget_set_usize(drawing_area,calc_width(),-1);
    usized=true;
  }
  
  // Begrenzung nach rechts
  gdk_draw_line(pixmap,drawing_area->style->dark_gc[0],
                drawing_area->allocation.width-1,
                drawing_area->allocation.height-1,
                drawing_area->allocation.width-1,0);

  // Grid-Hoehe
  const int gh=(drawing_area->allocation.height-20)/(grid+1);

  // Initialisieren
  char buf[100];
  int th;
  int tw;

  // Pango-Layout
  PangoLayout* pl=gtk_widget_create_pango_layout(drawing_area,0);

  // Skala zeichnen
  for (unsigned int i=0;i<grid+2;++i)
  {
    // Linie zeichnen
    const int p=10+i*gh;
    gdk_draw_line(pixmap,drawing_area->style->fg_gc[0],
                  drawing_area->allocation.width-4,p,
                  drawing_area->allocation.width-1,p);

    // Skalenwert ausrechnen
    double val=lower+(double)(grid+1-i)*(upper-lower)/(double)(grid+1);

    // Null-Rundungsfehler ausgleichen
    if (fabs(val)<pow(10.0,log10(upper-lower)-2.0)) val=0.0;

    // Text setzen und Hoehe bestimmen
    const char* fmt=fabs(val)<1e5 ? "%-1.3f" : "%-1.2e";
    sprintf(buf,fmt,val);
    pango_layout_set_text(pl,buf,-1);
    pango_layout_get_pixel_size(pl,&tw,&th);

    // Text zeichnen
    gdk_draw_layout(pixmap,drawing_area->style->fg_gc[0],
                    drawing_area->allocation.width-tw-6,p-th/2,pl);
  }

  // Masseinheit - Text setzen
  std::string m="<i>["+unit+"]</i>";
  pango_layout_set_markup(pl,m.c_str(),-1);

  // Masseinheit - Text rendern
  pango_layout_get_pixel_size(pl,&tw,&th);
  gdk_draw_layout(pixmap,drawing_area->style->fg_gc[0],
                  drawing_area->allocation.width-tw-10,10+(gh-th)/2,pl);

  // Pango-Layout freigeben
  g_object_unref(pl);
}
/******************************************************************************/


/******************************************************************************/
unsigned int VRule::calc_width()
/******************************************************************************/
{
  // Initialisieren
  char buf[100];
  int w=0;
  int maxw=0;

  // PangoLayout
  PangoLayout* pl=gtk_widget_create_pango_layout(drawing_area,0);

  // Skalenwerte 
  for (unsigned int i=0;i<grid+2;++i)
  {
    // Skalenwert ausrechnen
    double val=lower+(double)(grid+1-i)*(upper-lower)/(double)(grid+1);

    // Null-Rundungsfehler ausgleichen
    if (fabs(val)<pow(10.0,log10(upper-lower)-2.0)) val=0.0;

    // Textbreite
    sprintf(buf,"%-1.3f",val);
    pango_layout_set_text(pl,buf,-1);
    pango_layout_get_pixel_size(pl,&w,0);

    // neues Maximum
    if (w>maxw) maxw=w;
  }

  // Maßeinheit
  std::string m="<i>["+unit+"]</i>";
  pango_layout_set_text(pl,m.c_str(),-1);
  pango_layout_get_pixel_size(pl,&w,0);
  if (w>maxw) maxw=w;

  // Pango-Layout freigeben und return
  g_object_unref(pl);
  return maxw+10;
}
/******************************************************************************/


/******************************************************************************/
bool VRule::fit_to_value(double Value)
/******************************************************************************/
{
  // Initialisieren
  bool changed=false;

  // Beim ersten mal, min und max initialisieren
  if (!got_values)
  {
    min=Value;
    max=Value;
    changed=true;
    got_values=true;
  }
  else  // min und max sind gesetzt, Bereich pruefen
  {
    if (Value<min)
    {
      min=Value;
      changed=true;
    }
    if (Value>max)
    {
      max=Value;
      changed=true;
    }
  }

  // Y-Achse veraendern
  if (changed)
  {
    // Wenn Limits gleich, dann eins davon 0
    double xmin=min;
    double xmax=max;
    if (xmin==xmax)
    {
      if (xmin>0.0) xmin=0.0;   // max positiv
      if (xmax<0.0) xmax=0.0;   // min negativ
    }

    // Setzen
    SetBounds(xmin,xmax);
  }

  return changed;
}
/******************************************************************************/
