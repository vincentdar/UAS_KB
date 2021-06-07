#pragma once
#include "IState.h"
#include "Game.h"
#include <SFML/Graphics.hpp>
#include "Hero.h"

namespace UAS_KB
{
	class DemoState : public IState
	{
	private:
		sf::Clock m_clock;
		sf::Sprite m_background;
		GameDataRef m_data;

		Hero m_hero;
	public:
		DemoState(GameDataRef data);
		virtual void VInit();
		virtual void VDraw(float dt);
		virtual void VHandleInput();
		virtual void VUpdate(float dt);
		virtual void VResume();
		virtual void VPause();
		virtual void VExit();

	};
	
}


