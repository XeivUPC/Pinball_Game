#pragma once
#include "AnimationSystem.h"
#include <string.h>
class ScreenProgram
{
private:
	std::string identifier;
public:
	ScreenProgram(const std::string id);
	~ScreenProgram();
	std::string GetProgramIdentifier();
	virtual void StartProgram();
	virtual void Logic();
	virtual void Render();
	virtual void EndProgram();
};