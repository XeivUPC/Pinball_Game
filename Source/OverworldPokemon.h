#pragma once
#include "ScreenProgram.h"
#include "ModuleTexture.h"
#include "Bumper.h"
class OverworldPokemon : public ScreenProgram
{
private:
	int count = 0;
	int ID = 0;
	int overworldID = 0;
	bool animating = false;
	Texture* texture = nullptr;
	Rectangle rect = {0,0,0,0};
	Bumper* pokemon_bumper = nullptr;
	Animator* animator = nullptr;
	float fallingTime = 0.5f;
	float offset = 0;
	float factor = 0;

	Timer timer;
	float timerTime = 0;

	Timer failedTimer;
	float failedTime = 2;

	std::vector<std::string> capturedUIText = { "CATCHED","CATCHED","CAUCHETTE", "GEFANGEN", "ATRAPADO", "ACCERTATO" };

	std::vector<std::string> failedUIText = { "THE POKÉMON FLEES","THE POKÉMON FLEES","LE POKÉMON S'ENFUIT", "DAS POKÉMON FLIEHT", "EL POKÉMON HA HUIDO", "IL POKÉMON FUGGE" };

	int audioCaptureId = -1;
	int audioPokeballMovingId = -1;

	void AddHit();
public:
	OverworldPokemon(int id);
	~OverworldPokemon();
	void CallAction(int id)override;
	void StartProgram()override;
	void Logic()override;
	void Render()override;
	void EndProgram()override;
};