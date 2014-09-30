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
#include "include/valuewindow.h"
using namespace sarturis;
using namespace sarturis::gtk;


/******************************************************************************/
ValueWindow::ValueWindow(const std::string& Font)
/******************************************************************************/
{
  // Fenster
  window=gtk_window_new(GTK_WINDOW_POPUP);

  // Label
  label=gtk_label_new("Label 1");
  gtk_widget_show(label);
  gtk_container_add(GTK_CONTAINER(window),label);

  // Font
  PangoFontDescription* pfd=pango_font_description_from_string(Font.c_str());
  gtk_widget_modify_font(label,pfd);
  pango_font_description_free(pfd);
}
/******************************************************************************/


/******************************************************************************/
ValueWindow::~ValueWindow()
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
void ValueWindow::Show()
/******************************************************************************/
{
  gtk_widget_show(window);
}
/******************************************************************************/


/******************************************************************************/
void ValueWindow::Hide()
/******************************************************************************/
{
  gtk_widget_hide(window);
}
/******************************************************************************/


/******************************************************************************/
void ValueWindow::SetPosition(unsigned int X, unsigned int Y)
/******************************************************************************/
{
  gtk_window_move(GTK_WINDOW(window),X,Y);
}
/******************************************************************************/


/******************************************************************************/
void ValueWindow::SetValues(double X, double Y)
/******************************************************************************/
{
  char buf[100];
  const char* fmt=fabs(Y)<1e5 ? "%-1.3f : %-1.3f" : "%-1.3f : %-1.2e";
  sprintf(buf,fmt,X,Y);
  gtk_label_set_text(GTK_LABEL(label),buf);
}
/******************************************************************************/
