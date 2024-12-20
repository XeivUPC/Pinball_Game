#pragma once
#include "MapObject.h"
#include "ScreenProgram.h"
#include "AnimationSystem.h"
#include "CapturePokemon.h"
#include "HabitatSelectionProgram.h"
#include "HabitatSelectedProgram.h"
#include "BonusSelectionProgram.h"
#include "BonusStartProgram.h"
#include <vector>
#include <string.h>

class CentralScreen : public MapObject
{
private:
	ScreenProgram* actualProgram=nullptr;
	ScreenProgram* defaultProgram=nullptr;
public:
	Rectangle screenArea;
	void AddProgram(ScreenProgram* program);
	void SetDefaultProgram(ScreenProgram* program);
	void SwitchProgram(ScreenProgram* program);
	void CallScreenEvent(int index);
	bool HasProgram();
	bool CanProgramBeOverwritten();
	Rectangle GetScreenArea();
	update_status Update();
	void RemoveProgram();
	std::string GetActualProgramIdentifier();
	std::string GetDefaultProgramIdentifier();
	
	bool CleanUp()override;
	CentralScreen(ModuleGame* gameAt);
	~CentralScreen();
};