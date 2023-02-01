// Big thanks to Zolika for this helper wrapper <3

#pragma once

#include "util/Config.h"

#define CONFIG_VOLUME CONFIG ("Chaos.Volume", 100.0)

float
GetAudioVolume ()
{
    float volume = CONFIG_VOLUME;
    return std::clamp (volume, 0.0f, 100.0f);
}

bool
SetStreamVolume (HSTREAM stream, float volume)
{
    if (!stream) return false;

    return BASS_ChannelSetAttribute (stream, BASS_ATTRIB_VOL, volume / 100.0f);
}

HSTREAM
LoadAudioFile (const void *file)
{
    HSTREAM handle = 0;
    int     flags  = BASS_STREAM_PRESCAN | BASS_STREAM_AUTOFREE;
    handle         = BASS_StreamCreateFile (false, file, 0, 0, flags);
    return handle;
}

enum AudioPlayMode
{
    APM_Unknown,
    APM_Play,
    APM_Pause,
    APM_Stop
};

bool
ChangeStreamPlayMode (HSTREAM stream, AudioPlayMode newState,
                      BOOL restart = false)
{
    if (!stream) return false;

    switch (newState)
    {
        case AudioPlayMode::APM_Play: return BASS_ChannelPlay (stream, restart);
        case AudioPlayMode::APM_Pause: return BASS_ChannelPause (stream);
        case AudioPlayMode::APM_Stop: return BASS_ChannelStop (stream);
        default: return false;
    }
}

AudioPlayMode
GetStreamPlayMode (HSTREAM stream)
{
    if (!stream) return AudioPlayMode::APM_Unknown;

    switch (BASS_ChannelIsActive (stream))
    {
        case BASS_ACTIVE_PLAYING: return AudioPlayMode::APM_Play;
        case BASS_ACTIVE_PAUSED: return AudioPlayMode::APM_Pause;
        case BASS_ACTIVE_STOPPED: return AudioPlayMode::APM_Stop;
        default: return AudioPlayMode::APM_Unknown;
    }
}

bool
FreeStream (HSTREAM stream)
{
    if (!stream) return false;

    BASS_ChannelStop (stream);
    return BASS_StreamFree (stream);
}

void
InitBass ()
{
    static bool bFirst = 1;
    if (bFirst)
    {
        BASS_Init (-1, 44100, BASS_DEVICE_3D, 0, NULL);
        bFirst = 0;
    }
}

bool
IsAudioStreamInFolder (char *path)
{
    InitBass ();

    HSTREAM audioStream = LoadAudioFile (path);
    bool    exists      = audioStream != 0;
    FreeStream (audioStream);
    return exists;
}

HSTREAM
PlayAudioStream (const char *path)
{
    InitBass ();

    HSTREAM audioStream = LoadAudioFile (path);
    if (audioStream)
    {
        SetStreamVolume (audioStream, CONFIG_VOLUME);
        ChangeStreamPlayMode (audioStream, AudioPlayMode::APM_Play);
    }

    return audioStream;
}