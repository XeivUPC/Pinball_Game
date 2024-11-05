#include "Bumper.h"

Bumper::Bumper(ModuleGame* gameAt, b2Vec2 position, int restitution) : MapObject(gameAt)
{
	this->restitution = restitution;
	this->position = position;
}

Bumper::~Bumper()
{

}

update_status Bumper::Update()
{
	if (sensor.OnTriggerEnter()) {
		OnHit();
	}
	return UPDATE_CONTINUE;
}

bool Bumper::CleanUp()
{
	return true;
}

int Bumper::GetTotalHits()
{
	return hitsRecieved;
}

void Bumper::ResetTotalHits()
{
	hitsRecieved = 0;
}

void Bumper::OnHit()
{
	hitsRecieved++;
}
