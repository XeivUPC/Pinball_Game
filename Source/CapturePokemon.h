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
	CapturePokemon();
	~CapturePokemon();
	void CallAction(int id)override;
	void StartProgram()override;
	void Logic()override;
	void Render()override;
	void EndProgram()override;
};