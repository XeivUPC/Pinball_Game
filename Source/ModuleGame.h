#pragma once
#include "ModuleScene.h"
#include <vector>
#include "pugixml.hpp"
#include "Counter.h"

#pragma warning(disable:)
#include "box2D/box2d.h"
#pragma warning(default:)


class MapObject;
class PokeBall;
class CentralScreen;
class MapEnergyBattery;
class GameUI;
class MapCave;

class ModuleGame : public ModuleScene
{
public:

	enum GameStates {
		StartGame,
		
		PlayGame,

		BlockGame,

		RestartGame
	};


	ModuleGame(Application* app, bool start_enabled = true);
	virtual ~ModuleGame();

	virtual void LoadMap(std::string path) = 0;
	void AddObject(MapObject* object);

	virtual bool Start();
	virtual update_status Update();
	virtual bool CleanUp();
	Counter pointsCounter = Counter(100);
	PokeBall* GetPokeball();

	GameUI* GetUI();

	void NextHabitat();
	void PreviousHabitat();
	bool ChangeToHabitat(int habitat);
	int GetHabitat();

	bool IsEnergyCharged();
	void SetEnergyStatus(bool isCharged);
	void UseEnergy();

	bool CanEvolve();
	bool CanCapture();

	void OpenCave();
	void CloseCave();

	int GetBonusSelectionAttempts();
	void AddBonusSelectionAttempts();

	bool IsBallInTopSection();

	virtual void SetState(GameStates stateToChange) =0;
	GameStates GetState();

	CentralScreen* screen=nullptr;
private:
protected:
	Texture* map_texture= nullptr;
	PokeBall* pokeBall=nullptr;
	MapEnergyBattery* energyBattery=nullptr;
	GameUI* UI = nullptr;
	MapCave* cave = nullptr;

	void FromStringToVertices(std::string stringData, std::vector<b2Vec2>& vector);
	void RepositionCamera(b2Vec2 positionToTrack);

	std::vector<b2Body*> simpoleCollidersBodies;
	std::vector<MapObject*> mapObjects;
	pugi::xml_document mapFileXML;

	b2Vec2 ballSpawn;

	std::vector<int> mapHabitats;
	int habitatIndex=-1;

	bool saveBall=true;

	bool isEnergyCharged = false;
	bool isEnergyUsed = false;
	bool isBallInTopSection = false;

	bool canCapture = false;
	bool canEvolve = false;

	int bonusSelectionAttempts = 1;




	GameStates state = GameStates::StartGame;

	Timer statesTimer;
	float statesTime=0;



};

