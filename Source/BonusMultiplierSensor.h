#pragma once
#include "MapSensor.h"
#include "CollisionSensor.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"

class BonusMultiplierSensor : public MapSensor {
public:
	BonusMultiplierSensor(ModuleGame* gameAt, b2Vec2 position, float width, float height, float angle, int order, int variant);
	~BonusMultiplierSensor();

	update_status Update();
	bool CleanUp() override;
	void Activate() override;
	void Desactivate() override;

	void SetGlowing();
	void SetNotGlowing();

	void SetDualTwinkling();
	bool IsDualTwinkling() const;

	bool JustGotHit() const;

	void SetNumber(int num);
	int GetNumber(int num) const;

	int GetOrder() const;

protected:
	void OnTrigger() override;

	b2Body* body = nullptr;

private:
	int variant = -1;
	int order = -1;

	int thisNum = 0;
	bool glowing = false;
	bool twinkling = false;
	bool dualTwinkling = false;

	Texture* texture = nullptr;
	Texture* bumperTexture = nullptr;

	Timer twinkleTimer;
	float twinkleTime = 0.5;

	Timer dualTwinklingTimer;
	float dualTwinklingTime = 0.5;
	Timer dualTwinklingTotalTimer;
	float dualTwinklingTotalTime = 2;

	bool justHit = false;

	Timer glowBumperTimer;
	float glowBumperTime = 0.5;
	bool gameStart = true;
};

