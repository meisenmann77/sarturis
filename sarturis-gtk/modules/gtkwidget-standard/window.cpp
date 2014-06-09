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


#include <gtk/gtk.h>
#include "include/window.h"
#include "sarturis.h"
using namespace sarturis::application::gtk;


/******************************************************************************/
Window::Window(sarturis::ref<sarturis::gtk::Widget> Child, window::_Icon_ Icon,
               const std::string& Title, int X, int Y, unsigned int Width,
               unsigned int Height, unsigned int BorderWidth, bool FullScreen,
               bool QuitOnClose, bool AllowClose)
/******************************************************************************/
{
  // Fenster erzeugen
  window=new sarturis::gtk::Window(Child,Title,X,Y,Width,Height,BorderWidth,
                                   FullScreen,QuitOnClose,AllowClose);

  // Icon
  if (!Icon.empty) window->SetIcon(Icon.Filename);
  else window->SetIcon(Pixbuf(_sarturis_,sizeof(_sarturis_)));
}
/******************************************************************************/


/******************************************************************************/
Window::~Window()
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
void Window::OnInit()
/******************************************************************************/
{
  window->Show();
}
/******************************************************************************/


/******************************************************************************/
bool Window::OnLoop()
/******************************************************************************/
{
  // Event-Handling
  while (gtk_events_pending()) gtk_main_iteration();

  // Events abgebaut -> false
  return false;
}
/******************************************************************************/


/******************************************************************************/
void Window::OnExit()
/******************************************************************************/
{
  window->Hide();
}
/******************************************************************************/


/******************************************************************************/
void Window::OnError()
/******************************************************************************/
{
   window->Hide();
}
/******************************************************************************/
