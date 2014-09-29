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
#include "sarturis/gtk/compat.h"
#include "include/digitalslider.h"
using namespace sarturis;
using namespace sarturis::gtk;


/******************************************************************************/
DigitalSlider::DigitalSlider(double Value, double Min, double Max,
                             const std::string& Orientation, bool ShowValue):
                orientation(Orientation),
                min(Min),
                max(Max),
                scale(0),
                value((int)Value),
                value0((int)Value),
                show_value(ShowValue)
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
DigitalSlider::~DigitalSlider()
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
int DigitalSlider::Get()
/******************************************************************************/
{
  return value;
}
/******************************************************************************/


/******************************************************************************/
void DigitalSlider::Update()
/******************************************************************************/
{
  if (scale) value=(int)gtk_range_get_value(GTK_RANGE(scale));
}
/******************************************************************************/


/******************************************************************************/
void DigitalSlider::Reset()
/******************************************************************************/
{
  // Auf Anfangswert setzen
  if (scale) gtk_range_set_value(GTK_RANGE(scale),value0);
}
/******************************************************************************/


/******************************************************************************/
GtkWidget* DigitalSlider::setup()
/******************************************************************************/
{
  // Adjustment mit aktuellem Wert
  GtkAdjustment* adj=gtk_adjustment_new(value,min,max,1.0,1.0,0.0);

  // Schieber horizontal oder vertical
  if (orientation=="horizontal") scale=_gtk_hscale_new(GTK_ADJUSTMENT(adj));
  else if (orientation=="vertical") scale=_gtk_vscale_new(GTK_ADJUSTMENT(adj));
  else SARTURIS_THROW(GeneralException("Unknown orientation: "+orientation));

  // Stellen, Wert anzeigen
  gtk_scale_set_digits(GTK_SCALE(scale),4);
  gtk_scale_set_draw_value(GTK_SCALE(scale),show_value ? TRUE : FALSE);

  // Widget anzeigen
  gtk_widget_show(scale);

  return scale;
}
/******************************************************************************/
