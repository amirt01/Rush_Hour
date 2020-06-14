#include "stdafx.h"
#include "MainMenuState.h"
#include "FreePlayState.h"
#include "SettingsState.h"
#include "Level.h"
#include "LevelEditor.h"
#include "RankingsState.h"
#include "TutorialState.h"

// Initializers
void MainMenuState::initializeGUI()
{
	buttons["FREE_PLAY"] = std::make_unique<gui::Button>(220, 250, 150, 50,
		&fonts->at("DOSIS-BOLD"), &soundBuffers->at("CLICK"), "Free Play",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	buttons["LEVEL_1"] = std::make_unique<gui::Button>(520, 250, 150, 50,
		&fonts->at("DOSIS-BOLD"), &soundBuffers->at("CLICK"), "Level 1",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	buttons["LEVEL_2"] = std::make_unique<gui::Button>(520, 350, 150, 50,
		&fonts->at("DOSIS-BOLD"), &soundBuffers->at("CLICK"), "Level 2",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	buttons["LEVEL_3"] = std::make_unique<gui::Button>(520, 450, 150, 50,
		&fonts->at("DOSIS-BOLD"), &soundBuffers->at("CLICK"), "Level 3",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
	/*
	buttons["LEVEL_4"] = new gui::Button(720, 250, 150, 50,
		&font, "Level 4",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	buttons["LEVEL_5"] = new gui::Button(720, 350, 150, 50,
		&font, "Level 5",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	buttons["LEVEL_6"] = new gui::Button(720, 450, 150, 50,
		&font, "Level 6",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	buttons["LEVEL_7"] = new gui::Button(920, 250, 150, 50,
		&font, "Level 7",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	buttons["LEVEL_8"] = new gui::Button(920, 350, 150, 50,
		&font, "Level 8",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	buttons["LEVEL_9"] = new gui::Button(920, 450, 150, 50,
		&font, "Level 9",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
	*/
	buttons["RANKGINGS_STATE"] = std::make_unique<gui::Button>(220, 350, 150, 50,
		&fonts->at("DOSIS-BOLD"), &soundBuffers->at("CLICK"), "Rankings",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	buttons["TUTORIAL_STATE"] = std::make_unique<gui::Button>(920, 450, 150, 50,
		&fonts->at("DOSIS-BOLD"), &soundBuffers->at("CLICK"), "Tutorial",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	buttons["EXIT_STATE"] = std::make_unique<gui::Button>(220, 450, 150, 50,
		&fonts->at("DOSIS-BOLD"), &soundBuffers->at("CLICK"), "Quit",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
}

// Constructors/Destructors
MainMenuState::MainMenuState(std::shared_ptr<sf::RenderWindow> renderWindow, std::stack<std::unique_ptr<State>>* states,
	std::unordered_map<std::string, sf::Texture>* textures,
	std::unordered_map<std::string, sf::Font>* fonts,
	std::unordered_map<std::string, sf::SoundBuffer>* soundBuffers,
	Leaderboard* leaderboard, GameStats* gameStats)
	: State(renderWindow, states, textures, fonts, soundBuffers), leaderboard(leaderboard), gameStats(gameStats)
{
	initializeGUI();

	background.setSize(sf::Vector2f(static_cast<float>(renderWindow->getSize().x),
		static_cast<float>(renderWindow->getSize().y)));

	background.setFillColor(sf::Color(55, 148, 110, 255));
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::updateMouseWheel(const short& mouseDelta)
{
	// Any Unique Pause State Mouse Wheel Input
}

// Functions

// Update
void MainMenuState::updateKeyboard(const sf::Keyboard::Key& keyCode)
{
	if (sf::Keyboard::Key::G == keyCode)
		states->push(std::make_unique<FreePlayState>(renderWindow, states, textures, fonts, soundBuffers, leaderboard, gameStats));
}

void MainMenuState::updateMouseButtons(const sf::Mouse::Button& button)
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

void MainMenuState::updateGUI()
{
	// Updates all the buttons in the state and handles their functionality
	for (auto& it : buttons)
	{
		it.second->updateColor(mousePosView);
	}

	if (buttons["FREE_PLAY"]->getIsActivated())
		states->push(std::make_unique<FreePlayState>(renderWindow, states, textures, fonts, soundBuffers, leaderboard, gameStats));
	if (buttons["LEVEL_1"]->getIsActivated())
		states->push(std::make_unique<Level>(renderWindow, "Config/level1.bin", states, textures, fonts, soundBuffers, leaderboard, gameStats));
	if (buttons["LEVEL_2"]->getIsActivated())
		states->push(std::make_unique<Level>(renderWindow, "Config/level2.bin", states, textures, fonts, soundBuffers, leaderboard, gameStats));
	if (buttons["LEVEL_3"]->getIsActivated())
		states->push(std::make_unique<Level>(renderWindow, "Config/level3.bin", states, textures, fonts, soundBuffers, leaderboard, gameStats));
	if (buttons["RANKGINGS_STATE"]->getIsActivated())
		states->push(std::make_unique<RankingsState>(renderWindow, states, textures, fonts, soundBuffers, leaderboard));
	if (buttons["TUTORIAL_STATE"]->getIsActivated())
		states->push(std::make_unique<TutorialState>(renderWindow, states, textures, fonts, soundBuffers));
	if (buttons["EXIT_STATE"]->getIsActivated())
	{
		using namespace std::chrono_literals; // for ms
		std::this_thread::sleep_for(51ms);
		quitState();
	}
}

void MainMenuState::updateState(const float& deltaTime)
{
	updateMousePositions();
	updateGUI();
}

// Render
void MainMenuState::renerGUI(std::shared_ptr<sf::RenderTarget> renderTarget)
{
	for (auto& it : buttons)
	{
		it.second->draw(*renderTarget);
	}
}

void MainMenuState::renderState(std::shared_ptr<sf::RenderTarget> renderTarget)
{
	//if (!renderTarget)
	//	renderTarget = renderWindow;

	sf::Text title("Rush Hour", fonts->at("DOSIS-BOLD"));
	title.setCharacterSize(128);
	title.setStyle(sf::Text::Bold);
	title.setFillColor(sf::Color::White);

	sf::RenderStates renderStates;

	renderTarget->draw(background);
	renderTarget->draw(title, renderStates.transform.translate(sf::Vector2f(renderTarget->getSize().x / 2.f -
		title.getGlobalBounds().width / 2.f, 0.f)));
	renerGUI(renderTarget);
}