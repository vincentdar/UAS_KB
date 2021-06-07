#include "SplashState.h"
#include "DemoState.h"
#include "HexGame.h"

UAS_KB::SplashState::SplashState(GameDataRef data): m_data(data)
{
}

void UAS_KB::SplashState::VInit()
{
	logo_sfx.setBuffer(m_data->assets.GetSoundBuffer("LOGO_SFX"));
	//Play Sound
	//logo_sfx.play();
	m_data->assets.LoadTexture("SFML_Logo", SFML_LOGO);

	sf_logo.setTexture(m_data->assets.GetTexture("SFML_Logo"));
	sf_logo.setScale(0.5, 0.5);
	sf_logo.setPosition(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));

	//sf_logo.setOrigin(sf::Vector2f(sf_logo.getGlobalBounds().width, sf_logo.getGlobalBounds().height));	//final
	stop_point.x = SCREEN_WIDTH/2 - sf_logo.getGlobalBounds().width / 3;
	sf_logo.setOrigin(sf::Vector2f(sf_logo.getGlobalBounds().width / 3, sf_logo.getGlobalBounds().height)); //start
	/*sf_logo.setPosition(sf::Vector2f(SCREEN_WIDTH / 2 - sf_logo.getGlobalBounds().width/2,
		SCREEN_HEIGHT / 2 - sf_logo.getGlobalBounds().height/2));*/
	
	

	rect_mask.setSize(sf::Vector2f(500.0f, 128.0f));
	rect_mask.setPosition(sf::Vector2f(sf_logo.getPosition().x + 75.f, sf_logo.getPosition().y - 50.0f));
	rect_mask.setFillColor(sf::Color(15, 0, 20));

	rect_omask.setSize(sf::Vector2f(175.0f, 175.0f));
	rect_omask.setPosition(sf::Vector2f(sf_logo.getPosition().x - 100.0f, sf_logo.getPosition().y - 80.0f));
	rect_omask.setFillColor(sf::Color(15, 0, 20, opaque));
	//m_view = m_data->window.getDefaultView();
	//m_view.zoom(0.75f);
	//m_data->window.setView(m_view);

}

void UAS_KB::SplashState::VDraw(float dt)
{
	m_data->window.clear(sf::Color(15, 0, 20));
	m_data->window.draw(sf_logo);
	m_data->window.draw(rect_mask);
	m_data->window.draw(rect_omask);
	m_data->window.display();
}

void UAS_KB::SplashState::VHandleInput()
{
	sf::Event event;
	while (m_data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			this->VExit();
			this->m_data->window.close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			this->VExit();
		}
	}
}

void UAS_KB::SplashState::VUpdate(float dt)
{
	if (m_clock.getElapsedTime().asSeconds() < 1.75f)
	{
		opaque = 255 * ( 1.0f - (m_clock.getElapsedTime().asSeconds()) / 1.75f);
		rect_omask.setFillColor(sf::Color(15, 0, 20, opaque));
	}

	if (m_clock.getElapsedTime().asSeconds() > 1.75f)
	{
		if (sf_logo.getPosition().x > stop_point.x)
		{
			sf_logo.move(sf::Vector2f(initial_speed_sf, 0.0f));
			rect_mask.move(sf::Vector2f(initial_speed_rectMask, 0.0f));
		}
	}
	
	if (m_clock.getElapsedTime().asSeconds() > 4.5f)
	{
		VExit();
	}
}

void UAS_KB::SplashState::VResume()
{
}

void UAS_KB::SplashState::VPause()
{
}

void UAS_KB::SplashState::VExit()
{
	m_data->machine.AddState(StateRef(new HexGame(this->m_data)), true);
}
