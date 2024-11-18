#pragma once
#include "Effector.h"
#include "CollisionSensor.h"

class BlackHoleEffector : public Effector {
private:
public:
	BlackHoleEffector(ModuleGame* gameAt, b2Vec2 position, float radius, float force = 50.f );
	~BlackHoleEffector();

	update_status Update();
	bool CleanUp() override;

	void SetPosition(b2Vec2 pos);

protected:
	float force;
};

