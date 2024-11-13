#pragma once
#include "MapObject.h"
#include "ScreenProgram.h"
#include <vector>
#include <string.h>

class CentralScreen : public MapObject
{
private:
	ScreenProgram* actualProgram;
	Rectangle screenArea;
	void ActivateProgram(ScreenProgram* program);
protected:
	void DrawOnScreen(Texture2D texture, int x, int y, Rectangle section, Color tint, bool flip, double angle, float pivot_x, float pivot_y);
public:
	void AddProgram(ScreenProgram* program);
	update_status Update();
	void RemoveProgram();
	
	CentralScreen(ModuleGame* gameAt);
	~CentralScreen();
};