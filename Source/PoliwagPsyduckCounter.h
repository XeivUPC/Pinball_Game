#include "MapObject.h"
#include "CollisionSensor.h"
#include "Bumper.h"
#include "AnimationSystem.h"
#include "Timer.h"

class PoliwagPsyduckCounter : public MapObject {
public:
	PoliwagPsyduckCounter(ModuleGame* gameAt, b2Vec2 position, Bumper* bumperToTrack, bool flip);
	~PoliwagPsyduckCounter();

	update_status Update();
	bool CleanUp() override;

private:
	Bumper* bumperToTrack;
	bool flip = false;

	Texture* map_poliwagCounter = nullptr;
	Animator* map_poliwagCounter_animator = nullptr;

	Texture* map_psyduckCounter = nullptr;
	Animator* map_psyduckCounter_animator = nullptr;
};