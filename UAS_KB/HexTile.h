#pragma once
#include "Game.h"
#include "Animation.h"

namespace UAS_KB
{
	class HexTile
	{
	private:
		GameDataRef m_data;

		sf::Texture m_texture;
		sf::Sprite m_sprite;

		Animation anim;
		bool toggle = false;
		bool clicked = false;
	public:
		HexTile(GameDataRef data);
		virtual void VInit();
		virtual void VHandleInput();
		virtual void VDraw(float dt);
		virtual void VUpdate(float dt);
		virtual sf::Sprite& VGetSprite();
		void ClickRed();
	};
}


