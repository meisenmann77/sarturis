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


#ifndef __SAMPLE__
#define __SAMPLE__

#include <string>
#include <vector>
#include "sarturis/base/referenced.h"
#include "sarturis/linalg/vector3.h"
#include "sarturis/interface/analoginput.h"
#include "openalbase.h"


/******************************************************************************/
namespace sarturis
{
 namespace sound
 {
  class Sample : virtual public Referenced, public OpenALBase
  {
    public:
      // Konstruktor
      Sample(sarturis::ref<AnalogInput> Volume,
             sarturis::ref<AnalogInput> Frequency, const std::string& Filename);

      // Abspielen und Test
      void Update(bool Play);
      bool IsPlaying();

      // Position setzen
      void SetPosition(const Vector3& P);

      // Loop setzen
      void SetLooping(bool Loop);

    protected:
      // Destruktor
      ~Sample();

    private:
      // Referenzen
      sarturis::ref<AnalogInput> volume;
      sarturis::ref<AnalogInput> frequency;
  
      // Sound-Buffer und Daten
      ALuint _buffer;
      std::vector<unsigned short> data;
        
      // Sound-Source
      ALuint _source;
        
      // Flag Soundloop
      ALboolean _loop;
        
      // Position der Sound-Quelle
      ALfloat _sourcePos[3];
      // Geschwindigkeit der Sound-Quelle
      ALfloat _sourceVel[3];
    };
  }
}
/******************************************************************************/

#endif
