#include "HexGame.h"

namespace UAS_KB
{
	HexGame::HexGame(GameDataRef data): m_data(data)
	{
	}
	void HexGame::VInit()
	{
	}
	void HexGame::VDraw(float dt)
	{
		m_data->window.clear(sf::Color::Black);
		// Draw Disini
		m_data->window.display();
	}
	void HexGame::VHandleInput()
	{
		sf::Event event;
		while (m_data->window.pollEvent(event))
		{
			//Input khusus State HexGame disini
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
		//Polling input khusus Member Variable berupa Objek misal. m_hero.HandleInput()
	}
	void HexGame::VUpdate(float dt)
	{
	}
	void HexGame::VResume()
	{
	}
	void HexGame::VPause()
	{
	}
	void HexGame::VExit()
	{
		m_data->machine.RemoveState();
	}
}