#pragma once

/*
Used to simulate a dice that can return 
and store a random number between 1 and 6
*/
class Dice
{
public:
	/* 
	Default constructor that automatically seeds with srand()
	<param "rollDelay"> Optional arg to set a delay on rolling the dice </param>
	*/
	Dice();
	Dice(float rollDelay);

	/* Generates a random number between 1 and 6, stores that value, and returns it */
	unsigned RollDice();
	/* Public accessor for m_dieResult */
	unsigned GetResult() const;

	/* Sets rollDurRemaining back to m_dieRollDur */
	void ResetRollDelay();

	float rollDurRemaining;
private:
	unsigned m_dieResult;
	float m_dieRollDur;
};

