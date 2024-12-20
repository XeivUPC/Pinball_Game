#include "ModuleGameRedMap.h"
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
#include "PokeBall.h"
#include "TriangularBumper.h"
#include "StaryuBumper.h"
#include "MapEnergyRotator.h"
#include "MapEnergyBattery.h"
#include "PokeballChangerSensor.h"
#include "CaveSensor.h"
#include "CentralScreen.h"
#include "Pikachu.h"
#include "Staryu.h"
#include "Bellsprout.h"
#include "DiglettCounter.h"
#include "MapCave.h"
#include "SaveAgainBall.h"
#include "ModuleHighScore.h"
#include "GetArrowGroup.h"
#include "EvoArrowGroup.h"
#include "CatchedPokemon.h"
#include "BonusFinalBall.h"
#include "TornadoThrower.h"




ModuleGameRedMap::ModuleGameRedMap(Application* app, bool start_enabled) : ModuleGame(app, start_enabled)
{

	mapHabitats.emplace_back(0);
	mapHabitats.emplace_back(2);
	mapHabitats.emplace_back(3);
	mapHabitats.emplace_back(5);
	mapHabitats.emplace_back(7);
	mapHabitats.emplace_back(8);
	mapHabitats.emplace_back(9);
	mapHabitats.emplace_back(11);
	mapHabitats.emplace_back(14);
	mapHabitats.emplace_back(15);
	mapHabitats.emplace_back(16);
	mapHabitats.emplace_back(17);
	
}

ModuleGameRedMap::~ModuleGameRedMap()
{
}

bool ModuleGameRedMap::Start()
{

	ModuleGame::Start();

	App->texture->CreateTexture("Assets/map_redMap.png", "map_redMap");
	finalBallUI = new BonusFinalBall(this);
	map_texture = App->texture->GetTexture("map_redMap");	
	

	UI = new GameUI(this);
	timerUI = new TimerUI(this);

	StartFadeOut(WHITE, 0.3f);

	pokeballChangerGroup = new PokeballChangerGroup(this);
	caveSensorGroup = new CaveSensorGroup(this);
	lapSensorGroup = new LapSensorGroup(this);
	getArrowGroup = new GetArrowGroup(this);
	evoArrowGroup = new EvoArrowGroup(this);
	centerRedArrowGroup = new CenterRedArrowGroup(this);
	bonusMultiplierSensorGroup = new BonusMultiplierSensorGroup(this);
	dittoColliders = new DittoColliders(this, { 0,0 });
	LoadMap("Assets/MapData/red_map_data.tmx");
	screen = new CentralScreen(this);
	catchedPokemon = new CatchedPokemon(this);


	caveSensorGroup->Sort();
	pokeballChangerGroup->Sort();
	lapSensorGroup->Sort();
	getArrowGroup->Sort();
	evoArrowGroup->Sort();
	centerRedArrowGroup->Sort();
	bonusMultiplierSensorGroup->Sort();

	getArrowGroup->ActivateNext();
	getArrowGroup->ActivateNext();

	dittoColliders->SetMode(DittoColliders::Small);

	leftFlipper = new Flipper(this, -40000, { 13.9f,64.4f } , { -0.15f * b2_pi, 0.15f * b2_pi }, ModuleUserPreferences::LEFT, false);
	rightFlipper = new Flipper(this, 40000, { 26.1f,64.4f }, { -0.15f * b2_pi, 0.15f * b2_pi }, ModuleUserPreferences::RIGHT, true);

	pokeBall = new PokeBall(this, ballSpawn,PokeBall::Pokeball,70);

	Pikachu* pikachu = new Pikachu(this, { 139.f / SCREEN_SIZE ,245.f / SCREEN_SIZE });
	Staryu* staryu = new Staryu(this, { 0,0 }, {0,0});
	Bellsprout* bellsprout = new Bellsprout(this, { 104.f/ SCREEN_SIZE,78.f/SCREEN_SIZE },8.f/SCREEN_SIZE);

	

	SetState(StartGame);

	std::vector<int> habitatsToSelect(mapHabitats.begin(), mapHabitats.begin() + 7);
	screen->AddProgram(new HabitatSelectionProgram(habitatsToSelect));
	screen->SetDefaultProgram(new HabitatSelectedProgram());

	pointsCounter.AddMultiplier(1, "MapMultiplier");
	bonusPointsCounter.AddMultiplier(1, "BonusMultiplier");

	audioGameStartId = App->audio->LoadFx("Assets/SFX/Game_BallStart.ogg");

	musicPath = "Assets/Music/Red_Field.wav";
	catchEvoMusicPath = "Assets/Music/Catch_Evolution_Mode_Red_Field.wav";
	PlayFieldMusic();

	audioGameRestartId = App->audio->LoadFx("Assets/SFX/Game_Restart.ogg");
	audioGameOverId = App->audio->LoadFx("Assets/SFX/Game_Over.ogg");

	return true;
}

