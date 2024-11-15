#pragma once
#include <string>
#include <vector>
enum SPAWN_LOCATION
{
	Pallet_Town,
	Viridian_City,
	Viridian_Forest,
	Pewter_City,
	MtMoon,
	Celurean_City,
	Vermilion_City_Streets,
	Vermilion_City_Harbor,
	Rock_Tunnel,
	Lavender_Town,
	Celadon_City,
	Bike_Path,
	Saffron_City,
	Fuchsia_City,
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
	std::vector<int> redMapLocations;
	std::vector<int> blueMapLocations;
	Pokemon(int ID, bool discovered, bool captured, std::string weight, std::string height, int preevolutionIndex, int overworldIndex, const std::vector<std::string>& Names, const std::vector<int>& RedMapLocations, const std::vector<int>& BlueMapLocations)
		: ID(ID), discovered(discovered), captured(captured), weight(weight), height(height), preevolutionIndex(preevolutionIndex), overworldIndex(overworldIndex), Names(Names), redMapLocations(RedMapLocations), blueMapLocations(BlueMapLocations)
	{
	}
};