#pragma once
#include "ScreenProgram.h"
class CapturePokemon : public ScreenProgram
{
private:
	Texture* texture= nullptr;
	int animationStarted= -1;
	float factor = -1;
	float animationTime = -1;
	Timer animationTimer;
	Rectangle rect;
	Rectangle baseRect = {0,0,0,0};
	bool animating = -1;
	int count = -1;
	int ID = -1;

	Timer failedTimer;
	float failedTime = 2;

	std::vector<std::string> failedUIText = { "THE POK�MON FLEES","THE POK�MON FLEES","LE POK�MON S'ENFUIT", "DAS POK�MON FLIEHT", "EL POK�MON HA HUIDO", "IL POK�MON FUGGE" };

	void AddHit();
	void SetRandomPokemonByZone(bool zoneID, int rarity = 2);
public:
	CapturePokemon();
	~CapturePokemon();
	void SetID(int id);
	void CallAction(int id)override;
	void StartProgram()override;
	void Logic()override;
	void Render()override;
	void EndProgram()override;
};