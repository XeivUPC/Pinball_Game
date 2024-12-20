#pragma once
#include "AnimationSystem.h"
#include "ModuleGame.h"
#include <string.h>
class ScreenProgram
{
protected:
	ModuleGame* gameAt=nullptr;
	std::string identifier="";
	bool canBeOverwritten=false;

public:
	ScreenProgram(const std::string id);
	~ScreenProgram();
	void SetGameReference(ModuleGame* game);
	bool CanBeOverwritten();
	std::string GetProgramIdentifier();
	virtual void StartProgram();
	virtual void CallAction(int id);
	virtual void Logic();
	virtual void Render();
	virtual void EndProgram();
	
};