#include "Pikachu.h"

Pikachu::Pikachu(ModuleGame* gameAt, b2Vec2 position, float restitution) : MapObject(gameAt)
{

}

Pikachu::~Pikachu()
{

}
update_status Pikachu::Update()
{
	return UPDATE_CONTINUE;
}

bool Pikachu::CleanUp()
{
	return true;
}
