#include "MapObject.h"
#include "CollisionSensor.h"
#include "AnimationSystem.h"
#include "Timer.h"

class Pikachu : public MapObject {
public:
	Pikachu(ModuleGame* gameAt, b2Vec2 position);
	~Pikachu();

	update_status Update();
	bool CleanUp() override;

private:

	Texture* map_pikachu = nullptr;
	Animator* map_pikachu_animator = nullptr;

	Texture* map_pikachuEnergy = nullptr;
	Animator* map_pikachuEnergy_animator = nullptr;

	/*int position_x;*/

	int width = 16;
	int height = 16;

	b2Body* body;
	CollisionSensor sensor;

	Timer energizeTimer;
	float energizeTime = 1.f;

	bool ballIn = false;
};