#pragma once
#include "ScreenProgram.h"
class CapturePokemon : public ScreenProgram
{
private:
	Texture* texture;
	Timer animationType;
	Rectangle rect;
	int count;
	int ID;

	void AddHit();
	void SelectPokemonByZone(int zone);
public:
	CapturePokemon(const std::string id);
	~CapturePokemon();
	void StartProgram()override;
	void Logic()override;
	void Render()override;
	void EndProgram()override;
};