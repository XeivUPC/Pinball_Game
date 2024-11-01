#pragma once

#include "Box2DFactory.h"
#include "box2D/box2d.h"
#include "raylib.h"
#include "ModuleGame.h"
#include "ModuleUserPreferences.h"

class Animator;
class ModuleGame;

class Flipper
{
public:
	Flipper(ModuleGame* gameAt, float power, b2Vec2 position, b2Vec2 angleRange, ModuleUserPreferences::VirtualButton activationKey, bool flipped);
	~Flipper();

	update_status Update();

private:

	Texture* flipper_texture;
	Animator* flipper_animator;

	b2Vec2 drawingPosition{12,12};

	float power;
	bool flipped=false;
	ModuleUserPreferences::VirtualButton activationKey;

	ModuleGame* gameAt;

	b2Body* body;
	b2Body* anchorBody;
	b2RevoluteJoint* flipperJoint;
};

