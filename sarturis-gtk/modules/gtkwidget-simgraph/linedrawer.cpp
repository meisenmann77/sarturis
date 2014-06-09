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


#include "include/linedrawer.h"
using namespace sarturis;
using namespace sarturis::gtk;


/******************************************************************************/
LineDrawer::LineDrawer(unsigned long Red, unsigned long Green,
                       unsigned long Blue, unsigned char Style,
                       unsigned char Thickness)
/******************************************************************************/
{
  // Linientyp und -dicke
  style=Style;
  thick=Thickness;

  // Farbe
  color.red=(guint16)Red;
  color.green=(guint16)Green;
  color.blue=(guint16)Blue;
  gdk_colormap_alloc_color(gdk_colormap_get_system(),&color,FALSE,TRUE);
}
/******************************************************************************/


/******************************************************************************/
LineDrawer::~LineDrawer()
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
void LineDrawer::attach_to_gc(GdkGC* gc)
/******************************************************************************/
{
  // Farbe
  gdk_gc_set_foreground(gc,&color);

  // Linientyp
  gint8 dash;
  switch (style)
  {
    case 1:
      gdk_gc_set_line_attributes(gc,thick,GDK_LINE_SOLID,GDK_CAP_ROUND,
                                 GDK_JOIN_MITER);
      break;

    case 2:
      gdk_gc_set_line_attributes(gc,thick,GDK_LINE_ON_OFF_DASH,
                                 GDK_CAP_ROUND,GDK_JOIN_MITER);
      dash=3*thick;
      gdk_gc_set_dashes(gc,0,&dash,1);
      break;
    
    case 3:
      gdk_gc_set_line_attributes(gc,thick,GDK_LINE_ON_OFF_DASH,
                                 GDK_CAP_ROUND,GDK_JOIN_MITER);
      dash=thick;
      gdk_gc_set_dashes(gc,0,&dash,1);
      break;

    default :
      gdk_gc_set_line_attributes(gc,thick,GDK_LINE_SOLID,GDK_CAP_ROUND,
                                 GDK_JOIN_MITER);
      break;
  }
}
/******************************************************************************/
