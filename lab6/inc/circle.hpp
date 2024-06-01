#pragma once
#include <SFML/Graphics.hpp>

namespace sn
{
	class Circle
	{
		float m_r;
		float m_x, m_y;
		float m_v;
		float m_alpha;
		sf::CircleShape m_shape;

	public:
		Circle() = default;

		Circle(float x, float y, float r, float v, float alpha)
		{
			Setup(x, y, r, v, alpha);
		}

		void Setup(float x, float y, float r, float v, float alpha)
		{
			m_x = x;
			m_y = y;
			m_r = r;
			m_v = v;
			m_alpha = alpha;
			m_shape.setOrigin(m_r, m_r);
			m_shape.setRadius(m_r);
			m_shape.setPosition(m_x, m_y);
			m_shape.setFillColor(sf::Color(255, 253, 254));
			m_shape.setOutlineThickness(-10.f);
			m_shape.setOutlineColor(sf::Color(254, 238, 238));
		}

		sf::CircleShape Get()
		{
			return m_shape;
		}

		float X() { return m_x; }
		float Y() { return m_y; }
		float R() { return m_r; }
		float Alpha() { return m_alpha; }
		void Alpha(float alpha)
		{
			m_alpha = alpha;
		}

		void Move(float dt)
		{
			float vx = m_v * cos(m_alpha);
			float vy = m_v * sin(m_alpha);
			m_x += vx * dt;//дельта t
			m_y += vy * dt;
			m_shape.setPosition(m_x, m_y);
		}
		
		void Key()
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				m_x -= 0.25;
				m_shape.setPosition(m_x, m_y);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				m_x += 0.25;
				m_shape.setPosition(m_x, m_y);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				m_y -= 0.25;
				m_shape.setPosition(m_x, m_y);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				m_y += 0.25;
				m_shape.setPosition(m_x, m_y);
			}
			
		}
		

	};

}