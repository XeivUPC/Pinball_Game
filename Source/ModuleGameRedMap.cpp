#include "ModuleGameRedMap.h"
#include "ModulePhysics.h"
#include "Application.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleUserPreferences.h"
#include "ModuleKeybinds.h"
#include "GameUI.h"
#include "Box2DFactory.h"
#include <sstream>

#include "ModuleHighScore.h"

ModuleGameRedMap::ModuleGameRedMap(Application* app, bool start_enabled) : ModuleScene(app, start_enabled)
{

	
}

ModuleGameRedMap::~ModuleGameRedMap()
{
}

bool ModuleGameRedMap::Start()
{
	App->texture->CreateTexture("Assets/map_redMap.png", "map_redMap");
	map_texture = App->texture->GetTexture("map_redMap");	
	
	App->texture->CreateTexture("Assets/pokebal_defaultSize.png", "pokebal_defaultSize");
	pokeball_texture = App->texture->GetTexture("pokebal_defaultSize");

	App->texture->CreateTexture("Assets/map_paddle.png", "map_paddle");
	paddle_texture = App->texture->GetTexture("map_paddle");

	paddleLeft_animator = new Animator(App);
	paddleRight_animator = new Animator(App);

	AnimationData paddleIdle = AnimationData("Paddle_Idle");
	paddleIdle.AddSprite(Sprite{ paddle_texture,{2, 0}, {24,24} });

	AnimationData paddleClick = AnimationData("Paddle_Click");
	paddleClick.AddSprite(Sprite{ paddle_texture,{2, 0}, {24,24} });
	paddleClick.AddSprite(Sprite{ paddle_texture,{1, 0}, {24,24} });
	paddleClick.AddSprite(Sprite{ paddle_texture,{0, 0}, {24,24} });

	paddleLeft_animator->AddAnimation(paddleIdle);
	paddleLeft_animator->AddAnimation(paddleClick);
	paddleLeft_animator->SetSpeed(0.02);
	paddleLeft_animator->SelectAnimation("Paddle_Idle", true);

	paddleRight_animator->AddAnimation(paddleIdle);
	paddleRight_animator->AddAnimation(paddleClick);
	paddleRight_animator->SetSpeed(0.02);
	paddleRight_animator->SelectAnimation("Paddle_Idle", true);


	pokeball_animator = new Animator(App);
	AnimationData pokeballMove = AnimationData("Pokeball_Anim");
	pokeballMove.AddSprite(Sprite{ pokeball_texture,{0, 0}, {16,16} });
	pokeballMove.AddSprite(Sprite{ pokeball_texture,{1, 0}, {16,16} });
	pokeballMove.AddSprite(Sprite{ pokeball_texture,{2, 0}, {16,16} });
	pokeballMove.AddSprite(Sprite{ pokeball_texture,{3, 0}, {16,16} });
	pokeballMove.AddSprite(Sprite{ pokeball_texture,{4, 0}, {16,16} });
	pokeballMove.AddSprite(Sprite{ pokeball_texture,{5, 0}, {16,16} });
	pokeballMove.AddSprite(Sprite{ pokeball_texture,{6, 0}, {16,16} });
	pokeballMove.AddSprite(Sprite{ pokeball_texture,{7, 0}, {16,16} });

	pokeball_animator->SetSpeed(0);
	pokeball_animator->AddAnimation(pokeballMove);
	pokeball_animator->SelectAnimation("Pokeball_Anim", true);


	UI = new GameUI(App);

	StartFadeOut(WHITE, 0.3f);

	LoadMap("Assets/MapData/red_map_data.tmx");

	CreateBall();

	CreatePaddles();

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
		ballBody->ApplyLinearImpulseToCenter({ 0,-400 }, true);
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


	float pokeballSpeed = std::sqrt(ballBody->GetLinearVelocity().x * ballBody->GetLinearVelocity().x + ballBody->GetLinearVelocity().y * ballBody->GetLinearVelocity().y);
	pokeballSpeed = (pokeballAnimMaxSpeed / pokeballSpeed) / 100;

	if(ballBody->GetLinearVelocity().x <0)
		pokeball_animator->SetDirection(1);
	else
		pokeball_animator->SetDirection(-1);

	pokeball_animator->SetSpeed(pokeballSpeed);


	pokeball_animator->Update();
	pokeball_animator->Animate(ballBody->GetPosition().x * SCREEN_SIZE -8, ballBody->GetPosition().y * SCREEN_SIZE-8, true);

	UI->Render();

	ModuleScene::FadeUpdate();

	return UPDATE_CONTINUE;
}



void ModuleGameRedMap::RepositionCamera()
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

