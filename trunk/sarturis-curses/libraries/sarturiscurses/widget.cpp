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


#include "sarturis/base/generalexception.h"
#include "sarturis/curses/widget.h"
#include "sarturis/curses/color.h"
using namespace sarturis::curses;


/******************************************************************************/
Widget::Widget(unsigned int X, unsigned int Y, unsigned int Width,
               unsigned int Height):
          win(0),
          x(X),y(Y),width(Width),height(Height),
          bg_col(COLOR_BLACK),fg_col(COLOR_WHITE),
          color(Color::Get(fg_col,bg_col)),
          focus(false)
/******************************************************************************/
{
  win=newwin(height,width,y,x);
}
/******************************************************************************/


/******************************************************************************/
Widget::~Widget()
/******************************************************************************/
{
  if (win) delwin(win);
}
/******************************************************************************/


/******************************************************************************/
void Widget::SetBgColor(int Color)
/******************************************************************************/
{
  bg_col=Color;
  color=Color::Get(fg_col,bg_col);
}
/******************************************************************************/


/******************************************************************************/
void Widget::SetFgColor(int Color)
/******************************************************************************/
{
  fg_col=Color;
  color=Color::Get(fg_col,bg_col);
}
/******************************************************************************/


/******************************************************************************/
void Widget::SetColors(const std::string& Bg, const std::string& Fg)
/******************************************************************************/
{
  // Hintergrund
  if (Bg=="White") SetBgColor(COLOR_WHITE);
  else if (Bg=="Red") SetBgColor(COLOR_RED);
  else if (Bg=="Green") SetBgColor(COLOR_GREEN);
  else if (Bg=="Yellow") SetBgColor(COLOR_YELLOW);
  else if (Bg=="Blue") SetBgColor(COLOR_BLUE);
  else if (Bg=="Magenta") SetBgColor(COLOR_MAGENTA);
  else if (Bg=="Cyan") SetBgColor(COLOR_CYAN);
  else if (Bg=="Black") SetBgColor(COLOR_BLACK);
  else throw GeneralException("Unbekannte Farbe "+Bg);

  // Vordergrund
  if (Fg=="White") SetFgColor(COLOR_WHITE);
  else if (Fg=="Red") SetFgColor(COLOR_RED);
  else if (Fg=="Green") SetFgColor(COLOR_GREEN);
  else if (Fg=="Yellow") SetFgColor(COLOR_YELLOW);
  else if (Fg=="Blue") SetFgColor(COLOR_BLUE);
  else if (Fg=="Magenta") SetFgColor(COLOR_MAGENTA);
  else if (Fg=="Cyan") SetFgColor(COLOR_CYAN);
  else if (Fg=="Black") SetFgColor(COLOR_BLACK);
  else throw GeneralException("Unbekannte Farbe "+Fg);
}
/******************************************************************************/


/******************************************************************************/
void Widget::Draw()
/******************************************************************************/
{
  // Farbe an, Zeichnen, Farbe aus
  wattron(win,COLOR_PAIR(color));
  draw_content();
  wattroff(win,COLOR_PAIR(color));

  // Aktualisieren
  wrefresh(win);
}
/******************************************************************************/


/******************************************************************************/
void Widget::SetFocus(bool Focus)
/******************************************************************************/
{
  focus=Focus;
  Draw();
}
/******************************************************************************/


/******************************************************************************/
void Widget::move_by(int x, int y)
/******************************************************************************/
{
  move_to(this->x+x,this->y+y);
}
/******************************************************************************/


/******************************************************************************/
void Widget::move_to(int x, int y)
/******************************************************************************/
{
  // Merken
  this->x=x;
  this->y=y;

  // Bewegen und aktualisieren (Auch Untergrund)
  mvwin(win,y,x);
  wrefresh(win);
}
/******************************************************************************/

