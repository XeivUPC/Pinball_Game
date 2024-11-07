#pragma once
#include <string>
#include <vector>
enum SPAWN_LOCATION
{
	Pallet_Town,
	Viridian_Forest,
	Pewter_City,
	Celurean_City,
	Vermilion_City,
	Rock_Tunnel,
	Lavender_Town,
	Cycling_Road,
	Safari_Zone,
	Seafoam_Islands,
	Cinnabar_Island,
	Indigo_Plateau,
};

class Pokemon
{
public:
	int ID;
	bool discovered, captured;
	std::string weight, height;
	int preevolutionIndex;
	int overworldIndex;
	std::vector<std::string> Names;
	std::vector<int> RedMapLocations;
	std::vector<int> BlueMapLocations;
	Pokemon(int ID, bool discovered, bool captured, std::string weight, std::string height, int preevolutionIndex, int overworldIndex, const std::vector<std::string>& Names, const std::vector<int>& RedMapLocations, const std::vector<int>& BlueMapLocations)
		: ID(ID), discovered(discovered), captured(captured), weight(weight), height(height), preevolutionIndex(preevolutionIndex), overworldIndex(overworldIndex), Names(Names), RedMapLocations(RedMapLocations), BlueMapLocations(BlueMapLocations)
	{
	}
};