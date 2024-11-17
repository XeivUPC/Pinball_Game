#include "MapObject.h"
#include "CollisionSensor.h"
#include "AnimationSystem.h"
#include "Timer.h"

class Staryu : public MapObject {
public:
	Staryu(ModuleGame* gameAt, b2Vec2 position, b2Vec2 miniStaryuPosition);
	~Staryu();

	update_status Update();
	bool CleanUp() override;

private:

	Texture* map_staryu = nullptr;
	Texture* map_staryu_mini = nullptr;
	Animator* map_staryu_animator = nullptr;

	b2Vec2 miniStaryuPosition = { 0,0 };

};