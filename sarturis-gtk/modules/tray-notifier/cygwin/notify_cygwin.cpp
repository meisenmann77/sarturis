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


#include "notify_cygwin.h"
using namespace sarturis;
using namespace sarturis::gtk;

/******************************************************************************/
static char dummy=0;
/******************************************************************************/


/******************************************************************************/
sarturis::ref<Notify> Notify::Create(GdkPixbuf* Icon)
/******************************************************************************/
{
  return new NotifyCygwin(Icon);
}
/******************************************************************************/


/******************************************************************************/
NotifyCygwin::NotifyCygwin(GdkPixbuf* Icon):id(100+cnt++)
/******************************************************************************/
{
  HMODULE h;
  GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS,&dummy,&h);
  icon=LoadIcon(h,MAKEINTRESOURCE(500));

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
NotifyCygwin::~NotifyCygwin()
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
void NotifyCygwin::Balloon(const std::string& Title, const std::string& Info)
/******************************************************************************/
{
  NOTIFYICONDATA d;
  memset(&d,0,sizeof(NOTIFYICONDATA));
  d.cbSize=sizeof(NOTIFYICONDATA);
  d.hWnd=GetDesktopWindow();
  d.uFlags=NIF_INFO;
  d.dwInfoFlags=NIIF_USER;
  d.uID=id;

  strcpy(d.szInfo,Info.c_str());
  strcpy(d.szInfoTitle,Title.c_str());

  Shell_NotifyIcon(NIM_MODIFY,&d);
}
/******************************************************************************/
