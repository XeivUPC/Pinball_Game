#pragma once
#include "MapObject.h"
#include <vector>
#include <string.h>

struct ScreenLayer
{
	Texture* texture;
	Rectangle rect;
	Vector2 position;
};

class CentralScreen : public MapObject
{
private:
	int renderPriority;
	Vector2 basePosition;
	std::string renderingName;
	std::vector<ScreenLayer> layers;
	void AddLayer(Texture* texture, Rectangle textureSection, Vector2 position);
	int AlreadyInVector(Texture* texture, Rectangle textureSection, Vector2 position);
public:
	CentralScreen(ModuleGame* gameAt);
	~CentralScreen();
	void RenderInScreen(Texture* texture, Rectangle textureSection, Vector2 position, std::string groupName);
	void SetGroupPriority(std::string groupName, int priority);
	void StopRenderingGroup(std::string groupName);
	update_status Update();
	bool CleanUp() override;
};