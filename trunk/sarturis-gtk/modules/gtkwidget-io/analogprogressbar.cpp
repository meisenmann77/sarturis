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
  #define finite _finite
#endif

#include <math.h>
#include "sarturis/base/generalexception.h"
#include "sarturis/common/str.h"
#include "include/analogprogressbar.h"
using namespace sarturis;
using namespace sarturis::gtk;


/******************************************************************************/
AnalogProgressBar::AnalogProgressBar(double Min, double Max, bool ShowValue,
                                     const std::string& Orientation):
                     orientation(Orientation),
                     value(Min),
                     min(Min),
                     max(Max),
                     showvalue(ShowValue),
                     progressbar(0)
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
AnalogProgressBar::~AnalogProgressBar()
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
void AnalogProgressBar::Set(double V)
/******************************************************************************/
{
  value=V > max ? max : V < min ? min : V;
}
/******************************************************************************/


/******************************************************************************/
void AnalogProgressBar::Update()
/******************************************************************************/
{
  // Kein Progressbar - kein Update
  if (!progressbar) return;

  // Text setzen (auch wenn NaN oder INF)
  if (showvalue)
  {
    gtk_progress_bar_set_text(GTK_PROGRESS_BAR(progressbar),str(value).c_str());
  }

  // Balken setzen
  if (finite(value))
  {
    #ifdef SARTURIS_GTK2
      gtk_progress_bar_update(GTK_PROGRESS_BAR(progressbar),
                              (value-min)/(max-min));
    #else
      gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progressbar),
                                     (value-min)/(max-min));
    #endif
  }
}
/******************************************************************************/


/******************************************************************************/
GtkWidget* AnalogProgressBar::setup()
/******************************************************************************/
{
  // Progressbar
  progressbar=gtk_progress_bar_new();
  gtk_widget_show(progressbar);

#ifdef SARTURIS_GTK2
  // Orientation
  GtkProgressBarOrientation o=GTK_PROGRESS_LEFT_TO_RIGHT;
  if (orientation=="left-to-right") o=GTK_PROGRESS_LEFT_TO_RIGHT;
  else if (orientation=="right-to-left") o=GTK_PROGRESS_RIGHT_TO_LEFT;
  else if (orientation=="bottom-to-top") o=GTK_PROGRESS_BOTTOM_TO_TOP;
  else if (orientation=="top-to-bottom") o=GTK_PROGRESS_TOP_TO_BOTTOM;
  else SARTURIS_THROW(GeneralException("Unknown Orientation "+orientation+"!"));

  // Orientation setzen
  gtk_progress_bar_set_orientation(GTK_PROGRESS_BAR(progressbar),o);

#else
  // Orientation und Invertierung
  GtkOrientation o=GTK_ORIENTATION_HORIZONTAL;
  gboolean inv=false;
  if (orientation=="left-to-right")
  {
    o=GTK_ORIENTATION_HORIZONTAL;
    inv=false;
  }
  else if (orientation=="right-to-left")
  {
    o=GTK_ORIENTATION_HORIZONTAL;
    inv=true;
  }
  else if (orientation=="bottom-to-top")
  {
    o=GTK_ORIENTATION_VERTICAL;
    inv=true;
  }
  else if (orientation=="top-to-bottom")
  {
    o=GTK_ORIENTATION_VERTICAL;
    inv=false;
  }
  else SARTURIS_THROW(GeneralException("Unknown Orientation "+orientation+"!"));

  // Orientation und Invertierung setzen
  gtk_orientable_set_orientation(GTK_ORIENTABLE(progressbar),o);
  gtk_progress_bar_set_inverted(GTK_PROGRESS_BAR(progressbar),inv);
#endif

  // Aktualisieren und return
  Update();
  return progressbar;
}
/******************************************************************************/
