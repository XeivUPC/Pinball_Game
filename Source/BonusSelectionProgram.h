#pragma once
#include "ScreenProgram.h"
#include "AnimationSystem.h"
#include <vector>

class BonusSelectionProgram : public ScreenProgram
{
private:
	Texture* texture = nullptr;
	Animator* animator = nullptr;

	int attemptVariant = -1;

	std::vector<int> bonusToSelect;

	float speedReduction = 0.01f;

	Timer stopTimer;
	float stopTime=10.f;

	Timer selectedShowTimer;
	float selectedShowTime = 5.f;

	int selectedBonus = -1;
	int selectedBonusSubType = -1;

	bool showingSubType =false;

	bool GiveBonus(int type, int subType);

	int audioBonusSwapId = -1;
	int audioBonusSelectedId = -1;

	int previousSprite = 0;

public:
	BonusSelectionProgram(int attemptVariant);
	~BonusSelectionProgram();
	void CallAction(int id)override;
	void StartProgram()override;
	void Logic()override;
	void Render()override;
	void EndProgram()override;


};