#include "MainGame.h"
#include "IOHandler.h"
#include "Time.h"
#include "RandomNumberGenerator.h" 

#include <assert.h>

// Forward declaration(s)
GameManager::game_state GameManager::gameState;
GameSettings MainGame::gameSettings;
sf::Font GameData::digitalFont;
sf::Font GameData::dSansFont;

MainGame::MainGame() 
{}

MainGame::MainGame(sf::RenderWindow& renWin) {
	GameData::ptrRenderWindow = &renWin;		// Set the reference of the render window
												// Attempt to load the fonts
	assert(GameData::dSansFont.loadFromFile("../Assets/Fonts/DroidSans.ttf"));
	assert(GameData::digitalFont.loadFromFile("../Assets/Fonts/digital-7.ttf"));

	GameManager::GetInstance().Init(this);	// Setup GameManager with reference to this
	IOHandler::inputBuffer = "0";			// Setup input buffer for pot amount input

	GenerateClocks();
}

void MainGame::TextEntered(sf::Uint32 input) {
	if (input == GameConstants::ESCAPE_KEY)
		GameData::ptrRenderWindow->close();
	else IOHandler::lastInput = input;
}

void MainGame::GenerateClocks() {
	for (unsigned i(0); i < GameConstants::CLOCK_COUNT; ++i) {
		// Initialise clocks
		m_clocks[i] = new Clock(RandomNumberGenerator::GenerateRandomUnsigned(0, 86400));
		m_clocks[i]->SetPosition({ 250.f + (350.f * i), 500.f });	// Position each clock next to eachother
	}

	// Assign digital clock to a random analogue clock and store it for validation
	m_correctClock = RandomNumberGenerator::GenerateRandomUnsigned(0, 2);
	m_digiClock = new DigitalClock(*m_clocks[m_correctClock]);
	m_digiClock->SetPosition(sf::Vector2<float>(GameConstants::SCREEN_RES_X / 2.f, 150.f));
}

void MainGame::Update() {
	switch (GameManager::GetInstance().gameState) {
	case GameManager::INIT:
		break;
	case GameManager::DISPLAY_CLOCKS:
		IOHandler::NumericInput();	// Limit user input to numbers only
		// Update all Clocks
		for (unsigned i(0); i < GameConstants::CLOCK_COUNT; ++i) {
			m_clocks[i]->Update();
		}
		m_digiClock->Update();

		if (IOHandler::lastInput == GameConstants::RETURN_KEY) {
			const unsigned playerAnswer = std::stoi(IOHandler::inputBuffer);
			if (m_inputValid = (playerAnswer > 0 && playerAnswer <= GameConstants::CLOCK_COUNT)) {
				printf_s("Input Valid!\n");
				if (playerAnswer == m_correctClock) {
					// Win!
					GameManager::GetInstance().OnStateChange(GameManager::GUESS_CORRECT);
				}
				else {
					// Lose!
					GameManager::GetInstance().OnStateChange(GameManager::GUESS_INCORRECT);
				}
			}
		}
		break;
	case GameManager::GUESS_CORRECT:
		break;
	case GameManager::GUESS_INCORRECT:
		break;
	default:	// Should never be taken
		assert(false);
		break;
	}

	// Clear last input
	IOHandler::lastInput = NULL;
}

void MainGame::Render() {
	switch (GameManager::GetInstance().gameState) {
	case GameManager::INIT:
		break;
	case GameManager::DISPLAY_CLOCKS:
		// Render each clock on screen
		m_digiClock->Draw();
		for (unsigned i(0); i < GameConstants::CLOCK_COUNT; ++i) {
			//RenderMessage(m_clocks[i]->GetTimeFormatted(), {0.f, 25.f * i});	// Debugging
			m_clocks[i]->Draw();

			RenderMessage("Current Score: " + std::to_string(m_player.GetPlayerScore()), {25.f, 10.f});
			RenderMessage("Which clock matches the digital clock? (1, 2 or 3)?: " + IOHandler::inputBuffer, {25.f, 750.f});
		}
		break;
	case GameManager::GUESS_CORRECT:
		break;
	case GameManager::GUESS_INCORRECT:
		break;
	default:	// Should never be taken
		assert(false);
		break;
	}
}

void MainGame::RenderMessage(const std::string& msg, const sf::Vector2f& pos, const sf::Font& font) {
	sf::Text message = sf::Text(msg, font);
	message.setPosition(pos);

	GameData::ptrRenderWindow->draw(message);
}