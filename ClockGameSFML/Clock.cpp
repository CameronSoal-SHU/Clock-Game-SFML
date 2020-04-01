#include "Clock.h"
#include "Time.h"
#include "GameData.h"

#include <stdio.h>
#include <iomanip>

// Forward Declarations
sf::RenderWindow* GameData::ptrRenderWindow;

Clock::Clock()
	: m_hrs(0), m_mins(0), m_secs(0),
	m_totSeconds(0) {
	SetUpClockSprite();
	printf_s("Clock Initialised: %uhrs, %umins, %usecs, Seconds past midnight: %u\n", m_hrs, m_mins, m_secs, m_totSeconds);
}

Clock::Clock(const Clock& clock) {
	m_hrs = clock.m_hrs;
	m_mins = clock.m_mins;
	m_secs = clock.m_secs;
	m_totSeconds = (m_hrs * 3600) + (m_mins * 60) + (m_secs);
	SetUpClockSprite();
	printf_s("Clock Copied: %uhrs, %umins, %usecs, Seconds past midnight: %u\n", m_hrs, m_mins, m_secs, m_totSeconds);
}

Clock::Clock(const unsigned hrs, const unsigned mins, const unsigned secs)
	: m_hrs(hrs), m_mins(mins), m_secs(secs),
	m_totSeconds((hrs * 3600) + (mins * 60) + (secs)) {
	SetUpClockSprite();
	printf_s("Clock Initialised: %uhrs, %umins, %usecs, Seconds past midnight: %u\n", m_hrs, m_mins, m_secs, m_totSeconds);
}

Clock::Clock(const unsigned secs)
	: m_totSeconds(secs), 
	m_hrs((secs / 3600) % 24), m_mins((secs / 60) % 60), m_secs(secs % 60) {
	SetUpClockSprite();
	printf_s("Clock Initialised: %uhrs, %umins, %usecs, Seconds past midnight: %u\n", m_hrs, m_mins, m_secs, m_totSeconds);
}

void Clock::Update() {
	// "Tick" clock
	if (m_secDelay < 1.f) {
		m_secDelay += Time::GetDeltaTime();
	}
	else {	// Reset second delay and increment time
		m_secDelay = 0;

		++m_totSeconds;
		if (m_totSeconds == 86400)
			m_totSeconds = 0;

		/* Rotate clock hands as time progresses */
		m_sprClockHourHand.setRotation(m_totSeconds * (360.f / 43200));
		m_sprClockMinHand.setRotation(m_totSeconds * (360.f / 3600)); 

		m_secs = m_totSeconds % 60;
		m_mins = (m_totSeconds / 60) % 60;
		m_hrs = (m_totSeconds / 3600) % 24;
	}
}

void Clock::Draw() {
	GameData::ptrRenderWindow->draw(m_sprClockFace);
	GameData::ptrRenderWindow->draw(m_sprClockHourHand);
	GameData::ptrRenderWindow->draw(m_sprClockMinHand);
}

unsigned Clock::GetTimeInSecs() {
	return m_totSeconds;
}

unsigned Clock::GetHours() {
	return m_hrs;
}

unsigned Clock::GetMins() {
	return m_mins;
}

unsigned Clock::GetSecs() {
	return m_secs;
}

std::string Clock::GetTimeFormatted()
{
	// Hours, Mins and Secs formatted to string
	std::string fHours = m_hrs > 9 ? std::to_string(m_hrs) : '0' + std::to_string(m_hrs);
	std::string fMins = m_mins > 9 ? std::to_string(m_mins) : '0' + std::to_string(m_mins);
	std::string fSecs = m_secs > 9 ? std::to_string(m_secs) : '0' + std::to_string(m_secs);

	return fHours + ":" + fMins + ":" + fSecs;
}

void Clock::SetPosition(const sf::Vector2<float>& position) {
	m_sprClockFace.setPosition(position);
	m_sprClockHourHand.setPosition(position);
	m_sprClockMinHand.setPosition(position);
}

void Clock::SetUpClockSprite() {
	// Attempt to load textures from assets folder
	assert(m_txtrClockFace.loadFromFile("../Assets/Textures/clock_face.png"));
	assert(m_txtrClockHands.loadFromFile("../Assets/Textures/clock_hands.png"));

	const sf::Vector2<int> hrRectPos(11, 139), hrRectSize(75, 342);					// Hour Hand Texture info
	const sf::Vector2<int> minRectPos(100, 5), minRectSize(47, 474);				// Minute Hand Texture info
	const sf::Vector2<float> clockScale(0.6f, 0.6f), clockHandScale(0.3f, 0.3f);	// Clock hand scales

	// Assign textures and rects to sprites
	m_sprClockFace.setTexture(m_txtrClockFace);

	const sf::Rect<int> clockFaceRect = m_sprClockFace.getTextureRect();
	m_sprClockFace.setOrigin(sf::Vector2<float>(clockFaceRect.width / 2.f, 
		clockFaceRect.height / 2.f));

	m_sprClockHourHand.setTexture(m_txtrClockHands);
	m_sprClockHourHand.setTextureRect(sf::Rect<int>(hrRectPos, hrRectSize));
	// Set origin to centre of clock hand hole at the bottom of the sprite
	m_sprClockHourHand.setOrigin(sf::Vector2<float>((hrRectSize.x) / 2.f, hrRectSize.y - 25.f));

	m_sprClockMinHand.setTexture(m_txtrClockHands);
	m_sprClockMinHand.setTextureRect(sf::Rect<int>(minRectPos, minRectSize));
	// Set origin to centre of clock hand hole at the bottom of the sprite
	m_sprClockMinHand.setOrigin(sf::Vector2<float>(((minRectSize.x) / 2.f), minRectSize.y - 23.f));

	m_sprClockFace.setScale(clockScale);
	m_sprClockHourHand.setScale(clockHandScale);
	m_sprClockMinHand.setScale(clockHandScale);
}