#pragma once
#include "MapObject.h"
#include "ScreenProgram.h"
#include "AnimationSystem.h"
#include "CapturePokemon.h"
#include <vector>
#include <string.h>

class CentralScreen : public MapObject
{
private:
	ScreenProgram* actualProgram;
	Rectangle screenArea;
public:
	void AddProgram(ScreenProgram* program);
	void CallScreenEvent(int index);
	Rectangle GetScreenArea();
	update_status Update();
	void RemoveProgram();
	std::string GetActualProgramIdentifier();
	
	bool CleanUp()override;
	CentralScreen(ModuleGame* gameAt);
	~CentralScreen();
};