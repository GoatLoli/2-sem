#pragma once
#include <string>
#include <SFML/Graphics.hpp>

namespace sn
{
	class Game
	{
		int m_width;
		int m_height;
		std::string m_capture;
		sn::Circle* m_c;
		sn::Triangle* m_t;
		sn::Rectangle* m_rec;
		sn::RectLine* m_recl;
		sn::Vertex* m_l;
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
				int x = rand() % 1000;
				int y = rand() % 600;
				int r = rand() % 100 + 1;
				m_c[i].Setup(x, y, r);
			}

			m_t = new sn::Triangle[m_n];

			for (int i = 0; i < m_n; i++)
			{
				int x = rand() % 1000;
				int y = rand() % 600;
				int r = rand() % 100 + 1;
				m_t[i].Setup(x, y, r);
			}

			m_rec = new sn::Rectangle[m_n];

			for (int i = 0; i < m_n; i++)
			{
				int x = rand() % 1000;
				int y = rand() % 600;
				int a = rand() % 100 + 1;
				int b = rand() % 100 + 1;
				m_rec[i].Setup(x, y, a, b);
			}

			m_recl = new sn::RectLine[m_n];

			for (int i = 0; i < m_n; i++)
			{
				int x = rand() % 1000;
				int y = rand() % 600;
				int a = rand() % 400;
				int ang = rand() % 100 + 1;
				m_recl[i].Setup(x, y, a, ang);
			}
			/*
			m_l = new sn::Vertex[m_n];

			for (int i = 0; i < m_n; i++)
			{
				int x1 = rand() % 1000;
				int y1 = rand() % 600;
				int x2 = rand() % 1000;
				int y2 = rand() % 600;
				m_l[i].Setup(x1, y1, x2, y2);
			}
			*/
		}

		void LifeCycle()
		{
			while (m_window.isOpen())
			{
				//обработка событий
				sf::Event event;
				while (m_window.pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
						m_window.close();
				}

				m_window.clear();
				for (int i = 0; i < m_n; i++)
				{
					m_window.draw(m_c[i].Get());
					m_window.draw(m_t[i].Get());
					m_window.draw(m_rec[i].Get());
					m_window.draw(m_recl[i].Get());
					//m_window.draw(m_l[i].Get(),2);
				}
				m_window.display();
			}
		}
	};
}