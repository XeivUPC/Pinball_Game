#include "MapObject.h"
#include "CollisionSensor.h"
#include "AnimationSystem.h"
#include "Timer.h"

class Slowpoke : public MapObject {
public:
	Slowpoke(ModuleGame* gameAt, b2Vec2 position);
	~Slowpoke();

	update_status Update();
	bool CleanUp() override;

private:

	Texture* map_slowpoke = nullptr;
	Animator* map_slowpoke_animator = nullptr;

};