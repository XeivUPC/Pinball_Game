#include "MapObject.h"
#include "CollisionSensor.h"
#include "AnimationSystem.h"
#include "Timer.h"


class Slowpoke : public MapObject {
public:
	Slowpoke(ModuleGame* gameAt, b2Vec2 position, float mouthRadius);
	~Slowpoke();

	update_status Update();
	bool CleanUp() override;

private:

	Texture* map_slowpoke = nullptr;
	Animator* map_slowpoke_animator = nullptr;

	b2Body* body;

	CollisionSensor sensor;

	Timer mouthTimer;
	float mouthTime = 1.f;

	bool ballIn = false;
};