#pragma once
#include <SFML/Graphics.hpp>

namespace UAS_KB
{
	class Animation
	{
	private:
		sf::Sprite m_sprite;
		sf::Texture m_tex;
		sf::Vector2i m_sprite_size;
		int m_frameCount = 0;
		float m_elapsed = 0.0f;
		float m_duration = 0.0f;

		int animFrame = 0;
		int returnFrame = 0;

		int FrameX = 0;
		int FrameY = 0;
	public:
		void Attach(sf::Texture& tex, sf::Sprite& sprite);
		void Change(int m_frameCount, float m_duration, int frameX, int frameY);
		void Update(float dt, sf::Sprite& sprite, bool isRight);
		int GetAnimFrame();
		sf::Sprite GetSprite();
	};
}


