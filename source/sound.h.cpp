
#include "sound.h"

#include <SDL_mixer.h>
#include <string>


using namespace std;



//Class SoundEffect:------------------------------------------------------------------------------

TSoundEffect::TSoundEffect()
{
    soundEffect = NULL;
}


TSoundEffect::~TSoundEffect()
{
    free();
}


bool TSoundEffect::loadFormfile(string path)
{
    soundEffect = Mix_LoadWAV(path.c_str());

    return soundEffect != NULL;
}


void TSoundEffect::free()
{
    Mix_FreeChunk(soundEffect);
    soundEffect = NULL;
}


void TSoundEffect::playSoundEffect()
{
    Mix_PlayChannel(-1, soundEffect, 0);
}



//Class Music:-----------------------------------------------------------------------------------------------------------

TMusic::TMusic()
{
    music = NULL;
}


TMusic::~TMusic()
{
    free();
}


bool TMusic::loadFromfile(string path)
{
    music = Mix_LoadMUS(path.c_str());

    return music != NULL;
}


void TMusic::free()
{
    Mix_FreeMusic(music);
    music = NULL;
}


void TMusic::playMusic()
{
    if (Mix_PlayingMusic() == 0)
    {
        Mix_PlayMusic(music, -1);
    }
}


void TMusic::stopMusic()
{
    Mix_HaltMusic();
}



