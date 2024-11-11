#pragma once
#include "MapObject.h"
#include "MapSensor.h"

class MapSensorGroup : public MapObject {
private:
public:
	MapSensorGroup(ModuleGame* gameAt);
	~MapSensorGroup() = 0;

	update_status Update();
	bool CleanUp() override;

	void AddSensor(MapSensor mapSensor);

protected:
	std::vector<MapSensor> sensorGroup;

};

