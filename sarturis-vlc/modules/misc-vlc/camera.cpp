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


#include <string>
#include "include/camera.h"
using namespace sarturis::vlc;


/******************************************************************************/
#ifdef WIN32
  #define DSHOW
#else
  #ifdef __CYGWIN__
    #define DSHOW
  #else
    #define V4L
  #endif
#endif
/******************************************************************************/


/******************************************************************************/
Camera::Camera(const std::string& Device):device(Device)
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
Camera::~Camera()
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
libvlc_media_t* Camera::create()
/******************************************************************************/
{
  #ifdef DSHOW
    std::string l="dshow://";
    if (device!="__EMPTY__") l+=" :dshow-vdev="+device;
  #endif

  #ifdef V4L
    std::string l="v4l2://";
    if (device!="__EMPTY__") l+=" --v4l-vdev "+device;
  #endif

  return libvlc_media_new_location(vlc,l.c_str());
}
/******************************************************************************/
