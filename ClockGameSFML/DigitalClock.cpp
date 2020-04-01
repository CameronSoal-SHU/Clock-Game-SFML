#include "DigitalClock.h"
#include "GameData.h"

DigitalClock::DigitalClock() 
	: DigitalClock::Clock() {
	SetUpClockSprite();
}

DigitalClock::DigitalClock(const Clock& clock) 
	: DigitalClock::Clock(clock) {
	SetUpClockSprite();
}

DigitalClock::DigitalClock(const unsigned hrs, const unsigned mins, const unsigned secs)
	: DigitalClock::Clock(hrs, mins, secs) {
	SetUpClockSprite();
}

DigitalClock::DigitalClock(const unsigned secs)
	: DigitalClock::Clock(secs) {
	SetUpClockSprite();
}

void DigitalClock::Update() {
	/* Pull new formatted time every frame every second */
	if (!(m_secDelay < 1.f))
		m_txtClockDisplay.setString(GetTimeFormatted());
	Clock::Update();
}

void DigitalClock::Draw() {
	GameData::ptrRenderWindow->draw(m_sprDigiClockBG);
	GameData::ptrRenderWindow->draw(m_txtClockDisplay);
}

void DigitalClock::SetPosition(const sf::Vector2<float>& newPos) {
	// Local bounds of m_txtClockDisplay to centre text inside background sprite
	const sf::FloatRect textRect = m_txtClockDisplay.getLocalBounds();

	m_sprDigiClockBG.setPosition(newPos);
	/* Aligns display text to be in the centre of the background display */
	m_txtClockDisplay.setOrigin(sf::Vector2<float>(textRect.left + (textRect.width / 2.f),
		textRect.top + (textRect.height / 2.f)));
	m_txtClockDisplay.setPosition(m_sprDigiClockBG.getPosition());
}

void DigitalClock::SetUpClockSprite() {
	assert(m_txtrDigiClockBG.loadFromFile("../Assets/Textures/digital_clock.png"));

	const sf::Vector2<int> digiClockRectPos(0, 0), digiClockRectSize(512, 347);		// Digital clock sprite rect info
	const sf::Vector2<float> digiClockScale(0.9f, 0.9f);							// Digital clock sprite scaling

	// Set up clock display background sprite
	m_sprDigiClockBG.setTexture(m_txtrDigiClockBG);
	m_sprDigiClockBG.setTextureRect(sf::Rect<int>(digiClockRectPos, digiClockRectSize));
	m_sprDigiClockBG.setOrigin(sf::Vector2<float>(digiClockRectSize.x / 2.f, digiClockRectSize.y / 2.f));
	m_sprDigiClockBG.setScale(digiClockScale);
	
	// Set up digital clock display text
	m_txtClockDisplay = sf::Text(GetTimeFormatted(), GameData::digitalFont, 96);
}