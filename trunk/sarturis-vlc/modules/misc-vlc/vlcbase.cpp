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


#include "include/vlcbase.h"
using namespace sarturis::vlc;

/******************************************************************************/
unsigned int Base::cnt=0;
libvlc_instance_t* Base::vlc=0;
/******************************************************************************/


/******************************************************************************/
Base::Base()
/******************************************************************************/
{
  if (!cnt++) vlc=libvlc_new(0,0);
}
/******************************************************************************/


/******************************************************************************/
Base::~Base()
/******************************************************************************/
{
  if (!--cnt) libvlc_release(vlc);
}
/******************************************************************************/
