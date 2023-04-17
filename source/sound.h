#pragma once

#include <SDL_mixer.h>
#include <string>


using namespace std;



class TSoundEffect
{
    public:

        TSoundEffect();

        ~TSoundEffect();

        bool loadFormfile(string path);

        void free();

        void playSoundEffect();

    private:

        Mix_Chunk* soundEffect;

};


class TMusic
{
    public:

        TMusic();

        ~TMusic();

        bool loadFromfile(string path);

        void free();

        void playMusic();

        void stopMusic();

    private:

        Mix_Music* music;

};
