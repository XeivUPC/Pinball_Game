#pragma once
#include "ModuleGame.h"

class MapObject
{
public:
	MapObject(ModuleGame* gameAt);
	virtual ~MapObject();
	ModuleGame* GetGameAt();

	virtual update_status Update();
	virtual bool CleanUp() = 0;

private:

protected:
	ModuleGame* gameAt = nullptr;
};

