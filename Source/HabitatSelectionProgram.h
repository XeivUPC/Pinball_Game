#pragma once
#include "ScreenProgram.h"
#include "AnimationSystem.h"
#include <vector>
class HabitatSelectionProgram : public ScreenProgram
{
private:
	Texture* texture=nullptr;
	Animator* animator=nullptr;

	std::vector<int> habitatsToSelect;

public:
	HabitatSelectionProgram(std::vector<int> habitatsToSelect);
	~HabitatSelectionProgram();
	void CallAction(int id)override;
	void StartProgram()override;
	void Logic()override;
	void Render()override;
	void EndProgram()override;
};