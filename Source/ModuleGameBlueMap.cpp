#include "ModuleGameBlueMap.h"
#include "ModuleLevelSelection.h"
#include "ModulePhysics.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTexture.h"
#include "ModuleAudio.h"
#include "ModuleUserPreferences.h"
#include "ModuleKeybinds.h"
#include "Box2DFactory.h"
#include "CircularBumper.h"
#include "TriangularBumper.h"
#include "PokeBall.h"
#include "PoliwagBumper.h"
#include "PsyduckBumper.h"
#include "MapEnergyRotator.h"
#include "MapEnergyBattery.h"
#include "CentralScreen.h"
#include "PokeballChangerSensor.h"
#include "CaveSensor.h"
#include "Pikachu.h"
#include "Slowpoke.h"
#include "Cloyster.h"
#include "PoliwagPsyduckCounter.h"
#include "MapCave.h"
#include "SaveAgainBall.h"
#include "ModuleHighScore.h"
#include "GetArrowGroup.h"
#include "EvoArrowGroup.h"
#include "CatchedPokemon.h"
#include "BonusFinalBall.h"

ModuleGameBlueMap::ModuleGameBlueMap(Application* app, bool start_enabled) : ModuleGame(app, start_enabled)
{
	mapHabitats.emplace_back(1);
	mapHabitats.emplace_back(2);
	mapHabitats.emplace_back(4);
	mapHabitats.emplace_back(5);
	mapHabitats.emplace_back(6);
	mapHabitats.emplace_back(8);
	mapHabitats.emplace_back(10);
	mapHabitats.emplace_back(13);
	mapHabitats.emplace_back(14);
	mapHabitats.emplace_back(13);
	mapHabitats.emplace_back(16);
	mapHabitats.emplace_back(17);
}

ModuleGameBlueMap::~ModuleGameBlueMap()
{
}

bool ModuleGameBlueMap::Start()
{

	ModuleGame::Start();

	App->texture->CreateTexture("Assets/map_blueMap.png", "map_blueMap");
	map_texture = App->texture->GetTexture("map_blueMap");	
	

	UI = new GameUI(this);
	finalBallUI = new BonusFinalBall(this);
	timerUI = new TimerUI(this);

	StartFadeOut(WHITE, 0.3f);

	pokeballChangerGroup = new PokeballChangerGroup(this);
	caveSensorGroup = new CaveSensorGroup(this);
	lapSensorGroup = new LapSensorGroup(this);
	getArrowGroup = new GetArrowGroup(this);
	evoArrowGroup = new EvoArrowGroup(this);
	centerBlueArrowGroup = new CenterBlueArrowGroup(this);
	bonusMultiplierSensorGroup = new BonusMultiplierSensorGroup(this);
	catchedPokemon = new CatchedPokemon(this);

	LoadMap("Assets/MapData/blue_map_data.tmx");
	screen = new CentralScreen(this);

	caveSensorGroup->Sort();
	pokeballChangerGroup->Sort();
	lapSensorGroup->Sort();
	getArrowGroup->Sort();
	evoArrowGroup->Sort();
	centerBlueArrowGroup->Sort();
	bonusMultiplierSensorGroup->Sort();

	getArrowGroup->ActivateNext();
	getArrowGroup->ActivateNext();

	leftFlipper = new Flipper(this, -40000, { 13.9f,64.4f } , { -0.15f * b2_pi, 0.15f * b2_pi }, ModuleUserPreferences::LEFT, false);
	rightFlipper = new Flipper(this, 40000, { 26.1f,64.4f }, { -0.15f * b2_pi, 0.15f * b2_pi }, ModuleUserPreferences::RIGHT, true);

	pokeBall = new PokeBall(this, ballSpawn, PokeBall::Pokeball, 70);
	
	Pikachu* pikachu = new Pikachu(this, { 139.f / SCREEN_SIZE ,245.f / SCREEN_SIZE });
	Slowpoke* slowpoke = new Slowpoke(this, { 16.f / SCREEN_SIZE,95.f / SCREEN_SIZE }, 8.f / SCREEN_SIZE);
	Cloyster* cloyster = new Cloyster(this, { 110.f / SCREEN_SIZE,90.f / SCREEN_SIZE }, 8.f / SCREEN_SIZE);

	SetState(StartGame);

	pointsCounter.AddMultiplier(1, "MapMultiplier");
	bonusPointsCounter.AddMultiplier(1, "BonusMultiplier");

	std::vector<int> habitatsToSelect(mapHabitats.begin(), mapHabitats.begin() + 7);
	screen->AddProgram(new HabitatSelectionProgram(habitatsToSelect));
	screen->SetDefaultProgram(new HabitatSelectedProgram());

	audioGameStartId = App->audio->LoadFx("Assets/SFX/Game_BallStart.ogg");

	musicPath = "Assets/Music/Blue_Field.wav";
	catchEvoMusicPath = "Assets/Music/Catch_Evolution_Mode_Blue_Field.wav";
	PlayFieldMusic();

	audioGameRestartId = App->audio->LoadFx("Assets/SFX/Game_Restart.ogg");
	audioGameOverId = App->audio->LoadFx("Assets/SFX/Game_Over.ogg");

	return true;
}

