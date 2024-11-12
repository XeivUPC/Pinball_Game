#include "CentralScreen.h"
#include "ModuleRender.h"
#include "Application.h"

void CentralScreen::AddLayer(Texture* texture, Rectangle textureSection, Vector2 position)
{
	layers.push_back(ScreenLayer{ texture, textureSection, position});
}

int CentralScreen::AlreadyInVector(Texture* texture, Rectangle textureSection, Vector2 position)
{
	for (int i = 0; i < layers.size(); i++)
	{
		if (texture == layers.at(i).texture && textureSection.x == layers.at(i).rect.x && textureSection.y == layers.at(i).rect.y && textureSection.width == layers.at(i).rect.width && textureSection.height == layers.at(i).rect.height && position.x == layers.at(i).position.x && position.y == layers.at(i).position.y)
			return i;
	}
	return -1;
}

CentralScreen::CentralScreen(ModuleGame* gameAt) : MapObject(gameAt)
{
	gameAt->AddObject(this);
	basePosition.x = 56;
	basePosition.y = 166;
	renderPriority = 0;
}

CentralScreen::~CentralScreen()
{
}

void CentralScreen::RenderInScreen(Texture* texture, Rectangle textureSection, Vector2 position, std::string groupName)
{
	if (groupName != renderingName)return;
	if (AlreadyInVector(texture, textureSection, position) != -1)
	{
		for (int i = AlreadyInVector(texture, textureSection, position); i < layers.size()-1; i++)
		{
			layers.at(i) = layers.at(i + 1);
		}
	}
	AddLayer(texture, textureSection, position);
}

void CentralScreen::SetGroupPriority(std::string groupName, int priority)
{
	if (priority < renderPriority)return;
	renderingName = groupName;
	renderPriority = priority;
}

void CentralScreen::StopRenderingGroup(std::string groupName)
{
	if (groupName != renderingName)return;
	layers.clear();
	groupName = "";
	renderPriority = 0;
}

update_status CentralScreen::Update()
{
	for (int i = 0; i < layers.size(); i++)
	{
		gameAt->App->renderer->Draw(*(layers.at(i).texture), basePosition.x+layers.at(i).position.x, basePosition.y + layers.at(i).position.y, &layers.at(i).rect, WHITE);
	}
    return UPDATE_CONTINUE;
}

bool CentralScreen::CleanUp()
{
	layers.clear();
    return true;
}
