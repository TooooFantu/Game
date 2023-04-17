
#include "timer.h"
#include "const.h"

#include <SDL.h>



TTimer::TTimer()
{
    mStartTicks = 0;

    mPausedTicks = 0;

    mStarted = false;
    mPaused = false;
}


void TTimer::Start()
{
    mStarted = true;

    mPaused = false;

    mStartTicks = SDL_GetTicks();

    mPausedTicks = 0;
}


void TTimer::Stop()
{
    mStarted = false;

    mPaused = false;

    mStartTicks = 0;

    mPausedTicks = 0;
}


void TTimer::Pause()
{
    if (mStarted && !mPaused)
    {
        mPaused = true;

        mPausedTicks = SDL_GetTicks() - mStartTicks;

        mStartTicks = 0;
    }
}


void TTimer::unPause()
{
    if (mStarted && mPaused)
    {
        mPaused = false;

        mStartTicks = SDL_GetTicks() - mPausedTicks;

        mPausedTicks = 0;
    }
}


Unit32 TTimer::GetTicks()
{
    Unit32 time = 0;
    if (isStarted())
    {
        if (isPaused())
        {
            time = mPausedTicks;
        }
        else
        {
            time = SDL_GetTicks() - mStartTicks;
        }
    }
    return time;
}


bool TTimer::isStarted()
{
    return mStarted;
}


bool TTimer::isPaused()
{
    return mPaused && mStarted;
}

