#pragma once
#include "ScreenProgram.h"
#include "AnimationSystem.h"
#include <vector>
class HabitatSelectionProgram : public ScreenProgram
{
private:
	Texture* texture;
	Animator* animator;

	std::vector<int> habitatsToSelect;

	bool alreadySelected = false;
	int selectedHabitatIndex=-1;

public:
	HabitatSelectionProgram(std::vector<int> habitatsToSelect);
	~HabitatSelectionProgram();
	void SetID(int id);
	void CallAction(int id)override;
	void StartProgram()override;
	void Logic()override;
	void Render()override;
	void EndProgram()override;
};