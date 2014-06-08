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


#include <algorithm>
#include "include/iteration.h"
using namespace sarturis::curses;


/******************************************************************************/
Iteration::Iteration(const widget_vec& V):widgets(V)
/******************************************************************************/
{
  // Focus bestimmen und zeichnen
  for (unsigned int i=0;i<widgets.size();++i)
  {
    if (widgets[i]->CanHaveFocus()) focus_widgets.push_back(widgets[i]);
    widgets[i]->Draw();
  }

  // Focus einstellen
  focus=focus_next();
  if (focus.valid()) focus->SetFocus(true);

  // Cursor nach Focus einstellen
  curs_set(focus.valid() ? 1 : 0);
}
/******************************************************************************/


/******************************************************************************/
Iteration::~Iteration()
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
void Iteration::Exec()
/******************************************************************************/
{
  // Zeichen lesen
  int ch=getch();

  // Zeichenn vorhanden
  if (ch!=ERR)
  {
    switch (ch)
    {
      case 353: if (focus.valid()) focus->SetFocus(false);
                focus=focus_prev();
                if (focus.valid()) focus->SetFocus(true);
                break;

      case 9:   if (focus.valid()) focus->SetFocus(false);
                focus=focus_next();
                if (focus.valid()) focus->SetFocus(true);
                break;

      // Durch Focus-Widget behandeln
      default:  if (focus.valid()) focus->HandleKey(ch); break;
    }

    // Cursor nach Focus einstellen
    curs_set(focus.valid() ? 1 : 0);
  }
}
/******************************************************************************/


/******************************************************************************/
sarturis::ref<Widget> Iteration::focus_next()
/******************************************************************************/
{
  // Nichts da
  if (focus_widgets.size()==0) return 0;

  // Finde aktuelles Focus-Widget
  widget_vec::const_iterator iter=find(focus_widgets.begin(),
                                       focus_widgets.end(),focus);

  // Nicht drin, zb. am Anfang
  if (iter==focus_widgets.end()) return focus_widgets[0];

  // Nach vorn suchen (mit umschlagen)
  if (++iter==focus_widgets.end()) iter=focus_widgets.begin();

  return *iter;
}
/******************************************************************************/


/******************************************************************************/
sarturis::ref<Widget> Iteration::focus_prev()
/******************************************************************************/
{
  // Nichts da
  if (focus_widgets.size()==0) return 0;

  // Finde aktuelles Focus-Widget
  widget_vec::const_iterator iter=find(focus_widgets.begin(),
                                       focus_widgets.end(),focus);

  // Nicht drin, zb. am Anfang
  if (iter==focus_widgets.end()) return focus_widgets[0];

  // Nach hinten suchen mit umblaettern
  if (iter==focus_widgets.begin()) iter=focus_widgets.end();
  --iter;

  return *iter;
}
/******************************************************************************/
