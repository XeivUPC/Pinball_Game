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


//// vector<MapSensor>

//// AddSensor
//// RemoveSensor

//// ActivateAll
//// DesactivateAll

//// SwitchAllActiveStatus


//// AllActive

//// GetActiveAmount

//// OnAllActive virtual
