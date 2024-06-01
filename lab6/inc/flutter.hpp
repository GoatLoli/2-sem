#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <game.hpp>

namespace sn
{
	class Flutter
	{
		float m_x, m_y;
		float m_alpha;
		float m_v;
		sf::Texture m_texture_flutter;
		sf::Sprite m_sprite_flutter;

	public:

		Flutter() = default;

		Flutter(float x, float y)
		{
			m_x = x;
			m_y = y;
		}

		bool Setup(float x, float y)
		{
			m_x = x;
			m_y = y;
			m_alpha = 0;
			m_v = 0;

			if (!m_texture_flutter.loadFromFile("assets\\flutter.png"))
			{
				std::cout << "Entity file loading error";
				return false;
			}
			m_sprite_flutter.setTexture(m_texture_flutter);

			m_sprite_flutter.setScale(0.15f, 0.15f);
			m_sprite_flutter.getScale();
			m_sprite_flutter.setOrigin(m_texture_flutter.getSize().x / 2, m_texture_flutter.getSize().y / 2);
			m_sprite_flutter.setPosition(m_x, m_y);
			m_sprite_flutter.getPosition().x;
			m_sprite_flutter.getPosition().y;
			m_sprite_flutter.setRotation(m_alpha);
			m_sprite_flutter.getGlobalBounds().width;
		}

		void setVelocity(float dv)
		{
			m_v += dv;
		}
		void Move()
		{
			float alphaRad = acos(-1) * m_alpha / 180;
			m_x += m_v * cos(alphaRad);
			m_y += m_v * sin(alphaRad);
			m_sprite_flutter.setPosition(m_x, m_y);
		}
		void Rotate(float dalpha)
		{
			m_alpha += dalpha;
			m_sprite_flutter.setRotation(m_alpha);
		}
		float X() { return m_x; }
		float Y() { return m_y; }

		
		void PlayerBounds(sf::Window window)
		{

			int m_width = window.getSize().y;
			int m_height = window.getSize().x;

			//left border collision
			if (m_sprite_flutter.getPosition().x < 0) {
	
				m_sprite_flutter.setPosition(0, m_sprite_flutter.getPosition().y);
			};

			//top border collision
			if (m_sprite_flutter.getPosition().y < 0) {
				m_sprite_flutter.setPosition(m_sprite_flutter.getPosition().x, 0);
			};

			//right border collision
			if (m_sprite_flutter.getPosition().x + m_sprite_flutter.getGlobalBounds().width > m_width) {
				m_sprite_flutter.setPosition(m_width - m_sprite_flutter.getGlobalBounds().width, m_sprite_flutter.getPosition().y);
			};

			//bottom border collision
			if (m_sprite_flutter.getPosition().y + m_sprite_flutter.getGlobalBounds().height > m_height) {
				m_sprite_flutter.setPosition(m_sprite_flutter.getPosition().x, m_height - m_sprite_flutter.getGlobalBounds().height);
			};
		}
		
		//void
		sf::Sprite Get()
		{
			return m_sprite_flutter;
		}
	};
}

