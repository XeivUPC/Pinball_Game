#include "ModuleGameBlueMap.h"
#include "ModulePhysics.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTexture.h"
#include "ModuleAudio.h"
#include "ModuleUserPreferences.h"
#include "ModuleKeybinds.h"
#include "Box2DFactory.h"


#include "ModuleHighScore.h"

ModuleGameBlueMap::ModuleGameBlueMap(Application* app, bool start_enabled) : ModuleGame(app, start_enabled)
{

	
}

ModuleGameBlueMap::~ModuleGameBlueMap()
{
}

bool ModuleGameBlueMap::Start()
{
	App->texture->CreateTexture("Assets/map_blueMap.png", "map_blueMap");
	map_texture = App->texture->GetTexture("map_blueMap");	
	

	UI = new GameUI(App);

	StartFadeOut(WHITE, 0.3f);

	LoadMap("Assets/MapData/blue_map_data.tmx");

	pokeBall = new PokeBall(this, ballSpawn, 70);
	leftFlipper = new Flipper(this, -40000, { 13.9f,64.4f } , { -0.15f * b2_pi, 0.15f * b2_pi }, ModuleUserPreferences::LEFT, false);
	rightFlipper = new Flipper(this, 40000, { 26.1f,64.4f }, { -0.15f * b2_pi, 0.15f * b2_pi }, ModuleUserPreferences::RIGHT, true);

	return true;
}

update_status ModuleGameBlueMap::Update()
{
	RepositionCamera(pokeBall->GetPosition());

	if (IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::SELECT))) {
		StartFadeIn(App->scene_highScore, WHITE, 0.3f);
	}

	

	if (IsKeyPressed(KEY_P)) {
		pokeBall->ApplyForce({ 0,-4000 });
	}

	if (IsKeyPressed(KEY_R)) {
		pokeBall->SetPosition(ballSpawn);
		pokeBall->SetVelocity({0,0});
		
	}

	
	

	Rectangle rectBackground = { 0,0,191,278 };
	App->renderer->Draw(*map_texture, 0, 0, &rectBackground, WHITE);


	leftFlipper->Update();
	rightFlipper->Update();

	UI->Render();
	pokeBall->Update();

	ModuleScene::FadeUpdate();

	return UPDATE_CONTINUE;
}





bool ModuleGameBlueMap::CleanUp()
{
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
			chainFixtureDef.friction = 0.3f;

			b2BodyDef bd;
			bd.type = b2_staticBody; // Set the body type to static
			bd.position.Set(x, y); // Set the body's initial position

			// Create the body
			b2Body* body = App->physics->world->CreateBody(&bd);

			// Attach the fixture to the body
			body->CreateFixture(&chainFixtureDef);

			simpoleCollidersBodies.emplace_back(body);

			if (name == "DittoCollider1") {
				dittoCollider1 = body;
				//dittoCollider1->GetFixtureList()[0].SetSensor(true);
			}

			if (name == "DittoCollider2") {
				dittoCollider2 = body;
				dittoCollider2->GetFixtureList()[0].SetSensor(true);
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

				b2Body* bumperBody =  Box2DFactory::GetInstance().CreateCircle(App->physics->world, { x+ radius,y+ radius }, radius);
				bumperBody->SetType(b2_staticBody);
				bumperBody->GetFixtureList()[0].SetDensity(1);
				bumperBody->GetFixtureList()[0].SetRestitution(1.f);

				simpoleCollidersBodies.emplace_back(bumperBody);
			}
			else if (type == "triangularBumper") {

				std::string collisionPolygonPoints = objectNode.child("polygon").attribute("points").as_string();
				std::vector<b2Vec2> vertices;
				FromStringToVertices(collisionPolygonPoints, vertices);

				b2ChainShape chainShape;
				chainShape.CreateLoop(&vertices[0], vertices.size());

				b2FixtureDef chainFixtureDef;
				chainFixtureDef.shape = &chainShape;
				chainFixtureDef.density = 1.0f;
				chainFixtureDef.restitution = 0.8f;
				chainFixtureDef.friction = 1.f;

				b2BodyDef bd;
				bd.type = b2_staticBody; // Set the body type to static
				bd.position.Set(x, y); // Set the body's initial position

				// Create the body
				b2Body* body = App->physics->world->CreateBody(&bd);

				// Attach the fixture to the body
				body->CreateFixture(&chainFixtureDef);

				simpoleCollidersBodies.emplace_back(body);
			}
		}
	}
}