#pragma once
#include "ModuleScene.h"
#include "raylib.h"
#include "pugixml.hpp"
#include "pokemon.h"
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

	float direction = 1;
	
	const std::string Text0Format(int number);
	int AnchorToRight(const std::string& text, int x);
	void RenderPokemonInfo(int id);
	float StringToNumber(std::string string);
	std::string ToLibras(std::string weight);
	std::string ToFeet(std::string weight);
	std::string ToInchDecimal(std::string weight);
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
	void SavePokedex();

};