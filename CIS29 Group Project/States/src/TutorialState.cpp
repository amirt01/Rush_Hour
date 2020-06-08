#include "stdafx.h"
#include "TutorialState.h"
#include "MainMenuState.h"
#include "FreePlayState.h"
#include "SettingsState.h"
#include "Level.h"

// Initializers
void TutorialState::initializeGUI()
{
	buttons["MAINMENU_STATE"] = new gui::Button(220, 225, 150, 50,
		&fonts->at("DOSIS-BOLD"), "Main Menu",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
}

// Constructors/Destructors
TutorialState::TutorialState(sf::RenderWindow* renderWindow, std::stack<State*>* states,
	std::unordered_map<std::string, sf::Texture>* textures,
	std::unordered_map<std::string, sf::Font>* fonts,
	std::unordered_map<std::string, sf::SoundBuffer>* soundBuffers)
	: State(renderWindow, states, textures, fonts, soundBuffers)
{
	initializeGUI();

	background.setSize(sf::Vector2f(static_cast<float>(renderWindow->getSize().x),
		static_cast<float>(renderWindow->getSize().y)));

	background.setTexture(&textures->at("TUTORIAL_BACKGROUND"));
}

TutorialState::~TutorialState()
{
	auto it = buttons.begin();
	for (it = buttons.begin(); it != buttons.end(); ++it)
	{
		delete it->second;
	}
}

void TutorialState::updateMouseButtons(const sf::Mouse::Button& button)
{
	switch (button)
	{
	case sf::Mouse::Button::Left:
		for (auto& button : buttons)
		{
			button.second->checkBounds(mousePosView);
		}
	default:
		break;
	}
}

/* Functions */
// Update
void TutorialState::updateKeyboard(const sf::Keyboard::Key& keyCode)
{
}

void TutorialState::updateMouseWheel(const short& mouseDelta)
{
}

void TutorialState::updateGUI()
{
	/*Updates all the buttons in the state and handles their functionality*/
	for (auto& it : buttons)
	{
		it.second->updateColor(mousePosView);
	}

	if (buttons["MAINMENU_STATE"]->getIsActivated())
		quitState();
}

void TutorialState::updateState(const float& deltaTime)
{
	updateMousePositions();
	updateGUI();
}

// Render
void TutorialState::renerGUI(sf::RenderTarget* renderTarget)
{
	for (auto& it : buttons)
	{
		it.second->draw(*renderTarget);
	}
}

void TutorialState::renderState(sf::RenderTarget* renderTarget)
{
	if (!renderTarget)
		renderTarget = renderWindow;

	renderTarget->draw(background);
	renerGUI(renderTarget);
}