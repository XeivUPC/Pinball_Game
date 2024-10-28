#pragma once
#include "ModuleScene.h"
#include "AnimationSystem.h"
#include "box2D/box2d.h"
#include <vector>
#include "pugixml.hpp"

class GameUI;


using namespace pugi;

class ModuleGame : public ModuleScene {
private:
	Texture* map_texture;

	Texture* paddle_texture;
	Animator* paddleLeft_animator;
	Animator* paddleRight_animator;

	b2RevoluteJoint* leftPaddleJoint;
	b2RevoluteJoint* rightPaddleJoint;

	b2Body* ballBody;
	std::vector<b2Body*> objectsBodies;

	GameUI* UI;

	pugi::xml_document mapFileXML;


	//Create
	void LoadMap(std::string path);
	void CreateBall();
	void CreatePaddles();


	//Controls

	void RepositionCamera();

	void MovePaddles();

	std::string mapPath = "Assets/MapData/";

public:
	ModuleGame(Application* app, bool start_enabled = true);
	~ModuleGame();

	bool Start();
	update_status Update();
	bool CleanUp();
};

