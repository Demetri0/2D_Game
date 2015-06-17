#include "openal.h"
#include "GL/glut.h"
#include <math.h>
#include <iostream>
#include <QMap>
#include <stdio.h>


ALCdevice *pDevice;
ALCcontext *pContext;

ALboolean CheckALCError()
{
  ALenum ErrCode;
//  char *Err = "ALC error: ";
  if ((ErrCode = alcGetError(pDevice)) != ALC_NO_ERROR)
  {
//    Err += (char *)alcGetString(pDevice, ErrCode);
//    ERRMSG(Err.data());
    return AL_FALSE;
  }
  return AL_TRUE;
}
ALboolean CheckALError()
{
  ALenum ErrCode;
//  string Err = "OpenAL error: ";
  if ((ErrCode = alGetError()) != AL_NO_ERROR)
  {
//    Err += (char *)alGetString(ErrCode);
//    ERRMSG(Err.data());
    return AL_FALSE;
  }
  return AL_TRUE;
}

bool InitializeOpenAL()
{
    // Позиция слушателя.
    ALfloat ListenerPos[] = { 0.0, 0.0, 0.0 };

    // Скорость слушателя.
    ALfloat ListenerVel[] = { 0.0, 0.0, 0.0 };

    // Ориентация слушателя. (Первые 3 элемента – направление «на», последние 3 – «вверх»)
    ALfloat ListenerOri[] = { 0.0, 0.0, -1.0,  0.0, 1.0, 0.0 };
    // Открываем заданное по умолчанию устройство
//    pDevice = alOpenDevice(0);
    pDevice = alcOpenDevice(0);
    // Проверка на ошибки
    if (!pDevice)
    {
//        ERRMSG("Default sound device not present");
        return false;
    }
    // Создаем контекст рендеринга
    pContext = alcCreateContext(pDevice, 0);
//    if (!CheckALCError()) return false;

    // Делаем контекст текущим
    alcMakeContextCurrent(pContext);

    // Устанавливаем параметры слушателя
    // Позиция
    alListenerfv(AL_POSITION,    ListenerPos);
    // Скорость
    alListenerfv(AL_VELOCITY,    ListenerVel);
    // Ориентация
    alListenerfv(AL_ORIENTATION, ListenerOri);
    return true;
}

void DestroyOpenAL()
{
  // Очищаем все буффера
//  for (TBuf::iterator i = Buffers.begin(); i != Buffers.end(); i++)
//    alDeleteBuffers(1, &i->second.ID);
  // Выключаем текущий контекст
  alcMakeContextCurrent(NULL);
  // Уничтожаем контекст
  alcDestroyContext(pContext);
  // Закрываем звуковое устройство
  alcCloseDevice(pDevice);
}

typedef struct
{
  unsigned int  ID;
  const char*    fileName;
  unsigned int  Rate;
  unsigned int  Format;
} SndInfo;

QMap<ALuint, SndInfo> Buffers;

bool remSnd::LoadWavFile(const char *fileName)
{
  // Структура содержащая аудиопараметры
  SndInfo    buffer;
   // Формат данных в буфере
  ALenum    format;
   // Указатель на массив данных звука
  ALvoid    *data;
   // Размер этого массива
  ALsizei    size;
   // Частота звука в герцах
  ALsizei    freq;
   // Идентификатор циклического воспроизведения
  ALboolean  loop;
   // Идентификатор буфера
  ALuint    BufID = 0;

  // Заполняем SndInfo данными
  buffer.fileName = fileName;
  // Ищем, а нет ли уже существующего буфера с данным звуком?
  for (QMap<ALuint, SndInfo>::iterator i = Buffers.begin(); i != Buffers.end(); i++)
  {
    if (i.value().fileName == fileName) BufID = i.key();
  }

  // Если звук загружаем впервые
  if (!BufID)
  {
    // Создаём буфер
    alGenBuffers(1, &buffer.ID);
    if (!CheckALError()) return false;
    // Загружаем данные из wav файла
//-->    alutLoadWAVFile((ALbyte *)fileName, &format, &data, &size, &freq, &loop);
    if (!CheckALError()) return false;

    buffer.Format      = format;
    buffer.Rate      = freq;
    // Заполняем буфер данными
    alBufferData(buffer.ID, format, data, size, freq);
    if (!CheckALError()) return false;
    // Выгружаем файл за ненадобностью
//-->    alutUnloadWAV(format, data, size, freq);
    if (!CheckALError()) return false;

    // Добавляем этот буфер в массив
    Buffers[buffer.ID] = buffer;
  }
  else
    buffer = Buffers[BufID];

  // Ассоциируем буфер с источником
  alSourcei (mSourceID, AL_BUFFER, buffer.ID);

  return true;
}

bool remSnd::Open(const char *fileName, bool Looped, bool Streamed)
{
  // Проверяем файл на наличие
  FILE *pf = NULL;
  pf = fopen(fileName,"rb");
  if (pf == NULL) return false;
  fclose(pf);

  mLooped    = Looped;

  // Создаем источник соответствующий нашему звуку
  alGenSources(1, &mSourceID);
  if (!CheckALError()) return false;

  alSourcef (mSourceID, AL_PITCH,    1.0f);
  alSourcef (mSourceID, AL_GAIN,    1.0f);
  alSourcefv(mSourceID, AL_POSITION,  mPos);
  alSourcefv(mSourceID, AL_VELOCITY,  mVel);
  alSourcei (mSourceID, AL_LOOPING,  mLooped);

  // Extract ext
//  string Ext = ExtractFileExt(Filename).data();
  typeFile Ext = remSnd::WAV;
  if (Ext == remSnd::WAV)
      return LoadWavFile(fileName);
/*if (Ext == "OGG")
  {
    mStreamed = Streamed;
    return LoadOggFile(Filename, Streamed);
  } */
  return false;
}

void remSnd::Play()
{
  alSourcePlay(mSourceID);
}

void remSnd::Close()
{
  alSourceStop(mSourceID);
  if (alIsSource(mSourceID)) alDeleteSources(1, &mSourceID);
}

void remSnd::Stop()
{
  alSourceStop(mSourceID);
}

void remSnd::Move(float X, float Y, float Z)
{
  ALfloat Pos[3] = { X, Y, Z };
  alSourcefv(mSourceID, AL_POSITION, Pos);
}
