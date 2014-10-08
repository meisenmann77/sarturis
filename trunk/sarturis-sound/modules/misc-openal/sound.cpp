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


#include "include/sound.h"
using namespace sarturis;
using namespace sarturis::sound;

/******************************************************************************/
Sound::Sound(sarturis::ref<DigitalInput> Condition,
             sarturis::ref<PositionInput> Position,
             sarturis::ref<Sample> Start,
             std::vector<sarturis::ref<Sample> > Middle,
             sarturis::ref<Sample> End):  state(OFF),
     												              condition(Condition),
     												              position(Position),
                                          start_sample(Start),
                                          middle_samples(Middle),
                                          end_sample(End)
/******************************************************************************/
{
  // Start- und End-Sample werden nur einmal abgespielt
  if (start_sample.valid()) start_sample->SetLooping(false);
  if (end_sample.valid()) end_sample->SetLooping(false);

  // Middle-Samples werden wiederholt (Loop)
  for (unsigned int i=0;i<middle_samples.size();++i)
  {
    middle_samples[i]->SetLooping(true);
  }
}
/******************************************************************************/


/******************************************************************************/
Sound::~Sound()
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
void Sound::Update()
/******************************************************************************/
{	
  // Position setzen
  if (start_sample.valid()) start_sample->SetPosition(position->Get().vec);
  for (unsigned int i=0;i<middle_samples.size();++i)
  {
    middle_samples[i]->SetPosition(position->Get().vec);
  }
  if (end_sample.valid()) end_sample->SetPosition(position->Get().vec);

  // state veraendern
  if (condition->Get())
  {
    if (state==SWITCH_ON) state=ON;
    if (state==OFF) state=SWITCH_ON;
  }
  else
  {
    if (state==SWITCH_OFF) state=OFF;
    if (state==ON) state=SWITCH_OFF;
  }

  // Einschalten (StartSample spielen)
  if (state==SWITCH_ON)
  {
    if (start_sample.valid()) start_sample->Update(true);
  }

  // An (Wenn Start-Sample vorbei -> Mitte-Samples spielen
  if (state==ON)
  {
    if (start_sample.valid() ? !(start_sample->IsPlaying()) : true)
    {
      for (unsigned int i=0;i<middle_samples.size();++i)
      {
        middle_samples[i]->Update(true);
      }
    }
  }

  // Ausschalten - Start und Mitte ausmachen und Ende beginnen
  if (state==SWITCH_OFF)
  {
    if (start_sample.valid()) start_sample->Update(false);
    for (unsigned int i=0;i<middle_samples.size();++i)
    {
      middle_samples[i]->Update(false);
    }
    if (end_sample.valid()) end_sample->Update(true);
  }  
}
/******************************************************************************/
