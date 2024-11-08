#pragma once
#include "MapObject.h"
#include "MapSensor.h"

class MapSensorGroup : public MapObject {
private:
public:
	MapSensorGroup(ModuleGame* gameAt);
	~MapSensorGroup();

	update_status Update();
	bool CleanUp() override;

protected:

};

