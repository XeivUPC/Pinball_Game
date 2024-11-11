#pragma once

#include "Globals.h"
#include "Timer.h"

class Timer
{
public:

	// Constructor
	Timer();

	void Start();
	double ReadSec() const;
	void LockTimer();
	void UnlockTimer();
	bool IsLocked();

private:

    // Start time in seconds
	double started_at;   

	bool locked = false;
};