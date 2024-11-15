#pragma once
#include "MapObject.h"
#include "ScreenProgram.h"
#include "AnimationSystem.h"
#include "CapturePokemon.h"
#include "HabitatSelectionProgram.h"
#include <vector>
#include <string.h>

class CentralScreen : public MapObject
{
private:
	ScreenProgram* actualProgram;
public:
	Rectangle screenArea;
	void AddProgram(ScreenProgram* program);
	void CallScreenEvent(int index);
	bool HasProgram();
	Rectangle GetScreenArea();
	update_status Update();
	void RemoveProgram();
	void QuitProgram();
	std::string GetActualProgramIdentifier();
	
	bool CleanUp()override;
	CentralScreen(ModuleGame* gameAt);
	~CentralScreen();
};