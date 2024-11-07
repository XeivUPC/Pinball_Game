#include "DittoColliders.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "ModuleTexture.h"

DittoColliders::DittoColliders(ModuleGame* gameAt, b2Vec2 position) : MapObject(gameAt)
{
	gameAt->AddObject(this);

	this->position = position;

	gameAt->App->texture->CreateTexture("Assets/map_ditto.png", "map_ditto");
	ditto_texture = gameAt->App->texture->GetTexture("map_ditto");


	ditto_animator = new Animator(gameAt->App);

	AnimationData dittoSmall = AnimationData("Ditto_Small");
	dittoSmall.AddSprite(Sprite{ ditto_texture,{0, 0}, {41,96} });

	AnimationData dittoBig = AnimationData("Ditto_Big");
	dittoBig.AddSprite(Sprite{ ditto_texture,{1, 0}, {41,96} });


	AnimationData dittoHide = AnimationData("Ditto_Hide");
	dittoHide.AddSprite(Sprite{ ditto_texture,{2, 0}, {41,96} });

	ditto_animator->SetSpeed(1);
	ditto_animator->AddAnimation(dittoSmall);
	ditto_animator->AddAnimation(dittoBig);
	ditto_animator->AddAnimation(dittoHide);

	SetModeData(NONE, nullptr);
	

}

DittoColliders::~DittoColliders()
{
}

update_status DittoColliders::Update()
{
	ditto_animator->Update();

	if(currentMode!=NONE)
		ditto_animator->Animate((int)(position.x * SCREEN_SIZE), (int)(position.y * SCREEN_SIZE),false);
	return UPDATE_CONTINUE;
}

bool DittoColliders::CleanUp()
{
	for (const auto& data : dittoData) {
		if (data.second == nullptr)
			continue;
		gameAt->App->physics->world->DestroyBody(data.second);
	}
	dittoData.clear();
	return true;
}

void DittoColliders::SetModeData(DittoMode mode, b2Body* collider)
{
	dittoData[mode] = collider;
}

void DittoColliders::SetMode(DittoMode mode)
{
	for (const auto& data : dittoData) {
		if (data.second == nullptr)
			continue;
		if (data.first == mode) {	
			for (b2Fixture* f = data.second->GetFixtureList(); f; f = f->GetNext())
			{
				f->SetSensor(false);
			}
		}
		else {
			for (b2Fixture* f = data.second->GetFixtureList(); f; f = f->GetNext())
			{
				f->SetSensor(true);
			}
		}
	}

	switch (mode)
	{
	case DittoColliders::Hide:
		ditto_animator->SelectAnimation("Ditto_Hide", true);
		break;
	case DittoColliders::Small:
		ditto_animator->SelectAnimation("Ditto_Small", true);
		break;
	case DittoColliders::Big:
		ditto_animator->SelectAnimation("Ditto_Big", true);
		break;
	default:
		break;
	}

	currentMode = mode;
}

DittoColliders::DittoMode DittoColliders::GetMode()
{
	return currentMode;
}
