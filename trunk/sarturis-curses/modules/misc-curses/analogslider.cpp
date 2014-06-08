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


#include "include/analogslider.h"
using namespace sarturis::curses;


/******************************************************************************/
AnalogSlider::AnalogSlider(unsigned int X, unsigned int Y, unsigned int Width,
                           double Min, double Max, double Value,
                           bool ShowValue, const std::string& BgColor,
                           const std::string& FgColor):
                BarDrawer(X,Y,Width,Min,Max,Value,ShowValue)
/******************************************************************************/
{
  // Farben setzen
  SetColors(BgColor,FgColor);
}
/******************************************************************************/


/******************************************************************************/
AnalogSlider::~AnalogSlider()
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
double AnalogSlider::Get()
/******************************************************************************/
{
  return value;
}
/******************************************************************************/


/******************************************************************************/
bool AnalogSlider::CanHaveFocus()
/******************************************************************************/
{
  return true;
}
/******************************************************************************/


/******************************************************************************/
void AnalogSlider::HandleKey(int Key)
/******************************************************************************/
{
  // Je nach Taste erhoehen oder reduzieren
  switch(Key)
  {
    case KEY_LEFT:  value-=0.1; if (value<min) value=min; break;
    case KEY_RIGHT: value+=0.1; if (value>max) value=max; break;
  }

  // Neuzeichnen
  Draw();
}
/******************************************************************************/


/******************************************************************************/
void AnalogSlider::draw_content()
/******************************************************************************/
{
  // Zeichnen
  BarDrawer::draw_content();

  // Cursor positionieren
  unsigned int p=(unsigned int)((value-min)/(max-min)*(double)width+0.5);
  if (p>=width) p=width-1;
  wmove(win,0,p);
}
/******************************************************************************/
