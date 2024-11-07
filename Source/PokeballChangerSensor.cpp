#include "PokeballChangerSensor.h"
#include "Box2DFactory.h"
#include "Application.h"
#include "ModulePhysics.h"

PokeballChangerSensor::PokeballChangerSensor(ModuleGame* gameAt, b2Vec2 position, float width, float height, float angle, int variant) : MapSensor(gameAt, position, width, height, angle)
{
	gameAt->App->texture->CreateTexture("Assets/pokeball_changer_sensor.png", "pokeball_changer_sensor");
	texture = gameAt->App->texture->GetTexture("pokeball_changer_sensor");

	animator = new Animator(gameAt->App);

	AnimationData pokeballSensorUnactive = AnimationData("Pokeball_Sensor_Unactive");
	pokeballSensorUnactive.AddSprite(Sprite{ texture,{0, (float)variant}, {8,16} });

	AnimationData pokeballSensorActive = AnimationData("Pokeball_Sensor_Active");
	pokeballSensorActive.AddSprite(Sprite{ texture,{1, (float)variant}, {8,16} });

	animator->AddAnimation(pokeballSensorUnactive);
	animator->AddAnimation(pokeballSensorActive);
	animator->SetSpeed(0.25f);
	animator->SelectAnimation("Pokeball_Sensor_Unactive", true);
}

PokeballChangerSensor::~PokeballChangerSensor()
{
}

update_status PokeballChangerSensor::Update()
{
	animator->Update();
	animator->Animate((int)(body->GetPosition().x * SCREEN_SIZE - 9), (int)(body->GetPosition().y * SCREEN_SIZE - 9), true);
	return UPDATE_CONTINUE;
}

bool PokeballChangerSensor::CleanUp()
{
	gameAt->App->physics->world->DestroyBody(body);

	return true;
}

void PokeballChangerSensor::OnActivation()
{

}
