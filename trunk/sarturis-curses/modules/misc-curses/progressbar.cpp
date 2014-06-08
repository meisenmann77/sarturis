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


#include "include/progressbar.h"
using namespace sarturis::curses;


/******************************************************************************/
ProgressBar::ProgressBar(unsigned int X, unsigned int Y, unsigned int Width,
                         double Min, double Max, double Value, bool ShowValue,
                         const std::string& BgColor,
                         const std::string& FgColor):
               BarDrawer(X,Y,Width,Min,Max,Value,ShowValue)
/******************************************************************************/
{
  // Farben setzen
  SetColors(BgColor,FgColor);
}
/******************************************************************************/


/******************************************************************************/
ProgressBar::~ProgressBar()
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
void ProgressBar::Set(double V)
/******************************************************************************/
{
  // Uenbernehmen
  value=V;

  // Limits
  if (value>max) (value=max);
  if (value<min) (value=min);
}
/******************************************************************************/


/******************************************************************************/
void ProgressBar::Update()
/******************************************************************************/
{
  // Zeichnen
  Draw();
}
/******************************************************************************/


/******************************************************************************/
bool ProgressBar::CanHaveFocus()
/******************************************************************************/
{
  return false;
}
/******************************************************************************/


/******************************************************************************/
void ProgressBar::HandleKey(int Key)
/******************************************************************************/
{
}
/******************************************************************************/
