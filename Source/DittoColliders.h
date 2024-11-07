#pragma once
#include "Box2DFactory.h"
#pragma warning(disable:)
#include "box2D/box2d.h"
#pragma warning(default:)
#include "raylib.h"
#include "MapObject.h"
#include "AnimationSystem.h"
#include <unordered_map>

class DittoColliders : public MapObject
{
public:

	enum DittoMode {
		Hide,
		Small,
		Big,


		NONE
	};

	DittoColliders(ModuleGame* gameAt, b2Vec2 position);
	~DittoColliders();

	update_status Update();
	bool CleanUp() override;

	void SetModeData(DittoMode mode, b2Body* collider);
	void SetMode(DittoMode mode);
	DittoMode GetMode();


private:
	Texture* ditto_texture;
	Animator* ditto_animator;
	
	DittoMode currentMode;

	std::unordered_map<DittoMode, b2Body*> dittoData;

};


