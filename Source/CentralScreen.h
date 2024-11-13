#pragma once
#include "MapObject.h"
#include "ScreenProgram.h"
#include "AnimationSystem.h"
#include <vector>
#include <string.h>

class CentralScreen : public MapObject
{
private:
	ScreenProgram* actualProgram;
	Rectangle screenArea;
public:
	void AddProgram(ScreenProgram* program);
	Rectangle GetScreenArea();
	update_status Update();
	void RemoveProgram();
	
	bool CleanUp()override;
	CentralScreen(ModuleGame* gameAt);
	~CentralScreen();
};