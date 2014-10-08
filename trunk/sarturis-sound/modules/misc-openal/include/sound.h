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


#ifndef __SOUND__
#define __SOUND__

#include "sarturis/base/referenced.h"
#include "sarturis/interface/digitalinput.h"
#include "sarturis/interface/positioninput.h"
#include "openalbase.h"
#include "sample.h"

/******************************************************************************/
namespace sarturis
{
 namespace sound
 {
  class Sound : virtual public Referenced, public OpenALBase
  {
    public:
      // Konstruktor
      Sound(sarturis::ref<DigitalInput> Condition,
            sarturis::ref<PositionInput> Position,
            sarturis::ref<Sample> Start,
            std::vector<sarturis::ref<Sample> > Middle,
            sarturis::ref<Sample> End);

      // Update
      void Update();

    protected:
      // Destruktor
      ~Sound();

    private:
      // Zustand
      typedef enum
      {
        OFF,
        SWITCH_ON,
        ON,
        SWITCH_OFF
      } StateType;
      StateType state;

      // Bedingung
      sarturis::ref<DigitalInput> condition;

      // Position
      sarturis::ref<PositionInput> position;

      // Samples
      sarturis::ref<Sample> start_sample;
      std::vector<sarturis::ref<Sample> > middle_samples;
      sarturis::ref<Sample> end_sample;
  };
 }
}
/******************************************************************************/

#endif
