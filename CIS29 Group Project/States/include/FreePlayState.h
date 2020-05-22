#pragma once

#include "GameState.h"

enum level { TOP = 0, MIDDLE, BOTTOM };
enum obsticle { MEDIUM = 0, LARGE, SMALL};

class FreePlayState :
	public GameState
{
private:
	// Variables
	std::random_device randomDevice;

	sf::Clock GameClock;
	sf::Clock spawnClock;
	bool readyToSpawn;

	// Initializers
	void initializeVariables();

	// Functions
	std::pair<short, short> setObsticleStates();
	bool checkForSpawn();
	void updateSpawnClock();
	void spawnObsticle(std::pair<short, short> obsticleStats);
public:
	FreePlayState(sf::RenderWindow* renderWindow, std::stack<State*>* states);
	~FreePlayState();

	// Functions
	
	void updateState(const float& deltaTime);
};