update_status ModuleGameRedMap::Update()
{
	ModuleGame::Update();
	

	if (IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::RETURN))) {
		StartFadeIn(App->scene_levelSelection, WHITE, 0.3f);
		App->audio->StopMusic();
	}

	Rectangle rectBackground = { (IsTopSideCovered() ? 1 : 0) * 191.f,0,191,278};
	staryuCollider->GetFixtureList()[0].SetSensor(!IsTopSideCovered());
	pokeballChangerGroup->SetIfEnable(!IsTopSideCovered());

	App->renderer->Draw(*map_texture, 0, 0, &rectBackground, WHITE);

	switch (state)
	{
		case ModuleGame::StartGame:
			RepositionCamera(pokeBall->GetPosition());
			if (!statesTimer.IsLocked()) {
				if (statesTimer.ReadSecEvenLocked() < 0.5f)
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

			if (IsKeyPressed(KEY_F6)) {
				pointsCounter.Add(100000000);
			}

			if (IsKeyPressed(KEY_F7)) {
				App->audio->PlayFx(audioGameOverId);
				StartFadeOut(WHITE, statesTime);
				SetState(EndGame);
			}

			staryuCollider->GetFixtureList()[0].SetSensor(!staryuBumper->IsActive());

			if (lapSensorGroup->HaveToActivateArrowGet()) {
				getArrowGroup->ActivateNext();
			}
			if (lapSensorGroup->HaveToActivateArrowEvo()) {
				evoArrowGroup->ActivateNext();
			}
			//after catching/failing pokemon capture/evo, deactivate all get/evo arrows 

			if (getArrowGroup->GetActiveAmount() >= 2) {
				centerRedArrowGroup->ActivateRight();
				centerRedArrowGroup->TwinkleRight();
				canCapture = true;
			}
			else
			{
				centerRedArrowGroup->DeactivateRight();
				canCapture = false;
			}

			if (evoArrowGroup->GetActiveAmount() >= 3) {
				centerRedArrowGroup->ActivateLeft();
				centerRedArrowGroup->TwinkleLeft();
				canEvolve = true;
			}
			else {
				centerRedArrowGroup->DeactivateLeft();
				canEvolve = false;
			}

			if (cave->IsCaveOpen()) {
				centerRedArrowGroup->ActivateMid();
				centerRedArrowGroup->TwinkleMid();
			}
			else {
				centerRedArrowGroup->DeactivateMid();
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

			App->scene_highScore->SetPlayerPoints(pointsCounter());
			StartFadeIn(App->scene_highScore, WHITE, 0.3f);

			break;
		default:
			break;
	}


	for (const auto& object : mapObjects)
	{
		object->Update();
	}

	UI->Update();
	finalBallUI->Update();
	timerUI->Update();

	ModuleScene::FadeUpdate();
	ModuleGame::RemoveAllPendentObjects();
	return UPDATE_CONTINUE;
}

bool ModuleGameRedMap::CleanUp()
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


	mapObjects.clear();

	App->renderer->camera.offset = { 0,0 };
	return true;
}

bool ModuleGameRedMap::IsTopSideCovered()
{
	return staryuBumper->IsActive();
}