update_status ModuleGameBlueMap::Update()
{
	ModuleGame::Update();

	if (IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::RETURN))) {
		StartFadeIn(App->scene_levelSelection, WHITE, 0.3f);
		App->audio->StopMusic();
	}

	Rectangle rectBackground = { 0,0,191,278 };
	App->renderer->Draw(*map_texture, 0, 0, &rectBackground, WHITE);

	switch (state)
	{
		case ModuleGame::StartGame:
			RepositionCamera(pokeBall->GetPosition());

			if (!statesTimer.IsLocked()) {
				pokeBall->ApplyForce({ 0,-4000 });
				if (statesTimer.ReadSec() > statesTime ) {
					SetState(PlayGame);
				}
			}
			else {
				if (IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::DOWN))) {
					statesTimer.UnlockTimer();
					statesTimer.Start();
					App->audio->PlayFx(audioGameStartId);
				}
			}

			break;
		case ModuleGame::PlayGame:
			RepositionCamera(pokeBall->GetPosition());

			if (pokeBall->GetPosition().y >= 290 / SCREEN_SIZE) {
				SetState(RestartGame);
			}

			if (lapSensorGroup->HaveToActivateArrowGet()) {
				getArrowGroup->ActivateNext();
			}
			if (lapSensorGroup->HaveToActivateArrowEvo()) {
				evoArrowGroup->ActivateNext();
			}
			//after catching/failing pokemon capture/evo, deactivate all get/evo arrows 

			if (getArrowGroup->GetActiveAmount() >= 2) {
				centerBlueArrowGroup->ActivateLeftTop();
				canCapture = true;
			}
			else
			{
				centerBlueArrowGroup->DeactivateLeftTop();
				canCapture = false;
			}

			if (evoArrowGroup->GetActiveAmount() >= 3) {
				centerBlueArrowGroup->ActivateRightTop();
				canEvolve = true;
			}
			else {
				centerBlueArrowGroup->DeactivateRightTop();
				canEvolve = false;
			}

			if (cave->IsCaveOpen()) {
				centerBlueArrowGroup->ActivateMidTop();
			}
			else {
				centerBlueArrowGroup->DeactivateMidTop();
			}

			// the top arrow in the center is activated when there is a black hole for events

			// the bottom arrow follows where the air arrow controller in the middle of the top part points

			break;
	case ModuleGame::BlockGame:
		break;
	case ModuleGame::RestartGame:
		if (saveBall || finalBallUI->IsEnded())
		{
			StartFadeIn(this, WHITE, statesTime);
			App->audio->PlayFx(audioGameRestartId);

			if (statesTimer.ReadSec() >= statesTime) {
				if (HasExtraPika())
					SetExtraPika(false);
				pokeBall->Reset(saveBall);

				if (pokeBall->GetLivesPokeball() == 0 && !extraBall) {
					//// END
					App->audio->PlayFx(audioGameOverId);
					StartFadeOut(WHITE, statesTime);
					SetState(EndGame);
				}
				else {
					if (pokeBall->GetLivesPokeball() == 0)
						SetExtraBall(false);
					StartFadeOut(WHITE, statesTime);
					SetState(StartGame);
				}
			}
		}

		break;
	case ModuleGame::EndGame:
		if (statesTime < statesTimer.ReadSec()) {
			App->scene_highScore->SetPlayerPoints(pointsCounter());
			pointsCounter.Set(0);
			StartFadeIn(App->scene_highScore, WHITE, 0.3f);
		}
		break;
	default:
		break;
	}


	for (const auto& object : mapObjects) {
		object->Update();
	}
	UI->Update();
	finalBallUI->Update();
	timerUI->Update();

	ModuleScene::FadeUpdate();
	ModuleGame::RemoveAllPendentObjects();
	return UPDATE_CONTINUE;
}

