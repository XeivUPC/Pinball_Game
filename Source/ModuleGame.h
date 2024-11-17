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
class SaveAgainBall;
class GetArrowGroup;
class EvoArrowGroup;

class ModuleGame : public ModuleScene
{
public:

	enum GameStates {
		StartGame,
		
		PlayGame,

		BlockGame,

		RestartGame,

		EndGame
	};


	ModuleGame(Application* app, bool start_enabled = true);
	virtual ~ModuleGame();

	virtual void LoadMap(std::string path) = 0;
	void AddObject(MapObject* object);
	void RemoveObject(MapObject* object);

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
	void StartCapture();
	void StartEvolve();
	int GetCaptureRarityLevel();

	void SetSaveBall(bool status);
	void SetExtraBall(bool status);
	bool HasExtraBall();
	bool HasSaveBall();
	void SetTimeSaveBall(float time);


	void OpenCave();
	void CloseCave();
	void FreeBallCave();

	int GetBonusSelectionAttempts();
	void AddBonusSelectionAttempts();

	bool IsBallInTopSection();

	virtual void SetState(GameStates stateToChange) =0;
	GameStates GetState();

	CentralScreen* screen=nullptr;
private:
protected:
	std::vector<MapObject*> ObjectsToRemove;
	Texture* map_texture= nullptr;
	PokeBall* pokeBall=nullptr;
	MapEnergyBattery* energyBattery=nullptr;
	GameUI* UI = nullptr;
	MapCave* cave = nullptr;
	SaveAgainBall* saveAgainBall = nullptr;
	GetArrowGroup* getArrowGroup = nullptr;
	EvoArrowGroup* evoArrowGroup = nullptr;

	void FromStringToVertices(std::string stringData, std::vector<b2Vec2>& vector);
	void RepositionCamera(b2Vec2 positionToTrack);
	void RemoveAllPendentObjects();

	std::vector<b2Body*> simpoleCollidersBodies;
	std::vector<MapObject*> mapObjects;
	pugi::xml_document mapFileXML;

	b2Vec2 ballSpawn;

	std::vector<int> mapHabitats;
	int habitatIndex=-1;

	bool saveBall = false;
	bool extraBall = false;

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

