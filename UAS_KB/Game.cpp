#include "Game.h"
#include "DemoState.h"
#include "SplashState.h"

namespace UAS_KB
{
	Game::Game(int width, int height, std::string title)
	{
		m_data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);


		m_data->assets.LoadSoundBuffer("LOGO_SFX", LOGO_SFX);
		m_data->machine.AddState(StateRef(new SplashState(this->m_data)), true);
		std::cout << "Added Splash State" << std::endl;
		
		this->Run();
	}
	void Game::Run()
	{
		m_data->window.setFramerateLimit(60);

		float newTime, frameTime, interpolation;

		float currentTime = this-> m_clock.getElapsedTime().asSeconds();
		float accumulator = 0.0f;

		while (exit == false && this->m_data->window.isOpen())
		{
			this->m_data->machine.ProcessStateChanges();
			if (m_data->machine.StackEmpty())
			{
				exit = true;
			}
			else
			{
				newTime = this->m_clock.getElapsedTime().asSeconds();
				frameTime = newTime - currentTime;

				if (frameTime > 0.25f)
				{
					frameTime = 0.25f;
				}

				currentTime = newTime;
				accumulator += frameTime;

				while (accumulator >= dt)
				{
					this->m_data->machine.GetActiveState()->VHandleInput();
					this->m_data->machine.GetActiveState()->VUpdate(dt);

					accumulator -= dt;
				}

				interpolation = accumulator / dt;
				this->m_data->machine.GetActiveState()->VDraw(interpolation);
			}			
		}	
		CleanUp();
	}
		
	void Game::CleanUp()
	{
		if (exit)
		{
			m_data->window.close();
			printf("Signal exit");
		}
		else if (exit == false)
		{
			printf("window close exit");
		}
		else
		{
			printf("Unknown exit");
		}
	}
}

