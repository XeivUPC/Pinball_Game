#include "Globals.h"
#include "Application.h"
#include "ModuleDebug.h"

ModuleDebug::ModuleDebug(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

ModuleDebug::~ModuleDebug()
{
}

bool ModuleDebug::Start()
{
	LOG("Loading Debug");
	bool ret = true;

	return ret;
}

update_status ModuleDebug::Update()
{
	return UPDATE_CONTINUE;
}

bool ModuleDebug::CleanUp()
{
	LOG("Unloading Debug");


	return true;
}

void ModuleDebug::ShowColliders()
{
	is_visible = true;
}

void ModuleDebug::HideColliders()
{
	is_visible = false;
}

void ModuleDebug::PlayerManualControl(bool enabled)
{
	player_control = enabled;
}
