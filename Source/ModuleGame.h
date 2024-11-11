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

class ModuleGame : public ModuleScene
{
public:
	ModuleGame(Application* app, bool start_enabled = true);
	virtual ~ModuleGame();

	virtual void LoadMap(std::string path) = 0;
	void AddObject(MapObject* object);

	virtual bool Start();
	virtual update_status Update();
	virtual bool CleanUp();

	Counter pointsCounter = Counter(100);

	PokeBall* GetPokeball();

private:
protected:
	Texture* map_texture= nullptr;
	PokeBall* pokeBall=nullptr;

	void FromStringToVertices(std::string stringData, std::vector<b2Vec2>& vector);
	void RepositionCamera(b2Vec2 positionToTrack);

	std::vector<b2Body*> simpoleCollidersBodies;
	std::vector<MapObject*> mapObjects;
	pugi::xml_document mapFileXML;

	b2Vec2 ballSpawn;

};

