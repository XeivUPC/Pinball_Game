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

	PokeBall(ModuleGame* gameAt, b2Vec2 position, PokeballType type, float maxSpeed);
	~PokeBall();

	update_status Update();
	bool CleanUp() override;

	void ApplyForce(b2Vec2 force);
	void SetPosition(b2Vec2 position);
	void SetVelocity(b2Vec2 velocity);
	void SetType(PokeballType type);
	PokeballType GetType();
	b2Vec2 GetPosition();

private:
	float maxSpeed;
	Texture* pokeball_texture;
	Animator* pokeball_animator;

	int pokeballAnimMaxSpeed = 80;

	b2Body* body;

	PokeballType type;

	bool godMode = false;
};

