#include "DiglettCounter.h"
#include "Application.h"
#include "ModuleTexture.h"
#include "ModuleRender.h"
#include "ModuleUserPreferences.h"

DiglettCounter::DiglettCounter(ModuleGame* gameAt, b2Vec2 position, Bumper* bumperToTrack , bool flip) : MapObject(gameAt)
{
	gameAt->AddObject(this);

	this->flip = flip;
	this->bumperToTrack = bumperToTrack;

	gameAt->App->texture->CreateTexture("Assets/map_diglettCounter.png", "map_diglettCounter");
	map_diggletCounter = gameAt->App->texture->GetTexture("map_diglettCounter");


	map_diggletCounter_animator = new Animator(gameAt->App);

	AnimationData zeroHitAnim = AnimationData("ZeroHits");
	zeroHitAnim.AddSprite(Sprite{ map_diggletCounter,{0, 0}, {24,32} });
	
	AnimationData oneHitAnim = AnimationData("OneHits");
	oneHitAnim.AddSprite(Sprite{ map_diggletCounter,{1, 0}, {24,32} });

	AnimationData twoHitAnim = AnimationData("TwoHits");
	twoHitAnim.AddSprite(Sprite{ map_diggletCounter,{2, 0}, {24,32} });

	AnimationData threeHitAnim = AnimationData("ThreeHits");
	threeHitAnim.AddSprite(Sprite{ map_diggletCounter,{3, 0}, {24,32} });
	threeHitAnim.AddSprite(Sprite{ map_diggletCounter,{0, 0}, {24,32} });


	map_diggletCounter_animator->AddAnimation(zeroHitAnim);
	map_diggletCounter_animator->AddAnimation(oneHitAnim);
	map_diggletCounter_animator->AddAnimation(twoHitAnim);
	map_diggletCounter_animator->AddAnimation(threeHitAnim);
	map_diggletCounter_animator->SetSpeed(1.f);
	map_diggletCounter_animator->SelectAnimation("ZeroHits", true);

}

DiglettCounter::~DiglettCounter()
{}

update_status DiglettCounter::Update()
{
	int hits = bumperToTrack->GetTotalHits();
	switch (hits)
	{
		case 0:
			map_diggletCounter_animator->SelectAnimation("ZeroHits", true);
			break;
		case 1:
			map_diggletCounter_animator->SelectAnimation("OneHits", true);
			break;
		case 2:
			map_diggletCounter_animator->SelectAnimation("TwoHits", true);
			break;
		case 3:
			map_diggletCounter_animator->SelectAnimation("ThreeHits", false);
			break;

	default:
		break;
	}
	map_diggletCounter_animator->Update();

	b2Vec2 drawPos = {(flip ? 136.0f : 0.0f), 166.f};
	map_diggletCounter_animator->Animate((int)drawPos.x, (int)drawPos.y,flip);


	return UPDATE_CONTINUE;
}

bool DiglettCounter::CleanUp()
{
	if (map_diggletCounter_animator != nullptr) {
		delete map_diggletCounter_animator;
		map_diggletCounter_animator = nullptr;
	}

	LOG("Unloading Digglet Counter");
	return true;
}
