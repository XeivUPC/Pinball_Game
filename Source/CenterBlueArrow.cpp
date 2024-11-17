#include "CenterBlueArrow.h"
#include "Application.h"

CenterBlueArrow::CenterBlueArrow(ModuleGame* gameAt, b2Vec2 position, int order) : MapArrow(gameAt, position)
{
	gameAt->AddObject(this);

	this->order = order;
	this->position = position;

	gameAt->App->texture->CreateTexture("Assets/center_blue_arrows.png", "center_blue_arrows");
	texture = gameAt->App->texture->GetTexture("center_blue_arrows");

	animator = new Animator(gameAt->App);

	AnimationData unactive = AnimationData("Arrow_Unactive");
	unactive.AddSprite(Sprite{ texture,{(float)order, 0}, {16,16} });

	AnimationData active = AnimationData("Arrow_Active");
	active.AddSprite(Sprite{ texture,{(float)order, 2}, {16,16} });

	AnimationData topActiveTwinkle = AnimationData("Arrow_Unactive_Twinkle");
	topActiveTwinkle.AddSprite(Sprite{ texture,{(float)order, 0}, {16,16} });
	topActiveTwinkle.AddSprite(Sprite{ texture,{(float)order, 1}, {16,16} });

	AnimationData bothActiveTwinkle = AnimationData("Arrow_Active_Twinkle");
	bothActiveTwinkle.AddSprite(Sprite{ texture,{(float)order, 2}, {16,16} });
	bothActiveTwinkle.AddSprite(Sprite{ texture,{(float)order, 3}, {16,16} });

	animator->AddAnimation(unactive);
	animator->AddAnimation(active);
	animator->AddAnimation(topActiveTwinkle);
	animator->AddAnimation(bothActiveTwinkle);
	animator->SetSpeed(0.25f);
	animator->SelectAnimation("Arrow_Unactive", true);

}

CenterBlueArrow::~CenterBlueArrow()
{
}

update_status CenterBlueArrow::Update()
{
	if (botActive) {
		if (topActive) {
			animator->SelectAnimation("Arrow_Active_Twinkle", true);
		}
		else {
			animator->SelectAnimation("Arrow_Active", true);
		}
	}
	else {
		if (topActive) {
			animator->SelectAnimation("Arrow_Unactive_Twinkle", true);
		}
		else {
			animator->SelectAnimation("Arrow_Unactive", true);
		}
	}

	animator->Update();
	animator->Animate((int)(position.x * SCREEN_SIZE), (int)(position.y * SCREEN_SIZE), false);
	return UPDATE_CONTINUE;
}

bool CenterBlueArrow::CleanUp()
{
	if (animator != nullptr) {
		delete animator;
		animator = nullptr;
	}
	return true;
}

void CenterBlueArrow::ActivateTop()
{
	topActive = true;
}

void CenterBlueArrow::DesactivateTop()
{
	topActive = false;
}

void CenterBlueArrow::ActivateBot()
{
	botActive = true;
}

void CenterBlueArrow::DesactivateBot()
{
	botActive = false;
}

void CenterBlueArrow::Activate()
{
	topActive = true;
	botActive = true;
}

void CenterBlueArrow::Desactivate()
{
	topActive = false;
	botActive = false;
}

void CenterBlueArrow::Twinkle()
{
}

int CenterBlueArrow::GetOrder() const
{
	return order;
}
