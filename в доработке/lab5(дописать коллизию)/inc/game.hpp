#pragma once
#include <string>
#include <SFML/Graphics.hpp>

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

	public:
		Game(int width, int height, const std::string& capture)
		{
			m_width = width;
			m_height = height;
			m_capture = capture;
		}

		void Setup(int n)
		{
			m_n = n;//кол-во фигур
			
			//сглаживание
			sf::ContextSettings settings;
			settings.antialiasingLevel = 10;
			//создание и параметры окна
			m_window.setTitle(m_capture);
			m_window.create(sf::VideoMode(m_width, m_height), m_capture, sf::Style::Default, settings);//вместо капчур можно сразу написать название окна

			srand(time(0));//для разных параметров

			m_c = new sn::Circle[m_n];

			for (int i = 0; i < m_n; i++)
			{
				int r = rand() % 100 + 1;
				int x = rand() % (1000 - 2 * r) + r;
				int y = rand() % (600 - 2 * r) + r;		
				int v = rand() % 100 + 20;//[20; 99]
				float alpha = rand() % 7; // [0; 6]
				m_c[i].Setup(x, y, r, v, alpha);
			}

		}

		void TouchBorder(Circle& obj)
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

				//логика
				float dt = clock.getElapsedTime().asSeconds();
				clock.restart();

				//перемещение
				for (int i = 0; i < m_n; i++)					
					m_c[i].Move(dt);

				for (int i = 0; i < m_n; i++)
					TouchBorder(m_c[i]);

				//отображение
				m_window.clear();
				for (int i = 0; i < m_n; i++)
				{
					m_window.draw(m_c[i].Get());
				}
				m_window.display();
			}
		}
	};
}