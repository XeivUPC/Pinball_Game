#pragma once
#include "ScreenProgram.h"

class BonusStartProgram : public ScreenProgram
{
private:
	Texture* texture = nullptr;
	Rectangle section;

public:
	BonusStartProgram();
	~BonusStartProgram();
	void CallAction(int id)override;
	void StartProgram()override;
	void Logic()override;
	void Render()override;
	void EndProgram()override;
};