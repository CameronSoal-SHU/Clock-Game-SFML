#pragma once
#include <string>
#include <assert.h>

#include "SFML/Graphics.hpp"

/*
Clock class designed to simulate and replicate a real-life (24hr) clock
on-screen.
*/
class Clock
{
public:
	/* Constructors to initialise clocks
	(default 00:00:00)
	<param "hrs">Initial hours</param>
	<param "mins">Initial minutes</param>
	<param "secs">Initial seconds</param>
	*/
	Clock();
	Clock(const Clock& clock);
	Clock(const unsigned hrs, const unsigned mins, const unsigned secs);
	/* Initialise clock by seconds past midnight */
	Clock(const unsigned secs);

	/* Called every frame */
	void virtual Update();
	/* Called after Update */
	void virtual Draw();

	/* <return>Time in total seconds after 00:00:00</return> */
	unsigned GetTimeInSecs();
	unsigned GetHours();
	unsigned GetMins();
	unsigned GetSecs();

	/* <return>Returns the current time in a formatted string format</return>*/
	std::string GetTimeFormatted();

	void virtual SetPosition(const sf::Vector2<float>& position);
private:
	// Store textures
	sf::Texture m_txtrClockFace;
	sf::Texture m_txtrClockHands;

	// Store sprites
	sf::Sprite m_sprClockFace;
	sf::Sprite m_sprClockHourHand;
	sf::Sprite m_sprClockMinHand;
protected:
	/* Privately store time in hours, minutes and seconds (Should NEVER be externally changed) */
	unsigned m_hrs;
	unsigned m_mins;
	unsigned m_secs;
	unsigned m_totSeconds;	// Total seconds since midnight (00:00:00)

	/* Used to count every second to prevent strange behaviour with deltaTime slowdowns */
	float m_secDelay = 0.f;

	void SetUpClockSprite();
};

