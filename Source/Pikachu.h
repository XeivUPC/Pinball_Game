#include "MapObject.h"
#include "CollisionSensor.h"

class Pikachu : public MapObject {

	Pikachu(ModuleGame* gameAt, b2Vec2 position, float restitution);
	~Pikachu() = 0;

	update_status Update();
	bool CleanUp() override;
};