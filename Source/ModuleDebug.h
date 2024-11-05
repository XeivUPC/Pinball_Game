#pragma once

#include "Globals.h"
#include "Module.h"
#include "Timer.h"

#include "p2Point.h"

#include "raylib.h"
#include <vector>

class PhysBody;
class PhysicEntity;


class  ModuleDebug : public Module
{
public:
	ModuleDebug(Application* app, bool start_enabled = true);
	~ModuleDebug();

	bool Start();
	update_status Update();
	bool CleanUp();

	void ShowColliders();
	void HideColliders();

	void PlayerManualControl(bool enabled);

private:

	bool is_visible = false;
	bool player_control = false;
};
