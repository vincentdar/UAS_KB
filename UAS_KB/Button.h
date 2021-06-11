#pragma once
#include "Game.h"

namespace UAS_KB
{
	class Button
	{
	private:
		GameDataRef m_data;

		sf::Texture m_texture;
		sf::Sprite m_sprite;

		bool clicked = false;
		int status = 0;	//0 = Gay, 1 = Blue, 2 = Red
	public:
		Button();
		virtual void VInit(GameDataRef data, sf::Vector2f pos, float scale, std::string textureName);
		virtual void VHandleInput();
		virtual void VDraw(float dt);
		virtual void VUpdate(float dt);
		virtual sf::Sprite& VGetSprite();

		//Using mouse position to determine if it is clicked
		bool OnClicked(bool b, int x, int y)
		{
			if (x >= m_sprite.getPosition().x && x <= m_sprite.getPosition().x + (m_texture.getSize().x * m_sprite.getScale().x))
			{
				if (y >= m_sprite.getPosition().y && y <= m_sprite.getPosition().y + (m_texture.getSize().y * m_sprite.getScale().y))
				{
					return true;
				}
			}
			return false;
			
		}
		void SetClicked(bool b)
		{
			clicked = b;
		}
		bool GetClicked()
		{
			return clicked;
		}

	};
}

