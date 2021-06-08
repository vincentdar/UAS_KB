#include "DemoState.h"
#include "HexGame.h"

namespace UAS_KB
{
	DemoState::DemoState(GameDataRef data): m_data(data) , m_hero(data)
	{
	}
	void DemoState::VInit()
	{
		m_hero.VInit();
	}
	void DemoState::VDraw(float dt)
	{
		//Logger::PrintLn("DRAWING");
		m_data->window.clear(sf::Color::Red);
		m_data->window.draw(m_hero.VGetSprite());
		m_data->window.display();
	}
	void DemoState::VHandleInput()
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
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
			{
				m_data->machine.AddState(StateRef(new HexGame(m_data)), false);			
			}
		}
		m_hero.VHandleInput();
	}
	void DemoState::VUpdate(float dt)
	{
		m_hero.VUpdate(dt);
	}
	void DemoState::VResume()
	{
	}
	void DemoState::VPause()
	{
	}
	void DemoState::VExit()
	{
		m_data->machine.RemoveState();
	}
}

