#include "HexGame.h"

namespace UAS_KB
{
	HexGame::HexGame(GameDataRef data): m_data(data)
	{
		
	}
	void HexGame::VInit()
	{
		std::cout << "Abed beb" << std::endl;
		m_data->assets.LoadTexture("HexTile", HEX_TILESET);

		tile = new HexTile(m_data);
		tile->VInit();
	}
	void HexGame::VDraw(float dt)
	{
		m_data->window.clear(sf::Color::Red);
		// Draw Disini
		m_data->window.draw(tile->VGetSprite());
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
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				tile->ClickRed();
			}
		}
		//Polling input khusus Member Variable berupa Objek misal. m_hero.HandleInput()
		tile->VHandleInput();
	}
	void HexGame::VUpdate(float dt)
	{
		tile->VUpdate(dt);
	}
	void HexGame::VResume()
	{
	}
	void HexGame::VPause()
	{
	}
	void HexGame::VExit()
	{
		std::cout << "lope u" << std::endl;
		m_data->machine.RemoveState();
	}
}