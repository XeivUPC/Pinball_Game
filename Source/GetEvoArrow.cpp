#include "GetEvoArrow.h"
#include "Application.h"

GetEvoArrow::GetEvoArrow(ModuleGame* gameAt, b2Vec2 position, int order, int type, int variant) : MapArrow(gameAt, position)
{
	gameAt->AddObject(this);

	this->variant = variant;
	this->order = order;

	gameAt->App->texture->CreateTexture("Assets/get_evo_arrows.png", "get_evo_arrows");
	texture = gameAt->App->texture->GetTexture("get_evo_arrows");

	animator = new Animator(gameAt->App);

	AnimationData arrowUnactive = AnimationData("Arrow_Unactive");
	arrowUnactive.AddSprite(Sprite{ texture,{0, (float)2 * variant + type}, {16,16} });

	AnimationData arrowActive = AnimationData("Arrow_Active");
	arrowActive.AddSprite(Sprite{ texture,{(float)1 + order, (float)2 * variant + type}, {16,16} });

	AnimationData arrowTwinkle = AnimationData("Arrow_Twinkle");
	arrowTwinkle.AddSprite(Sprite{ texture,{0, (float)2 * variant + type}, {16,16} });
	arrowTwinkle.AddSprite(Sprite{ texture,{(float)1 + order, (float)2 * variant + type}, {16,16} });

	animator->AddAnimation(arrowUnactive);
	animator->AddAnimation(arrowActive);
	animator->AddAnimation(arrowTwinkle);
	animator->SetSpeed(0.25f);
	animator->SelectAnimation("Arrow_Unactive", true);
}

GetEvoArrow::~GetEvoArrow()
{
}

update_status GetEvoArrow::Update()
{
	return UPDATE_CONTINUE;
}

bool GetEvoArrow::CleanUp()
{
	return true;
}

void GetEvoArrow::Activate()
{
	animator->SelectAnimation("Arrow_Active", true);
}

void GetEvoArrow::Desactivate()
{
	animator->SelectAnimation("Arrow_Unactive", true);
}

void GetEvoArrow::Twinkle()
{
	animator->SelectAnimation("Arrow_Twinkle", true);
}

int GetEvoArrow::GetOrder() const
{
	return order;
}
