#include "MapSensorGroup.h"

MapSensorGroup::MapSensorGroup(ModuleGame* gameAt) : MapObject(gameAt)
{

}

MapSensorGroup::~MapSensorGroup()
{

}

update_status MapSensorGroup::Update()
{
	return UPDATE_CONTINUE;
}

bool MapSensorGroup::CleanUp()
{
	return true;
}
