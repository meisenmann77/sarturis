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
#include "include/backgroundimage.h"
using namespace sarturis::gtk;


/******************************************************************************/
BackgroundImage::BackgroundImage(sarturis::ref<Widget> Child,
                                 const std::string& Filename):filename(Filename),
                                                              child(Child)
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
BackgroundImage::~BackgroundImage()
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
GtkWidget* BackgroundImage::setup()
/******************************************************************************/
{
  // Eventbox erzeugen, welche das Bild und ein Widget enthaelt
  GtkWidget* bg_image_widget;
  bg_image_widget = gtk_event_box_new();
  gtk_widget_show(bg_image_widget);

#ifdef SARTURIS_GTK2
  GdkPixmap* img_pixmap;
  GdkColormap* colormap = gdk_colormap_new(gdk_visual_get_system(),FALSE);
  img_pixmap = gdk_pixmap_colormap_create_from_xpm(NULL,colormap,NULL,NULL,filename.c_str());

  GtkStyle* style = gtk_style_new();
  style->bg_pixmap[0] = img_pixmap;
  gtk_widget_set_style((GtkWidget*)bg_image_widget,style);
#else

  Logger::Warning("Background images are not supported by sarturis and gtk3");
#endif

  gtk_container_add (GTK_CONTAINER (bg_image_widget), child->GetWidget() );

  return bg_image_widget;
}
/******************************************************************************/
