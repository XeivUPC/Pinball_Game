#pragma once
#include "ScreenProgram.h"

class EmptyProgram : public ScreenProgram
{
private:

public:
	EmptyProgram();
	~EmptyProgram();
	void CallAction(int id)override;
	void StartProgram()override;
	void Logic()override;
	void Render()override;
	void EndProgram()override;
};