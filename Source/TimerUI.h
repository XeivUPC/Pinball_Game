#pragma once
#include "UI.h"
#include <string>
#include "ModuleGame.h"

class TimerUI : public UI
{
public:
	TimerUI(ModuleGame* gameAt);
	~TimerUI();
	void Render();
	update_status Update();

	void AddTimer(int seconds);

	bool IsTimerFinished() const;

private:
	ModuleGame* gameAt;

	std::string FormatTime(int minutes, int seconds);

	int totalSeconds = 0;
	int timerSeconds = 0;
	int timerMinutes = 0;

	Timer secondTimer;

	bool finished = false;
};

