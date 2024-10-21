#include "ModuleTexture.h"

ModuleTexture::ModuleTexture(Application* app, bool start_enabled) : Module(app, start_enabled) {

}

ModuleTexture::~ModuleTexture()
{

}


Texture2D* ModuleTexture::GetTexture(std::string textureID)
{
	if (!IsTextureLoaded(textureID))
	{
		printf("Sound File Not Loaded");
		return nullptr;
	}
    return &textureData[textureID];
}

void ModuleTexture::CreateTexture(std::string path, std::string textureID)
{
	if (IsTextureLoaded(textureID))
	{
		printf("Texture File Already Loaded");
		return;
	}


	textureData[textureID] = LoadTexture(path.c_str());
}

void ModuleTexture::DeleteTexture(std::string textureID)
{
	if (!IsTextureLoaded(textureID))
	{
		printf("Texture File Not Loaded");
		return;
	}
	UnloadTexture(textureData[textureID]);
	textureData.erase(textureID);
}

bool ModuleTexture::CleanUp() {
	for (; textureData.size() != 0;)
	{
		DeleteTexture(textureData.begin()->first);
	}
	textureData.clear();
	return true;
}

bool ModuleTexture::IsTextureLoaded(std::string textureID)
{
    return textureData.find(textureID) != textureData.end();
}
