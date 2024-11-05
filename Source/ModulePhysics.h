#pragma once

#include "Module.h"
#include "Globals.h"

#pragma warning(disable:)
#include "box2D/box2d.h"
#pragma warning(default:)


// Module --------------------------------------
class ModulePhysics : public Module, public b2ContactListener // TODO
{
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();

	bool Start();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();

	b2World* world = nullptr;
	

private:

	bool debug;
	
};