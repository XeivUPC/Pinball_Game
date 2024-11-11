#include "MapObject.h"
#include "CollisionSensor.h"
#include "AnimationSystem.h"
#include "Timer.h"

class Bellsprout : public MapObject {
public:
	Bellsprout(ModuleGame* gameAt, b2Vec2 position);
	~Bellsprout();

	update_status Update();
	bool CleanUp() override;

private:

	Texture* map_bellsprout = nullptr;
	Animator* map_bellsprout_animator = nullptr;

};