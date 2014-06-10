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


#include "sarturis/common/str.h"
#include "include/httpstream.h"
using namespace sarturis::vlc;


/******************************************************************************/
HttpStream::HttpStream(httpstream::_Proxy_ Proxy, const std::string& Host,
                       unsigned int Port):
              host(Host),
              port(Port),
              proxy(Proxy)
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
HttpStream::~HttpStream()
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
libvlc_media_t* HttpStream::create()
/******************************************************************************/
{
  // Host und Port
  std::string location="http://"+host;
  if (port) location+=":"+str(port);

  // Proxy Configuration
  if (!proxy.empty)
  {
    // Einleitung
    location+=" --http-proxy=";

    // User und Password
    if (proxy.User!="__EMTPY__") location+=proxy.User;
    if (proxy.Password!="__EMPTY__") location+=":"+proxy.Password;
    if (proxy.User!="__EMTPY__") location+="@";

    // Host und Port
    location+=proxy.Host;
    if (proxy.Port) location+=":"+str(proxy.Port);
  }

  // VLC-Media
  return libvlc_media_new_location(vlc,location.c_str());
}
/******************************************************************************/
