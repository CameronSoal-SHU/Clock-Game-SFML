#include "Dice.h"
#include "RandomNumberGenerator.h"
#include "Time.h"

Dice::Dice() 
	: m_dieRollDur(0.f), rollDurRemaining(0.f) {
}

Dice::Dice(float rollDelay)
	: m_dieRollDur(rollDelay), rollDurRemaining(rollDelay) {
}

unsigned Dice::RollDice() {
	// Generate a random number between 1 and 6
	m_dieResult = RandomNumberGenerator::GenerateRandomUnsigned(1, 6);
	return m_dieResult;
}

unsigned Dice::GetResult() const {
	return m_dieResult;
}

void Dice::ResetRollDelay() {
	rollDurRemaining = m_dieRollDur;
}