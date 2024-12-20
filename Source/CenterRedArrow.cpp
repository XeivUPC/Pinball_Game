#include "CenterRedArrow.h"
#include "Application.h"

CenterRedArrow::CenterRedArrow(ModuleGame* gameAt, b2Vec2 position, int order) : MapArrow(gameAt, position)
{
	gameAt->AddObject(this);

	this->order = order;
	this->position = position;

	gameAt->App->texture->CreateTexture("Assets/center_red_arrows.png", "center_red_arrows");
	texture = gameAt->App->texture->GetTexture("center_red_arrows");

	animator = new Animator(gameAt->App);

	AnimationData unactive = AnimationData("Arrow_Unactive");
	unactive.AddSprite(Sprite{ texture,{(float)order, 0}, {16,16} });

	AnimationData active = AnimationData("Arrow_Active");
	active.AddSprite(Sprite{ texture,{(float)order, 2}, {16,16} });

	AnimationData twinkle = AnimationData("Arrow_Twinkle");
	twinkle.AddSprite(Sprite{ texture,{(float)order, 0}, {16,16} });
	twinkle.AddSprite(Sprite{ texture,{(float)order, 1}, {16,16} });

	animator->AddAnimation(unactive);
	animator->AddAnimation(active);
	animator->AddAnimation(twinkle);
	animator->SetSpeed(0.25f);
	animator->SelectAnimation("Arrow_Unactive", true);

}

CenterRedArrow::~CenterRedArrow()
{
}

update_status CenterRedArrow::Update()
{
	if (active) {
		if (twinkle) {
			animator->SelectAnimation("Arrow_Twinkle", true);
		}
		else {
			animator->SelectAnimation("Arrow_Active", true);
		}
	}
	else {
		animator->SelectAnimation("Arrow_Unactive", true);
	}

	animator->Update();
	animator->Animate((int)(position.x * SCREEN_SIZE), (int)(position.y * SCREEN_SIZE), false);
	return UPDATE_CONTINUE;
}

bool CenterRedArrow::CleanUp()
{
	if (animator != nullptr) {
		delete animator;
		animator = nullptr;
	}
	return true;
}

void CenterRedArrow::Activate()
{
	active = true;
}

void CenterRedArrow::Desactivate()
{
	active = false;
}

void CenterRedArrow::Twinkle()
{
	twinkle = true;
}

int CenterRedArrow::GetOrder() const
{
	return order;
}
