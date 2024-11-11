#include "MapSensorGroup.h"

MapSensorGroup::MapSensorGroup(ModuleGame* gameAt) : MapObject(gameAt)
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

//void MapSensorGroup::AddSensor(MapSensor mapSensor)
//{
//	sensorGroup.push_back(mapSensor);
//}
