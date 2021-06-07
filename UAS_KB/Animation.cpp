#include "Animation.h"

namespace UAS_KB
{
	void Animation::Attach(sf::Texture& tex, sf::Sprite& sprite)
	{
		m_tex = tex;
		m_frameCount = 0;
		m_sprite_size.x = 50;
		m_sprite_size.y = 37;
		m_duration = 0;
		FrameX = 0;
		FrameY = 0;
	}

	void Animation::Change(int frameCount, float duration, int frameX, int frameY)
	{
		m_frameCount = frameCount;
		m_duration = duration;
		FrameX = frameX;
		FrameY = frameY;
	}

	void Animation::Update(float dt, sf::Sprite& sprite, bool isRight)
	{
		if (isRight)
		{
			m_elapsed += dt;
			animFrame = static_cast<int> ((m_elapsed / m_duration) * m_frameCount) % m_frameCount + FrameX;
			returnFrame = animFrame;
			int addY = 0;
			if (animFrame >= 7)
			{
				addY = animFrame / 7;
				animFrame = animFrame % 7;
			}

			if (m_elapsed > m_frameCount)
			{
				m_elapsed = 0;
			}

			sprite.setTextureRect(sf::IntRect(animFrame * m_sprite_size.x, (FrameY + addY) * m_sprite_size.y,
				m_sprite_size.x, m_sprite_size.y));
		}
		else
		{
			m_elapsed += dt;
			animFrame = static_cast<int> ((m_elapsed / m_duration) * m_frameCount) % m_frameCount + FrameX;
			returnFrame = animFrame;
			int addY = 0;
			if (animFrame >= 7)
			{
				addY = animFrame / 7;
				animFrame = animFrame % 7;
			}

			if (m_elapsed > m_frameCount)
			{
				m_elapsed = 0;
			}

			sprite.setTextureRect(sf::IntRect((6 - animFrame) * m_sprite_size.x, (FrameY + addY) * m_sprite_size.y,
				m_sprite_size.x, m_sprite_size.y));
		}
		
	}

	int Animation::GetAnimFrame()
	{
		return returnFrame;
	}

	sf::Sprite Animation::GetSprite()
	{
		return m_sprite;
	}

}
