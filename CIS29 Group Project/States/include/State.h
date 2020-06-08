#pragma once

#include "Constants.h"

class State
{
private:

protected:
	//Variables
	sf::RenderWindow* renderWindow;
	std::map<std::string, sf::Texture> textures;
	std::map<std::string, sf::SoundBuffer> soundBuffers;
	sf::Sound sounds;

	bool quit;

	std::stack<State*>* states;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	void initializeSounds();

public:
	// Constructors/Destructors
	State(sf::RenderWindow* renderWindow, std::stack<State*>* states);
	virtual ~State();

	// Sound Functions
	void playSound(std::string soundBuffer, float volume);

	// Quit State Functions
	const bool& getQuit() const;
	void quitState();

	virtual std::string name() const;

	// Update
	virtual void updateMousePositions();
	virtual void updateMouseButtons(const sf::Mouse::Button& button) = 0;
	virtual void updateMouseWheel(const short& mouseDelta) = 0;
	virtual void updateKeyboard(const sf::Keyboard::Key& keyCode) = 0;
	virtual void updateState(const float& deltaTime) = 0;

	// Render
	virtual void renderState(sf::RenderTarget* renderTarget = nullptr) = 0;
};
