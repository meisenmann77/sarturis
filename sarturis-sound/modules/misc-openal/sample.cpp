#include <sndfile.h>
#include "sarturis/base/logger.h"
#include "sarturis/base/fileexceptions.h"
#include "sarturis/base/generalexception.h"
#include "include/sample.h"

using namespace sarturis;
using namespace sarturis::sound;


/******************************************************************************/
Sample::Sample(sarturis::ref<AnalogInput> Volume,
               sarturis::ref<AnalogInput> Frequency,
               const std::string& Filename): volume(Volume),
                                             frequency(Frequency),
                                             _loop(AL_FALSE)
/******************************************************************************/
{
  // Position der Sound-Quelle
  _sourcePos[0] = 0.0; _sourcePos[1] = 0.0; _sourcePos[2] = 0.0;
  // Geschwindigkeit der Sound-Quelle
  _sourceVel[0] = 0.0; _sourceVel[1] = 0.0; _sourceVel[2] = 0.0;

  // Sample laden
  SF_INFO info;
  SNDFILE* file=sf_open(Filename.c_str(),SFM_READ,&info);
  if (!file) SARTURIS_THROW(FileReadException(Filename));

  // Lesen
  std::vector<int16_t> read_buf(4096);
  size_t read_size=0;
  while((read_size=sf_read_short(file,read_buf.data(),read_buf.size()))!=0)
  {
    data.insert(data.end(),read_buf.begin(),read_buf.begin()+read_size);
  }

  // _buffer erzeugen
  alGenBuffers(1,&_buffer);
  alBufferData(_buffer,info.channels==1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16,
               &data.front(),data.size()*sizeof(uint16_t),info.samplerate);
  if (alGetError()!=AL_NO_ERROR)
    SARTURIS_THROW(GeneralException("Could not create buffer!"));

  // Leere Sound-Quelle erzeugen
  alGenSources(1, &_source);

  // Fehlerbehandlung
  if (alGetError() != AL_NO_ERROR)
    sarturis::Logger::Warning("Couldn't create a empty source.");

  alSourcei (_source, AL_BUFFER,   _buffer    ); // Verweis auf Buffer
  alSourcef (_source, AL_PITCH,    1.0f      ); // Abspielgeschwindigkeit
  alSourcef (_source, AL_GAIN,     1.0f      ); // Verstärkung
  alSourcefv(_source, AL_POSITION, _sourcePos ); // Position der Quelle
  alSourcefv(_source, AL_VELOCITY, _sourceVel ); // Geschwindigkeit der Quelle
  alSourcei (_source, AL_LOOPING,  _loop     ); // Soundwiederholung

  // Fehlerbehandlung
  if (alGetError() != AL_NO_ERROR)
    sarturis::Logger::Warning("Couldn't create the sample.");
}
/******************************************************************************/


/******************************************************************************/
Sample::~Sample()
/******************************************************************************/
{
  alDeleteSources(1,&_source);
  alDeleteBuffers(1,&_buffer);
}
/******************************************************************************/


/******************************************************************************/
void Sample::Update(bool Play)
/******************************************************************************/
{
  // Wenn nicht gespielt werden soll, dann stoppen
  if (!Play)
  {
    alSourceStop(_source);
    return;
  }

  // Lautstaerke und Frequenz setzen
  //--------------------------------
  // Abspielgeschwindigkeit
  alSourcef (_source, AL_PITCH,(!frequency) ? 1.0f : (float)frequency->Get());
  // Verstärkung
  alSourcef (_source, AL_GAIN,(!volume) ? 1.0f : (float)volume->Get());

  // Starten, wenn nicht schon laeuft;
  if (!IsPlaying()) alSourcePlay(_source);
}
/******************************************************************************/


/******************************************************************************/
bool Sample::IsPlaying()
/******************************************************************************/
{
  ALint play;
  alGetSourcei(_source, AL_SOURCE_STATE, &play);
  return (play==AL_PLAYING);
}
/******************************************************************************/


/******************************************************************************/
void Sample::SetPosition(const Vector3& P)
/******************************************************************************/
{
  // Position der Sound-Quelle
  _sourcePos[0] = (float)P(0);
  _sourcePos[1] = (float)P(1);
  _sourcePos[2] = (float)P(2);
  alSourcefv(_source, AL_POSITION, _sourcePos ); // Position der Quelle
}
/******************************************************************************/


/******************************************************************************/
void Sample::SetLooping(bool Loop)
/******************************************************************************/
{
  _loop = Loop;
  alSourcei (_source, AL_LOOPING,  _loop ); // Soundwiederholung
}
/******************************************************************************/
