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


#include "include/ruler.h"
using namespace sarturis;
using namespace sarturis::gtk;


/******************************************************************************/
Ruler::Ruler(unsigned int Grid, const std::string& Unit):unit(Unit)
/******************************************************************************/
{
  // Initialisieren
  grid=Grid;
  lower=0.0;
  upper=30.0;
  fitted=0;
}
/******************************************************************************/


/******************************************************************************/
Ruler::~Ruler()
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
void Ruler::SetGrid(unsigned int Grid)
/******************************************************************************/
{
  grid=Grid;
}
/******************************************************************************/


/******************************************************************************/
void Ruler::SetBounds(double Lower, double Upper)
/******************************************************************************/
{
  if ((lower!=Lower) || (upper!=Upper))
  {
    // Setzen
    lower=Lower;
    upper=Upper;

    // Neuzeichnen
    draw();
    gtk_widget_queue_draw(drawing_area);
  }
}
/******************************************************************************/


/******************************************************************************/
double Ruler::GetLower() const
/******************************************************************************/
{
  return lower;
}
/******************************************************************************/


/******************************************************************************/
double Ruler::GetUpper() const
/******************************************************************************/
{
  return upper;
}
/******************************************************************************/


/******************************************************************************/
bool Ruler::FitToValue(double* Values, unsigned int Cnt)
/******************************************************************************/
{
  bool ret=false;
  for (unsigned int i=fitted;i<Cnt;++i)
  {
    if (fit_to_value(Values[i])) ret=true;
  }
  fitted=Cnt;
  return ret;
}
/******************************************************************************/


/******************************************************************************/
void Ruler::Reset()
/******************************************************************************/
{
  // Zuruecksetzen
  lower=0.0;
  upper=30.0;
  fitted=0;

  // Neuzeichnen
  gtk_widget_queue_resize(drawing_area);
}
/******************************************************************************/
