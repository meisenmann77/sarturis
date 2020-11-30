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


#include "include/speak.h"
using namespace sarturis::speech;


/******************************************************************************/
Speak::ESPEAKInitializer Speak::init;
/******************************************************************************/


/******************************************************************************/
Speak::Speak(sarturis::ref<TextInput> Text):text(Text)
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
Speak::~Speak()
/******************************************************************************/
{
}
/******************************************************************************/


/******************************************************************************/
void Speak::Exec()
/******************************************************************************/
{
  // get the text
  std::string t=text->Get().c_str();

  // speak
  espeak_ERROR ret;
  if ((ret=espeak_Synth(t.c_str(),
                        t.size(),
                        0,
                        POS_SENTENCE,
                        0,
                        espeakCHARS_AUTO,
                        NULL,
                        NULL))!=EE_OK)
  {
    // TODO: error handling
  }
}
/******************************************************************************/


/******************************************************************************/
int Speak::synth_cb(short *wav, int numsamples, espeak_EVENT *events)
/******************************************************************************/
{
  return 0;
}
/******************************************************************************/


/******************************************************************************/
Speak::ESPEAKInitializer::ESPEAKInitializer()
/******************************************************************************/
{
  if (espeak_Initialize(AUDIO_OUTPUT_SYNCH_PLAYBACK,
                        0,
                        NULL,
                        espeakINITIALIZE_PHONEME_EVENTS)<0)
  {
    // TODO: error handling
  }

  espeak_SetSynthCallback(Speak::synth_cb);
}
/******************************************************************************/
