// ----------------------------------------------------
// j1Timer.cpp
// Fast timer with milisecons precision
// ----------------------------------------------------

#include "Timer.h"

#include "raylib.h"

Timer::Timer()
{
	Start();
}

void Timer::Start()
{
	if (locked)
		return;
	started_at = GetTime();
}

double Timer::ReadSec() const
{
	if (locked)
		return -1;
	return (GetTime() - started_at);
}

void Timer::LockTimer()
{
	locked = true;
}

void Timer::UnlockTimer()
{
	locked = false;
}

bool Timer::IsLocked()
{
	return locked;
}
