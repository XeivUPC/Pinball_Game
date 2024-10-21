#pragma once

#include "Module.h"
#include "Globals.h"

#include "box2d\box2d.h"


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

	

private:

	bool debug;
	b2World* world;
	
};