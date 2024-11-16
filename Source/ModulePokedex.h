#pragma once
#include "ModuleScene.h"
#include "raylib.h"
#include "pugixml.hpp"
#include "pokemon.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "AnimationSystem.h"
#include <vector>

using namespace pugi;
class ModulePokedex : public ModuleScene
{
private:
	std::vector<Pokemon> pokemon_list;
	int selectedLanguage = -1;
	int audioSelectId = -1;
	int audioMoveId = -1;

	Texture2D* pokedexSpritesheet = nullptr;
	Texture2D* pokedexPokemon = nullptr;
	Texture2D* pokedexSlot = nullptr;
	Animator* ScrollBarAnimator;
	bool arrowAppeared = true;
	float arrowCurrentTime;
	float arrowAnimSpeed = 0.2f;

	xml_document _data;

	int minId = 0;
	int maxId = 150;

	int minLocalId = 0;
	int maxLocalId = 4;

	int selectedId=0;
	int localSelectedId=0;

	float offset=0;
	float targetOffset=0;

	Timer lerpTimer;
	float lerpTime=0.1f;

	bool moving = false;
	int direction = 1;
	
	const std::string Text0Format(int number);
	int AnchorToRight(const std::string& text, int x);
	void RenderPokemonInfo(int id);
	float StringToNumber(std::string string);
	std::string ToLibras(std::string weight);
	std::string ToFeet(std::string weight);
	std::string ToInchDecimal(std::string weight);
	void SavePokemon(int id);
	int SearchEvolutionID(int id);
public:
	ModulePokedex(Application* app, bool start_enabled = true);
	~ModulePokedex();
	bool Init();
	bool Start();
	update_status Update();
	bool CleanUp();
	void LoadConfigFile();
	void SaveConfigFile();
	void LoadPokedex();
	int GetPokemonListCount();
	int GetOverworldTexture(int i);
	std::vector<int> GetBlueMapHabitats(int i);
	std::vector<int> GetRedMapHabitats(int i);
	int GetPokemonRarity(int i);

	void DiscoverPokemon(int id);
	void CapturePokemon(int id);
};