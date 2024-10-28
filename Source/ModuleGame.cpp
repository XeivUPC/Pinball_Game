#include "ModuleGame.h"
#include "ModulePhysics.h"
#include "Application.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleUserPreferences.h"
#include "ModuleKeybinds.h"
#include "GameUI.h"
#include <sstream>

#include "ModuleHighScore.h"

ModuleGame::ModuleGame(Application* app, bool start_enabled) : ModuleScene(app, start_enabled)
{

	
}

ModuleGame::~ModuleGame()
{
}

bool ModuleGame::Start()
{
	App->texture->CreateTexture("Assets/map_redMap.png", "map_redMap");
	map_texture = App->texture->GetTexture("map_redMap");

	App->texture->CreateTexture("Assets/map_paddle.png", "map_paddle");
	paddle_texture = App->texture->GetTexture("map_paddle");

	paddleLeft_animator = new Animator(App);
	paddleRight_animator = new Animator(App);

	AnimationData paddleIdle = AnimationData("Paddle_Idle");
	paddleIdle.AddSprite(Sprite{ paddle_texture,{2, 0}, {24,24} });

	AnimationData paddleClick = AnimationData("Paddle_Click");
	paddleClick.AddSprite(Sprite{ paddle_texture,{0, 0}, {24,24} });
	paddleClick.AddSprite(Sprite{ paddle_texture,{1, 0}, {24,24} });
	paddleClick.AddSprite(Sprite{ paddle_texture,{2, 0}, {24,24} });
	paddleClick.AddSprite(Sprite{ paddle_texture,{2, 0}, {24,24} });

	paddleLeft_animator->AddAnimation(paddleIdle);
	paddleLeft_animator->AddAnimation(paddleClick);
	paddleLeft_animator->SetSpeed(0.07);
	paddleLeft_animator->SelectAnimation("Paddle_Idle", true);

	paddleRight_animator->AddAnimation(paddleIdle);
	paddleRight_animator->AddAnimation(paddleClick);
	paddleRight_animator->SetSpeed(0.07);
	paddleRight_animator->SelectAnimation("Paddle_Idle", true);


	UI = new GameUI(App);

	StartFadeOut(WHITE, 0.3f);

	LoadMap("Assets/MapData/red_map_data.tmx");

	CreateBall();

	CreatePaddles();

	return true;
}

update_status ModuleGame::Update()
{
	RepositionCamera();
	MovePaddles();

	if (IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::SELECT))) {
		StartFadeIn(App->scene_highScore, WHITE, 0.3f);
	}

	

	if (IsKeyPressed(KEY_P)) {
		ballBody->ApplyLinearImpulseToCenter({ 0,450 }, true);
	}

	if (IsKeyPressed(KEY_R)) {
		ballBody->SetTransform({ 43, 68 },0);
	}

	
	

	Rectangle rectBackground = { 0,0,191,278 };
	App->renderer->Draw(*map_texture, 0, 0, &rectBackground, WHITE);

	paddleLeft_animator->Update();
	paddleLeft_animator->Animate(51,245,false);

	paddleRight_animator->Update();
	paddleRight_animator->Animate(160-75, 245,true);

	UI->Render();

	ModuleScene::FadeUpdate();

	return UPDATE_CONTINUE;
}



void ModuleGame::RepositionCamera()
{

	if (ballBody->GetPosition().x > 160/ SCREEN_SIZE) {
		App->renderer->camera.offset.x = -31 * SCREEN_SIZE;
	}
	else {
		App->renderer->camera.offset.x = 0;
	}

	if (ballBody->GetPosition().y > 135/SCREEN_SIZE) {
		App->renderer->camera.offset.y = -135 * SCREEN_SIZE;
	}
	else{
		App->renderer->camera.offset.y = 0;
	}
}

void ModuleGame::MovePaddles()
{
	if (paddleLeft_animator->HasAnimationFinished()) {
		paddleLeft_animator->SelectAnimation("Paddle_Idle", true);
	}

	if (paddleRight_animator->HasAnimationFinished()) {
		paddleRight_animator->SelectAnimation("Paddle_Idle", true);	
	}

	if (IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::LEFT))) {
		/// Trigger Left Paddle
		paddleLeft_animator->SelectAnimation("Paddle_Click", false);
	}

	if (IsKeyPressed(App->userPreferences->GetKeyValue(ModuleUserPreferences::RIGHT))) {
		/// Trigger Right Paddle
		paddleRight_animator->SelectAnimation("Paddle_Click", false);
	}

	
}

bool ModuleGame::CleanUp()
{
	for (const auto& objectBody : objectsBodies) {
		if(objectBody!=nullptr)
			App->physics->world->DestroyBody(objectBody);
	}
	objectsBodies.clear();

	App->renderer->camera.offset = { 0,0 };
	return true;
}

void ModuleGame::LoadMap(std::string path)
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
			chainFixtureDef.restitution = 0.8f;
			chainFixtureDef.friction = 0.3f;

			b2BodyDef bd;
			bd.type = b2_staticBody; // Set the body type to static
			bd.position.Set(x, y); // Set the body's initial position

			// Create the body
			b2Body* body = App->physics->world->CreateBody(&bd);

			// Attach the fixture to the body
			body->CreateFixture(&chainFixtureDef);

			objectsBodies.emplace_back(body);
		}

		for (pugi::xml_node objectNode = mapObjectsNode.child("object"); objectNode != NULL; objectNode = objectNode.next_sibling("object"))
		{
			///Create Map Objects
			pugi::xml_node typeNode  = objectNode.child("properties").find_child_by_attribute("property", "name", "type");
			std::string type = typeNode.attribute("value").as_string();

			float x = objectNode.attribute("x").as_float() / SCREEN_SIZE;
			float y = objectNode.attribute("y").as_float() / SCREEN_SIZE;

			if (type == "bumper") {
				b2BodyDef bumperDef;
				bumperDef.type = b2_staticBody;
				bumperDef.position.Set(x, y);
				b2Body* bumperBody = App->physics->world->CreateBody(&bumperDef);

				b2CircleShape bumperShape;
				bumperShape.m_radius = 1.3f;

				b2FixtureDef bumperFixture;
				bumperFixture.shape = &bumperShape;
				bumperFixture.density = 1.0f;
				bumperFixture.restitution = 1.3f;
				bumperBody->CreateFixture(&bumperFixture);

				objectsBodies.emplace_back(bumperBody);
			}
		}
	}
}

void ModuleGame::CreateBall()
{
	b2BodyDef ballDef;
	ballDef.type = b2_dynamicBody;
	ballDef.position.Set(43,68);
	ballBody = App->physics->world->CreateBody(&ballDef);
	ballBody->SetBullet(true);

	// Crear el collider circular de la pelota
	b2CircleShape ballShape;
	ballShape.m_radius = 1.3f;

	b2FixtureDef ballFixture;
	ballFixture.shape = &ballShape;
	ballFixture.density = 1.0f;
	ballFixture.restitution = 0.7f; // Rebote alto
	ballBody->CreateFixture(&ballFixture);


	objectsBodies.emplace_back(ballBody);
}

void ModuleGame::CreatePaddles()
{
	
}
