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


#include <espeak-ng/speak_lib.h>
#include "sarturis/interface/executable.h"
#include "sarturis/interface/textinput.h"


namespace sarturis
{
  namespace speech
  {
    class Speak : virtual public Executable
    {
      public:
        Speak(sarturis::ref<TextInput> Text);
        void Exec();

      protected:
        ~Speak();

      private:
        sarturis::ref<TextInput> text;

        static int synth_cb(short *wav, int numsamples, espeak_EVENT *events);

        class ESPEAKInitializer
        {
          public:
            ESPEAKInitializer();
        };

        static ESPEAKInitializer init;
    };
  }
}
