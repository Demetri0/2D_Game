#ifndef OPENAL_H
#define OPENAL_H

//#include <AL/al.h>
//#include <AL/alc.h>
//#include <AL/alu.h>
#include <AL/alut.h>
/*
#include <AL/alext.h>
#include <AL/efx-creative.h>
#include <AL/efx-presets.h>
#include <AL/efx.h>
*/
bool InitializeOpenAL();
void DestroyOpenAL();

class remSnd
{
public:
  enum typeFile{WAV,OGG};
  ALfloat mVel[3];
  ALfloat mPos[3];
  bool  mLooped;

  // Functions
  bool Open(const char *fileName, bool Looped, bool Streamed);
  bool IsStreamed();
  void Play();
  void Close();
  void Update();
  void Move(float X, float Y, float Z);
  void Stop();

  // Construction/destruction
  remSnd();
  virtual ~remSnd();
private:
  // Идентификатор источника
  ALuint      mSourceID;
  // Потоковый ли наш звук?
  bool      mStreamed;

  bool LoadWavFile(const char *fileName);
};

#endif // OPENAL_H
