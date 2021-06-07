#include "Physics.h"

namespace UAS_KB
{
	void Physics::Attach(float mass, float friction)
	{
		m_mass = mass;
		m_friction = friction;
	}
	sf::Vector2f Physics::CalculatePos(sf::Vector2f currentPos, int x_axis, int y_axis, float stamina)
	{
		sf::Vector2f newPos;
		newPos.x = ((abs(stamina - m_mass * m_friction)) * x_axis) + currentPos.x;
		newPos.y = ((abs(stamina - m_mass * m_friction)) * y_axis) + currentPos.y;
		return newPos;
	}

}
