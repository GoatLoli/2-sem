#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <bullet.hpp>
#include <vector>

namespace mt
{

	class Ship
	{
		const int m_bulletR = 10;
		float m_v_bullet = 200;
		
		float m_x, m_y;
		float m_alpha;
		float m_v;
		float m_r;
		sf::Texture m_textureShip;
		sf::Sprite m_spriteShip;
		float m_scaleFactor = 0.2f;
		
		

	public:
		std::vector<Bullet*> m_bullet;
		
		Ship() = default;
		// !!!
		Ship(float x, float y)
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

			// Загрузка текстуры фона
			if (!m_textureShip.loadFromFile("assets\\falcon.png"))
			{
				std::cout << "Error while loading falcon.png" << std::endl;
				return false;
			}
			m_spriteShip.setTexture(m_textureShip);

			m_spriteShip.setScale(m_scaleFactor, m_scaleFactor);
			m_spriteShip.setOrigin(m_textureShip.getSize().x / 2, m_textureShip.getSize().y / 2);
			m_spriteShip.setPosition(m_x, m_y);
			m_spriteShip.setRotation(m_alpha);

			if (m_textureShip.getSize().x > m_textureShip.getSize().y)
				m_r = m_scaleFactor * m_textureShip.getSize().x / 2;
			else
				m_r = m_scaleFactor * m_textureShip.getSize().y / 2;

			//bullet.Setup(100, 100, 20, 10, 10);
		}

		void creatbullet()
		{
			float alphaRad = acos(-1) * m_alpha / 180;
			//push_back новая переменная в вектор
			m_bullet.push_back(new Bullet(m_x, m_y, m_bulletR, (m_v + m_v_bullet) * cos(alphaRad), (m_v + m_v_bullet) * sin(alphaRad)));
		}

		void setVelocity(float dv)
		{
			m_v += dv;

		}

		float V() { return m_v; }

		void Move(float dt)
		{
			for (int i = 0; i < m_bullet.size(); i++)
				m_bullet[i]->Move(dt);

			float alphaRad = acos(-1) * m_alpha / 180;
			m_x += m_v * cos(alphaRad) * dt;
			m_y += m_v * sin(alphaRad) * dt;
			m_spriteShip.setPosition(m_x, m_y);
		}

		void Attack()
		{
			creatbullet();
		}

		float R() { return m_r; }
		float X() { return m_x; }
		float Y() { return m_y; }

		void Rotate(float dalpha)
		{
			m_alpha += dalpha;
			m_spriteShip.setRotation(m_alpha);
		}

		sf::Sprite Get()
		{
			return m_spriteShip;
		}

		void delbul(int i)
		{
			//аннигиляция i-ой пули из вектора (erase убирает 1 элемент)
			m_bullet.erase(m_bullet.begin() + i);
		}
		

		Bullet* GetBullet(int i) { return m_bullet[i]; }

		int numberOfBullets() { return m_bullet.size(); } //кол-во пуль
		
	};

}