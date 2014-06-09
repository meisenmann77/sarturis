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


#include <gdk/gdkwin32.h>
#include "include/notify.h"
using namespace sarturis::gtk;


/******************************************************************************/
int Notify::cnt=0;
/******************************************************************************/


/******************************************************************************/
Notify::Notify(GdkPixbuf* Icon):id(100+cnt++)
/******************************************************************************/
{
  icon=gdk_win32_pixbuf_to_hicon_libgtk_only(Icon);

  NOTIFYICONDATA d;
  memset(&d,0,sizeof(NOTIFYICONDATA));
  d.cbSize=sizeof(NOTIFYICONDATA);
  d.hIcon=icon;
  d.uFlags=NIF_ICON;
  d.hWnd=GetDesktopWindow();
  d.uID=id;

  Shell_NotifyIcon(NIM_ADD,&d);
}
/******************************************************************************/


/******************************************************************************/
Notify::~Notify()
/******************************************************************************/
{
  NOTIFYICONDATA d;
  memset(&d,0,sizeof(NOTIFYICONDATA));
  d.cbSize=sizeof(NOTIFYICONDATA);
  d.hWnd=GetDesktopWindow();
  d.uID=id;
  Shell_NotifyIcon(NIM_DELETE,&d);
}
/******************************************************************************/


/******************************************************************************/
void Notify::Balloon(const std::string& Title, const std::string& Info)
/******************************************************************************/
{
  NOTIFYICONDATA d;
  memset(&d,0,sizeof(NOTIFYICONDATA));
  d.cbSize=NOTIFYICONDATA_V3_SIZE;
  d.hWnd=GetDesktopWindow();
  d.uFlags=NIF_INFO;
  d.dwInfoFlags=NIIF_USER;
  d.uID=id;
  d.hBalloonIcon=icon;

  strcpy_s(d.szInfo,Info.c_str());
  strcpy_s(d.szInfoTitle,Title.c_str());

  Shell_NotifyIcon(NIM_MODIFY,&d);
}
/******************************************************************************/
