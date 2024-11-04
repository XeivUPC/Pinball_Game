#pragma once

#include "Box2DFactory.h"
#pragma warning(disable:)
#include "box2D/box2d.h"
#pragma warning(default:)

#include "raylib.h"
#include "MapObject.h"
#include "ModuleUserPreferences.h"
#include "AnimationSystem.h"

class Flipper : public MapObject
{
public:
	Flipper(ModuleGame* gameAt, float power, b2Vec2 position, b2Vec2 angleRange, ModuleUserPreferences::VirtualButton activationKey, bool flipped);
	~Flipper();

	update_status Update();
	bool CleanUp() override;

private:

	Texture* flipper_texture;
	Animator* flipper_animator;

	b2Vec2 drawingPosition{12,12};

	float power;
	bool flipped=false;
	ModuleUserPreferences::VirtualButton activationKey;

	

	b2Body* body;
	b2Body* anchorBody;
	b2RevoluteJoint* flipperJoint;
};

