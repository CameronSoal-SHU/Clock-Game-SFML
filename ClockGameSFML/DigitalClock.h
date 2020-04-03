#pragma once
#include "Clock.h"

/* 
Digital representation of an analogue clock to show time.
*/
class DigitalClock : public Clock {
public:
	/* Constructors to initialise clocks (calls base constructors)
	(default 00:00:00)
	<param "hrs">Initial hours</param>
	<param "mins">Initial minutes</param>
	<param "secs">Initial seconds</param>
	*/
	DigitalClock();
	DigitalClock(const Clock& clock);
	DigitalClock(const unsigned hrs, const unsigned mins, const unsigned secs);
	/* Initialise clock by seconds past midnight */
	DigitalClock(const unsigned secs);

	/* 
	Called every frame to update clock data
	(Also calls base Update)
	*/
	void Update();
	/* Called after update to display clock sprite and display on screen */
	void Draw();

	/* 
	Sets the position of the entire digital clock (background + text display) 
	<param "newPos">New position of digital clock</param>
	*/
	void SetPosition(const sf::Vector2<float>& newPos);
private:
	/* Hold the sprite info of the digital clocks background */
	sf::Texture m_txtrDigiClockBG;
	sf::Sprite m_sprDigiClockBG;
	/* Clock display to show the time */
	sf::Text m_txtClockDisplay;

	/* Assigns textures and sets up display text for digital clock */
	void SetUpClockSprite();
};

