#include "GameManager.h"

#include <stdio.h>

// Static class variable instances
GameManager::game_state m_gameState;

//GameManager::GameManager()
//	: m_mainGamePtr(nullptr)
//{
//	OnStateChange(INIT);
//	printf_s("Game Initialised!\n");
//}

void GameManager::Init() {
	OnStateChange(game_state::DISPLAY_CLOCKS);
}

void GameManager::OnStateChange(GameManager::game_state newState) {
	if (gameState != newState) {
		printf_s("State changed to: ");

		switch (newState) {
		case game_state::INIT:
			printf_s("Init!\n");
			break;
		case game_state::DISPLAY_CLOCKS:
			printf_s("Display Clocks!\n");
			break;
		case game_state::GUESS_CORRECT:
			printf_s("Guess Correct!\n");
			break;
		case game_state::GUESS_INCORRECT:
			printf_s("Guess Incorrect!\n");
			break;
		default:
			printf_s("UNKNOWN!\n");
			break;
		}

		gameState = newState;
	}
}