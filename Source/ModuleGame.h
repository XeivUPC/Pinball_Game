#pragma once
#include "ModuleScene.h"
#include <vector>
#include "pugixml.hpp"
#include "box2D/box2d.h"

class ModuleGame : public ModuleScene
{
public:
	ModuleGame(Application* app, bool start_enabled = true);
	~ModuleGame();

private:

protected:
	Texture* map_texture;

	

	std::vector<b2Body*> objectsBodies;
	pugi::xml_document mapFileXML;


};

