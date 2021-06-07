#pragma once
#include "IState.h"
#include "Game.h"
#include "HexTile.h"
#include <SFML/Graphics.hpp>

namespace UAS_KB
{
	class HexGame: public IState
	{
	private:
		sf::Clock m_clock;
		sf::Sprite m_background;
		GameDataRef m_data;
		
		//Game Components
		HexTile* tile;
	public:
		HexGame(GameDataRef data);
		virtual void VInit();
		virtual void VDraw(float dt);
		virtual void VHandleInput();
		virtual void VUpdate(float dt);
		virtual void VResume();
		virtual void VPause();
		virtual void VExit();
	};

}