void ModuleGameRedMap::LoadMap(std::string path)
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
			chainFixtureDef.restitution = 0.2f;
			chainFixtureDef.friction = 0.f;

			b2BodyDef bd;
			bd.type = b2_staticBody; // Set the body type to static
			bd.position.Set(x, y); // Set the body's initial position

			// Create the body
			b2Body* body = App->physics->world->CreateBody(&bd);

			// Attach the fixture to the body
			body->CreateFixture(&chainFixtureDef);


			if (name == "DittoCollider1") {
				dittoColliders->SetModeData(DittoColliders::Small, body);
			}
			else if (name == "DittoCollider2") {;
				dittoColliders->SetModeData(DittoColliders::Big, body);
			}
			else {
				simpoleCollidersBodies.emplace_back(body);
			}

			if (name == "StaryuCollider") {
				staryuCollider = body;
			}


		}

		for (pugi::xml_node objectNode = mapObjectsNode.child("object"); objectNode != NULL; objectNode = objectNode.next_sibling("object"))
		{
			///Create Map Objects
			pugi::xml_node typeNode  = objectNode.child("properties").find_child_by_attribute("property", "name", "type");
			std::string type = typeNode.attribute("value").as_string();

			float x = objectNode.attribute("x").as_float() / SCREEN_SIZE;
			float y = objectNode.attribute("y").as_float() / SCREEN_SIZE;

			if (type == "ballSpawn") {
				ballSpawn = { x,y };
			}
			else if (type == "pokemonCircularBumper") {

				float radius = objectNode.attribute("width").as_float() / SCREEN_SIZE;
				radius /= 2;

				CircularBumper* circularBumper = new CircularBumper(this, { x,y }, radius, 1.f, 0);
			}
			else if (type == "triangularBumper") {

				std::string collisionPolygonPoints = objectNode.child("polygon").attribute("points").as_string();
				std::vector<b2Vec2> vertices;
				FromStringToVertices(collisionPolygonPoints, vertices);

				bool flip = false;
				if (x*SCREEN_SIZE > SCREEN_WIDTH/2) {
					flip = true;
				}

				TriangularBumper* triangularBumper = new TriangularBumper(this, { x,y }, vertices, 0.9f, flip, 0);

			}
			else if (type == "diglettBumper") {

				std::string collisionPolygonPoints = objectNode.child("polygon").attribute("points").as_string();
				std::vector<b2Vec2> vertices;
				FromStringToVertices(collisionPolygonPoints, vertices);

				bool flip = false;
				if (x * SCREEN_SIZE > SCREEN_WIDTH / 2) {
					flip = true;
				}

				DiglettBumper* diglettBumper = new DiglettBumper(this, { x,y }, vertices, 1.f, flip);
				DiglettCounter* counter = new DiglettCounter(this, { 0,0 }, diglettBumper, flip);
			}
			else if (type == "staryuBumper") {

				std::string collisionPolygonPoints = objectNode.child("polygon").attribute("points").as_string();
				std::vector<b2Vec2> vertices;
				FromStringToVertices(collisionPolygonPoints, vertices);

				bool flip = false;
				if (x * SCREEN_SIZE > SCREEN_WIDTH / 2) {
					flip = true;
				}

				staryuBumper = new StaryuBumper(this, { x,y }, vertices, 1.f, flip);
			}
			else if (type == "energyRotator") {
				float width = objectNode.attribute("width").as_float() / SCREEN_SIZE;
				float heigth = objectNode.attribute("height").as_float() / SCREEN_SIZE;

				pugi::xml_node batteryIdNode = objectNode.child("properties").find_child_by_attribute("property", "name", "battery");

				int batteryId = batteryIdNode.attribute("value").as_int();

				pugi::xml_node energyBatteryNode = mapObjectsNode.find_child_by_attribute("object", "id", std::to_string(batteryId).c_str());

				float batteryX = energyBatteryNode.attribute("x").as_float() / SCREEN_SIZE;
				float batteryY = energyBatteryNode.attribute("y").as_float() / SCREEN_SIZE;

				energyBattery = new MapEnergyBattery(this, { batteryX ,batteryY }, 0);

				x += width / 2;
				y += heigth / 2;
				MapEnergyRotator* enrgyRotator = new MapEnergyRotator(this, { x,y }, energyBattery, width, heigth, 0);
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
				float angle = objectNode.attribute("rotation").as_float();

				pugi::xml_node orderNode = objectNode.child("properties").find_child_by_attribute("property", "name", "order");
				int order = orderNode.attribute("value").as_int();

				PokeballChangerSensor* pokeballChangerSensor = new PokeballChangerSensor(this, { x,y }, width, height, angle, order, 0);

				pokeballChangerGroup->AddSensor(pokeballChangerSensor);
			}
			else if (type == "caveSensor") {

				float width = objectNode.attribute("width").as_float() / SCREEN_SIZE;
				float height = objectNode.attribute("height").as_float() / SCREEN_SIZE;
				float angle = objectNode.attribute("rotation").as_float();

				pugi::xml_node orderNode = objectNode.child("properties").find_child_by_attribute("property", "name", "order");
				int order = orderNode.attribute("value").as_int();

				CaveSensor* caveSensor = new CaveSensor(this, { x,y }, width, height, angle, order, 0);

				caveSensorGroup->AddSensor(caveSensor);
			}
			else if (type == "lapSensor") {

				float width = objectNode.attribute("width").as_float() / SCREEN_SIZE;
				float height = objectNode.attribute("height").as_float() / SCREEN_SIZE;
				float angle = objectNode.attribute("rotation").as_float();

				pugi::xml_node orderNode = objectNode.child("properties").find_child_by_attribute("property", "name", "order");
				int order = orderNode.attribute("value").as_int();

				LapSensor* lapSensor = new LapSensor(this, { x,y }, width, height, angle, order, 0);

				lapSensorGroup->AddSensor(lapSensor);
			}
			else if (type == "getEvoArrow") {

				float width = objectNode.attribute("width").as_float() / SCREEN_SIZE;
				float height = objectNode.attribute("height").as_float() / SCREEN_SIZE;

				pugi::xml_node orderNode = objectNode.child("properties").find_child_by_attribute("property", "name", "order");
				int order = orderNode.attribute("value").as_int();

				pugi::xml_node arrowTypeNode = objectNode.child("properties").find_child_by_attribute("property", "name", "arrowType");
				int arrowType = arrowTypeNode.attribute("value").as_int();

				GetEvoArrow* getEvoArrow = new GetEvoArrow(this, { x,y }, order, arrowType, 0);

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

				CenterRedArrow* centerArrow = new CenterRedArrow(this, { x,y }, order);

				centerRedArrowGroup->AddArrow(centerArrow);
			}
			else if (type == "bonusMultiplierSensor") {

				float width = objectNode.attribute("width").as_float() / SCREEN_SIZE;
				float height = objectNode.attribute("height").as_float() / SCREEN_SIZE;
				float angle = objectNode.attribute("rotation").as_float();

				pugi::xml_node orderNode = objectNode.child("properties").find_child_by_attribute("property", "name", "order");
				int order = orderNode.attribute("value").as_int();

				BonusMultiplierSensor* bonusMultiplierSensor = new BonusMultiplierSensor(this, { x,y }, width, height, angle, order, 0);

				bonusMultiplierSensorGroup->AddSensor(bonusMultiplierSensor);
			}
		}
	}


}
void ModuleGameRedMap::SetState(GameStates stateToChange)
{
	ModuleGame::SetState(stateToChange);

	statesTimer.UnlockTimer();
	statesTimer.Start();
	switch (state)
	{
	case ModuleGame::StartGame:
		if(!saveBall)
			SetTimeSaveBall(24.f);
		dittoColliders->SetMode(DittoColliders::Small);
		statesTimer.LockTimer();
		statesTime = 1.8f;
		break;
	case ModuleGame::PlayGame:
		dittoColliders->SetMode(DittoColliders::Big);
		break;
	case ModuleGame::BlockGame:
		break;
	case ModuleGame::RestartGame:
		if (!saveBall) {
			timerUI->HideTimer();
			screen->RemoveProgram();
			finalBallUI->Activate();
		}
		statesTime = 0.5f;
		break;
	case ModuleGame::EndGame:
		break;
	default:
		break;
	}
}