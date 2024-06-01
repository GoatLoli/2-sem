#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <flutter.hpp>

namespace sn
{
	const float pi = acos(-1);

	class Game
	{
		int m_width;
		int m_height;
		std::string m_capture;
		sn::Circle* m_c;
		int m_n;
		sf::RenderWindow m_window;
		sf::Texture m_texture_bg;
		sf::Sprite m_sprite_bg;

		Flutter m_flutter;

	public:
		Game(int width, int height, const std::string& capture)
		{
			m_width = width;
			m_height = height;
			m_capture = capture;
		}

		bool Setup(int n)
		{
			m_n = n;//кол-во фигур
			
			//сглаживание
			sf::ContextSettings settings;
			settings.antialiasingLevel = 10;
			//создание и параметры окна
			m_window.setTitle(m_capture);
			m_window.create(sf::VideoMode(m_width, m_height), m_capture, sf::Style::Default, settings);//вместо капчур можно сразу написать название окна

			//загрузка текстуры фона
			if (!m_texture_bg.loadFromFile("assets\\sky.png"))
			{
				std::cout << "Backgroung file loading error";
				return false;
			}
			m_sprite_bg.setTexture(m_texture_bg);
			m_sprite_bg.setScale(0.38f, 0.38f);

			//создание сущности
			if (!m_flutter.Setup(100, 100))
				return false;

			srand(time(0));//для разных параметров

			m_c = new sn::Circle[m_n];

			for (int i = 0; i < m_n; i++)
			{
				int r = rand() % 100 + 1;
				int x = rand() % (1000 - 2 * r) + r;
				int y = rand() % (600 - 2 * r) + r;		
				int v = rand() % 100 + 20;
				float alpha = rand() % 7; // [0; 6]
				m_c[i].Setup(x, y, r, v, alpha);
			}

		}
		/*
		//граница экрана
		void BorderBlock(Flutter& obj)
		{
			float x = obj.X();
			float y = obj.Y();
			//float r = obj.R();
			float f_width = m_flutter.

			if (( / 2) >= m_width || x - r <= 0)//кружок касается правой/левой границы
			{
				obj.Alpha(pi - obj.Alpha());
			}
			if (y + r >= m_height || y - r <= 0)
			{
				obj.Alpha(2 * pi - obj.Alpha());
			}
		}
		*/
		void TouchBorderBounce(Circle& obj)
		{
			float x = obj.X();
			float y = obj.Y();
			float r = obj.R();

			if (x + r >= m_width || x - r <= 0)//кружок касается правой/левой границы
			{
				obj.Alpha(pi - obj.Alpha());
			}
			if (y + r >= m_height || y - r <= 0)
			{
				obj.Alpha(2 * pi - obj.Alpha());
			}

		}
		/*
		void Bord()
		{
			if (m_flutter.getPosition().x < 0)
			{
				m_flutter.setPosition(0, m_flutter.getPosition().y);
			};

		}
		*/
		void LifeCycle()
		{
			sf::Clock clock;

			while (m_window.isOpen())
			{
				//обработка событий
				sf::Event event;
				while (m_window.pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
						m_window.close();
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					m_flutter.setVelocity(0.00005);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					m_flutter.setVelocity(-0.00005);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					m_flutter.Rotate(-0.2);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					m_flutter.Rotate(0.2);
				}
				//логика
				float dt = clock.getElapsedTime().asSeconds();
				clock.restart();

				//перемещение
				for (int i = 0; i < m_n; i++)
				{
					m_c[i].Move(dt);
					m_c[i].Key();
				}


				/*
				// Ограничить позицию объекта в пределах окна
				//m_flutter.setPosition(limitPosition(m_flutter.getPosition(), m_window.getSize(), m_flutter.getScale()));

				// //left border collision
				if (m_flutter.getPosition().x < 0)
				{
					m_flutter.setPosition(0, m_flutter.getPosition().y);
				};
				*/
				//отталкивание шариков
				for (int i = 0; i < m_n; i++)
					TouchBorderBounce(m_c[i]);
				//движение флаты
				m_flutter.Move();

				//отображение
				m_window.draw(m_sprite_bg);
				m_window.draw(m_flutter.Get());
				for (int i = 0; i < m_n; i++)
				{
					m_window.draw(m_c[i].Get());
				}
				m_window.display();
			}
		}
	};
}