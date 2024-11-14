#pragma once
#include "ScreenProgram.h"
class CapturePokemon : public ScreenProgram
{
private:
	Texture* texture;
	int animationStarted;
	float factor;
	float animationTime;
	Timer animationTimer;
	Rectangle rect;
	Rectangle baseRect;
	bool animating;
	int count;
	int ID;

	void AddHit();
	void SelectPokemonByZone(int zone);
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