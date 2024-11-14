#pragma once
#include "MapArrow.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "AnimationSystem.h"

class CenterBlueArrow : public MapArrow {
public:
	CenterBlueArrow(ModuleGame* gameAt, b2Vec2 position, int order);
	~CenterBlueArrow();

	update_status Update();
	bool CleanUp() override;

	void ActivateTop();
	void DesactivateTop();
	void ActivateBot();
	void DesactivateBot();
	void ActivateBoth();
	void DesactivateBoth();
	void Twinkle() override;

	int GetOrder() const;

private:
	int order = -1;
	int type = -1;

	bool topActive = false;
	bool botActive = false;

	bool twinkle = false;

	b2Vec2 position = { 0,0 };

	Texture* texture = nullptr;
	Animator* animator = nullptr;

	Timer cooldownTimer;
	float cooldownTime = 0.5;
};

