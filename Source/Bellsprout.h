#include "MapObject.h"
#include "AnimationSystem.h"
#include "CollisionSensor.h"
#include "Timer.h"


class Bellsprout : public MapObject {
public:
	Bellsprout(ModuleGame* gameAt, b2Vec2 position, float mouthRadius);
	~Bellsprout();

	update_status Update();
	bool CleanUp() override;

private:

	Texture* map_bellsprout = nullptr;
	Animator* map_bellsprout_animator = nullptr;

	b2Body* body;

	CollisionSensor sensor;

	Timer mouthTimer;
	float mouthTime = 1.f;


	bool ballIn = false;


	std::vector<std::string> catchModeUIText = { "LET'S GET POKÉMON","LET'S GET POKÉMON","ATTRAPEZ LE POKÉMON", "FANGE DAS POKÉMON", "ATRAPA AL POKEMON", "CATTURA I POKEMON" };

	int audioBellsproutAbsorbId = -1;
	int audioBellsproutHawkTuahId = -1;

};