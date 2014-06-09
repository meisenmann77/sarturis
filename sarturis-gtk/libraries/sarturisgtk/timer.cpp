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


#include "sarturis/gtk/timer.h"
using namespace sarturis;
using namespace sarturis::gtk;


/******************************************************************************/
Timer::Timer(unsigned int Interval, sarturis::ref<Executable> B):
         interval(Interval),
         block(B),
         timer(0)
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
Timer::~Timer()
/******************************************************************************/
{
  if (timer) g_source_remove(timer);
}
/******************************************************************************/


/******************************************************************************/
void Timer::Start()
/******************************************************************************/
{
  if (timer==0) timer=g_timeout_add(interval,(GSourceFunc)timerfunc,this);
}
/******************************************************************************/


/******************************************************************************/
void Timer::Stop()
/******************************************************************************/
{
  if (timer) g_source_remove(timer);
  timer=0;
}
/******************************************************************************/


/******************************************************************************/
gint Timer::GetId() const
/******************************************************************************/
{
  return timer;
}
/******************************************************************************/


/******************************************************************************/
gboolean Timer::timerfunc(Timer* t)
/******************************************************************************/
{
  // Schon beendet
  if (!t->GetId()) return FALSE;

  // Timer
  if (t->block.valid()) t->block->Exec();
  return TRUE;
}
/******************************************************************************/
