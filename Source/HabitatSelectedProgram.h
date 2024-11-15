#pragma once
#include "ScreenProgram.h"
#include "AnimationSystem.h"

class HabitatSelectedProgram : public ScreenProgram
{
private:
	Texture* texture=nullptr;

	Timer timer;
	float minTimeInScreen = 1.f;

public:
	HabitatSelectedProgram();
	~HabitatSelectedProgram();
	void SetID(int id);
	void CallAction(int id)override;
	void StartProgram()override;
	void Logic()override;
	void Render()override;
	void EndProgram()override;
};