#pragma once
#include "ScreenProgram.h"
#include "ModuleTexture.h"
#include "Bumper.h"
class OverworldPokemon : public ScreenProgram
{
private:
	int count;
	int ID;
	int overworldID;
	bool animating = false;
	Texture* texture;
	Rectangle rect;
	Bumper* pokemon_bumper;
	Animator* animator;
	float fallingTime = 1.5f;
	float offset;
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