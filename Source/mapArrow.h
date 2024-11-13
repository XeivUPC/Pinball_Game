#pragma once
#include "MapObject.h"
#include "CollisionSensor.h"

class MapArrow : public MapObject {
private:
public:
	MapArrow(ModuleGame* gameAt, b2Vec2 position);
	~MapArrow() = 0;

	update_status Update();
	bool CleanUp() override;

	virtual void Activate() = 0;
	virtual void Desactivate() = 0;
	void SwitchActiveStatus();
	bool IsActive();

protected:
	bool active = false;

	b2Vec2 position = { 0,0 };
};