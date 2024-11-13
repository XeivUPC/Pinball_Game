#include "MapArrow.h"

MapArrow::MapArrow(ModuleGame* gameAt, b2Vec2 position) : MapObject(gameAt)
{
	this->position = position;
}

MapArrow::~MapArrow()
{

}

update_status MapArrow::Update()
{
	
	return UPDATE_CONTINUE;
}

bool MapArrow::CleanUp()
{
	return true;
}

void MapArrow::Activate() {
	active = true;
}
void MapArrow::Desactivate() {
	active = false;
}

void MapArrow::SwitchActiveStatus()
{
	if (active)
		Desactivate();
	else
		Activate();
}

bool MapArrow::IsActive()
{
	return active;
}