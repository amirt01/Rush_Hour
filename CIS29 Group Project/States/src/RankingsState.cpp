#include "stdafx.h"
#include "RankingsState.h"

void RankingsState::initializeBackground()
{
	background.setSize(sf::Vector2f(static_cast<float>(renderWindow->getSize().x),
		static_cast<float>(renderWindow->getSize().y)));
	background.setFillColor(sf::Color(55, 148, 110, 255));
}

void RankingsState::initializeGUI()
{
	buttons["EXIT_STATE"] = new gui::Button(220, 450, 150, 50,
		&fonts->at("DOSIS-BOLD"), "Back",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
}

RankingsState::RankingsState(sf::RenderWindow* renderWindow, std::stack<State*>* states,
	std::unordered_map<std::string, sf::Texture>* textures,
	std::unordered_map<std::string, sf::Font>* fonts,
	std::unordered_map<std::string, sf::SoundBuffer>* soundBuffers,
	Leaderboard* leaderboard)
	: State(renderWindow, states, textures, fonts, soundBuffers), leaderboard(leaderboard)
{
	initializeBackground();
	initializeGUI();
}

RankingsState::~RankingsState()
{
	auto it = buttons.begin();
	for (it = buttons.begin(); it != buttons.end(); ++it)
	{
		delete it->second;
	}
}

void RankingsState::updateMouseButtons(const sf::Mouse::Button& button)
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
void RankingsState::updateKeyboard(const sf::Keyboard::Key& keyCode)
{
	if (sf::Keyboard::Key::Escape == keyCode)
		quitState();
}

void RankingsState::updateGUI(const float& deltaTime)
{
	/*Updates all the GUI elements in the state and handles their functionality*/
	// Buttons
	for (auto& it : buttons)
	{
		it.second->updateColor(mousePosView);
	}

	//Quit This Game
	if (buttons["EXIT_STATE"]->getIsActivated())
	{
		quitState();
	}
}

void RankingsState::updateState(const float& deltaTime)
{
	updateMousePositions();
	updateGUI(deltaTime);
}

// Render
void RankingsState::renerGUI(sf::RenderTarget* renderTarget)
{
	for (auto& it : buttons)
	{
		it.second->draw(*renderTarget);
	}
}

void RankingsState::renderState(sf::RenderTarget* renderTarget)
{
	if (!renderTarget)
		renderTarget = renderWindow;

	sf::Text title("Rankings", fonts->at("DOSIS-BOLD"));
	title.setCharacterSize(128);
	title.setStyle(sf::Text::Bold);
	title.setFillColor(sf::Color::White);

	sf::RenderStates renderStates;

	renderTarget->draw(background);
	renderTarget->draw(title, renderStates.transform.translate(sf::Vector2f(renderTarget->getSize().x / 2.f -
		title.getGlobalBounds().width / 2.f, 0.f)));
	renderTarget->draw(*leaderboard);
	renerGUI(renderTarget);
}