#include "HexTile.h"

namespace UAS_KB
{
	HexTile::HexTile(GameDataRef data): m_data(data)
	{
	}
	void HexTile::VInit()
	{
		m_texture = m_data->assets.GetTexture("HexTile");
		anim.Attach(m_texture, m_sprite, 60, 52);
		anim.Change(1, 0.5, 0, 0);
		m_sprite.setTexture(m_texture);
		m_sprite.setPosition(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
		m_sprite.setScale(1, 1);

	}
	void HexTile::VHandleInput()
	{	
	}
	void HexTile::VDraw(float dt)
	{
	}
	void HexTile::VUpdate(float dt)
	{
		anim.Update(dt, m_sprite, true);
	}
	sf::Sprite& HexTile::VGetSprite()
	{
		// TODO: insert return statement here
		return m_sprite;
	}
	void HexTile::ClickRed()
	{
		if (toggle)
		{
			anim.Change(1, 0.5, 1, 0);
			toggle = false;
		}
		else if (!toggle)
		{
			anim.Change(1, 0.5, 0, 0);
			toggle = true;
		}
	}
}