#include "MapObject.h"
#include "AnimationSystem.h"
#include "CollisionSensor.h"
#include "Timer.h"


class SaveAgainBall : public MapObject {
public:
	SaveAgainBall(ModuleGame* gameAt, b2Vec2 position);
	~SaveAgainBall();

	update_status Update();
	bool CleanUp() override;

private:

	Texture* map_saveAgainBall = nullptr;
	Animator* map_saveAgainBall_animator = nullptr;

	int selectedLanguage = -1;

	Timer* BallSaverTimer;
	float BallSaverTime = 60.f;

	int numBallsSaved = 0;
};