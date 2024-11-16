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
	float fallingTime = 1.5f;
	float offset = 0;
	float factor = 0;

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