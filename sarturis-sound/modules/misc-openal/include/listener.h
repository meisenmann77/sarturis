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


#ifndef __LISTENER__
#define __LISTENER__

#include "sarturis/linalg/vector3.h"
#include "sarturis/linalg/matrix3x3.h"
#include "sarturis/interface/updateable.h"
#include "sarturis/interface/positioninput.h"
#include "openalbase.h"
#include "sound.h"

/******************************************************************************/
namespace sarturis
{
 namespace sound
 {
  class Listener : public Updateable, public OpenALBase
  {
    public:
      // Konstruktor
      Listener(sarturis::ref<PositionInput> Position,
               std::vector<sarturis::ref<Sound> > Sounds);

      // Update
      void Update();

    protected:
      // Destruktor
      ~Listener();

    private:
      // Position
      sarturis::ref<PositionInput> position;

      // Sounds
      std::vector<sarturis::ref<Sound> > sounds;
  };
 }
}
/******************************************************************************/

#endif
