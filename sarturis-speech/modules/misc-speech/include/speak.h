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
