#pragma once
#include "MapObject.h"
class PokemonRevealer : public MapObject
{
private:
	int count = 0;
	int id;
	Vector2 rectPos;
	Texture* tex;
public:
	PokemonRevealer();
	~PokemonRevealer();
	void SelectPokemonIDByZone();
	update_status Update();
};