bool ModuleGameBlueMap::CleanUp()
{
	ModuleGame::CleanUp();
	for (const auto& colliderBody : simpoleCollidersBodies) {
		if(colliderBody !=nullptr)
			App->physics->world->DestroyBody(colliderBody);
	}
	simpoleCollidersBodies.clear();

	for (const auto& objectBody : mapObjects) {
		if (objectBody != nullptr) {
			objectBody->CleanUp();
			delete objectBody;
		}
	}
	mapObjects.clear();

	if (timerUI != nullptr) {
		delete timerUI;
		timerUI = nullptr;
	}

	if (UI != nullptr) {
		delete UI;
		UI = nullptr;
	}

	if (finalBallUI != nullptr) {
		delete finalBallUI;
		finalBallUI = nullptr;
	}

	App->renderer->camera.offset = { 0,0 };
	return true;
}


void ModuleGameBlueMap::LoadMap(std::string path)
{
	pugi::xml_parse_result result = mapFileXML.load_file(path.c_str());

	if (result == NULL)
	{
		printf("Could not load map xml file %s. pugi error: %s", path.c_str(), result.description());
	}
	else {
		pugi::xml_node mapCollisionsNode = mapFileXML.child("map").find_child_by_attribute("objectgroup", "name", "Collisions");
		pugi::xml_node mapObjectsNode = mapFileXML.child("map").find_child_by_attribute("objectgroup", "name", "Objects");


		for (pugi::xml_node collisionNode = mapCollisionsNode.child("object"); collisionNode != NULL; collisionNode = collisionNode.next_sibling("object")) 
		{
			///Create Map Colliders
			std::string collisionPolygonPoints = collisionNode.child("polygon").attribute("points").as_string();

			float x = collisionNode.attribute("x").as_float() / SCREEN_SIZE;
			float y = collisionNode.attribute("y").as_float() / SCREEN_SIZE;

			std::string name = collisionNode.attribute("name").as_string();

			std::vector<b2Vec2> vertices;

			FromStringToVertices(collisionPolygonPoints, vertices);

			b2ChainShape chainShape;
			chainShape.CreateLoop(&vertices[0], vertices.size());

			b2FixtureDef chainFixtureDef;
			chainFixtureDef.shape = &chainShape;
			chainFixtureDef.density = 1.0f;
			chainFixtureDef.restitution = 0.5f;
			chainFixtureDef.friction = 0.f;

			b2BodyDef bd;
			bd.type = b2_staticBody; // Set the body type to static
			bd.position.Set(x, y); // Set the body's initial position

			// Create the body
			b2Body* body = App->physics->world->CreateBody(&bd);
			
			// Attach the fixture to the body
			body->CreateFixture(&chainFixtureDef);

			if (name == "EntryCollider") {
				entryCollider = body;
				entryCollider->GetFixtureList()[0].SetSensor(true);
			}

			simpoleCollidersBodies.emplace_back(body);
		}

		for (pugi::xml_node objectNode = mapObjectsNode.child("object"); objectNode != NULL; objectNode = objectNode.next_sibling("object"))
		{
			///Create Map Objects
			pugi::xml_node typeNode = objectNode.child("properties").find_child_by_attribute("property", "name", "type");
			std::string type = typeNode.attribute("value").as_string();

			float x = objectNode.attribute("x").as_float() / SCREEN_SIZE;
			float y = objectNode.attribute("y").as_float() / SCREEN_SIZE;

			if (type == "ballSpawn") {
				ballSpawn = { x,y };
			}
			else if (type == "pokemonCircularBumper") {

				float radius = objectNode.attribute("width").as_float() / SCREEN_SIZE;
				radius /= 2;
				CircularBumper* circularBumper = new CircularBumper(this, { x,y }, radius, 1.f, 1);
			}
			else if (type == "triangularBumper") {

				std::string collisionPolygonPoints = objectNode.child("polygon").attribute("points").as_string();
				std::vector<b2Vec2> vertices;
				FromStringToVertices(collisionPolygonPoints, vertices);

				bool flip = false;
				if (x * SCREEN_SIZE > SCREEN_WIDTH / 2) {
					flip = true;
				}

				TriangularBumper* triangularBumper = new TriangularBumper(this, { x,y }, vertices, 1.f, flip, 1);
			}
			else if (type == "poliwagBumper") {
				std::string collisionPolygonPoints = objectNode.child("polygon").attribute("points").as_string();
				std::vector<b2Vec2> vertices;
				FromStringToVertices(collisionPolygonPoints, vertices);

				bool flip = false;
				if (x * SCREEN_SIZE > SCREEN_WIDTH / 2) {
					flip = true;
				}

				PoliwagBumper* poliwagBumper = new PoliwagBumper(this, { x,y }, vertices, 1.f, flip);
				PoliwagPsyduckCounter* poliwagCounter = new PoliwagPsyduckCounter(this, { 0,0 }, poliwagBumper, flip);
			}
			else if (type == "psyduckBumper") {
				std::string collisionPolygonPoints = objectNode.child("polygon").attribute("points").as_string();
				std::vector<b2Vec2> vertices;
				FromStringToVertices(collisionPolygonPoints, vertices);

				bool flip = false;
				if (x * SCREEN_SIZE > SCREEN_WIDTH / 2) {
					flip = true;
				}

				PsyduckBumper* psyduckBumper = new PsyduckBumper(this, { x,y }, vertices, 1.f, flip);
				PoliwagPsyduckCounter* psyduckCounter = new PoliwagPsyduckCounter(this, { 0,0 }, psyduckBumper, flip);
			}
			else if (type == "energyRotator") {
				float width = objectNode.attribute("width").as_float() / SCREEN_SIZE;
				float heigth = objectNode.attribute("height").as_float() / SCREEN_SIZE;
				
				pugi::xml_node batteryIdNode = objectNode.child("properties").find_child_by_attribute("property", "name", "battery");

				int batteryId = batteryIdNode.attribute("value").as_int();

				pugi::xml_node energyBatteryNode = mapObjectsNode.find_child_by_attribute("object", "id", std::to_string(batteryId).c_str());

				float batteryX = energyBatteryNode.attribute("x").as_float() / SCREEN_SIZE;
				float batteryY = energyBatteryNode.attribute("y").as_float() / SCREEN_SIZE;

				energyBattery = new MapEnergyBattery(this, { batteryX ,batteryY},1);

				x += width / 2;
				y += heigth / 2;
				MapEnergyRotator* circularBumper = new MapEnergyRotator(this, { x,y }, energyBattery, width, heigth, 1);
			}
			else if (type == "cave") {
				b2Vec2 entryPos = { 0,0 };
				float entryRadius = 0; 

				pugi::xml_node entryIdNode = objectNode.child("properties").find_child_by_attribute("property", "name", "entry");

				int entryId = entryIdNode.attribute("value").as_int();

				pugi::xml_node entryNode = mapObjectsNode.find_child_by_attribute("object", "id", std::to_string(entryId).c_str());
				entryPos.x = entryNode.attribute("x").as_float() / SCREEN_SIZE;
				entryPos.y = entryNode.attribute("y").as_float() / SCREEN_SIZE;

				entryRadius = entryNode.attribute("width").as_float() / SCREEN_SIZE;
				entryRadius /= 2;

				cave = new MapCave(this, { x,y }, entryPos, entryRadius);
			}
			else if (type == "pokeballChangerSensor") {

				float width = objectNode.attribute("width").as_float() / SCREEN_SIZE;
				float height = objectNode.attribute("height").as_float() / SCREEN_SIZE;
				float angle = objectNode.attribute("angle").as_float() / SCREEN_SIZE;

				pugi::xml_node orderNode = objectNode.child("properties").find_child_by_attribute("property", "name", "order");
				int order = orderNode.attribute("value").as_int();

				PokeballChangerSensor* pokeballChangerSensor = new PokeballChangerSensor(this, { x,y }, width, height, angle, order, 1);
				pokeballChangerGroup->AddSensor(pokeballChangerSensor);
			}
			else if (type == "caveSensor") {

				float width = objectNode.attribute("width").as_float() / SCREEN_SIZE;
				float height = objectNode.attribute("height").as_float() / SCREEN_SIZE;
				float angle = objectNode.attribute("angle").as_float() / SCREEN_SIZE;

				pugi::xml_node orderNode = objectNode.child("properties").find_child_by_attribute("property", "name", "order");
				int order = orderNode.attribute("value").as_int();

				CaveSensor* caveSensor = new CaveSensor(this, { x,y }, width, height, angle, order, 1);

				caveSensorGroup->AddSensor(caveSensor);
			}
			else if (type == "lapSensor") {

				float width = objectNode.attribute("width").as_float() / SCREEN_SIZE;
				float height = objectNode.attribute("height").as_float() / SCREEN_SIZE;
				float angle = objectNode.attribute("rotation").as_float();

				pugi::xml_node orderNode = objectNode.child("properties").find_child_by_attribute("property", "name", "order");
				int order = orderNode.attribute("value").as_int();

				LapSensor* lapSensor = new LapSensor(this, { x,y }, width, height, angle, order, 1);

				lapSensorGroup->AddSensor(lapSensor);
			}
			else if (type == "getEvoArrow") {

				float width = objectNode.attribute("width").as_float() / SCREEN_SIZE;
				float height = objectNode.attribute("height").as_float() / SCREEN_SIZE;

				pugi::xml_node orderNode = objectNode.child("properties").find_child_by_attribute("property", "name", "order");
				int order = orderNode.attribute("value").as_int();

				pugi::xml_node arrowTypeNode = objectNode.child("properties").find_child_by_attribute("property", "name", "arrowType");
				int arrowType = arrowTypeNode.attribute("value").as_int();

				GetEvoArrow* getEvoArrow = new GetEvoArrow(this, { x,y }, order, arrowType, 1);

				if (arrowType == 0) {
					evoArrowGroup->AddArrow(getEvoArrow);
				}
				else if (arrowType == 1) {
					getArrowGroup->AddArrow(getEvoArrow);
				}
			}
			else if (type == "centerArrow") {

				float width = objectNode.attribute("width").as_float() / SCREEN_SIZE;
				float height = objectNode.attribute("height").as_float() / SCREEN_SIZE;

				pugi::xml_node orderNode = objectNode.child("properties").find_child_by_attribute("property", "name", "order");
				int order = orderNode.attribute("value").as_int();

				CenterBlueArrow* centerArrow = new CenterBlueArrow(this, { x,y }, order);

				centerBlueArrowGroup->AddArrow(centerArrow);
			}
			else if (type == "bonusMultiplierSensor") {

				float width = objectNode.attribute("width").as_float() / SCREEN_SIZE;
				float height = objectNode.attribute("height").as_float() / SCREEN_SIZE;
				float angle = objectNode.attribute("rotation").as_float();

				pugi::xml_node orderNode = objectNode.child("properties").find_child_by_attribute("property", "name", "order");
				int order = orderNode.attribute("value").as_int();

				BonusMultiplierSensor* bonusMultiplierSensor = new BonusMultiplierSensor(this, { x,y }, width, height, angle, order, 1);

				bonusMultiplierSensorGroup->AddSensor(bonusMultiplierSensor);
				}
		}
	}
}

void ModuleGameBlueMap::SetState(GameStates stateToChange)
{
	ModuleGame::SetState(stateToChange);

	statesTimer.UnlockTimer();
	statesTimer.Start();

	switch (state)
	{
	case ModuleGame::StartGame:
		if (!saveBall)
			SetTimeSaveBall(24.f);
		pokeBall->SetIfBlockMovement(false);

		entryCollider->GetFixtureList()[0].SetSensor(true);
		statesTimer.LockTimer();
		statesTime = 1.1f;
		break;
	case ModuleGame::PlayGame:
		entryCollider->GetFixtureList()[0].SetSensor(false);
		break;
	case ModuleGame::BlockGame:
		break;
	case ModuleGame::RestartGame:
		pokeBall->SetIfBlockMovement(true);
		if (!saveBall)finalBallUI->Activate();
		statesTime = 0.5f;
		break;
	case ModuleGame::EndGame:
		statesTime = 1.f;
		break;
	default:
		break;
	}
}
