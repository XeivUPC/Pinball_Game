#include "MapObject.h"

MapObject::MapObject(ModuleGame* gameAt)
{
	this->gameAt = gameAt;
}

MapObject::~MapObject()
{
}

update_status MapObject::Update()
{
	return UPDATE_CONTINUE;
}

ModuleGame* MapObject::GetGameAt()
{
	return gameAt;
}

bool MapObject::CleanUp()
{
	return true;
}
