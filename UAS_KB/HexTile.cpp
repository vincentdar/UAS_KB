#include "HexTile.h"

namespace UAS_KB
{
	HexTile::HexTile()
	{
	}
	void HexTile::VInit(GameDataRef data)
	{
		m_data = data;
		m_texture = m_data->assets.GetTexture("HexTile");
		anim.Attach(m_texture, m_sprite, 60, 52);
		anim.Change(1, 0.5, 2, 0);
		m_sprite.setTexture(m_texture);
		m_sprite.setPosition(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
		m_sprite.setScale(1, 1);
		anim.Update(0.0f, m_sprite, true);
	}
	void HexTile::VHandleInput()
	{	
	}
	void HexTile::VDraw(float dt)
	{
	}
	void HexTile::VUpdate(float dt)
	{
		if (status == 0)
		{
			anim.Change(1, 0.5, 2, 0);
		}
		anim.Update(dt, m_sprite, true);
	}
	sf::Sprite& HexTile::VGetSprite()
	{
		// TODO: insert return statement here
		return m_sprite;
	}
	void HexTile::SetPosition(float x, float y)
	{
		m_sprite.setPosition(x, y);
	}
	void HexTile::ClickBlue(int x, int y)
	{
		sf::Vector2f origin = m_sprite.getPosition();
		if (x >= origin.x && x <= origin.x + 60)
		{
			if (y >= origin.y + 13 && y <= origin.y + 52 - 13)
			{
				if (status == 0)
				{
					anim.Change(1, 0.5, 1, 0);
					status = 1;
				}
			}
		}
	}
	void HexTile::ClickRed(int x, int y)
	{
		sf::Vector2f origin = m_sprite.getPosition();
		if (x >= origin.x && x <= origin.x + 60)
		{
			if (y >= origin.y + 13 && y <= origin.y + 52 - 13)
			{
				if (status == 0)
				{
					anim.Change(1, 0.5, 0, 0);
					status = 2;
				}
			}
		}
	}
	void HexTile::SetStatus(int status)
	{
		this->status = status;
	}
	int HexTile::GetStatus()
	{
		return status;
	}
	void HexTile::SetVisited(bool b)
	{
		visited = b;
	}
	bool HexTile::IsVisited()
	{
		return visited;
	}
}