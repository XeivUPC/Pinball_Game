#pragma once
#include "Box2DFactory.h"
#pragma warning(disable:)
#include "box2D/box2d.h"
#pragma warning(default:)
#include "raylib.h"
#include "MapObject.h"
#include "AnimationSystem.h"

class PokeBall : public MapObject 
{

	

public:

	enum PokeballType {
		Pokeball,
		SuperBall,
		Ultraball,
		MasterBall
	};

	PokeBall(ModuleGame* gameAt, b2Vec2 spawn, PokeballType type, float maxSpeed);
	~PokeBall();

	update_status Update();
	bool CleanUp() override;

	void ApplyForce(b2Vec2 force);
	void SetPosition(b2Vec2 position);
	void SetVelocity(b2Vec2 velocity);
	void SetType(PokeballType type);
	PokeballType GetType();
	b2Vec2 GetPosition();
	void Reset(bool saveBall= false);

	int GetLivesPokeball() const;

	
	void SetIfBlockMovement(bool status);
	bool IsMovementBlocked();
	void SetIfBlockRender(bool status);
	bool IsRenderBlocked();

private:

	float GetMultiplierByType(PokeballType type);

	float maxSpeed;
	Texture* pokeball_texture;
	Animator* pokeball_animator;

	int pokeballAnimMaxSpeed = 80;

	b2Body* body;

	PokeballType type;

	b2Vec2 spawn;

	bool godMode = false;

	int lives_pokeball=3;


	Timer pokeballDowngradeTimer;
	float pokeballDowngradeTime = 60;

	bool blockMovement = false;
	bool blockRender = false;

	std::vector<std::string> ballSavedUIText = { "BALL SAVED","BALL SAVED","BILLE SAUVEE", "BALL GERETTET", "BOLA SALVADA", "PALLA SALVATA" };
};

