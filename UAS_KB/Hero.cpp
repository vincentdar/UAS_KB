#include "Hero.h"

namespace UAS_KB
{
	Hero::Hero(GameDataRef data): m_data(data) 
	{
	}
	void Hero::VInit()
	{
		m_data->assets.LoadTexture("Hero SpriteR", HERO_ANIMATION_SPRITESHEET_R);
		m_data->assets.LoadTexture("Hero SpriteL", HERO_ANIMATION_SPRITESHEET_L);
		m_textureR = m_data->assets.GetTexture("Hero SpriteR");
		m_textureL = m_data->assets.GetTexture("Hero SpriteL");
		m_sprite.setTexture(m_textureR);
		m_isRight = true;
		m_sprite.setPosition(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
		m_sprite.setScale(2, 2);

		anim.Attach(m_textureR, m_sprite);
		physics.Attach(8.5f, 1.0f);
	}
	void Hero::VHandleInput()
	{
		bool isRunning = false;
		bool isAttacking = false;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			isRunning = true;
			m_sprite.setPosition(physics.CalculatePos(m_sprite.getPosition(), 0, -1, m_stamina));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			isRunning = true;
			m_isRight = false;
			m_sprite.setPosition(physics.CalculatePos(m_sprite.getPosition(), -1, 0, m_stamina));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			isRunning = true;
			m_sprite.setPosition(physics.CalculatePos(m_sprite.getPosition(), 0, 1, m_stamina));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			isRunning = true;
			m_isRight = true;
			m_sprite.setPosition(physics.CalculatePos(m_sprite.getPosition(), 1, 0, m_stamina));
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			isAttacking = true;
		}
		//hero orientation
		if (m_isRight)
		{
			m_sprite.setTexture(m_data->assets.GetTexture("Hero SpriteR"));
		}
		else
		{
			m_sprite.setTexture(m_data->assets.GetTexture("Hero SpriteL"));
		}
		
		//Animation Change
		if (isRunning || isAttacking)
		{
			m_isIdle = false;
			if (isAttacking)
			{
				m_isAttacking = true;
				m_isRunning = false;
				m_stamina = 8.5f;
			}
			else
			{
				m_stamina = 12.0f;
				m_isAttacking = false;
				m_isRunning = true;
			}
		}
		else
		{
			m_stamina = 12.0f;
			m_isAttacking = false;
			m_isRunning = false;
			m_isIdle = true;
		}
	}
	void Hero::VDraw(float dt)
	{
	}
	void Hero::VUpdate(float dt)
	{
		if (m_isRight)
		{
			if (m_isRunning)
			{
				anim.Change(6, 0.5f, 1, 1);
			}
			if (m_isAttacking)
			{
				anim.Change(17, 1.5f, 0, 6);
				if (anim.GetAnimFrame() >= 11 && anim.GetAnimFrame() <= 12)
				{
					m_sprite.move(sf::Vector2f(5.0f, 0.f));
				}
			}
			if (m_isIdle)
			{
				anim.Change(4, 0.5f, 0, 0);
			}
		}
		else
		{
			if (m_isRunning)
			{
				anim.Change(6, 0.5f, 1, 1);
			}
			if (m_isAttacking)
			{
				anim.Change(17, 1.5f, 0, 6);
				if (anim.GetAnimFrame() >= 11 && anim.GetAnimFrame() <= 12)
				{
					m_sprite.move(sf::Vector2f(-5.0f, 0.f));
				}
			}
			if (m_isIdle)
			{
				anim.Change(4, 0.5f, 0, 0);
			}
		}
		
		anim.Update(dt, m_sprite, m_isRight);

	}
	sf::Sprite& Hero::VGetSprite()
	{
		return m_sprite;
	}
}

