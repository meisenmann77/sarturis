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


#include "include/window.h"
using namespace sarturis::curses;


/******************************************************************************/
Window::Window(unsigned int X, unsigned int Y, unsigned Width,
               unsigned int Height, const std::string& Caption,
               const std::string& BgColor, const std::string& FgColor):
          Widget(X,Y,Width,Height),
          caption(Caption)
/******************************************************************************/
{
  // Farben setzen
  SetColors(BgColor,FgColor);
}
/******************************************************************************/


/******************************************************************************/
Window::~Window()
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
bool Window::CanHaveFocus()
/******************************************************************************/
{
  return false;
}
/******************************************************************************/


/******************************************************************************/
void Window::HandleKey(int Key)
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
void Window::draw_content()
/******************************************************************************/
{
  // Box
  box(win,0,0);
  if (height<2) return;

  // Ausfuellen
  for (unsigned int i=1;i<height-1;++i) mvwhline(win,i,1,' ',width-2);

  // Ueberschrift
  if (caption!="")
  {
    // Zusatzlinie
    mvwaddch(win,2,0,ACS_LTEE);
    mvwhline(win,2,1,ACS_HLINE,width-2);
    mvwaddch(win,2,width-1,ACS_RTEE);

    // Ueberschrift an Breite anpassen
    std::string cap=caption;
    if (cap.length()>width-2) cap=cap.substr(0,width-2);

    // Ueberschrift zeichnen
    mvwprintw(win,1,1+(width-cap.length()-2)/2,"%s",cap.c_str());
  }
}
/******************************************************************************/
