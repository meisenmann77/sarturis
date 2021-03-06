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


#include <libnotify/notify.h>
#include "notify_linux.h"
using namespace sarturis::gtk;


/******************************************************************************/
sarturis::ref<Notify> Notify::Create(GdkPixbuf* Icon)
/******************************************************************************/
{
  return new NotifyLinux(Icon);
}
/******************************************************************************/


/******************************************************************************/
NotifyLinux::NotifyLinux(GdkPixbuf* Icon):icon(Icon)
/******************************************************************************/
{
  // Init
  if (cnt==1) notify_init("SARTURIS");
}
/******************************************************************************/


/******************************************************************************/
NotifyLinux::~NotifyLinux()
/******************************************************************************/
{
  // Deinit
//  if (cnt==1) notify_uninit();
}
/******************************************************************************/


/******************************************************************************/
void NotifyLinux::Balloon(const std::string& Title, const std::string& Info)
/******************************************************************************/
{
  // Notification
  #if (NOTIFY_VERSION_MINOR < 7)
    NotifyNotification* n=notify_notification_new(Title.c_str(),Info.c_str(),
                                                  NULL,NULL);
  #else
    NotifyNotification* n=notify_notification_new(Title.c_str(),Info.c_str(),
                                                  NULL);
  #endif

  // Bild und Prio setzen  
  notify_notification_set_icon_from_pixbuf(n,icon);
  notify_notification_set_urgency(n,NOTIFY_URGENCY_CRITICAL);

  // Anzeigen
  notify_notification_show(n,NULL);
}
/******************************************************************************/
