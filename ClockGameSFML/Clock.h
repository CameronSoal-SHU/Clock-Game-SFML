#pragma once
#include <string>
#include <assert.h>

#include "SFML/Graphics.hpp"
#include "GameData.h"
#include "Time.h"

/*
Clock class designed to simulate and replicate a real-life (24hr) clock
on-screen.
*/
class Clock {
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
	virtual void Update();
	/* Called after Update */
	virtual void Draw();

	unsigned GetHours() const;
	unsigned GetMins() const;
	unsigned GetSecs() const;
	/* <return> Time in total seconds after 00:00:00 </return> */
	unsigned GetTimeInSecs() const;

	/* <return>Returns the current time in a formatted string format</return>*/
	std::string GetTimeFormatted() const;

	virtual void SetPosition(const sf::Vector2<float>& position);
private:
	// Store textures
	sf::Texture m_txtrClockFace;
	sf::Texture m_txtrClockHands;

	// Store sprites
	sf::Sprite m_sprClockFace;
	sf::Sprite m_sprClockHourHand;
	sf::Sprite m_sprClockMinHand;
protected:
	/* Store time in hours, minutes and seconds in protected scope (Should NEVER be externally changed unless by derived class) */
	unsigned m_hrs;
	unsigned m_mins;
	unsigned m_secs;
	unsigned m_totSecs;	// Total seconds after midnight (00:00:00)

	/* Used to count every second to prevent strange behaviour with deltaTime slowdowns */
	float m_secDelay = 0.f;

	virtual void SetUpClockSprite();
};

