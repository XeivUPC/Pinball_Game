#pragma once
#include "Effector.h"
#include "CollisionSensor.h"

class BlackHoleEffector : public Effector {
private:
public:
	BlackHoleEffector(ModuleGame* gameAt, b2Vec2 position, float radius);
	~BlackHoleEffector();

	update_status Update();
	bool CleanUp() override;

protected:

};

