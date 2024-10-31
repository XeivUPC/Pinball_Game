#include "ModuleGameRedMap.h"
#include "ModulePhysics.h"
#include "Application.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleUserPreferences.h"
#include "ModuleKeybinds.h"
#include "Box2DFactory.h"
#include <sstream>

#include "ModuleHighScore.h"

ModuleGameRedMap::ModuleGameRedMap(Application* app, bool start_enabled) : ModuleGame(app, start_enabled)
{

	
}

ModuleGameRedMap::~ModuleGameRedMap()
{
}

bool ModuleGameRedMap::Start()
{
	App->texture->CreateTexture("Assets/map_redMap.png", "map_redMap");
	map_texture = App->texture->GetTexture("map_redMap");	
	

	UI = new GameUI(App);

	StartFadeOut(WHITE, 0.3f);

	LoadMap("Assets/MapData/red_map_data.tmx");

	pokeBall = new PokeBall(this);
	leftFlipper = new Flipper(this, 40000, 0.15 * b2_pi, -0.15f * b2_pi, { 13.9,64.4 }, {51,245}, false);
	rightFlipper = new Flipper(this, 40000, 0.15 * b2_pi, -0.15f * b2_pi, { 26.1,64.4 }, { 85,245 }, true);
	return true;
}

update_status ModuleGameRedMap::Update()
{
	RepositionCamera();
	MovePaddles();

	if (IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::SELECT))) {
		StartFadeIn(App->scene_highScore, WHITE, 0.3f);
	}

	

	if (IsKeyPressed(KEY_P)) {
		pokeBall->ApplyForce({ 0,-400 });
	}

	if (IsKeyPressed(KEY_R)) {
		pokeBall->SetPosition({ 43, 68 });
	}

	
	

	Rectangle rectBackground = { 0,0,191,278 };
	App->renderer->Draw(*map_texture, 0, 0, &rectBackground, WHITE);


	leftFlipper->Update();
	rightFlipper->Update();
	pokeBall->Update();

	UI->Render();

	ModuleScene::FadeUpdate();

	return UPDATE_CONTINUE;
}



void ModuleGameRedMap::RepositionCamera()
{

	if (pokeBall->GetPosition().x > 160/ SCREEN_SIZE) {
		App->renderer->camera.offset.x = -31 * SCREEN_SIZE;
	}
	else {
		App->renderer->camera.offset.x = 0;
	}

	if (pokeBall->GetPosition().y > 135/SCREEN_SIZE) {
		App->renderer->camera.offset.y = -135 * SCREEN_SIZE;
	}
	else{
		App->renderer->camera.offset.y = 0;
	}
}

void ModuleGameRedMap::MovePaddles()
{

	//if (IsKeyDown(App->userPreferences->GetKeyValue(ModuleUserPreferences::LEFT))) {
	//	/// Trigger Left Paddle
	//	paddleLeft_animator->SelectAnimation("Paddle_Click", false);
	//	leftPaddleJoint->SetMotorSpeed(40000.0f);
	//}else
	//{
	//	leftPaddleJoint->SetMotorSpeed(-40000.0f);
	//	paddleLeft_animator->SelectAnimation("Paddle_Idle", true);
	//}

	//if (IsKeyDown(App->userPreferences->GetKeyValue(ModuleUserPreferences::RIGHT))) {
	//	/// Trigger Right Paddle
	//	rightPaddleJoint->SetMotorSpeed(-40000.0f);
	//	paddleRight_animator->SelectAnimation("Paddle_Click", false);
	//	
	//}
	//else
	//{
	//	rightPaddleJoint->SetMotorSpeed(40000.0f);
	//	paddleRight_animator->SelectAnimation("Paddle_Idle", true);
	//}

	//
}

bool ModuleGameRedMap::CleanUp()
{
	for (const auto& objectBody : objectsBodies) {
		if(objectBody!=nullptr)
			App->physics->world->DestroyBody(objectBody);
	}
	objectsBodies.clear();

	if (pokeBall != nullptr) {
		delete pokeBall;
		pokeBall = nullptr;
	}
	if (leftFlipper != nullptr) {
		delete leftFlipper;
		leftFlipper = nullptr;
	}
	if (rightFlipper != nullptr) {
		delete rightFlipper;
		rightFlipper = nullptr;
	}

	App->renderer->camera.offset = { 0,0 };
	return true;
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

			std::stringstream ss(collisionPolygonPoints);
			std::string vectorValue;

			while (std::getline(ss, vectorValue, ' ')) {
				std::stringstream ss_vectorValue(vectorValue);

				std::string x_str, y_str;
				
				std::getline(ss_vectorValue, x_str, ',');
				std::getline(ss_vectorValue, y_str);

				float x_poly = std::stof(x_str);
				float y_poly = std::stof(y_str);

				
				vertices.push_back(b2Vec2(x_poly/SCREEN_SIZE, y_poly / SCREEN_SIZE));
			}

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

			objectsBodies.emplace_back(body);

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

			if (type == "bumper") {

				b2Body* bumperBody =  Box2DFactory::GetInstance().CreateCircle(App->physics->world, { x,y }, 1.3f);
				bumperBody->SetType(b2_staticBody);
				bumperBody->GetFixtureList()[0].SetDensity(1);
				bumperBody->GetFixtureList()[0].SetRestitution(1.5f);

				objectsBodies.emplace_back(bumperBody);
			}
		}
	}
}
