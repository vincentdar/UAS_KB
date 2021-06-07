#pragma once
#include "IState.h"
#include "Game.h"
#include <SFML/Graphics.hpp>

namespace UAS_KB
{
	class SplashState: public IState
	{
	private:
		sf::View m_view;

		sf::Clock m_clock;
		sf::Sprite m_background;
		GameDataRef m_data;

		sf::Sprite sf_logo;
		sf::RectangleShape rect_mask;
		sf::RectangleShape rect_omask;
		int opaque = 255;
		bool reach_zero = false;
		sf::Vector2f stop_point;

		float initial_speed_sf = -4.0f;
		float initial_speed_rectMask = 4.4f;
		sf::Sound logo_sfx;
	public:
		SplashState(GameDataRef data);
		virtual void VInit();
		virtual void VDraw(float dt);
		virtual void VHandleInput();
		virtual void VUpdate(float dt);
		virtual void VResume();
		virtual void VPause();
		virtual void VExit();
	};
}

