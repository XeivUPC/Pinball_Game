#pragma once
#include "MapArrow.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "AnimationSystem.h"

class GetEvoArrow : public MapArrow {
public:
	GetEvoArrow(ModuleGame* gameAt, b2Vec2 position, int order, int type, int variant);
	~GetEvoArrow();

	update_status Update();
	bool CleanUp() override;
	void Activate() override;
	void Desactivate() override;
	void Twinkle() override;

	int GetOrder() const;

private:
	int variant = -1;
	int order = -1;
	int type = -1;

	b2Vec2 position = { 0,0 };

	Texture* texture = nullptr;
	Animator* animator = nullptr;

	Timer cooldownTimer;
	float cooldownTime = 0.5;
};

