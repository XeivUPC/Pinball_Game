#include "TextureManager.hpp"

TextureManager::TextureManager() {

}
Texture2D* TextureManager::GetTexture(const char* textureID)
{
	if (!IsTextureLoaded(textureID))
	{
		printf("Sound File Not Loaded");
		return nullptr;
	}
    return &textureData[textureID];
}

void TextureManager::CreateTexture(const char* path, const char* textureID)
{
	if (IsTextureLoaded(textureID))
	{
		printf("Texture File Already Loaded");
		return;
	}


	textureData[textureID] = LoadTexture(path);
}

void TextureManager::DeleteTexture(const char* textureID)
{
	if (!IsTextureLoaded(textureID))
	{
		printf("Texture File Not Loaded");
		return;
	}
	UnloadTexture(textureData[textureID]);
	textureData.erase(textureID);
}

TextureManager::~TextureManager()
{
	for (; textureData.size() != 0;)
	{
		DeleteTexture(textureData.begin()->first);
	}
	textureData.clear();
}

bool TextureManager::IsTextureLoaded(const char* textureID)
{
    return textureData.find(textureID) != textureData.end();
}
