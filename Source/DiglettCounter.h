#include "MapObject.h"
#include "CollisionSensor.h"
#include "Bumper.h"
#include "AnimationSystem.h"
#include "Timer.h"

class DiglettCounter : public MapObject {
public:
	DiglettCounter(ModuleGame* gameAt, b2Vec2 position, Bumper* bumperToTrack, bool flip);
	~DiglettCounter();

	update_status Update();
	bool CleanUp() override;

private:
	Bumper* bumperToTrack;
	bool flip = false;

	Texture* map_diggletCounter = nullptr;
	Animator* map_diggletCounter_animator = nullptr;

};