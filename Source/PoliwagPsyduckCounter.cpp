#include "PoliwagPsyduckCounter.h"
#include "Application.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "ModuleUserPreferences.h"

PoliwagPsyduckCounter::PoliwagPsyduckCounter(ModuleGame* gameAt, b2Vec2 position, Bumper* bumperToTrack, bool flip) : MapObject(gameAt)
{
	gameAt->AddObject(this);

	this->flip = flip;
	this->bumperToTrack = bumperToTrack;

	gameAt->App->texture->CreateTexture("Assets/map_poliwagCounter.png", "map_poliwagCounter");
	map_poliwagCounter = gameAt->App->texture->GetTexture("map_poliwagCounter");


	map_poliwagCounter_animator = new Animator(gameAt->App);

	AnimationData zeroHitAnimPoliwag = AnimationData("ZeroHitsPoliwag");
	zeroHitAnimPoliwag.AddSprite(Sprite{ map_poliwagCounter,{0, 0}, {24,32} });

	AnimationData oneHitAnimPoliwag = AnimationData("OneHitsPoliwag");
	oneHitAnimPoliwag.AddSprite(Sprite{ map_poliwagCounter,{1, 0}, {24,32} });
	oneHitAnimPoliwag.AddSprite(Sprite{ map_poliwagCounter,{2, 0}, {24,32} });
	oneHitAnimPoliwag.AddSprite(Sprite{ map_poliwagCounter,{1, 0}, {24,32} });

	AnimationData twoHitAnimPoliwag = AnimationData("TwoHitsPoliwag");
	twoHitAnimPoliwag.AddSprite(Sprite{ map_poliwagCounter,{3, 0}, {24,32} });
	twoHitAnimPoliwag.AddSprite(Sprite{ map_poliwagCounter,{4, 0}, {24,32} });
	twoHitAnimPoliwag.AddSprite(Sprite{ map_poliwagCounter,{3, 0}, {24,32} });

	AnimationData threeHitAnimPoliwag = AnimationData("ThreeHitsPoliwag");
	threeHitAnimPoliwag.AddSprite(Sprite{ map_poliwagCounter,{5, 0}, {24,32} });
	threeHitAnimPoliwag.AddSprite(Sprite{ map_poliwagCounter,{6, 0}, {24,32} });
	threeHitAnimPoliwag.AddSprite(Sprite{ map_poliwagCounter,{0, 0}, {24,32} });


	map_poliwagCounter_animator->AddAnimation(zeroHitAnimPoliwag);
	map_poliwagCounter_animator->AddAnimation(oneHitAnimPoliwag);
	map_poliwagCounter_animator->AddAnimation(twoHitAnimPoliwag);
	map_poliwagCounter_animator->AddAnimation(threeHitAnimPoliwag);
	map_poliwagCounter_animator->SetSpeed(0.5f);
	map_poliwagCounter_animator->SelectAnimation("ZeroHitsPoliwag", true);


	gameAt->App->texture->CreateTexture("Assets/map_psyduckCounter.png", "map_psyduckCounter");
	map_psyduckCounter = gameAt->App->texture->GetTexture("map_psyduckCounter");

	map_psyduckCounter_animator = new Animator(gameAt->App);

	AnimationData zeroHitAnimPsyduck = AnimationData("ZeroHitsPsyduck");
	zeroHitAnimPsyduck.AddSprite(Sprite{ map_psyduckCounter,{0, 0}, {20,24} });

	AnimationData oneHitAnimPsyduck = AnimationData("OneHitsPsyduck");
	oneHitAnimPsyduck.AddSprite(Sprite{ map_psyduckCounter,{1, 0}, {20,24} });
	oneHitAnimPsyduck.AddSprite(Sprite{ map_psyduckCounter,{2, 0}, {20,24} });

	AnimationData twoHitAnimPsyduck = AnimationData("TwoHitsPsyduck");
	twoHitAnimPsyduck.AddSprite(Sprite{ map_psyduckCounter,{3, 0}, {20,24} });
	twoHitAnimPsyduck.AddSprite(Sprite{ map_psyduckCounter,{4, 0}, {20,24} });

	AnimationData threeHitAnimPsyduck = AnimationData("ThreeHitsPsyduck");
	threeHitAnimPsyduck.AddSprite(Sprite{ map_psyduckCounter,{5, 0}, {20,24} });
	threeHitAnimPsyduck.AddSprite(Sprite{ map_psyduckCounter,{0, 0}, {20,24} });


	map_psyduckCounter_animator->AddAnimation(zeroHitAnimPsyduck);
	map_psyduckCounter_animator->AddAnimation(oneHitAnimPsyduck);
	map_psyduckCounter_animator->AddAnimation(twoHitAnimPsyduck);
	map_psyduckCounter_animator->AddAnimation(threeHitAnimPsyduck);
	map_psyduckCounter_animator->SetSpeed(2.0f);
	map_psyduckCounter_animator->SelectAnimation("ZeroHitsPsyduck", true);
}

PoliwagPsyduckCounter::~PoliwagPsyduckCounter()
{
}

update_status PoliwagPsyduckCounter::Update()
{
	int hits = bumperToTrack->GetTotalHits();

	if (!flip)
	{
		switch (hits)
		{
		case 0:

			map_poliwagCounter_animator->SelectAnimation("ZeroHitsPoliwag", false);
			break;
		case 1:
			map_poliwagCounter_animator->SelectAnimation("OneHitsPoliwag", false);
			break;
		case 2:
			map_poliwagCounter_animator->SelectAnimation("TwoHitsPoliwag", false);
			break;
		case 3:
			map_poliwagCounter_animator->SelectAnimation("ThreeHitsPoliwag", false);
			break;

		default:
			break;
		}
		map_poliwagCounter_animator->Update();

		b2Vec2 drawPos = { (flip ? 136.0f : 0.0f), 158.f };
		map_poliwagCounter_animator->Animate(drawPos.x, drawPos.y, false);
	}
	else 
	{
		switch (hits)
		{
		case 0:
			map_psyduckCounter_animator->SelectAnimation("ZeroHitsPsyduck", false);
			break;
		case 1:
			map_psyduckCounter_animator->SelectAnimation("OneHitsPsyduck", false);
			break;
		case 2:
			map_psyduckCounter_animator->SelectAnimation("TwoHitsPsyduck", false);
			break;
		case 3:
			map_psyduckCounter_animator->SelectAnimation("ThreeHitsPsyduck", false);
			break;

		default:
			break;
		}
		map_psyduckCounter_animator->Update();

		b2Vec2 drawPos = { (flip ? 138.0f : 0.0f), 166.f };
		map_psyduckCounter_animator->Animate(drawPos.x, drawPos.y, false);
	}
	
	return UPDATE_CONTINUE;
}

bool PoliwagPsyduckCounter::CleanUp()
{
	if (map_poliwagCounter_animator != nullptr) {
		delete map_poliwagCounter_animator;
		map_poliwagCounter_animator = nullptr;
	}

	if (map_psyduckCounter_animator != nullptr) {
		delete map_psyduckCounter_animator;
		map_psyduckCounter_animator = nullptr;
	}

	LOG("Unloading Poliwag/Psyduck Counter");
	return true;
}
