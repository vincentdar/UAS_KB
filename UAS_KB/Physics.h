#pragma once
#include <SFML/Graphics.hpp>

namespace UAS_KB
{
	class Physics
	{
	private:
		float m_mass = 0;
		float m_friction = 0;
	public:
		void Attach(float mass, float friction);
		sf::Vector2f CalculatePos(sf::Vector2f currentPos, int x_axis, int y_axis, float stamina);
	};
}

