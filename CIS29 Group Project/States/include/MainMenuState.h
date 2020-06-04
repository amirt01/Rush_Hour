#pragma once

#include "State.h"
#include "GUI.h"
#include "Leaderboard.h"

class MainMenuState :
	public State
{
private:
	//Variables
	sf::RectangleShape background;
	sf::Font font;

	Leaderboard* leaderboard;

	std::map<std::string, gui::Button*> buttons;

	// Initializers
	void initializeTextures();
	void initializeFonts();
	void initializeGUI();

public:
	// Constructors/Destructors
	MainMenuState(sf::RenderWindow* renderWindow, std::stack<State*>* states, Leaderboard* leaderboard);
	virtual ~MainMenuState();

	// Update
	void updateMouseWheel(short mouseDelta);
	void updateKeyboard(unsigned short keyCode);
	void updateGUI();
	void updateState(const float& deltaTime);

	// Render
	void renerGUI(sf::RenderTarget* renderTarget);
	void renderState(sf::RenderTarget* renderTarget = nullptr);
};