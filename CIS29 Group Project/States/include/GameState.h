#pragma once

#include "State.h"
#include "PauseState.h"
#include "Obstacle.h"
#include "Player.h"

enum type { OBSTICLE = 0, COIN };
enum obsticle { MEDIUM = 0, LARGE, SMALL };

class GameState :
	public State
{
protected:
	float speed;
	float frequency;

	PauseState pauseState;
	std::map<std::string, gui::Button*> buttons;
	std::map<std::string, sf::Texture> textures;
	std::deque<Object*> objects;
	Player* player;
	void togglePause();

	std::stack<State*>* states;
	sf::RectangleShape background;
	sf::Texture backgroundTexture;

	// Initializers
	void initializeBackground();
public:
	// Constructors/Destructors
	GameState(sf::RenderWindow* renderWindow, std::stack<State*>* states);
	virtual ~GameState();

	void spawnPlayer();
	void spawnObject(unsigned short level, unsigned short type);

	// Update
	void updateGUI();
	void updateInput(unsigned short keyCode);
	void updateObjects(const float& deltaTime);

	// Render
	void renderState(sf::RenderTarget* renderTarget = nullptr);
};