void ModuleGameRedMap::MovePaddles()
{

	if (IsKeyDown(App->userPreferences->GetKeyValue(ModuleUserPreferences::LEFT))) {
		/// Trigger Left Paddle
		paddleLeft_animator->SelectAnimation("Paddle_Click", false);
		leftPaddleJoint->SetMotorSpeed(40000.0f);
	}else
	{
		leftPaddleJoint->SetMotorSpeed(-40000.0f);
		paddleLeft_animator->SelectAnimation("Paddle_Idle", true);
	}

	if (IsKeyDown(App->userPreferences->GetKeyValue(ModuleUserPreferences::RIGHT))) {
		/// Trigger Right Paddle
		rightPaddleJoint->SetMotorSpeed(-40000.0f);
		paddleRight_animator->SelectAnimation("Paddle_Click", false);
		
	}
	else
	{
		rightPaddleJoint->SetMotorSpeed(40000.0f);
		paddleRight_animator->SelectAnimation("Paddle_Idle", true);
	}

	
}

bool ModuleGameRedMap::CleanUp()
{
	for (const auto& objectBody : objectsBodies) {
		if(objectBody!=nullptr)
			App->physics->world->DestroyBody(objectBody);
	}
	objectsBodies.clear();


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

void ModuleGameRedMap::CreateBall()
{
	ballBody = Box2DFactory::GetInstance().CreateCircle(App->physics->world, { 43,68 }, 1.3f);
	ballBody->GetFixtureList()[0].SetRestitution(0.5f);
	ballBody->GetFixtureList()[0].SetFriction(0);
	ballBody->GetFixtureList()[0].SetDensity(100);

	ballBody->SetBullet(true);

	objectsBodies.emplace_back(ballBody);
}

void ModuleGameRedMap::CreatePaddles()
{
	b2MassData paddleMassData;
	b2Body* bodyA = Box2DFactory::GetInstance().CreateBox(App->physics->world, { 13.9,64.4 }, 5.2f,1);
	bodyA->GetFixtureList()[0].SetDensity(100000000);
	bodyA->SetType(b2_dynamicBody); 

	b2Body* bodyB = Box2DFactory::GetInstance().CreateCircle(App->physics->world, { 13.9,64.4 },0.2);
	bodyB->SetType(b2_staticBody);

	b2RevoluteJointDef jointDef;
	b2Vec2 offset = bodyA->GetWorldCenter();

	jointDef.bodyA = bodyA;
	jointDef.bodyB = bodyB;

	jointDef.localAnchorA.Set(-2.55, 0);
	jointDef.localAnchorB.Set(0.0f, 0.0f);

	jointDef.collideConnected = false;
	jointDef.enableLimit = true;
	jointDef.lowerAngle = -0.15f * b2_pi; // -90 degrees
	jointDef.upperAngle = 0.15 * b2_pi; // 45 degrees

	jointDef.enableMotor = true;
	jointDef.maxMotorTorque = 40000.0f;
	jointDef.motorSpeed = 0.0f;

	leftPaddleJoint = (b2RevoluteJoint*)App->physics->world->CreateJoint(&jointDef);

	leftPaddleJoint->EnableMotor(true);

	objectsBodies.emplace_back(bodyA);
	objectsBodies.emplace_back(bodyB);



	paddleMassData;
	bodyA = Box2DFactory::GetInstance().CreateBox(App->physics->world, { 26.1,64.4 }, 5.2f, 1);
	bodyA->GetFixtureList()[0].SetDensity(100000000);
	bodyA->SetType(b2_dynamicBody);


	bodyB = Box2DFactory::GetInstance().CreateCircle(App->physics->world, { 26.1,64.4 }, 0.2);
	bodyB->SetType(b2_staticBody);

	jointDef;
	offset = bodyA->GetWorldCenter();

	jointDef.bodyA = bodyA;
	jointDef.bodyB = bodyB;


	jointDef.localAnchorA.Set(2.55, 0);
	jointDef.localAnchorB.Set(0.0f, 0.0f);

	jointDef.collideConnected = false;
	jointDef.enableLimit = true;
	jointDef.lowerAngle = -0.15f * b2_pi; // -90 degrees
	jointDef.upperAngle = 0.15 * b2_pi; // 45 degrees

	jointDef.enableMotor = true;
	jointDef.maxMotorTorque = 40000.0f;
	jointDef.motorSpeed = 0.0f;

	rightPaddleJoint = (b2RevoluteJoint*)App->physics->world->CreateJoint(&jointDef);

	rightPaddleJoint->EnableMotor(true);

	objectsBodies.emplace_back(bodyA);
	objectsBodies.emplace_back(bodyB);

}
