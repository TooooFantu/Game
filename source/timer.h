#pragma once

#include "const.h"



class TTimer
{
    public:

        TTimer();

        void Start();
        void Stop();
        void Pause();
        void unPause();

        Unit32 GetTicks();

        bool isStarted();

        bool isPaused();

    private:

        Unit32 mStartTicks;

        Unit32 mPausedTicks;

        bool mStarted;

        bool mPaused;

};
