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


#include <sarturis/base/logger.h>
#include "include/openalbase.h"
using namespace sarturis;


/******************************************************************************/
sarturis::ref<OpenALBase::Context> OpenALBase::ctxt;
/******************************************************************************/


/******************************************************************************/
OpenALBase::OpenALBase()
/******************************************************************************/
{
  if (!ctxt) ctxt=new Context();
}
/******************************************************************************/


/******************************************************************************/
OpenALBase::Context::Context()
/******************************************************************************/
{
  // Initialisieren
  dev=alcOpenDevice(NULL);
  ctxt=alcCreateContext(dev,NULL);
  alcMakeContextCurrent(ctxt);
  if (alGetError()!=AL_NO_ERROR)
    sarturis::Logger::Warning("OpenAL-Context not initialized");
  else
  sarturis::Logger::Info("OpenAL-Context initialized");
}
/******************************************************************************/


/******************************************************************************/
OpenALBase::Context::~Context()
/******************************************************************************/
{
  alcMakeContextCurrent(NULL);
  alcDestroyContext(ctxt);
  alcCloseDevice(dev);
}
/******************************************************************************/
