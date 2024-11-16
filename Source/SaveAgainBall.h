#include "MapObject.h"
#include "AnimationSystem.h"
#include "CollisionSensor.h"
#include "Timer.h"


class SaveAgainBall : public MapObject {
public:
	SaveAgainBall(ModuleGame* gameAt, b2Vec2 position);
	~SaveAgainBall();

	void SetBallSaverTimer(float time);
	update_status Update();
	bool CleanUp() override;

private:

	Texture* map_saveAgainBall = nullptr;
	Animator* map_saveBall_animator = nullptr;
	Animator* map_againBall_animator = nullptr;

	int selectedLanguage = -1;

	Timer ballSaverTimer;
	float ballSaverTime = 0.f;

	int numBallsSaved = 0;
};