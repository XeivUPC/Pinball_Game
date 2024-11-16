#pragma once
#include "MapObject.h"
#include "Counter.h"

class CatchedPokemon : public MapObject
{
private:
	Texture* texture;
	Rectangle rect;
public:
	Counter counter;
	CatchedPokemon(ModuleGame* gameAt);
	~CatchedPokemon();
	void CatchPokemon();
	update_status Update();
	bool CleanUp();
};