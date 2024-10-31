#pragma once
#include "Box2DFactory.h"
#include "box2D/box2d.h"
#include "raylib.h"
#include "ModuleGame.h"


class Animator;
class ModuleGame;

class PokeBall
{
public:
	PokeBall(ModuleGame* gameAt);
	~PokeBall();

	update_status Update();

	void ApplyForce(b2Vec2 force);
	void SetPosition(b2Vec2 position);
	b2Vec2 GetPosition();

private:

	Texture* pokeball_texture;
	Animator* pokeball_animator;

	int pokeballAnimMaxSpeed = 80;


	ModuleGame* gameAt;
	b2Body* body;
};

