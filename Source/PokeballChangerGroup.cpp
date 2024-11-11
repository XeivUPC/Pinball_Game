#include "PokeballChangerGroup.h"
#include "PokeBall.h"

PokeballChangerGroup::PokeballChangerGroup(ModuleGame* gameAt) : MapSensorGroup(gameAt)
{
	this->gameAt = gameAt;
}

PokeballChangerGroup::~PokeballChangerGroup()
{

}

update_status PokeballChangerGroup::Update()
{
	if (AllActive())
		OnAllActive();
	return UPDATE_CONTINUE;
}

bool PokeballChangerGroup::CleanUp()
{
	
	return true;
}

void PokeballChangerGroup::OnAllActive()
{
	PokeBall* pokeBall = gameAt->GetPokeball();

	if (pokeBall->GetType() != PokeBall::PokeballType::MasterBall) {
		pokeBall->SetType(PokeBall::PokeballType(pokeBall->GetType() + 1));
	}
	else {
		//give points
		gameAt->pointsCounter.Add(10000000);
	}
	DesactivateAll();
}
