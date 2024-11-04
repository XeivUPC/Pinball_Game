#pragma once
#include "Box2DFactory.h"
#include "box2D/box2d.h"
#include "raylib.h"
#include "MapObject.h"
#include "AnimationSystem.h"

class PokeBall : public MapObject
{
public:
	PokeBall(ModuleGame* gameAt, b2Vec2 position, float maxSpeed);
	~PokeBall();

	update_status Update();
	bool CleanUp() override;

	void ApplyForce(b2Vec2 force);
	void SetPosition(b2Vec2 position);
	void SetVelocity(b2Vec2 velocity);
	b2Vec2 GetPosition();

private:
	float maxSpeed;
	Texture* pokeball_texture;
	Animator* pokeball_animator;

	int pokeballAnimMaxSpeed = 80;

	b2Body* body;
};

