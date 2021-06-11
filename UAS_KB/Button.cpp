#include "Button.h"

UAS_KB::Button::Button()
{
}

void UAS_KB::Button::VInit(GameDataRef data, sf::Vector2f pos, float scale, std::string textureName)
{
	m_data = data;
	m_texture = m_data->assets.GetTexture(textureName);
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(pos);
	m_sprite.scale(scale, scale);
}

void UAS_KB::Button::VHandleInput()
{
}

void UAS_KB::Button::VDraw(float dt)
{
}

void UAS_KB::Button::VUpdate(float dt)
{
}

sf::Sprite& UAS_KB::Button::VGetSprite()
{
	// TODO: insert return statement here
	return m_sprite;
}
