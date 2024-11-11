#pragma once
#include "MapObject.h"
class PokemonRevealer : public MapObject
{
private:
	int count = 0;
	int id = 0;
	float factor = 0;
	float animTime = 100;
	bool pokemonCompleted;
	Vector2 rectPos;
	Texture* tex;
	Timer time;
public:
	PokemonRevealer(ModuleGame* gameAt);
	~PokemonRevealer();
	void SelectPokemonIDByZone();
	update_status Update();
	bool CleanUp() override;
};