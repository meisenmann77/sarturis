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


#include <ncurses.h>
#include "sarturis/curses/color.h"
using namespace sarturis::curses;


/******************************************************************************/
static int color[]={COLOR_WHITE,COLOR_RED,COLOR_GREEN,COLOR_YELLOW,
                    COLOR_BLUE,COLOR_MAGENTA,COLOR_CYAN,COLOR_BLACK};
static int limit=0;
/******************************************************************************/


/******************************************************************************/
void Color::Init()
/******************************************************************************/
{
  // Werden Farben unterstuetzt
  if (has_colors())
  {
    // Farben aktivieren und limit initialisieren
    start_color();
    limit=(COLORS < 8) ? COLORS : 8;

    // Farbkombinationen anlegnen
    int pair=1;
    for (int fg=0;fg<limit;++fg)
    {
      for (int bg=0;bg<limit;++bg)
      {
        init_pair(pair++,color[fg],color[bg]);
      }
    }

  }
}
/******************************************************************************/


/******************************************************************************/
int Color::Get(int Fg, int Bg)
/******************************************************************************/
{
  int id_fg=-1;
  int id_bg=-1;

  for (int i=0;i<limit;++i)
  {
    if (Fg==color[i]) id_fg=i;
    if (Bg==color[i]) id_bg=i;
  }

  return id_fg*limit+id_bg+1;
}
/******************************************************************************/


/******************************************************************************/
int Color::Invert(int Color)
/******************************************************************************/
{
  Color--;
  return (Color % limit)*limit+Color/limit+1;
}
/******************************************************************************/
