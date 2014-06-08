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


#include <math.h>
#include <sarturis/common/str.h>
#include <sarturis/curses/color.h>
#include "include/bardrawer.h"
using namespace sarturis::curses;

#define EPS 1e-6


/******************************************************************************/
BarDrawer::BarDrawer(unsigned int X, unsigned int Y, unsigned int Width,
                     double Min, double Max, double Value, bool ShowValue):
             Widget(X,Y,Width,1),
             min(Min),
             max(Max),
             showvalue(ShowValue),
             value(Value)
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
BarDrawer::~BarDrawer()
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
void BarDrawer::draw_content()
/******************************************************************************/
{
  // Position
  const unsigned int p=(unsigned int)((value-min)/(max-min)*(double)width+0.5);

  // Zwei Teile des Bars
  mvwhline(win,0,0,A_REVERSE | ' ',p);  // "Gefuellter" Teil
  mvwhline(win,0,p,' ',width-p);        // Rest

  // Wert
  if (showvalue)
  {
    // Wert in String umwandeln - "0" und in Breite einpassen
    std::string sval=str(value);
    if (fabs(value)<EPS) sval="0";
    if (sval.length()>width) sval=sval.substr(0,width);

    // Start-Pos und End-Pos
    const unsigned int cp=(width-sval.length())/2;
    const unsigned int ce=cp+sval.length();

    // Teil-Strings und Positionen
    std::string sback;  unsigned int back_pos=0;
    std::string sfill;  unsigned int fill_pos=0;

    // Komplett auf Hintergrund
    if (p<=cp)
    {
      sback=sval;
      back_pos=cp;
    }
    // Komplett auf Fuellung
    else if (p>=ce)
    {
      sfill=sval;
      fill_pos=cp;
    }
    // cp < p < ce - Teilen
    else
    {
      sfill=sval.substr(0,p-cp);     // Linker Teil, auf Fuellung
      fill_pos=cp;
      sback=sval.substr(p-cp,ce-p);  // Rechter Teil, auf Hintergrund
      back_pos=p;
    }

    // Auf Hintergrund
    if (sback!="") mvwprintw(win,0,back_pos,sback.c_str());

    // Auf Fuellung (invertiert)
    if (cp<p)
    {
      wattron(win,COLOR_PAIR(Color::Invert(color)));
      mvwprintw(win,0,fill_pos,sfill.c_str());
      wattroff(win,COLOR_PAIR(Color::Invert(color)));
    }
  }
}
/******************************************************************************/
