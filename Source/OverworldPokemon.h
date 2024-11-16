#pragma once
#include "ScreenProgram.h"
#include "ModuleTexture.h"
class OverworldPokemon : public ScreenProgram
{
private:
	int count;
	int ID;
	int overworldID;
	Texture* texture;
	Rectangle rect;

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